#include "glad/glad.h"
#include "GLFW/glfw3.h"

void framebuff_size_callback(GLFWwindow *pWwindow, const int width, const int height);

int getProgram(GLFWwindow *pWwindow, const char* vertexShaderSource, const char* fragmentShaderSource);