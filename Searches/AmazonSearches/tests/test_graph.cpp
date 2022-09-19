#include <algorithm>
#include <iostream>
#include <vector>

#include "../catch/catch.hpp"
#include "../src/graph.h"

Graph ConstructMediumGraph() {
  Graph graph{};

  graph.InsertEdge(0, 1, 10);
  graph.InsertEdge(1, 2, 20);
  graph.InsertEdge(0, 2, 30);
  graph.InsertEdge(2, 0, 40);
  graph.InsertEdge(2, 3, 50);

  return graph;
}

TEST_CASE("Constructor does not cause unexpected behavior",
          "[graph][constructor]") {
  Graph graph{};

  SECTION("Get vertices returns empty vector") {
    std::vector<int> vertices = graph.GetVertices();
    REQUIRE(vertices.empty());
  }

  SECTION("Get edges returns empty vector") {
    std::vector<Edge> edges = graph.GetEdges();
    REQUIRE(edges.empty());
  }

  SECTION("Cannot remove any vertex") { REQUIRE_THROWS(graph.RemoveVertex(5)); }

  SECTION("Cannot check if any vertex is adjacent") {
    REQUIRE_THROWS(graph.IsAdjacent(1, 2));
  }
}

TEST_CASE("Add vertices but no edges", "[graph][AddVertex][IsAdjacent]") {
  Graph graph{};
  int start_vertex = 1;
  int end_vertex = 5;

  // Add vertices from 1 to 5 (inclusive)
  for (int vertex = start_vertex; vertex <= end_vertex; vertex++) {
    graph.InsertVertex(vertex);
  }

  SECTION("Check vertices exist in graph") {
    for (int vertex = start_vertex; vertex <= end_vertex; vertex++) {
      REQUIRE(graph.VertexExists(vertex));
    }
    for (int invalid_vert = end_vertex + 1; invalid_vert < end_vertex + 5; invalid_vert++) {
      REQUIRE(!graph.VertexExists(invalid_vert));
    }
  }

  SECTION("Get vertices returns correct vertices") {
    std::vector<int> exepcted{};
    for (int vertex = start_vertex; vertex <= end_vertex; vertex++) {
      exepcted.push_back(vertex);
    }
    std::vector<int> actual = graph.GetVertices();
    std::sort(actual.begin(), actual.end());
    REQUIRE(exepcted == actual);
  }

  SECTION("Get edges returns empty vector") {
    std::vector<Edge> edges = graph.GetEdges();
    REQUIRE(edges.empty());
  }

  SECTION("None of the vertices are adjacent") {
    for (int v1 = start_vertex; v1 <= end_vertex; v1++) {
      for (int v2 = start_vertex; v2 <= end_vertex; v2++) {
        REQUIRE(!graph.IsAdjacent(v1, v2));
      }
    }
  }
}

TEST_CASE(
    "Same vertex can be added twice, but second addition doesn't do anything",
    "[graph][AddVertex][IsAdjacent]") {
  Graph graph{};
  graph.InsertVertex(1);
  graph.InsertVertex(1);

  SECTION("Contains only 1 vertex") {
    std::vector<int> vertices = graph.GetVertices();
    REQUIRE(vertices.size() == 1);
    REQUIRE(vertices.at(0) == 1);
  }

  SECTION("Vertex 1 is not adjacent to itself") {
    REQUIRE(!graph.IsAdjacent(1, 1));
  }
}

TEST_CASE("Add a single edge between two vertices",
          "[graph][AddEdge][IsAdjacent]") {
  Graph graph{};
  graph.InsertEdge(1, 2, 10);

  SECTION("Graph has two vertices (1, 2)") {
    std::vector<int> expected{1, 2};
    std::vector<int> actual = graph.GetVertices();
    std::sort(actual.begin(), actual.end());
    REQUIRE(expected == actual);
  }

  SECTION("Graph has 1 edge") {
    std::vector<Edge> actual_edges = graph.GetEdges();
    REQUIRE(actual_edges.size() == 1);

    Edge expected{1, 2, 10};
    REQUIRE(expected == actual_edges[0]);
  }

  SECTION("Vertex 2 is adjacent to vertex 1 (no other vertices adjacent)") {
    REQUIRE(graph.IsAdjacent(1, 2));
    REQUIRE(!graph.IsAdjacent(2, 1));
  }
}

TEST_CASE("Check construction of larger graph",
          "[graph][AddEdge][IsAdjacent]") {
  Graph graph = ConstructMediumGraph();

  SECTION("Check graph vertices") {
    std::vector<int> actual = graph.GetVertices();
    std::sort(actual.begin(), actual.end());
    std::vector<int> expected{0, 1, 2, 3};
    REQUIRE(actual == expected);
  }

  SECTION("Check graph edges") {
    std::vector<Edge> actual = graph.GetEdges();
    std::sort(actual.begin(), actual.end());

    std::vector<Edge> expected{
        {0, 1, 10}, {1, 2, 20}, {0, 2, 30}, {2, 0, 40}, {2, 3, 50}};
    REQUIRE(actual == expected);
  }

  SECTION("Check adjacency") {
    REQUIRE(graph.IsAdjacent(0, 1));
    REQUIRE(graph.IsAdjacent(1, 2));
    REQUIRE(graph.IsAdjacent(2, 0));
    REQUIRE(graph.IsAdjacent(0, 2));
    REQUIRE(graph.IsAdjacent(2, 3));

    REQUIRE(!graph.IsAdjacent(2, 1));
    REQUIRE(!graph.IsAdjacent(0, 3));
  }
}

