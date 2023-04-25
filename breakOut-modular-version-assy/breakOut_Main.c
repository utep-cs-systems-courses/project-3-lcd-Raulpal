
#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "ball.h"
#include "paddle.h"
#include "blocks.h"
#include "switches.h"
#include "hearts.h"
#include "scoreBoard.h"
#include "buzzer.h"
#include <stdio.h>
// WARNING: LCD DISPLAY USES P1.0.  Do not touch!!!
#define LED BIT6 /* note that bit zero req'd for display */


short redrawScreen = 1;

void wdt_c_handler()
{
  static int secCount = 0;

  secCount ++;

  if (secCount >= 25) {   /* 10/sec */
    /* move ball */
    secCount = 0;
    ball_collisions(); // check boundries //

    // ball_paddle_collision();
    redrawScreen = 1;
  }

  // button 4 = right movement and button 1 = left movement //
  if (switches & SW4) 
    paddle_right_boundry();
      
  if (switches & SW1) 
    paddle_left_boundry();
   
}

void update_screen();
void main()
{

  P1DIR |= LED; /**< Green led on when CPU on */

  P1OUT |= LED;

  configureClocks();

  lcd_init();

  switch_init();              // setp up switches //

  buzzer_init();              // set up sound  //

  enableWDTInterrupts();      /**< enable periodic interrupt */

  or_sr(0x8);                 /**< GIE (enable interrupts) */

  //buzzer_set_period(1000);

  clearScreen(COLOR_BLACK);  // background is black //

  fillRectangle(0,screenHeight-18, screenWidth, 3, COLOR_WHITE);

  update_heart();            // initial heart lives //

  draw_paddle(screenHeight-23, (screenWidth/2) -15, COLOR_RED); 
  
  drawString8x12((screenWidth/2) + 39,screenHeight-12,"/30", COLOR_WHITE, COLOR_BLACK);

  while(block_count < 30 &&  ball_health > 0) { // until play finshed game or loses last life//
    if (redrawScreen) {
      redrawScreen = 0;
      update_screen();
    }
    P1OUT &= ~LED;      // led off //
    or_sr(0x10);        // CPU OFF //
    P1OUT |= LED;       // led on //
    
  }
   or_sr(~0x8);       /**< GIE (disable interrupts) */
   or_sr(0x10);        // CPU OFF //
 
 
}


void update_screen()
{
   update_paddle(); 
   update_blocks();
   update_score();
   update_ball();
}
