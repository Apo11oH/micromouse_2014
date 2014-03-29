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

Node::~Node(){
}

void Node::addEdge(Edge* e){

}

Graph::Graph(){
  for(int i=0; i<BOARD_MAX*BOARD_MAX; i++)
  {
    nodes[i]->setIndex(BOARD_MAX*BOARD_MAX);
  }
  start = nodes[(BOARD_MAX-1)*(BOARD_MAX-1) + 0];
}

void Graph::loadMaze(const int[][BOARD_MAX] maze){

}

void dijkstra(int start, int end, bool isSearching){

}

void astar(int start, int end, bool isSearching){

}

const Route getRoute(int start, int end) const{

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
