#include <iostream>
#include <vector>

#include "../catch/catch.hpp"
#include "../src/DFS.h"
#include "../src/graph.h"


TEST_CASE("Simple Traversal", "[traverse]") {
    Graph graph;

    SECTION("Empty graph/start DNE") {
        DFS dfs(graph);
        REQUIRE_THROWS_AS(dfs.traverse(0), std::invalid_argument);
    }

    SECTION("Single child") {
        graph.InsertEdge(0, 1, 0);
        graph.InsertEdge(1, 2, 0);
        graph.InsertEdge(2, 3, 0);
        graph.InsertEdge(3, 4, 0);

        vector<int> expected;
        expected.push_back(0);
        expected.push_back(1);
        expected.push_back(2);
        expected.push_back(3);
        expected.push_back(4);

        DFS dfs(graph);
        vector<int> result = dfs.traverse(0);

        REQUIRE(result == expected);
    }
    SECTION("Multiple children"){
        graph.InsertEdge(0, 1, 0);
        graph.InsertEdge(0, 2, 0);
        graph.InsertEdge(0, 3, 0);
        graph.InsertEdge(1, 4, 0);
        graph.InsertEdge(1, 5, 0);
        graph.InsertEdge(1, 6, 0);
        graph.InsertEdge(2, 7, 0);
        graph.InsertEdge(2, 8, 0);
        graph.InsertEdge(2, 9, 0);
        graph.InsertEdge(3, 10, 0);
        graph.InsertEdge(3, 11, 0);
        graph.InsertEdge(3, 12, 0);

        vector<int> expected;
        expected.push_back(0);
        expected.push_back(1);
        expected.push_back(4);
        expected.push_back(5);
        expected.push_back(6);
        expected.push_back(2);
        expected.push_back(7);
        expected.push_back(8);
        expected.push_back(9);
        expected.push_back(3);
        expected.push_back(10);
        expected.push_back(11);
        expected.push_back(12);

        DFS dfs(graph);
        vector<int> result = dfs.traverse(0);

        REQUIRE(result == expected);

    }

}
TEST_CASE("Traversing with cycles", "[traverse][cycles]") {
    Graph graph;

    SECTION("Self-cycles") {
        graph.InsertEdge(0, 0, 0);
        graph.InsertEdge(0, 1, 0);
        graph.InsertEdge(1, 1, 0);
        graph.InsertEdge(1, 2, 0);
        graph.InsertEdge(2, 2, 0);
        graph.InsertEdge(2, 3, 0);
        graph.InsertEdge(3, 3, 0);
        graph.InsertEdge(3, 4, 0);

        vector<int> expected;
        expected.push_back(0);
        expected.push_back(1);
        expected.push_back(2);
        expected.push_back(3);
        expected.push_back(4);

        DFS dfs(graph);
        vector<int> result = dfs.traverse(0);

        REQUIRE(result == expected);
    }
    SECTION("Bigger cycles - forward", "[traverse][cycles]") {
        graph.InsertEdge(0, 1, 0);
        graph.InsertEdge(0, 3, 0);
        graph.InsertEdge(1, 2, 0);
        graph.InsertEdge(2, 3, 0);
        graph.InsertEdge(3, 4, 0);
        graph.InsertEdge(4, 5, 0);
        graph.InsertEdge(5, 6, 0);

        vector<int> expected;
        expected.push_back(0);
        expected.push_back(1);
        expected.push_back(2);
        expected.push_back(3);
        expected.push_back(4);
        expected.push_back(5);
        expected.push_back(6);

        DFS dfs(graph);
        vector<int> result = dfs.traverse(0);

        REQUIRE(result == expected);
    }
    SECTION("Bigger cycles - backward", "[traverse][cycles]") {
        graph.InsertEdge(0, 1, 0);
        graph.InsertEdge(1, 2, 0);
        graph.InsertEdge(2, 3, 0);
        graph.InsertEdge(3, 4, 0);
        graph.InsertEdge(4, 0, 0);
        graph.InsertEdge(4, 6, 0);

        vector<int> expected;
        expected.push_back(0);
        expected.push_back(1);
        expected.push_back(2);
        expected.push_back(3);
        expected.push_back(4);
        expected.push_back(6);

        DFS dfs(graph);
        vector<int> result = dfs.traverse(0);

        REQUIRE(result == expected);
    }
}
TEST_CASE("Disconnected", "[traverse]") {
    Graph graph;

    graph.InsertEdge(0, 1, 0);
    graph.InsertEdge(1, 2, 0);
    graph.InsertEdge(2, 3, 0);
    graph.InsertEdge(3, 4, 0);
    graph.InsertEdge(7, 9, 0);

    vector<int> expected;
    expected.push_back(0);
    expected.push_back(1);
    expected.push_back(2);
    expected.push_back(3);
    expected.push_back(4);

    DFS dfs(graph);
    vector<int> result = dfs.traverse(0);

    REQUIRE(result == expected);
}
TEST_CASE("Find returns correct path", "[find]") {
    Graph graph;

    SECTION("Empty graph/start DNE") {
        DFS dfs(graph);
        REQUIRE_THROWS_AS(dfs.find(0,7), std::invalid_argument);
    }
    SECTION("Simple path") {
        graph.InsertEdge(0, 1, 0);
        graph.InsertEdge(0, 2, 0);
        graph.InsertEdge(0, 3, 0);
        graph.InsertEdge(1, 4, 0);
        graph.InsertEdge(1, 5, 0);
        graph.InsertEdge(1, 6, 0);
        graph.InsertEdge(2, 7, 0);
        graph.InsertEdge(2, 8, 0);
        graph.InsertEdge(2, 9, 0);
        graph.InsertEdge(3, 10, 0);
        graph.InsertEdge(3, 11, 0);
        graph.InsertEdge(3, 12, 0);

        vector<int> expected;
        expected.push_back(0);
        expected.push_back(3);
        expected.push_back(12);

        DFS dfs(graph);
        vector<int> result = dfs.find(0,12);

        REQUIRE(result == expected);
    }
    SECTION("No path found") {
        graph.InsertEdge(0, 1, 0);
        graph.InsertEdge(0, 2, 0);
        graph.InsertEdge(0, 3, 0);
        graph.InsertEdge(1, 4, 0);
        graph.InsertEdge(1, 5, 0);
        graph.InsertEdge(1, 6, 0);
        graph.InsertEdge(2, 7, 0);
        graph.InsertEdge(2, 8, 0);
        graph.InsertEdge(2, 9, 0);
        graph.InsertEdge(3, 10, 0);
        graph.InsertEdge(3, 11, 0);
        graph.InsertEdge(3, 12, 0);

        vector<int> expected;

        DFS dfs(graph);
        vector<int> result = dfs.find(0, 87);

        REQUIRE(result == expected);
    }
}