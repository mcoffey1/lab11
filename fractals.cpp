#include "gfx.h"
#include <cmath>
using namespace std;

const double PI =atan(1)*4;

void sierpinski( int x1, int y1, int x2, int y2, int x3, int y3 );
void drawTriangle( int x1, int y1, int x2, int y2, int x3, int y3 );
void shrinkSquares( int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int length );
void drawSquare( int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4 );
void circles(float xc, float  yc, float rad);
void spiral(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y5, float rad, float theta);
void snowflake(float xc, float yc, float length);
void tree(float x1, float y1, float length, float ang);
void wheat(float x1, float y1, float length, float ang);
void spiralSpiral(float x, float y, float rad, float ang);
void spiral(float x, float y, float rad);
int main(){
  int width = 700, height = 700, rad = 500, mrgn = 10;
  int startLength = 200;
  int startRad = 2;
  float theta = 0; 
  char c;
  bool run = true;
  gfx_open(width, height, "fractals");
  while(run){
    c = gfx_wait();
    switch (c){
      case '1':
        gfx_clear();
        sierpinski(mrgn, mrgn, width-mrgn, mrgn, width/2, height-mrgn);
	break;
      case '2':
        gfx_clear();
        shrinkSquares(width/2+startLength, height/2-startLength, width/2+startLength, height/2+startLength, width/2-startLength, height/2+startLength, width/2-startLength, height/2-startLength, startLength);
	break;
      case '3':	
	gfx_clear();
        spiral(width/2+startRad, height/2-startRad, width/2+startRad, height/2+startRad, width/2-startRad, height/2+startRad, width/2-startRad, height/2-startRad, startRad, theta);
	break;
      case '4':
        gfx_clear();
        circles(width/2, height/2, rad/2);
	break;
      case '5':
   	gfx_clear();
	snowflake(width/2, height/2, rad/2);
	break;
      case '6':
        gfx_clear();
   	tree(width/2, height-10, rad/2, PI/2);
        break;
      case '7':
	gfx_clear();
	wheat(width/2, height-mrgn, rad, PI/2);
	break;
      case '8':
        gfx_clear();
	spiralSpiral(width/2, height/2, 1, 0);
	break;
      case 'q':
	run =false;
	break;
      default:
	gfx_clear();
	break;
    }
   }
}

void sierpinski( int x1, int y1, int x2, int y2, int x3, int y3 )
{
  // Base case.
     if( abs(x2-x1) < 5 ) return;
    // Draw the triangle
        drawTriangle( x1, y1, x2, y2, x3, y3 );
  
    // Recursive calls
       sierpinski( x1, y1, (x1+x2)/2, (y1+y2)/2, (x1+x3)/2, (y1+y3)/2 );
       sierpinski( (x1+x2)/2, (y1+y2)/2, x2, y2, (x2+x3)/2, (y2+y3)/2 );
       sierpinski( (x1+x3)/2, (y1+y3)/2, (x2+x3)/2, (y2+y3)/2, x3, y3 );
}

 void drawTriangle( int x1, int y1, int x2, int y2, int x3, int y3 )
 {
     gfx_line(x1,y1,x2,y2);
     gfx_line(x2,y2,x3,y3);
     gfx_line(x3,y3,x1,y1);
 }


void shrinkSquares( int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int length )
{
  if( length < 5 ) return;

  drawSquare( x1, y1, x2, y2, x3, y3, x4, y4 );

  shrinkSquares( x1+length/2, y1-length/2, x1+length/2, y1+length/2, x1-length/2, y1+length/2, x1-length/2, y1-length/2, length/2 );
  shrinkSquares( x2+length/2, y2-length/2, x2+length/2, y2+length/2, x2-length/2, y2+length/2, x2-length/2, y2-length/2, length/2 );
  shrinkSquares( x3+length/2, y3-length/2, x3+length/2, y3+length/2, x3-length/2, y3+length/2, x3-length/2, y3-length/2, length/2 );
  shrinkSquares( x4+length/2, y4-length/2, x4+length/2, y4+length/2, x4-length/2, y4+length/2, x4-length/2, y4-length/2, length/2 );
}

void drawSquare( int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4 )
{
  gfx_line(x1,y1,x2,y2);
  gfx_line(x2,y2,x3,y3);
  gfx_line(x3,y3,x4,y4);
  gfx_line(x4,y4,x1,y1);
}


void spiral (int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, float rad, float theta){

  if (rad > 100) return;


  drawSquare(x1, y1, x2, y2, x3, y3, x4, y4);
  float xc = ((x1+x3)/2) + 4*rad*cos(theta);
  float yc = ((y1+y2)/2) + 4*rad*sin(theta);

  spiral (xc+rad, yc-rad, xc+rad, yc+rad, xc-rad, yc+rad, xc-rad, yc-rad, rad+4, theta+PI/5);

}

void circles (float xc, float yc, float rad){
  if (rad < 1) return;

  gfx_circle(xc, yc, rad);

  for (float theta = 0; theta < 2*PI; theta+=PI/3){
    circles (xc+rad*cos(theta), yc+rad*sin(theta), rad/3);
  }
}


void snowflake(float xc, float yc, float length){
  if (length < 1) return;
    float ang;
    for (int i = 0; i < 5; i++){
       ang  = 2 * PI * i / 5;
       gfx_line(xc, yc, xc + length * cos(ang), yc + length * sin(ang));
       snowflake(xc+length*cos(ang), yc+length*sin(ang), length/3);
    }
}
void tree(float x1, float y1, float length, float ang){
  if (length < 1) return;
  gfx_line(x1, y1, x1+length*cos(ang), y1 - length*sin(ang));

  tree(x1+length*cos(ang), y1-length*sin(ang), length/(1.5), ang+PI/4);
  tree(x1+length*cos(ang), y1-length*sin(ang), length/(1.5), ang-PI/4);

}
   
void wheat(float x1, float y1, float length, float ang){
  if (length < 1) return;
  gfx_line(x1, y1, x1+length*cos(ang), y1-length*sin(ang));

  for (int i = 1; i <= 4; i++){
    wheat(x1+(length*i/4)*cos(ang), y1-(length*i/4)*sin(ang), length/4, ang+PI/4);
    wheat(x1+(length*i/4)*cos(ang), y1-(length*i/4)*sin(ang), length/4, ang-PI/4);
  }
} 

void spiralSpiral(float x, float y, float rad, float ang){
  if (rad >  95) return;
  spiral (x, y, rad);
  spiralSpiral(x+rad*cos(ang), y+rad*sin(ang), rad+1.2, ang+(PI/12));
  
}
void spiral(float x, float y, float rad){
   if (rad < 5) return;
   for (int i = 1; i < rad/2; i++){
     gfx_point(x+i*cos(i*PI/12), y+i*sin(i*PI/12));
     spiral (x+i*cos(i*PI/12), y+i*sin(i*PI/12), i);
   }
   
}
      
