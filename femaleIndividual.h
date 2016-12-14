#ifndef _femaleIndividual_
#define _femaleIndividual_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdlib>

class femaleIndividual{
  GLfloat vertices[12];
  GLuint VAO;
  GLuint VBO;
  int dir;
  GLfloat beakValue;
  int numFrames;
  int fed;

 public:

  femaleIndividual(GLfloat bottomLeftX, GLfloat bottomLeftY);

  void draw();

  void changeDir();

  void move();

  int getNumFrames();

  GLfloat* getVertices();

  int getFed();

  void getHungry();
};

#endif
