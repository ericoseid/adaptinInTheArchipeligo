#include "geometry.h"

Point::Point(GLfloat xCor, GLfloat yCor){
  x = xCor;
  y = yCor;
}

int isInSquare(Point p, Point bLeft, float s){
  if(p.x > (bLeft.x + s) && p.y > (bLeft.y + s)){
    return 1;
  }
  else if(p.x > (bLeft.x + s) && p.y > bLeft.y && p.y < (bLeft.y + s)){
    return 2;
  }
  else if(p.x > (bLeft.x + s) && p.y < (bLeft.y)){
    return 3;
  }
  else if(p.x > bLeft.x && p.x < (bLeft.x + s) && p.y < bLeft.y){
    return 4;
  }
  else if(p.x < bLeft.x && p.y < bLeft.y){
    return 5;
  }
  else if(p.x < bLeft.x && p.y > bLeft.y && p.y < (bLeft.y + s)){
    return 6;
  }
  else if(p.x < bLeft.x && p.y > (bLeft.y + s)){
    return 7;
  }
  else if(p.x > bLeft.x && p.x < (bLeft.x + s) && p.y > (bLeft.y+s)){
    return 8;
  }
  else{
    return 0;
  }
}
