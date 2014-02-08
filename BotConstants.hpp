/*
 * Constants used throughout the codes
 */

#ifndef MY_CONSTS
#define MY_CONSTS

namespace BotConsts
{
    const int BOARD_MAX = 16;
    const int FRONT_THRESH = 2000;
    const int RIGHT_THRESH = 2000;
    const int LEFT_THRESH = 2000;
    const int GOAL_X = BOARD_MAX/2-1;
    const int GOAL_Y = BOARD_MAX/2-1; 
    const int CELL_MAX = BOARD_MAX * BOARD_MAX + 1;
} 

#endif
