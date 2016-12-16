#include "femaleIndividual.h"

femaleIndividual::femaleIndividual(GLfloat bottomLeftX, GLfloat bottomLeftY, GLfloat initialBeakValue){
  beakValue = initialBeakValue;
  numFrames = 0;
  dir = 0;
  fed = 500;

  vertices[0] = bottomLeftX; 
  vertices[1] = bottomLeftY;
  vertices[2] = 0.0f;
  vertices[3] = beakValue;
  vertices[4] = bottomLeftX + .02;
  vertices[5] = bottomLeftY;
  vertices[6] = 0.0f;
  vertices[7] = beakValue;
  vertices[8] = bottomLeftX + .01;
  vertices[9] = bottomLeftY + .015;
  vertices[10] = 0.0f;
  vertices[11] = beakValue;

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

void femaleIndividual::draw(){
  glBindVertexArray(VAO);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 3);
  glBindVertexArray(0);
  
  numFrames++;
}

void femaleIndividual::changeDir(){
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

void femaleIndividual::move(){
  Point center(this->vertices[0]+.01f, this->vertices[1]+.01f);
  
  changeDir();
  if(dir == 0){
  }
  else if(dir == 1){
    vertices[0] += .002;
    vertices[4] += .002;
    vertices[8] += .002;
  }
  else if(dir == 2){
    vertices[1] += .002;
    vertices[5] += .002;
    vertices[9] += .002;
    vertices[0] += .002;
    vertices[4] += .002;
    vertices[8] += .002;
  }
  else if(dir == 3){
    vertices[1] += .002;
    vertices[5] += .002;
    vertices[9] += .002;
  }
  else if(dir == 4){
    vertices[1] += .002;
    vertices[5] += .002;
    vertices[9] += .002;
    vertices[0] -= .002;
    vertices[4] -= .002;
    vertices[8] -= .002;
  }
  else if(dir == 5){
    vertices[0] -= .002;
    vertices[4] -= .002;
    vertices[8] -= .002;
  }
  else if(dir == 6){
    vertices[1] -= .002;
    vertices[5] -= .002;
    vertices[9] -= .002;
    vertices[0] -= .002;
    vertices[4] -= .002;
    vertices[8] -= .002;
  }
  else if(dir == 7){
    vertices[1] -= .002;
    vertices[5] -= .002;
    vertices[9] -= .002;
  }
  else{
    vertices[0] += .002;
    vertices[4] += .002;
    vertices[8] += .002;
    vertices[1] -= .002;
    vertices[5] -= .002;
    vertices[9] -= .002;
  }

  int num = inHomeland(center);

  if(num == 1){
    vertices[1] -= .02;
    vertices[5] -= .02;
    vertices[9] -= .02;
    vertices[0] -= .02;
    vertices[4] -= .02;
    vertices[8] -= .02;
  }
  else if(num == 2){
   vertices[0] -= .02;
   vertices[4] -= .02;
   vertices[8] -= .02;
  }
  else if(num == 3){
    vertices[1] += .02;
    vertices[5] += .02;
    vertices[9] += .02;
    vertices[0] -= .02;
    vertices[4] -= .02;
    vertices[8] -= .02;
  }
  else if(num == 4){
    vertices[1] += .02;
    vertices[5] += .02;
    vertices[9] += .02;
  }
  else if(num == 5){
    vertices[1] += .02;
    vertices[5] += .02;
    vertices[9] += .02;
    vertices[0] += .02;
    vertices[4] += .02;
    vertices[8] += .02;
  }
  else if(num == 6){
    vertices[0] += .02;
    vertices[4] += .02;
    vertices[8] += .02;
  }
  else if(num == 7){
    vertices[1] -= .02;
    vertices[5] -= .02;
    vertices[9] -= .02;
    vertices[0] += .02;
    vertices[4] += .02;
    vertices[8] += .02;
  }
  else if(num == 8){
    vertices[1] -= .02;
    vertices[5] -= .02;
    vertices[9] -= .02;
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

int femaleIndividual::getNumFrames(){
  return numFrames;
}

vector<GLfloat> femaleIndividual::getVertices(){
  vector<GLfloat> retVerts;

  retVerts.push_back(this->vertices[0]);
  retVerts.push_back(this->vertices[1]);
  retVerts.push_back(this->vertices[4]);
  retVerts.push_back(this->vertices[5]);
  retVerts.push_back(this->vertices[8]);
  retVerts.push_back(this->vertices[9]);

  return retVerts;
  
}

int femaleIndividual::getFed(){
  return fed;
}

void femaleIndividual::getHungry(){
  fed = 0;
}

void femaleIndividual::setHomeland(landMass* h){
  home = h;
}

int femaleIndividual::inHomeland(Point p){
  vector<GLfloat> homeVerts = home->getVerts();
  
  Point one(homeVerts[0], homeVerts[1]);
  
  return isInSquare(p, one, 0.125f * 2.0f); 
}

GLfloat femaleIndividual::getBeakValue(){
	return beakValue;
}
