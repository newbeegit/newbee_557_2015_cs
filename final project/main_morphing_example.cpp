//
//  main_spotlight.cpp
//  HCI 557 Spotlight example
//
//  Created by Rafael Radkowski on 5/28/15.
//  Copyright (c) 2015 -. All rights reserved.
//

// stl include
#include <iostream>
#include <string>
#
#include <ctime>
#include <map>
#include <cmath>
#include <algorithm>

// GLEW include
#include <GL/glew.h>

// GLM include files
#define GLM_FORCE_INLINE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>


// glfw includes
#include <GLFW/glfw3.h>


// include local files
#include "controls.h"
#include "HCI557Common.h"
#include "CoordSystem.h"
#include "Plane3D.h"
#include "Texture.h"
#include "GLObjectObj.h"
#include "Sphere3D.h"

using namespace std;
using namespace glm;

// The handle to the window object
GLFWwindow* window;

// Define some of the global variables we're using for this sample
GLuint program;

/* A trackball to move and rotate the camera view */
extern Trackball trackball;

GLSpotLightSource  light_source1;
GLDirectLightSource  light_source2;
GLMaterial ball_material;
GLAppearance* ball1;
GLSphere3D* sphere;
/////////////
//building water
/////////////

// this is a helper variable to allow us to change the texture blend model
extern int g_change_texture_blend;
int bump_map = 0;
GLAppearance* apperance_water;
bool jump = false;
int space_presstime = 0;
int ball_light = 1;
int view = 0;



