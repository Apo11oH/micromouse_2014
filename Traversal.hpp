/*
 * TRAVERSAL HEADER
 * The Traversal class will keep track of the cells we have traveled and record 
 * the necessary wall information.
 */

#ifndef TRAV_HPP
#define TRAV_HPP

#include <vector>
#include "BotConstants.hpp"
#include "Node.hpp"

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
     *
     * (x, y) -> index:
     *    index = y * BOARD_MAX + x
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
     * Input: int bDir - current direction that the bot is facing
     *        int fSen - front sensor value 
     *        int rSen - right sensor value 
     *        int lSen - left sensor value 
     *        int i - current node index 
     * Return: None
     */
    void evalNodeWall(int bDir, int fSen, int rSen, int lSen, int i);

    /*
     * Return the traversal map
     * Input: Nothing
     * Output: The Traversal map
     */
    const vector<Node*> &getTraversalMap() const { return nodes; }

    /*
     * Returns node at the specified index
     * Input: int i - index of the node
     * Output: The node
     */
    Node* getNode(int i) { return nodes[i]; }

    /*
     * Print the node cost used in the floodfill algorithm 
     * Input: Nothing 
     * Return: Nothing 
     */
    void printFloodFillCost();

    /*
     * Print the wall value for each node
     * Input: Nothing 
     * Return: Nothing 
     */
    void printAllWalls();
};

#endif
