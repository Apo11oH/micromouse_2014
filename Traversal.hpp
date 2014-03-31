/*
 * TRAVERSAL HEADER
 * The Traversal class will keep track of the cells we have traveled and record 
 * the necessary wall information.
 */

#ifndef TRAV_HPP
#define TRAV_HPP

#include <vector>
#include "BotConstants.hpp"

using namespace BotConsts;

class Traversal{
  private:
    /*
     * Vector that holds the nodes for the maze
     * Maze index representation:
     *   0   1   2   3   4  .....   12  13  14  15
     *  16  17  18  19  20  .....   28  29  30  31
     *  | ...................................... |
     *  | ...................................... |
     *  | ...................................... |
     * 240 241 242 243 245  .....  252 253 254 255
     */
    vector<Node*> nodes;

  public:
    /*
     * Default constructor
     */
    Traversal(){}

    /*
     * Initializes the traversal map
     * Input: None
     * Return: None
     */
    void initTraversal();

    /*
     * Checks the sensor values to see if there is a wall or not and record
     * the result. Based on the values, either calls setWall or setSeen.
     * Input: int curDirec - current direction that the bot is facing
     *        int fSen - front sensor value 
     *        int rSen - right sensor value 
     *        int lSen - left sensor value 
     *        int index - current node index 
     * Return: None
     */
    void evalNode(int curDirec, int fSen, int rSen, int lSen, int index);

    /*
     * Return the traversal map
     * Input: Nothing
     * Output: The Traversal map
     */
    const vector<Node*> &getTraversalMap() const { return nodes; }

    /*
     * Print information regarding a specific traversal cell
     * Input: int i - node index 
     * Return: None
     */
    void printTraversalVal(int i);
};

#endif