// This is the callback we'll be registering with GLFW for keyboard handling.
// The only thing we're doing here is setting up the window to close when we press ESC
void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	else if (key == 77 && action == GLFW_PRESS) 
	{
		//cout <<  "key m pressed" << endl;
		glUseProgram(apperance_water->getProgram());
		bump_map = (bump_map + 1) % 2;

		int loc = glGetUniformLocation(apperance_water->getProgram(), "bump_mode");
		glUniform1i(loc, bump_map);
		glUseProgram(0);
	}
	else if (key == 32 && action == GLFW_PRESS) // key w
	{
		//cout <<  "key spacebar pressed" << endl;
		space_presstime = (space_presstime + 1) % 2;
		if (space_presstime == 1) {
			jump = true;
		}
		else {
			jump = false;
		}
	}
	else if (key == 49 && action == GLFW_PRESS) // 
	{
		//cout <<  "pressed 1" << endl;
		ball1 = new GLAppearance("../../data/shaders/multi_vertex_lights.vs", "../../data/shaders/multi_vertex_lights.fs");

		// The spotlight object
		//GLSpotLightSource  light_source1;
		light_source1._lightPos = glm::vec4(40.0, 15.0, 35.0, 1.0);
		light_source1._ambient_intensity = 0.02;
		light_source1._specular_intensity = 0.9;
		light_source1._diffuse_intensity = 0.9;
		light_source1._attenuation_coeff = 0.0;
		light_source1._cone_angle = 17.0; // in degree
		light_source1._cone_direction = glm::vec3(0.0, -13.0, -35.0); // this must be aligned with the object and light position.
		light_source1._inner_angle = 12.0;
		light_source1._outer_angle = 17.0;

		
		light_source2._lightPos = glm::vec4(-20.0, -10.0, 20.0, 0.0);
		light_source2._ambient_intensity = 0.005;//0.005
		light_source2._specular_intensity = 0.4;//0.4
		light_source2._diffuse_intensity = 0.8;//0.8
		light_source2._attenuation_coeff = 0.12;//0.12

		// add the spot light to this apperance object
		ball1->addLightSource(light_source1);
		ball1->addLightSource(light_source2);

		// Create a material object
	//	GLMaterial ball_material;
		ball_material._diffuse_material = glm::vec3(0.7, 0.2, 0.1); //   glm::vec3(0.93, 0.9, 0.11)
		ball_material._ambient_material = glm::vec3(0.7, 0.2, 0.1); //   glm::vec3(0.93, 0.9, 0.11)
		ball_material._specular_material = glm::vec3(1.0, 1.0, 1.0); //    glm::vec3(1.0, 1.0, 1.0)
		ball_material._shininess = 90.0;

		// Add the material to the apperance object
		ball1->setMaterial(ball_material);

		ball1->updateLightSources();

		ball1->finalize();

		// create the sphere geometry
		sphere = new GLSphere3D(0.0, 0.0, 125.0, 10.0, 450, 250);




		//	ball_material._diffuse_material = glm::vec3(0.93, 0.9, 0.11);
		//	ball_material._ambient_material = glm::vec3(0.93, 0.9, 0.11);
		//	ball1->updateMaterial();


		sphere->setApperance(*ball1);
		sphere->init();
		cout << "dwdw" << endl;

	}
	else if (key == 50 && action == GLFW_PRESS) // key w
	{
		//cout <<  "pressed 2" << endl;
		ball1 = new GLAppearance("../../data/shaders/multi_vertex_lights.vs", "../../data/shaders/multi_vertex_lights.fs");

		// The spotlight object
//		GLSpotLightSource  light_source1;
		light_source1._lightPos = glm::vec4(10.0, 20.0, 20.0, 1.0);
		light_source1._ambient_intensity = 0.005;
		light_source1._specular_intensity = 0.0;
		light_source1._diffuse_intensity = 99.9;
		light_source1._attenuation_coeff = 0.0;
		light_source1._cone_angle = 17.0; // in degree
		light_source1._cone_direction = glm::vec3(0.0, -1.0, -1.0); // this must be aligned with the object and light position.
		light_source1._inner_angle = 12.0;
		light_source1._outer_angle = 17.0;

//		GLDirectLightSource  light_source2;
		light_source2._lightPos = glm::vec4(5.0, 1.0, 10.0, 0.0);
		light_source2._ambient_intensity = 0.005;
		light_source2._specular_intensity = 0.4;
		light_source2._diffuse_intensity = 0.8;
		light_source2._attenuation_coeff = 0.12;

		// add the spot light to this apperance object
		ball1->addLightSource(light_source1);
		ball1->addLightSource(light_source2);

		// Create a material object
	//	GLMaterial ball_material;
		ball_material._diffuse_material = glm::vec3(0.117, 0.701, 0.101); //   glm::vec3(0.93, 0.9, 0.11)
		ball_material._ambient_material = glm::vec3(0.117, 0.701, 0.101); //   glm::vec3(0.93, 0.9, 0.11)
		ball_material._specular_material = glm::vec3(1.0, 1.0, 1.0); //    glm::vec3(1.0, 1.0, 1.0)
		ball_material._shininess = 90.0;

		// Add the material to the apperance object
		ball1->setMaterial(ball_material);

		ball1->updateLightSources();

		ball1->finalize();

		// create the sphere geometry
		sphere = new GLSphere3D(0.0, 0.0, 125.0, 10.0, 450, 250);




		//	ball_material._diffuse_material = glm::vec3(0.93, 0.9, 0.11);
		//	ball_material._ambient_material = glm::vec3(0.93, 0.9, 0.11);
		//	ball1->updateMaterial();


		sphere->setApperance(*ball1);
		sphere->init();

	}
	else if (key == 51 && action == GLFW_PRESS) 
	{
		GLAppearance* ball1 = new GLAppearance("../../data/shaders/multi_vertex_lights.vs", "../../data/shaders/multi_vertex_lights.fs");

		// The spotlight object
	//	GLSpotLightSource  light_source1;
		light_source1._lightPos = glm::vec4(40.0, 15.0, 35.0, 1.0);
		light_source1._ambient_intensity = 0.02;
		light_source1._specular_intensity = 0.9;
		light_source1._diffuse_intensity = 0.9;
		light_source1._attenuation_coeff = 0.0;
		light_source1._cone_angle = 17.0; // in degree
		light_source1._cone_direction = glm::vec3(0.0, -13.0, -35.0); // this must be aligned with the object and light position.
		light_source1._inner_angle = 12.0;
		light_source1._outer_angle = 17.0;

//		GLDirectLightSource  light_source2;
		light_source2._lightPos = glm::vec4(-20.0, -10.0, 20.0, 0.0);
		light_source2._ambient_intensity = 0.005;
		light_source2._specular_intensity = 0.4;
		light_source2._diffuse_intensity = 0.8;
		light_source2._attenuation_coeff = 0.12;

		// add the spot light to this apperance object
		ball1->addLightSource(light_source1);
		ball1->addLightSource(light_source2);

		// Create a material object
		
		ball_material._diffuse_material = glm::vec3(0.93, 0.9, 0.11); //   glm::vec3(0.93, 0.9, 0.11)
		ball_material._ambient_material = glm::vec3(0.93, 0.9, 0.11); //   glm::vec3(0.93, 0.9, 0.11)
		ball_material._specular_material = glm::vec3(1.0, 1.0, 1.0); //    glm::vec3(1.0, 1.0, 1.0)
		ball_material._shininess = 90.0;

		// Add the material to the apperance object
		ball1->setMaterial(ball_material);

		ball1->updateLightSources();

		ball1->finalize();

		sphere = new GLSphere3D(0.0, 0.0, 125.0, 10.0, 450, 250);




		//	ball_material._diffuse_material = glm::vec3(0.93, 0.9, 0.11);
		//	ball_material._ambient_material = glm::vec3(0.93, 0.9, 0.11);
		//	ball1->updateMaterial();


		sphere->setApperance(*ball1);
		sphere->init();
	}
	//(NumPad) 1
	else if (key == 73 && action == GLFW_PRESS) {
		view = 0;
	}
	//(NumPad) 2
	else if (key == 79 && action == GLFW_PRESS) {
		view = 1;
	}
	//(NumPad) 3
	else if (key == 80 && action == GLFW_PRESS) {
		view = 2;
	}
}

