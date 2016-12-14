#ifndef _landMass_
#define _landMass_

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <cmath>
using namespace std;

class landMass{
  GLfloat vertices[24];
  GLuint VAO;
  GLuint VBO;
  GLfloat cX;
  GLfloat cY;
  GLfloat vertDist;
  GLfloat edgeDist;
  float foodVal;
  
 public:

  //lalal
  landMass(GLfloat centerX, GLfloat centerY,
	   GLfloat distToVert, GLfloat distToEdge);

  void draw();
  float getFoodVal();
  void setFoodVal(float newVal);
};

#endif
