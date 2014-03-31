/*
 * TRAVERSAL RELATED
 * Keeps track of cells we have traveled and sets wall information
 */
#include <iostream>
#include "Traversal.hpp"
#include "BotConstants.hpp"
#include "Node.hpp"

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
    nodes.push_back(new Node(i));
  }
  // Initialize start cell by setting the wall in E, S, and W 
  // 0 0 0 0 1 1 1 0 
  nodes[CELL_MAX-BOARD_MAX]->setWall(1, DIR_EAST);
  nodes[CELL_MAX-BOARD_MAX]->setWall(1, DIR_SOUTH);
  nodes[CELL_MAX-BOARD_MAX]->setWall(1, DIR_WEST);
}

/*
 * Checks the sensor values to see if there is a wall or not and record
 * the result. Based on the values, either calls setWall or setSeen.
 * Input: int bDir - current direction that the bot is facing
 *        int fSen - front sensor value 
 *        int rSen - right sensor value 
 *        int lSen - left sensor value 
 *        int i - current node index 
 * Return: None
 */
void Traversal::evalNodeWall(int bDir, int fSen, int rSen, int lSen, int i)
{
  switch(bDir)
  {
    case DIR_NORTH: 
      if(fSen > FRONT_THRESH) { nodes[i]->setWall(1, DIR_NORTH); }
      if(rSen > RIGHT_THRESH) { nodes[i]->setWall(1, DIR_EAST); } 
      if(lSen > LEFT_THRESH) { nodes[i]->setWall(1, DIR_WEST); } 
      break;
    case DIR_EAST: 
      if(fSen > FRONT_THRESH) { nodes[i]->setWall(1, DIR_EAST); }
      if(rSen > RIGHT_THRESH) { nodes[i]->setWall(1, DIR_SOUTH); } 
      if(lSen > LEFT_THRESH) { nodes[i]->setWall(1, DIR_NORTH); } 
      break;
    case DIR_SOUTH: 
      if(fSen > FRONT_THRESH) { nodes[i]->setWall(1, DIR_SOUTH); }
      if(rSen > RIGHT_THRESH) { nodes[i]->setWall(1, DIR_WEST); } 
      if(lSen > LEFT_THRESH) { nodes[i]->setWall(1, DIR_EAST); } 
      break;
    case DIR_WEST: 
      if(fSen > FRONT_THRESH) { nodes[i]->setWall(1, DIR_WEST); }
      if(rSen > RIGHT_THRESH) { nodes[i]->setWall(1, DIR_NORTH); } 
      if(lSen > LEFT_THRESH) { nodes[i]->setWall(1, DIR_SOUTH); } 
      break;
    default: break;
  }
  nodes[i]->setChecked(true);
}

/*
 * Print the node cost used in the floodfill algorithm 
 * Input: Nothing 
 * Return: Nothing 
 */
void Traversal::printFloodFillCost()
{
  for(int i=0; i<CELL_MAX; i++)
  {
    if(i>0 && (i%BOARD_MAX == 0)){ cout << endl; } 
    printf("%4d", nodes[i]->getCost());
  }
  printf("\n");
}

/*
 * Print the wall value for each node
 * Input: Nothing 
 * Return: Nothing 
 */
void Traversal::printAllWalls()
{
  for(int i=0; i<CELL_MAX; i++)
  {
    if(i>0 && (i%BOARD_MAX == 0)){ cout << endl; } 
    printf("%4x", nodes[i]->getWallPat());
  }
  printf("\n");
}
