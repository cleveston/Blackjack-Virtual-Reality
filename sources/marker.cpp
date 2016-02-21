


#include "marker.h"


// ...
Marker::Marker()
{
	id = -1;
}


// ...
bool operator < (const Marker& M1, const Marker& M2)
{
	return M1.id < M2.id;
}


// Rotate the input image 90 degrees clockwise.
cv::Mat Marker::rotate(cv::Mat in)
{
	cv::Mat out;
	in.copyTo(out);
	for (int i = 0; i < in.rows; i++) {
		for (int j = 0; j < in.cols; j++) {
			out.at<uchar>(i, j) = in.at<uchar>(in.cols - j - 1, i);
		}
	}
	return out;
}


// ...
int Marker::hammDistMarker(cv::Mat bits)
{
	int ids[4][5] = { { 1, 0, 0, 0, 0 },
	{ 1, 0, 1, 1, 1 },
	{ 0, 1, 0, 0, 1 },
	{ 0, 1, 1, 1, 0 } };
	int dist = 0;
	for (int y = 0; y < 5; y++) {
		// Hamming distance to each possible word.
		int minSum = int(1e5);
		for (int p = 0; p < 4; p++) {
			int sum = 0;
			// Now, count.
			for (int x = 0; x < 5; x++) {
				sum += bits.at<uchar>(y, x) == ids[p][x] ? 0 : 1;
			}
			if (minSum > sum) { minSum = sum; }
		}
		// Do the and.
		dist += minSum;
	}
	return dist;
}


// ...
int Marker::mat2id(const cv::Mat& bits)
{
	int val = 0;
	for (int y = 0; y < 5; y++) {
		val <<= 1;
		if (bits.at<uchar>(y, 1)) { val |= 1; }
		val <<= 1;
		if (bits.at<uchar>(y, 3)) { val |= 1; }
	}
	return val;
}


// This function tests the input image to verify if it is a valid marker image.
// Then the function tries to extract the bit mask with the marker code.
// As we expect our marker to contain only black and white colors,
// we can perform Otsu thresholding to remove gray pixels.
int Marker::getMarkerId(cv::Mat& markerImage, int& nRotations)
{
	assert(markerImage.rows == markerImage.cols);
	assert(markerImage.type() == CV_8UC1);
	cv::Mat gray = markerImage;
	// Threshold image.
	cv::threshold(gray, gray, 125, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);

#ifdef _DEBUG
	cv::imshow("Binary Marker", gray);
#endif

	// Check the marker black border.
	int cellSize = markerImage.rows / 7;
	for (int y = 0; y < 7; y++) {
		int inc = 6;
		// For first and last row, check the whole border.
		if ((y == 0) || (y == 6)) { inc = 1; }
		for (int x = 0; x < 7; x += inc) {
			int cellX = x * cellSize;
			int cellY = y * cellSize;
			cv::Mat cell = gray(cv::Rect(cellX, cellY, cellSize, cellSize));
			int nZ = cv::countNonZero(cell);
			// Check if it can not be a marker because the border element is not black!
			if (nZ > (cellSize * cellSize) / 2) { return -1; }
		}
	}
	// Markers are divided in 7x7 regions, 
	// of which the inner 5x5 belongs to marker info the external border should be entirely black.
	// The codification employed is a mod of the Hamming code (see: http://en.wikipedia.org/wiki/Hamming_code).
	// In total, each word has only 2 bits of information out of the 5 bits employed.
	// The other 3 are employed for error detection.
	// Therefore, we can have up to 1024 different IDs (2^2^5).
	// *   The main difference with the Hamming code is that the first bit (parity of bits 3 and 5) is inverted.
	//     So, ID 0 (00000 in Hamming code) becomes 10000 in our code.
	//     The idea is to prevent a completely black rectangle from being a valid marker,
	//     with the goal of reducing the probability of false positives with objects in the environment.
	cv::Mat bitMatrix = cv::Mat::zeros(5, 5, CV_8UC1);
	// Get information(for each inner square, determine if it is black or white).
	for (int y = 0; y < 5; y++) {
		for (int x = 0; x < 5; x++) {
			// Counting the number of black and white pixels for each cell gives us a 5x5 bit mask with marker code.
			// To count the number of non-zero pixels on a certain image, the cv::countNonZero function is used.
			// This function counts non-zero array elements from a given 1D or 2D array.
			int cellX = (x + 1) * cellSize;
			int cellY = (y + 1) * cellSize;
			cv::Mat cell = gray(cv::Rect(cellX, cellY, cellSize, cellSize));
			int nZ = cv::countNonZero(cell);
			if (nZ > (cellSize * cellSize) / 2) { bitMatrix.at<uchar>(y, x) = 1; }
		}
	}
	// The same marker can have 4 possible representation depending on the point of view of the camera.
	// Therefore we have to find the correct marker position.
	// Since we introduced 3 parity bits for each 2 bits of information,
	// we can find the Hamming distance for each possible marker orientation.
	// The correct marker position will have 0 Hamming distance error, while the other rotations won't.
	// Check all possible rotations.
	cv::Mat rotations[4];
	int distances[4];
	rotations[0] = bitMatrix;
	distances[0] = Marker::hammDistMarker(rotations[0]);
	std::pair<int, int> minDist(distances[0], 0);
	for (int i = 1; i < 4; i++) {
		// Get the hamming distance to the nearest possible word.
		rotations[i] = Marker::rotate(rotations[i - 1]);
		distances[i] = Marker::hammDistMarker(rotations[i]);
		if (distances[i] < minDist.first) {
			minDist.first = distances[i];
			minDist.second = i;
		}
	}
	nRotations = minDist.second;
	if (minDist.first == 0) { return Marker::mat2id(rotations[minDist.second]); }
	return -1;
}


// Helper function to draw the marker contour over the image.
void Marker::drawContour(cv::Mat& image, cv::Scalar color) const
{
	int thickness = 2;
	cv::line(image, points[0], points[1], color, thickness, CV_AA);
	cv::line(image, points[1], points[2], color, thickness, CV_AA);
	cv::line(image, points[2], points[3], color, thickness, CV_AA);
	cv::line(image, points[3], points[0], color, thickness, CV_AA);
}


