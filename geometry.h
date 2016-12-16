#ifndef _geometry_
#define _geometry_

#include <GL/glew.h>

struct Point{
  GLfloat x;
  GLfloat y;

  Point(GLfloat xCor, GLfloat yCor);
};

int isInSquare(Point p, Point bLeft, float s);

#endif
