#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"

// WARNING: LCD DISPLAY USES P1.0.  Do not touch!!! 

#define LED BIT6		/* note that bit zero req'd for display */


#define SW1 1  // for moving to the left
#define SW2 2
#define SW3 4
#define SW4 8 // for moving the the right

#define SWITCHES 15


static char

switch_update_interrupt_sense()

{

char p2val = P2IN;

/* update switch interrupt to detect changes from current buttons */

P2IES |= (p2val & SWITCHES);/* if switch up, sense down */

P2IES &= (p2val | ~SWITCHES);/* if switch down, sense up */

return p2val;

}

void

switch_init()/* setup switch */

{

P2REN |= SWITCHES;/* enables resistors for switches */

P2IE |= SWITCHES;/* enable interrupts from switches */

P2OUT |= SWITCHES;/* pull-ups for switches */

P2DIR &= ~SWITCHES;/* set switches' bits for input */

switch_update_interrupt_sense();

}

int switches = 0;

void

switch_interrupt_handler()

{

char p2val = switch_update_interrupt_sense();

switches = ~p2val & SWITCHES;

}





// ball
  // row and column coordinates position
  int ball_position[2] = {screenHeight/2, screenWidth/2};
  int next_position[2] = {(screenHeight/2)+1, (screenWidth/2)+1};
  // Velocity of x = column direction and y = row direction
  int ball_velocity[2] = {3,3};
  
  int colLimits[2] = {1,screenWidth};
  int rowLimits[2] = {1,screenHeight};

// paddle

  int paddle_position[2] = {screenHeight-6,(screenWidth/2) -15};
  int future_position[2] = {screenHeight-6,(screenWidth/2) -15};

  int paddle_velocity[1] = {1}; // only horizontal x-compontent velocity
  
void
draw_ball(int row, int col, int color)
{
  fillRectangle(col-1, row-1, 5, 5, color);
}

int ball_color[] = {COLOR_BLUE, COLOR_RED,COLOR_GOLD, COLOR_PURPLE, COLOR_GREEN};


void update_ball(int color)
{

 for (int position = 0; position < 2; position++)
    if (ball_position[position] != next_position[position]) // position changed //
      goto re_draw_ball;
 return;
 re_draw_ball:
  draw_ball(ball_position[0], ball_position[1], COLOR_BLACK); //erase ball at row and column //

  for (int position = 0; position < 2; position++)
    ball_position[position] = next_position[position];

  draw_ball(ball_position[0], ball_position[1], color); // draw ball at new row and column//
}

char ball_paddle_collision();
char ball_block_collision();
int block_ball[2] = {0,0}; // row/col
// check left/right/upper/bottom screen edges to get new velocity and positio //
void ball_boundries()
{
  int oldCol = next_position[1];
  int newCol = oldCol + ball_velocity[0];

  int oldRow = next_position[0];
  int newRow = oldRow  + ball_velocity[1];
	
  if (newCol < colLimits[0] || newCol >= colLimits[1])  //left/right
     ball_velocity[0] = -ball_velocity[0]; 
  if (newRow < rowLimits[0] || newRow >= rowLimits[1]) // top/bottom
      ball_velocity[1] = -ball_velocity[1];
  if (ball_paddle_collision())  // paddle hit
      ball_velocity[1] = -ball_velocity[1];
  if (ball_block_collision()) { //  block hit
    if(block_ball[0] == 1) // row hit
     ball_velocity[1] = -ball_velocity[1];
    else if (block_ball[1] == 1) // colum hit
	ball_velocity[0] = -ball_velocity[0];
      
  }
  
  
 
   newCol = oldCol + ball_velocity[0];  // compute new col
   newRow = oldRow  + ball_velocity[1]; // compute new row

   next_position[1] = newCol;
   next_position[0] = newRow;
  
}

// min and max column positions
int paddle_Col_Coordintates[2] = {0,0};
void draw_paddle(int row, int col, int color)
{
  paddle_Col_Coordintates[0] = col - 1; // get paddles min column
  paddle_Col_Coordintates[1] = col + 30; // get paddles max column
  
  fillRectangle(col-1, row-1, 30, 5, color);
}

char ball_paddle_collision()
{
  //    ball within paddle width range
  if ((ball_position[1]  >= paddle_Col_Coordintates[0]) && (ball_position[1] <= paddle_Col_Coordintates[1])) 
  if ( (ball_position[0] + 5) >= (screenHeight-6))   // on same row coordinates
      return 1;
  return 0;
}

void update_paddle()
{
  draw_paddle(paddle_position[0], paddle_position[1], COLOR_BLACK); //erase ball at row and column //
  
  paddle_position[1] = future_position[1];

  draw_paddle(paddle_position[0], paddle_position[1], COLOR_RED); // draw ball at new row and column//
}

