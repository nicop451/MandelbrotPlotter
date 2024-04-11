
#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>
#include <thread>
#include <cstdlib>
#include <iostream>
#include <vector>
#include "math.hpp"
#include "displayUtils.hpp"
#include "MandelbrotFunctionality.hpp"


using namespace sf;

void Zoom_and_Pan(float &offset_x, float &offset_y, float &scale, float scale_change, float deltaTime)
{
   if(Keyboard::isKeyPressed(Keyboard::PageUp))
   {
      scale *= 1 - scale_change * deltaTime;// * deltaTime;
   }
   if(Keyboard::isKeyPressed(Keyboard::PageDown))
   {
      scale *= 1 + scale_change * deltaTime;   
   }
   if(Keyboard::isKeyPressed(Keyboard::Up))
   {
      offset_y += (-100)* deltaTime * scale;
   }
   if(Keyboard::isKeyPressed(Keyboard::Down))
   {
      offset_y += (100)* deltaTime * scale;
   }
   if(Keyboard::isKeyPressed(Keyboard::Left))
   {
      offset_x += (-100)* deltaTime * scale;
   }
   if(Keyboard::isKeyPressed(Keyboard::Right))
   {
      offset_x += (100)* deltaTime * scale;
   }
}







int main ()
{
   // Window Dimensions
   int win_width = 980;
   int win_height = 520;
   
   // Window Init
   sf::RenderWindow win = sf::RenderWindow(sf::VideoMode(win_width, win_height), "Mandelbrot Plotter");
   win.setFramerateLimit(230);

   // Time and frame rate
   sf::Clock clock;
   float deltaTime;
   float timeMultiplier = 14;
   
   // FPS display
   sf::Font font;
   font.loadFromFile("C:\\SFML_fonts\\Kanit-Regular.ttf");
   sf::Text fpsText;
   fpsText.setFont(font);
   fpsText.setFillColor(Color::Green);

   // Mandelbrot stuff
   sf::RectangleShape drawShape(Vector2f(1,1));
   
   float scale = 0.003;
   int iteration_amt = 1000;

   float scale_speed = 0.4;

   float offset_x = 0;
   float offset_y = 0;

   // Rendering variables and Texture for plotter
   VertexArray pixels(sf::Points, win_width * win_height);

   Image plotBufferImage;
   plotBufferImage.create(win_width, win_height, Color(0, 0, 0));

   Texture plotBufferTexture;
   plotBufferTexture.loadFromImage(plotBufferImage);

   Sprite plot_sprite;
   plot_sprite.setTexture(plotBufferTexture);

   CircleShape middleScreen;
   middleScreen.setPosition(Vector2f(win_width/2 - 4, win_height/2 - 4));
   middleScreen.setRadius(4);


   //mandelParams thread1Params = {win_width, win_height, offset_x, offset_y, scale, 0, 0, iteration_amt, pixels, plotBufferImage, plotBufferTexture, plot_sprite, win};

   
   //sf::Thread thread1(&plotMandelbrot, thread1Params);

   //Image mbImage = 

   
   


   // Program Loop
   while (win.isOpen())
   {
      // Checks if window close event happens then it closes program
      sf::Event event;
      while(win.pollEvent(event))
      {
         if (event.type == sf::Event::Closed)
         {
            win.close();
         }            
      }

      // Calculate FPS
      float deltaTime = clock.restart().asSeconds();

      win.clear();

      Zoom_and_Pan(offset_x, offset_y, scale, scale_speed, deltaTime);


      plotMandelbrot(win_width, win_height, offset_x, offset_y, scale, 0, 0, iteration_amt, pixels, plotBufferImage, plotBufferTexture, plot_sprite, win);

      
      // win.draw(plot_sprite);
      win.display();
      
      // Rendering----------------------------------------------------------------------------
      // win.clear();

      

      // //thread1.launch();
      //       // Mandelbrot
      // //plotMandelbrot(win_width, win_height, offset_x, offset_y, scale, 0, 0, iteration_amt, pixels, plotBufferImage, plotBufferTexture, plot_sprite, win);

      // // Crosshair
      // win.draw(middleScreen);

      // // Fps Hud
      // fpsDisplay(fpsText, win, deltaTime);
      
      // // Displays particles
      // win.display();
      //---------------------------------------------------------------------------------
   }

   return 0;
}
