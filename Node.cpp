/*
 * NODE CLASS
 * Actual implementations of the node functions
 */

#include <vector>
#include "BotConstants.hpp"
#include "Edge.hpp"
#include "Node.hpp"

using namespace std;
using namespace BotConsts;

/*
 * Destructor for the node
 */
Node::~Node(){
}

/*
 * Adds the edges to the adjacent nodes
 * Input: e - edge to be added
 * Output: Nothing
 */
void Node::addEdge(Edge* e){
  edges.push_back(e);
}

/*
 * Sets the wall in the given direction
 * Input: b - new bit
 *        dir - direction
 * Output: Nothing
 */
void Node::setWall(unsigned b, int dir)
{
  switch(dir)
  {
    case DIR_NORTH: wall.NORTH = b; break;
    case DIR_EAST: wall.EAST = b; break;
    case DIR_SOUTH: wall.SOUTH = b; break;
    case DIR_WEST: wall.WEST = b; break;
  }
}

/*
 * Get the wall value in the given direction
 * Input: dir - direction
 * Output: wall value of the given direction 
 */
unsigned Node::getWall(int dir)
{
  switch(dir)
  {
    case DIR_NORTH: return wall.NORTH;
    case DIR_EAST: return wall.EAST;
    case DIR_SOUTH: return wall.SOUTH;
    case DIR_WEST: return wall.WEST;
    default: return -1;
  }
}