///////////////////////////////////




//////////////////////////////////////////////////////////////////////
// Morphing
//
// The morphing operation requires three steps
// 1. Load a normal model and the morphed model of the object you like to morph.
// 2. Calculate a difference vector (blend shaphe morphing). This happens in function init_morphing()
// 3. During the main loop - call a function that calculates the current animation time fraction and updates the
//      vertices.

GLObjectObj* loadedModel1 = NULL; // the basic / normal model
GLObjectObj* loadedModel2 = NULL; // the morphed model
GLObjectObj* TempModel = NULL;
GLfloat* vector_diff = 0;
GLfloat* vector_diff_2 = 0;
GLfloat* vector_result = 0;

/*!
 @brief returns the time fraction for a given time and animation duration
 @param time - the current animation time, application runtime, etc. in seconds
 @param duration - the duration of the animation in seconds
 @return the time fraction in an interval between 0 and 1.
 */
float getTimeFraction(const float time, const float duration)
{
    // we cast to an int. this results in the number of
    float interval = floor(time/duration);
    
    // return the current interval time
    float current_interval = time - interval*duration;
    
    // return the fraction / position in our current timeline
    float fraction = current_interval / duration;

    return fraction;
}




void init_morphing(void)
{
	// allocate memory for the difference vector.
	vector_diff = (GLfloat*)malloc(sizeof(GLfloat) * 3 * loadedModel2->size());

	int size = loadedModel2->size();
	// calculate the difference vector
	for (int i = 0; i<size; i++) {
		vector_diff[i * 3 + 0] = loadedModel2->getVertices()[i].x - loadedModel1->getVertices()[i].x;
		vector_diff[i * 3 + 1] = loadedModel2->getVertices()[i].y - loadedModel1->getVertices()[i].y;
		vector_diff[i * 3 + 2] = loadedModel2->getVertices()[i].z - loadedModel1->getVertices()[i].z;
	}

	vector_diff_2 = (GLfloat*)malloc(sizeof(GLfloat) * 3 * loadedModel1->size());

	// calculate the difference vector
	for (int i = 0; i < size; i++) {
		vector_diff_2[i * 3 + 0] = loadedModel2->getVertices()[i].x - loadedModel1->getVertices()[i].x;
		vector_diff_2[i * 3 + 1] = loadedModel2->getVertices()[i].y - loadedModel1->getVertices()[i].y;
		vector_diff_2[i * 3 + 2] = loadedModel2->getVertices()[i].z - loadedModel1->getVertices()[i].z;
	}
}


