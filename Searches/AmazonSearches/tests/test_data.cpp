#include <iostream>
#include <vector>

#include "../catch/catch.hpp"
#include "../src/data.h"

TEST_CASE("Test Amazon data", "[readfromfile][largedata]") {
  Data amazon;
  amazon.read_from_file("data/amazon.txt");
  std::vector<int> first = amazon.getNodesFrom();
  std::vector<int> second = amazon.getNodesTo();

  SECTION("Parsed correct number of edges (85535)") {
    int num_edges = 85535;
    REQUIRE(first.size() == num_edges);
    REQUIRE(second.size() == num_edges);
  }

  SECTION("Check section of first") {
    std::vector<int> expected_first{0, 0, 0, 0, 0, 1, 1, 1};
    for (size_t ind = 0; ind < expected_first.size(); ind++) {
      REQUIRE(first.at(ind) == expected_first.at(ind));
    }
  }

  SECTION("Check section of second") {
    std::vector<int> expected_second{1, 2, 3, 4, 5, 0, 2, 4};
    for (size_t ind = 0; ind < expected_second.size(); ind++) {
      REQUIRE(second.at(ind) == expected_second.at(ind));
    }
  }
}

TEST_CASE("Test full set of small data", "[readfromfile]") {
  Data empty;
  empty.read_from_file("tests/testing_data/small_data.txt");
  std::vector<int> first = empty.getNodesFrom();
  std::vector<int> second = empty.getNodesTo();

  SECTION("Has correct number of edges (5)") {
    int num_edges = 5;
    REQUIRE(first.size() == num_edges);
    REQUIRE(second.size() == num_edges);
  }

  SECTION("Check all of first") {
    std::vector<int> expected_first{1, 2, 3, 4, 5};
    for (size_t ind = 0; ind < expected_first.size(); ind++) {
      REQUIRE(first.at(ind) == expected_first.at(ind));
    }
  }

  SECTION("Check all of second") {
    std::vector<int> expected_second{10, 20, 30, 10, 20};
    for (size_t ind = 0; ind < expected_second.size(); ind++) {
      REQUIRE(second.at(ind) == expected_second.at(ind));
    }
  }
}