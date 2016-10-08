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

// GLEW include
#include <GL/glew.h>

// GLM include files
#define GLM_FORCE_INLINE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>


// glfw includes
#include <GLFW/glfw3.h>


// include local files
#include "controls.h"
#include "HCI557Common.h"
#include "CoordSystem.h"
#include "Sphere3D.h"
#include "GLAppearance.h"




using namespace std;


// The handle to the window object
GLFWwindow*         window;

// Define some of the global variables we're using for this sample
GLuint program;

/* A trackball to move and rotate the camera view */
extern Trackball trackball;



int main(int argc, const char * argv[])
{
    
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// Init glfw, create a window, and init glew
    
    // Init the GLFW Window
    window = initWindow();
    
    
    // Init the glew api
    initGlew();
    
    

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// Create some models
    
    // coordinate system
    CoordSystem* cs = new CoordSystem(40.0);

    /**
    // create an apperance object.
    GLAppearance* apperance = new GLAppearance("../../data/shaders/multi_vertex_lights.vs", "../../data/shaders/multi_vertex_lights.fs");
    
    
    // The spotlight object
    GLSpotLightSource  light_source1;
    light_source1._lightPos = glm::vec4(10.0,20.0,20.0, 1.0);
    light_source1._ambient_intensity = 0.01;
    light_source1._specular_intensity = 8.0;
    light_source1._diffuse_intensity = 3.0;
    light_source1._attenuation_coeff = 0.02;
    light_source1._cone_angle = 24.0; // in degree
    light_source1._cone_direction = glm::vec3(-0.5, -1.0, -1.0); // this must be aligned with the object and light position.
    
    
    GLDirectLightSource  light_source2;
    light_source2._lightPos = glm::vec4(30.0,0.0,0.0, 0.0);
    light_source2._ambient_intensity = 0.1;
    light_source2._specular_intensity = 5.5;
    light_source2._diffuse_intensity = 1.0;
    light_source2._attenuation_coeff = 0.02;
    //light_source2._cone_angle = 12.0; // in degree
    //light_source2._cone_direction = glm::vec3(-1.0, 0.0, 0.0); // this must be aligned with the object and light position.
    
    
    // add the spot light to this apperance object
    apperance->addLightSource(light_source1);
    apperance->addLightSource(light_source2);
    
    // Create a material object
    GLMaterial material;
    material._diffuse_material = glm::vec3(1.0, 0.0, 0.0);
    material._ambient_material = glm::vec3(1.0, 0.0, 0.0);
    material._specular_material = glm::vec3(1.0, 1.0, 1.0);
    material._shininess = 80.0;
    
    // Add the material to the apperance object
    apperance->setMaterial(material);
    apperance->finalize();
    
    // create the sphere geometry
    GLSphere3D* sphere = new GLSphere3D(10.0, 0.0, 0.0, 10.0, 90, 50);
    sphere->setApperance(*apperance);
    sphere->init();
    
    
    
    material._diffuse_material = glm::vec3(1.0, 0.0, 0.0);
    material._ambient_material = glm::vec3(1.0, 0.0, 0.0);
    apperance->updateMaterial();
    light_source1._diffuse_intensity = 1.0;
    apperance->updateLightSources();
    
	**/

	///////////////////////object 2 ////////////////////////////////  THIS IS THE FIRST OBJECT ON THE LEFT
	//create object 2
	GLAppearance* apperance2 = new GLAppearance("../../data/shaders/multi_vertex_lights.vs", "../../data/shaders/multi_vertex_lights.fs");

	//create light
	/**
	GLDirectLightSource  light_source3;
	light_source3._lightPos = glm::vec4(0.0, 0.0, 30.0, 0.0);
	light_source3._ambient_intensity = 0.1;
	light_source3._specular_intensity = 5.5;
	light_source3._diffuse_intensity = 1.0;
	light_source3._attenuation_coeff = 0.02;
	*/

	GLDirectLightSource  light_source3;
	light_source3._lightPos = glm::vec4(5.0, 5.0, 5.0, 0.0);
	light_source3._ambient_intensity = 0.05;
	light_source3._specular_intensity = 0.5;
	light_source3._diffuse_intensity = 0.01;
	light_source3._attenuation_coeff = 1.0;

	// add the spot light to this apperance object
	apperance2->addLightSource(light_source3);


	// Create a material object 2
	GLMaterial material2;
	material2._diffuse_material = glm::vec3(0.6, 0.04, 0.08);
	material2._ambient_material = glm::vec3(0.6, 0.04, 0.08);
	material2._specular_material = glm::vec3(1.0, 1.0, 1.0);
	material2._shininess = 40.0;

	// Add the material to the apperance object
	apperance2->setMaterial(material2);
	apperance2->finalize();
    
	// create the sphere geometry
	GLSphere3D* sphere2 = new GLSphere3D(-50.0, 0.0, 0.0, 10.0, 90, 50);
	sphere2->setApperance(*apperance2);
	sphere2->init();

	material2._diffuse_material = glm::vec3(1.0, 0.0, 0.0);
	material2._ambient_material = glm::vec3(1.0, 0.0, 0.0);
	apperance2->updateMaterial();
	light_source3._diffuse_intensity = 1.0;
	apperance2->updateLightSources();



	///////object 3  //////////////////////// THIS IS SECOND OBJECT ON THE LEFT

	// create an apperance object.
	GLAppearance* apperance3 = new GLAppearance("../../data/shaders/multi_vertex_lights.vs", "../../data/shaders/multi_vertex_lights.fs");


	// The spotlight object

	GLSpotLightSource  light_source4;
	light_source4._lightPos = glm::vec4(-20.0, 20.0, 0.0, 1.0);
	light_source4._ambient_intensity = 0.01;
	light_source4._specular_intensity = 8.0;
	light_source4._diffuse_intensity = 0.01;
	light_source4._attenuation_coeff = 0.02;
	light_source4._cone_angle = 12.0; // in degree
	light_source4._cone_direction = glm::vec3(0.0, -1.0, -1.0); // this must be aligned with the object and light position.


	GLDirectLightSource  light_source5;
	light_source5._lightPos = glm::vec4(15.0, 5.0, 5.0, 0.0);
	light_source5._ambient_intensity = 0.05;
	light_source5._specular_intensity = 0.0;
	light_source5._diffuse_intensity = 1.0;
	light_source5._attenuation_coeff = 0.02;
	//light_source2._cone_angle = 12.0; // in degree
	//light_source2._cone_direction = glm::vec3(-1.0, 0.0, 0.0); // this must be aligned with the object and light position.


	// add the spot light to this apperance object
	//apperance3->addLightSource(light_source4);
	apperance3->addLightSource(light_source5);

	// Create a material object
	GLMaterial material3;
	material3._diffuse_material = glm::vec3(0.06, 0.13, 0.72);
	material3._ambient_material = glm::vec3(0.06, 0.13, 0.72);
	material3._specular_material = glm::vec3(1.0, 1.0, 1.0);
	material3._shininess = 5.0;

	// Add the material to the apperance object
	apperance3->setMaterial(material3);
	apperance3->finalize();

	// create the sphere geometry
	GLSphere3D* sphere3 = new GLSphere3D(-20.0, 0.0, 0.0, 10.0, 90, 50);
	sphere3->setApperance(*apperance3);
	sphere3->init();



	material3._diffuse_material = glm::vec3(0.06, 0.13, 0.72);
	material3._ambient_material = glm::vec3(0.06, 0.13, 0.72);
	apperance3->updateMaterial();
	light_source4._diffuse_intensity = 0.5;
	apperance3->updateLightSources();


	///////////////////// THIS IS THE THIRD OBJECT ON THE LEFT    OBJECT 4 //////////////

	// create an apperance object.
	GLAppearance* apperance4 = new GLAppearance("../../data/shaders/multi_vertex_lights.vs", "../../data/shaders/multi_vertex_lights.fs");


	// The spotlight object
	GLSpotLightSource  light_source6;
	light_source6._lightPos = glm::vec4(10.0, 20.0, 20.0, 1.0);
	light_source6._ambient_intensity = 0.005;
	light_source6._specular_intensity = 0.0;
	light_source6._diffuse_intensity = 99.0;
	light_source6._attenuation_coeff = 0.0;
	light_source6._cone_angle = 20.0; // in degree
	light_source6._cone_direction = glm::vec3(0.0, -1.0, -1.0); // this must be aligned with the object and light position.


	GLDirectLightSource  light_source7;
	light_source7._lightPos = glm::vec4(5.0, 1.0, 10.0, 0.0);
	light_source7._ambient_intensity = 0.0;
	light_source7._specular_intensity = 4.0;
	light_source7._diffuse_intensity = 0.0;
	light_source7._attenuation_coeff = 0.0;
	//light_source2._cone_angle = 12.0; // in degree
	//light_source2._cone_direction = glm::vec3(-1.0, 0.0, 0.0); // this must be aligned with the object and light position.


	// add the spot light to this apperance object
	apperance4->addLightSource(light_source6);
	apperance4->addLightSource(light_source7);

	// Create a material object
	GLMaterial material4;
	material4._diffuse_material = glm::vec3(0.01, 1.0, 0.01);
	material4._ambient_material = glm::vec3(0.01, 1.0, 0.01);
	material4._specular_material = glm::vec3(1.0, 1.0, 1.0);
	material4._shininess = 80.0;

	// Add the material to the apperance object
	apperance4->setMaterial(material4);
	apperance4->finalize();

	// create the sphere geometry
	GLSphere3D* sphere4 = new GLSphere3D(10.0, 0.0, 0.0, 10.0, 450, 250);
	sphere4->setApperance(*apperance4);
	sphere4->init();



	material4._diffuse_material = glm::vec3(0.01, 1.0, 0.01);
	material4._ambient_material = glm::vec3(0.01, 1.0, 0.01);
	apperance4->updateMaterial();
	light_source6._diffuse_intensity = 1.0;
	apperance4->updateLightSources();

	////////////////////FIRST OBJECT ON THE RIGHT



	// create an apperance object.
	GLAppearance* apperance = new GLAppearance("../../data/shaders/multi_vertex_lights.vs", "../../data/shaders/multi_vertex_lights.fs");


	// The spotlight object
	GLSpotLightSource  light_source1;
	light_source1._lightPos = glm::vec4(40.0, 15.0, 35.0, 1.0);
	light_source1._ambient_intensity = 0.02;
	light_source1._specular_intensity = 0.9;
	light_source1._diffuse_intensity = 0.9;
	light_source1._attenuation_coeff = 0.0;
	light_source1._cone_angle = 17.0; // in degree
	light_source1._cone_direction = glm::vec3(0.0, -13.0, -35.0); // this must be aligned with the object and light position.
	light_source1._inner_angle = 12.0;
	light_source1._outer_angle = 17.0;

	GLDirectLightSource  light_source2;
	light_source2._lightPos = glm::vec4(-20.0, -10.0, 20.0, 0.0);
	light_source2._ambient_intensity = 0.005;
	light_source2._specular_intensity = 0.4;
	light_source2._diffuse_intensity = 0.8;
	light_source2._attenuation_coeff = 0.12;
	


	// add the spot light to this apperance object
	apperance->addLightSource(light_source1);
	apperance->addLightSource(light_source2);

	// Create a material object
	GLMaterial material;
	material._diffuse_material = glm::vec3(0.93, 0.9, 0.11);
	material._ambient_material = glm::vec3(0.93, 0.9, 0.11);
	material._specular_material = glm::vec3(1.0, 1.0, 1.0);
	material._shininess = 90.0;

	// Add the material to the apperance object
	apperance->setMaterial(material);
	apperance->finalize();

	// create the sphere geometry
	GLSphere3D* sphere = new GLSphere3D(40.0, 0.0, 0.0, 10.0, 450, 250);
	sphere->setApperance(*apperance);
	sphere->init();



	material._diffuse_material = glm::vec3(0.93, 0.9, 0.11);
	material._ambient_material = glm::vec3(0.93, 0.9, 0.11);
	apperance->updateMaterial();
	light_source1._diffuse_intensity = 0.9;
	apperance->updateLightSources();


	
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// Main render loop
    
    // Set up our green background color to WHITE
    static const GLfloat clear_color[] = { 1.0f, 1.0f, 1.0f, 1.0f };  /// edited
    static const GLfloat clear_depth[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    
    // This sets the camera to a new location
    // the first parameter is the eye position, the second the center location, and the third the up vector. 
    SetViewAsLookAt(glm::vec3(0.0f, 0.0f, 142.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    
    
    // Enable depth test
    // ignore this line, it allows us to keep the distance value after we proejct each object to a 2d canvas.
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
   // sphere->enableNormalVectorRenderer();
    
    // This is our render loop. As long as our window remains open (ESC is not pressed), we'll continue to render things.
    while(!glfwWindowShouldClose(window))
    {
        
        // Clear the entire buffer with our green color (sets the background to be green).
        glClearBufferfv(GL_COLOR , 0, clear_color);
        glClearBufferfv(GL_DEPTH , 0, clear_depth);
        
    
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //// This renders the objects
        
        // Set the trackball locatiom
        SetTrackballLocation(trackball.getRotationMatrix());
        
        // draw the objects
        cs->draw();
        
        sphere->draw();

		sphere2->draw();

		sphere3->draw();

		sphere4->draw();

        
        //// This renders the objects
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        
        
        // Swap the buffers so that what we drew will appear on the screen.
        glfwSwapBuffers(window);
        glfwPollEvents();
        
    }
    
    
    delete cs;


}

