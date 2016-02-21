


#ifndef MARKER_DETECTOR_H
#define MARKER_DETECTOR_H


#include <vector>
#include <opencv2/opencv.hpp>

#include "camera_calibration.h"
#include "marker.h"


// A marker is usually designed as a rectangle image holding black and white areas inside it.
// Due to known limitations, the marker detection procedure is a simple one:
// 1.   we need to find closed contours on the input image;
// 2.   unwarp the image inside it to a rectangle;
// 3.   check the unwarped image against our marker model.
// In this sample a 5x5 marker will be used.


// A top-level class encapsulating marker detector algorithm.
class MarkerDetector
{
	private :
		
		float minContourLengthAllowed;
		cv::Size markerSize;			// Size of the original marker image in pixels.
		cv::Mat camMatrix;				// Instrinsics camera 3x3 matrix.
		cv::Mat distCoeff;				// Distortion coefficient vector 4x1.
		std::vector<Transformation> transformations;
		std::vector<int> ids;
		cv::Mat grayscaleImage;
		cv::Mat thresholdImg;
		cv::Mat canonicalMarkerImage;
		std::vector< std::vector<cv::Point> > contours;
		std::vector<cv::Point3f> markerCorners3D;
		std::vector<cv::Point2f> markerCorners2D;

	public :
		
		// Initialize a new instance of marker detector object: 
		// camera calibration (intrinsic and distorsion components) necessary for pose estimation.
		MarkerDetector( CameraCalibration calibration );
		
		// ...
		void processFrame( const cv::Mat& frame );
		
		// ...
		const std::vector<Transformation>& getTransformations() const;
		
		// ...
		const std::vector<int>& getIds() const;

	protected :
		
		// ...
		void findContours( const cv::Mat& thresholdImg, std::vector< std::vector<cv::Point> >& contours, int minContourPointsAllowed );
		
		// ...
		void findMarkerCandidates( const std::vector< std::vector<cv::Point> >& contours, std::vector<Marker>& detectedMarkers );
		
		// ...
		void detectMarkers( const cv::Mat& grayscale, std::vector<Marker>& detectedMarkers );
		
		// ...
		void estimatePosition( std::vector<Marker>& detectedMarkers );

		// ...
		float perimeter( const std::vector<cv::Point2f>& a );
		
		// ...
		bool isInto( cv::Mat& contour, std::vector<cv::Point2f>& b );

};


#endif // MARKER_DETECTOR_H


