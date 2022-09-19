#include "dijkstra.h"
#include <iostream>

vector<int> dijkstra(const Graph & g, int source, int dest){
    unordered_map<int, int> distance; // Maps a node with given key to its distance from the source
    unordered_map<int, int> previous; // Maps a node with given key to its previous node in the traversal order
    unordered_map<int, bool> visited; // Maps a node to a boolean that holds whether or not the node was visited
    std::priority_queue<intpair, vector<intpair>, std::greater<intpair>> queue; // A priority queue that sorts nodes based on distance, with the smallest at the top
    
    previous.insert(std::make_pair(source, -1)); // Adds the source's previous node as -1, which is an invalid ID
    queue.push(std::make_pair(0, source)); // Adds the source to the queue, with distance zero (distance is first in order to make the queue prioritize low distance)
    distance.insert(std::make_pair(source, 0)); // Sets the mapped distance of source to zero

    // Initializes the maps with the default values for distance and visitation status
    for(int vert : g.GetVertices()){
        distance.insert(std::make_pair(vert, __INT_MAX__));
        visited.insert(std::make_pair(vert, false));
    }

    while(!queue.empty()){
        // Stores the vertex with the current highest priority (lowest distance),
        // which is the source the first run through, then pops from the queue
        int vert = queue.top().second;
        queue.pop();
        if(vert == dest){ break; } // If we have reached the destination. If not,
        // for each of the current node's neighbors, if they are unvisited, 
        // then, if their distance should be updated, it is, then the previous
        // neighbor is stored into the previous map
        vector<Edge> edgevert = g.OutoingEdges(vert);
        for(const Edge& e : edgevert){
            int adj = e.end_;
            if(!visited.at(adj)){
                if(distance.at(adj) > distance.at(vert) + e.weight_){
                    distance.at(adj) = distance.at(vert) + e.weight_;
                    queue.push(std::make_pair(distance.at(adj), adj)); // Queues the adjacent vertex
                    previous.insert(std::make_pair(adj, vert));
                }
            }
        }
        // Sets the current node to visited
        visited.at(vert) = true;
    }

    vector<int> path;
    // Next, the path is extracted from the previous map in reverse, then returned
    int prev = dest;
    while(prev != -1){
        path.insert(path.begin(), prev);
        prev = previous.at(prev);
    }
    return path;
}
