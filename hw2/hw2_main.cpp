//
//  main.cpp
//  OpenGL4Test
//
//  Created by Rafael Radkowski on 5/28/15.
//  Copyright (c) 2015 -. All rights reserved.
//

// stl include
#include <iostream>
#include <string>

// GLEW include
#include <GL/glew.h>

// GLM include files
#define GLM_FORCE_INLINE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


// glfw includes
#include <GLFW/glfw3.h>


// include local files
#include "controls.h"
#include "HCI557Common.h"
#include "CoordSystem.h"

// this line tells the compiler to use the namespace std.
// Each object, command without a namespace is assumed to be part of std. 
using namespace std;




static const string vs_string =
"#version 410 core                                                 \n"
"                                                                   \n"
"uniform mat4 projectionMatrix;                                    \n"
"uniform mat4 viewMatrix;                                           \n"
"uniform mat4 modelMatrix;                                          \n"
"in vec3 in_Position;                                               \n"
"                                                                   \n"
"in vec3 in_Color;                                                  \n"
"out vec3 pass_Color;                                               \n"
"                                                                  \n"
"void main(void)                                                   \n"
"{                                                                 \n"
"    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(in_Position, 1.0);  \n"
"    pass_Color = in_Color;                                         \n"
"}                                                                 \n";

// Fragment shader source code. This determines the colors in the fragment generated in the shader pipeline. In this case, it colors the inside of our triangle specified by our vertex shader.
static const string fs_string  =
"#version 410 core                                                 \n"
"                                                                  \n"
"in vec3 pass_Color;                                                 \n"
"out vec4 color;                                                    \n"
"void main(void)                                                   \n"
"{                                                                 \n"
"    color = vec4(pass_Color, 1.0);                               \n"
"}                                                                 \n";




/// Camera control matrices
glm::mat4 projectionMatrix; // Store the projection matrix
glm::mat4 viewMatrix; // Store the view matrix
glm::mat4 modelMatrix; // Store the model matrix




// The handle to the window object
GLFWwindow*         window;


// Define some of the global variables we're using for this sample
GLuint program;







///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// Fill this functions with your model code.

// USE THESE vertex array objects to define your objects
unsigned int vaoID[2];

unsigned int vboID[4];

int TriangleStripVerticeNum = 111;
int TriangleVerticeNum = 243;
/*!
 ADD YOUR CODE TO CREATE THE TRIANGLE STRIP MODEL TO THIS FUNCTION
 */
