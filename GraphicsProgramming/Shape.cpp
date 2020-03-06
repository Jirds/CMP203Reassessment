#include "shape.h"

Shape::Shape()
{

}

Shape::~Shape()
{

}

void Shape::Plane(float width, float height, int xSegs, int ySegs)
{
	float xPanelSize = width / xSegs;
	float yPanelSize = height / ySegs;

	for (int x = 0; x < xSegs; x++)
	{
		for (int y = 0; y < ySegs; y++)
		{
			glBegin(GL_QUADS);

			glNormal3f(0.0f, 0.0f, -1.0f);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f((xPanelSize * x), (yPanelSize * y), 0); // top left

			glNormal3f(0.0f, 0.0f, -1.0f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f((xPanelSize * (x + 1)), (yPanelSize * y), 0); //top right

			glNormal3f(0.0f, 0.0f, -1.0f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f((xPanelSize * (x + 1)), (yPanelSize * (y + 1)), 0); //bottom right

			glNormal3f(0.0f, 0.0f, -1.0f);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(xPanelSize * x, (yPanelSize * (y + 1)), 0); //bottom left

			glEnd();

		}
	}
}

void Shape::Quad(float width, float height, int xSegs, int ySegs, float xNorm, float yNorm, float zNorm)
{
	float xPanelSize = width / xSegs;
	float yPanelSize = height / ySegs;

	for (int x = 0; x < xSegs; x++)
	{
		for (int y = 0; y < ySegs; y++)
		{
			glBegin(GL_QUADS);

			glNormal3f(xNorm, yNorm, zNorm);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f((xPanelSize * x), (yPanelSize * y), 0); // top left

			glNormal3f(xNorm, yNorm, zNorm);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f((xPanelSize * (x + 1)), (yPanelSize * y), 0); //top right

			glNormal3f(xNorm, yNorm, zNorm);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f((xPanelSize * (x + 1)), (yPanelSize * (y + 1)), 0); //bottom right

			glNormal3f(xNorm, yNorm, zNorm);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(xPanelSize * x, (yPanelSize * (y + 1)), 0); //bottom left

			glEnd();

		}
	}
}

void Shape::Cuboid(float width, float height, float length, int xSegs, int ySegs, int zSegs, bool exNorms)
{
	glPushMatrix();
	if (exNorms)
	{
		Quad(width, height, xSegs, ySegs, 0.0f, 0.0f, -1.0f); //front 1
	}
	else
	{
		Quad(width, height, xSegs, ySegs, 0.0f, 0.0f, 1.0f); //front 1
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, length);
	if (exNorms)
	{
		Quad(width, height, xSegs, ySegs, 0.0f, 0.0f, 1.0f); //back 3
	}
	else
	{
		Quad(width, height, xSegs, ySegs, 0.0f, 0.0f, -1.0f); //back 3
	}
	glPopMatrix();

	glPushMatrix();
	glRotatef(270, 0.0f, 1.0f, 0.0f);
	if (exNorms)
	{

		Quad(length, height, zSegs, ySegs, 0.0f, 0.0f, 1.0f); //left 4
	}
	else
	{
		Quad(length, height, zSegs, ySegs, 0.0f, 0.0f, -1.0f); //left 4
	}

	glPopMatrix();

	glPushMatrix();
	glTranslatef(width, 0.0f, 0.0f);
	glRotatef(270, 0.0f, 1.0f, 0.0f);
	if (exNorms)
	{

		Quad(length, height, zSegs, ySegs, 0.0f, 0.0f, -1.0f); //right 2
	}
	else
	{
		Quad(length, height, zSegs, ySegs, 0.0f, 0.0f, 1.0f); //right 2
	}
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1.0f, 0.0f, 0.0f);
	if (exNorms)
	{

		Quad(width, length, xSegs, zSegs, 0.0f, 0.0f, 1.0f); //bottom 6
	}
	else
	{
		Quad(width, length, xSegs, zSegs, 0.0f, 0.0f, -1.0f); //bottom 6
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, height, 0.0f);
	glRotatef(90, 1.0f, 0.0f, 0.0f);
	if (exNorms)
	{

		Quad(width, length, xSegs, zSegs, 0.0f, 0.0f, -1.0f); //top 5
	}
	else
	{
		Quad(width, length, xSegs, zSegs, 0.0f, 0.0f, 1.0f); //top 5
	}

	glPopMatrix();


}