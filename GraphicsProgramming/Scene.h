// Scene class. Configures a basic 3D scene.
// Interfaces with the Input class to handle user input
// Calculates and outputs Frames Per Second (FPS) rendered.
// Important functions are the constructor (initialising the scene), 
// update (for process user input and updating scene objects) and render (renders scene).
#ifndef _SCENE_H
#define _SCENE_H

// Include GLUT, openGL, input.
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Input.h"
#include "Camera.h"
#include "Shape.h"
#include "Model.h"
#include <stdio.h>
#include <iostream>
// Further includes should go here:
#include "SOIL.h"
#include <vector>


class Scene{

public:
	Scene(Input *in);
	// Main render function
	void render();
	// Handle input function that receives delta time from parent.
	void handleInput(float dt);
	// Update function receives delta time from parent (used for frame independent updating).
	void update(float dt);
	// Resizes the OpenGL output based on new window size.
	void resize(int w, int h);

protected:
	// Renders text (x, y positions, RGB colour of text, string of text to be rendered)
	void displayText(float x, float y, float r, float g, float b, char* string);
	// A function to collate all text output in a single location
	void renderTextOutput();
	void calculateFPS();

	// draw primitive functions
	
	//Shape Object
	


	// For access to user input.
	Input* input;
	Shape shape;
	// For Window and frustum calculation.
	int width, height;
	float fov, nearPlane, farPlane;

	// For FPS counter and mouse coordinate output.
	int frame = 0, time, timebase = 0;
	char fps[40];
	char mouseText[40];
	char rotText[80];

	float xLast = 0, yLast = 0;
	float rotation;
	float rotation2;
	float speed;

	Camera camera1;
	Model sphere;



	GLuint floor;
	GLuint wood;
	GLuint wall;
	GLint polygonMode[2];

	bool redLight = false;

};

#endif