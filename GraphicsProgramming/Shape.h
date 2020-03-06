#include "glut.h"
#include <gl/gl.h>
#include <gl/glu.h>

class Shape
{
public:
		Shape();
		~Shape();

		void Plane(float width, float height, int xSegs, int ySegs);

		void Quad(float width, float height, int xSegs, int ySegs, float xNorm, float yNorm, float zNorm);

		void Cuboid(float width, float height, float length, int xSegs, int ySegs, int zSegs, bool exNorms);


 };
 
