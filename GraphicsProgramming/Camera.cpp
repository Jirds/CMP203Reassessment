#include "Camera.h"

#include <iostream>

Camera::Camera() {}
Camera::~Camera() {}

void Camera::updateCameraRot(float mouseX, float mouseY, float width, float height, float dt)
{
	if (mouseX != (width / 2))
	{
		rotateYaw(mouseX, width, dt);
	
	}

	if (mouseY != (height / 2))
	{
		rotatePitch(mouseY, height, dt);
	}
}
void Camera::rotatePitch(float mouseY, float height, float dt)
{
	pitch -= mouseY - (height / 2), dt;
}
void Camera::rotateYaw(float mouseX, float width, float dt)
{
	yaw += mouseX - (width / 2), dt;

}


void Camera::update() {
	float cosR, cosP, cosY;
	float sinR, sinP, sinY;
	// Only want to calculate these values once, when rotation changes, not every frame.
	cosY= cosf(yaw*3.1415/180);
	cosP= cosf(pitch*3.1415/180);
	cosR= cosf(roll*3.1415/180);
	sinY= sinf(yaw*3.1415/180);
	sinP= sinf(pitch*3.1415/180);
	sinR= sinf(roll*3.1415/180);
	//This using the parametric equation of a sphere
	// Calculate the three vectors to put into  gluLookat
	// Look direction,  position and the up vector 
	// This function could also calculate the right vector
	forward.x= sinY* cosP;
	forward.y= sinP;
	forward.z = cosP * -cosY;
		// Look At Point
		// To calculate add Forward Vector to Camera position.
		// Up Vector
		up.x = -cosY * sinR -sinY * sinP * cosR;
	up.y = cosP * cosR;
	up.z = -sinY * sinR -sinP * cosR * -cosY;
	// Side Vector (right)
	// this is a cross product between the forward and up vector. 
	// If you don’t need to calculate this,  don’t do it.
	}
		

void Camera::moveForward(float dt)
{
	pos.x += forward.x * (speed * dt);
	pos.y += forward.y * (speed * dt);
	pos.z += forward.z * (speed * dt);
}
void Camera::moveBackward(float dt)
{
	pos.x -= forward.x * (speed * dt);
	pos.y -= forward.y * (speed * dt);
	pos.z -= forward.z * (speed * dt);
}
void Camera::moveUp(float dt)
{
	pos.x += up.x * (speed * dt);
	pos.y += up.y * (speed * dt);
	pos.z += up.z * (speed * dt);
}
void Camera::moveDown(float dt)
{
	pos.x -= up.x * (speed * dt);
	pos.y -= up.y * (speed * dt);
	pos.z -= up.z * (speed * dt);
}


 
Vector3 Camera::getPos()
{
	return pos;

}
Vector3 Camera::getUp()
{
	return up;
}
Vector3 Camera::getLook()
{
	Vector3 look = pos + forward;

	return look;
}