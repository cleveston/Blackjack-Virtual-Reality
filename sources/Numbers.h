#ifndef NUMBERS_H
#define	NUMBERS_H

// 3D models Blackjack
#include <glew.h>
#include <windows.h>
#include <freeglut.h>
#include <glui.h>
#include <cstdlib>
#include <iostream>
#include <string.h>
#include <numeric>
#include <sstream>

#include "../../common/shader_program_manager.h"
#include "../../common/shader_program_info.h"
#include "../../common/shader_info.h"

#include "../../common/vmath.h"


//  Variables and Enums.

enum VAOIDs { VAON0, VAON1, VAON2, VAON3, VAON4, VAON5, VAON6, VAON7, VAON8, VAON9, NumVAOs };
enum VBOIDs { VBON0, VBON1, VBON2, VBON3, VBON4, VBON5, VBON6, VBON7, VBON8, VBON9, NumVBOs };
enum EBOIDs { EBON0, EBON1, EBON2, EBON3, EBON4, EBON5, EBON6, EBON7, EBON8, EBON9, NumEBOs };
enum AttribIDs { VertPos = 0, VertCol = 1 };

// NUMBER ZERO (TEN) - Array storing vertex positions.

static const GLfloat n0VertPos[44][4] = {

	// front - number 1

	{ -0.4F, 1.0F, 0.0F, 1.0F },	// Vertex 0.
	{ -0.2F, 1.0F, 0.0F, 1.0F },	// Vertex 1.
	{ -0.2F, 0.0F, 0.0F, 1.0F },	// Vertex 2.
	{ -0.2F, -1.0F, 0.0F, 1.0F },	// Vertex 3.
	{ -0.4F, -1.0F, 0.0F, 1.0F },	// Vertex 4.
	{ -0.4F, 0.0F, 0.0F, 1.0F },	// Vertex 5.
	{ -0.4F, 0.4F, 0.0F, 1.0F },	// Vertex 6.
	{ -0.6F, 0.4F, 0.0F, 1.0F },	// Vertex 7.

	// back - number 1

	{ -0.4F, 1.0F, -0.2F, 1.0F },	// Vertex 8.
	{ -0.2F, 1.0F, -0.2F, 1.0F },	// Vertex 9.
	{ -0.2F, 0.0F, -0.2F, 1.0F },	// Vertex 10.
	{ -0.2F, -1.0F, -0.2F, 1.0F },	// Vertex 11.
	{ -0.4F, -1.0F, -0.2F, 1.0F },	// Vertex 12.
	{ -0.4F, 0.0F, -0.2F, 1.0F },	// Vertex 13.
	{ -0.4F, 0.4F, -0.2F, 1.0F },	// Vertex 14.
	{ -0.6F, 0.4F, -0.2F, 1.0F },	// Vertex 15.

	// front - number 0

	{ 0.0F, 1.0F, 0.0F, 1.0F },		// Vertex 16.
	{ 0.4F, 1.0F, 0.0F, 1.0F },		// Vertex 17.
	{ 0.8F, 1.0F, 0.0F, 1.0F },		// Vertex 18.
	{ 0.8F, 0.0F, 0.0F, 1.0F },		// Vertex 19.
	{ 0.8F, -1.0F, 0.0F, 1.0F },	// Vertex 20.
	{ 0.4F, -1.0F, 0.0F, 1.0F },	// Vertex 21.
	{ 0.0F, -1.0F, 0.0F, 1.0F },	// Vertex 22.
	{ 0.0F, 0.0F, 0.0F, 1.0F },		// Vertex 23.
	{ 0.2F, 0.8F, 0.0F, 1.0F },		// Vertex 24.
	{ 0.6F, 0.8F, 0.0F, 1.0F },		// Vertex 25.
	{ 0.6F, 0.0F, 0.0F, 1.0F },		// Vertex 26.
	{ 0.6F, -0.8F, 0.0F, 1.0F },	// Vertex 27.
	{ 0.2F, -0.8F, 0.0F, 1.0F },	// Vertex 28.
	{ 0.2F, 0.0F, 0.0F, 1.0F },		// Vertex 29.

	// back - number 0

	{ 0.0F, 1.0F, -0.2F, 1.0F },	// Vertex 30.
	{ 0.4F, 1.0F, -0.2F, 1.0F },	// Vertex 31.
	{ 0.8F, 1.0F, -0.2F, 1.0F },	// Vertex 32.
	{ 0.8F, 0.0F, -0.2F, 1.0F },	// Vertex 33.
	{ 0.8F, -1.0F, -0.2F, 1.0F },	// Vertex 34.
	{ 0.4F, -1.0F, -0.2F, 1.0F },	// Vertex 35.
	{ 0.0F, -1.0F, -0.2F, 1.0F },	// Vertex 36.
	{ 0.0F, 0.0F, -0.2F, 1.0F },	// Vertex 37.
	{ 0.2F, 0.8F, -0.2F, 1.0F },	// Vertex 38.
	{ 0.6F, 0.8F, -0.2F, 1.0F },	// Vertex 39.
	{ 0.6F, 0.0F, -0.2F, 1.0F },	// Vertex 40.
	{ 0.6F, -0.8F, -0.2F, 1.0F },	// Vertex 41.
	{ 0.2F, -0.8F, -0.2F, 1.0F },	// Vertex 42.
	{ 0.2F, 0.0F, -0.2F, 1.0F },	// Vertex 43.

};

// NUMBER ZERO (TEN) - Array storing vertex colors.
static const GLfloat n0VertCol[44][4] = {
	{ 0.5F, 0.0F, 0.0F, 1.0F },		// Vertex 0.
	{ 0.6F, 0.0F, 0.0F, 1.0F },		// Vertex 1.
	{ 0.7F, 0.0F, 0.0F, 1.0F },		// Vertex 2.
	{ 0.8F, 0.0F, 0.0F, 1.0F },		// Vertex 3.
	{ 0.9F, 0.0F, 0.0F, 1.0F },		// Vertex 4.
	{ 0.5F, 0.0F, 0.0F, 1.0F },		// Vertex 5.
	{ 0.6F, 0.0F, 0.0F, 1.0F },		// Vertex 6.
	{ 0.7F, 0.0F, 0.0F, 1.0F },		// Vertex 7.
	{ 0.8F, 0.0F, 0.0F, 1.0F },		// Vertex 8.
	{ 0.9F, 0.0F, 0.0F, 1.0F },		// Vertex 9.
	{ 0.5F, 0.0F, 0.0F, 1.0F },		// Vertex 10.
	{ 0.6F, 0.0F, 0.0F, 1.0F },		// Vertex 11.
	{ 0.7F, 0.0F, 0.0F, 1.0F },		// Vertex 12.
	{ 0.8F, 0.0F, 0.0F, 1.0F },		// Vertex 13.
	{ 0.9F, 0.0F, 0.0F, 1.0F },		// Vertex 14.
	{ 0.5F, 0.0F, 0.0F, 1.0F },		// Vertex 15.
	{ 0.5F, 0.0F, 0.0F, 1.0F },		// Vertex 16.
	{ 0.6F, 0.0F, 0.0F, 1.0F },		// Vertex 17.
	{ 0.7F, 0.0F, 0.0F, 1.0F },		// Vertex 18.
	{ 0.8F, 0.0F, 0.0F, 1.0F },		// Vertex 19.
	{ 0.9F, 0.0F, 0.0F, 1.0F },		// Vertex 20.
	{ 0.5F, 0.0F, 0.0F, 1.0F },		// Vertex 21.
	{ 0.6F, 0.0F, 0.0F, 1.0F },		// Vertex 22.
	{ 0.7F, 0.0F, 0.0F, 1.0F },		// Vertex 23.
	{ 0.8F, 0.0F, 0.0F, 1.0F },		// Vertex 24.
	{ 0.9F, 0.0F, 0.0F, 1.0F },		// Vertex 25.
	{ 0.5F, 0.0F, 0.0F, 1.0F },		// Vertex 26.
	{ 0.6F, 0.0F, 0.0F, 1.0F },		// Vertex 27.
	{ 0.7F, 0.0F, 0.0F, 1.0F },		// Vertex 28.
	{ 0.8F, 0.0F, 0.0F, 1.0F },		// Vertex 29.
	{ 0.9F, 0.0F, 0.0F, 1.0F },		// Vertex 30.
	{ 0.5F, 0.0F, 0.0F, 1.0F },		// Vertex 31.
	{ 0.9F, 0.0F, 0.0F, 1.0F },		// Vertex 32.
	{ 0.5F, 0.0F, 0.0F, 1.0F },		// Vertex 33.
	{ 0.6F, 0.0F, 0.0F, 1.0F },		// Vertex 34.
	{ 0.7F, 0.0F, 0.0F, 1.0F },		// Vertex 35.
	{ 0.8F, 0.0F, 0.0F, 1.0F },		// Vertex 36.
	{ 0.9F, 0.0F, 0.0F, 1.0F },		// Vertex 37.
	{ 0.5F, 0.0F, 0.0F, 1.0F },		// Vertex 38.
	{ 0.6F, 0.0F, 0.0F, 1.0F },		// Vertex 39.
	{ 0.7F, 0.0F, 0.0F, 1.0F },		// Vertex 40.
	{ 0.8F, 0.0F, 0.0F, 1.0F },		// Vertex 41.
	{ 0.9F, 0.0F, 0.0F, 1.0F },		// Vertex 42.
	{ 0.5F, 0.0F, 0.0F, 1.0F },		// Vertex 43.

};

