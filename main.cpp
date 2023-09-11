#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <string>
#include <stdio.h>

#define FRAGMENT_SHADER_PATH "shaders/fragment/"
#define VERTEX_SHADER_PATH "shaders/vertex/"
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define FILE_READ_BUFFER_SIZE 4096

using std::string;
using std::cout;
using std::endl;



static void CheckShaderCompileStatus(unsigned int shader){
  int success;
  char infoLog[512];
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if(!success){
    glGetShaderInfoLog(shader, 512, NULL, infoLog);
    printf("Error: Shader compilation failed: %s\n", infoLog);
  }
}
static int CreateShader(char *vertexShader,char *fragmentShader){
  const GLchar* vertexShaderSource = vertexShader;
  const GLchar* fragmentShaderSource = fragmentShader;




  unsigned int program = glCreateProgram();
  unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
  unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);

  glShaderSource(vs, 1, &vertexShaderSource, NULL);
  glShaderSource(fs, 1, &fragmentShaderSource, NULL);

  glCompileShader(vs);
  glCompileShader(fs);
  
  cout << "Checking Vertex Shader: " << endl;
  CheckShaderCompileStatus(vs);
  cout << "Checking Fragment Shader: " << endl;
  CheckShaderCompileStatus(fs);

  glAttachShader(program, vs);
  glAttachShader(program, fs);

  glLinkProgram(program);
  glValidateProgram(program);

  glDeleteShader(vs);
  glDeleteShader(fs);


  return program;
}
void loadShaderFile(string shaderPath, char** buffer){
  FILE* shaderFile = fopen(shaderPath.c_str(), "r");
  if(!shaderFile){
    printf("Error: Could not open shader file: %s\n", shaderPath.c_str());
    return;
  }

  fseek(shaderFile, 0, SEEK_END);
  long fileSize = ftell(shaderFile);
  fseek(shaderFile, 0, SEEK_SET);

  *buffer = (char*)malloc(fileSize + 1);
  fread(*buffer, 1, fileSize, shaderFile);
  printf("Shader File after read: %s\n", *buffer);
  fclose(shaderFile);
  //Null terminate the buffer
  //(*buffer)[fileSize] = 0;
}

int main(){


  if(!glfwInit()){
    return -1;
  }


  GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello World", NULL, NULL);

  if(!window){
    cout << "Error: Welp, we couldn't make a window, did you try turning it off an back on again!\n" << endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
    printf("Failed to start GLAD, are you even trying\n");
    return -1;

  }
  
  //Loads shaders to the gpu
  




  printf("OpenGL Version: %s\n", glGetString(GL_VERSION));

  float vertices[] = {
    -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f, 1.0f, 0.5f, 0.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.5f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.5f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.5f, 0.0f,
    -0.5f,  0.5f,  0.5f, 1.0f, 0.5f, 0.0f,
    -0.5f, -0.5f,  0.5f, 1.0f, 0.5f, 0.0f,

    -0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 1.0f,

    0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 0.5f,
    0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.5f,
    0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.5f,
    0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.5f,
    0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 0.5f,
    0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 0.5f,

    -0.5f, -0.5f, -0.5f, 1.0f, 0.5f, 1.0f,
    0.5f, -0.5f, -0.5f,  1.0f, 0.5f, 1.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.5f, 1.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.5f, 1.0f,
    -0.5f, -0.5f,  0.5f, 1.0f, 0.5f, 1.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 0.5f, 1.0f,

    -0.5f,  0.5f, -0.5f, 1.0f, 0.5f, 0.5f,
    0.5f,  0.5f, -0.5f,  1.0f, 0.5f, 0.5f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.5f, 0.5f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.5f, 0.5f,
    -0.5f,  0.5f,  0.5f, 1.0f, 0.5f, 0.5f,
    -0.5f,  0.5f, -0.5f, 1.0f, 0.5f, 0.5f
  };
  char* vertexShaderSource = NULL;
  char* fragmentShaderSource = NULL;
  string vertexShaderPath = "shaders/vertex/basic.vert";
  string fragmentShaderPath = "shaders/fragment/basic.frag";



  loadShaderFile(vertexShaderPath, &vertexShaderSource);
  loadShaderFile(fragmentShaderPath, &fragmentShaderSource);

  cout << "Vertex Shader Source: " << vertexShaderSource << endl;
  cout << "Fragment Shader Source: " << fragmentShaderSource << endl;

  unsigned int shaderProgram = CreateShader(vertexShaderSource, fragmentShaderSource);


  unsigned int VBO, VAO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  //Position Attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);


  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  while(!glfwWindowShouldClose(window)){
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);




    glUseProgram(shaderProgram);

    //Rotate cube around x axis using glm 

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, (float)glfwGetTime() * glm::radians(5.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);

    unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");
    unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
    unsigned int projectionLoc = glGetUniformLocation(shaderProgram, "projection");


    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));


    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);


    glfwSwapBuffers(window);
    glfwPollEvents();
  }


  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
