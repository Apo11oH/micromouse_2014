/*
 * Dijkstra's Algoithm implementation
 */

#include <queue>
#include "BotConstants.hpp"
#include "Traversal.hpp"
#include "Navigation.hpp"

using namespace std;
using namespace BotConsts;

/*
 * Comparitor override for the priority_queue used when comparing edges
 */
class EdgeCostCmp
{
  public:
    bool operator()(Edge* edge1, Edge* edge2)
    {
      return edge1->getCost() > edge2->getCost();
    }
}

/*
 * Run Dijkstra's Algorithm on a board represented as a matix
 * Input:  
 * Output: 
 */
void dijkstraMatrix(Traversal trav, Navigation nav){ 
  int dist[BOARD_MAX][BOARD_MAX];
  int previous[BOARD_MAX][BOARD_MAX];

  for(int i=0; i<BOARD_MAX; i++){
    for(int j=0; j<BOARD_MAX; j++){
      dist[i][j] = BOARD_MAX*BOARD_MAX;
      previous[i][j] = BOARD_MAX*BOARD_MAX;
    }
  }

  dist[BOARD_MAX-1][0] = 0;

}

/*
 * Run Dijkstra's Algorithm on a board represented as a graph 
 * Input:  
 * Output: 
 */
int dijkstraGraph(Node* start)
{
  priority_queue<Node*, vector<Node*>, VertexDistCmp> pQueue;

  return 0;
}