void my_morphing_callback(float duration)
{
	
	// get the current system time
	float time = glfwGetTime();

	// calcualte the time fraction
	float fraction = getTimeFraction(time, duration);

	// get the number of vertices.
	int size = loadedModel1->size();

	

		for (int i = 0; i < size; i++) {
			vector_diff[i * 3 + 0] = loadedModel2->getVertices()[i].x - loadedModel1->getVertices()[i].x;
			vector_diff[i * 3 + 1] = loadedModel2->getVertices()[i].y - loadedModel1->getVertices()[i].y;
			vector_diff[i * 3 + 2] = loadedModel2->getVertices()[i].z - loadedModel1->getVertices()[i].z;
		}

		for (int i = 0; i < size; i++) {
			vector_result[i * 3 + 0] = loadedModel1->getVertices()[i].x + fraction * vector_diff[i * 3 + 0];
			vector_result[i * 3 + 1] = loadedModel1->getVertices()[i].y + fraction * vector_diff[i * 3 + 1];
			vector_result[i * 3 + 2] = loadedModel1->getVertices()[i].z + fraction * vector_diff[i * 3 + 2];
		}


		//---------------------------
		// Draw the output
		loadedModel1->updateVertices(vector_result);
		loadedModel1->draw();
}

void my_morphing_callback_2(float duration)
{
	// get the current system time
	float time = glfwGetTime();

	// calcualte the time fraction
	float fraction = getTimeFraction(time, duration);

	// get the number of vertices.
	int size = loadedModel1->size();

	// init the vector the first time we call this function.
	
	if (vector_result == NULL)
	{
		vector_result = (GLfloat*)malloc(sizeof(GLfloat) * 3 * loadedModel2->size());
	}
	float t1,t2,t_temp;
	if (2 * fraction > float(1.0)) {
		t1 = float(1.0);
	}
	else {
		t1 = 2 * fraction;
	}

	if (float(0)>(2 * fraction - 1)) {
		t_temp = float(0);
	}
	else {
		t_temp = 2 * fraction - 1;
	}

	if (t_temp > float(1.0)) {
		t2 = float(1.0);
	}
	else {
		t2 = t_temp;
	}

		for (int i = 0; i < size; i++) {
			vector_result[i * 3 + 0] = loadedModel1->getVertices()[i].x + t1  * vector_diff_2[i * 3 + 0] - t2* vector_diff[i * 3 + 0];
			vector_result[i * 3 + 1] = loadedModel1->getVertices()[i].y + t1 * vector_diff_2[i * 3 + 1] - t2* vector_diff[i * 3 + 1];
			vector_result[i * 3 + 2] = loadedModel1->getVertices()[i].z + t1 * vector_diff_2[i * 3 + 2] - t2* vector_diff[i * 3 + 2];
		}


		//---------------------------
		// Draw the output
		loadedModel1->updateVertices(vector_result);
		
}



bool go_down = false;
bool go_up = false;

////////////keyframe////

