#include <iostream>
#include <vector>

#include "../catch/catch.hpp"
#include "../src/IDDFS.h"
#include "../src/graph.h"


TEST_CASE("Simple IDDFS Tests", "[traverse]") {
    Graph graph;
    Graph graph2;
    Graph graph3;
    Graph graph4;

    SECTION("Empty graph/start DNE") {
        IDDFS iddfs(graph);
        REQUIRE_THROWS_AS(iddfs.search(0, 1, 5), std::invalid_argument);
        REQUIRE_THROWS_AS(iddfs.get_path(0, 1, 5), std::invalid_argument);
    }

    SECTION("Single child") {
        graph.InsertEdge(0, 1, 0);
        graph.InsertEdge(1, 2, 0);
        graph.InsertEdge(2, 3, 0);
        graph.InsertEdge(3, 4, 0);

        IDDFS iddfs(graph);
        bool result = iddfs.search(0, 4, 4);
        bool result2 = iddfs.search(0, 4, 3);
        vector<int> expected;
        expected.push_back(1);
        expected.push_back(2);
        expected.push_back(3);
        vector<int> path = iddfs.get_path(1,3,3);
        REQUIRE(result == true);
        REQUIRE(result2 == false);
        REQUIRE_THROWS_AS(iddfs.search(0, 7, 5), std::invalid_argument);
        REQUIRE_THROWS_AS(iddfs.search(5, 1, 5), std::invalid_argument);
        REQUIRE(path == expected);
    }
    SECTION("Multiple children"){
        int curr = 1;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 3; j++) {
                graph2.InsertEdge(i, curr, 0);
                curr++;
            }
        }
        IDDFS iddfs2(graph2);
        bool result1 = iddfs2.search(0,9,1);
        bool result2 = iddfs2.search(0,9,2);
        bool result3 = iddfs2.search(0,12, 2);
        REQUIRE(result1 == false);
        REQUIRE(result2 == true);
        REQUIRE(result3 == true);

    }
    SECTION("Long single child graph") {
        for (int i = 0; i < 200; i++) {
            graph3.InsertEdge(i, i+1, 0);
        }
        IDDFS iddfs3(graph3);
        bool result1 = iddfs3.search(5, 6, 3);
        bool result2 = iddfs3.search(0, 100, 99);
        bool result3 = iddfs3.search(4, 71, 67);
        REQUIRE(result1 == true);
        REQUIRE(result2 == false);
        REQUIRE(result3 == true);

    }
}

TEST_CASE("Disconnected graph") {
    Graph graph;
    int temp = 10;
    for (int i = 0; i <= 10; i++) {
        for (int j = 0; j <= 10; j++) {
            graph.InsertEdge(i, temp, 0);
            temp++;
        }
    }
    IDDFS iddfs(graph);
    bool result1 = iddfs.search(4, 12, 10);
    bool result2 = iddfs.search(0, 19, 1);
    bool result3 = iddfs.search(0, 65, 100);
    REQUIRE(result1 == false);
    REQUIRE(result2 == true);
    REQUIRE(result3 == false);
}

TEST_CASE("IDDFS Path") {
    Graph graph;
    Graph graph2;
    for (int i = 0; i < 100; i++) {
        graph.InsertEdge(i, i+1, 0);
    }
    graph2.InsertEdge(2, 7, 0);
    graph2.InsertEdge(6, 7, 0);
    graph2.InsertEdge(7, 6, 0);
    graph2.InsertEdge(6, 12, 0);
    graph2.InsertEdge(12, 15, 0);
    graph2.InsertEdge(17, 12, 0);
    graph2.InsertEdge(11, 6, 0);
    graph2.InsertEdge(14, 21, 0);
    graph2.InsertEdge(6, 21, 0);

    IDDFS iddfs(graph);
    IDDFS iddfs2(graph2);
    vector<int> path = iddfs.get_path(4, 71, 100);
    vector<int> expected;
    vector<int> path2 = iddfs2.get_path(2, 15, 100);
    vector<int> expected2;
    vector<int> path3 = iddfs2.get_path(11, 15, 100);
    vector<int> expected3;
    for (int i = 4; i <= 71; i++) {
        expected.push_back(i);
    }
    expected2.push_back(2);
    expected2.push_back(7);
    expected2.push_back(6);
    expected2.push_back(12);
    expected2.push_back(15);

    expected3.push_back(11);
    expected3.push_back(6);
    expected3.push_back(12);
    expected3.push_back(15);

    REQUIRE_THROWS_AS(iddfs2.get_path(17, 21, 100), std::invalid_argument);
    REQUIRE(expected == path);
    REQUIRE(expected2 == path2);
    REQUIRE(expected3 == path3);
}