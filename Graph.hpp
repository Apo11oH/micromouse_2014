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

class Node{
  private:
    int index;
    vector<Node*> nodes;
    int cost;
    bool checked;

  public:
    Node(int cor, int cost):index(cor), cost(cost){}
    void setIndex(int idx){ index = idx; }
    int getIndex(int idx){ return index; }

};


class Graph{
    private: 
        Node* start;
        vector<Node*> nodes;
        // vector<Edge*> edges;

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


        /*
         * From the traversal matrix, create a graph
         */
        void mtxToGraph();


        void printGraph();

};



#endif
