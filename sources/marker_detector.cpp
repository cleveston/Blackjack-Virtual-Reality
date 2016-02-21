


#include <iostream>

#include "marker_detector.h"
#include "marker.h"


// ...
MarkerDetector::MarkerDetector(CameraCalibration calibration)
{
	minContourLengthAllowed = 100.0f;
	markerSize = cv::Size(100, 100);
	cv::Mat(3, 3, CV_32F, const_cast<float*>(&calibration.getIntrinsic().data[0])).copyTo(camMatrix);
	cv::Mat(4, 1, CV_32F, const_cast<float*>(&calibration.getDistorsion().data[0])).copyTo(distCoeff);
	bool centerOrigin = true;
	if (centerOrigin) {
		markerCorners3D.push_back(cv::Point3f(-0.5f, -0.5f, 0.0f));
		markerCorners3D.push_back(cv::Point3f(+0.5f, -0.5f, 0.0f));
		markerCorners3D.push_back(cv::Point3f(+0.5f, +0.5f, 0.0f));
		markerCorners3D.push_back(cv::Point3f(-0.5f, +0.5f, 0.0f));
	}
	else {
		markerCorners3D.push_back(cv::Point3f(0.0f, 0.0f, 0.0f));
		markerCorners3D.push_back(cv::Point3f(1.0f, 0.0f, 0.0f));
		markerCorners3D.push_back(cv::Point3f(1.0f, 1.0f, 0.0f));
		markerCorners3D.push_back(cv::Point3f(0.0f, 1.0f, 0.0f));
	}
	markerCorners2D.push_back(cv::Point2f(0, 0));
	markerCorners2D.push_back(cv::Point2f(float(markerSize.width - 1), 0.0f));
	markerCorners2D.push_back(cv::Point2f(float(markerSize.width - 1), float(markerSize.height - 1)));
	markerCorners2D.push_back(cv::Point2f(0.0f, float(markerSize.height - 1)));
}


// The workflow of the marker detection routine is the following:
// 1.   convert the input image to grayscale;
// 2.   perform a binary threshold operation;
// 3.   detect contours;
// 4.   search for possible markers;
// 5.   detect and decode markers;
// 6.   estimate marker 3D pose.
void MarkerDetector::processFrame(const cv::Mat& frame)
{
	// ...
	std::vector<Marker> markers;
	//cv::Mat bgraMat( frame.rows, frame.cols, CV_8UC4 );
	//cv::cvtColor( frame, bgraMat, CV_BGR2BGRA );
	// Convert the image to grayscale.
	// See: http://docs.opencv.org/modules/imgproc/doc/miscellaneous_transformations.html#cvtcolor
	// The conversion to grayscale is necessary because markers usually contain only black and white blocks.
	// So it is much easier to operate with them using grayscale images.
	//cv::cvtColor( bgraMat, grayscaleImage, CV_BGRA2GRAY );
	cv::cvtColor(frame, grayscaleImage, CV_BGR2GRAY);

	// Make it binary.
	// See: http://docs.opencv.org/modules/imgproc/doc/miscellaneous_transformations.html#adaptivethreshold
	// The binarization operation will transform each pixel of our image to black (0 intensity) or white (255 intensity).
	// This step is required to find contours.
	cv::threshold(grayscaleImage, thresholdImg, 127.0, 255.0, cv::THRESH_BINARY_INV);

#ifdef _DEBUG
	cv::imshow("THR", thresholdImg);
#endif

	// Detect contours.
	MarkerDetector::findContours(thresholdImg, contours, grayscaleImage.cols / 5);

#ifdef _DEBUG
	cv::Mat contoursImage(thresholdImg.size(), CV_8UC1);
	contoursImage = cv::Scalar(0);
	// See: http://docs.opencv.org/modules/imgproc/doc/structural_analysis_and_shape_descriptors.html#drawcontours
	cv::drawContours(contoursImage, contours, -1, cv::Scalar(255), 2, CV_AA);
	cv::imshow("CNT", contoursImage);
#endif

	// Find closed contours that can be approximated with 4 points.
	findMarkerCandidates(contours, markers);

	// Find if there are markers.
	detectMarkers(grayscaleImage, markers);

	// Calcualte their poses.
	estimatePosition(markers);
	// Sort by id.
	// See: http://www.cplusplus.com/reference/algorithm/sort/
	std::sort(markers.begin(), markers.end());
	// ...
	transformations.clear();
	ids.clear();
	for (size_t i = 0; i < markers.size(); i++) {
		transformations.push_back(markers[i].transformation);
		ids.push_back(markers[i].id);
	}
}


