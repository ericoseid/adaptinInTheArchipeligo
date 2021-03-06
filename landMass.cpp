#include "landMass.h"

landMass::landMass(GLfloat centerX, GLfloat centerY,
		   GLfloat distToVert, GLfloat distToEdge){
  cX = centerX;
  cY = centerY;
  vertDist = distToVert;
  edgeDist = distToEdge;

  //vertex one
  vertices[0] = cX - edgeDist;
  vertices[1] = cY - edgeDist;
  vertices[2] = 1.0f;
  //vertex two
  vertices[3] = cX + edgeDist;
  vertices[4] = cY - edgeDist;
  vertices[5] = 1.0f;
  //vertex three
  vertices[6] = cX - edgeDist;
  vertices[7] = cY + edgeDist;
  vertices[8] = 1.0f;
  //vertex four
  vertices[9] = cX + edgeDist;
  vertices[10] = cY + edgeDist;
  vertices[11] = 1.0f;

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
			(GLvoid*) 0);

  glEnableVertexAttribArray(0);
  glBindVertexArray(0);
}

void landMass::draw(){
  glBindVertexArray(VAO);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  glBindVertexArray(0);
}

float landMass::getFoodVal(){
  return foodVal;
}

void landMass::setFoodVal(float newVal){
  foodVal = newVal;
}

vector<GLfloat> landMass::getVerts(){
  vector<GLfloat> verts;
  
  verts.push_back(this->vertices[0]);
  verts.push_back(this->vertices[1]);
  verts.push_back(this->vertices[3]);
  verts.push_back(this->vertices[4]);
  verts.push_back(this->vertices[6]);
  verts.push_back(this->vertices[7]);
  verts.push_back(this->vertices[9]);
  verts.push_back(this->vertices[10]);

  return verts;
}
