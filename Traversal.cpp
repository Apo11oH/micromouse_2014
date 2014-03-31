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
  for(int i=0; i<CELL_MAX; i++)
  {
    nodes[i] = new Node(i);
  }
  // Initialize start cell by setting the wall in E, S, and W 
  // 1 1 1 0 1 1 1 0 
  node[CELL_MAX-BOARD_MAX]->setWall(1, DIR_EAST);
  node[CELL_MAX-BOARD_MAX]->setWall(1, DIR_SOUTH);
  node[CELL_MAX-BOARD_MAX]->setWall(1, DIR_WEST);
}

/*
 * Checks the sensor values to see if there is a wall or not and record
 * the result. Based on the values, either calls setWall or setSeen.
 * Input: int curDirec - current direction that the bot is facing
 *        int fSen - front sensor value 
 *        int rSen - right sensor value 
 *        int lSen - left sensor value 
 *        int index - current node index 
 * Return: None
 */
void evalNode(int curDirec, int fSen, int rSen, int lSen, int index);

/*
 * Print information regarding a specific traversal cell
 * Input: int i - node index 
 * Return: None
 */
void printTraversalVal(int i);
