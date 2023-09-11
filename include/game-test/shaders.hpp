#pragma once




typedef struct shader_s{
  unsigned int program;
  unsigned int vs;
  unsigned int fs;
} shader_t;



shader_t CreateShader(const char* vertexShaderPath, const char* fragmentShaderPath);
void DestroyShader(shader_t* shader);
void UseShader(shader_t* shader);


void loadShaderSource(const char* fileName, char* shaderBuffer, int len);

