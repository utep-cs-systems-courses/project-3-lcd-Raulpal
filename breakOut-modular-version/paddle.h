#ifndef paddle_included
#define paddle_included

     // paddle//
extern int paddle_position[2];

extern int future_position[2];

extern int paddle_velocity[1]; // only horizontal x-compontent velocity

// min and max column positions //
extern int paddle_Col_Coordintates[2];

void draw_paddle(int row, int col, int color);
void update_paddle();
char ball_paddle_collision();
void update_paddle();
void paddle_left_boundry();
void paddle_right_boundry();

#endif // included
