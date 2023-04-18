/** \file lcddemo.c
 *  \brief A simple demo that draws a string and square
 */
#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"


  // row and column coordinates position
  int ball_position[2] = {screenHeight/2, screenWidth/2};
  int next_position[2] = {(screenHeight/2)+1, (screenWidth/2)+1};
  // Velocity of x = column direction and y = row direction
  int ball_velocity[2] = {1,1};
  
  int colLimits[2] = {1,screenWidth};
  int rowLimits[2] = {1,screenHeight};


void draw_ball(int row, int col, int color)
{
  // column, row, width, height and color
  fillRectangle(col-1,row-1, 5,5, color);
}

void update_ball()
{

 for (int position = 0; position < 2; position++)
    if (ball_position[position] != next_position[position]) // position changed //
      goto re_draw_ball;
 return;
 re_draw_ball:
  draw_ball(ball_position[0], ball_position[1], COLOR_BLACK); //erase ball at row and column //

  for (int position = 0; position < 2; position++)
    ball_position[position] = next_position[position];

  draw_ball(ball_position[0], ball_position[1], COLOR_BLUE); // draw ball at new row and column//
}

void wdt_c_handler()
{
  static int secCount = 0;
  secCount++;

  if (secCount >= 25) {
     secCount = 0;
     int oldCol = next_position[1];
     int newCol = oldCol + ball_velocity[0];

     int oldRow = next_position[0];
     int newRow = oldRow  + ball_velocity[1];
	
     if (newCol < colLimits[0] || newCol >= colLimits[1]) {
        ball_velocity[0] = -ball_velocity[0]; 
     }
     if (newRow < rowLimits[0] || newRow >= rowLimits[1]) {
        ball_velocity[1] = -ball_velocity[1]; 
     }else {
        next_position[1] = newCol;
        next_position[0] = newRow;
	//secCount= 0;
     } 
  }
}

main()
{
  configureClocks();
  lcd_init();
  //  u_char width = screenWidth, height = screenHeight;
  enableWDTInterrupts();
  or_sr(0x8);
  
  clearScreen(COLOR_BLACK);

  draw_ball(ball_position[0], ball_position[1], COLOR_RED);

  while (1) {
    update_ball();
  }
  /*
  int i = 0;
    while(1) {
      update_ball();
      if (i>= 25) {
	int oldCol = next_position[1];
	int newCol = next_position[1] + ball_velocity[0];

	int oldRow = next_position[0];
	int newRow = next_position[0] + ball_velocity[1];
	
	if (newCol < colLimits[0] || newCol >= colLimits[1]) {
	  ball_velocity[0] = -ball_velocity[0]; 
	}
	if (newRow < rowLimits[0] || newRow >= rowLimits[1]) {
	  ball_velocity[1] = -ball_velocity[1]; 
	}else {
	  next_position[1] = newCol;
	  next_position[0] = newRow;
	  i = 0;
	}
      }
      i++;
    }
  */
}
