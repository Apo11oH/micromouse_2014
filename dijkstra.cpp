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
 * Check how many cells the bot can move till it reaches a cell where it can 
 * change direction
 * Input: 
 * Output: 
 */
int checkNextTurn(int cur_x, int cur_y, int dir, Traversal trav){
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
