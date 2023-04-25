#include "lcdutils.h"
#include "lcddraw.h"
#include "hearts.h"
#include "ball.h"

void heart_outline_1(int color) // white
{
  int i = 0;
  for (int r = (screenHeight- 16); r < (screenHeight-10); r++){
    for (int c  = 0; c < i; c++){
      // top left
      drawPixel(5+c,r,color);
      drawPixel(5-c,r,color);
      // top right
      drawPixel(12+c,r,color);
      drawPixel(12-c,r,color);
    }
    i++;
  }
  
  // bottom half
  i = 0;
  for (int r = (screenHeight- 15); r < (screenHeight- 7); r++){
    for (int c  = i; c < 8; c++){
      drawPixel(1+c,r+5,color);
      drawPixel(15-c,r+5,color);
    }
    i++;
  }
}

void heart_fill_1(int color)
{ 
  int i = 0;
  for (int r = (screenHeight- 15); r < (screenHeight-10); r++){
    for (int c  = 0; c < i; c++){
      // top left
      drawPixel(5+c,r,color);
      drawPixel(5-c,r,color);

      // top right
       drawPixel(12+c,r,color);
       drawPixel(12-c,r,color);
    }
    i++;
  }   
  // bottom half
  i = 0;
  for (int r = (screenHeight- 15); r < (screenHeight- 8); r++){
    for (int c  = i; c < 7; c++){
      drawPixel(2+c,r+5,color);
      drawPixel(14-c,r +5,color);
    }
    i++;
  }
}

void heart_outline_2(int color)
{ 
  int i = 0;
  for (int r = (screenHeight- 16); r < (screenHeight-10); r++){
    for (int c  = 0; c < i; c++){
      // top left
      drawPixel(23+c,r,color);
      drawPixel(23-c,r,color);
      // top right
      drawPixel(30+c,r,color);
      drawPixel(30-c,r,color);
    }
    i++;
  }

  // bottom half
  i = 0;
  for (int r = (screenHeight- 15); r < (screenHeight- 7); r++){
    for (int c  = i; c < 8; c++){
      drawPixel(19+c,r+5,color);
      drawPixel(34-c,r +5,color);
    }
    i++;
  }


}

void heart_fill_2(int color)
{
  int i = 0;
  for (int r = (screenHeight- 15); r < (screenHeight-10); r++){
    for (int c  = 0; c < i; c++){
      // top left
      drawPixel(23+c,r,color);
      drawPixel(23-c,r,color);

      // top right
       drawPixel(30+c,r,color);
       drawPixel(30-c,r,color);
    }
    i++;
  }
  
  // bottom half
  i = 0;
  for (int r = (screenHeight- 15); r < (screenHeight- 8); r++){
    for (int c  = i; c < 7; c++){
      drawPixel(20+c,r+5,color);
      drawPixel(33-c,r +5,color);
    }
    i++;
  }
}

void heart_outline_3(int color)
{
  int i = 0;
  for (int r = (screenHeight- 16); r < (screenHeight-10); r++){
    for (int c  = 0; c < i; c++){
      // top left
      drawPixel(41+c,r,color);
      drawPixel(41-c,r,color);
      // top right
      drawPixel(48+c,r,color);
      drawPixel(48-c,r,color);
    }
    i++;
  }

  // bottom half
  i = 0;
  for (int r = (screenHeight- 15); r < (screenHeight- 7); r++){
    for (int c  = i; c < 8; c++){
      drawPixel(37+c,r+5,color);
      drawPixel(52-c,r +5,color);
    }
    i++;
  }
}
void heart_fill_3(int color)
{
  int i = 0;
  for (int r = (screenHeight- 15); r < (screenHeight-10); r++){
    for (int c  = 0; c < i; c++){
      // top left
      drawPixel(41+c,r,color);
      drawPixel(41-c,r,color);

      // top right
       drawPixel(48+c,r,color);
       drawPixel(48-c,r,color);
    }
    i++;
  }
  
  // bottom half
  i = 0;
  for (int r = (screenHeight- 15); r < (screenHeight- 8); r++){
    for (int c  = i; c < 7; c++){
      drawPixel(38+c,r+5,color);
      drawPixel(51-c,r +5,color);
    }
    i++;
  }
}
void draw_heart_1()
{
  heart_outline_1(COLOR_WHITE);
  heart_fill_1(COLOR_RED);     
}
void draw_heart_2()
{
  heart_outline_2(COLOR_WHITE);
  heart_fill_2(COLOR_RED);
}
void draw_heart_3()
{
  heart_outline_3(COLOR_WHITE);
  heart_fill_3(COLOR_RED);
}


void update_heart()
{
  if (ball_health == 3) {
    draw_heart_1();
    draw_heart_2();
    draw_heart_3();
  }
  else if (ball_health == 2) {
    draw_heart_1();
    draw_heart_2();
    heart_outline_3(COLOR_BLACK);
    heart_fill_3(COLOR_BLACK);
  }
  else if (ball_health == 1) {
    draw_heart_1();
    heart_outline_2(COLOR_BLACK);
    // heart_outline_3(COLOR_BLACK); 
  } else {
    heart_outline_1(COLOR_BLACK);
    //heart_outline_2(COLOR_BLACK);
    // heart_outline_3(COLOR_BLACK); 
  }
  
}
