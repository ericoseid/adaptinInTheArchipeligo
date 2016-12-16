#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <vector>
#include "femaleIndividual.h"
#include "maleIndividual.h"
#include "landMass.h"
using namespace std;

static const GLchar* individualVertexSource =
"#version 330 core\n" 
"layout (location = 0) in vec4 position;\n"
"out vec4 vertexColor;"
"void main(){\n"
"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
"vertexColor = vec4((1.0 - position.w), (1.0 - position.w),(1.0 - position.w), 1.0f);" 
  "}";

static const GLchar* landmassVertexSource =
  "#version 330 core\n"
  "layout (location = 0) in vec4 position;\n"
  "void main(){\n"
  "gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
  "}";

static const GLchar* individualFragmentSource =
"#version 330 core\n"
"in vec4 vertexColor;"
"out vec4 color;\n"
"void main(){\n"
"color = vertexColor; }";

static const GLchar* landmassFragmentSource =
  "#version 330 core\n"
  "out vec4 color;\n"
  "void main(){"
  "color = vec4(0.0f, 1.0f, 0.0f, 1.0f);"
  "}";

void key_callback(GLFWwindow* window, int key, int scancode,
		  int action, int mode){
  if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
}

int initializeGLFW(){
  glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}

int main(){

  initializeGLFW();
  
  GLFWwindow* window = glfwCreateWindow(800, 800, "window", NULL, NULL);
  if(window == NULL){
    cout<<"GLFW is goofy"<<endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetKeyCallback(window, key_callback);

  glewExperimental = GL_TRUE;
  if(glewInit() != GLEW_OK){
    cout<<"GLEW is goofy"<<endl;
  }

  int width, height;
  glfwGetFramebufferSize(window, &width, &height);

  glViewport(0, 0, width, height);

  GLint success;
  GLchar infoLog[512];
  
  GLuint individualVertexShader;
  individualVertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(individualVertexShader, 1, &individualVertexSource, NULL);
  glCompileShader(individualVertexShader);
  glGetShaderiv(individualVertexShader, GL_COMPILE_STATUS, &success);

  if(!success){
    glGetShaderInfoLog(individualVertexShader, 512, NULL, infoLog);
    cout<<infoLog<<endl;
  }

  GLuint individualFragmentShader;
  individualFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(individualFragmentShader, 1, &individualFragmentSource, NULL);
  glCompileShader(individualFragmentShader);
  glGetShaderiv(individualFragmentShader, GL_COMPILE_STATUS, &success);

  if(!success){
    glGetShaderInfoLog(individualFragmentShader, 512, NULL, infoLog);
    cout<<infoLog<<endl;
  }

  GLuint individualShaderProgram;
  individualShaderProgram = glCreateProgram();
  glAttachShader(individualShaderProgram, individualVertexShader);
  glAttachShader(individualShaderProgram, individualFragmentShader);
  glLinkProgram(individualShaderProgram);
  glGetProgramiv(individualShaderProgram, GL_LINK_STATUS, &success);

  if(!success){
    glGetProgramInfoLog(individualShaderProgram, 512, NULL, infoLog);
    cout<<infoLog<<endl;
  }

  glDeleteShader(individualVertexShader);
  glDeleteShader(individualFragmentShader);

  GLuint landmassVertexShader;
  landmassVertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(landmassVertexShader, 1, &landmassVertexSource, NULL);
  glCompileShader(landmassVertexShader);
  glGetShaderiv(landmassVertexShader, GL_COMPILE_STATUS, &success);

  if(!success){
    glGetShaderInfoLog(landmassVertexShader, 512, NULL, infoLog);
    cout<<infoLog<<endl;
  }

  GLuint landmassFragmentShader;
  landmassFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(landmassFragmentShader, 1, &landmassFragmentSource, NULL);
  glCompileShader(landmassFragmentShader);
  glGetShaderiv(landmassFragmentShader, GL_COMPILE_STATUS, &success);

  if(!success){
    glGetShaderInfoLog(landmassFragmentShader, 512, NULL, infoLog);
    cout<<infoLog<<endl;
  }

  GLuint landmassShaderProgram;
  landmassShaderProgram = glCreateProgram();
  glAttachShader(landmassShaderProgram, landmassVertexShader);
  glAttachShader(landmassShaderProgram, landmassFragmentShader);
  glLinkProgram(landmassShaderProgram);
  glGetProgramiv(landmassShaderProgram, GL_LINK_STATUS, &success);

  if(!success){
    glGetProgramInfoLog(landmassShaderProgram, 512, NULL, infoLog);
    cout<<infoLog<<endl;
  }

  glDeleteShader(landmassVertexShader);
  glDeleteShader(landmassFragmentShader);

  landMass origin(0.0f, 0.0f, 0.1875f, 0.125f);
  origin.setFoodVal(0.3f);
  vector<maleIndividual> originMalePop;
  vector<femaleIndividual> originFemPop;
  
  srand(time(NULL));

  GLfloat randBeak;
  GLfloat xVal = 0.0f + .0625f;
  GLfloat yVal = 0.0f + .0625f;
  for(int i = 0; i < 5; i++){
	randBeak = (float)(rand() % 1000 + 1)/(float)1000;
	//give random initial beak value
    maleIndividual temp(xVal, yVal, randBeak);
    temp.setHomeland(&origin);
    originMalePop.push_back(temp);
    yVal -= 0.03;
  }

  yVal = 0.0f + .0625f;
  for(int i = 0; i < 5; i++){
	randBeak = (float)(rand() % 1000 + 1)/(float)1000;
    femaleIndividual temp((-1 * xVal), yVal, randBeak);
    temp.setHomeland(&origin);
    originFemPop.push_back(temp);
    yVal -= 0.05;
  }

  landMass cactusLand(0.5f, 0.5f, 0.1875f, 0.125f);
  cactusLand.setFoodVal(1.0f);
  vector<maleIndividual> cactusMalePop;
  vector<femaleIndividual> cactusFemPop;

  xVal = 0.5f + .0625f;
  yVal = 0.5f + .0625f;
  for(int i = 0; i < 5; i++){
	randBeak = (float)(rand() % 1000 + 1)/(float)1000;
    maleIndividual temp(xVal, yVal, randBeak);
    temp.setHomeland(&cactusLand);
    cactusMalePop.push_back(temp);
    yVal -= 0.03;
  }

  yVal = 0.5f + .0625f;
  for(int i = 0; i < 5; i++){
	randBeak = (float)(rand() % 1000 + 1)/(float)1000;
    femaleIndividual temp((xVal - 0.0625f), yVal, randBeak);
    temp.setHomeland(&cactusLand);
    cactusFemPop.push_back(temp);
    yVal -= 0.05;
  }
  
  landMass flowerLand(0.5f, -0.5f, 0.1875f, 0.125f);
  flowerLand.setFoodVal(0.75f);
  vector<maleIndividual> flowerMalePop;
  vector<femaleIndividual> flowerFemPop;

  xVal = 0.5f + .0625f;
  yVal = -0.5f + .0625f;
  for(int i = 0; i < 5; i++){
	randBeak = (float)(rand() % 1000 + 1)/(float)1000;
    maleIndividual temp(xVal, yVal, randBeak);
    temp.setHomeland(&flowerLand);
    flowerMalePop.push_back(temp);
    yVal -= 0.03;
  }

  yVal =-0.5f + .0625f;
  for(int i = 0; i < 5; i++){
	randBeak = (float)(rand() % 1000 + 1)/(float)1000;
    femaleIndividual temp((xVal - .0625f), yVal, randBeak);
    temp.setHomeland(&flowerLand);
    flowerFemPop.push_back(temp);
    yVal -= 0.05;
  }
  
  landMass nutLand(-0.5f, 0.5f, 0.1875f, 0.125f);
  nutLand.setFoodVal(0.0f);
  vector<maleIndividual> nutMalePop;
  vector<femaleIndividual> nutFemPop;

  xVal = -0.5f + .0625f;
  yVal = 0.5f + .0625f;
  for(int i = 0; i < 5; i++){
	randBeak = (float)(rand() % 1000 + 1)/(float)1000;
    maleIndividual temp(xVal, yVal, randBeak);
    temp.setHomeland(&nutLand);
    nutMalePop.push_back(temp);
    yVal -= 0.03;
  }

  yVal = 0.5f + .0625f;
  for(int i = 0; i < 5; i++){
	randBeak = (float)(rand() % 1000 + 1)/(float)1000;
    femaleIndividual temp((xVal - .0625f), yVal, randBeak);
    temp.setHomeland(&nutLand);
    nutFemPop.push_back(temp);
    yVal -= 0.05;
  }
  
  landMass bugLand(-0.5f, -0.5f, 0.1875f, 0.125f);
  bugLand.setFoodVal(0.5f);
  vector<maleIndividual> bugMalePop;
  vector<femaleIndividual> bugFemPop;

  xVal = -0.5f + .0625f;
  yVal = -0.5f + .0625f;
  for(int i = 0; i < 5; i++){
	randBeak = (float)(rand() % 1000 + 1)/(float)1000;
    maleIndividual temp(xVal, yVal, randBeak);
    temp.setHomeland(&bugLand);
    bugMalePop.push_back(temp);
    yVal -= 0.03;
  }

  yVal = -0.5f + .0625f;
  for(int i = 0; i < 5; i++){
	randBeak = (float)(rand() % 1000 + 1)/(float)1000;
    femaleIndividual temp((xVal - .0625f), yVal, randBeak);
    temp.setHomeland(&bugLand);
    bugFemPop.push_back(temp);
    yVal -= 0.05;
  }

  cout<<originFemPop.size()<<" "<<originMalePop.size()<<endl;
  while(!glfwWindowShouldClose(window)){
    glfwPollEvents();

    glClearColor(0.0f, 0.0f, 1.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(landmassShaderProgram);
    origin.draw();
    nutLand.draw();
    cactusLand.draw();
    flowerLand.draw();
    bugLand.draw();

    glUseProgram(individualShaderProgram);
    for(unsigned int i = 0; i < originFemPop.size(); ++i){
      if(originFemPop[i].getFed() > 0.0f){
	originFemPop[i].draw();
	originFemPop[i].move();
      }
      else{
	originFemPop.erase(originFemPop.begin() + i);
	i--;
      }
    }
    
    for(unsigned int i = 0; i < originMalePop.size(); ++i){
      if(originMalePop[i].getFed() > 0.0f){
	int size = originFemPop.size();
	for(unsigned int j = 0; j < size; ++j){
	  if(originMalePop[i].checkContact(originFemPop[j]) &&
	     originFemPop[j].getFed() >= 1000 &&
	     originMalePop[i].getFed() >= 1000){
	    bool boyGirl = rand() % 2;
	    if(boyGirl){
	      cout<<"new man"<<endl;
	      maleIndividual temp = originMalePop[i].makeManBaby(originFemPop[j]);
	      temp.setHomeland(&origin);
	      originMalePop.push_back(temp);
	    }
	    else{
	      cout<<"new girl"<<endl;
	      femaleIndividual temp = originMalePop[i].makeLadyBaby(originFemPop[j]);

	      temp.setHomeland(&origin);
	      originFemPop.push_back(temp);
	    }
	    originFemPop[j].getHungry();
	    originMalePop[i].getHungry();
	  }
	}
	originMalePop[i].draw();
	originMalePop[i].move();
      }
      else{
	originMalePop.erase(originMalePop.begin() + i);
	i--;
      }
    }

    for(unsigned int i = 0; i < cactusFemPop.size(); ++i){
      if(cactusFemPop[i].getFed() > 0.0f){
	cactusFemPop[i].draw();
	cactusFemPop[i].move();
      }
      else{
	cactusFemPop.erase(cactusFemPop.begin() + i);
	i--;
      }
    }
    
    for(unsigned int i = 0; i < cactusMalePop.size(); ++i){
      if(cactusMalePop[i].getFed() > 0.0f){
	int size = cactusFemPop.size();
	for(unsigned int j = 0; j < size; ++j){
	  if(cactusMalePop[i].checkContact(cactusFemPop[j]) &&
	     cactusFemPop[j].getFed() >= 1000 &&
	     cactusMalePop[i].getFed() >= 1000){
	    bool boyGirl = rand() % 2;
	    if(boyGirl){
	      maleIndividual temp = cactusMalePop[i].makeManBaby(cactusFemPop[j]);
	      temp.setHomeland(&cactusLand);
	      cactusMalePop.push_back(temp);
	    }
	    else{
	      femaleIndividual temp = cactusMalePop[i].makeLadyBaby(cactusFemPop[j]);
	      temp.setHomeland(&cactusLand);
	      cactusFemPop.push_back(temp);
	    }
	    cactusFemPop[j].getHungry();
	    cactusMalePop[i].getHungry();
	  }
	}
	cactusMalePop[i].draw();
	cactusMalePop[i].move();
      }
      else{
	cactusMalePop.erase(cactusMalePop.begin() + i);
	i--;
      }
    }

    for(unsigned int i = 0; i < flowerFemPop.size(); ++i){
      if(flowerFemPop[i].getFed() > 0.0f){
	flowerFemPop[i].draw();
	flowerFemPop[i].move();
      }
      else{
	flowerFemPop.erase(flowerFemPop.begin() + i);
	i--;
      }
    }
    
    for(unsigned int i = 0; i < flowerMalePop.size(); ++i){
      if(flowerMalePop[i].getFed() > 0.0f){
	int size = flowerFemPop.size();
	for(unsigned int j = 0; j < size; ++j){
	  if(flowerMalePop[i].checkContact(flowerFemPop[j]) &&
	     flowerFemPop[j].getFed() >= 1000 &&
	     flowerMalePop[i].getFed() >= 1000){
	    bool boyGirl = rand() % 2;
	    if(boyGirl){
	      maleIndividual temp = flowerMalePop[i].makeManBaby(flowerFemPop[j]);
	      temp.setHomeland(&flowerLand);
	      flowerMalePop.push_back(temp);
	    }
	    else{
	      femaleIndividual temp = flowerMalePop[i].makeLadyBaby(flowerFemPop[j]);
	      temp.setHomeland(&flowerLand);
	      flowerFemPop.push_back(temp);
	    }
	    flowerFemPop[j].getHungry();
	    flowerMalePop[i].getHungry();
	  }
	}
	flowerMalePop[i].draw();
	flowerMalePop[i].move();
      }
      else{
	flowerMalePop.erase(flowerMalePop.begin() + i);
	i--;
      }
    }

    for(unsigned int i = 0; i < nutFemPop.size(); ++i){
      if(nutFemPop[i].getFed() > 0.0f){
	nutFemPop[i].draw();
	nutFemPop[i].move();
      }
      else{
	nutFemPop.erase(nutFemPop.begin() + i);
	i--;
      }
    }
    
    for(unsigned int i = 0; i < nutMalePop.size(); ++i){
      if(nutMalePop[i].getFed() > 0.0f){
	int size = nutFemPop.size();
	for(unsigned int j = 0; j < size; ++j){
	  if(nutMalePop[i].checkContact(nutFemPop[j]) &&
	     nutFemPop[j].getFed() >= 1000 &&
	     nutMalePop[i].getFed() >= 1000){
	    bool boyGirl = rand() % 2;
	    if(boyGirl){
	      maleIndividual temp = nutMalePop[i].makeManBaby(nutFemPop[j]);
	      temp.setHomeland(&nutLand);
	      nutMalePop.push_back(temp);
	    }
	    else{
	      femaleIndividual temp = nutMalePop[i].makeLadyBaby(nutFemPop[j]);
	      temp.setHomeland(&nutLand);
	      nutFemPop.push_back(temp);
	    }
	    nutFemPop[j].getHungry();
	    nutMalePop[i].getHungry();
	  }
	}
	nutMalePop[i].draw();
	nutMalePop[i].move();
      }
      else{
	nutMalePop.erase(nutMalePop.begin() + i);
	i--;
      }
    }

    for(unsigned int i = 0; i < bugFemPop.size(); ++i){
      if(bugFemPop[i].getFed() > 0.0f){
	bugFemPop[i].draw();
	bugFemPop[i].move();
      }
      else{
	bugFemPop.erase(bugFemPop.begin() + i);
	i--;
      }
    }
    
    for(unsigned int i = 0; i < bugMalePop.size(); ++i){
      if(bugMalePop[i].getFed() > 0.0f){
	int size = bugFemPop.size();
	for(unsigned int j = 0; j < size; ++j){
	  if(bugMalePop[i].checkContact(bugFemPop[j]) &&
	     bugFemPop[j].getFed() >= 1000 &&
	     bugMalePop[i].getFed() >= 1000){
	    bool boyGirl = rand() % 2;
	    if(boyGirl){
	      maleIndividual temp = bugMalePop[i].makeManBaby(bugFemPop[j]);
	      temp.setHomeland(&bugLand);
	      bugMalePop.push_back(temp);
	    }
	    else{
	      femaleIndividual temp = bugMalePop[i].makeLadyBaby(bugFemPop[j]);
	      temp.setHomeland(&bugLand);
	      bugFemPop.push_back(temp);
	    }
	    bugFemPop[j].getHungry();
	    bugMalePop[i].getHungry();
	  }
	}
	bugMalePop[i].draw();
	bugMalePop[i].move();
      }
      else{
	bugMalePop.erase(bugMalePop.begin() + i);
	i--;
      }
    }

    glfwSwapBuffers(window);
  }
  
  glfwTerminate();
}