// NUMBER ZERO (TEN) - Array storing vertex indices for the triangles.
static const GLushort n0VertIdx[69][3] = {

	//number 1 triangles

	//front
	{ 7, 6, 0 }, { 0, 6, 1 }, { 1, 6, 2 }, { 5, 2, 6 }, { 4, 2, 5 },
	{ 2, 4, 3 },

	//sides
	{ 4, 3, 12 }, { 3, 12, 11 }, { 3, 2, 11 }, { 11, 2, 10 }, { 2, 10, 1 },
	{ 10, 1, 9 }, { 1, 0, 9 }, { 9, 0, 8 }, { 0, 7, 8 }, { 8, 7, 15 },
	{ 7, 6, 14 }, { 14, 7, 15 }, { 6, 5, 14 }, { 14, 5, 13 }, { 5, 4, 12 },
	{ 12, 5, 13 },

	//back 
	{ 8, 9, 12 }, { 11, 12, 9 },
	{ 14, 15, 8 },

	//number 0 triangles

	//front
	{ 16, 24, 17 }, { 24, 25, 17 }, { 25, 18, 17 },
	{ 25, 19, 18 }, { 26, 19, 25 }, { 27, 19, 26 },
	{ 27, 20, 19 }, { 21, 20, 27 }, { 21, 27, 28 },
	{ 22, 21, 28 }, { 22, 28, 23 }, { 23, 28, 29 },
	{ 23, 29, 24 }, { 23, 24, 16 },

	//sides -outer
	{ 16, 18, 30 }, { 18, 32, 30 },
	{ 18, 20, 34 }, { 34, 32, 18 },
	{ 20, 22, 36 }, { 36, 34, 20 },
	{ 22, 16, 30 }, { 36, 22, 30 },
	//sides -inner
	{ 42, 38, 24 }, { 28, 42, 24 },
	{ 24, 25, 39 }, { 39, 38, 24 },
	{ 25, 27, 41 }, { 41, 39, 25 },
	{ 41, 42, 28 }, { 28, 27, 41 },

	//back
	{ 30, 31, 38 }, { 31, 39, 38 },
	{ 39, 32, 33 }, { 40, 39, 33 },
	{ 41, 40, 33 }, { 34, 41, 33 },
	{ 34, 35, 41 }, { 35, 42, 41 },
	{ 35, 36, 42 }, { 42, 36, 37 },
	{ 42, 37, 43 }, { 43, 37, 38 },
	{ 38, 37, 30 }, { 31, 32, 39 }
};

// NUMBER ONE - Array storing vertex positions.
static const GLfloat n1VertPos[16][4] = {

	// front

	{ 0.0F, 1.0F, 0.0F, 1.0F },		// Vertex 0.
	{ 0.5F, 1.0F, 0.0F, 1.0F },		// Vertex 1.
	{ 0.5F, 0.0F, 0.0F, 1.0F },		// Vertex 2.
	{ 0.5F, -1.0F, 0.0F, 1.0F },	// Vertex 3.
	{ 0.0F, -1.0F, 0.0F, 1.0F },	// Vertex 4.
	{ 0.0F, 0.0F, 0.0F, 1.0F },		// Vertex 5.
	{ 0.0F, 0.5F, 0.0F, 1.0F },		// Vertex 6.
	{ -0.5F, 0.5F, 0.0F, 1.0F },	// Vertex 7.

	// back

	{ 0.0F, 1.0F, -0.2F, 1.0F },	// Vertex 8.
	{ 0.5F, 1.0F, -0.2F, 1.0F },	// Vertex 9.
	{ 0.5F, 0.0F, -0.2F, 1.0F },	// Vertex 10.
	{ 0.5F, -1.0F, -0.2F, 1.0F },	// Vertex 11.
	{ 0.0F, -1.0F, -0.2F, 1.0F },	// Vertex 12.
	{ 0.0F, 0.0F, -0.2F, 1.0F },	// Vertex 13.
	{ 0.0F, 0.5F, -0.2F, 1.0F },	// Vertex 14.
	{ -0.5F, 0.5F, -0.2F, 1.0F },	// Vertex 15.

};

// NUMBER ONE - Array storing vertex colors.
static const GLfloat n1VertCol[16][4] = {
	{ 0.5F, 0.0F, 0.0F, 1.0F },		// Vertex 0.
	{ 0.6F, 0.0F, 0.0F, 1.0F },		// Vertex 1.
	{ 0.7F, 0.0F, 0.0F, 1.0F },		// Vertex 2.
	{ 0.8F, 0.0F, 0.0F, 1.0F },		// Vertex 3.
	{ 0.9F, 0.0F, 0.0F, 1.0F },		// Vertex 4.
	{ 0.5F, 0.0F, 0.0F, 1.0F },		// Vertex 5.
	{ 0.6F, 0.0F, 0.0F, 1.0F },		// Vertex 6.
	{ 0.7F, 0.0F, 0.0F, 1.0F },		// Vertex 7.
	{ 0.8F, 0.0F, 0.0F, 1.0F },		// Vertex 8.
	{ 0.9F, 0.0F, 0.0F, 1.0F },		// Vertex 9.
	{ 0.5F, 0.0F, 0.0F, 1.0F },		// Vertex 10.
	{ 0.6F, 0.0F, 0.0F, 1.0F },		// Vertex 11.
	{ 0.7F, 0.0F, 0.0F, 1.0F },		// Vertex 12.
	{ 0.8F, 0.0F, 0.0F, 1.0F },		// Vertex 13.
	{ 0.9F, 0.0F, 0.0F, 1.0F },		// Vertex 14.
	{ 0.5F, 0.0F, 0.0F, 1.0F }		// Vertex 15.

};

// NUMBER ONE - Array storing vertex indices for the triangles.
static const GLushort n1VertIdx[25][3] = {
	//front
	{ 7, 6, 0 }, { 0, 6, 1 }, { 1, 6, 2 }, { 5, 2, 6 }, { 4, 2, 5 },
	{ 2, 4, 3 },

	//sides
	{ 4, 3, 12 }, { 3, 12, 11 }, { 3, 2, 11 }, { 11, 2, 10 }, { 2, 10, 1 },
	{ 10, 1, 9 }, { 1, 0, 9 }, { 9, 0, 8 }, { 0, 7, 8 }, { 8, 7, 15 },
	{ 7, 6, 14 }, { 14, 7, 15 }, { 6, 5, 14 }, { 14, 5, 13 }, { 5, 4, 12 },
	{ 12, 5, 13 },

	//back 
	{ 8, 9, 12 }, { 11, 12, 9 },
	{ 14, 15, 8 }

};

// NUMBER TWO - Array storing vertex positions.
static const GLfloat n2VertPos[24][4] = {

	//front

	{ -0.6F, 1.0F, 0.0F, 1.0F },		// Vertex 0.
	{ 0.6F, 1.0F, 0.0F, 1.0F },			// Vertex 1.
	{ 0.6F, 0.4F, 0.0F, 1.0F },			// Vertex 2.
	{ -0.2F, -0.4F, 0.0F, 1.0F },		// Vertex 3.
	{ -0.2F, -0.6F, 0.0F, 1.0F },		// Vertex 4.
	{ 0.6F, -0.6F, 0.0F, 1.0F },		// Vertex 5.
	{ 0.6F, -1.0F, 0.0F, 1.0F },		// Vertex 6.
	{ -0.6F, -1.0F, 0.0F, 1.0F },		// Vertex 7.
	{ -0.6F, -0.4F, 0.0F, 1.0F },		// Vertex 8.
	{ 0.2F, 0.4F, 0.0F, 1.0F },			// Vertex 9.
	{ 0.2F, 0.6F, 0.0F, 1.0F },			// Vertex 10.
	{ -0.6F, 0.6F, 0.0F, 1.0F },		// Vertex 11.

	// back

	{ -0.6F, 1.0F, -0.2F, 1.0F },		// Vertex 12.
	{ 0.6F, 1.0F, -0.2F, 1.0F },		// Vertex 13.
	{ 0.6F, 0.4F, -0.2F, 1.0F },		// Vertex 14.
	{ -0.2F, -0.4F, -0.2F, 1.0F },		// Vertex 15.
	{ -0.2F, -0.6F, -0.2F, 1.0F },		// Vertex 16.
	{ 0.6F, -0.6F, -0.2F, 1.0F },		// Vertex 17.
	{ 0.6F, -1.0F, -0.2F, 1.0F },		// Vertex 18.
	{ -0.6F, -1.0F, -0.2F, 1.0F },		// Vertex 19.
	{ -0.6F, -0.4F, -0.2F, 1.0F },		// Vertex 20.
	{ 0.2F, 0.4F, -0.2F, 1.0F },		// Vertex 21.
	{ 0.2F, 0.6F, -0.2F, 1.0F },		// Vertex 22.
	{ -0.6F, 0.6F, -0.2F, 1.0F }		// Vertex 23.

};

