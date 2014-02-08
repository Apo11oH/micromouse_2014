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

void Graph::printGraph()
{
  cout << "Graph map" << endl << endl;
  for(int i=0; i<BOARD_MAX*BOARD_MAX; i++)
  {
    //nodes[i]->getIndex(BOARD_MAX*BOARD_MAX);
    if(i%BOARD_MAX == 0){ cout << endl; } 
  }
}
