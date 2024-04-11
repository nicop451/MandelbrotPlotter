#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

using namespace sf;

void fpsDisplay(sf::Text &text, sf::RenderWindow &win, float deltaTime)
{
   std::string fps_string = std::to_string(roundf(((1 / deltaTime)) * 100) / 100);

   float fps_float = std::stof(fps_string); 

   if (fps_float < 60)
   {
      text.setFillColor(Color::Red);
   }
   else
   {
      text.setFillColor(Color::Green);
   }

   text.setString("   " + std::to_string(fps_float) + "fps");

   win.draw(text);
}