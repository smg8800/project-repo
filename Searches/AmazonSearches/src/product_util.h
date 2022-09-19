#pragma once

#include "data.h"
#include "graph.h"
#include "metadata.h"

namespace ProductUtil {

// Cretes a Graph given a set of product data and metadat about each product
Graph CreateGraph(const Data& product_data, const Metadata& product_meta_data);

/*
 * Converts a vector of product ids into a vector of product names, using
 * product metadata
 */
std::vector<std::string> GetProductNames(const std::vector<int>& product_ids,
                                         const Metadata& metadata);
}  // namespace ProductUtil