unsigned int createTriangleStripModel(void)
{

    // use the vertex array object vaoID[0] for this model representation
	
	float* vertices = new float[TriangleStripVerticeNum];  // Vertices for model
	float *colors = new float[TriangleStripVerticeNum]; // Colors for our vertices

								   // FRONT
	vertices[0] = 2; vertices[1] = 0; vertices[2] = 1; //point 1
	colors[0] = 1.0; colors[1] = 0.0; colors[2] = 0.0; 

	vertices[3] = 0; vertices[4] = 0; vertices[5] = 1;  //point2
	colors[3] = 1.0; colors[4] = 1.0; colors[5] = 1.0; 

	vertices[6] = 2; vertices[7] = 1; vertices[8] = 1; //point3
	colors[6] = 0.0; colors[7] = 1.0; colors[8] = 0.0; 

	vertices[9] = 0; vertices[10] = 1; vertices[11] = 1; //point4
	colors[9] = 0.0; colors[10] = 1.0; colors[11] = 0.0; 
	
	vertices[12] = 2; vertices[13] = 1; vertices[14] = 0; //point 5
	colors[12] = 1.0; colors[13] = 0.0; colors[14] = 0.0;

	vertices[15] = 0; vertices[16] = 1; vertices[17] = 0;  //point 6
	colors[15] = 1.0; colors[16] = 1.0; colors[17] = 1.0;
	
	vertices[18] = 2; vertices[19] = 0; vertices[20] = 0; //point 7
	colors[18] = 0.0; colors[19] = 1.0; colors[20] = 0.0;

	vertices[21] = 0; vertices[22] = 0; vertices[23] = 0; //point 8
	colors[1] = 0.0; colors[22] = 1.0; colors[23] = 0.0;

	vertices[24] = 2; vertices[25] = 0; vertices[26] = 1; //point 9
	colors[24] = 1.0; colors[25] = 0.0; colors[26] = 0.0;

	vertices[27] = 0; vertices[28] = 0; vertices[29] = 1;  //point 10
	colors[27] = 1.0; colors[28] = 1.0; colors[29] = 1.0;

	vertices[30] = 0; vertices[31] = 0; vertices[32] = 1; //point 11
	colors[30] = 0.0; colors[31] = 1.0; colors[32] = 0.0;

	vertices[33] = 0; vertices[34] = 0; vertices[35] = 0; //point 12
	colors[33] = 0.0; colors[34] = 1.0; colors[35] = 0.0;
    
	vertices[36] = 0; vertices[37] = 1; vertices[38] = 1; //point 13
	colors[36] = 1.0; colors[37] = 0.0; colors[38] = 0.0;

	vertices[39] = 0; vertices[40] = 1; vertices[41] = 0;  //point14 and left part is done!
	colors[39] = 1.0; colors[40] = 1.0; colors[41] = 1.0;




	vertices[42] = 2; vertices[43] = 1; vertices[44] = 0;  //point 15
	colors[42] = 1.0; colors[43] = 1.0; colors[44] = 1.0;

	vertices[45] = 2; vertices[46] = 1; vertices[47] = 1; //point 16
	colors[45] = 0.0; colors[46] = 1.0; colors[47] = 0.0;

	vertices[48] = 2; vertices[49] = 2; vertices[50] = 0; //point 17
	colors[48] = 0.0; colors[49] = 1.0; colors[50] = 0.0;

	vertices[51] = 2; vertices[52] = 2; vertices[53] = 1; //point 18
	colors[51] = 1.0; colors[52] = 0.0; colors[53] = 0.0;

	vertices[54] = 3; vertices[55] = 2; vertices[56] = 1;  //point 19
	colors[54] = 1.0; colors[55] = 1.0; colors[56] = 1.0;

	vertices[57] = 3; vertices[58] = 2; vertices[59] = 0; //point 20
	colors[57] = 0.0; colors[58] = 1.0; colors[59] = 0.0;

	vertices[60] = 2; vertices[61] = 2; vertices[62] = 0; //point 21
	colors[60] = 0.0; colors[61] = 1.0; colors[62] = 0.0;

	vertices[63] = 2; vertices[64] = 0; vertices[65] = 0; //point 22
	colors[63] = 1.0; colors[64] = 0.0; colors[65] = 0.0;

	vertices[66] = 3; vertices[67] = 0; vertices[68] = 0; //point 23
	colors[66] = 1.0; colors[67] = 0.0; colors[68] = 0.0;

	vertices[69] = 2; vertices[70] = 0; vertices[71] = 3;  //point 24
	colors[69] = 1.0; colors[70] = 1.0; colors[71] = 1.0;

	vertices[72] = 3; vertices[73] = 0; vertices[74] = 3; //point 25
	colors[72] = 0.0; colors[73] = 1.0; colors[74] = 0.0;

	vertices[75] = 2; vertices[76] = 1; vertices[77] = 3; //point 26
	colors[75] = 0.0; colors[76] = 1.0; colors[77] = 0.0;

	vertices[78] = 3; vertices[79] = 1; vertices[80] = 3; //point 27
	colors[78] = 1.0; colors[79] = 0.0; colors[80] = 0.0;

	vertices[81] = 2; vertices[82] = 2; vertices[83] = 1; //point 28
	colors[81] = 1.0; colors[82] = 0.0; colors[83] = 0.0;

	vertices[84] = 3; vertices[85] = 2; vertices[86] = 1; //point 29
	colors[84] = 1.0; colors[85] = 0.0; colors[86] = 0.0;

	vertices[87] = 3; vertices[88] = 2; vertices[89] = 0; //point 30 *****
	colors[87] = 1.0; colors[88] = 0.0; colors[89] = 0.0;

	vertices[90] = 3; vertices[91] = 1; vertices[92] = 3; //point 31
	colors[90] = 1.0; colors[91] = 0.0; colors[92] = 0.0;

	vertices[93] = 3; vertices[94] = 0; vertices[95] = 0;  //point 32
	colors[93] = 1.0; colors[94] = 1.0; colors[95] = 1.0;

	vertices[96] = 3; vertices[97] = 0; vertices[98] = 3; //point 33
	colors[96] = 0.0; colors[97] = 1.0; colors[98] = 0.0;

	vertices[99] = 2; vertices[100] = 0; vertices[101] = 1; //point 34
	colors[99] = 0.0; colors[100] = 1.0; colors[101] = 0.0;

	vertices[102] = 2; vertices[103] = 0; vertices[104] = 3; //point 35
	colors[102] = 1.0; colors[103] = 0.0; colors[104] = 0.0;

	vertices[105] = 2; vertices[106] = 2; vertices[107] = 1; //point 36
	colors[105] = 1.0; colors[106] = 0.0; colors[107] = 0.0;

	vertices[108] = 2; vertices[109] = 1; vertices[110] = 3; //point 37
	colors[108] = 1.0; colors[109] = 0.0; colors[110] = 0.0;

	//vertices[111] = 3; vertices[112] = 2; vertices[113] = 0; //point 30
	//colors[111] = 1.0; colors[112] = 0.0; colors[113] = 0.0;
	

	//TODO:
    //vaoID[0];

	glGenVertexArrays(2, &vaoID[0]); // Create our Vertex Array Object
	glBindVertexArray(vaoID[0]); // Bind our Vertex Array Object so we can use it

	glGenBuffers(4, vboID); // Generate our Vertex Buffer Object

							// vertices
	glBindBuffer(GL_ARRAY_BUFFER, vboID[0]); // Bind our Vertex Buffer Object
	glBufferData(GL_ARRAY_BUFFER, TriangleStripVerticeNum* sizeof(GLfloat), vertices, GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW

	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0); // Set up our vertex attributes pointer
	glEnableVertexAttribArray(0); // Disable our Vertex Array Object


								  //Color
	glBindBuffer(GL_ARRAY_BUFFER, vboID[1]); // Bind our second Vertex Buffer Object
	glBufferData(GL_ARRAY_BUFFER, TriangleStripVerticeNum* sizeof(GLfloat), colors, GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW

	glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, 0); // Set up our vertex attributes pointer
	glEnableVertexAttribArray(1); // Enable the second vertex attribute array

	glBindVertexArray(0); // Disable our Vertex Buffer Object


	delete[] vertices; // Delete our vertices from memory
	delete[] colors;
    
    return 1;
}

