/*
 * NAVIGATION
 * Figure out which direction to move next
 */

#ifndef NAV_HPP
#define NAV_HPP

#include "BotConstants.hpp"
#include "Traversal.hpp"

using namespace BotConsts;

class Navigation{
    private:
      int floodfill[BOARD_MAX][BOARD_MAX];
      int curLocX;
      int curLocY;
      int curDirec;
      int nxtDirec;
      int turnAmt;

    public:
      /*
       * Default constructor
       */
      Navigation():curLocX(0),curLocY(BOARD_MAX-1),curDirec(0),nxtDirec(0){}

      /*
       * Initialize floodfill matrix for finding the goal
       * Input: None
       * Return: None
       */
      void initNaviGoal();

      /*
       * Initialize floodfill matrix for getting back to the starting point 
       * Input: None
       * Return: None
       */
      void initNavHoming();

      /*
       * Update the floodfill map based on the current recorded maze
       * Input: Traversal - trav
       * Return: None
       */
      void updateFloodfill(Traversal trav);

      /*
       * Based on the floodfill map, determine which direction to move next.
       * Low potential value have priority.
       * Input: int trav - traversal value at (x, y)
       * Return: Next direction we have to go. (0,1,2,3)=(N,E,S,W)
       */
      int findNextDirec(int trav);

      /*
       * Based on the current direction and the next direction we have to move,
       * calculate how many degrees we have to turn (or not)
       * Input: int curDirec - current direction. (0,1,2,3)=(N,E,S,W)
       *        int nxtDirec - next direction (0,1,2,3)=(N,E,S,W)
       * Return: 
       */
      int chooseTurn();

      /*
       * Update direction of the droid
       * Input:
       * Return:
       */
      void updateDirec();

      /*
       * Update the coordinates for the bot based on the direction we have
       * chosen to go next
       * Input: 
       * Return: 
       */
      void updateLoc();

      /*
       * Update all relavent information and figure out which direction to move next
       * Input: int trav - traversal value (wall information) of the cell we're checking
       * Return: amount the droid needs to move to arrive at next direction
       */
      int makeMove(int trav);

      /*
       * Getter for the current x-coordinate
       * Input: None
       * Return: Current x-coordinate
       */
      int getLocX();

      /*
       * Getter for the current y-coordinate
       * Input: None
       * Return: Current y-coordinate
       */
      int getLocY();

      /*
       * Getter for the current heading
       * Input: None
       * Return: Current heading
       */
      int getCurrDirec();

      /*
       * Print out the flood fill array
       * Input: None
       * Return: None
       */
      void printFloodfillMap();
};

#endif
