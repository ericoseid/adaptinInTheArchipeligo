#include "maleIndividual.h"

maleIndividual::maleIndividual(GLfloat bottomLeftX, GLfloat bottomLeftY, GLfloat initialBeakValue){
  fed = 2000;
  beakValue = initialBeakValue;
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
  Point center(this->vertices[0]+.01f, this->vertices[1]+.01f);
  
  if (rand() % 10 + 1==4) changeDir();
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
  
  int num = inHomeland(center);

  if(num == 1){
    vertices[1] -= .02;
    vertices[5] -= .02;
    vertices[9] -= .02;
    vertices[13] -= .02;
    vertices[0] -= .02;
    vertices[4] -= .02;
    vertices[8] -= .02;
    vertices[12] -= .02;
  }
  else if(num == 2){
   vertices[0] -= .02;
   vertices[4] -= .02;
   vertices[8] -= .02;
   vertices[12] -= .02; 
  }
  else if(num == 3){
    vertices[1] += .02;
    vertices[5] += .02;
    vertices[9] += .02;
    vertices[13] += .02;
    vertices[0] -= .02;
    vertices[4] -= .02;
    vertices[8] -= .02;
    vertices[12] -= .02;
  }
  else if(num == 4){
    vertices[1] += .02;
    vertices[5] += .02;
    vertices[9] += .02;
    vertices[13] += .02;
  }
  else if(num == 5){
    vertices[1] += .02;
    vertices[5] += .02;
    vertices[9] += .02;
    vertices[13] += .02;
    vertices[0] += .02;
    vertices[4] += .02;
    vertices[8] += .02;
    vertices[12] += .02;
  }
  else if(num == 6){
    vertices[0] += .02;
    vertices[4] += .02;
    vertices[8] += .02;
    vertices[12] += .02;
  }
  else if(num == 7){
    vertices[1] -= .02;
    vertices[5] -= .02;
    vertices[9] -= .02;
    vertices[13] -= .02;
    vertices[0] += .02;
    vertices[4] += .02;
    vertices[8] += .02;
    vertices[12] += .02; 
  }
  else if(num == 8){
    vertices[1] -= .02;
    vertices[5] -= .02;
    vertices[9] -= .02;
    vertices[13] -= .02;
  }
  
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat),
			(GLvoid*) 0);
  glEnableVertexAttribArray(0);
  glBindVertexArray(0);
  fed -= 1;
  fed += .05/.01+(beakValue-home->getFoodVal())*(beakValue-home->getFoodVal());
}

int maleIndividual::getNumFrames(){
  return numFrames;
}

bool maleIndividual::checkContact(femaleIndividual f){
  vector<GLfloat> fVerts = f.getVertices();

  Point center( (this->vertices[0] + .01), (this->vertices[1] + .01) );

  Point vert1(fVerts[0], fVerts[1]);

  if(center.x > vert1.x && center.x < (vert1.x + .02) &&
     center.y > vert1.y && center.y < (vert1.y + .02))
    return true;
  else
    return false;
}

void maleIndividual::setHomeland(landMass* h){
  home = h;
}

GLfloat maleIndividual::getBeakValue(){
	return beakValue;
}
int maleIndividual::inHomeland(Point p){
  vector<GLfloat> homeVerts = home->getVerts();
  
  Point one(homeVerts[0], homeVerts[1]);
  
  return isInSquare(p, one, 0.125f * 2.0f); 
}
float maleIndividual::getFed(){
  return fed;
}

void maleIndividual::getHungry(){
  fed -=1500;
}

femaleIndividual maleIndividual::makeLadyBaby(femaleIndividual mate){
  femaleIndividual res(this->vertices[0] + .03, this->vertices[1], (beakValue+mate.getBeakValue())/2);

  return res;
}

maleIndividual maleIndividual::makeManBaby(femaleIndividual mate){
  maleIndividual res(this->vertices[0] + .03, this->vertices[1], (beakValue+mate.getBeakValue())/2);

  return res;
}

void maleIndividual::incFed(){
	if (fed < 500) fed+=5;
}
