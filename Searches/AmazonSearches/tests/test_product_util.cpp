#include <algorithm>
#include <iostream>
#include <vector>

#include "../catch/catch.hpp"
#include "../src/data.h"
#include "../src/graph.h"
#include "../src/metadata.h"
#include "../src/product_util.h"


TEST_CASE("Correctly assembles graph from small file", "[productutil]") {
  Data data;
  data.read_from_file("tests/testing_data/small_amazon.txt");

  Metadata metadata;
  metadata.read_from_file("tests/testing_data/small_amazon_meta.txt");

  Graph graph = ProductUtil::CreateGraph(data, metadata);

  SECTION("Check correct vertices") {
    std::vector<int> expected{1, 2, 3, 4, 6, 7, 8, 9};

    std::vector<int> actual = graph.GetVertices();
    std::sort(actual.begin(), actual.end());

    REQUIRE(actual == expected);
  }

  SECTION("Check correct edges") {
    std::vector<Edge> expected{{1, 3, 7}, {1, 6, 4}, {2, 7, 8}, {4, 8, 11}};
    std::vector<Edge> actual = graph.GetEdges();

    std::sort(expected.begin(), expected.end());
    std::sort(actual.begin(), actual.end());

    REQUIRE(actual == expected);
  }
}

TEST_CASE("Assembles graph from full amazon file without errors",
          "[productutil][largefile]") {
  Data data;
  data.read_from_file("data/amazon.txt");

  Metadata metadata;
  metadata.read_from_file("data/amazon-meta.txt");

  REQUIRE_NOTHROW(ProductUtil::CreateGraph(data, metadata));
}

TEST_CASE("Correctly returns a list of product names",
          "[productutil][getproductnames]") {
  Metadata metadata;
  metadata.read_from_file("tests/testing_data/small_amazon_meta.txt");

  std::vector<int> product_ids{1, 2, 3, 4, 5};
  std::vector<std::string> expected_names{
      "Patterns of Preaching: A Sermon Sampler", "Candlemas: Feast of Flames",
      "World War II Allied Fighter Planes Trading Cards",
      "Life Application Bible Commentary: 1 and 2 Timothy and Titus",
      "Prayers That Avail Much for Business: Executive"};

  std::vector<std::string> actual_names =
      ProductUtil::GetProductNames(product_ids, metadata);

  REQUIRE(expected_names == actual_names);
}