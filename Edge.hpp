/*
 * EDGE HEADER
 * Definition of the edges used by the nodes
 */

#ifndef EDGE_HPP
#define EDGE_HPP

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
    /*
     * Default constructor
     */
    Edge():from(-1),to(-1),cost(256),checked(false){}

    /*
     * Constructor with "from" and "to" nodes specified
     */
    Edge(int f, int t):from(f),to(t),cost(256),checked(false){}

    /*
     * Constructor with "from" and "to" nodes specified and cost assigned
     */
    Edge(int f, int t, int c):from(f),to(t),cost(c),checked(false){}

    /*
     * Returns the index of the "to" node (overloaded)
     */
    int getTo() const { return to; }

    /*
     * Returns the index of the "to" node (overloaded)
     */
    int getTo(int f) const { return to; }

    /*
     * Returns the index of the "from" node 
     */
    int getFrom() const { return from; }

    /*
     * Returns the cost of the node
     */
    int getCost() const { return cost; }

    /*
     * Sets a cost of the node
     */
    void setCost(int c) { cost = c; }

    /*
     * Checks if the node has already been traversed
     */
    bool isChecked() const { return checked; }

    /*
     * Sets the new checked flag
     */
    void setChecked(bool c){ checked = c; }
};

#endif 