// NUMBER TWO - Array storing vertex colors.
static const GLfloat n2VertCol[24][4] = {
	{ 0.5F, 0.0F, 0.0F, 1.0F },		// Vertex 0.
	{ 0.6F, 0.0F, 0.0F, 1.0F },		// Vertex 1.
	{ 0.7F, 0.0F, 0.0F, 1.0F },		// Vertex 2.
	{ 0.8F, 0.0F, 0.0F, 1.0F },		// Vertex 3.
	{ 0.9F, 0.0F, 0.0F, 1.0F },		// Vertex 4.
	{ 0.5F, 0.0F, 0.0F, 1.0F },		// Vertex 5.
	{ 0.6F, 0.0F, 0.0F, 1.0F },		// Vertex 6.
	{ 0.7F, 0.0F, 0.0F, 1.0F },		// Vertex 7.
	{ 0.8F, 0.0F, 0.0F, 1.0F },		// Vertex 8.
	{ 0.9F, 0.0F, 0.0F, 1.0F },		// Vertex 9.
	{ 0.5F, 0.0F, 0.0F, 1.0F },		// Vertex 10.
	{ 0.6F, 0.0F, 0.0F, 1.0F },		// Vertex 11.
	{ 0.7F, 0.0F, 0.0F, 1.0F },		// Vertex 12.
	{ 0.8F, 0.0F, 0.0F, 1.0F },		// Vertex 13.
	{ 0.9F, 0.0F, 0.0F, 1.0F },		// Vertex 14.
	{ 0.5F, 0.0F, 0.0F, 1.0F },		// Vertex 15.
	{ 0.7F, 0.0F, 0.0F, 1.0F },		// Vertex 16.
	{ 0.8F, 0.0F, 0.0F, 1.0F },		// Vertex 17.
	{ 0.9F, 0.0F, 0.0F, 1.0F },		// Vertex 18.
	{ 0.5F, 0.0F, 0.0F, 1.0F },		// Vertex 19.
	{ 0.6F, 0.0F, 0.0F, 1.0F },		// Vertex 20.
	{ 0.7F, 0.0F, 0.0F, 1.0F },		// Vertex 21.
	{ 0.8F, 0.0F, 0.0F, 1.0F },		// Vertex 22.
	{ 0.9F, 0.0F, 0.0F, 1.0F }		// Vertex 23.
};

// NUMBER TWO - Array storing vertex indices for the triangles.
static const GLushort n2VertIdx[44][3] = {
	//front
	{ 11, 10, 0 }, { 0, 10, 1 }, { 10, 2, 1 }, { 9, 2, 10 }, { 9, 3, 2 },
	{ 8, 3, 9 }, { 8, 4, 3 }, { 8, 7, 4 }, { 7, 6, 4 }, { 4, 6, 5 },

	//back
	{ 22, 23, 12 }, { 13, 22, 12 }, { 14, 22, 13 }, { 14, 21, 22 }, { 15, 21, 14 },
	{ 15, 20, 21 }, { 16, 20, 15 }, { 16, 19, 20 }, { 18, 19, 16 }, { 18, 16, 17 },

	//sides
	{ 0, 1, 12 }, { 12, 1, 13 }, { 1, 2, 14 }, { 14, 1, 13 }, { 2, 3, 15 },
	{ 15, 2, 14 }, { 3, 4, 16 }, { 16, 3, 15 }, { 4, 5, 17 }, { 17, 16, 4 },
	{ 5, 6, 18 }, { 18, 5, 17 }, { 6, 7, 19 }, { 19, 18, 6 }, { 7, 8, 20 },
	{ 20, 19, 7 }, { 8, 9, 21 }, { 21, 20, 8 }, { 9, 10, 22 }, { 22, 21, 9 },
	{ 10, 11, 23 }, { 23, 22, 10 }, { 11, 0, 12 }, { 12, 23, 11 }

};

// NUMBER THREE - Array storing vertex positions.
static const GLfloat n3VertPos[28][4] = {
	//front

	{ -0.6F, 1.0F, 0.0F, 1.0F },		// Vertex 0.
	{ 0.6F, 1.0F, 0.0F, 1.0F },			// Vertex 1.
	{ 0.6F, -0.2F, 0.0F, 1.0F },		// Vertex 2.
	{ 0.6F, -0.6F, 0.0F, 1.0F },		// Vertex 3.
	{ 0.6F, -1.0F, 0.0F, 1.0F },		// Vertex 4.
	{ -0.6F, -1.0F, 0.0F, 1.0F },		// Vertex 5.
	{ -0.6F, -0.6F, 0.0F, 1.0F },		// Vertex 6.
	{ 0.2F, -0.6F, 0.0F, 1.0F },		// Vertex 7.
	{ 0.2F, -0.2F, 0.0F, 1.0F },		// Vertex 8.
	{ -0.4F, -0.2F, 0.0F, 1.0F },		// Vertex 9.
	{ -0.4F, 0.2F, 0.0F, 1.0F },		// Vertex 10.
	{ 0.2F, 0.2F, 0.0F, 1.0F },			// Vertex 11.
	{ 0.2F, 0.6F, 0.0F, 1.0F },			// Vertex 12.
	{ -0.6F, 0.6F, 0.0F, 1.0F },		// Vertex 13.

	// back

	{ -0.6F, 1.0F, -0.2F, 1.0F },		// Vertex 14.
	{ 0.6F, 1.0F, -0.2F, 1.0F },		// Vertex 15.
	{ 0.6F, -0.2F, -0.2F, 1.0F },		// Vertex 16.
	{ 0.6F, -0.6F, -0.2F, 1.0F },		// Vertex 17.
	{ 0.6F, -1.0F, -0.2F, 1.0F },		// Vertex 18.
	{ -0.6F, -1.0F, -0.2F, 1.0F },		// Vertex 19.
	{ -0.6F, -0.6F, -0.2F, 1.0F },		// Vertex 20.
	{ 0.2F, -0.6F, -0.2F, 1.0F },		// Vertex 21.
	{ 0.2F, -0.2F, -0.2F, 1.0F },		// Vertex 22.
	{ -0.4F, -0.2F, -0.2F, 1.0F },		// Vertex 23.
	{ -0.4F, 0.2F, -0.2F, 1.0F },		// Vertex 24.
	{ 0.2F, 0.2F, -0.2F, 1.0F },		// Vertex 25.
	{ 0.2F, 0.6F, -0.2F, 1.0F },		// Vertex 26.
	{ -0.6F, 0.6F, -0.2F, 1.0F }		// Vertex 27.

};

// NUMBER THREE - Array storing vertex colors.
static const GLfloat n3VertCol[28][4] = {
	{ 0.5F, 0.0F, 0.0F, 1.0F },		// Vertex 0.
	{ 0.6F, 0.0F, 0.0F, 1.0F },		// Vertex 1.
	{ 0.7F, 0.0F, 0.0F, 1.0F },		// Vertex 2.
	{ 0.8F, 0.0F, 0.0F, 1.0F },		// Vertex 3.
	{ 0.9F, 0.0F, 0.0F, 1.0F },		// Vertex 4.
	{ 0.5F, 0.0F, 0.0F, 1.0F },		// Vertex 5.
	{ 0.6F, 0.0F, 0.0F, 1.0F },		// Vertex 6.
	{ 0.7F, 0.0F, 0.0F, 1.0F },		// Vertex 7.
	{ 0.8F, 0.0F, 0.0F, 1.0F },		// Vertex 8.
	{ 0.9F, 0.0F, 0.0F, 1.0F },		// Vertex 9.
	{ 0.5F, 0.0F, 0.0F, 1.0F },		// Vertex 10.
	{ 0.6F, 0.0F, 0.0F, 1.0F },		// Vertex 11.
	{ 0.7F, 0.0F, 0.0F, 1.0F },		// Vertex 12.
	{ 0.8F, 0.0F, 0.0F, 1.0F },		// Vertex 13.
	{ 0.9F, 0.0F, 0.0F, 1.0F },		// Vertex 14.
	{ 0.5F, 0.0F, 0.0F, 1.0F },		// Vertex 15. 
	{ 0.9F, 0.0F, 0.0F, 1.0F },		// Vertex 16.
	{ 0.5F, 0.0F, 0.0F, 1.0F },		// Vertex 17.
	{ 0.6F, 0.0F, 0.0F, 1.0F },		// Vertex 18.
	{ 0.7F, 0.0F, 0.0F, 1.0F },		// Vertex 19.
	{ 0.8F, 0.0F, 0.0F, 1.0F },		// Vertex 20.
	{ 0.9F, 0.0F, 0.0F, 1.0F },		// Vertex 21.
	{ 0.5F, 0.0F, 0.0F, 1.0F },		// Vertex 22.
	{ 0.6F, 0.0F, 0.0F, 1.0F },		// Vertex 23.
	{ 0.7F, 0.0F, 0.0F, 1.0F },		// Vertex 24.
	{ 0.8F, 0.0F, 0.0F, 1.0F },		// Vertex 25.
	{ 0.9F, 0.0F, 0.0F, 1.0F },		// Vertex 26.
	{ 0.5F, 0.0F, 0.0F, 1.0F },		// Vertex 27.
};

