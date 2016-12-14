#include "landMass.h"

landMass::landMass(GLfloat centerX, GLfloat centerY,
		   GLfloat distToVert, GLfloat distToEdge){
  cX = centerX;
  cY = centerY;
  vertDist = distToVert;
  edgeDist = distToEdge;

  GLfloat b;
  b = sqrt(((vertDist * vertDist) - (edgeDist * edgeDist)));

  //vertex one
  vertices[0] = cX - b;
  vertices[1] = cY - edgeDist;
  vertices[2] = 1.0f;
  //vertex two
  vertices[3] = cX + b;
  vertices[4] = cY - edgeDist;
  vertices[5] = 1.0f;
  //vertex three
  vertices[6] = cX - vertDist;
  vertices[7] = cY;
  vertices[8] = 1.0f;
  //vertex four
  vertices[9] = cX + vertDist;
  vertices[10] = cY;
  vertices[11] = 1.0f;
  //vertex five
  vertices[12] = cX - b;
  vertices[13] = cY + edgeDist;
  vertices[14] = 1.0f;
  //vertex six
  vertices[15] = cX + b;
  vertices[16] = cY + edgeDist;
  vertices[17] = 1.0f;

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
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);
  glBindVertexArray(0);
}

float landMass::getFoodVal(){
  return foodVal;
}

void landMass::setFoodVal(float newVal){
  foodVal = newVal;
}
