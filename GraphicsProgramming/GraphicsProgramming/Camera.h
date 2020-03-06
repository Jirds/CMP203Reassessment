#pragma once
#include"Vector3.h"
class Camera
{

public:

	Camera();
	~Camera();
	void update();
	void updateCameraRot(float, float, float, float, float);
	void rotateYaw(float mouseX, float width, float dt);
	void rotatePitch(float, float, float);
	void moveForward(float);
	void moveBackward(float);
	void moveUp(float);
	void moveDown(float);

	Vector3 getPos();
	Vector3 getUp();
	Vector3 getLook();

	float yaw = 0.00;
	float pitch = 0.00;
	float roll = 0.00;


private:

	Vector3 pos = Vector3(1.0, 60.0, -1.0);
	Vector3 forward = Vector3(5.0, -1.0, 5.0);
	Vector3 up = Vector3(0.0, 1.0, 0.0);


	float speed = 15;
};