//o  move left check paddles left boundry 
void paddle_left_boundry()
{
  int oldCol =  future_position[1];
  int newCol = oldCol + (-paddle_velocity[0]);
  if ( newCol  > (colLimits[0]))
    future_position[1] = newCol;  

}

// To move right check paddles right boundry
void paddle_right_boundry()
{
  int oldCol =  future_position[1];
  int newCol = oldCol + paddle_velocity[0];
  if ( newCol  < (colLimits[1]-30))
    future_position[1] = newCol;  


}

short redrawScreen = 1;
char leftWall;
char rightWall;

void wdt_c_handler()
{
  static int secCount = 0;

  secCount ++;
  if (secCount >= 25) {		/* 10/sec */
     /* move ball */
     secCount = 0;
     ball_boundries(); // check boundries //
     // ball_paddle_collision();
     redrawScreen = 1;  
  }

  if (switches & SW4) {  // move paddle to the right
    paddle_right_boundry();
  }  
  if (switches & SW1) { // move paddle to the left
    paddle_left_boundry();
  }

}

void draw_Blocks(int row, int col, int color)
{ 
  fillRectangle(col-1, row-1, 20, 15, color);
}

// 1 means block is not destroyed, 0 means block is destroyed//
// 5x6
int blockLife[5][6] =  {{1,1,1,1,1,1},
			{1,1,1,1,1,1},
		        {1,1,1,1,1,1},
	                {1,1,1,1,1,1},
			{1,1,1,1,1,1}};

// color of each block
int blockColor[5][6] =
          {{COLOR_RED,COLOR_GREEN,COLOR_GOLD,COLOR_PINK,COLOR_PURPLE,COLOR_BROWN},
	  {COLOR_LIME_GREEN,COLOR_RED,COLOR_KHAKI,COLOR_GREEN_YELLOW,COLOR_LIGHT_BLUE,COLOR_CYAN},
	  {COLOR_MAGENTA,COLOR_TURQUOISE,COLOR_ORANGE,COLOR_TAN,COLOR_DEEP,COLOR_PURPLE},
	  {COLOR_PINK,COLOR_BEIGE,COLOR_FIREBRICK,COLOR_SIENNA,COLOR_GOLDENROD,COLOR_VIOLET},
	  {COLOR_RED,COLOR_GREEN,COLOR_GOLD,COLOR_PINK,COLOR_PURPLE,COLOR_BROWN}};

int block_count = 0;
void update_blocks()
{
  int row = 0;  // block row
  for (int i = 0; i < (screenHeight/2); i+= 16) { // Height of block
    int col = 0; // block column
    for (int j = 2; j < (screenWidth-20); j += 21){ // Width of the block
      if (blockLife[row][col] == 1)  // block still alive
         draw_Blocks(i,j,blockColor[row][col]);
      else // block destroyed
	draw_Blocks(i,j, COLOR_BLACK);
      col++;
    }
    row++;
  }  
}

char ball_block_collision()
{
  int row = 0;  // block row
  for (int i = 0; i < (screenHeight/2); i+= 16) { // Height of block
    int col = 0; // block column
    for (int j = 2; j < (screenWidth-20); j += 21){ // Width of the block
      if(blockLife[row][col] == 1 && ball_position[0] >= i &&  ball_position[0] <= i + 15  &&  ball_position[1] >= j  && ball_position[1] <= j + 20) { // ball hit row
	blockLife[row][col] = 0;
        block_count++;
	if (ball_position[0] >= i &&  ball_position[0] <= i + 15)
	  block_ball[0] = 1; // row hit
        if (ball_position[1] >= j  && ball_position[1] <= j + 20)
	  block_ball[1] = 1; // column hit
	return 1;
      }
      col++;
  }
    row++;
}
  block_ball[0] = 0;
  block_ball[1] = 0;
  return 0;
}

void main()
{
  
  P1DIR |= LED;		/**< Green led on when CPU on */
  P1OUT |= LED;
  configureClocks();
  lcd_init();
  switch_init(); 
  
  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);	              /**< GIE (enable interrupts) */
  
  clearScreen(COLOR_BLACK);

  // draw_paddle(paddle_position[0], paddle_position[1], COLOR_RED);
  int i = 0;
  while (block_count != 30) {			/* forever */
    if (redrawScreen) {
      if (i >= 5) i = 0;
      redrawScreen = 0;
      update_paddle();
      update_blocks();
      update_ball(ball_color[i]);
      i++;
    }
    P1OUT &= ~LED;	/* led off */
    or_sr(0x10);	/**< CPU OFF */
    P1OUT |= LED;	/* led on */
  }
}
 
void

  __interrupt_vec(PORT2_VECTOR) Port_2(){

  if (P2IFG & SWITCHES) {      /* did a button cause this interrupt? */

  P2IFG &= ~SWITCHES;      /* clear pending sw interrupts */

  switch_interrupt_handler();/* single handler for all switches */

}

}
