#include <glad.h>
#include <glfw3.h>

#include <iostream>

void initProcedure(unsigned int major_version, int minor_version)
{
   glfwInit();
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major_version); // Specifies use of OpenGL major version 3
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor_version); // Specifies use of OpengGL minor version 3 (In this case 3.3)
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Specifies version of OpenGL --> CORE (Compatability is older functions)
}

void terminatingProcedure(GLFWwindow* window)
{
   glfwDestroyWindow(window);
   glfwTerminate();
}