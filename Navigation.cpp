/*
 * NAVIGATION
 * Figure out which direction to move next
 */
#include <iostream>
#include "BotConstants.hpp"
#include "Traversal.hpp"
#include "Navigation.hpp"

using namespace std;
using namespace BotConsts;

/*
 * Initialize floodfill matrix for finding the goal
 * Input: None
 * Return: None
 */
void Navigation::initNaviGoal()
{
  for(int i=0; i<BOARD_MAX; i++)
  {
    for(int j=0; j<BOARD_MAX; j++)
    {
      floodfill[i][j] = BOARD_MAX*BOARD_MAX;
    }
  }
  floodfill[GOAL_Y][GOAL_X] = 0;
  floodfill[GOAL_Y+1][GOAL_X] = 0;
  floodfill[GOAL_Y][GOAL_X+1] = 0;
  floodfill[GOAL_Y+1][GOAL_X+1] = 0;
}

/*
 * Initialize floodfill matrix for getting back to the starting point 
 * Input: None
 * Return: None
 */
void Navigation::initNavHoming()
{
  for(int i=0; i<BOARD_MAX; i++)
  {
    for(int j=0; j<BOARD_MAX; j++)
    {
      floodfill[i][j] = BOARD_MAX*BOARD_MAX;
    }
  }
  floodfill[BOARD_MAX-1][0] = 0;
}

/*
 * Update the floodfill map based on the current recorded maze
 * Input: Traversal - trav
 * Return: None
 */
void Navigation::updateFloodfill(Traversal trav)
{
  bool foundFlag;
  int temp;

  for(int i=0; i<CELL_MAX-1; i++)
  {
    foundFlag = false;
    for(int j=0; j<CELL_MAX; j++) // y-coordinates
    {
      for( int k=0; k<CELL_MAX; k++) // x-coordinates
      {
        if(floodfill[k][j]==i)
        {
          foundFlag = true;
          temp = trav.getTraversalVal(k, j);
          // Check North 
          if(j > 0)
            if((floodfill[j-1][k]==CELL_MAX)&&((temp&0x01) != 0x01))
              floodfill[j-1][k] = floodfill[j][k]+1;
          // Check East 
          if(k < BOARD_MAX-1)
            if((floodfill[j][k+1]==CELL_MAX) && ((temp&0x02) != 0x02))
              floodfill[j][k+1] = floodfill[j][k]+1;
          // Check South 
          if(j < BOARD_MAX-1)
            if((floodfill[j+1][k]==CELL_MAX) && ((temp&0x04) != 0x04))
              floodfill[j+1][k] = floodfill[j][k]+1;
          // Check West 
          if(k > 0)
            if((floodfill[j][k-1]==CELL_MAX)&&((temp&0x08) != 0x08))
              floodfill[j][k-1] = floodfill[j][k]+1;
        }
      }
    }
    if(!foundFlag){ break; }
  }
  

}


/*
 * Based on the floodfill map, determine which direction to move 
 * next. Low floodfill value have priority.
 * Input: int trav - traversal value for the cell to be checked 
 * Return: 0 for North, 1 for East, 2 for South, 3 for West 
 */
int Navigation::findNextDirec(int trav)
{
  int around[4];
  int smallest;
  int index = 0;

  // Initialize the around array to maximum values
  for(int i=0; i<4; i++) around[i]=BOARD_MAX*BOARD_MAX;

  // (North) If current location is within bounds and there is no wall
  if(curLocY > 0 && (trav&0x01) != 0x01 ) 
      around[0] = floodfill[curLocY-1][curLocX];
  // (East) If current location is within bounds and there is no wall
  if(curLocX < BOARD_MAX-1 && (trav&0x02) != 0x02 )
      around[1] = floodfill[curLocY][curLocX+1];
  // (South) If current location is within bounds and there is no wall
  if(curLocX < BOARD_MAX-1 && (trav&0x04) != 0x04 )
      around[2] = floodfill[curLocY+1][curLocX];
  // (West) If current location is within bounds and there is no wall
  if(curLocX > 0 && (trav&0x08) != 0x08 )
      around[3] = floodfill[curLocY][curLocX-1];

  smallest = around[0];
  for(int i=1; i<4; i++)
  {
    if(around[i] < smallest)
    {
      smallest = around[i];
      index = i;
    }
  }

  return index;
}

/*
 * Based on the current direction and the next direction we have to move,
 * calculate how many degrees we have to turn (or not)
 * Input: None 
 * Return: amount we need to turn to get to the new direction
 */
int Navigation::chooseTurn()
{
  int diff = nxtDirec - curDirec;

  if(diff == 0)
  {
    turnAmt = 0;
  }else if(diff == 2 || diff == -2)
  {
    turnAmt = 2;
  }else if(diff == 1 || diff == -3)
  {
    turnAmt = 1;
  }else // diff==3 || diff==-1
  {
    turnAmt = 3;
  }

  return turnAmt;
}

/*
 * Update direction of the droid
 * Input:
 * Return:
 */
void Navigation::updateDirec()
{
  curDirec = (curDirec + turnAmt) % 4;
}

/*
 * Update the coordinates for the bot based on the direction we have
 * chosen to go next
 * Input: 
 * Return: 
 */
void Navigation::updateLoc()
{
  switch(curDirec)
  {
    case 0: curLocY--; break;
    case 1: curLocX++; break;
    case 2: curLocY++; break;
    case 3: curLocX--; break; 
  }
}

/*
 * Update all relavent information and figure out which direction to move next
 * Input: int trav - traversal value (wall information) of the cell we're checking
 * Return: amount the droid needs to move to arrive at next direction
 */
int Navigation::makeMove(int trav)
{
  nxtDirec = findNextDirec(trav); 
  turnAmt = chooseTurn();
  updateDirec();
  if(turnAmt != 0){ updateLoc(); }
  return turnAmt;
}

/*
 * Getter for the current x-coordinate
 * Input: None
 * Return: Current x-coordinate
 */
int Navigation::getLocX()
{
  return curLocX;
}

/*
 * Getter for the current y-coordinate
 * Input: None
 * Return: Current y-coordinate
 */
int Navigation::getLocY()
{
  return curLocY;
}

/*
 * Getter for the current heading
 * Input: None
 * Return: Current heading
 */
int Navigation::getCurrDirec()
{
  return curDirec;
}

/*
 * Print out the flood fill array
 * Input: None
 * Return: None
 */
void Navigation::printFloodfillMap()
{
  for(int i=0; i<BOARD_MAX; i++)
  {
    for(int j=0; j<BOARD_MAX; j++)
    {
      printf("%03d ", floodfill[i][j]);
    }
    printf("\n");
  }
}