/*!
A struct to define keyframe
*/
typedef struct _keyframe
{
	float               _t; // the time fraction
	glm::vec3           _p; // the position
	glm::quat           _q; // the orientation

							/*
							Constructor
							*/
	_keyframe(float t, glm::vec3 p, glm::quat q)
	{
		_t = t;
		_p = p;
		_q = q;
	}

	/*
	Default constructor
	*/
	_keyframe()
	{
		_t = -1.0;
		_p = glm::vec3(0.0, 0.0, 0.0);
		_q = glm::quat(0.0, 0.0, 0.0, 0.0);
	}

	// prints the data into a terminal
	void print(void)
	{
		cout << "t: " << _t << "\tp: " << _p.x << ", " << _p.y << ", " << _p.z << "\tq: " << _q.x << ", " << _q.y << ", " << _q.z << ", " << _q.w << endl;
	}

}Keyframe;

/*
Type for the keyframe animation
*/
typedef map<double, Keyframe> KeyframeAnimation;

// Variable to store the keyframes
KeyframeAnimation myKeyframes;

/*!
@brief returns the two keyframes for a given time.
@param keyframes - a map with all keyframes of type KeyframeAnimation
@param time - the time fraction between 0 and 1.
@param k0, reference to the first keyframe
@param k2, reference to the second keyframe
@return the number of keyframes. 1 if the time is equal to a keyframe, otherwise 2.
*/
int getKeyframes(KeyframeAnimation& keyframes, const double time, Keyframe& k0, Keyframe& k1)
{
	int num_keyframes = 0;

	// get a keyframe iterator
	KeyframeAnimation::iterator k_itr = keyframes.lower_bound(time);

	Keyframe k0_temp, k1_temp;

	// Obtain the first keyframe
	k1 = (*k_itr).second; num_keyframes++;


	// Check whether we are not at the beginning of this map
	if (k_itr != keyframes.begin())
	{
		k_itr--;  // decrement
		k0 = (*k_itr).second; // obtain the second keyframe
		num_keyframes++;
	}

	// write the first keyframe into k0 if we only have one
	if (num_keyframes == 1)
	{
		k0 = k1;
	}

	return num_keyframes;
}

/*!
@brief Interpolate between two keyframes
@param fraction - the time fraction for the interpolation / the location between two keyframes.
The value must be between 0 and 1.
@param k0, the start keyframe
@param k1, the end keyframe,
@param res, reference to a variable for the result.
*/
bool interpolateKeyframe(const float fraction, const Keyframe& k0, const Keyframe& k1, Keyframe& res)
{
	/////////////////////////////////////////////////////////////////////////
	// 1. Check the time delta

	// delta time
	float delta_t = k1._t - k0._t;

	// Check whether we have a delta time. Otherwise, we are at the location of exactly one keyframe
	if (delta_t == 0.0f) {
		res = k0;
		return true;
	}

	/////////////////////////////////////////////////////////////////////////
	// 2. Interpolat the position

	// get the delta
	glm::vec3 delta_p = k1._p - k0._p;

	// position interpolation
	glm::vec3 p_int = k0._p + delta_p * (fraction - k0._t) / (delta_t);


	/////////////////////////////////////////////////////////////////////////
	// 3. Rotation interpolation

	// Calculate the distance between the target angle and the current angle.
	float delta_angle = sqrt((k1._q.x - k0._q.x)*(k1._q.x - k0._q.x) +
		(k1._q.y - k0._q.y)*(k1._q.y - k0._q.y) +
		(k1._q.z - k0._q.z)*(k1._q.z - k0._q.z) +
		(k1._q.w - k0._q.w)*(k1._q.w - k0._q.w));


	// Linear interpolation of the rotation using slerp
	glm::quat r_int = glm::slerp(k0._q, k1._q, (fraction - k0._t) / (delta_t));


	/////////////////////////////////////////////////////////////////////////
	// 4. Write the result
	res = Keyframe(fraction, p_int, r_int);

	return true;
}

