#include "maleIndividual.h"

struct Point{
  float x;
  float y;

  Point(float xCor, float yCor){
    x = xCor;
    y = yCor;
  }
};

float Sign(Point p1, Point p2, Point p3){
  return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x -p3.x) * (p1.y - p3.y);
}

bool isInTriang(Point p, Point v1, Point v2, Point v3){
  bool b1, b2, b3;

  b1 = Sign(p, v1, v2) < 0.0f;
  b2 = Sign(p, v2, v3) < 0.0f;
  b3 = Sign(p, v3, v1) < 0.0f;

  return ((b1 == b2) && (b2 == b3));
}
  

maleIndividual::maleIndividual(GLfloat bottomLeftX, GLfloat bottomLeftY){
  beakValue = 0.0;
  numFrames = 0;
  dir = 0;
  
  vertices[0] = bottomLeftX; 
  vertices[1] = bottomLeftY;
  vertices[2] = 0.0f;
  vertices[3] = beakValue;
  vertices[4] = bottomLeftX + .02;
  vertices[5] = bottomLeftY;
  vertices[6] = 0.0f;
  vertices[7] = beakValue;
  vertices[8] = bottomLeftX;
  vertices[9] = bottomLeftY + .02;
  vertices[10] = 0.0f;
  vertices[11] = beakValue;
  vertices[12] = bottomLeftX + .02;
  vertices[13] = bottomLeftY + .02;
  vertices[14] = 0.0f;
  vertices[15] = beakValue;
  
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat),
			(GLvoid*) 0);
  glEnableVertexAttribArray(0);
  glBindVertexArray(0);
}

void maleIndividual::draw(){
  glBindVertexArray(VAO);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  glBindVertexArray(0);
  
  numFrames++;
}

void maleIndividual::changeDir(){
  bool willChange = (rand() % 2) != 0;
  if(willChange){
    int newDir = rand() % 9;
    if(newDir == 0)
      dir = 0;
    else if(newDir == 1)
      dir = 1;
    else if(newDir == 2)
      dir = 2;
    else if(newDir == 3)
      dir = 3;
    else if(newDir == 4)
      dir = 4;
    else if(newDir == 5)
      dir = 5;
    else if(newDir == 6)
      dir = 6;
    else if(newDir == 7)
      dir = 7;
    else
      dir = 8;
  }
}

void maleIndividual::move(){
  changeDir();
  if(dir == 0){
  }
  else if(dir == 1){
    vertices[0] += .002;
    vertices[4] += .002;
    vertices[8] += .002;
    vertices[12] += .002;
  }
  else if(dir == 2){
    vertices[1] += .002;
    vertices[5] += .002;
    vertices[9] += .002;
    vertices[13] += .002;
    vertices[0] += .002;
    vertices[4] += .002;
    vertices[8] += .002;
    vertices[12] += .002;
  }
  else if(dir == 3){
    vertices[1] += .002;
    vertices[5] += .002;
    vertices[9] += .002;
    vertices[13] += .002;
  }
  else if(dir == 4){
    vertices[1] += .002;
    vertices[5] += .002;
    vertices[9] += .002;
    vertices[13] += .002;
    vertices[0] -= .002;
    vertices[4] -= .002;
    vertices[8] -= .002;
    vertices[12] -= .002;
  }
  else if(dir == 5){
    vertices[0] -= .002;
    vertices[4] -= .002;
    vertices[8] -= .002;
    vertices[12] -= .002;
  }
  else if(dir == 6){
    vertices[1] -= .002;
    vertices[5] -= .002;
    vertices[9] -= .002;
    vertices[13] -= .002;
    vertices[0] -= .002;
    vertices[4] -= .002;
    vertices[8] -= .002;
    vertices[12] -= .002;
  }
  else if(dir == 7){
    vertices[1] -= .002;
    vertices[5] -= .002;
    vertices[9] -= .002;
    vertices[13] -= .002;
  }
  else{
    vertices[0] += .002;
    vertices[4] += .002;
    vertices[8] += .002;
    vertices[12] += .002;
    vertices[1] -= .002;
    vertices[5] -= .002;
    vertices[9] -= .002;
    vertices[13] -= .002;
  }
  
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat),
			(GLvoid*) 0);
  glEnableVertexAttribArray(0);
  glBindVertexArray(0);
  numFrames++;
}

int maleIndividual::getNumFrames(){
  return numFrames;
}

bool maleIndividual::checkContact(femaleIndividual f){
  GLfloat* fVerts = f.getVertices();

  Point center( (this->vertices[0] + .01), (this->vertices[1] + .01) );

  Point vert1(fVerts[0], fVerts[1]);
  Point vert2(fVerts[2], fVerts[3]);
  Point vert3(fVerts[4], fVerts[5]);
 
  return isInTriang(center, vert1, vert2, vert3);
}

femaleIndividual maleIndividual::makeLadyBaby(){
  femaleIndividual res(this->vertices[0] + .03, this->vertices[1]);

  return res;
}

maleIndividual maleIndividual::makeManBaby(){
  cout<<"fuck off"<<endl;
  maleIndividual res(this->vertices[0] + .03, this->vertices[1]);

  return res;
}
