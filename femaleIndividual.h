#ifndef _femaleIndividual_
#define _femaleIndividual_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <vector>
#include "landMass.h"
#include "geometry.h"
using namespace std;

class landMass;

class femaleIndividual{
  GLfloat vertices[12];
  GLuint VAO;
  GLuint VBO;
  int dir;
  GLfloat beakValue;
  int numFrames;
  int fed;
  landMass* home;

 public:

  femaleIndividual(GLfloat bottomLeftX, GLfloat bottomLeftY);

  void draw();

  void changeDir();

  void move();

  int getNumFrames();

  vector<GLfloat> getVertices();

  int getFed();

  void getHungry();

  void setHomeland(landMass* h);

  int inHomeland(Point p);
};

#endif
