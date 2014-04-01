/*
 * NODE HEADER
 * Definition for the node used in the matrix
 */

#ifndef NODE_HPP
#define NODE_HPP

#include <vector>
#include "BotConstants.hpp"
#include "Edge.hpp"

using namespace std;
using namespace BotConsts;

typedef union{
  unsigned bpat:4;
  struct {
    unsigned NORTH:1;
    unsigned EAST:1;
    unsigned SOUTH:1;
    unsigned WEST:1;
  } dir;
} Wall;


class Node{
  private:
    int index;
    vector<Edge*> edges;
    int cost;
    bool checked;
    int from;
    Wall wall;

  public:
    /*
     * Default constructor
     */
    Node():index(-1),cost(256),checked(false),from(-1)
    {
      wall.dir.NORTH = 0;
      wall.dir.EAST = 0;
      wall.dir.SOUTH = 0;
      wall.dir.WEST = 0;
    }

    /*
     * Constructor with index of node and cost specified
     * Input: i - index
     * Output: Nothing
     */
    Node(int i):index(i), cost(256), checked(false), from(-1)
    {
      wall.dir.NORTH = 0;
      wall.dir.EAST = 0;
      wall.dir.SOUTH = 0;
      wall.dir.WEST = 0;
    }
    
    /*
     * Constructor with index of node and cost specified
     * Input: i - index
     *        c - cost
     * Output: Nothing
     */
    Node(int i, int c):index(i), cost(c), checked(false), from(-1)
    {
      wall.dir.NORTH = 0;
      wall.dir.EAST = 0;
      wall.dir.SOUTH = 0;
      wall.dir.WEST = 0;
    }

    /*
     * Destructor for the node
     */
    ~Node();

    /*
     * Returns the index of the node
     * Input: Nothing
     * Output: index of the node
     */
    int getIndex() const { return index; }

    /*
     * Adds the edges to the adjacent nodes
     * Input: e - edge to be added
     * Output: Nothing
     */
    void addEdge(Edge* e);

    /*
     * Clears all edges from the vector 
     * Input: Nothing
     * Output: Nothing
     */
    void clearAllEdges() { edges.clear(); }

    /*
     * Returns the list of all connected edges
     * Input: Nothing
     * Output: List of all edges
     */
    vector<Edge*> getEdges() { return edges; }

    /*
     * Get the cost of the node
     * Input: Nothing
     * Output: cost of the node
     */
    int getCost() const { return cost; }

    /*
     * Set a new cost to the node
     * Input: c - new cost
     * Output: Nothing
     */
    void setCost(int c) { cost = c; }
    
    /*
     * Get the checked flag
     * Input: Nothing
     * Output: checked flag
     */
    bool isChecked() const { return checked; }

    /*
     * Set the checked flag
     * Input: c - new checked flag value
     * Output: Nothing
     */
    void setChecked(bool c) { checked = c; }

    /*
     * Gets the "from" node
     * Intput: Nothing
     * Output: index of the from node
     */
    int getFrom() const { return from; }

    /*
     * Sets the "from" node
     * Input: f - index of the from node
     * Output: Nothing
     */
    void setFrom(int f) { from = f; }

    /*
     * Sets the wall in the given direction
     * Input: b - new bit
     *        dir - direction
     * Output: Nothing
     */
    void setWall(unsigned b, int dir);

    /*
     * Get the wall value in the given direction
     * Input: dir - direction
     * Output: wall value of the given direction 
     */
    unsigned getWall(int dir);

    /*
     * Get the wall pattern
     * Input: Nothing
     * Output: The wall pattern
     */
    unsigned getWallPat() { return wall.bpat; }
};

#endif