/*!
 ADD YOUR CODE TO CREATE A MODEL USING PRIMITIVES OF YOUR CHOISE TO THIS FUNCTION
 */
unsigned int createPolygonModel(void)
{
	/**/
    // use the vertex array object vaoID[1] for this model representation
	float* vertices = new float[TriangleVerticeNum];  // Vertices for our model
	float *colors = new float[TriangleVerticeNum]; // Colors for our vertices

								   //start drawing bottom side 
	vertices[0] = 0; vertices[1] = 0; vertices[2] = 0; // point 1
	colors[0] = 1.0; colors[1] = 0.0; colors[2] = 0.0; // 

	vertices[3] = 3; vertices[4] = 0; vertices[5] = 0; // point 2
	colors[3] = 1.0; colors[4] = 1.0; colors[5] = 1.0; // 

	vertices[6] = 0; vertices[7] = 0; vertices[8] = 1; // point 3
	colors[6] = 0.0; colors[7] = 1.0; colors[8] = 0.0; //

	vertices[9] = 3; vertices[10] = 0; vertices[11] = 0; // point 4
	colors[9] = 1.0; colors[10] = 0.0; colors[11] = 0.0; // 

	vertices[12] = 0; vertices[13] = 0; vertices[14] = 1; // point 5
	colors[12] = 1.0; colors[13] = 1.0; colors[14] = 1.0; // 

	vertices[15] = 3; vertices[16] = 0; vertices[17] = 1; // point 6
	colors[15] = 0.0; colors[16] = 1.0; colors[17] = 0.0; //

	vertices[18] = 2; vertices[19] = 0; vertices[20] = 1; // point 7
	colors[18] = 1.0; colors[19] = 0.0; colors[20] = 0.0; // 

	vertices[21] = 2; vertices[22] = 0; vertices[23] = 3; // point 8
	colors[21] = 1.0; colors[22] = 1.0; colors[23] = 1.0; // 

	vertices[24] = 3; vertices[25] = 0; vertices[26] = 1; // point 9
	colors[24] = 0.0; colors[25] = 1.0; colors[26] = 0.0; //

	vertices[27] = 3; vertices[28] = 0; vertices[29] = 3; // point 10
	colors[27] = 1.0; colors[28] = 0.0; colors[29] = 0.0; // 

	vertices[30] = 2; vertices[31] = 0; vertices[32] = 3; // point 11
	colors[30] = 1.0; colors[31] = 1.0; colors[32] = 1.0; // 

	vertices[33] = 3; vertices[34] = 0; vertices[35] = 1; // point 12
	colors[33] = 0.0; colors[34] = 1.0; colors[35] = 0.0; //
   
	//bottom done

	//back side start

	vertices[36] = 0; vertices[37] = 0; vertices[38] = 0; // point 13
	colors[36] = 1.0; colors[37] = 0.0; colors[38] = 0.0; // 

	vertices[39] = 3; vertices[40] = 0; vertices[41] = 0; // point 14
	colors[39] = 1.0; colors[40] = 1.0; colors[41] = 1.0; // 

	vertices[42] = 0; vertices[43] = 1; vertices[44] = 0; // point 15
	colors[42] = 0.0; colors[43] = 1.0; colors[44] = 0.0; //

	vertices[45] = 3; vertices[46] = 0; vertices[47] = 0; // point 16
	colors[45] = 1.0; colors[46] = 1.0; colors[47] = 1.0; // 

	vertices[48] = 0; vertices[49] = 1; vertices[50] = 0; // point 17
	colors[48] = 0.0; colors[49] = 1.0; colors[50] = 0.0; //

	vertices[51] = 3; vertices[52] = 1; vertices[53] = 0; // point 18
	colors[51] = 0.0; colors[52] = 1.0; colors[53] = 0.0; //

	vertices[54] = 2; vertices[55] = 1; vertices[56] = 0; // point 19
	colors[54] = 1.0; colors[55] = 0.0; colors[56] = 0.0; // 

	vertices[57] = 3; vertices[58] = 1; vertices[59] = 0; // point 20
	colors[57] = 0.0; colors[58] = 1.0; colors[59] = 0.0; //

	vertices[60] = 2; vertices[61] = 2; vertices[62] = 0; // point 21
	colors[60] = 1.0; colors[61] = 0.0; colors[62] = 0.0; // 

	vertices[63] = 3; vertices[64] = 1; vertices[65] = 0; // point 22
	colors[63] = 1.0; colors[64] = 0.0; colors[65] = 0.0; // 

	vertices[66] = 2; vertices[67] = 2; vertices[68] = 0; // point 23
	colors[66] = 1.0; colors[67] = 1.0; colors[68] = 1.0; // 

	vertices[69] = 3; vertices[70] = 2; vertices[71] = 0; // point 24
	colors[69] = 0.0; colors[70] = 1.0; colors[71] = 0.0; //


	// back side done

	// start right side   (vertices num need to be edited)

	vertices[72] = 3; vertices[73] = 2; vertices[74] = 0; // point 25
	colors[72] = 1.0; colors[73] = 1.0; colors[74] = 1.0; // 

	vertices[75] = 3; vertices[76] = 0; vertices[77] = 0; // point 26
	colors[75] = 0.0; colors[76] = 1.0; colors[77] = 0.0; //

	vertices[78] = 3; vertices[79] = 0; vertices[80] = 3; // point 27
	colors[78] = 0.0; colors[79] = 1.0; colors[80] = 0.0; //

	vertices[81] = 3; vertices[82] = 2; vertices[83] = 0; // point 28
	colors[81] = 1.0; colors[82] = 0.0; colors[83] = 0.0; // 

	vertices[84] = 3; vertices[85] = 2; vertices[86] = 1; // point 29
	colors[57] = 0.0; colors[85] = 1.0; colors[86] = 0.0; //

	vertices[87] = 3; vertices[88] = 0; vertices[89] = 3; // point 30
	colors[87] = 1.0; colors[88] = 0.0; colors[89] = 0.0; // 

	vertices[90] = 3; vertices[91] = 1; vertices[92] = 3; // point 31
	colors[90] = 1.0; colors[91] = 0.0; colors[92] = 0.0; // 

	vertices[93] = 3; vertices[94] = 2; vertices[95] = 1; // point 32
	colors[93] = 1.0; colors[94] = 1.0; colors[95] = 1.0; // 

	vertices[96] = 3; vertices[97] = 0; vertices[98] = 3; // point 33
	colors[96] = 0.0; colors[97] = 1.0; colors[98] = 0.0; //

	//right side down

	//vertices[96] = 3; vertices[97] = 0; vertices[98] = 3; // point 34
	//colors[96] = 0.0; colors[97] = 1.0; colors[98] = 0.0; //

	//start left square

	vertices[99] = 0; vertices[100] = 0; vertices[101] = 0; // point 34
	colors[99] = 1.0; colors[100] = 1.0; colors[101] = 1.0; // 

	vertices[102] = 0; vertices[103] = 0; vertices[104] = 1; // point 35
	colors[102] = 0.0; colors[103] = 1.0; colors[104] = 0.0; //

	vertices[105] = 0; vertices[106] = 1; vertices[107] = 0; // point 36
	colors[105] = 0.0; colors[106] = 1.0; colors[107] = 0.0; //

	vertices[108] = 0; vertices[109] = 1; vertices[110] = 0; // point 37
	colors[108] = 1.0; colors[109] = 0.0; colors[110] = 0.0; // 

	vertices[111] = 0; vertices[112] = 0; vertices[113] = 1; // point 38
	colors[111] = 0.0; colors[112] = 1.0; colors[113] = 0.0; //

	vertices[114] = 0; vertices[115] = 1; vertices[116] = 1; // point 39
	colors[114] = 1.0; colors[115] = 0.0; colors[116] = 0.0; // 

	//left square done
	//start front square

	vertices[117] = 2; vertices[118] = 0; vertices[119] = 3; // point 34
	colors[117] = 1.0; colors[118] = 1.0; colors[119] = 1.0; // 

	vertices[120] = 2; vertices[121] = 1; vertices[122] = 3; // point 35
	colors[120] = 0.0; colors[121] = 1.0; colors[122] = 0.0; //

	vertices[123] = 3; vertices[124] = 0; vertices[125] = 3; // point 36
	colors[123] = 0.0; colors[124] = 1.0; colors[125] = 0.0; //

	vertices[126] = 2; vertices[127] = 1; vertices[128] = 3; // point 37
	colors[126] = 1.0; colors[127] = 0.0; colors[128] = 0.0; // 

	vertices[129] = 3; vertices[130] = 0; vertices[131] = 3; // point 38
	colors[129] = 0.0; colors[130] = 1.0; colors[131] = 0.0; //

	vertices[132] = 3; vertices[133] = 1; vertices[134] = 3; // point 39
	colors[132] = 1.0; colors[133] = 0.0; colors[134] = 0.0; // 


	// right part top side

	vertices[135] = 2; vertices[136] = 2; vertices[137] = 0; // point 40
	colors[135] = 1.0; colors[136] = 1.0; colors[137] = 1.0; // 

	vertices[138] = 2; vertices[139] = 2; vertices[140] = 1; // point 41
	colors[138] = 0.0; colors[139] = 1.0; colors[140] = 0.0; //

	vertices[141] = 3; vertices[142] = 2; vertices[143] = 0; // point 42
	colors[141] = 0.0; colors[142] = 1.0; colors[143] = 0.0; //

	vertices[144] = 3; vertices[145] = 2; vertices[146] = 0; // point 43
	colors[144] = 1.0; colors[145] = 0.0; colors[146] = 0.0; // 

	vertices[147] = 2; vertices[148] = 2; vertices[149] = 1; // point 44
	colors[147] = 0.0; colors[148] = 1.0; colors[149] = 0.0; //

	vertices[150] = 3; vertices[151] = 2; vertices[152] = 1; // point 45
	colors[150] = 1.0; colors[151] = 0.0; colors[152] = 0.0; // 

	vertices[153] = 2; vertices[154] = 2; vertices[155] = 1; // point 46
	colors[153] = 1.0; colors[154] = 1.0; colors[155] = 1.0; // 

	vertices[156] = 2; vertices[157] = 1; vertices[158] = 3; // point 47
	colors[156] = 0.0; colors[157] = 1.0; colors[158] = 0.0; //

	vertices[159] = 3; vertices[160] = 2; vertices[161] = 1; // point 48
	colors[159] = 0.0; colors[160] = 1.0; colors[161] = 0.0; //

	vertices[162] = 2; vertices[163] = 1; vertices[164] = 3; // point 49
	colors[162] = 1.0; colors[163] = 0.0; colors[164] = 0.0; // 

	vertices[165] = 3; vertices[166] = 2; vertices[167] = 1; // point 50
	colors[165] = 0.0; colors[166] = 1.0; colors[167] = 0.0; //

	vertices[168] = 3; vertices[169] = 1; vertices[170] = 3; // point 51
	colors[168] = 1.0; colors[169] = 0.0; colors[170] = 0.0; // 

	// right part top side done
	//start left part top and front side

	vertices[171] = 0; vertices[172] = 1; vertices[173] = 0; // point 52
	colors[171] = 1.0; colors[172] = 1.0; colors[173] = 1.0; // 

	vertices[174] = 2; vertices[175] = 1; vertices[176] = 0; // point 53
	colors[174] = 0.0; colors[175] = 1.0; colors[176] = 0.0; //

	vertices[177] = 0; vertices[178] = 1; vertices[179] = 1; // point 54
	colors[177] = 0.0; colors[178] = 1.0; colors[179] = 0.0; //

	vertices[180] = 0; vertices[181] = 1; vertices[182] = 1; // point 5
	colors[180] = 1.0; colors[181] = 0.0; colors[182] = 0.0; // 

	vertices[183] = 2; vertices[184] = 1; vertices[185] = 0; // point 56
	colors[183] = 0.0; colors[184] = 1.0; colors[185] = 0.0; //

	vertices[186] = 2; vertices[187] = 1; vertices[188] = 1; // point 57
	colors[186] = 1.0; colors[187] = 0.0; colors[188] = 0.0; // 

	vertices[189] = 0; vertices[190] = 1; vertices[191] = 1; // point 58
	colors[189] = 1.0; colors[190] = 1.0; colors[191] = 1.0; // 

	vertices[192] = 2; vertices[193] = 1; vertices[194] = 1; // point 59
	colors[192] = 0.0; colors[193] = 1.0; colors[194] = 0.0; //

	vertices[195] = 0; vertices[196] = 0; vertices[197] = 1; // point 60
	colors[195] = 0.0; colors[196] = 1.0; colors[197] = 0.0; //

	vertices[198] = 2; vertices[199] = 0; vertices[200] = 1; // point 61
	colors[198] = 1.0; colors[199] = 0.0; colors[200] = 0.0; // 

	vertices[201] = 2; vertices[202] = 1; vertices[203] = 1; // point 62
	colors[201] = 0.0; colors[202] = 1.0; colors[203] = 0.0; //

	vertices[204] = 0; vertices[205] = 0; vertices[206] = 1; // point 63
	colors[204] = 1.0; colors[205] = 0.0; colors[206] = 0.0; // 

	//left part top and front side done
	//start middle surface

	vertices[207] = 2; vertices[208] = 1; vertices[209] = 0; // point 52
	colors[207] = 1.0; colors[208] = 1.0; colors[209] = 1.0; // 

	vertices[210] = 2; vertices[211] = 2; vertices[212] = 0; // point 53
	colors[210] = 0.0; colors[211] = 1.0; colors[212] = 0.0; //

	vertices[213] = 2; vertices[214] = 2; vertices[215] = 1; // point 54
	colors[213] = 0.0; colors[214] = 1.0; colors[215] = 0.0; //

	vertices[216] = 2; vertices[217] = 1; vertices[218] = 0; // point 5
	colors[216] = 1.0; colors[217] = 0.0; colors[218] = 0.0; // 

	vertices[219] = 2; vertices[220] = 2; vertices[221] = 1; // point 56
	colors[219] = 0.0; colors[220] = 1.0; colors[221] = 0.0; //

	vertices[222] = 2; vertices[223] = 1; vertices[224] = 3; // point 57
	colors[222] = 1.0; colors[223] = 0.0; colors[224] = 0.0; // 

	vertices[225] = 2; vertices[226] = 1; vertices[227] = 1; // point 58
	colors[225] = 1.0; colors[226] = 1.0; colors[227] = 1.0; // 

	vertices[228] = 2; vertices[229] = 1; vertices[230] = 3; // point 59
	colors[228] = 0.0; colors[229] = 1.0; colors[230] = 0.0; //

	vertices[231] = 2; vertices[232] = 0; vertices[233] = 3; // point 60
	colors[231] = 0.0; colors[232] = 1.0; colors[233] = 0.0; //

	vertices[234] = 2; vertices[235] = 1; vertices[236] = 1; // point 61
	colors[234] = 1.0; colors[235] = 0.0; colors[236] = 0.0; // 

	vertices[237] = 2; vertices[238] = 0; vertices[239] = 3; // point 62
	colors[237] = 0.0; colors[238] = 1.0; colors[239] = 0.0; //

	vertices[240] = 2; vertices[241] = 0; vertices[242] = 1; // point 63
	colors[240] = 1.0; colors[241] = 0.0; colors[242] = 0.0; // 



	//glGenVertexArrays(1, &vaoID[1]); // Create our Vertex Array Object
	glBindVertexArray(vaoID[1]); // Bind our Vertex Array Object so we can use it

	//glGenBuffers(2, vboID); // Generate our Vertex Buffer Object

							// vertices
	glBindBuffer(GL_ARRAY_BUFFER, vboID[2]); // Bind our Vertex Buffer Object
	glBufferData(GL_ARRAY_BUFFER, TriangleVerticeNum*sizeof(GLfloat), vertices, GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW

	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0); // Set up our vertex attributes pointer
	glEnableVertexAttribArray(0); // Disable our Vertex Array Object


								  //Color
	glBindBuffer(GL_ARRAY_BUFFER, vboID[3]); // Bind our second Vertex Buffer Object
	glBufferData(GL_ARRAY_BUFFER, TriangleVerticeNum*sizeof(GLfloat), colors, GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW

	glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, 0); // Set up our vertex attributes pointer
	glEnableVertexAttribArray(1); // Enable the second vertex attribute array

	glBindVertexArray(0); // Disable our Vertex Buffer Object


	delete[] vertices; // Delete our vertices from memory
	delete[] colors;

	//TODO:
	//vaoID[1];
    return 1;
}



