/*
 * TRAVERSAL HEADER
 * The Traversal class will keep track of the cells we have traveled and record 
 * the necessary wall information.
 */

#ifndef TRAV_HPP
#define TRAV_HPP

#include "BotConstants.hpp"

using namespace BotConsts;

class Traversal{
    private:
        /*
         * The matrix that holds the wall information for the mouse
         * The lower nibble of each byte per cell will contain the wall info
         * and the upper nibble of eacy byte will contain the seen info.
         * The upper nibble will be useful when constructing the shortest path.
         * _ _ _ _ _ _ _ _ 
         * W S E N W S E N
         */
        int traversal[BOARD_MAX][BOARD_MAX];

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
         * Sets the wall and checked bits for a specific direction in the 
         * traversal map for a single cell if it meets the conditon.
         * Input: int setDirec - direction of the wall. 
         *                       0 for N, 1 for E, 2 for S, and 3 for W
         *        int curlocX - current x coordinate
         *        int curlocY - current y coordinate
         * Return: None
         */
        void setWall(int setDirec, int curLocX, int curLocY);

        /*
         * Sets only the checked bits for a specific direction in the 
         * traversal map for a single cell if it meets the conditon.
         * Input: int setDirec - direction of the wall. 
         *                       0 for N, 1 for E, 2 for S, and 3 for W
         *        int curlocX - current x coordinate
         *        int curlocY - current y coordinate
         * Return: None
         */
        void setSeen(int setDirec, int curLocX, int curLocY);

        /*
         * Checks the sensor values to see if there is a wall or not and record
         * the result. Based on the values, either calls setWall or setSeen.
         * Input: int curDirec - current direction that the bot is facing
         *        int fSen - front sensor value 
         *        int rSen - right sensor value 
         *        int lSen - left sensor value 
         *        int curlocX - current x coordinate
         *        int curlocY - current y coordinate
         * Return: None
         */
        void setTraversalMap(int curDirec, int fSen, int rSen, int lSen,
                int curLocX, int curLocY);

        /*
         * If the bot came out of a dead end, it will mark the previously
         * inhabited cell as inaccessible and close it off
         * Input: int curDirec - current direction that the bot is facing
         *        int curlocX - current x coordinate
         *        int curlocY - current y coordinate
         * Return: None
         */
        void plugDeadEnd(int curDirec, int curLocX, int curLocY);

        /*
         * Get the traversal value for a specific location
         * Input: int curlocX - current x coordinate
         *        int curlocY - current y coordinate
         * Return: int value - traversal value for the specified locaction
         */
        int getTraversalVal(int curLocX, int curLocY);

        /*
         * Print information regarding a specific traversal cell
         * Input: int curlocX - current x coordinate
         *        int curlocY - current y coordinate
         * Return: None
         */
        void printTraversalVal(int curLocX, int curLocY);

        /*
         * Print the traversal map at it's current state
         * Input: None
         * Return: None
         */
        void printTraversalMap();

};

#endif
