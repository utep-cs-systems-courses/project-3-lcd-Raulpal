#ifndef blocks_included
#define blocks_included

extern int blockLife[5][6], blockColor[5][6];
extern int block_count, past_ball_count;
extern int block_ball[2]; // row and col //

void draw_Blocks(int row, int col, int color);
void update_blocks();
char ball_block_collision();
#endif // included
