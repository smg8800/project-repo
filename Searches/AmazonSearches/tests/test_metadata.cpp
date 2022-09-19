#include "../catch/catch.hpp"
#include "../src/metadata.h"

TEST_CASE("Test on small metadata", "[metadata]") {
  Metadata metadata;
  metadata.read_from_file("tests/testing_data/small_metadata.txt");

  SECTION("Test valid id") {
    REQUIRE(metadata.ProductExists(1));
    REQUIRE(metadata.GetAsin(1) == "0827229534");
    REQUIRE(metadata.GetTitle(1) == "Patterns of Preaching: A Sermon Sampler");
    REQUIRE(metadata.GetGroup(1) == "Book");
    REQUIRE(metadata.GetSalesRank(1) == 396585);
  }

  SECTION("Test valid near end of file") {
    REQUIRE(metadata.ProductExists(10));
    REQUIRE(metadata.GetAsin(10) == "0375709363");
    REQUIRE(metadata.GetTitle(10) == "The Edward Said Reader");
    REQUIRE(metadata.GetGroup(10) == "Book");
    REQUIRE(metadata.GetSalesRank(10) == 220379);
  }

  SECTION("Test invalid data") {
    REQUIRE(metadata.ProductExists(0));
    REQUIRE(metadata.GetAsin(0) == "0771044445");
    REQUIRE(metadata.GetTitle(0) == "NA");
    REQUIRE(metadata.GetGroup(0) == "NA");
    REQUIRE(metadata.GetSalesRank(0) == -1);
  }
}