// ...
const std::vector<Transformation>& MarkerDetector::getTransformations() const
{
	return transformations;
}


// ...
const std::vector<int>& MarkerDetector::getIds() const
{
	return ids;
}


// Each marker usually looks like a square figure with black and white areas inside it.
// So the best way to locate a marker is to find closed contours and approximate them with polygons of 4 vertices.
// This function will detect contours on the input binary image.
// The return value is a list of polygons where each polygon represents a single contour.
// This function skips contours that have their perimeter in pixel value set to be less than a specific input threshold.
// This because we are not interested in small contours.
void MarkerDetector::findContours(const cv::Mat& thresholdImg,
	std::vector< std::vector<cv::Point> >& contours,
	int minContourPointsAllowed)
{
	std::vector< std::vector<cv::Point> > allContours;
	// See: http://docs.opencv.org/modules/imgproc/doc/structural_analysis_and_shape_descriptors.html#findcontours
	cv::findContours(thresholdImg, allContours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
	contours.clear();
	for (size_t i = 0; i < allContours.size(); i++) {
		int contourSize = allContours[i].size();
		if (contourSize > minContourPointsAllowed) { contours.push_back(allContours[i]); }
	}

#ifdef _DEBUG
	cv::Mat contoursImage(thresholdImg.size(), CV_8UC1);
	contoursImage = cv::Scalar(0);
	cv::drawContours(contoursImage, contours, -1, cv::Scalar(255), 2, CV_AA);
	cv::imshow("Contours Image", contoursImage);
#endif
}


// The polygon approximation stage is used to decrease the number of points 
// describing the contour shape.
// This is a good quality check to filter out areas without markers 
// because they can always be represented with a polygon that contains 4 vertices.
// If the approximated polygon has more than (or fewer than) 4 vertices, 
// it is definitely not what we are looking for...
void MarkerDetector::findMarkerCandidates(const std::vector<std::vector<cv::Point> >& contours, std::vector<Marker>& detectedMarkers)
{
	std::vector<cv::Point> approxCurve;
	std::vector<Marker> possibleMarkers;
	// For each contour, analyze if it is a paralelepiped likely to be the marker.
	for (size_t i = 0; i < contours.size(); i++) {
		// Approximate a polygonal curve with the specified precision.
		// Approximate a curve or a polygon with another curve-polygon with less vertices 
		// so that the distance between them is less or equal to the specified precision. 
		// It uses the Douglas-Peucker algorithm http://en.wikipedia.org/wiki/Ramer-Douglas-Peucker_algorithm
		// See: http://docs.opencv.org/modules/imgproc/doc/structural_analysis_and_shape_descriptors.html#approxpolydp
		cv::approxPolyDP(contours[i], approxCurve, double(contours[i].size()) * 0.05, true);
		// We interested only in polygons that contains only four vertices.
		if (approxCurve.size() != 4) { continue; }
		// And they have to be convex.
		// See: http://docs.opencv.org/modules/imgproc/doc/structural_analysis_and_shape_descriptors.html#iscontourconvex
		if (!cv::isContourConvex(approxCurve)) { continue; }
		// Ensure that the distace between consecutive points is large enough.
		float minDist = std::numeric_limits<float>::max();
		for (int i = 0; i < 4; i++) {
			cv::Point side = approxCurve[i] - approxCurve[(i + 1) % 4];
			float squaredSideLength = float(side.dot(side));
			minDist = std::min(minDist, squaredSideLength);
		}
		// Check that distance is not very small.
		if (minDist < minContourLengthAllowed) { continue; }
		// ...
		Marker m;
		for (int i = 0; i < 4; i++) { m.points.push_back(cv::Point2f(float(approxCurve[i].x), float(approxCurve[i].y))); }
		// Sort the points in anti-clockwise order:
		// trace a line between the first and second point and 
		// if the third point is at the right side, then the points are anti-clockwise.
		cv::Point v1 = m.points[1] - m.points[0];
		cv::Point v2 = m.points[2] - m.points[0];
		double o = (v1.x * v2.y) - (v1.y * v2.x);
		// If the third point is in the left side, then sort in anti-clockwise order.
		if (o < 0.0) { std::swap(m.points[1], m.points[3]); }
		possibleMarkers.push_back(m);
	}
	// Remove these elements which corners are too close to each other.
	// First detect candidates for removal:
	std::vector< std::pair<int, int> > tooNearCandidates;
	for (size_t i = 0; i < possibleMarkers.size(); i++) {
		const Marker& m1 = possibleMarkers[i];
		// Calculate the average distance of each corner to the nearest corner of the other marker candidate.
		for (size_t j = i + 1; j < possibleMarkers.size(); j++) {
			const Marker& m2 = possibleMarkers[j];
			float distSquared = 0.0f;
			for (int c = 0; c < 4; c++) {
				cv::Point v = m1.points[c] - m2.points[c];
				distSquared += v.dot(v);
			}
			distSquared /= 4.0f;
			if (distSquared < 100.0f) { tooNearCandidates.push_back(std::pair<int, int>(i, j)); }
		}
	}
	// Mark for removal the element of  the pair with smaller perimeter.
	std::vector<bool> removalMask(possibleMarkers.size(), false);
	for (size_t i = 0; i < tooNearCandidates.size(); i++) {
		float p1 = MarkerDetector::perimeter(possibleMarkers[tooNearCandidates[i].first].points);
		float p2 = MarkerDetector::perimeter(possibleMarkers[tooNearCandidates[i].second].points);
		size_t removalIndex;
		if (p1 > p2) { removalIndex = tooNearCandidates[i].second; }
		else { removalIndex = tooNearCandidates[i].first; }
		removalMask[removalIndex] = true;
	}
	// Return candidates.
	detectedMarkers.clear();
	for (size_t i = 0; i < possibleMarkers.size(); i++) {
		if (!removalMask[i]) { detectedMarkers.push_back(possibleMarkers[i]); }
	}
}


// This function takes the input list of parallelepipeds and verifies wheter they are markers or not.
// The following are the main steps performed:
// 1.   Removal of the perspective projection to obtain a frontal view of the rectangle area.
// 2.   Perform a thresholding of the image using the Otsu algorithm (see: Marker::getMarkerId).
// 3.   Identify the marker internal code: the marker is divided into a 7x7 grid.
//      The internal 5x5 cells contain ID information, and the rest represent the external black border.
void MarkerDetector::detectMarkers(const cv::Mat& grayscale, std::vector<Marker>& detectedMarkers)
{
	std::vector<Marker> goodMarkers;
	// Identify the markers.
	for (size_t i = 0; i < detectedMarkers.size(); i++) {
		Marker& marker = detectedMarkers[i];
		// To get the rectangle marker image we have to unwarp the input image using the proper perspective transformation.
		// This matrix can be retrieved from pairs of corresponding points (marker coords in image space + square marker image coords).
		// Find the perspective transformation that brings current marker to rectangular form.
		// See: http://docs.opencv.org/modules/imgproc/doc/geometric_transformations.html#getperspectivetransform
		cv::Mat markerTransform = cv::getPerspectiveTransform(marker.points, markerCorners2D);
		// Transform image to get a canonical marker image.
		// See: http://docs.opencv.org/modules/imgproc/doc/geometric_transformations.html#warpperspective
		cv::warpPerspective(grayscale, canonicalMarkerImage, markerTransform, markerSize);

#ifdef _DEBUG
		cv::Mat markerImage = grayscale.clone();
		marker.drawContour(markerImage);
		cv::Mat markerSubImage = markerImage(cv::boundingRect(marker.points));
		cv::imshow("Source Marker", markerSubImage);
		cv::imshow("Marker After Warp", canonicalMarkerImage);
#endif

		int nRotations;
		int id = Marker::getMarkerId(canonicalMarkerImage, nRotations);
		if (id != -1) {
			// After finding the right marker orientation, 
			// we rotate the corners of the marker respectively to conform to their order.
			marker.id = id;
			// Sort the points so that they are always in the same order no matter the camera orientation.
			std::rotate(marker.points.begin(), marker.points.begin() + 4 - nRotations, marker.points.end());
			goodMarkers.push_back(marker);
		}
	}
	// Refine marker corners using sub pixel accuracy.
	if (goodMarkers.size() > 0) {
		// After detecting a marker and decoding its ID, we will refine its corners.
		// This operation will ease the next step consisting in the estimation of the marker 3D position.
		// To find the corner location with subpixel accuracy we use the cv::cornerSubPix function:
		// 1.   prepare the input data copying the list of vertices,
		// 2.   then we call cv::cornerSubPix with the proper input arguments,
		// 3.   finally we copy the refined locations back to marker corners.
		// *   We do not use cv::cornerSubPix in the earlier stages of marker detection due to its complexity.
		//     It is very computationally expensive to call this function for large numbers of points.
		//     Therefore we do this only for valid markers.
		std::vector<cv::Point2f> preciseCorners(4 * goodMarkers.size());
		for (size_t i = 0; i < goodMarkers.size(); i++) {
			const Marker& marker = goodMarkers[i];
			for (int c = 0; c < 4; c++) { preciseCorners[i * 4 + c] = marker.points[c]; }
		}
		cv::TermCriteria termCriteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER | cv::TermCriteria::EPS, 30, 0.01);
		cv::cornerSubPix(grayscale, preciseCorners, cv::Size(5, 5), cv::Size(-1, -1), termCriteria);
		// Copy refined corners position back to markers.
		for (size_t i = 0; i < goodMarkers.size(); i++) {
			Marker& marker = goodMarkers[i];
			for (int c = 0; c < 4; c++) { marker.points[c] = preciseCorners[i * 4 + c]; }
		}
	}

#ifdef _DEBUG
	cv::Mat markerCornersMat(grayscale.size(), grayscale.type());
	markerCornersMat = cv::Scalar(0);
	for (size_t i = 0; i < goodMarkers.size(); i++) { goodMarkers[i].drawContour(markerCornersMat, cv::Scalar(255)); }
	cv::imshow("Markers Refined Edges", grayscale * 0.5 + markerCornersMat);
#endif

	detectedMarkers = goodMarkers;
}


