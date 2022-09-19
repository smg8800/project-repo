#include <fstream>
#include <iostream>
#include <string>

#include "src/DFS.h"
#include "src/IDDFS.h"
#include "src/data.h"
#include "src/dijkstra.h"
#include "src/metadata.h"
#include "src/product_util.h"

void PrintProductsToFile(const std::vector<int>& path,
                         const std::vector<std::string>& product_names,
                         std::ostream& out_stream) {
  for (size_t i = 0; i < path.size(); i++) {
    out_stream << path[i] << ": " << product_names[i] << std::endl;
  }
}

void RunDfsTraversal(const Graph& graph, const Metadata& metadata,
                     std::ostream& out_stream) {
  // Ask user for start IDs
  int start;
  std::cout << "Enter start node ID" << std::endl;
  std::cin >> start;

  // Run DFS Algorithm
  DFS dfs(graph);
  std::vector<int> dfs_traversal = dfs.traverse(start);

  // Save to file
  std::cout << "Saving to file..." << std::endl;
  std::vector<std::string> product_names =
      ProductUtil::GetProductNames(dfs_traversal, metadata);
  PrintProductsToFile(dfs_traversal, product_names, out_stream);
}

void RunDfsFind(const Graph& graph, const Metadata& metadata,
                  std::ostream& out_stream) {
  // Ask user for start and end IDs
  int start;
  int end;
  std::cout << "Enter start node ID" << std::endl;
  std::cin >> start;
  std::cout << "Enter end node ID" << std::endl;
  std::cin >> end;

  // Run Dijkstra's algorithm
  DFS dfs(graph);
  std::vector<int> path = dfs.find(start, end);

  // Save to file
  std::cout << "Saving to file: " << std::endl;
  std::vector<std::string> product_names =
      ProductUtil::GetProductNames(path, metadata);
  PrintProductsToFile(path, product_names, out_stream);
}

void RunDijkstra(const Graph& graph, const Metadata& metadata,
                 std::ostream& out_stream) {
  // Ask user for start and end IDs
  int start;
  int end;
  std::cout << "Enter start node ID" << std::endl;
  std::cin >> start;
  std::cout << "Enter end node ID" << std::endl;
  std::cin >> end;

  // Run Dijkstra's algorithm
  std::vector<int> path = dijkstra(graph, start, end);

  // Save to file
  std::cout << "Saving to file: " << std::endl;
  std::vector<std::string> product_names =
      ProductUtil::GetProductNames(path, metadata);
  PrintProductsToFile(path, product_names, out_stream);
}

void RunIDDFS(const Graph& graph, const Metadata& metadata,
              std::ostream& out_stream) {
  // Ask user for start and end IDs
  int start;
  int end;
  std::cout << "Enter start node ID" << std::endl;
  std::cin >> start;
  std::cout << "Enter end node ID" << std::endl;
  std::cin >> end;

  // Run IDDFS algorithm
  IDDFS iddfs(graph);
  bool path_exists = iddfs.search(start, end, 20000);

  // Save to file
  std::cout << "Saving to file: " << std::endl;
  std::string start_product = metadata.GetTitle(start);
  std::string end_product = metadata.GetTitle(end);

  out_stream << "Start vertex:\t\t" << start_product << std::endl;
  out_stream << "End vertex:\t\t" << end_product << std::endl;
  out_stream << "Path exists?:\t\t" << std::boolalpha << path_exists
             << std::endl;
}

void PrintVertexInfo(const Graph& graph, const Metadata& metadata,
                     std::ostream& out_stream) {
  std::vector<int> vert_inds = graph.GetVertices();
  std::vector<std::string> vert_names =
      ProductUtil::GetProductNames(vert_inds, metadata);

  out_stream << "Vertex ID:\t\t"
             << "Product name" << std::endl;

  for (size_t ind = 0; ind < vert_inds.size(); ind++) {
    out_stream << vert_inds.at(ind) << "\t\t" << vert_names.at(ind)
               << std::endl;
  }
}

// Requires 3 arguments: data file name, metadata file name, output file
// name
int main(int argc, char** argv) {
  if (argc < 4) {
    throw std::invalid_argument(
        "Main requires three arguments: data file name, metadata file name, "
        "output file name");
  }

  // Extract command-line arguments
  std::string data_file(argv[1]);
  std::string metadata_file(argv[2]);
  std::string output_file(argv[3]);

  // Load files
  std::cout << "Loading files..." << std::endl;
  std::cout << "Data: " << data_file << "\tMetadata: " << metadata_file
            << std::endl;
  Data data;
  data.read_from_file(data_file);
  Metadata metadata;
  metadata.read_from_file(metadata_file);

  // Ask user to choose algorithm
  std::cout << std::endl
            << "What operation would you like to perform?: Input using choices "
               "below..."
            << std::endl;
  std::cout << " 1: DFS Traversal" << std::endl
            << " 2: DFS Search" << std::endl
            << " 3: Dijkstra's Search" << std::endl
            << " 4: IDDFS" << std::endl
            << " 5: Get list of vertex names" << std::endl;

  // Verify choice
  int choice;
  std::cin >> choice;
  while (choice < 0 || choice > 5) {
    std::cout << std::endl << "Please make a valid choice! (1, 2, 3, 4, or 5): ";
    std::cin >> choice;
  }

  // Execute choice
  Graph product_graph = ProductUtil::CreateGraph(data, metadata);

  std::ofstream out_stream(output_file);
  if (out_stream.is_open()) {
    if (choice == 1) {
      RunDfsTraversal(product_graph, metadata, out_stream);
    } else if (choice == 2) {
      RunDfsFind(product_graph, metadata, out_stream);
    } else if (choice == 3) {
      RunDijkstra(product_graph, metadata, out_stream);
    } else if (choice == 4) {
      RunIDDFS(product_graph, metadata, out_stream);
    } else if (choice == 5) {
      PrintVertexInfo(product_graph, metadata, out_stream);
    }
  }

  out_stream.close();
};