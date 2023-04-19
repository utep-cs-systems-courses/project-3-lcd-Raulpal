#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "ball.h"
#include "switches.h"

// WARNING: LCD DISPLAY USES P1.0.  Do not touch!!!
#define LED BIT6 /* note that bit zero req'd for display */


short redrawScreen = 1;

void wdt_c_handler()
{
  static int secCount = 0;

  secCount ++;

  if (secCount >= 25) {/* 10/sec */

    /* move ball */
    secCount = 0;
    ball_collisions(); // check boundries //

    // ball_paddle_collision();
    redrawScreen = 1;
  }

  // Testing switches
  if (switches & SW4)
    update_ball(COLOR_BLUE);
  if (switches & SW1)
    update_ball(COLOR_GREEN);
}
  
void main()
{

  P1DIR |= LED; /**< Green led on when CPU on */

  P1OUT |= LED;

  configureClocks();

  lcd_init();

  switch_init();              // setp up switches //

  enableWDTInterrupts();      /**< enable periodic interrupt */

  or_sr(0x8);                 /**< GIE (enable interrupts) */


  clearScreen(COLOR_BLACK);  // background is black //


  while(1) { // Testing ball modular//
    if (redrawScreen) {
      redrawScreen = 0;
      update_ball(COLOR_RED);
    }
    P1OUT &= ~LED;      /* led off */
    or_sr(0x10);        /**< CPU OFF */
    P1OUT |= LED;       /* led on */
    
  }
}
