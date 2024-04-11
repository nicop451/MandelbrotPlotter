#version 330 core
out vec4 FragColor;
void main()
{
   int maxIterations = 100; 

   float a = gl_FragCoord.x * 0.01;
   float b = gl_FragCoord.y * 0.01;

   float Ca = a;
   float Cb = b;

   int n = 0;
   while(n < maxIterations && a*a + b*b < 17)
   {
      float ZnSqr_a = a*a - b*b;
      float ZnSqr_b = 2 * a * b;

      a = ZnSqr_a + Ca;
      b = ZnSqr_b + Cb;
      n++;
   }
   float bright = n;
   if(n == maxIterations)
   {
      bright = 0;
   }
   FragColor = vec4(bright, bright, bright, 1.0f);
}