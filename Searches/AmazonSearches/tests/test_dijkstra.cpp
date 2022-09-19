#include <iostream>
#include <list>
#include <queue>
#include <unordered_map>
#include <utility>
#include <vector>

#include "../catch/catch.hpp"
#include "../src/dijkstra.h"
#include "../src/graph.h"

TEST_CASE("Dijkstra run on graph returns proper path and distance") {
  Graph g;
  g.InsertEdge(0, 1, 10);
  g.InsertEdge(1, 2, 20);
  g.InsertEdge(0, 2, 30);
  g.InsertEdge(2, 0, 40);
  g.InsertEdge(2, 3, 50);
  std::vector<int> path1 = dijkstra(g, 0, 3);
  std::vector<int> corpath1 = {0, 2, 3};
  SECTION("Path 1 is correct") { REQUIRE(path1 == corpath1); }
  std::vector<int> path2 = dijkstra(g, 1, 0);
  std::vector<int> corpath2 = {1, 2, 0};
  SECTION("Path 2 is correct") { REQUIRE(path2 == corpath2); }
}

TEST_CASE("Dijkstra run on cycled graph returns proper path") {
  Graph g;
  g.InsertEdge(0, 1, 20);
  g.InsertEdge(1, 2, 20);
  g.InsertEdge(0, 2, 40);
  std::vector<int> path = dijkstra(g, 0, 2);
  std::vector<int> corpath = {0, 2};
  SECTION("Path is correct") { REQUIRE(path == corpath); }
}