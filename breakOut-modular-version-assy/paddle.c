#include "lcdutils.h"
#include "lcddraw.h"
#include "ball.h"
#include "paddle.h"


                // paddle//
int paddle_position[2] = {screenHeight-23,(screenWidth/2) -15};

int future_position[2] = {screenHeight-23,(screenWidth/2) -15};

int paddle_velocity[1] = {1}; // only horizontal x-compontent velocity

// min and max column positions //
int paddle_Col_Coordintates[2] = {0,0};

void draw_paddle(int row, int col, int color)
{
  paddle_Col_Coordintates[0] = col - 1; // get paddles min column

  paddle_Col_Coordintates[1] = col + 30; // get paddles max column

  fillRectangle(col-1, row-1, 30, 5, color);
}

// Detect collisions //
char ball_paddle_collision()
{
  //    ball within paddle min width and max width range
  if ((ball_position[1]  >= paddle_Col_Coordintates[0] - 2) && (ball_position[1] <= paddle_Col_Coordintates[1] + 2))
    if ( (ball_position[0] + 8) >=  paddle_position[0]) {  // on same row coordinates
      ball_color = COLOR_RED;
      return 1;
    }
  return 0;
}

void update_paddle()
{
  if (paddle_position[1] != future_position[1]) {
     draw_paddle(paddle_position[0], paddle_position[1], COLOR_BLACK); //erase ball at row and column //
    paddle_position[1] = future_position[1];

    draw_paddle(paddle_position[0], paddle_position[1], COLOR_RED); // draw ball at new row and column//
  }
}


//To  move left check paddles left boundry
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
