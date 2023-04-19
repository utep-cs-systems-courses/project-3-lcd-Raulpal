#ifndef ball_included
#define ball_included


// ---------------ball---------------//

// row = zero element and column  = first element //
// start at center screen//
extern int ball_position[2], next_position[2]; 

extern int ball_velocity[2];

extern int colLimits[2], rowLimits[2];


  
void draw_ball(int row, int col, int color);
void update_ball(int color);
void ball_collisions();

#endif // included
