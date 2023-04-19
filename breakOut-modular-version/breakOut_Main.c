#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "ball.h"

// WARNING: LCD DISPLAY USES P1.0.  Do not touch!!!
#define LED BIT6 /* note that bit zero req'd for display */

void main()
{

  P1DIR |= LED; /**< Green led on when CPU on */

  P1OUT |= LED;

  configureClocks();

  lcd_init();

  //enableWDTInterrupts();      /**< enable periodic interrupt */

  //  or_sr(0x8);              /**< GIE (enable interrupts) */

  clearScreen(COLOR_BLACK);  // background is black //

  draw_ball(screenHeight/2, screenWidth/2, COLOR_RED);

  int i = 0;
  while(1) { // Testing ball modular//
    update_ball(COLOR_RED);
    if (i >= 800) {
      int oldCol = next_position[1];
      int newCol = oldCol + ball_velocity[0];

      int oldRow = next_position[0];
      int newRow = oldRow  + ball_velocity[1];

      if (newCol < colLimits[0] || newCol >= colLimits[1])  //left/right
	ball_velocity[0] = -ball_velocity[0];
      if (newRow < rowLimits[0] || newRow >= rowLimits[1]) // top/bottom
	ball_velocity[1] = -ball_velocity[1];
      else{
	next_position[1] = newCol;
	next_position[0] = newRow;
	i = 0;
      }
     
    }
    i++;
  }
}