// We can use the precise location of marker corners to estimate a transformation between our camera and a marker in 3D.
// This operation is known as pose estimation from 2D-3D correspondences.
// This process finds an Euclidean transformation (rotation + translation) between the camera and the object.
// We define the 3D coordinates of marker corners putting our marker on the XY plane (Z=0),
// with the marker center in the origin (0,0,0).
// Then we find the camera location using the 2D-3D correspondences as input for cv::solvePnP.
void MarkerDetector::estimatePosition(std::vector<Marker>& detectedMarkers)
{
	for (size_t i = 0; i < detectedMarkers.size(); i++) {
		Marker& m = detectedMarkers[i];
		cv::Mat Rvec;
		cv::Mat_<float> Tvec;
		cv::Mat raux;
		cv::Mat taux;
		// See: http://docs.opencv.org/modules/calib3d/doc/camera_calibration_and_3d_reconstruction.html#solvepnp
		cv::solvePnP(markerCorners3D, m.points, camMatrix, distCoeff, raux, taux);
		// See; http://docs.opencv.org/modules/core/doc/basic_structures.html#mat-convertto
		raux.convertTo(Rvec, CV_32F);
		taux.convertTo(Tvec, CV_32F);
		cv::Mat_<float> rotMat(3, 3);
		// See: http://docs.opencv.org/modules/calib3d/doc/camera_calibration_and_3d_reconstruction.html#rodrigues
		cv::Rodrigues(Rvec, rotMat);
		// Copy to transformation matrix.
		m.transformation = Transformation();
		for (int col = 0; col < 3; col++) {
			for (int row = 0; row < 3; row++) {
				// Copy rotation component.
				m.transformation.r().mat[row][col] = rotMat(row, col);
			}
			// Copy translation component.
			m.transformation.t().data[col] = Tvec(col);
		}
		// Since solvePnP finds camera location, with regard to the marker pose, 
		// to get marker pose with regard to the camera we invert it.
		m.transformation = m.transformation.getInverted();
	}
}


// ...
float MarkerDetector::perimeter(const std::vector<cv::Point2f>& a)
{
	float sum = 0;
	float dx;
	float dy;
	for (size_t i = 0; i < a.size(); i++) {
		size_t i2 = (i + 1) % a.size();
		dx = a[i].x - a[i2].x;
		dy = a[i].y - a[i2].y;
		sum += sqrt(dx * dx + dy * dy);
	}
	return sum;
};


// ...
bool MarkerDetector::isInto(cv::Mat& contour, std::vector<cv::Point2f>& b)
{
	for (size_t i = 0; i < b.size(); i++) {
		if (cv::pointPolygonTest(contour, b[i], false) > 0) { return true; }
	}
	return false;
}


