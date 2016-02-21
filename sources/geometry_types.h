


#ifndef GEOMETRY_TYPES_H
#define GEOMETRY_TYPES_H


// ...
struct Matrix44
{

	union { float data[16]; float mat[4][4]; };
	
	// ...
	Matrix44 getTransposed() const {
		Matrix44 t;
		for( int i = 0; i < 4; i++ ) {
			for( int j = 0; j < 4; j++ ) {
				t.mat[i][j] = mat[j][i]; } }
		return t; };

	// ...
	Matrix44 getInvertedRT() const {
		Matrix44 t = identity();
		for( int col = 0; col < 3; col++ ) {
			for( int row = 0; row < 3; row++ ) {
				// Transpose rotation component (inversion).
				t.mat[row][col] = mat[col][row]; }
			// Inverse translation component.
			t.mat[3][col] = - mat[3][col]; }
		return t; };

	// ...
	static Matrix44 identity() {
		Matrix44 eye;
		for( int i = 0; i < 4; i++ ) {
			for( int j = 0; j < 4; j++ ) {
				eye.mat[i][j] = i == j ? 1.0f : 0.0f; } }
		return eye; };

};


// ...
struct Matrix33
{

	union { float data[9]; float mat[3][3]; };
	
	// ...
	static Matrix33 identity() {
		Matrix33 eye;
		for( int i = 0; i < 3; i++ ) {
			for( int j = 0; j < 3; j++ ) {
				eye.mat[i][j] = i == j ? 1.0f : 0.0f; } }
		return eye; };
	
	// ...
	Matrix33 getTransposed() const {
		Matrix33 t;
		for( int i = 0; i < 3; i++ ) { 
			for( int j = 0; j < 3; j++ ) {
				t.mat[i][j] = mat[j][i]; } }
		return t; };

};


// ...
struct Vector4
{
	float data[4];
};


// ...
struct Vector3
{

	float data[3];
	
	// ...
	static Vector3 zero() { Vector3 v = { 0.0f, 0.0f, 0.0f }; return v; };
	
	// ...
	Vector3 operator - () const { Vector3 v = { -data[0], -data[1], -data[2] }; return v; };

};


// ...
struct Transformation
{

	private :

		Matrix33 rotation;
		Vector3 translation;

	public :

		// ...
		Transformation() {
			rotation = Matrix33::identity();
			translation = Vector3::zero(); };

		// ...
		Transformation( const Matrix33& r, const Vector3& t ) {
			rotation = r;
			translation = t; };

		// ...
		Matrix33& r() { return rotation; };

		// ...
		Vector3& t() { return translation; };

		// ...
		const Matrix33& r() const { return rotation; };
		
		// ...
		const Vector3&  t() const { return translation; };
		
		// ...
		Matrix44 getMat44() const {
			Matrix44 res = Matrix44::identity();
			for( int col = 0; col < 3; col++ ) {
				for( int row = 0; row < 3; row++ ) {
					// Copy rotation component.
					res.mat[row][col] = rotation.mat[row][col]; }
				// Copy translation component.
				res.mat[3][col] = translation.data[col]; }
			return res; };

		Transformation getInverted() const { return Transformation( rotation.getTransposed(), -translation ); };

};


#endif // GEOMETRY_TYPES_H


