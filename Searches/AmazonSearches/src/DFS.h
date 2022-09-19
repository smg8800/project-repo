#pragma once
#include "graph.h"
#include <stack>
#include <vector>


using namespace std;

class DFS {
public:
    /**
     * Overloaded constructor.
     * @param graph object
     */
    DFS(const Graph & graph);

    /**
     * Traverses graph from start vertex in DFS order.
     * Time Complexity: O(n)
     * @param start integer representing where to start traversing from in graph
     * @return vector of integers following in DFS order of visits
     */
    vector<int> traverse(int start);

    /**
     * Finds path between start and target vertices in graphs.
     * Time Complexity: O(n)
     * @param start integer representing where to start traversing from in graph
     * @param target integer representing vertex to find
     * @return path vector of integers representing path between start and target
     */
    vector<int> find(int start, int target);

private:
    const Graph graph_;


};