#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <vector>
#include "maleIndividual.h"
#include "femaleIndividual.h"
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
  
  landMass cactusLand(0.5f, 0.5f, 0.1875f, 0.125f);
  cactusLand.setFoodVal(1.0f);
  
  landMass flowerLand(0.5f, -0.5f, 0.1875f, 0.125f);
  flowerLand.setFoodVal(0.75f);
  
  landMass nutLand(-0.5f, 0.5f, 0.1875f, 0.125f);
  nutLand.setFoodVal(0.0f);
  
  landMass bugLand(-0.5f, -0.5f, 0.1875f, 0.125f);
  bugLand.setFoodVal(0.5f);
  
  GLfloat xVal = .0625;
  GLfloat yVal = .0625;
  vector<maleIndividual> malePopulation;
  for(int i = 0; i < 5; i++){
    maleIndividual temp(xVal, yVal);
    malePopulation.push_back(temp);
    yVal -= 0.05;
  }

  yVal = .0625;
  vector<femaleIndividual> femalePopulation;
  for(int i = 0; i < 5; i++){
    femaleIndividual temp((-1 * xVal), yVal);
    femalePopulation.push_back(temp);
    yVal -= 0.05;
  }
  
  srand(time(NULL));
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
    for(unsigned int i = 0; i < femalePopulation.size(); ++i){
      if(femalePopulation[i].getNumFrames() < 2000){
	femalePopulation[i].draw();
	femalePopulation[i].move();
      }
      else{
	femalePopulation.erase(femalePopulation.begin() + i);
	i--;
      }
    }
    
    for(unsigned int i = 0; i < malePopulation.size(); ++i){
      if(malePopulation[i].getNumFrames() < 2000){
	int size = femalePopulation.size();
	for(unsigned int j = 0; j < size; ++j){
	  if(malePopulation[i].checkContact(femalePopulation[j]) &&
	     femalePopulation[j].getFed() == 500){
	    bool boyGirl = rand() % 2;
	    if(boyGirl){
	      maleIndividual temp = malePopulation[i].makeManBaby();
	      malePopulation.push_back(temp);
	    }
	    else{
	      femaleIndividual temp = malePopulation[i].makeLadyBaby();
	      femalePopulation.push_back(temp);
	    }
	    femalePopulation[j].getHungry();
	  }
	}
	malePopulation[i].draw();
	malePopulation[i].move();
      }
      else{
	malePopulation.erase(malePopulation.begin() + i);
	i--;
      }
    }

    glfwSwapBuffers(window);
  }
  
  glfwTerminate();
}