/*!
 ADD YOUR CODE TO RENDER THE TRIANGLE STRIP MODEL TO THIS FUNCTION
 */
void renderTriangleStripModel(void)
{

    // Bind the buffer and switch it to an active buffer
    glBindVertexArray(vaoID[0]);
        
	// HERE: THIS CAUSES AN ERROR BECAUSE I DO NOT KNOW HOW MANY TRIANGLES / VERTICES YOU HAVE.
	// COMPLETE THE LINE
    // Draw the triangles
    glDrawArrays(GL_TRIANGLE_STRIP, 0 , TriangleStripVerticeNum/3);


	



	//glDrawArrays(GL_TRIANGLE_STRIP, 42, TriangleStripVerticeNum - TriangleStripVerticeLeftNum);
    // Unbind our Vertex Array Object
    glBindVertexArray(0);
}



/*!
 ADD YOUR CODE TO RENDER THE POLYGON STRIP MODEL TO THIS FUNCTION
 */
void renderPolygonModel(void)
{

    // Bind the buffer and switch it to an active buffer
    glBindVertexArray(vaoID[1]);
        

	// HERE: THIS CAUSES AN ERROR BECAUSE I DO NOT KNOW HOW MANY POLYGONS YOU HAVE.
	// COMPLETE THE LINE
    // Draw the triangles
    glDrawArrays(GL_TRIANGLES, 0 , TriangleVerticeNum/3);

    // Unbind our Vertex Array Object
    glBindVertexArray(0);
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/*!

 This function creates the two models
 */
void setupScene(void) {
    
    createTriangleStripModel();
 //   renderTriangleStripModel();
	createPolygonModel();
}




int main(int argc, const char * argv[])
{
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// Init glfw, create a window, and init glew
    
    // Init the GLFW Window
    window = initWindow();
    
    
    // Init the glew api
    initGlew();
    
	// Prepares some defaults
	CoordSystemRenderer* coordinate_system_renderer = new CoordSystemRenderer(10.0);

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// The Shader Program starts here
    
    // Vertex shader source code. This draws the vertices in our window. We have 3 vertices since we're drawing an triangle.
    // Each vertex is represented by a vector of size 4 (x, y, z, w) coordinates.
    static const string vertex_code = vs_string;
    static const char * vs_source = vertex_code.c_str();
    
    // Fragment shader source code. This determines the colors in the fragment generated in the shader pipeline. In this case, it colors the inside of our triangle specified by our vertex shader.
    static const string fragment_code = fs_string;
    static const char * fs_source = fragment_code.c_str();
    
    // This next section we'll generate the OpenGL program and attach the shaders to it so that we can render our triangle.
    program = glCreateProgram();
    
    // We create a shader with our fragment shader source code and compile it.
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fs_source, NULL);
    glCompileShader(fs);
    
    // We create a shader with our vertex shader source code and compile it.
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vs_source, NULL);
    glCompileShader(vs);
    
    // We'll attach our two compiled shaders to the OpenGL program.
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    
    glLinkProgram(program);
    
    // We'll specify that we want to use this program that we've attached the shaders to.
    glUseProgram(program);
    
    //// The Shader Program ends here
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    
    /// IGNORE THE NEXT PART OF THIS CODE
    /// IGNORE THE NEXT PART OF THIS CODE
    /// IGNORE THE NEXT PART OF THIS CODE
    // It controls the virtual camera
    
    // Set up our green background color
    static const GLfloat clear_color[] = { 0.6f, 0.7f, 1.0f, 1.0f };
    static const GLfloat clear_depth[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    
    
    projectionMatrix = glm::perspective(1.1f, (float)800 / (float)600, 0.1f, 100.f);
    modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)); // Create our model matrix which will halve the size of our model
    viewMatrix = glm::lookAt(glm::vec3(1.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    
    int projectionMatrixLocation = glGetUniformLocation(program, "projectionMatrix"); // Get the location of our projection matrix in the shader
    int viewMatrixLocation = glGetUniformLocation(program, "viewMatrix"); // Get the location of our view matrix in the shader
    int modelMatrixLocation = glGetUniformLocation(program, "modelMatrix"); // Get the location of our model matrix in the shader
    
    
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]); // Send our projection matrix to the shader
    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]); // Send our view matrix to the shader
    glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]); // Send our model matrix to the shader
    
    
	 //// The Shader Program ends here
    //// START TO READ AGAIN
    //// START TO READ AGAIN
    //// START TO READ AGAIN
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    


    glBindAttribLocation(program, 0, "in_Position");
    glBindAttribLocation(program, 1, "in_Color");
    

    
    // this creates the scene
    setupScene();
    
    int i=0;

    // Enable depth test
    // ignore this line, it allows us to keep the distance value after we proejct each object to a 2d canvas.
    glEnable(GL_DEPTH_TEST);
    
    // This is our render loop. As long as our window remains open (ESC is not pressed), we'll continue to render things.
    while(!glfwWindowShouldClose(window))
    {
        
        // Clear the entire buffer with our green color (sets the background to be green).
        glClearBufferfv(GL_COLOR , 0, clear_color);
        glClearBufferfv(GL_DEPTH , 0, clear_depth);
        
        // this draws the coordinate system
		coordinate_system_renderer->draw();
        
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //// This generate the object
        // Enable the shader program
        glUseProgram(program);
        
        // this changes the camera location
        glm::mat4 rotated_view = viewMatrix * GetRotationMatrix();
        glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &rotated_view[0][0]); // send the view matrix to our shader
        

        // This moves the model to the right
        modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]); // Send our model matrix to the shader
        

		// This line renders your triangle strip model
        renderTriangleStripModel();
        

        // This moves the model to the left
        modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-2.0f, -0.0f, 0.0f));
        glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]); // Send our model matrix to the shader
        
		// This line renders your Ppolygon model
        renderPolygonModel();
        
        
		// disable the shader program
        glUseProgram(0);


        //// This generate the object
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        
        
        // Swap the buffers so that what we drew will appear on the screen.
        glfwSwapBuffers(window);
        glfwPollEvents();
        
    }
    
	// delete the coordinate system object
	delete coordinate_system_renderer;

    // Program clean up when the window gets closed.
    glDeleteVertexArrays(2, vaoID);
    glDeleteProgram(program);
}

