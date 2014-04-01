# Just a makefile for convenience

CC=g++
CXXFLAGS= -std=c++11 -O2 -g -Wall
LDFLAGS=-g

avengers: Floodfill.o Navigation.o Graph.o

testAll: testEdge testNode testFloodfill 

testNavigation: Navigation.o

testFloodfill: Floodfill.o
	g++ -isystem ${GTEST_DIR}/include -pthread gtest_main.cc Node.o\
		Floodfill.o floodfill_unittest.cc libgtest.a -o floodfill_unittest
	./floodfill_unittest

testEdge: Edge.hpp
	g++ -isystem ${GTEST_DIR}/include -pthread gtest_main.cc\
		edge_unittest.cc libgtest.a -o edge_unittest 
	./edge_unittest

testNode: Node.o Edge.hpp
	g++ -isystem ${GTEST_DIR}/include -pthread gtest_main.cc Node.o\
		node_unittest.cc libgtest.a -o node_unittest 
	./node_unittest

Edge.o: Edge.hpp


Navigation.o: Floodfill.o Navigation.hpp 

Floodfill.o: Node.o Floodfill.hpp

Node.o: Edge.o Node.hpp

Graph.o: Graph.hpp

clean: 
	rm -f avengers *.o floodfill_unittest edge_unittest navigation_unittest\
		node_unittest