/*!
This initializes the keyframes.
*/
void initKeyframeAnimation(void)
{
	myKeyframes[0.0] = Keyframe(0.0, glm::vec3(0.0, 0.0, 0.0), angleAxis(0.0f, glm::vec3(0.0, 0.0, 1.0)));
	myKeyframes[0.5] = Keyframe(0.5, glm::vec3(0.5, 0.0, 0.0), angleAxis(0.57f, glm::vec3(0.0, 0.0, 1.0)));
	myKeyframes[0.7] = Keyframe(0.7, glm::vec3(0.7, 0.5, 0.0), angleAxis(1.28f, glm::vec3(0.0, 0.0, 1.0)));
	myKeyframes[0.8] = Keyframe(0.8, glm::vec3(0.35, 0.7, 0.0), angleAxis(1.53f, glm::vec3(0.0, 0.0, 1.0)));
	myKeyframes[1.0] = Keyframe(1.0, glm::vec3(0.2, 0.9, 0.0), angleAxis(1.98f, glm::vec3(0.0, 0.1, 1.0)));

}





int main(int argc, const char * argv[])
{
    
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// Init glfw, create a window, and init glew
    
    // Init the GLFW Window
    window = initWindow();
    
    
    // Init the glew api
    initGlew();
    SetCameraManipulator(CameraTypes::CAMERA_MANIPULATOR);

    

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// Create some models
    
    // coordinate system
    CoordSystem* cs = new CoordSystem(0.0);
    
    
    // create an apperance object.
    GLAppearance* apperance_0 = new GLAppearance("../../data/shaders/multi_vertex_lights.vs", "../../data/shaders/multi_vertex_lights.fs");
    
	apperance_water = new GLAppearance("../../data/shaders/displacement_texture.vs", "../../data/shaders/displacement_texture.fs");


    GLDirectLightSource  light_source;
    light_source._lightPos = glm::vec4(20.0,20.0,0.0, 0.0);
    light_source._ambient_intensity = 0.2;
    light_source._specular_intensity = 1.5;
    light_source._diffuse_intensity = 2.0;
    light_source._attenuation_coeff = 0.0;
    
	///////water lights/////
	GLDirectLightSource  light_source_water;
	light_source_water._lightPos = glm::vec4(00.0, 5.0, 20.0, 0.0);
	light_source_water._ambient_intensity = 0.2;
	light_source_water._specular_intensity = 7.5;
	light_source_water._diffuse_intensity = 1.0;
	light_source_water._attenuation_coeff = 0.0;

	apperance_water->addLightSource(light_source_water);

	GLSpotLightSource spotlight_source_water;
	spotlight_source_water._lightPos = glm::vec4(0.0, 20.0, 20.0, 1.0);
	spotlight_source_water._ambient_intensity = 0.2;
	spotlight_source_water._specular_intensity = 1.0;
	spotlight_source_water._diffuse_intensity = 5.0;
	spotlight_source_water._attenuation_coeff = 0.0002;
	spotlight_source_water._cone_direction = glm::vec3(-1.0, -1.0, -1.0);
	spotlight_source_water._cone_angle = 20.0;

	//apperance_water->addLightSource(spotlight_source_water);

	GLMaterial material_water;
	material_water._diffuse_material = glm::vec3(0.8, 0.8, 0.8);
	material_water._ambient_material = glm::vec3(0.8, 0.8, 0.8);
	material_water._specular_material = glm::vec3(1.0, 1.0, 1.0);
	material_water._shininess = 12.0;
	material_water._transparency = 1.0;

	apperance_water->setMaterial(material_water);

	//adding water texture
	GLMultiTexture* texture_water = new GLMultiTexture();
	int texid_water = texture_water->loadAndCreateTextures("../../data/textures/water2.bmp", "../../data/maps/water.bmp");

	apperance_water->setTexture(texture_water);
	apperance_water->finalize();

	// create the sphere geometry
	GLPlane3D* plane_water = new GLPlane3D(0.0, 0.0, -80.0, 5000.0, 5000.0); /////////////////////sea level here
	plane_water->setApperance(*apperance_water);
	plane_water->init();
	// If you want to change appearance parameters after you init the object, call the update function
	apperance_water->updateLightSources();

	// enable the program
	glUseProgram(apperance_water->getProgram());
	int location_water = glGetUniformLocation(apperance_water->getProgram(), "texture_delta");
	glUniform1f(location_water, 0.00f);
	glUniform1f(glGetUniformLocation(apperance_water->getProgram(), "bump_mode"), 0);
	/////////////////////////////////////////////////////////////////////////////////

    // add the light to this apperance object
    apperance_0->addLightSource(light_source);
    
    // Create a material object
    GLMaterial material_0;
    material_0._diffuse_material = glm::vec3(0.8, 0.8, 0.8);
    material_0._ambient_material = glm::vec3(0.8, 0.8, 0.8);
    material_0._specular_material = glm::vec3(0.1, 0.1, 0.1);
    material_0._shininess = 12.0;
    material_0._transparency = 1.0;
    
    // Add the material to the apperance object
    apperance_0->setMaterial(material_0);
    apperance_0->finalize();
    
	//add texture here:


    // If you want to change appearance parameters after you init the object, call the update function
    apperance_0->updateLightSources();

    
    //loadedModel1 = new GLObjectObj("../../data/dphn1.obj");
	loadedModel1 = new GLObjectObj("./dphn1.obj");
    loadedModel1->setApperance(*apperance_0);
    loadedModel1->init();
    

    glm::mat4 tranform = glm::scale(glm::vec3(10.0, 10.0f, 10.0f));
    loadedModel1->setMatrix(tranform);
    
	TempModel = loadedModel1;
    
    //loadedModel2 = new GLObjectObj("../../data/dphn2.obj");
	loadedModel2 = new GLObjectObj("./temp.obj");
    loadedModel2->setApperance(*apperance_0);
    loadedModel2->init();
    loadedModel2->setMatrix(tranform);
    
    
    // init the difference vector for the morphing operation.
    init_morphing();
    
    ////////////////////////////////////ADD a Ball/////////////////////
	ball1 = new GLAppearance("../../data/shaders/multi_vertex_lights.vs", "../../data/shaders/multi_vertex_lights.fs");

	// The spotlight object
//	GLSpotLightSource  light_source1;
	light_source1._lightPos = glm::vec4(40.0, 15.0, 35.0, 1.0);
	light_source1._ambient_intensity = 0.02;
	light_source1._specular_intensity = 0.9;
	light_source1._diffuse_intensity = 0.9;
	light_source1._attenuation_coeff = 0.0;
	light_source1._cone_angle = 17.0; // in degree
	light_source1._cone_direction = glm::vec3(0.0, -13.0, -35.0); // this must be aligned with the object and light position.
	light_source1._inner_angle = 12.0;
	light_source1._outer_angle = 17.0;

//	GLDirectLightSource  light_source2;
	light_source2._lightPos = glm::vec4(-20.0, -10.0, 20.0, 0.0);
	light_source2._ambient_intensity = 0.005;
	light_source2._specular_intensity = 0.4;
	light_source2._diffuse_intensity = 0.8;
	light_source2._attenuation_coeff = 0.12;

	// add the spot light to this apperance object
	ball1->addLightSource(light_source1);
	ball1->addLightSource(light_source2);

	// Create a material object
//	GLMaterial ball_material;
	ball_material._diffuse_material = glm::vec3(0.0, 0.0, 0.0); //   glm::vec3(0.93, 0.9, 0.11)
	ball_material._ambient_material = glm::vec3(0.0, 0.0, 0.0); //   glm::vec3(0.93, 0.9, 0.11)
	ball_material._specular_material = glm::vec3(1.0, 1.0, 1.0); //    glm::vec3(1.0, 1.0, 1.0)
	ball_material._shininess = 90.0;

	// Add the material to the apperance object
	ball1->setMaterial(ball_material);
	
	ball1->updateLightSources();

	ball1->finalize();

	// create the sphere geometry
	sphere = new GLSphere3D(0.0, 0.0, 125.0, 10.0, 450, 250);
	



//	ball_material._diffuse_material = glm::vec3(0.93, 0.9, 0.11);
//	ball_material._ambient_material = glm::vec3(0.93, 0.9, 0.11);
//	ball1->updateMaterial();
	
	
	sphere->setApperance(*ball1);
	sphere->init();
	/////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// Main render loop
    
    // Set up our green background color
	static const GLfloat clear_color[] = { 0.6f, 0.7f, 1.0f, 1.0f };
	static const GLfloat clear_depth[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    // This sets the camera to a new location
    // the first parameter is the eye position, the second the center location, and the third the up vector. 
    //SetViewAsLookAt(glm::vec3(0.0f, 500.0f, 0.0f), glm::vec3(1.0f, 0.0f, 50.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    
    
    // Enable depth test
    // ignore this line, it allows us to keep the distance value after we proejct each object to a 2d canvas.
    glEnable(GL_DEPTH_TEST);
    
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// Blending
    
    // Enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    

	/////water/////
	// Set the keyboard callback so that when we press ESC, it knows what to do.
	glfwSetKeyCallback(window, keyboard_callback);
	time(0);
	/////water//////

	initKeyframeAnimation();
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// Main render loop
    
    // This is our render loop. As long as our window remains open (ESC is not pressed), we'll continue to render things.
    while(!glfwWindowShouldClose(window))
    {
        
        // Clear the entire buffer with our green color (sets the background to be green).
        glClearBufferfv(GL_COLOR , 0, clear_color);
        glClearBufferfv(GL_DEPTH , 0, clear_depth);
        
		//////////////////////////////////////////////////////////////////
		// Interpolate between keyframes
		Keyframe k0, k1, k_res;

		float time = glfwGetTime();

		float f = getTimeFraction(time, 8.0); // we assume that the animation takes 8 seconds

		int num = getKeyframes(myKeyframes, f, k0, k1);

		bool ret = interpolateKeyframe(f, k0, k1, k_res);

		//k_res.print();

		//
		//////////////////////////////////////////////////////////////////

		// [this is the place where we need to draw some objects]


        //---
        // this morphes the model.
        //my_morphing_callback(3.0);
		if (jump == true) {
			my_morphing_callback_2(3.0);
		}
		loadedModel1->draw();
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //// This renders the objects
        
        // Set the trackball locatiom
        SetTrackballLocation(GetCurrentCameraMatrix(), GetCurrentCameraTranslation());
        
		if (view == 0) {
			SetViewAsLookAt(glm::vec3(0.0f, 500.0f, 0.0f), glm::vec3(1.0f, 0.0f, 50.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		}
		else if (view ==1 ) {
			SetViewAsLookAt(glm::vec3(0.0f, 0.0f, 200.0f), glm::vec3(1.0f, 0.0f, 50.0f), glm::vec3(0.0f, 0.0f, -1.0f));
		}
		else if (view ==2) {
			SetViewAsLookAt(glm::vec3(0.0f, -500.0f, 0.0f), glm::vec3(1.0f, 0.0f, 50.0f), glm::vec3(0.0f, -1.0f, 0.0f));
		}

        // draw the objects
        cs->draw();
		plane_water->draw();

		//draw the ball
		sphere->draw();
 
		glUseProgram(apperance_water->getProgram());
		float time_2 = (float)clock() / CLOCKS_PER_SEC;
		float delta = 0.05f * sin(time_2 * 5.0) + 0.05f;
		glUniform1f(location_water, delta);

		// change the texture appearance blend mode
		bool ret_2 = texture_water->setTextureBlendMode(g_change_texture_blend);
		if (ret_2)apperance_water->updateTextures();



		// Swap the buffers so that what we drew will appear on the screen.
		glfwSwapBuffers(window);
		glfwPollEvents();


    }
	glfwTerminate();
    delete cs;

}