// NUMBER THREE - Array storing vertex indices for the triangles.
static const GLushort n3VertIdx[44][3] = {
	//front
	{ 13, 12, 0 }, { 0, 12, 1 }, { 12, 11, 1 }, { 1, 11, 2 }, { 11, 9, 2 },
	{ 10, 9, 11 }, { 8, 7, 2 }, { 2, 7, 3 }, { 6, 4, 3 }, { 6, 5, 4 },

	//back
	{ 26, 27, 14 }, { 26, 14, 15 }, { 25, 26, 15 }, { 16, 25, 15 }, { 16, 23, 25 },
	{ 23, 24, 25 }, { 16, 21, 22 }, { 17, 21, 16 }, { 18, 20, 17 }, { 18, 19, 20 },

	//sides
	{ 0, 1, 15 }, { 15, 14, 0 }, { 1, 4, 18 }, { 18, 15, 1 }, { 5, 4, 18 },
	{ 18, 19, 5 }, { 5, 6, 20 }, { 20, 19, 5 }, { 6, 7, 21 }, { 21, 20, 6 },
	{ 7, 8, 22 }, { 22, 21, 7 }, { 8, 9, 23 }, { 23, 22, 8 }, { 9, 10, 24 },
	{ 24, 23, 9 }, { 10, 11, 25 }, { 25, 24, 10 }, { 11, 12, 26 }, { 26, 25, 11 },
	{ 12, 13, 27 }, { 27, 26, 12 }, { 13, 0, 14 }, { 14, 27, 13 }

};

// NUMBER FOUR - Array storing vertex positions.
static const GLfloat n4VertPos[22][4] = {

	//front

	{ -0.6F, 1.0F, 0.0F, 1.0F },	// Vertex 0.
	{ -0.2F, 1.0F, 0.0F, 1.0F },	// Vertex 1.
	{ -0.2F, 0.4F, 0.0F, 1.0F },	// Vertex 2.
	{ 0.2F, 0.4F, 0.0F, 1.0F },		// Vertex 3.
	{ 0.2F, 1.0F, 0.0F, 1.0F },		// Vertex 4.
	{ 0.6F, 1.0F, 0.0F, 1.0F },		// Vertex 5.
	{ 0.6F, -1.0F, 0.0F, 1.0F },	// Vertex 6.
	{ 0.2F, -1.0F, 0.0F, 1.0F },	// Vertex 7.
	{ 0.2F, 0.0F, 0.0F, 1.0F },		// Vertex 8.
	{ -0.2F, 0.0F, 0.0F, 1.0F },	// Vertex 9.
	{ -0.6F, 0.0F, 0.0F, 1.0F },	// Vertex 10.

	// back

	{ -0.6F, 1.0F, -0.2F, 1.0F },	// Vertex 11.
	{ -0.2F, 1.0F, -0.2F, 1.0F },	// Vertex 12.
	{ -0.2F, 0.4F, -0.2F, 1.0F },	// Vertex 13.
	{ 0.2F, 0.4F, -0.2F, 1.0F },	// Vertex 14.
	{ 0.2F, 1.0F, -0.2F, 1.0F },	// Vertex 15.
	{ 0.6F, 1.0F, -0.2F, 1.0F },	// Vertex 16.
	{ 0.6F, -1.0F, -0.2F, 1.0F },	// Vertex 17.
	{ 0.2F, -1.0F, -0.2F, 1.0F },	// Vertex 18.
	{ 0.2F, 0.0F, -0.2F, 1.0F },	// Vertex 19.
	{ -0.2F, 0.0F, -0.2F, 1.0F },	// Vertex 20.
	{ -0.6F, 0.0F, -0.2F, 1.0F },	// Vertex 21.

};

// NUMBER FOUR - Array storing vertex colors.
static const GLfloat n4VertCol[22][4] = {
	{ 0.5F, 0.0F, 0.0F, 1.0F },		// Vertex 0.
	{ 0.6F, 0.0F, 0.0F, 1.0F },		// Vertex 1.
	{ 0.7F, 0.0F, 0.0F, 1.0F },		// Vertex 2.
	{ 0.8F, 0.0F, 0.0F, 1.0F },		// Vertex 3.
	{ 0.9F, 0.0F, 0.0F, 1.0F },		// Vertex 4.
	{ 0.5F, 0.0F, 0.0F, 1.0F },		// Vertex 5.
	{ 0.6F, 0.0F, 0.0F, 1.0F },		// Vertex 6.
	{ 0.7F, 0.0F, 0.0F, 1.0F },		// Vertex 7.
	{ 0.8F, 0.0F, 0.0F, 1.0F },		// Vertex 8.
	{ 0.9F, 0.0F, 0.0F, 1.0F },		// Vertex 9.
	{ 0.5F, 0.0F, 0.0F, 1.0F },		// Vertex 10.
	{ 0.6F, 0.0F, 0.0F, 1.0F },		// Vertex 11.
	{ 0.7F, 0.0F, 0.0F, 1.0F },		// Vertex 12.
	{ 0.8F, 0.0F, 0.0F, 1.0F },		// Vertex 13.
	{ 0.9F, 0.0F, 0.0F, 1.0F },		// Vertex 14.
	{ 0.5F, 0.0F, 0.0F, 1.0F },		// Vertex 15.
	{ 0.9F, 0.0F, 0.0F, 1.0F },		// Vertex 16.
	{ 0.5F, 0.0F, 0.0F, 1.0F },		// Vertex 17.
	{ 0.6F, 0.0F, 0.0F, 1.0F },		// Vertex 18.
	{ 0.7F, 0.0F, 0.0F, 1.0F },		// Vertex 19.
	{ 0.8F, 0.0F, 0.0F, 1.0F },		// Vertex 20.
	{ 0.9F, 0.0F, 0.0F, 1.0F }		// Vertex 21.

};

// NUMBER FOUR - Array storing vertex indices for the triangles.
static const GLushort n4VertIdx[34][3] = {
	//front
	{ 10, 1, 0 }, { 10, 9, 1 }, { 9, 3, 2 }, { 9, 8, 3 }, { 7, 5, 4 },
	{ 7, 6, 5 },

	//back
	{ 21, 11, 12 }, { 20, 21, 12 }, { 20, 13, 14 }, { 19, 20, 14 }, { 18, 15, 16 },
	{ 18, 16, 17 },

	//sides
	{ 0, 1, 12 }, { 12, 11, 0 }, { 1, 2, 13 }, { 13, 12, 1 }, { 2, 3, 14 },
	{ 14, 13, 2 }, { 3, 4, 15 }, { 15, 14, 3 }, { 4, 5, 16 }, { 16, 15, 4 },
	{ 5, 6, 17 }, { 17, 16, 5 }, { 6, 7, 18 }, { 18, 17, 6 }, { 7, 8, 19 },
	{ 19, 18, 7 }, { 8, 9, 20 }, { 20, 19, 8 }, { 9, 10, 21 }, { 21, 20, 9 },
	{ 10, 0, 11 }, { 11, 21, 10 }

};

// NUMBER FIVE - Array storing vertex positions.
static const GLfloat n5VertPos[32][4] = {

	//front

	{ -0.6F, 1.0F, 0.0F, 1.0F },	// Vertex 0.
	{ 0.6F, 1.0F, 0.0F, 1.0F },		// Vertex 1.
	{ 0.6F, 0.6F, 0.0F, 1.0F },		// Vertex 2.
	{ -0.2F, 0.6F, 0.0F, 1.0F },	// Vertex 3.
	{ -0.2F, 0.2F, 0.0F, 1.0F },	// Vertex 4.
	{ 0.6F, 0.2F, 0.0F, 1.0F },		// Vertex 5.
	{ 0.6F, -0.2F, 0.0F, 1.0F },	// Vertex 6.
	{ 0.6F, -0.6F, 0.0F, 1.0F },	// Vertex 7.
	{ 0.6F, -1.0F, 0.0F, 1.0F },	// Vertex 8.
	{ -0.6F, -1.0F, 0.0F, 1.0F },	// Vertex 9.
	{ -0.6F, -0.6F, 0.0F, 1.0F },	// Vertex 10.
	{ 0.2F, -0.6F, 0.0F, 1.0F },	// Vertex 11.
	{ 0.2F, -0.2F, 0.0F, 1.0F },	// Vertex 12.
	{ -0.6F, -0.2F, 0.0F, 1.0F },	// Vertex 13.
	{ -0.6F, 0.2F, 0.0F, 1.0F },	// Vertex 14.
	{ -0.6F, 0.6F, 0.0F, 1.0F },	// Vertex 15.

	// back

	{ -0.6F, 1.0F, -0.2F, 1.0F },	// Vertex 16.
	{ 0.6F, 1.0F, -0.2F, 1.0F },	// Vertex 17.
	{ 0.6F, 0.6F, -0.2F, 1.0F },	// Vertex 18.
	{ -0.2F, 0.6F, -0.2F, 1.0F },	// Vertex 19.
	{ -0.2F, 0.2F, -0.2F, 1.0F },	// Vertex 20.
	{ 0.6F, 0.2F, -0.2F, 1.0F },	// Vertex 21.
	{ 0.6F, -0.2F, -0.2F, 1.0F },	// Vertex 22.
	{ 0.6F, -0.6F, -0.2F, 1.0F },	// Vertex 23.
	{ 0.6F, -1.0F, -0.2F, 1.0F },	// Vertex 24.
	{ -0.6F, -1.0F, -0.2F, 1.0F },	// Vertex 25.
	{ -0.6F, -0.6F, -0.2F, 1.0F },	// Vertex 26.
	{ 0.2F, -0.6F, -0.2F, 1.0F },	// Vertex 27.
	{ 0.2F, -0.2F, -0.2F, 1.0F },	// Vertex 28.
	{ -0.6F, -0.2F, -0.2F, 1.0F },	// Vertex 29.
	{ -0.6F, 0.2F, -0.2F, 1.0F },	// Vertex 30.
	{ -0.6F, 0.6F, -0.2F, 1.0F }	// Vertex 31.

};

