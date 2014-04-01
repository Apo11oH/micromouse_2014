#include <stdio.h>
#include <iostream>
#include "BotConstants.hpp"
#include "Floodfill.hpp"
#include "gtest/gtest.h"

using namespace BotConsts;

TEST(Floodfill, DefaultConstructor)
{
    unsigned pat = 0x0E;
    Floodfill *floodfill = new Floodfill();
    floodfill->initFloodfill();
    for(int i=0; i<CELL_MAX; i++)
    {
        if( !(i == 119 || i == 120 || i == 135 || i == 136) )
            ASSERT_EQ(256, (floodfill->getNode(i))->getCost());
    }
    // Checking x coordinate of start position
    ASSERT_EQ(0, (CELL_MAX-BOARD_MAX)%BOARD_MAX);
    // Checking y coordinate of start position
    ASSERT_EQ(15, (CELL_MAX-BOARD_MAX)/BOARD_MAX);
    ASSERT_EQ(pat, (floodfill->getNode(CELL_MAX-BOARD_MAX))->getWallPat());
    //floodfill->printFloodfillCost();
    //floodfill->printAllWalls();
    //floodfill->printEdgeCount();
}

TEST(Floodfill, setWallAt_1_1_WhenDirecNorth)
{
    int i = 1*BOARD_MAX+1;
    unsigned pat = 0x09;
    Floodfill *floodfill = new Floodfill();
    floodfill->initFloodfill();

    // Set wall in North and West (00001001)
    floodfill->evalNodeWall(DIR_NORTH, FRONT_THRESH+1, RIGHT_THRESH-1, 
            LEFT_THRESH+1, i);
    ASSERT_EQ(pat, floodfill->getNode(i)->getWallPat());
    //floodfill->printAllWalls();
}

TEST(Floodfill, setWallAt_0_0_WhenDirecNorth)
{
    int i = 0*BOARD_MAX+0;
    unsigned pat = 0x0B;
    Floodfill *floodfill = new Floodfill();
    floodfill->initFloodfill();

    // Set wall in North, East, and West (00001011)
    floodfill->evalNodeWall(DIR_NORTH, FRONT_THRESH+1, RIGHT_THRESH+1, 
            LEFT_THRESH+1, i);
    ASSERT_EQ(pat, floodfill->getNode(i)->getWallPat());
    //floodfill->printAllWalls();
}

TEST(Floodfill, setWallAt_1_1_WhenDirecEast)
{
    int i = 1*BOARD_MAX+1;
    unsigned pat = 0x03;
    Floodfill *floodfill = new Floodfill();
    floodfill->initFloodfill();

    // Set wall in North and East (00000011)
    floodfill->evalNodeWall(DIR_EAST, FRONT_THRESH+1, RIGHT_THRESH-1, 
            LEFT_THRESH+1, i);
    ASSERT_EQ(pat, floodfill->getNode(i)->getWallPat());
    //floodfill->printAllWalls();
}

TEST(Floodfill, setWallAt_MAX_1_WhenDirecEast)
{
    int i = 1*BOARD_MAX+(BOARD_MAX-1);
    unsigned pat = 0x03;
    Floodfill *floodfill = new Floodfill();
    floodfill->initFloodfill();

    // Make sure index is correct
    ASSERT_EQ(BOARD_MAX-1, i%BOARD_MAX);
    ASSERT_EQ(1, i/BOARD_MAX);

    // Set wall in North and East (00000011)
    floodfill->evalNodeWall(DIR_EAST, FRONT_THRESH+1, RIGHT_THRESH-1, 
            LEFT_THRESH+1, i);
    ASSERT_EQ(pat, floodfill->getNode(i)->getWallPat());
    //floodfill->printAllWalls();
}

TEST(Floodfill, setWallAt_1_1_WhenDirecSouth)
{
    int i = 1*BOARD_MAX+1;
    unsigned pat = 0x0E;
    Floodfill *floodfill = new Floodfill();
    floodfill->initFloodfill();

    // Set wall in South, East, and West (00001110)
    floodfill->evalNodeWall(DIR_SOUTH, FRONT_THRESH+1, RIGHT_THRESH+1, 
            LEFT_THRESH+1, i);
    ASSERT_EQ(pat, floodfill->getNode(i)->getWallPat());
    //floodfill->printAllWalls();
}

TEST(Floodfill, setWallAt_1_MAX_WhenDirecSouth)
{
    int i = (BOARD_MAX-1)*BOARD_MAX+1;
    unsigned pat = 0x06;
    Floodfill *floodfill = new Floodfill();
    floodfill->initFloodfill();

    // Make sure index is correct
    ASSERT_EQ(1, i%BOARD_MAX);
    ASSERT_EQ(BOARD_MAX-1, i/BOARD_MAX);

    // Set wall in South and East (00000110)
    floodfill->evalNodeWall(DIR_SOUTH, FRONT_THRESH+1, RIGHT_THRESH-1, 
            LEFT_THRESH+1, i);
    ASSERT_EQ(pat, floodfill->getNode(i)->getWallPat());
    //floodfill->printAllWalls();
}

TEST(Floodfill, setWallAt_1_1_WhenDirecWest)
{
    int i = 1*BOARD_MAX+1;
    unsigned pat = 0x05;
    Floodfill *floodfill = new Floodfill();
    floodfill->initFloodfill();

    // Set wall in North, and South (00000101)
    floodfill->evalNodeWall(DIR_WEST, FRONT_THRESH-1, RIGHT_THRESH+1, 
            LEFT_THRESH+1, i);
    ASSERT_EQ(pat, floodfill->getNode(i)->getWallPat());
    //floodfill->printAllWalls();
}

TEST(Floodfill, setWallAt_0_1_WhenDirecWest)
{
    int i = 1*BOARD_MAX+0;
    unsigned pat = 0x0D;
    Floodfill *floodfill = new Floodfill();
    floodfill->initFloodfill();

    // Set wall in South, West, and North (00001101)
    floodfill->evalNodeWall(DIR_WEST, FRONT_THRESH+1, RIGHT_THRESH+1, 
            LEFT_THRESH+1, i);
    ASSERT_EQ(pat, floodfill->getNode(i)->getWallPat());
    //floodfill->printAllWalls();
}

TEST(Floodfill, update_node_edges)
{
    int i = 1*BOARD_MAX+1;
    Floodfill *floodfill = new Floodfill();
    floodfill->initFloodfill();
    ASSERT_EQ(4, (floodfill->getNode(i)->getEdges()).size());
    // Set wall in South, West, and North (00001101)
    floodfill->evalNodeWall(DIR_WEST, FRONT_THRESH+1, RIGHT_THRESH+1, 
            LEFT_THRESH+1, i);
    floodfill->updateNodeEdges(i);
    ASSERT_EQ(1, (floodfill->getNode(i)->getEdges()).size());
}
