/*
 * GRAPH HEADER
 * Used to create a graph of the map based on the wall information and 
 * to calculate the shortest path.
 */

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include "BotConstants.hpp"

using namespace std;
using namespace BotConsts;

class Graph{
  private: 
    Node* start;
    vector<Edge*> edges;
    vector<Node*> nodes;

  public:
    /*
     * Default Constructor
     */
    Graph();

    void loadMaze(const int[][BOARD_MAX] maze);
    void dijkstra(int start, int end, bool isSearching);
    void astar(int start, int end, bool isSearching); 
    const Route getRoute(int start, int end) const;
    void printGraph();
};

#endif
