#include "metadata.h"

#include <fstream>

void Metadata::read_from_file(const std::string& filename) {
  std::ifstream file;
  file.open(filename);
  if (!file.is_open()) {
    throw std::invalid_argument("Invalid file path(s) given");
  }

  std::string line;

  // Drop all intitial comment lines
  while (getline(file, line)) {
    if (line.at(0) != '#') {
      break;
    }
  }

  // Now line has information about total items
  int total_items = GetIntFromLine(line);

  // Reserve more space in products
  size_t new_product_size = products_.size() + total_items;
  products_.reserve(new_product_size);

  int curr_id = -1;
  // Get rest of data
  while (getline(file, line)) {
    if (line.length() <= 1) {
        // Line is empty
        continue;
    } else if (line.substr(0, 2) == "Id") {
        curr_id = GetIntFromLine(line);
        products_[curr_id];
    } else if (line.substr(0, 4) == "ASIN") {
        products_[curr_id].asin_ = line.substr(6);
    } else if (line.substr(2, 5) == "title") {
        products_[curr_id].title_ = line.substr(9);
    } else if (line.substr(2, 5) == "group") {
        products_[curr_id].group_ = line.substr(9);
    } else if (line.substr(2, 9) == "salesrank") {
        products_[curr_id].sales_rank_ = GetIntFromLine(line);
    }
  }

  file.close();
}

int Metadata::GetIntFromLine(const std::string& line) const {
  size_t digit_start = line.find_first_of("0123456789");
  return std::stoi(line.substr(digit_start));
}

std::string Metadata::GetStringAfterColon(const std::string& line) const {
  size_t colon_ind = line.find(':');
  return line.substr(colon_ind + 2);
}

std::string Metadata::GetAsin(int id) const {
  return products_.at(id).asin_;
}

std::string Metadata::GetGroup(int id) const {
  return products_.at(id).group_;
}

std::string Metadata::GetTitle(int id) const {
  return products_.at(id).title_;
}

int Metadata::GetSalesRank(int id) const {
  return products_.at(id).sales_rank_;
}

bool Metadata::ProductExists(int id) const {
  return products_.find(id) != products_.end();
}