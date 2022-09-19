#include "DFS.h"
#include <unordered_map>
#include <algorithm>


using namespace std;

DFS::DFS(const Graph & graph) : graph_(graph){}

vector<int> DFS::traverse(int start) {
    std::vector<int> vertices = graph_.GetVertices();
    if (vertices.size() == 0 || std::find(vertices.begin(), vertices.end(), start) == vertices.end()) {
        throw std::invalid_argument("Start vertex could not be found");
    }

    std::stack<int> dfs_s;
    std::unordered_map<int, bool> visited;
    for (int vertex : vertices) {
        visited[vertex] = false;
    }

    std::vector<int> traversal;
    int current = start;
    dfs_s.push(current);
    visited[start] = true;

    while(dfs_s.size() > 0) {
        current = dfs_s.top();
        while(dfs_s.size() > 1 && visited[current]) {   // pops off already visited vertices on the stack
            dfs_s.pop();
            current = dfs_s.top();
        }
        if (dfs_s.size() == 1 && current != start && visited[current]) {
            break;
        }

        dfs_s.pop();
        traversal.push_back(current);

        vector<int> adjacent = graph_.AdjacentVertices(current);
        if (adjacent.size() > 0) {
            for (int vertex : adjacent) {
                if (!visited[vertex]) {
                    dfs_s.push(vertex);
                }
            }
        }
        visited[current] = true;

    }
    return traversal;
}

vector<int> DFS::find(int start, int target) {
    std::vector<int> vertices = graph_.GetVertices();
    if (std::find(vertices.begin(), vertices.end(), start) == vertices.end()) {
        throw std::invalid_argument("Start vertex could not be found");
    }

    std::stack<int> dfs_s;
    std::unordered_map<int, bool> visited;
    for (int vertex : vertices) {
        visited[vertex] = false;
    }

    std::unordered_map<int,int> previous;
    int current = start;
    dfs_s.push(start);
    visited[start] = true;

    while(dfs_s.size() > 0) {
        current = dfs_s.top();
        while(dfs_s.size() > 1 && visited[current]) {
            dfs_s.pop();
            current = dfs_s.top();
        }
        if (current != start && visited[current]) {
            break;
        }
        dfs_s.pop();

        if(current == target) {
            vector<int> path;
            int tail = target;
            while (tail != start) {
                path.push_back(tail);
                tail = previous[tail];
            }
            path.push_back(start);
            std::reverse(path.begin(), path.end());
            return path;
        }

        vector<int> adjacent = graph_.AdjacentVertices(current);
        if (adjacent.size() > 0) {
            for (int vertex : graph_.AdjacentVertices(current)) {
                if (!visited[vertex]) {
                    dfs_s.push(vertex);
                    previous[vertex] = current;
                }
            }
        }
        visited[current] = true;

    }
    vector<int> empty;
    return empty;
}