// #ifndef GENERALFUNCTIONS_CPP
// #define GENERALFUNCTIONS_CPP

// #include <iostream>
// #include <cmath>
// #include <vector>

// #include "Color.hpp"

// int getOrbitIterations(float a, float b, int maxIterations)
// {
   
//    float Ca = a;
//    float Cb = b;

//    int n = 0;
//    while(n < maxIterations)
//    {
//       float ZnSqr_a = a*a - b*b;
//       float ZnSqr_b = 2 * a * b;

//       a = ZnSqr_a + Ca;
//       b = ZnSqr_b + Cb;
//       if(a*a+b*b > 12)
//          break;
//       n++;
//    }
//    return n;
// }


// Color getOrbitColor(int n, int maxIterations)
// {
//    float bright =(float(n)/(maxIterations)) * 0.03;
//    float gradient_r = sin(sqrt(float(n)/(float(maxIterations))));
//    float gradient_g = 1/(gradient_r);
//    float gradient_b = 1/(gradient_g/gradient_r);
//    if(n == maxIterations)
//    {
//       bright = 0;
//    }
//    return Color(gradient_r * bright * 50, gradient_b * bright * 170, gradient_g * bright * 100, 1.0f);
// }

// std::vector<Color> plotFractal(int winWidth, int winHeight, float scale, float shift_x, float shift_y, std::vector<Color> &pixelArray)
// {
//    std::vector<Color> plotArray;

//    int maxIterations = 1000;

   

//    for(int x = 0; x < winWidth; x++)
//    {
//       for(int y = 0; y < winHeight; y++)
//       {

//          float a = ((x - 964) * scale) + shift_x;
//          float b = ((y - 540) * scale) + shift_y*-1;

//          int n = getOrbitIterations(a, b, maxIterations);

//          Color plotPointColor = getOrbitColor(n, maxIterations); 

//          plotArray[y*winWidth + x] = ;
//       }
//    }
   
//    return plotArray;
// }




// out vec4 FragColor;
// uniform float scale;
// uniform float shift_x;
// uniform float shift_y;
// void main()
// {
//    int maxIterations = 1000;

//    float a = ((gl_FragCoord.x - 964) * scale) + shift_x;
//    float b = (((gl_FragCoord.y - 540) * scale) + shift_y)*-1;

//    getIterations()
   
// }

// #endif