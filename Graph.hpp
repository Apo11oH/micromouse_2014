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

class Edge{
  private:
    int from;
    int to;
    int cost;
    bool checked;

  public:
    Edge():from(-1),to(-1),cost(256),checked(false){}
    Edge(int f, int t):from(f),to(t),cost(256),checked(false){}
    Edge(int f, int t, int c):from(f),to(t),cost(c),checked(false){}

    int getTo(int f) const { return to; }
    int getCost() const { return cost; }
    void setCost(int c) { cost = c; }
    bool isChecked() const { return checked; }
    void setChecked(bool c){ checked = c; }
}

class Node{
  private:
    int index;
    vector<Edge*> edges;
    int cost;
    bool checked;
    int from;

  public:
    Node():index(-1),cost(256),checked(false),from(-1){}
    Node(int i, int c):index(i), cost(c){}
    ~Node();

    int getIndex() const { return index; }
    void addEdge(Edge* e);
    const vector<Edge*> &getEdges() const { return edges; }
    int getCost() const { return cost; }
    void setCost(int c) { cost = c; }
    bool getChecked() const { return checked; }
    void setChecked(bool c) { checked = c; }
    int getFrom() const { return from; }
    void setFrom(int f) { from = f; }
};


class Graph{
  private: 
    Node* start;
    vector<Edge*> edges;
    vector<Node*> nodes;

  public:
    /*
     * Default Constructor
     */
    Graph()
    {
      for(int i=0; i<BOARD_MAX*BOARD_MAX; i++)
      {
        nodes[i]->setIndex(BOARD_MAX*BOARD_MAX);
      }
      start = nodes[(BOARD_MAX-1)*(BOARD_MAX-1) + 0];
    }

    void loadMaze(const int[][BOARD_MAX] maze);
    void dijkstra(int start, int end, bool isSearching);
    void astar(int start, int end, bool isSearching); 
    const Route getRoute(int start, int end) const;
    void printGraph();
};



#endif
