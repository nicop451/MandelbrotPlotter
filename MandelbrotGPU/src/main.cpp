#include <iostream>
#include <chrono>
#include "ConcisionFuncs.hpp"

#include <glad.h>
#include <glfw3.h>


const unsigned int win_Width = 1920;
const unsigned int win_Height = 1080;
const float shiftSpeed = 180;
const float scaleSpeed = 1;


/// SHADERS **
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"  gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform float scale;\n"
"uniform float shift_x;\n"
"uniform float shift_y;\n"
"uniform float NormallyTwo;"
"void main()\n"
"{\n"
"   int maxIterations = 10000;" 

"   float a = ((gl_FragCoord.x - 964) * scale) + shift_x;"
"   float b = (((gl_FragCoord.y - 540) * scale) + shift_y)*-1;"

"   float Ca = a;"
"   float Cb = b;"

"   int n = 0;\n"
"   while(n < maxIterations)\n"
"   {\n"
"      float ZnSqr_a = abs(a*a - b*b);"
"      float ZnSqr_b = abs(NormallyTwo * a * b);"

"      a = ZnSqr_a + Ca + sqrt(ZnSqr_a);"
"      b = ZnSqr_b + Cb - sqrt(ZnSqr_b);"
"      if(a*a+b*b > 16)"
       "break;"
"      n++;"
   "}"
"   float bright = n * 0.001;"
"   float gradient_r = mod(sqrt(float(n*10)) , maxIterations);"
"   float gradient_g = 1/gradient_r;"
"   float gradient_b = sin(sqrt(float(n*0.1)));"
"   if(n == maxIterations)"
"   {"
"      bright = 0;"
"   }"
"  FragColor = vec4(bright * 20, bright * 20, bright * 30, 1.0f);"
"}\n\0";
//------------------------


void Zoom_Pan(GLFWwindow* window, float &scale, float &shift_x, float &shift_y, float &deltaTime, float &temp)
{
   int pageUp = glfwGetKey(window, GLFW_KEY_PAGE_UP);
   int pageDown = glfwGetKey(window, GLFW_KEY_PAGE_DOWN);

   int arrowUp = glfwGetKey(window, GLFW_KEY_UP);
   int arrowDown = glfwGetKey(window, GLFW_KEY_DOWN);
   int arrowLeft = glfwGetKey(window, GLFW_KEY_LEFT);
   int arrowRight = glfwGetKey(window, GLFW_KEY_RIGHT);

   int temp_key = glfwGetKey(window, GLFW_KEY_H);

   if(pageUp == GLFW_REPEAT || pageUp == GLFW_PRESS)
   {
      scale *= 1 - scaleSpeed * deltaTime;
   }

   if(pageDown == GLFW_REPEAT || pageDown == GLFW_PRESS)
   {
      scale *= 1 + scaleSpeed * 2 * deltaTime;
   }

   if(arrowLeft == GLFW_REPEAT || arrowLeft == GLFW_PRESS)
   {
      shift_x += -shiftSpeed * scale * deltaTime;
   }

   if(arrowRight == GLFW_REPEAT || arrowRight == GLFW_PRESS)
   {
      shift_x += shiftSpeed * scale * deltaTime;
   }

   if(arrowDown == GLFW_REPEAT || arrowDown == GLFW_PRESS)
   {
      shift_y += -shiftSpeed * scale * deltaTime;
   }

   if(arrowUp == GLFW_REPEAT || arrowUp == GLFW_PRESS)
   {
      shift_y += shiftSpeed * scale * deltaTime;
   }

   if(temp_key == GLFW_REPEAT || temp_key == GLFW_PRESS)
   {
      temp *= 1.0001;
      std::cout << "sup" << std::endl;
   }

}