// NUMBER FIVE - Array storing vertex colors.
static const GLfloat n5VertCol[32][4] = {
	{ 0.5F, 0.0F, 0.0F, 1.0F },		// Vertex 0.
	{ 0.6F, 0.0F, 0.0F, 1.0F },		// Vertex 1.
	{ 0.7F, 0.0F, 0.0F, 1.0F },		// Vertex 2.
	{ 0.8F, 0.0F, 0.0F, 1.0F },		// Vertex 3.
	{ 0.8F, 0.0F, 0.0F, 1.0F },		// Vertex 4.
	{ 0.5F, 0.0F, 0.0F, 1.0F },		// Vertex 5.
	{ 0.6F, 0.0F, 0.0F, 1.0F },		// Vertex 6.
	{ 0.7F, 0.0F, 0.0F, 1.0F },		// Vertex 7.
	{ 0.8F, 0.0F, 0.0F, 1.0F },		// Vertex 8.
	{ 0.9F, 0.0F, 0.0F, 1.0F },		// Vertex 9.
	{ 0.5F, 0.0F, 0.0F, 1.0F },		// Vertex 10.
	{ 0.6F, 0.0F, 0.0F, 1.0F },		// Vertex 11.
	{ 0.8F, 0.0F, 0.0F, 1.0F },		// Vertex 12.
	{ 0.8F, 0.0F, 0.0F, 1.0F },		// Vertex 13.
	{ 0.8F, 0.0F, 0.0F, 1.0F },		// Vertex 14.
	{ 0.8F, 0.0F, 0.0F, 1.0F },		// Vertex 15.
	{ 0.5F, 0.0F, 0.0F, 1.0F },		// Vertex 16.
	{ 0.6F, 0.0F, 0.0F, 1.0F },		// Vertex 17.
	{ 0.7F, 0.0F, 0.0F, 1.0F },		// Vertex 18.
	{ 0.8F, 0.0F, 0.0F, 1.0F },		// Vertex 19.
	{ 0.9F, 0.0F, 0.0F, 1.0F },		// Vertex 20.
	{ 0.5F, 0.0F, 0.0F, 1.0F },		// Vertex 21.
	{ 0.6F, 0.0F, 0.0F, 1.0F },		// Vertex 22.
	{ 0.7F, 0.0F, 0.0F, 1.0F },		// Vertex 23.
	{ 0.8F, 0.0F, 0.0F, 1.0F },		// Vertex 24.
	{ 0.9F, 0.0F, 0.0F, 1.0F },		// Vertex 25.
	{ 0.5F, 0.0F, 0.0F, 1.0F },		// Vertex 26.
	{ 0.6F, 0.0F, 0.0F, 1.0F },		// Vertex 27.
	{ 0.7F, 0.0F, 0.0F, 1.0F },		// Vertex 28.
	{ 0.8F, 0.0F, 0.0F, 1.0F },		// Vertex 29.
	{ 0.9F, 0.0F, 0.0F, 1.0F },		// Vertex 30.
	{ 0.5F, 0.0F, 0.0F, 1.0F }		// Vertex 31. 

};

// NUMBER FIVE - Array storing vertex indices for the triangles.
static const GLushort n5VertIdx[44][3] = {
	//front
	{ 0, 15, 1 }, { 15, 2, 1 }, { 15, 14, 3 }, { 14, 4, 3 }, { 14, 6, 5 },
	{ 14, 13, 6 }, { 12, 11, 6 }, { 11, 7, 6 }, { 10, 8, 7 }, { 10, 9, 8 },

	//back
	{ 31, 16, 17 }, { 17, 18, 31 }, { 19, 30, 31 }, { 20, 30, 19 }, { 21, 22, 30 },
	{ 22, 29, 30 }, { 22, 27, 28 }, { 23, 27, 22 }, { 23, 24, 26 }, { 24, 25, 26 },

	//sides
	{ 0, 1, 17 }, { 17, 16, 0 }, { 1, 2, 18 }, { 18, 17, 1 }, { 2, 3, 19 },
	{ 19, 18, 2 }, { 3, 4, 20 }, { 20, 19, 3 }, { 4, 5, 21 }, { 21, 20, 4 },
	{ 5, 8, 24 }, { 24, 21, 5 }, { 8, 9, 25 }, { 25, 24, 8 }, { 9, 10, 26 },
	{ 26, 25, 9 }, { 10, 11, 27 }, { 27, 26, 10 }, { 11, 12, 28 }, { 28, 27, 11 },
	{ 12, 13, 29 }, { 29, 28, 12 }, { 13, 0, 16 }, { 16, 29, 13 }

};

// NUMBER SIX - Array storing vertex positions.
static const GLfloat n6VertPos[36][4] = {
	//front - number 5 copy

	{ -0.6F, 1.0F, 0.0F, 1.0F },	// Vertex 0.
	{ 0.6F, 1.0F, 0.0F, 1.0F },		// Vertex 1.
	{ 0.6F, 0.6F, 0.0F, 1.0F },		// Vertex 2.
	{ -0.2F, 0.6F, 0.0F, 1.0F },	// Vertex 3.
	{ -0.2F, 0.2F, 0.0F, 1.0F },	// Vertex 4.
	{ 0.6F, 0.2F, 0.0F, 1.0F },		// Vertex 5.
	{ 0.6F, -0.2F, 0.0F, 1.0F },	// Vertex 6.
	{ 0.6F, -0.6F, 0.0F, 1.0F },	// Vertex 7.
	{ 0.6F, -1.0F, 0.0F, 1.0F },	// Vertex 8.
	{ -0.6F, -1.0F, 0.0F, 1.0F },	// Vertex 9.
	{ -0.6F, -0.6F, 0.0F, 1.0F },	// Vertex 10.
	{ 0.2F, -0.6F, 0.0F, 1.0F },	// Vertex 11.
	{ 0.2F, -0.2F, 0.0F, 1.0F },	// Vertex 12.
	{ -0.6F, -0.2F, 0.0F, 1.0F },	// Vertex 13.
	{ -0.6F, 0.2F, 0.0F, 1.0F },	// Vertex 14.
	{ -0.6F, 0.6F, 0.0F, 1.0F },	// Vertex 15.

	// back - number 5 copy

	{ -0.6F, 1.0F, -0.2F, 1.0F },	// Vertex 16.
	{ 0.6F, 1.0F, -0.2F, 1.0F },	// Vertex 17.
	{ 0.6F, 0.6F, -0.2F, 1.0F },	// Vertex 18.
	{ -0.2F, 0.6F, -0.2F, 1.0F },	// Vertex 19.
	{ -0.2F, 0.2F, -0.2F, 1.0F },	// Vertex 20.
	{ 0.6F, 0.2F, -0.2F, 1.0F },	// Vertex 21.
	{ 0.6F, -0.2F, -0.2F, 1.0F },	// Vertex 22.
	{ 0.6F, -0.6F, -0.2F, 1.0F },	// Vertex 23.
	{ 0.6F, -1.0F, -0.2F, 1.0F },	// Vertex 24.
	{ -0.6F, -1.0F, -0.2F, 1.0F },	// Vertex 25.
	{ -0.6F, -0.6F, -0.2F, 1.0F },	// Vertex 26.
	{ 0.2F, -0.6F, -0.2F, 1.0F },	// Vertex 27.
	{ 0.2F, -0.2F, -0.2F, 1.0F },	// Vertex 28.
	{ -0.6F, -0.2F, -0.2F, 1.0F },	// Vertex 29.
	{ -0.6F, 0.2F, -0.2F, 1.0F },	// Vertex 30.
	{ -0.6F, 0.6F, -0.2F, 1.0F },	// Vertex 31.

	//front - number 6 complementary

	{ -0.2F, -0.6F, 0.0F, 1.0F },	// Vertex 32.
	{ -0.2F, -0.2F, 0.0F, 1.0F },	// Vertex 33.

	//back - number 6 complementary

	{ -0.2F, -0.6F, -0.2F, 1.0F },	// Vertex 34.
	{ -0.2F, -0.2F, -0.2F, 1.0F },	// Vertex 35.

};

