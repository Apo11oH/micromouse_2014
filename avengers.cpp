#include <stdio.h>
#include <iostream>
#include "BotConstants.hpp"
#include "Traversal.hpp"
#include "Navigation.hpp"
#include "Graph.hpp"

using namespace std;
using namespace BotConsts;

int main(int argc, 	const char* argv[])
{
  Traversal *traversal = new Traversal();
  Navigation *navigation = new Navigation();
  //Graph *graph = new Graph();

  cout << "Traversal map" << endl;
  traversal->initTraversal();
  traversal->printTraversalMap();
  cout << endl;

  cout << "Floodfill map" << endl;
  navigation->initNaviGoal();
  navigation->printFloodfillMap();
  cout << endl;

  /*
  cout << "Graph map" << endl;
  graph->printGraph();
  cout << endl;
  */
}
