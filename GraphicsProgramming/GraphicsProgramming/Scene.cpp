#include "Scene.h"
//#include "Shape.cpp"

// Scene constructor, initilises OpenGL
// You should add further variables to need initilised.
Scene::Scene(Input* in)
{
	// Store pointer for input class
	input = in;

	//OpenGL settings
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.39f, 0.58f, 93.0f, 1.0f);			// Cornflour Blue Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glClearStencil(0);									// Clear stencil buffer
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);
	gluPerspective(120.0f, (GLfloat)16.0 / (GLfloat)9.0, 1, 150.0f);

	glutSetCursor(GLUT_CURSOR_NONE);
	// Other OpenGL / render setting should be applied here.
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST
	);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST
	);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	// Initialise scene variables
	wood = SOIL_load_OGL_texture
	(
		"gfx/wooden.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	floor = SOIL_load_OGL_texture
	(
		"gfx/red carpet.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	wall = SOIL_load_OGL_texture
	(
		"gfx/Brick.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
}

void Scene::handleInput(float dt)
{
	glGetIntegerv(GL_POLYGON_MODE, polygonMode);
	if (input->isKeyDown('r'))
	{
		if (polygonMode[0] == GL_LINE)
		{
			glPolygonMode(GL_FRONT, GL_FILL);
			input->SetKeyUp('r');
		}
		else if (polygonMode[0] == GL_FILL)
		{
			glPolygonMode(GL_FRONT, GL_LINE);
			input->SetKeyUp('r');
		}
	}



	if (input->isKeyDown('w'))
	{
		camera1.moveForward(dt);
		input->SetKeyUp('w');
	}
	if (input->isKeyDown('s'))
	{
		camera1.moveBackward(dt);
		input->SetKeyUp('s');
	}
	if (input->isKeyDown('q'))
	{
		camera1.moveUp(dt);
		input->SetKeyUp('q');
	}
	if (input->isKeyDown('e'))
	{
		camera1.moveDown(dt);
		input->SetKeyUp('e');
	}
	if (input->isKeyDown('l'))
	{
		if (redLight)
		{
			glDisable(GL_LIGHT1);
			redLight = false;
		}
		else
		{
			glEnable(GL_LIGHT1);
			redLight = true;
		}
		input->SetKeyUp('l');
	}

	
	camera1.updateCameraRot(input->getMouseX(),input->getMouseY(), width, height, dt);
	glutWarpPointer(width/2, height/2);
	//float xCurr, yCurr = 0;
	//float yaw = 0, pitch = 0, roll = 0;
	////Get the change in mouse position since last frame
	//yaw = input->getMouseX() - xLast;
	//pitch = input->getMouseY() - yLast;	
	//yaw = 0 - yaw;
	//yaw *= 7 * dt;
	//pitch *= 10 * dt;
	//
	////Save mouse position as last mouse position
	//xLast = input->getMouseX();
	//yLast = input->getMouseY();
	//glutWarpPointer(250, 250);
	// Handle user input
	void setKeyDown(unsigned char key);
	void setKeyup(unsigned char key);
	bool isKeyDown(int);


	
	
	
}
void Scene::update(float dt)
{
	// update scene related variables.
	camera1.update();


	// Calculate FPS for output
	calculateFPS();
}

void Scene::render() {



	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();
	// Set the camera  (Translate, Coords of intrest, Which way is up)
	//			x	y	  z     x(?)  y(?)  z(?)
	gluLookAt(camera1.getPos().x, camera1.getPos().y, camera1.getPos().z, camera1.getLook().x, camera1.getLook().y, camera1.getLook().z, camera1.getUp().x, camera1.getUp().y, camera1.getUp().z);
	
	float roomLength = 200;
	float roomHeight = 120.0f;
	float roomWidth = 120.0f;

	GLfloat Light_Ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat Light_Diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat Light_Specular[] = { 0.7, 0.7, 0.7, 1.0 };
	GLfloat Light_Position[] = { roomWidth/2 , roomHeight - 5.0f , -roomLength /2 , 1.0f };


	glLightfv(GL_LIGHT0, GL_AMBIENT, Light_Ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, Light_Diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, Light_Position);
	glLightfv(GL_LIGHT0, GL_SPECULAR, Light_Specular);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.4);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.02);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0);

	GLfloat Light_Amb[] = { 0.2f, 0.1f, 0.1f, 0.7f };
	GLfloat Light_Dif[] = { 0.3f, 0.1f, 0.1f, 0.3f };
	GLfloat Light_Spec[] = { 0.2, 0.1, 0.1, 0.3 };
	GLfloat Light_Pos[] = { roomWidth - 8.0f, 41.5, - 127.5f };


	glLightfv(GL_LIGHT1, GL_AMBIENT, Light_Amb);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Light_Dif);
	glLightfv(GL_LIGHT1, GL_POSITION, Light_Pos);
	glLightfv(GL_LIGHT1, GL_SPECULAR, Light_Spec);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.3);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.02);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0);

	glEnable(GL_LIGHT0);

	glPushMatrix(); // origin

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, wall); //brick wall
	glTranslatef(0.0f, 0.0f, -roomLength);
	shape.Cuboid(roomWidth, roomHeight, roomLength, 24, 24, 40, false);
	glPopMatrix();


	glPushMatrix(); //origin
	glBindTexture(GL_TEXTURE_2D, floor); //red carpet
	glTranslatef(0.0f, 0.1f, 0.0f);
	glRotatef(270, 1.0f, 0.0f, 0.0f);
	shape.Quad(roomWidth, roomLength, 24, 40, 0, 0, -1); //draw floor
	glPopMatrix();

	
	// making a table
	glPushMatrix(); // origin
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, wood); //wooden texture
	glColor3f(1.0f, 1.0f, 1.0f);
	glTranslatef(roomWidth - 35.5f, 0.0f, -130.0f);

	glPushMatrix(); // corner of table

	glPushMatrix();
	shape.Cuboid(5, 30.0f, 5.0f, 1, 6, 1, true);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(30.0f, 0.0f, 0.0f);
	shape.Cuboid(5, 30.0f, 5.0f, 1, 6, 1, true);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 30.0f);
	shape.Cuboid(5, 30.0f, 5.0f, 1, 6, 1, true);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(30.0f, 0.0f, 30.0f);
	shape.Cuboid(5.0f, 30.0f, 5.0f, 1, 6, 1, true);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 30.0f, 0.0f);
	shape.Cuboid(35.0f, 5.0f, 35.0f, 6, 1, 6, true);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(30.0f, 0.0f, 30.0f);
	shape.Cuboid(5.0f, 30.0f, 5.0f, 1, 6, 1, true);
	glPopMatrix();

	//making a lamp

	glPushMatrix();
	glTranslatef(27.5f, 35.0f, 2.5f);
	shape.Cuboid(5.0f, 1.5f, 5.0f, 6, 1, 6, true);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(28.75f, 36.5f, 3.75f);
	shape.Cuboid(1.0f, 5.0f, 1.0f, 1, 6, 1, true);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(27.5f, 41.5f, 2.5f);
	shape.Cuboid(5.0f, 6.5f, 5.0f, 1, 1, 1, true);
	glPopMatrix();

	glPopMatrix();

	glPopMatrix();


	//Making a chair
	glPushMatrix(); // origin
	glColor3f(0.3f, 0.4f, 1.0f);
	glTranslatef(40.0f, 0.0f, -roomLength + 40.5f);
	glPushMatrix(); // corner of chair

	glPushMatrix();
	shape.Cuboid(5, 15.0f, 5.0f, 1, 6, 1, true);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(30.0f, 0.0f, 0.0f);
	shape.Cuboid(5, 15.0f, 5.0f, 1, 6, 1, true);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 30.0f);
	shape.Cuboid(5, 15.0f, 5.0f, 1, 6, 1, true);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(30.0f, 0.0f, 30.0f);
	shape.Cuboid(5.0f, 15.0f, 5.0f, 1, 6, 1, true);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 15.0f, 0.0f);
	shape.Cuboid(35.0f, 5.0f, 35.0f, 6, 1, 6, true);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 20.0f, 30.0f);
	shape.Cuboid(5.0f, 15.0f, 5.0f, 1, 6, 1, true);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 20.0f, 0.0f);
	shape.Cuboid(5.0f, 15.0f, 5.0f, 1, 6, 1, true);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 35.0f, 0.0f);
	shape.Cuboid(5.0f, 15.0f, 35.0f, 1, 6, 1, true);
	glPopMatrix();

	glPopMatrix();

	glPopMatrix();


	// Render text, should be last object rendered.
	renderTextOutput();

	// Swap buffers, after all objects are rendered.
	glutSwapBuffers();
}

