#pragma once

#include <list>
#include <unordered_map>
#include <utility>
#include <vector>

using std::list;
using std::unordered_map;
using std::vector;

/*
 * A directed edge with a start vertex, end vertex, and weight
 */
struct Edge {
  int start_;
  int end_;
  int weight_;

  Edge(int start, int end, int weight)
      : start_(start), end_(end), weight_(weight) {}

  bool operator==(const Edge& other) const {
    return start_ == other.start_ && end_ == other.end_ &&
           weight_ == other.weight_;
  }

  bool operator<(const Edge& other) const { return weight_ < other.weight_; }
};

/*
 * A directed graph data structure that matches the Stanford Amazon data
 * interface Nodes are stored as integers, which represent product ids. Edges
 * contain weights, which are also stored as integers.
 * For time complexity: deg(v) = indegree(v) + outdegree(v)
 */
class Graph {
 public:
  /*
   * Default construct graph without any edges or vertices
   */
  Graph();

  /*
   * Adds vertex to vertex list if vertex doesn't already exist.
   * Adjacency list will be empty when a vertex if first inserted
   * Time complexity: O(1)
   */
  void InsertVertex(int id);

  /*
   * Removes vertex from vertex list if it exists. Throws exception if vertex
   * does not exist. Also removes all edges incident to the input vertex
   * Time complexity: O(deg(v))
   */
  void RemoveVertex(int id);

  /*
   * Adds edge to edge list if edge doesn't already exist
   * Adds iterator to edge to adjacency list of both vertices
   * Time complexity: O(1)
   */
  void InsertEdge(int v1, int v2, int weight);

  /*
   * Remove edge given incident vertices. Throws exception if either vertex is
   * not found.
   * Time complexity: O(min(deg(v1), deg(v2)))
   */
  void RemoveEdge(int v1, int v2);

  /*
   * Get edge given incident vertices. Throws exception if either vertex is
   * not found.
   * Time complexity: O(min(deg(v1), deg(v2)))
   */
  Edge GetEdge(int v1, int v2) const;

  /*
   * Checks if vertex_2 is adjacent to vertex_1.
   * Vertex_2 is adjacent to vertex_1 if there is an edge going from
   * vertex_1 to vertex_2
   * Time complexity: min(deg(v1), deg(v2))
   */
  bool IsAdjacent(int v1, int v2) const;

  /*
   * Returns all incident edges to a vertex. Gives ingoing and outgoing edges
   * Throws exception if not found.
   * Time complexity: O(deg(v))
   */
  vector<Edge> IncidentEdges(int vertex) const;

  /*
   * Returns all outgoing edges from a vertex. Gives ingoing and outgoing edges
   * Throws exception if not found.
   * Time complexity: O(deg(v))
   */
  vector<Edge> OutoingEdges(int vertex) const;

  /*
   * Returns all adjacent vertices to a vertex. Every outgoing edge from
   * input vertex will lead to an adjacent vertex
   * Time complexity: O(deg(v)) amortized (because of vector appending)
   */
  vector<int> AdjacentVertices(int vertex) const;

  /*
   * Gets all vertices in graph by copying vertex names in vertex list
   * Time complexity: O(n)
   */
  vector<int> GetVertices() const;

  /*
   * Gets all edges in graph by copying edge data in edge list
   * Time complexity: O(m)
   */
  vector<Edge> GetEdges() const;

  /*
   * Checks if a vertex exists in the graph
   * Time complexity: O(1)
   */
  bool VertexExists(int id) const;

  /*
   * Time complexity: O(1)
   */
  size_t GetNumEdges() const;

  /*
   * Time complexity: O(1)
   */
  size_t GetNumVertices() const;

 private:
  // Forward declare AdjacencyEdge struct
  struct AdjacencyEdge;

  // Every element in adjacency list is an iterator to an edge list
  // Therefore, an adjacency list is a list of iterators to an edge list
  using AdjacencyList = list<list<AdjacencyEdge>::iterator>;

  /*
   * Internal edge struct to track pointers to adjacency lists
   */
  struct AdjacencyEdge {
    /*
     * start_ and end_ are pairs of vertices and their corresponding edge in the
     * adjacency list. It's less confusing if you think of start_ and end_ as
     * iterators to an adjacency list. But technically, start_ and end_ are
     * iterators to a list of iterators to an edge list.
     */
    std::pair<int, AdjacencyList::iterator> start_;
    std::pair<int, AdjacencyList::iterator> end_;
    int weight_;
  };

  unordered_map<int, AdjacencyList> vertices_;
  list<AdjacencyEdge> edges_;

  // Helper functions

  /*
   * Find an edge with vertices. Returns edge_.end() if not found.
   * Time complexity: O(min(deg(v1), deg(v2)))
   */
  list<AdjacencyEdge>::iterator FindEdge(int v1, int v2);

  /*
   * Find an edge with vertices. Returns edge_.end() if not found.
   * Time complexity: O(min(deg(v1), deg(v2)))
   */
  list<AdjacencyEdge>::const_iterator FindEdge(int v1, int v2) const;
};