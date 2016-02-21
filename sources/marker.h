


#ifndef MARKER_H
#define MARKER_H


#include <vector>
#include <iostream>
#include <opencv2/opencv.hpp>

#include "geometry_types.h"


// This class represents a marker.
class Marker
{

	public :
		
		int id;								// Id of  the marker.
		Transformation transformation;		// Marker transformation wrt to the camera.
		std::vector<cv::Point2f> points;	// ...

	public :
		
		// ...
		Marker();
		
		// ...
		friend bool operator < ( const Marker& M1, const Marker& M2 );
		
		// ...
		friend std::ostream& operator << ( std::ostream& str, const Marker& M );
		
		// ...
		static cv::Mat rotate( cv::Mat in );
		
		// ...
		static int hammDistMarker( cv::Mat bits );
		
		// ...
		static int mat2id( const cv::Mat& bits );
		
		// ...
		static int getMarkerId( cv::Mat& in, int& nRotations );

		// Helper function to draw the marker contour over the image.
		void drawContour( cv::Mat& image, cv::Scalar color = CV_RGB( 0, 250, 0 ) ) const;

};


#endif // MARKER_H


