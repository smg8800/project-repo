#pragma once

#include <string>
#include <unordered_map>

class Metadata {
 public:
  void read_from_file(const std::string& filename);

  // Returns "NA" if Asin could not be found
  std::string GetAsin(int id) const;

  // Returns "NA" if Title could not be found
  std::string GetTitle(int id) const;

  // Returns "NA" if Group could not be found
  std::string GetGroup(int id) const;

  // Return -1 if Sales Rank could not be found
  int GetSalesRank(int id) const;

  // Checks if product exists in metadata
  bool ProductExists(int id) const;

 private:
  struct ProductData {
    std::string asin_;
    std::string title_;
    std::string group_;
    int sales_rank_;

    ProductData() : asin_("NA"), title_("NA"), group_("NA"), sales_rank_(-1) {}
  };

  std::unordered_map<int, ProductData> products_;

  // Helper methods
  int GetIntFromLine(const std::string& line) const;
  std::string GetStringAfterColon(const std::string& line) const;
};