int main()
{
   // Initialize glfw
   initProcedure(3,3);

   // Vertex Array defines positions
   float vertices[] = 
   {
   //    x      y      z   
     -1.0f, -1.0f, 0.0f, // Bottom Left 0
      1.0f,  1.0f, 0.0f, // Top Right 1
     -1.0f,  1.0f, 0.0f, // Top Left 2
      1.0f, -1.0f, 0.0f // Bottom Right 3 
   };
   //Indices Array defines triangle connections
   unsigned int indices[] = 
   {
      0, 1, 2, // First Triangle
      0, 3, 1, // Second Triangle
   };

   float scale = 0.003;
   float temp = 2;
   float shift_x = 0;
   float shift_y = 0;


   // TIME
   auto startTime = std::chrono::system_clock::now();

   GLFWmonitor* monitor = glfwGetPrimaryMonitor();
   const GLFWvidmode* mode = glfwGetVideoMode(monitor);

   // Window Creation
   GLFWwindow* window = glfwCreateWindow(win_Width, win_Height, "Fullscreen Window", monitor, NULL);
   if(window == NULL) // Error Checking for glfw window
   { 
      std::cout << "Couldn't create GLFW window!" << std::endl;
      glfwTerminate();
      return -1;
   }  
   glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_FALSE);
   glfwMakeContextCurrent(window);

   // Initialize OpenGL through glad and set background color
   gladLoadGL(); // Loads OpenGL functions through glad and I think intializes context
   glViewport(0, 0, win_Width, win_Height);
   glClearColor(0.1f, 0.15f, 0.3f, 1);


   // Shader stuff
   unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER); // Brings vertex shader into context and set our variable vertexShader as the reference to it
   glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); // Transfer shader code to OpenGL GL_VERTEX_SHADER which is binded to vertexShader
   glCompileShader(vertexShader); // Compile shader into GPU language

   unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); // Brings fragment shader into context and set our variable fragmentShader as the reference to it
   glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL); // Transfer shader code to OpenGL GL_FRAGMENT_SHADER which is binded to fragmentShader
   glCompileShader(fragmentShader);

   unsigned int shaderProgram = glCreateProgram(); // Create GL shader program that packages shaders into one program
   glAttachShader(shaderProgram, vertexShader); // Attaches vertexShader to shaderProgram
   glAttachShader(shaderProgram, fragmentShader); // Attaches fragmentShader to shaderProgram
   glLinkProgram(shaderProgram); // Bring it into current context

   // Delete shader references they are useless
   glDeleteShader(vertexShader);
   glDeleteShader(fragmentShader);

   // BUFFER OBJECTS - Generation, Binding and Unbinding 
   unsigned int VAO, VBO, EBO; // Declare Vertex Buffer Object, Vertex Array Object, Element Buffer Object
   glGenVertexArrays(1, &VAO); // Generate Vertex Array Object in the context and sets the VAO variable to the name of the Vertex Array Object in the context
   glGenBuffers(1, &VBO);
   glGenBuffers(1, &EBO);

   glBindVertexArray(VAO); // Binds our variable to the current OpenGL context's Vertex Array Object which is a space in memory

   glBindBuffer(GL_ARRAY_BUFFER, VBO); // Binds Vertex Buffer Object in context to VBO variable and VBO now identifys the VBO in the context
   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // Intializes Vertex Buffer Object in context and sends vertices data to it and tell GL that vertices are not gonna be changed often

   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); // Binds Element Buffer Object to our variable EBO and 
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); // Creates data store for Element Buffer Object and adds indeces data to that store

   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // This specifies the format of the vertex data in the Vertex Buffer Object
   glEnableVertexAttribArray(0); // Enables the above defined format so OpenGL knows to use it
   

   // Clean Up unbind Buffers and Array objects
   glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind VB0 to avoid modifications
   glBindVertexArray(0); // Unbind VAO to avoid modifications
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


   // Program Loop....................................
   while(!glfwWindowShouldClose(window))
   {

      auto currentTime = std::chrono::system_clock::now();
      std::chrono::duration<float> deltaTimeRaw = currentTime - startTime;
      float deltaTime = deltaTimeRaw.count();

      Zoom_Pan(window, scale, shift_x, shift_y, deltaTime, temp);



      glClearColor(0.1f, 0.15f, 0.3f, 1);
      glClear(GL_COLOR_BUFFER_BIT);

   //temp += 0.01;

      // Set uniforms
      unsigned int uniformLocation_scale = glGetUniformLocation(shaderProgram, "scale");
      unsigned int uniformLocation_shift_x = glGetUniformLocation(shaderProgram, "shift_x");
      unsigned int uniformLocation_shift_y = glGetUniformLocation(shaderProgram, "shift_y");
      unsigned int uniformLocation_temp = glGetUniformLocation(shaderProgram, "NormallyTwo");
      glUniform1f(uniformLocation_scale, scale);
      //glUniform1f(uniformLocation_temp, temp);
      
      glUniform1f(uniformLocation_shift_x, shift_x);
      glUniform1f(uniformLocation_shift_y, shift_y);
      glUniform1f(uniformLocation_temp, temp);


      glUseProgram(shaderProgram);
      glBindVertexArray(VAO);
      glDrawElements(GL_TRIANGLES, 8, GL_UNSIGNED_INT, 0);
      
     
      startTime = currentTime;
      glfwSwapBuffers(window);
      glfwPollEvents();// Procces Window Events and update it
   }
   //.................................................

   // Window closing procedure
   glDeleteVertexArrays(1, &VAO);
   glDeleteBuffers(1, &VBO);
   glDeleteBuffers(1, &EBO);
   glDeleteProgram(shaderProgram);
   terminatingProcedure(window);
   return 0;
}