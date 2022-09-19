#include "IDDFS.h"


IDDFS::IDDFS(const Graph & graph) : graph_(graph), path_(vector<int>()){}

bool IDDFS::DLS(int start, int target, int limit, std::unordered_set<int>& visited) {
    visited.insert(start);
    if (start == target) {
        return true;
    }
    if (limit <= 0) { // gone past limit, return false
        return false;
    }
    vector<int> adjacent = graph_.AdjacentVertices(start);
    for (int adj_vert : adjacent) {
        if (visited.find(adj_vert) != visited.end()) {
            continue;
        }
        if (DLS(adj_vert, target, limit-1, visited)) {
            path_.push_back(adj_vert);
            return true;
        }
    }
    return false;
}

bool IDDFS::search(int start, int target, int max_depth) {
    std::vector<int> vertices = graph_.GetVertices();
    path_.clear();
    // ensure the start and target vertices are in the graph
    if (vertices.size() == 0 || std::find(vertices.begin(), vertices.end(), start) == vertices.end()) {
        throw std::invalid_argument("Start vertex could not be found");
    }
    if (std::find(vertices.begin(), vertices.end(), target) == vertices.end()) {
        throw std::invalid_argument("Target vertex could not be found");
    }
    for (int i = 0; i <= max_depth; i++) {
        std::unordered_set<int> visited;
        if (DLS(start, target, i, visited)) {
            path_.push_back(start);
            return true;
        }
    }
    return false;
}

vector<int> IDDFS::get_path(int start, int target, int limit) {
    if (search(start, target, limit)) {
        std::reverse(path_.begin(), path_.end());
    } else {
        throw std::invalid_argument("No valid path within limit from source to target");
    }
    return path_;
}
