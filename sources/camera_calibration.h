


#ifndef CAMERA_CALIBRATION_H
#define CAMERA_CALIBRATION_H


#include "geometry_types.h"


// A camera calibraiton class that stores intrinsic matrix and distorsion coefficients.
class CameraCalibration
{

	private :
		
		Matrix33 intrinsic;
		Vector4  distorsion;

	public :

		// ...
		CameraCalibration() {};
		
		// ...
		CameraCalibration( float fx, float fy, float cx, float cy ) {
			for( int i = 0; i < 3; i++ ) {
				for( int j = 0; j < 3; j++ ) {
					intrinsic.mat[i][j] = 0.0f; } }
			intrinsic.mat[0][0] = fx;
			intrinsic.mat[1][1] = fy;
			intrinsic.mat[0][2] = cx;
			intrinsic.mat[1][2] = cy;
			for( int i = 0; i < 4; i++ ) { distorsion.data[i] = 0.0f; } };
		
		// ...
		CameraCalibration( float fx, float fy, float cx, float cy, float distorsionCoeff[4] ) {
			for( int i = 0; i < 3; i++ ) {
				for( int j = 0; j < 3; j++ ) { 
					intrinsic.mat[i][j] = 0.0f; } }
			intrinsic.mat[0][0] = fx;
			intrinsic.mat[1][1] = fy;
			intrinsic.mat[0][2] = cx;
			intrinsic.mat[1][2] = cy;
			for( int i = 0; i < 4; i++ ) { distorsion.data[i] = distorsionCoeff[i]; } };
		
		// ...
		void getMatrix3x4( float cparam[3][4] ) const {
			for( int j = 0; j < 3; j++ ) {
				for( int i = 0; i < 3; i++ ) {
					cparam[i][j] = intrinsic.mat[i][j]; } }
			for( int i = 0; i < 4; i++ ) { cparam[3][i] = distorsion.data[i]; } };
		
		// ...
		const Matrix33& getIntrinsic() const { return intrinsic; };
		
		// ...
		const Vector4&  getDistorsion() const { return distorsion; };

};


#endif // CAMERA_CALIBRATION_H


