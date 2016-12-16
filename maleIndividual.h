#ifndef _maleIndividual_
#define _maleIndividual_

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include "landMass.h"
#include "femaleIndividual.h"
#include "geometry.h"
using namespace std;

class landMass;
class femaleIndividual;

class maleIndividual{
  GLfloat vertices[16];
  GLuint VAO;
  GLuint VBO;
  int dir;
  GLfloat beakValue;
  int numFrames;
  landMass* home;
  float fed;
  

public:

  maleIndividual(GLfloat bottomLeftX, GLfloat bottomLeftY, GLfloat initialBeakValue);

  void draw();

  void changeDir();

  void move();

  GLfloat getBeakValue();

  int getNumFrames();

  bool checkContact(femaleIndividual f);

  void setHomeland(landMass* h);

  int inHomeland(Point p);

  femaleIndividual makeLadyBaby(femaleIndividual mate);

  maleIndividual makeManBaby(femaleIndividual mate);


  float getFed();

  void getHungry();

  void incFed();
};

#endif
