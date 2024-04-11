#include <SFML/Graphics.hpp>

using namespace sf;

struct mandelParams
{
   float win_width;
   float win_height;
   float offset_x; float offset_y; float scale;
   float init_x; float init_y;
   int iteration_amt;
   VertexArray &pixels;
   Image &plotBufferImage;
   Texture &plotBufferTexture;
   Sprite &plot_sprite;
   RenderWindow &win;
};

void plotMandelbrot
(
   float win_width,
   float win_height, 
   float offset_x, float offset_y, float scale,
   float init_x, float init_y,
   int iteration_amt,
   VertexArray &pixels,
   Image &plotBufferImage,
   Texture &plotBufferTexture,
   Sprite &plot_sprite,
   RenderWindow &win
)

{
   for(int x = init_x; x < win_width; x++)// for every coulmn
   {
      for(int y = init_y; y < win_height; y++)//for every row
      {  
         float a = ((x - win_width/2)  *  scale) + offset_x; float b = ((y - win_height/2) *  scale) + offset_y; // Properly scale and translate values 
         float root_a = a, root_b = b; // Store starting a and b values to use as + C 

         int n = 0;// Iterate n number of times on point
         while(n < iteration_amt)
         {
            float ZnSqr_a = a * a - b * b;// Calculate terms
            float ZnSqr_b = 2 * a * b;// Calculate terms
            a = ZnSqr_a + root_a, b = ZnSqr_b + root_b; // Update new terms invdividually as them plus pixel coordinate we are checking Zn = Zn+1^2 +C 
            if(a*a + b*b > 25){break;}// If point is not part of set break out of checking this point
            n++;
         }
         float bright = n;// Color Pixel According to iteration amount before it was removed from set
         if(n == iteration_amt){bright = 0;}// If its part of set color it dark
         plotBufferImage.setPixel(x, y, Color(bright * 1.3, bright * 1.5, bright * 2)); // Set pixel color to calculated value at current pixel coordinate
      }
   }
plotBufferTexture.loadFromImage(plotBufferImage);
plot_sprite.setTexture(plotBufferTexture);
win.draw(plot_sprite);

}