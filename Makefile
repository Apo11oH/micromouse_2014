# Just a makefile for convenience

CC=g++
CXXFLAGS= -std=c++11 -O2 -g -Wall
LDFLAGS=-g

avengers: Traversal.o Navigation.o Graph.o

testTraversal: Traversal.o
	g++ -isystem ${GTEST_DIR}/include -pthread gtest_main.cc Traversal.o traversal_unittest.cc libgtest.a -o traversal_unittest
	./traversal_unittest

testEdge: Edge.hpp
	g++ -isystem ${GTEST_DIR}/include -pthread gtest_main.cc edge_unittest.cc libgtest.a -o edge_unittest 
	./edge_unittest

testNode: Node.o Edge.hpp
	g++ -isystem ${GTEST_DIR}/include -pthread gtest_main.cc Node.o node_unittest.cc libgtest.a -o node_unittest 
	./node_unittest

Edge.o: Edge.hpp


testNavigation: Navigation.o

Navigation.o: Traversal.o Navigation.hpp 

Traversal.o: Traversal.hpp

Node.o: Edge.o Node.hpp


Graph.o: Graph.hpp

clean: 
	rm -f avengers *.o traversal_unittest edge_unittest navigation_unittest\
		node_unittest