// Handles the resize of the window. If the window changes size the perspective matrix requires re-calculation to match new window size.
void Scene::resize(int w, int h)
{
	width = w;
	height = h;
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio = (float)w / (float)h;
	fov = 45.0f;
	nearPlane = 0.1f;
	farPlane = 300.0f;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(fov, ratio, nearPlane, farPlane);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);


}

// Calculates FPS
void Scene::calculateFPS()
{

	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);

	if (time - timebase > 1000) {
		sprintf_s(fps, "FPS: %4.2f", frame * 1000.0 / (time - timebase));
		timebase = time;
		frame = 0;
	}
}

// Compiles standard output text including FPS and current mouse position.
void Scene::renderTextOutput()
{

	

	// Render current mouse position and frames per second.
	sprintf_s(mouseText, "Mouse: %i, %i", input->getMouseX(), input->getMouseY());
	sprintf_s(rotText, "Rotation: %i, %i, %i", camera1.yaw, camera1.pitch, camera1.roll);
	displayText(-1.f, 0.96f, 1.f, 0.f, 0.f, mouseText);
	displayText(-1.f, 0.90f, 1.f, 0.f, 0.f, fps);
	displayText(-1.f, 0.84f, 1.f, 0.f, 0.f, rotText);
}

// Renders text to screen. Must be called last in render function (before swap buffers)
void Scene::displayText(float x, float y, float r, float g, float b, char* string) {
	// Get Lenth of string
	int j = strlen(string);

	// Swap to 2D rendering
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, 5, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Orthographic lookAt (along the z-axis).
	gluLookAt(0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	// Set text colour and position.
	glColor3f(r, g, b);
	glRasterPos2f(x, y);
	// Render text.
	for (int i = 0; i < j; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, string[i]);
	}
	// Reset colour to white.
	glColor3f(1.f, 1.f, 1.f);

	// Swap back to 3D rendering.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov, ((float)width / (float)height), nearPlane, farPlane);
	glMatrixMode(GL_MODELVIEW);
}
