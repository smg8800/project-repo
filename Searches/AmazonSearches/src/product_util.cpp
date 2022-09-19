#include "product_util.h"

#include <string>
#include <vector>

namespace ProductUtil {
Graph CreateGraph(const Data& product_data, const Metadata& product_meta_data) {
  Graph graph;

  std::vector<int> nodesFrom = product_data.getNodesFrom();
  std::vector<int> nodesTo = product_data.getNodesTo();

  for (size_t ind = 0; ind < nodesFrom.size(); ind++) {
    int start = nodesFrom.at(ind);
    int end = nodesTo.at(ind);

    int start_sales_rank = product_meta_data.GetSalesRank(start);
    int end_sales_rank = product_meta_data.GetSalesRank(end);

    bool start_is_valid =
        product_meta_data.ProductExists(start) && start_sales_rank != -1;
    bool end_is_valid =
        product_meta_data.ProductExists(end) && end_sales_rank != -1;

    if (start_is_valid) {
      graph.InsertVertex(start);
    }
    if (end_is_valid) {
      graph.InsertVertex(end);
    }
    if (start_is_valid && end_is_valid) {
      int sales_rank_sum = start_sales_rank + end_sales_rank;
      graph.InsertEdge(start, end, sales_rank_sum);
    }
  }

  return graph;
}

std::vector<std::string> GetProductNames(const std::vector<int>& product_ids,
                                         const Metadata& metadata) {
  std::vector<std::string> product_names;
  product_names.reserve(product_ids.size());
  for (int id : product_ids) {
    product_names.push_back(metadata.GetTitle(id));
  }
  return product_names;
}
}  // namespace ProductUtil