// NUMBER SIX - Array storing vertex colors.
static const GLfloat n6VertCol[36][4] = {

	{ 0.5F, 0.0F, 0.0F, 1.0F },		// Vertex 0.
	{ 0.6F, 0.0F, 0.0F, 1.0F },		// Vertex 1.
	{ 0.7F, 0.0F, 0.0F, 1.0F },		// Vertex 2.
	{ 0.8F, 0.0F, 0.0F, 1.0F },		// Vertex 3.
	{ 0.9F, 0.0F, 0.0F, 1.0F },		// Vertex 4.
	{ 0.5F, 0.0F, 0.0F, 1.0F },		// Vertex 5.
	{ 0.6F, 0.0F, 0.0F, 1.0F },		// Vertex 6.
	{ 0.7F, 0.0F, 0.0F, 1.0F },		// Vertex 7.
	{ 0.8F, 0.0F, 0.0F, 1.0F },		// Vertex 8.
	{ 0.9F, 0.0F, 0.0F, 1.0F },		// Vertex 9.
	{ 0.5F, 0.0F, 0.0F, 1.0F },		// Vertex 10.
	{ 0.6F, 0.0F, 0.0F, 1.0F },		// Vertex 11.
	{ 0.7F, 0.0F, 0.0F, 1.0F },		// Vertex 12.
	{ 0.8F, 0.0F, 0.0F, 1.0F },		// Vertex 13.
	{ 0.9F, 0.0F, 0.0F, 1.0F },		// Vertex 14.
	{ 0.5F, 0.0F, 0.0F, 1.0F },		// Vertex 15.
	{ 0.5F, 0.0F, 0.0F, 1.0F },		// Vertex 16.
	{ 0.6F, 0.0F, 0.0F, 1.0F },		// Vertex 17.
	{ 0.7F, 0.0F, 0.0F, 1.0F },		// Vertex 18.
	{ 0.8F, 0.0F, 0.0F, 1.0F },		// Vertex 19.
	{ 0.9F, 0.0F, 0.0F, 1.0F },		// Vertex 20.
	{ 0.5F, 0.0F, 0.0F, 1.0F },		// Vertex 21.
	{ 0.6F, 0.0F, 0.0F, 1.0F },		// Vertex 22.
	{ 0.7F, 0.0F, 0.0F, 1.0F },		// Vertex 23.
	{ 0.8F, 0.0F, 0.0F, 1.0F },		// Vertex 24.
	{ 0.9F, 0.0F, 0.0F, 1.0F },		// Vertex 25.
	{ 0.5F, 0.0F, 0.0F, 1.0F },		// Vertex 26.
	{ 0.6F, 0.0F, 0.0F, 1.0F },		// Vertex 27.
	{ 0.7F, 0.0F, 0.0F, 1.0F },		// Vertex 28.
	{ 0.8F, 0.0F, 0.0F, 1.0F },		// Vertex 29.
	{ 0.9F, 0.0F, 0.0F, 1.0F },		// Vertex 30.
	{ 0.5F, 0.0F, 0.0F, 1.0F },		// Vertex 31. 
	{ 0.7F, 0.0F, 0.0F, 1.0F },		// Vertex 32.
	{ 0.8F, 0.0F, 0.0F, 1.0F },		// Vertex 33.
	{ 0.9F, 0.0F, 0.0F, 1.0F },		// Vertex 34.
	{ 0.5F, 0.0F, 0.0F, 1.0F }		// Vertex 35. 
};

// NUMBER SIX - Array storing vertex indices for the triangles.
static const GLushort n6VertIdx[52][3] = {
	//front - number 5 copy
	{ 0, 15, 1 }, { 15, 2, 1 }, { 15, 14, 3 }, { 14, 4, 3 }, { 14, 6, 5 },
	{ 14, 13, 6 }, { 12, 11, 6 }, { 11, 7, 6 }, { 10, 8, 7 }, { 10, 9, 8 },

	//back - number 5 copy
	{ 31, 16, 17 }, { 17, 18, 31 }, { 19, 30, 31 }, { 20, 30, 19 }, { 21, 22, 30 },
	{ 22, 29, 30 }, { 22, 27, 28 }, { 23, 27, 22 }, { 23, 24, 26 }, { 24, 25, 26 },

	//sides - number 5 copy
	{ 0, 1, 17 }, { 17, 16, 0 }, { 1, 2, 18 }, { 18, 17, 1 }, { 2, 3, 19 },
	{ 19, 18, 2 }, { 3, 4, 20 }, { 20, 19, 3 }, { 4, 5, 21 }, { 21, 20, 4 },
	{ 5, 8, 24 }, { 24, 21, 5 }, { 8, 9, 25 }, { 25, 24, 8 }, { 9, 10, 26 },
	{ 26, 25, 9 }, { 10, 11, 27 }, { 27, 26, 10 }, { 11, 12, 28 }, { 28, 27, 11 },
	{ 12, 13, 29 }, { 29, 28, 12 }, { 13, 0, 16 }, { 16, 29, 13 },

	//front - number 6 complementary
	{ 10, 33, 13 }, { 10, 32, 33 },

	//back - number 6 complementary
	{ 26, 29, 35 }, { 34, 26, 35 },

	//sides - number 6 complementary
	{ 10, 13, 29 }, { 29, 26, 10 }, { 32, 33, 35 }, { 35, 34, 32 }

};

// NUMBER SEVEN - Array storing vertex positions.
static const GLfloat n7VertPos[14][4] = {

	// front

	{ -0.6F, 1.0F, 0.0F, 1.0F },	// Vertex 0.
	{ 0.6F, 1.0F, 0.0F, 1.0F },		// Vertex 1.
	{ 0.6F, 0.6F, 0.0F, 1.0F },		// Vertex 2.
	{ -0.2F, -1.0F, 0.0F, 1.0F },	// Vertex 3.
	{ -0.6F, -1.0F, 0.0F, 1.0F },	// Vertex 4.
	{ 0.2F, 0.6F, 0.0F, 1.0F },		// Vertex 5.
	{ -0.6F, 0.6F, 0.0F, 1.0F },	// Vertex 6.

	// back

	{ -0.6F, 1.0F, -0.2F, 1.0F },	// Vertex 7.
	{ 0.6F, 1.0F, -0.2F, 1.0F },	// Vertex 8.
	{ 0.6F, 0.6F, -0.2F, 1.0F },	// Vertex 9.
	{ -0.2F, -1.0F, -0.2F, 1.0F },	// Vertex 10.
	{ -0.6F, -1.0F, -0.2F, 1.0F },	// Vertex 11.
	{ 0.2F, 0.6F, -0.2F, 1.0F },	// Vertex 12.
	{ -0.6F, 0.6F, -0.2F, 1.0F }	// Vertex 13.

};

// NUMBER SEVEN - Array storing vertex colors.
static const GLfloat n7VertCol[14][4] = {
	{ 0.5F, 0.0F, 0.0F, 1.0F },		// Vertex 0.
	{ 0.6F, 0.0F, 0.0F, 1.0F },		// Vertex 1.
	{ 0.7F, 0.0F, 0.0F, 1.0F },		// Vertex 2.
	{ 0.8F, 0.0F, 0.0F, 1.0F },		// Vertex 3.
	{ 0.9F, 0.0F, 0.0F, 1.0F },		// Vertex 4.
	{ 0.5F, 0.0F, 0.0F, 1.0F },		// Vertex 5.
	{ 0.6F, 0.0F, 0.0F, 1.0F },		// Vertex 6.
	{ 0.7F, 0.0F, 0.0F, 1.0F },		// Vertex 7.
	{ 0.8F, 0.0F, 0.0F, 1.0F },		// Vertex 8.
	{ 0.9F, 0.0F, 0.0F, 1.0F },		// Vertex 9.
	{ 0.5F, 0.0F, 0.0F, 1.0F },		// Vertex 10.
	{ 0.6F, 0.0F, 0.0F, 1.0F },		// Vertex 11.
	{ 0.7F, 0.0F, 0.0F, 1.0F },		// Vertex 12.
	{ 0.8F, 0.0F, 0.0F, 1.0F }		// Vertex 13.

};

// NUMBER SEVEN - Array storing vertex indices for the triangles.
static const GLushort n7VertIdx[22][3] = {
	//front
	{ 0, 6, 2 }, { 0, 2, 1 }, { 3, 2, 5 }, { 4, 3, 5 },

	//back
	{ 9, 13, 7 }, { 9, 7, 8 }, { 9, 10, 12 }, { 10, 11, 12 },

	//sides
	{ 0, 1, 8 }, { 8, 7, 0 }, { 1, 2, 9 }, { 9, 8, 1 }, { 2, 3, 10 },
	{ 10, 9, 2 }, { 3, 4, 11 }, { 11, 10, 3 }, { 4, 5, 12 }, { 12, 11, 4 },
	{ 5, 6, 13 }, { 13, 12, 5 }, { 6, 0, 7 }, { 7, 13, 6 }

};

