/*
 * Floodfill RELATED
 * Keeps track of cells we have traveled and sets wall information
 */
#include <iostream>
#include "Floodfill.hpp"
#include "BotConstants.hpp"
#include "Edge.hpp"
#include "Node.hpp"

using namespace BotConsts;

/*
 * Initializes the floodfill map
 * Input: None
 * Return: None
 */
void Floodfill::initFloodfill()
{
  for(int i=0; i<CELL_MAX; i++)
  {
    Node* n = new Node(i);
    // add north edge
    if((i/BOARD_MAX) > 0) 
    { 
      n->addEdge(new Edge(i, i-BOARD_MAX)); 
    }
    // add east edge
    if((i%BOARD_MAX) != (BOARD_MAX-1)) 
    { 
      n->addEdge(new Edge(i, i+1)); 
    }
    // add south edge
    if((i+BOARD_MAX) <= CELL_MAX) 
    { 
      n->addEdge(new Edge(i, i+BOARD_MAX)); 
    }
    // add west edge
    if((i%BOARD_MAX) != 0) 
    { 
      n->addEdge(new Edge(i, i-1)); 
    }
    nodes.push_back(n);
  }
  // Initialize start cell by setting the wall in E, S, and W 
  // 0 0 0 0 1 1 1 0 
  nodes[CELL_MAX-BOARD_MAX]->setWall(1, DIR_EAST);
  nodes[CELL_MAX-BOARD_MAX]->setWall(1, DIR_SOUTH);
  nodes[CELL_MAX-BOARD_MAX]->setWall(1, DIR_WEST);
  // Initialize the goal cost to 0
  nodes[(CELL_MAX/2-BOARD_MAX) + BOARD_MAX/2]->setCost(0);
  nodes[(CELL_MAX/2-BOARD_MAX) + BOARD_MAX/2 - 1]->setCost(0);
  nodes[CELL_MAX/2 + BOARD_MAX/2]->setCost(0);
  nodes[CELL_MAX/2 + BOARD_MAX/2 - 1]->setCost(0);
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
void Floodfill::evalNodeWall(int bDir, int fSen, int rSen, int lSen, int i)
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
 * Updates the edges for the cell based on the wall information
 * Input: int i - index of the cell
 * Output: Nothing
 */
void Floodfill::updateNodeEdges(int i)
{
  Node* node = nodes[i];
  node->clearAllEdges();
  // check east edge
  if(node->getWall(DIR_NORTH) == 0)
  { 
    if((i/BOARD_MAX) > 0) 
    { 
      node->addEdge(new Edge(i, i-BOARD_MAX)); 
    }
  }
  // check east edge
  if(node->getWall(DIR_EAST) == 0)
  { 
    if((i%BOARD_MAX) != (BOARD_MAX-1)) 
    { 
      node->addEdge(new Edge(i, i+1)); 
    }
  }
  // check south edge
  if(node->getWall(DIR_SOUTH) == 0)
  { 
    if((i+BOARD_MAX) <= CELL_MAX) 
    { 
      node->addEdge(new Edge(i, i+BOARD_MAX)); 
    }
  }
  // check west edge
  if(node->getWall(DIR_WEST) == 0)
  { 
    if((i%BOARD_MAX) != 0) 
    { 
      node->addEdge(new Edge(i, i-1)); 
    }
  }
}

/*
 * Updates the floodfill cost values 
 * Input: Nothing
 * Output: Nothing 
 */
void Floodfill::updateFloodfill()
{

}

/*
 * Print the node cost used in the floodfill algorithm 
 * Input: Nothing 
 * Return: Nothing 
 */
void Floodfill::printFloodfillCost()
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
void Floodfill::printAllWalls()
{
  for(int i=0; i<CELL_MAX; i++)
  {
    if(i>0 && (i%BOARD_MAX == 0)){ cout << endl; } 
    printf("%4x", nodes[i]->getWallPat());
  }
  printf("\n");
}

/*
 * Print the wall value for each node
 * Input: Nothing 
 * Return: Nothing 
 */
void Floodfill::printEdgeCount()
{
  for(int i=0; i<CELL_MAX; i++)
  {
    if(i>0 && (i%BOARD_MAX == 0)){ cout << endl; } 
    printf("%4lu", (nodes[i]->getEdges()).size());
  }
  printf("\n");
}

