#include "lcdutils.h"
#include "lcddraw.h"

int ball_position[2] = {screenHeight/2, screenWidth/2}; 

int next_position[2] = {(screenHeight/2)+1, (screenWidth/2)+1}; 

int ball_velocity[2] = {3,3}; // x = columns, y = row direction

// row and col bounds//
int colLimits[2] = {1,screenWidth};

int rowLimits[2] = {1,screenHeight};


// draw size of ball 5x5 //
void draw_ball(int row, int col, int color) 
{
  fillRectangle(col-1, row-1, 5, 5, color);
}

// update balls position //
void update_ball(int color) 
{
  for (int position = 0; position < 2; position++)
    if (ball_position[position] != next_position[position]) // Position changed //
      goto re_draw_ball;
  
  return;

 re_draw_ball:

  draw_ball(ball_position[0], ball_position[1], COLOR_BLACK); // Erase ball at row and column //

  for (int position = 0; position < 2; position++)

    ball_position[position] = next_position[position];

  draw_ball(ball_position[0], ball_position[1], color); // Draw ball at new row and column//
}
// left/right/upper/lower/paddles/block collisions //
void ball_collisions()
{
  int oldCol = next_position[1];
  int newCol = oldCol + ball_velocity[0];

  int oldRow = next_position[0];
  int newRow = oldRow  + ball_velocity[1];

  if (newCol < colLimits[0] || newCol >= colLimits[1])  //left/right
    ball_velocity[0] = -ball_velocity[0];

  if (newRow < rowLimits[0] || newRow >= rowLimits[1]) // top/bottom
    ball_velocity[1] = -ball_velocity[1];

  newCol = oldCol + ball_velocity[0];  // compute new col
  newRow = oldRow  + ball_velocity[1]; // compute new row

  next_position[1] = newCol;
  next_position[0] = newRow;
}
