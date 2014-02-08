# Just a makefile for convenience

CC=g++
CXXFLAGS= -std=c++11 -O2 -g -Wall
LDFLAGS=-g

avengers: Traversal.o Navigation.o Graph.o

testTraversal: Traversal.o
	g++ -isystem ${GTEST_DIR}/include -pthread gtest_main.cc Traversal.o traversal_unittest.cc libgtest.a -o traversal_unittest

testNavigation: Navigation.o

Traversal.o: Traversal.hpp

Navigation.o: Navigation.hpp

Graph.o: Graph.hpp

clean: 
	rm -f avengers *.o traversal_unittest