// NUMBER EIGHT - Array storing vertex positions.
static const GLfloat n8VertPos[40][4] = {

	//front - number 5 copy

	{ -0.6F, 1.0F, 0.0F, 1.0F },	// Vertex 0.
	{ 0.6F, 1.0F, 0.0F, 1.0F },		// Vertex 1.
	{ 0.6F, 0.6F, 0.0F, 1.0F },		// Vertex 2.
	{ -0.2F, 0.6F, 0.0F, 1.0F },	// Vertex 3.
	{ -0.2F, 0.2F, 0.0F, 1.0F },	// Vertex 4.
	{ 0.6F, 0.2F, 0.0F, 1.0F },		// Vertex 5.
	{ 0.6F, -0.2F, 0.0F, 1.0F },	// Vertex 6.
	{ 0.6F, -0.6F, 0.0F, 1.0F },	// Vertex 7.
	{ 0.6F, -1.0F, 0.0F, 1.0F },	// Vertex 8.
	{ -0.6F, -1.0F, 0.0F, 1.0F },	// Vertex 9.
	{ -0.6F, -0.6F, 0.0F, 1.0F },	// Vertex 10.
	{ 0.2F, -0.6F, 0.0F, 1.0F },	// Vertex 11.
	{ 0.2F, -0.2F, 0.0F, 1.0F },	// Vertex 12.
	{ -0.6F, -0.2F, 0.0F, 1.0F },	// Vertex 13.
	{ -0.6F, 0.2F, 0.0F, 1.0F },	// Vertex 14.
	{ -0.6F, 0.6F, 0.0F, 1.0F },	// Vertex 15.

	// back - number 5 copy

	{ -0.6F, 1.0F, -0.2F, 1.0F },	// Vertex 16.
	{ 0.6F, 1.0F, -0.2F, 1.0F },	// Vertex 17.
	{ 0.6F, 0.6F, -0.2F, 1.0F },	// Vertex 18.
	{ -0.2F, 0.6F, -0.2F, 1.0F },	// Vertex 19.
	{ -0.2F, 0.2F, -0.2F, 1.0F },	// Vertex 20.
	{ 0.6F, 0.2F, -0.2F, 1.0F },	// Vertex 21.
	{ 0.6F, -0.2F, -0.2F, 1.0F },	// Vertex 22.
	{ 0.6F, -0.6F, -0.2F, 1.0F },	// Vertex 23.
	{ 0.6F, -1.0F, -0.2F, 1.0F },	// Vertex 24.
	{ -0.6F, -1.0F, -0.2F, 1.0F },	// Vertex 25.
	{ -0.6F, -0.6F, -0.2F, 1.0F },	// Vertex 26.
	{ 0.2F, -0.6F, -0.2F, 1.0F },	// Vertex 27.
	{ 0.2F, -0.2F, -0.2F, 1.0F },	// Vertex 28.
	{ -0.6F, -0.2F, -0.2F, 1.0F },	// Vertex 29.
	{ -0.6F, 0.2F, -0.2F, 1.0F },	// Vertex 30.
	{ -0.6F, 0.6F, -0.2F, 1.0F },	// Vertex 31.

	//front - number 6 complementary copy

	{ -0.2F, -0.6F, 0.0F, 1.0F },	// Vertex 32.
	{ -0.2F, -0.2F, 0.0F, 1.0F },	// Vertex 33.

	//back - number 6 complementary copy

	{ -0.2F, -0.6F, -0.2F, 1.0F },	// Vertex 34.
	{ -0.2F, -0.2F, -0.2F, 1.0F },	// Vertex 35.

	//front - number 8 complementary

	{ 0.2F, 0.2F, 0.0F, 1.0F },		// Vertex 36.
	{ 0.2F, 0.6F, 0.0F, 1.0F },		// Vertex 37.

	//back - number 8 complementary

	{ 0.2F, 0.2F, -0.2F, 1.0F },	// Vertex 38.
	{ 0.2F, 0.6F, -0.2F, 1.0F },	// Vertex 39.

};

// NUMBER EIGHT - Array storing vertex colors.
static const GLfloat n8VertCol[40][4] = {
	{ 0.5F, 0.0F, 0.0F, 1.0F },		// Vertex 0.
	{ 0.6F, 0.0F, 0.0F, 1.0F },		// Vertex 1.
	{ 0.7F, 0.0F, 0.0F, 1.0F },		// Vertex 2.
	{ 0.8F, 0.0F, 0.0F, 1.0F },		// Vertex 3.
	{ 0.9F, 0.0F, 0.0F, 1.0F },		// Vertex 4.
	{ 0.5F, 0.0F, 0.0F, 1.0F },		// Vertex 5.
	{ 0.6F, 0.0F, 0.0F, 1.0F },		// Vertex 6.
	{ 0.7F, 0.0F, 0.0F, 1.0F },		// Vertex 7.
	{ 0.8F, 0.0F, 0.0F, 1.0F },		// Vertex 8.
	{ 0.9F, 0.0F, 0.0F, 1.0F },		// Vertex 9.
	{ 0.5F, 0.0F, 0.0F, 1.0F },		// Vertex 10.
	{ 0.6F, 0.0F, 0.0F, 1.0F },		// Vertex 11.
	{ 0.7F, 0.0F, 0.0F, 1.0F },		// Vertex 12.
	{ 0.8F, 0.0F, 0.0F, 1.0F },		// Vertex 13.
	{ 0.9F, 0.0F, 0.0F, 1.0F },		// Vertex 14.
	{ 0.5F, 0.0F, 0.0F, 1.0F },		// Vertex 15.
	{ 0.6F, 0.0F, 0.0F, 1.0F },		// Vertex 16.
	{ 0.7F, 0.0F, 0.0F, 1.0F },		// Vertex 17.
	{ 0.8F, 0.0F, 0.0F, 1.0F },		// Vertex 18.
	{ 0.9F, 0.0F, 0.0F, 1.0F },		// Vertex 19.
	{ 0.5F, 0.0F, 0.0F, 1.0F },		// Vertex 20.
	{ 0.6F, 0.0F, 0.0F, 1.0F },		// Vertex 21.
	{ 0.7F, 0.0F, 0.0F, 1.0F },		// Vertex 22.
	{ 0.8F, 0.0F, 0.0F, 1.0F },		// Vertex 23.
	{ 0.9F, 0.0F, 0.0F, 1.0F },		// Vertex 24.
	{ 0.5F, 0.0F, 0.0F, 1.0F },		// Vertex 25.
	{ 0.6F, 0.0F, 0.0F, 1.0F },		// Vertex 26.
	{ 0.7F, 0.0F, 0.0F, 1.0F },		// Vertex 27.
	{ 0.8F, 0.0F, 0.0F, 1.0F },		// Vertex 28.
	{ 0.9F, 0.0F, 0.0F, 1.0F },		// Vertex 29.
	{ 0.5F, 0.0F, 0.0F, 1.0F },		// Vertex 30.
	{ 0.7F, 0.0F, 0.0F, 1.0F },		// Vertex 31.
	{ 0.8F, 0.0F, 0.0F, 1.0F },		// Vertex 32.
	{ 0.9F, 0.0F, 0.0F, 1.0F },		// Vertex 33.
	{ 0.5F, 0.0F, 0.0F, 1.0F },		// Vertex 34.
	{ 0.6F, 0.0F, 0.0F, 1.0F },		// Vertex 35.
	{ 0.7F, 0.0F, 0.0F, 1.0F },		// Vertex 36.
	{ 0.8F, 0.0F, 0.0F, 1.0F },		// Vertex 37.
	{ 0.9F, 0.0F, 0.0F, 1.0F },		// Vertex 38.
	{ 0.5F, 0.0F, 0.0F, 1.0F }		// Vertex 39.

};

// NUMBER EIGHT - Array storing vertex indices for the triangles.
static const GLushort n8VertIdx[60][3] = {
	//front - number 5 copy
	{ 0, 15, 1 }, { 15, 2, 1 }, { 15, 14, 3 }, { 14, 4, 3 }, { 14, 6, 5 },
	{ 14, 13, 6 }, { 12, 11, 6 }, { 11, 7, 6 }, { 10, 8, 7 }, { 10, 9, 8 },

	//back - number 5 copy
	{ 31, 16, 17 }, { 17, 18, 31 }, { 19, 30, 31 }, { 20, 30, 19 }, { 21, 22, 30 },
	{ 22, 29, 30 }, { 22, 27, 28 }, { 23, 27, 22 }, { 23, 24, 26 }, { 24, 25, 26 },

	//sides - number 5 copy
	{ 0, 1, 17 }, { 17, 16, 0 }, { 1, 2, 18 }, { 18, 17, 1 }, { 2, 3, 19 },
	{ 19, 18, 2 }, { 3, 4, 20 }, { 20, 19, 3 }, { 4, 5, 21 }, { 21, 20, 4 },
	{ 5, 8, 24 }, { 24, 21, 5 }, { 8, 9, 25 }, { 25, 24, 8 }, { 9, 10, 26 },
	{ 26, 25, 9 }, { 10, 11, 27 }, { 27, 26, 10 }, { 11, 12, 28 }, { 28, 27, 11 },
	{ 12, 13, 29 }, { 29, 28, 12 }, { 13, 0, 16 }, { 16, 29, 13 },

	//front - number 6 complementary copy
	{ 10, 33, 13 }, { 10, 32, 33 },

	//back - number 6 complementary copy
	{ 26, 29, 35 }, { 34, 26, 35 },

	//sides - number 6 complementary copy
	{ 10, 13, 29 }, { 29, 26, 10 }, { 32, 33, 35 }, { 35, 34, 32 },

	//front - number 8 complementary 
	{ 37, 36, 2 }, { 36, 5, 2 },

	//back - number 8 complementary
	{ 38, 39, 18 }, { 21, 38, 18 },

	//sides - number 8 complementary
	{ 2, 5, 21 }, { 21, 18, 2 }, { 36, 37, 39 }, { 39, 38, 36 }

};