TEST_CASE("Remove vertices", "[graph][AddEdge][IsAdjacent][RemoveVertex]") {
  Graph graph = ConstructMediumGraph();

  graph.RemoveVertex(2);

  SECTION("Check graph vertices") {
    std::vector<int> actual = graph.GetVertices();
    std::sort(actual.begin(), actual.end());
    std::vector<int> expected{0, 1, 3};
    REQUIRE(actual == expected);
  }

  SECTION("Check graph edges") {
    std::vector<Edge> actual = graph.GetEdges();
    std::sort(actual.begin(), actual.end());

    std::vector<Edge> expected{{0, 1, 10}};
    REQUIRE(actual == expected);
  }

  SECTION("Check adjacency") {
    REQUIRE(graph.IsAdjacent(0, 1));
    REQUIRE(!graph.IsAdjacent(1, 0));

    REQUIRE(!graph.IsAdjacent(1, 3));
    REQUIRE(!graph.IsAdjacent(0, 3));
  }
}

TEST_CASE("Can't remove non-existent edge", "[graph][RemoveEdge]") {
  Graph graph{};

  graph.InsertEdge(0, 1, 10);
  REQUIRE_THROWS_AS(graph.RemoveEdge(1, 0), std::invalid_argument);
}

TEST_CASE("Remove edges", "[graph][AddEdge][IsAdjacent][RemoveEdge]") {
  Graph graph = ConstructMediumGraph();

  graph.RemoveEdge(0, 1);
  graph.RemoveEdge(0, 2);
  graph.RemoveEdge(2, 3);

  SECTION("Check graph vertices") {
    std::vector<int> actual = graph.GetVertices();
    std::sort(actual.begin(), actual.end());
    std::vector<int> expected{0, 1, 2, 3};
    REQUIRE(actual == expected);
  }

  SECTION("Check graph edges") {
    std::vector<Edge> actual = graph.GetEdges();
    std::sort(actual.begin(), actual.end());

    std::vector<Edge> expected{{1, 2, 20}, {2, 0, 40}};
    REQUIRE(actual == expected);
  }

  SECTION("Check adjacency") {
    REQUIRE(graph.IsAdjacent(1, 2));
    REQUIRE(graph.IsAdjacent(2, 0));

    REQUIRE(!graph.IsAdjacent(0, 1));
    REQUIRE(!graph.IsAdjacent(0, 2));
    REQUIRE(!graph.IsAdjacent(2, 3));
  }
}

TEST_CASE("Incident edges", "[graph][IncidentEdges]") {
  Graph graph = ConstructMediumGraph();

  SECTION("Vertex with one incident edge") {
    std::vector<Edge> actual = graph.IncidentEdges(3);
    std::vector<Edge> expected{{2, 3, 50}};
    REQUIRE(expected == actual);
  }

  SECTION("Vertex with multiple incident edges") {
    std::vector<Edge> actual = graph.IncidentEdges(1);
    std::sort(actual.begin(), actual.end());

    std::vector<Edge> expected{{0, 1, 10}, {1, 2, 20}};
    REQUIRE(expected == actual);
  }

  // Remove an edge
  graph.RemoveEdge(0, 1);
  SECTION("Vertex 1 now has a single incident edge") {
    std::vector<Edge> actual = graph.IncidentEdges(1);
    std::sort(actual.begin(), actual.end());

    std::vector<Edge> expected{{1, 2, 20}};
    REQUIRE(expected == actual);
  }

  // Remove a vertex
  graph.RemoveVertex(2);
  SECTION("Vertex 0 now has no incident edge") {
    REQUIRE(graph.IncidentEdges(0).empty());
  }
}

TEST_CASE("Outgoing edges", "[graph][OutgoingEdges]") {
  Graph graph = ConstructMediumGraph();

  SECTION("Vertex with multiple outgoing edge") {
    std::vector<Edge> actual = graph.OutoingEdges(2);
    std::sort(actual.begin(), actual.end());
    std::vector<Edge> expected{{2, 0, 40}, {2, 3, 50}};
    REQUIRE(expected == actual);
  }

  SECTION("Vertex with no outgoing edges edges") {
    REQUIRE(graph.OutoingEdges(3).empty());
  }

  SECTION("Check that start of every edge is the input vertex") {
    for (int vertex = 0; vertex <= 3; vertex++) {
      std::vector<Edge> outgoing = graph.OutoingEdges(vertex);
      for (const Edge& edge : outgoing) {
        REQUIRE(edge.start_ == vertex);
      }
    }
  }
}

TEST_CASE("Adjacent vertices", "[graph][AdjacentVertices]") {
  Graph graph = ConstructMediumGraph();

  SECTION("Vertex with one adjacent vertex") {
    std::vector<int> actual = graph.AdjacentVertices(1);
    std::vector<int> expected{2};
    REQUIRE(expected == actual);
  }

  SECTION("Vertex with multiple adjacent vertex") {
    std::vector<int> actual = graph.AdjacentVertices(2);
    std::sort(actual.begin(), actual.end());

    std::vector<int> expected{0, 3};
    REQUIRE(expected == actual);
  }

  // Remove an edge
  graph.RemoveEdge(2, 0);
  SECTION("Vertex 2 now has a single adjacent vertex") {
    std::vector<int> actual = graph.AdjacentVertices(2);
    std::vector<int> expected{3};
    REQUIRE(expected == actual);
  }

  // Remove a vertex
  graph.RemoveVertex(2);
  SECTION("Vertex 1 now has no incident edge") {
    REQUIRE(graph.AdjacentVertices(1).empty());
  }
}

TEST_CASE("GetEdge", "[graph][GetEdge]") {
  Graph graph = ConstructMediumGraph();

  SECTION("Check that correct edge is returned") {
    Edge expected(0, 1, 10);
    REQUIRE(graph.GetEdge(0, 1) == expected);
  }
}