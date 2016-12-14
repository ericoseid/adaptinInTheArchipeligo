#ifndef _maleIndividual_
#define _maleIndividual_

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include "femaleIndividual.h"
using namespace std;

class maleIndividual{
  GLfloat vertices[16];
  GLuint VAO;
  GLuint VBO;
  int dir;
  GLfloat beakValue;
  int numFrames;

public:

  maleIndividual(GLfloat bottomLeftX, GLfloat bottomLeftY);

  void draw();

  void changeDir();

  void move();

  int getNumFrames();

  bool checkContact(femaleIndividual f);

  femaleIndividual makeLadyBaby();
  
  maleIndividual makeManBaby();
};

#endif
