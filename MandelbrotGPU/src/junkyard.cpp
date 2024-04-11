

/* 

struct UserData {
   float* scale;
   float* shift_x;
   float* shift_y;
};

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
   UserData* userData = static_cast<UserData*>(glfwGetWindowUserPointer(window));

   float shift_amount = 14;
   float scale_change = 0.2;

   if(key == GLFW_KEY_PAGE_UP && (action == GLFW_REPEAT || action == GLFW_PRESS))
   {
      *(userData->scale) *= 1 - scale_change;
   }

   if(key == GLFW_KEY_PAGE_DOWN && (action == GLFW_REPEAT || action == GLFW_PRESS))
   {
      *(userData->scale) *= 1 + scale_change;
   }


   if(key == GLFW_KEY_LEFT && (action == GLFW_REPEAT || action == GLFW_PRESS))
   {
      *(userData->shift_x) += -shift_amount * *(userData->scale);
   }

     if(key == GLFW_KEY_RIGHT && (action == GLFW_REPEAT || action == GLFW_PRESS))
   {
      *(userData->shift_x) += shift_amount * *(userData->scale);
   }

     if(key == GLFW_KEY_UP && (action == GLFW_REPEAT || action == GLFW_PRESS))
   {
      *(userData->shift_y) += -shift_amount * *(userData->scale);
   }

     if(key == GLFW_KEY_DOWN && (action == GLFW_REPEAT || action == GLFW_PRESS))
   {
      *(userData->shift_y) += shift_amount * *(userData->scale);
   }
}



   // KEYBOARD INPUT
   //glfwSetKeyCallback(window, key_callback);

   // Set up the user data
   UserData userData;
   userData.scale = &scale;
   userData.shift_x = &shift_x;
   userData.shift_y = &shift_y;




   // Associate the user data with the window
   glfwSetWindowUserPointer(window, &userData);





























*/