// NUMBER NINE - Array storing vertex positions.
static const GLfloat n9VertPos[36][4] = {

	//front - number 5 copy

	{ -0.6F, 1.0F, 0.0F, 1.0F },	// Vertex 0.
	{ 0.6F, 1.0F, 0.0F, 1.0F },		// Vertex 1.
	{ 0.6F, 0.6F, 0.0F, 1.0F },		// Vertex 2.
	{ -0.2F, 0.6F, 0.0F, 1.0F },	// Vertex 3.
	{ -0.2F, 0.2F, 0.0F, 1.0F },	// Vertex 4.
	{ 0.6F, 0.2F, 0.0F, 1.0F },		// Vertex 5.
	{ 0.6F, -0.2F, 0.0F, 1.0F },	// Vertex 6.
	{ 0.6F, -0.6F, 0.0F, 1.0F },	// Vertex 7.
	{ 0.6F, -1.0F, 0.0F, 1.0F },	// Vertex 8.
	{ -0.6F, -1.0F, 0.0F, 1.0F },	// Vertex 9.
	{ -0.6F, -0.6F, 0.0F, 1.0F },	// Vertex 10.
	{ 0.2F, -0.6F, 0.0F, 1.0F },	// Vertex 11.
	{ 0.2F, -0.2F, 0.0F, 1.0F },	// Vertex 12.
	{ -0.6F, -0.2F, 0.0F, 1.0F },	// Vertex 13.
	{ -0.6F, 0.2F, 0.0F, 1.0F },	// Vertex 14.
	{ -0.6F, 0.6F, 0.0F, 1.0F },	// Vertex 15.

	// back - number 5 copy

	{ -0.6F, 1.0F, -0.2F, 1.0F },	// Vertex 16.
	{ 0.6F, 1.0F, -0.2F, 1.0F },	// Vertex 17.
	{ 0.6F, 0.6F, -0.2F, 1.0F },	// Vertex 18.
	{ -0.2F, 0.6F, -0.2F, 1.0F },	// Vertex 19.
	{ -0.2F, 0.2F, -0.2F, 1.0F },	// Vertex 20.
	{ 0.6F, 0.2F, -0.2F, 1.0F },	// Vertex 21.
	{ 0.6F, -0.2F, -0.2F, 1.0F },	// Vertex 22.
	{ 0.6F, -0.6F, -0.2F, 1.0F },	// Vertex 23.
	{ 0.6F, -1.0F, -0.2F, 1.0F },	// Vertex 24.
	{ -0.6F, -1.0F, -0.2F, 1.0F },	// Vertex 25.
	{ -0.6F, -0.6F, -0.2F, 1.0F },	// Vertex 26.
	{ 0.2F, -0.6F, -0.2F, 1.0F },	// Vertex 27.
	{ 0.2F, -0.2F, -0.2F, 1.0F },	// Vertex 28.
	{ -0.6F, -0.2F, -0.2F, 1.0F },	// Vertex 29.
	{ -0.6F, 0.2F, -0.2F, 1.0F },	// Vertex 30.
	{ -0.6F, 0.6F, -0.2F, 1.0F },	// Vertex 31.

	// front - number 9 complementary

	{ 0.2F, 0.2F, 0.0F, 1.0F },		// Vertex 32.
	{ 0.2F, 0.6F, 0.0F, 1.0F },		// Vertex 33.

	// back - number 9 complementary 

	{ 0.2F, 0.2F, -0.2F, 1.0F },	// Vertex 34.
	{ 0.2F, 0.6F, -0.2F, 1.0F }		// Vertex 35.

};

// NUMBER NINE - Array storing vertex colors.
static const GLfloat n9VertCol[36][4] = {
	{ 0.5F, 0.0F, 0.0F, 1.0F },		// Vertex 0.
	{ 0.6F, 0.0F, 0.0F, 1.0F },		// Vertex 1.
	{ 0.7F, 0.0F, 0.0F, 1.0F },		// Vertex 2.
	{ 0.8F, 0.0F, 0.0F, 1.0F },		// Vertex 3.
	{ 0.9F, 0.0F, 0.0F, 1.0F },		// Vertex 4.
	{ 0.5F, 0.0F, 0.0F, 1.0F },		// Vertex 5.
	{ 0.6F, 0.0F, 0.0F, 1.0F },		// Vertex 6.
	{ 0.7F, 0.0F, 0.0F, 1.0F },		// Vertex 7.
	{ 0.8F, 0.0F, 0.0F, 1.0F },		// Vertex 8.
	{ 0.9F, 0.0F, 0.0F, 1.0F },		// Vertex 9.
	{ 0.5F, 0.0F, 0.0F, 1.0F },		// Vertex 10.
	{ 0.6F, 0.0F, 0.0F, 1.0F },		// Vertex 11.
	{ 0.7F, 0.0F, 0.0F, 1.0F },		// Vertex 12.
	{ 0.8F, 0.0F, 0.0F, 1.0F },		// Vertex 13.
	{ 0.9F, 0.0F, 0.0F, 1.0F },		// Vertex 14.
	{ 0.5F, 0.0F, 0.0F, 1.0F },		// Vertex 15.
	{ 0.6F, 0.0F, 0.0F, 1.0F },		// Vertex 16.
	{ 0.7F, 0.0F, 0.0F, 1.0F },		// Vertex 17.
	{ 0.8F, 0.0F, 0.0F, 1.0F },		// Vertex 18.
	{ 0.9F, 0.0F, 0.0F, 1.0F },		// Vertex 19.
	{ 0.5F, 0.0F, 0.0F, 1.0F },		// Vertex 20.
	{ 0.6F, 0.0F, 0.0F, 1.0F },		// Vertex 21.
	{ 0.7F, 0.0F, 0.0F, 1.0F },		// Vertex 22.
	{ 0.8F, 0.0F, 0.0F, 1.0F },		// Vertex 23.
	{ 0.9F, 0.0F, 0.0F, 1.0F },		// Vertex 24.
	{ 0.5F, 0.0F, 0.0F, 1.0F },		// Vertex 25.
	{ 0.6F, 0.0F, 0.0F, 1.0F },		// Vertex 26.
	{ 0.7F, 0.0F, 0.0F, 1.0F },		// Vertex 27.
	{ 0.8F, 0.0F, 0.0F, 1.0F },		// Vertex 28.
	{ 0.9F, 0.0F, 0.0F, 1.0F },		// Vertex 29.
	{ 0.5F, 0.0F, 0.0F, 1.0F },		// Vertex 30.
	{ 0.6F, 0.0F, 0.0F, 1.0F },		// Vertex 31.
	{ 0.7F, 0.0F, 0.0F, 1.0F },		// Vertex 32.
	{ 0.8F, 0.0F, 0.0F, 1.0F },		// Vertex 33.
	{ 0.9F, 0.0F, 0.0F, 1.0F },		// Vertex 34.
	{ 0.5F, 0.0F, 0.0F, 1.0F }		// Vertex 35. 

};

// NUMBER NINE - Array storing vertex indices for the triangles.
static const GLushort n9VertIdx[52][3] = {
	//front - number 5 copy
	{ 0, 15, 1 }, { 15, 2, 1 }, { 15, 14, 3 }, { 14, 4, 3 }, { 14, 6, 5 },
	{ 14, 13, 6 }, { 12, 11, 6 }, { 11, 7, 6 }, { 10, 8, 7 }, { 10, 9, 8 },

	//back - number 5 copy
	{ 31, 16, 17 }, { 17, 18, 31 }, { 19, 30, 31 }, { 20, 30, 19 }, { 21, 22, 30 },
	{ 22, 29, 30 }, { 22, 27, 28 }, { 23, 27, 22 }, { 23, 24, 26 }, { 24, 25, 26 },

	//sides - number 5 copy
	{ 0, 1, 17 }, { 17, 16, 0 }, { 1, 2, 18 }, { 18, 17, 1 }, { 2, 3, 19 },
	{ 19, 18, 2 }, { 3, 4, 20 }, { 20, 19, 3 }, { 4, 5, 21 }, { 21, 20, 4 },
	{ 5, 8, 24 }, { 24, 21, 5 }, { 8, 9, 25 }, { 25, 24, 8 }, { 9, 10, 26 },
	{ 26, 25, 9 }, { 10, 11, 27 }, { 27, 26, 10 }, { 11, 12, 28 }, { 28, 27, 11 },
	{ 12, 13, 29 }, { 29, 28, 12 }, { 13, 0, 16 }, { 16, 29, 13 },

	//front - number 9 complementary
	{ 33, 32, 2 }, { 32, 5, 2 },

	//back - number 9 complementary
	{ 18, 34, 35 }, { 21, 34, 18 },

	//sides - number 9 complementary
	{ 32, 33, 35 }, { 35, 34, 32 }, { 2, 5, 21 }, { 21, 18, 2 }

};

GLfloat aspectRatio;
GLuint VAOs[NumVAOs];
GLuint VBOs[NumVBOs];
GLuint EBOs[NumEBOs];
GLint locMatrixModel;
GLint locMatrixProj;
ShaderInfo shaderVert;
ShaderInfo shaderFrag;
ShaderProgramInfo shaderProg;

#endif