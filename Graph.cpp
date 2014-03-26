/*
 * GRAPH CLASS 
 * Used to create a graph of the map based on the wall information and 
 * to calculate the shortest path.
 */

#include <iostream>
#include <vector>
#include "BotConstants.hpp"
#include "Graph.hpp"

using namespace std;
using namespace BotConsts;

/*
class Edge{
  private:
    Node fNode;
    Node tNode;
    int weight;

  public:
    Edge(Node from, Node to,int cost):fNode(from), tNode(to), weight(cost){}
    Edge():fNode(NULL), tNode(NULL), weight(0){}
    int getWeight(){ return weight; }
    Node getFrom(){ return fNode; }
    Node getTo(){ return tNode; }
}
*/

void Graph::mtxToGraph()
{

}

/*
 * Check how many cells the bot can move till it reaches a cell where it can 
 * change direction
 * Input: 
 * Output: 
 */
int Graph::checkNextTurn(int cur_x, int cur_y, int dir, Traversal trav){
  int count = 0;
  int x_wk = cur_x;
  int y_wk = cur_y;
  int mask;
  int inc_x;
  int inc_y;

  // Determine mask to use based on the current direction
  switch(dir){
    case 0: mask = 0xFB; inc_x=0; inc_y=-1; break; //1011
    case 1: mask = 0xF7; inc_x=1; inc_y=0; break; //0111
    case 2: mask = 0xFE; inc_x=0; inc_y=1; break; //1110
    case 3: mask = 0xFD; inc_x=-1; inc_y=0; break; //1101
  }

  // Calculate number of cells
  while((trav.getTraversalVal(x_wk, y_wk)&0x0F) == mask){
    x_wk += inc_x;
    y_wk += inc_y;
    count++;
  }

  return count;
}

void Graph::printGraph()
{
  cout << "Graph map" << endl << endl;
  for(int i=0; i<BOARD_MAX*BOARD_MAX; i++)
  {
    //nodes[i]->getIndex(BOARD_MAX*BOARD_MAX);
    if(i%BOARD_MAX == 0){ cout << endl; } 
  }
}
