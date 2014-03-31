#include <stdio.h>
#include <iostream>
#include "BotConstants.hpp"
#include "Traversal.hpp"
#include "gtest/gtest.h"

using namespace BotConsts;

TEST(Traversal, DefaultConstructor)
{
    unsigned pat = 0x0E;
    Traversal *traversal = new Traversal();
    traversal->initTraversal();
    for(int i=0; i<CELL_MAX; i++)
    {
        ASSERT_EQ(256, (traversal->getNode(i))->getCost());
    }
    // Checking x coordinate of start position
    ASSERT_EQ(0, (CELL_MAX-BOARD_MAX)%BOARD_MAX);
    // Checking y coordinate of start position
    ASSERT_EQ(15, (CELL_MAX-BOARD_MAX)/BOARD_MAX);
    ASSERT_EQ(pat, (traversal->getNode(CELL_MAX-BOARD_MAX))->getWallPat());
}

TEST(Traversal, setWallAt_1_1_WhenDirecNorth)
{
    int i = 1*BOARD_MAX+1;
    unsigned pat = 0x09;
    Traversal *traversal = new Traversal();
    traversal->initTraversal();

    // Set wall in North and West (00001001)
    traversal->evalNodeWall(DIR_NORTH, FRONT_THRESH+1, RIGHT_THRESH-1, 
            LEFT_THRESH+1, i);
    ASSERT_EQ(pat, traversal->getNode(i)->getWallPat());
}

TEST(Traversal, setWallAt_0_0_WhenDirecNorth)
{
    int i = 0*BOARD_MAX+0;
    unsigned pat = 0x0B;
    Traversal *traversal = new Traversal();
    traversal->initTraversal();

    // Set wall in North, East, and West (00001011)
    traversal->evalNodeWall(DIR_NORTH, FRONT_THRESH+1, RIGHT_THRESH+1, 
            LEFT_THRESH+1, i);
    ASSERT_EQ(pat, traversal->getNode(i)->getWallPat());
}

TEST(Traversal, setWallAt_1_1_WhenDirecEast)
{
    int i = 1*BOARD_MAX+1;
    unsigned pat = 0x03;
    Traversal *traversal = new Traversal();
    traversal->initTraversal();

    // Set wall in North and East (00000011)
    traversal->evalNodeWall(DIR_EAST, FRONT_THRESH+1, RIGHT_THRESH-1, 
            LEFT_THRESH+1, i);
    ASSERT_EQ(pat, traversal->getNode(i)->getWallPat());
}

TEST(Traversal, setWallAt_MAX_1_WhenDirecEast)
{
    int i = 1*BOARD_MAX+(BOARD_MAX-1);
    unsigned pat = 0x03;
    Traversal *traversal = new Traversal();
    traversal->initTraversal();

    // Make sure index is correct
    ASSERT_EQ(BOARD_MAX-1, i%BOARD_MAX);
    ASSERT_EQ(1, i/BOARD_MAX);

    // Set wall in North and East (00000011)
    traversal->evalNodeWall(DIR_EAST, FRONT_THRESH+1, RIGHT_THRESH-1, 
            LEFT_THRESH+1, i);
    ASSERT_EQ(pat, traversal->getNode(i)->getWallPat());
}

TEST(Traversal, setWallAt_1_1_WhenDirecSouth)
{
    int i = 1*BOARD_MAX+1;
    unsigned pat = 0x0E;
    Traversal *traversal = new Traversal();
    traversal->initTraversal();

    // Set wall in South, East, and West (00001110)
    traversal->evalNodeWall(DIR_SOUTH, FRONT_THRESH+1, RIGHT_THRESH+1, 
            LEFT_THRESH+1, i);
    ASSERT_EQ(pat, traversal->getNode(i)->getWallPat());
}

TEST(Traversal, setWallAt_1_MAX_WhenDirecSouth)
{
    int i = (BOARD_MAX-1)*BOARD_MAX+1;
    unsigned pat = 0x06;
    Traversal *traversal = new Traversal();
    traversal->initTraversal();

    // Make sure index is correct
    ASSERT_EQ(1, i%BOARD_MAX);
    ASSERT_EQ(BOARD_MAX-1, i/BOARD_MAX);

    // Set wall in South and East (00000110)
    traversal->evalNodeWall(DIR_SOUTH, FRONT_THRESH+1, RIGHT_THRESH-1, 
            LEFT_THRESH+1, i);
    ASSERT_EQ(pat, traversal->getNode(i)->getWallPat());
}

TEST(Traversal, setWallAt_1_1_WhenDirecWest)
{
    int i = 1*BOARD_MAX+1;
    unsigned pat = 0x05;
    Traversal *traversal = new Traversal();
    traversal->initTraversal();

    // Set wall in North, and South (00000101)
    traversal->evalNodeWall(DIR_WEST, FRONT_THRESH-1, RIGHT_THRESH+1, 
            LEFT_THRESH+1, i);
    ASSERT_EQ(pat, traversal->getNode(i)->getWallPat());
}

TEST(Traversal, setWallAt_0_1_WhenDirecWest)
{
    int i = 1*BOARD_MAX+0;
    unsigned pat = 0x0D;
    Traversal *traversal = new Traversal();
    traversal->initTraversal();

    // Set wall in South, West, and North (00001101)
    traversal->evalNodeWall(DIR_WEST, FRONT_THRESH+1, RIGHT_THRESH+1, 
            LEFT_THRESH+1, i);
    ASSERT_EQ(pat, traversal->getNode(i)->getWallPat());
}
