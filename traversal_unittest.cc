#include <stdio.h>
#include <iostream>
#include "BotConstants.hpp"
#include "Traversal.hpp"
#include "gtest/gtest.h"

using namespace BotConsts;

TEST(Traversal, DefaultConstructor)
{
    Traversal *traversal = new Traversal();
    traversal->initTraversal();
    ASSERT_EQ(0x00, traversal->getTraversalVal(0, 0));
    ASSERT_EQ(0xEE, traversal->getTraversalVal(0, BOARD_MAX-1)); 
}



TEST(Traversal, setWallAt_1_1_WhenDirecNorth)
{
    int direc = 0;
    Traversal *traversal = new Traversal();
    traversal->initTraversal();

    traversal->setWall(direc, 1, 1);
    
    ASSERT_EQ(0x11, traversal->getTraversalVal(1, 1)); 
    ASSERT_EQ(0x44, traversal->getTraversalVal(1, 0)); 
}

TEST(Traversal, setWallAt_0_0_WhenDirecNorth)
{
    int direc = 0;
    Traversal *traversal = new Traversal();
    traversal->initTraversal();

    traversal->setWall(direc, 0, 0);
    
    ASSERT_EQ(0x11, traversal->getTraversalVal(0, 0));
    ASSERT_EQ(0x00, traversal->getTraversalVal(0, 1));
}


TEST(Traversal, setWallAt_1_1_WhenDirecEast)
{
    int direc = 1;
    Traversal *traversal = new Traversal();
    traversal->initTraversal();

    traversal->setWall(direc, 1, 1);
    
    ASSERT_EQ(0x22, traversal->getTraversalVal(1, 1));
    ASSERT_EQ(0x88, traversal->getTraversalVal(2, 1));
}

TEST(Traversal, setWallAt_MAX_1_WhenDirecEast)
{
    int direc = 1;
    Traversal *traversal = new Traversal();
    traversal->initTraversal();

    traversal->setWall(direc, BOARD_MAX-1, 1);
    
    ASSERT_EQ(0x22, traversal->getTraversalVal(BOARD_MAX-1, 1));
}

TEST(Traversal, setWallAt_1_1_WhenDirecSouth)
{
    int direc = 2;
    Traversal *traversal = new Traversal();
    traversal->initTraversal();

    traversal->setWall(direc, 1, 1);
    
    ASSERT_EQ(0x44, traversal->getTraversalVal(1, 1));
    ASSERT_EQ(0x11, traversal->getTraversalVal(1, 2));
}

TEST(Traversal, setWallAt_1_MAX_WhenDirecSouth)
{
    int direc = 2;
    Traversal *traversal = new Traversal();
    traversal->initTraversal();

    traversal->setWall(direc, 1, BOARD_MAX-1);
    
    ASSERT_EQ(0x44, traversal->getTraversalVal(1, BOARD_MAX-1));
}

TEST(Traversal, setWallAt_1_1_WhenDirecWest)
{
    int direc = 3;
    Traversal *traversal = new Traversal();
    traversal->initTraversal();

    traversal->setWall(direc, 1, 1);
    
    ASSERT_EQ(0x88, traversal->getTraversalVal(1, 1));
    ASSERT_EQ(0x22, traversal->getTraversalVal(0, 1));
}

TEST(Traversal, setWallAt_0_1_WhenDirecWest)
{
    int direc = 3;
    Traversal *traversal = new Traversal();
    traversal->initTraversal();

    traversal->setWall(direc, 0, 1);
    
    ASSERT_EQ(0x88, traversal->getTraversalVal(0, 1));
}

