
#include "data.h"
#include "DFS.h"
#include "graph.h"

#include <iostream>
#include <vector>

#include "data.h"
#include "metadata.h"

using namespace std;

// This file is a temporary driver to test functions that have been made
void TestData() {
  Data data;
  data.read_from_file("amazon.txt");
  vector<int> to = data.getNodesTo();
  vector<int> from = data.getNodesFrom();
  for (size_t i = 0; i < to.size(); i++) {  // print out all pairs in order
    cout << from[i] << " : " << to[i] << endl;
  }
  cout
      << from[11] * to[11] << " ?= 22"
      << endl;  // check a random idx to check string to int conversion happened
}

void TestMetaData() {
    Metadata metadata;
    metadata.read_from_file("data_files/amazon-meta.txt");

    // metadata.GetAsins(1);
}

int main() {

    TestMetaData();
}