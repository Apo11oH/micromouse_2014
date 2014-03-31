/*
 * TRAVERSAL RELATED
 * Keeps track of cells we have traveled and sets wall information
 */
#include <iostream>
#include "Traversal.hpp"
#include "BotConstants.hpp"

using namespace BotConsts;

/*
 * Initializes the traversal map
 * Input: None
 * Return: None
 */
void Traversal::initTraversal()
{
  for(int i=0; i<BOARD_MAX; i++)
  {
    for(int j=0; j<BOARD_MAX; j++)
    {
      traversal[i][j] = 0;
    }
  }
  // Initialize start cell by setting the wall in E, S, and W 
  // 1 1 1 0 1 1 1 0 
  traversal[BOARD_MAX-1][0] = 0xEE; 
}

/*
 * Sets the wall and checked bits for a specific direction in the 
 * traversal map for a single cell if it meets the conditon.
 * Input: int setDirec - direction of the wall. 
 *                       0 for N, 1 for E, 2 for S, and 3 for W
 *        int curlocX - current x coordinate
 *        int curlocY - current y coordinate
 * Return: None
 */
void Traversal::setWall(int setDirec, int curLocX, int curLocY)
{
  switch(setDirec)
  {
    case 0: traversal[curLocY][curLocX] |= 0x11;
            if( curLocY>0 ) traversal[curLocY-1][curLocX] |= 0x44;
            break;
    case 1: traversal[curLocY][curLocX] |= 0x22;
            if( curLocX<BOARD_MAX-1 ) traversal[curLocY][curLocX+1] |= 0x88;
            break;
    case 2: traversal[curLocY][curLocX] |= 0x44;
            if( curLocY<BOARD_MAX-1 ) traversal[curLocY+1][curLocX] |= 0x11;
            break;
    case 3: traversal[curLocY][curLocX] |= 0x88;
            if( curLocX>0 ) traversal[curLocY][curLocX-1] |= 0x22;
            break;
  }
}

/*
 * Sets only the checked bits for a specific direction in the 
 * traversal map for a single cell if it meets the conditon.
 * Input: int setDirec - direction of the wall. 
 *                       0 for N, 1 for E, 2 for S, and 3 for W
 *        int curlocX - current x coordinate
 *        int curlocY - current y coordinate
 * Return: None
 */
void Traversal::setSeen(int setDirec, int curLocX, int curLocY)
{
  switch(setDirec)
  {
    case 0: traversal[curLocY][curLocX] |= 0x10;
            if( curLocY>0 ) traversal[curLocY-1][curLocX] |= 0x40;
            break;
    case 1: traversal[curLocY][curLocX] |= 0x20;
            if( curLocX<BOARD_MAX-1 ) traversal[curLocY][curLocX+1] |= 0x80;
            break;
    case 2: traversal[curLocY][curLocX] |= 0x40;
            if( curLocY<BOARD_MAX-1 ) traversal[curLocY+1][curLocX] |= 0x10;
            break;
    case 3: traversal[curLocY][curLocX] |= 0x80;
            if( curLocX>0 ) traversal[curLocY][curLocX-1] |= 0x20;
            break;
  }
}
/*
 * Checks the sensor values to see if there is a wall or not and record
 * the result. Based on the values, either calls setWall or setSeen.
 * Input: int curDirec - current direction that the bot is facing
 *        int fSen - front sensor value 
 *        int rSen - right sensor value 
 *        int lSen - left sensor value 
 *        int curlocX - current x coordinate
 *        int curlocY - current y coordinate
 * Return: None
 */
void Traversal::setTraversalMap(int curDirec, int fSen, int rSen, int lSen, 
                                int curLocX, int curLocY)
{
  // Check Front Sensors
  (fSen > FRONT_THRESH) ? setWall(curDirec, curLocX, curLocY):setSeen(curDirec, curLocX, curLocY);
  // Check Right Sensors
  (rSen > RIGHT_THRESH) ? setWall((curDirec+1)%3, curLocX, curLocY):setSeen((curDirec+1)%3, curLocX, curLocY);
  // Check Left Sensors
  (lSen > LEFT_THRESH) ? setWall((curDirec+3)%3, curLocX, curLocY):setSeen((curDirec+3)%3, curLocX, curLocY);
}

/*
 * If the bot came out of a dead end, it will mark the previously
 * inhabited cell as inaccessible and close it off
 * Input: int curDirec - current direction that the bot is facing
 *        int curlocX - current x coordinate
 *        int curlocY - current y coordinate
 * Return: None
 */
void Traversal::plugDeadEnd(int curDirec, int curLocX, int curLocY)
{
  switch (curDirec) {
    case 0:
      if ((traversal[curLocY][curLocX] & 0x0E) == 0x0E) {
        traversal[curLocY][curLocX] |= 0x11;
        if (curLocY > 0) traversal[curLocY-1][curLocX] |= 0x44;
      }
      break;
    case 1:
      if ((traversal[curLocY][curLocX] & 0x0D) == 0x0D) {
        traversal[curLocY][curLocX] |= 0x22;
        if (curLocX < BOARD_MAX-1) traversal[curLocY][curLocX+1] |= 0x88;
      }
      break;
    case 2:
      if ((traversal[curLocY][curLocX] & 0x0B) == 0x0B) {
        traversal[curLocY][curLocX] |= 0x44;
        if (curLocY < BOARD_MAX-1) traversal[curLocY+1][curLocX] |= 0x11;
      }
      break;
    case 3:
      if ((traversal[curLocY][curLocX] & 0x07) == 0x07) {
        traversal[curLocY][curLocX] |= 0x88;
        if (curLocX > 0) traversal[curLocY][curLocX-1] |= 0x22;
      }
      break;
  }
}

/*
 * Get the traversal value for a specific location
 * Input: int curlocX - current x coordinate
 *        int curlocY - current y coordinate
 * Return: int value - traversal value for the specified locaction
 */
int Traversal::getTraversalVal(int curLocX, int curLocY)
{
  return traversal[curLocY][curLocX];
}

/*
 * Print information regarding a specific traversal cell
 * Input: int curlocX - current x coordinate
 *        int curlocY - current y coordinate
 * Return: None
 */
void Traversal::printTraversalVal(int curLocX, int curLocY)
{
  printf("Cell (%d, %d)\n", curLocX, curLocY);
  printf("Hex of the cell: 0x%x\n", getTraversalVal(curLocX, curLocY));
}

/*
 * Print the traversal map at it's current state
 * Input: None
 * Return: None
 */
void Traversal::printTraversalMap()
{
  for(int i=0; i<BOARD_MAX; i++)
  {
    for(int j=0; j<BOARD_MAX; j++)
    {
      if (traversal[i][j] == 0)
      {
        printf("     ");
      }else{
        printf("0x%02x ", traversal[i][j]);
      }
    }
    printf("\n");
  }
}
