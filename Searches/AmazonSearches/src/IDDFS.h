#pragma once
#include "graph.h"
#include <stack>
#include <vector>
#include <limits>
#include <unordered_set>

using namespace std;

class IDDFS {
    public:
        /*
        * Initializes an IDDFS object with a given graph and empty path.
        */
        IDDFS(const Graph & graph);

        /* 
        * Function calls DLS on the given starting vertex with increasing depth.
        * Will throw expection if the given graph is invalid,
        * or if the start or target vertices are not in the graph.
        * Returns true if the target vertex was found within a max_depth, false otherwise.
        * Populates the path_ vector if a path from the source to the target is found.
        * Runtime: O(b^d) where d is the depth of the target and 
        * b is the average number of adjacent vertices per vertex.
        */
        bool search(int start, int target, int max_depth);

        /* 
        * Depth Limited Search
        * Recursive function called on all adjacent vertices to the start vertex.
        * Returns true if the recursive call returns true, false otherwise.
        */
        bool DLS(int start, int target, int limit, std::unordered_set<int>& set);

        /*
        * Utilizes the search function to return a path in the form of a vector of ints.
        * Same runtime as search()
        */
        vector<int> get_path(int start, int target, int limit);

    private:
        /*
        * Stores graph to be traversed.
        */
        const Graph graph_;
        /*
        * Stores path from most recent call of search.
        */
        vector<int> path_;
};