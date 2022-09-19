#include "graph.h"

Graph::Graph() {}

void Graph::InsertVertex(int id) { vertices_[id]; }

void Graph::RemoveVertex(int id) {
  // Start by removing all occurrences of input vertex in edge list and in
  // other vertex's adjacency lists
  AdjacencyList& adjacent_edges = vertices_.at(id);
  for (list<AdjacencyEdge>::iterator& edge_it : adjacent_edges) {
    // First, remove edge iterator fron adjacency list of the adjacent vertex
    std::pair<int, AdjacencyList::iterator> adjacent_vertex = edge_it->start_;
    if (adjacent_vertex.first == id) {
      // Adjacent id and id are the same, so adjacent id needs to switch
      adjacent_vertex = edge_it->end_;
    }

    AdjacencyList& adjacent_list = vertices_.at(adjacent_vertex.first);
    adjacent_list.erase(adjacent_vertex.second);

    // Second, remove edge from edge list
    edges_.erase(edge_it);
  }

  // Remove entire entry corresponding to vertex with input id
  vertices_.erase(id);
}

bool Graph::IsAdjacent(int v1, int v2) const {
  list<AdjacencyEdge>::const_iterator edge = FindEdge(v1, v2);
  return edge != edges_.end();
}

vector<Edge> Graph::IncidentEdges(int vertex) const {
  const AdjacencyList& adj_list = vertices_.at(vertex);

  vector<Edge> incident_edges{};
  incident_edges.reserve(adj_list.size());

  for (const list<AdjacencyEdge>::iterator& edge_it : adj_list) {
    int start_vertex = edge_it->start_.first;
    int end_vertex = edge_it->end_.first;
    incident_edges.emplace_back(start_vertex, end_vertex, edge_it->weight_);
  }

  return incident_edges;
}

vector<Edge> Graph::OutoingEdges(int vertex) const {
  const AdjacencyList& adj_list = vertices_.at(vertex);

  vector<Edge> outgoing_edges{};

  for (const list<AdjacencyEdge>::iterator& edge_it : adj_list) {
    if (edge_it->start_.first == vertex) {
      int start_vertex = edge_it->start_.first;
      int end_vertex = edge_it->end_.first;
      outgoing_edges.emplace_back(start_vertex, end_vertex, edge_it->weight_);
    }
  }

  return outgoing_edges;
}

vector<int> Graph::AdjacentVertices(int vertex) const {
  vector<Edge> incident_edges = IncidentEdges(vertex);
  vector<int> adjacent_vertices{};

  for (const Edge& edge : incident_edges) {
    if (edge.start_ == vertex) {
      // Then input vertex is start_ and the end_ is the adjacent vertex
      adjacent_vertices.push_back(edge.end_);
    }
  }

  return adjacent_vertices;
}

void Graph::InsertEdge(int v1, int v2, int weight) {
  // Create edge with correct weight but invalid start_ and end_ iterators
  AdjacencyEdge new_edge{};
  new_edge.weight_ = weight;

  // Add edge to list and get iterator to new edge
  edges_.push_front(new_edge);
  list<AdjacencyEdge>::iterator new_edge_it = edges_.begin();

  // Add iterator to new edge to v1 and v2 adjacency lists
  vertices_[v1].push_front(new_edge_it);
  vertices_[v2].push_front(new_edge_it);

  // Get iterator to new entries in v1 and v2 adjacency lists
  AdjacencyList::iterator adj_list_1_it = vertices_[v1].begin();
  AdjacencyList::iterator adj_list_2_it = vertices_[v2].begin();

  // Update start_ and end_ of new edge to point at v1 and v2 adjacency lists
  new_edge_it->start_ =
      std::pair<int, AdjacencyList::iterator>{v1, adj_list_1_it};
  new_edge_it->end_ =
      std::pair<int, AdjacencyList::iterator>{v2, adj_list_2_it};
}

void Graph::RemoveEdge(int v1, int v2) {
  list<AdjacencyEdge>::iterator edge_to_remove = FindEdge(v1, v2);
  if (edge_to_remove == edges_.end()) {
    throw std::invalid_argument("Edge could not be found");
  }

  // Get iterators to correct location at each adjacency list
  int start_vertex = edge_to_remove->start_.first;
  AdjacencyList::iterator start_adj_it = edge_to_remove->start_.second;
  int end_vertex = edge_to_remove->end_.first;
  AdjacencyList::iterator end_adj_it = edge_to_remove->end_.second;

  // Erase edge iterators from each adjacency list
  vertices_.at(start_vertex).erase(start_adj_it);
  vertices_.at(end_vertex).erase(end_adj_it);

  // Erase edge from edge list
  edges_.erase(edge_to_remove);
}

Edge Graph::GetEdge(int v1, int v2) const {
  list<AdjacencyEdge>::const_iterator edge = FindEdge(v1, v2);
  if (edge == edges_.end()) {
    throw std::invalid_argument("Edge could not be found");
  }
  return Edge(edge->start_.first, edge->end_.first, edge->weight_);
}

vector<int> Graph::GetVertices() const {
  vector<int> vertices{};
  vertices.reserve(vertices_.size());

  for (const std::pair<const int, AdjacencyList>& vertex_pair : vertices_) {
    // Keep appending vertex ids
    vertices.push_back(vertex_pair.first);
  }

  return vertices;
}

vector<Edge> Graph::GetEdges() const {
  vector<Edge> edges{};
  edges.reserve(edges_.size());

  for (const AdjacencyEdge& adj_edge : edges_) {
    // Keep appending edge data
    int start_vertex = adj_edge.start_.first;
    int end_vertex = adj_edge.end_.first;
    edges.emplace_back(start_vertex, end_vertex, adj_edge.weight_);
  }

  return edges;
}

list<Graph::AdjacencyEdge>::iterator Graph::FindEdge(int v1, int v2) {
  int degree_1 = vertices_.at(v1).size();
  int degree_2 = vertices_.at(v2).size();

  if (degree_1 <= degree_2) {
    // Search vertex_1 adjacency list for vertex_2 as an end vertex
    for (const list<AdjacencyEdge>::iterator& edge_it : vertices_.at(v1)) {
      if (edge_it->end_.first == v2) {
        return edge_it;
      }
    }
  } else {
    // Search vertex_2 adjacency list for vertex_1 as start vertex
    for (const list<AdjacencyEdge>::iterator& edge_it : vertices_.at(v2)) {
      if (edge_it->start_.first == v1) {
        return edge_it;
      }
    }
  }

  return edges_.end();
}

list<Graph::AdjacencyEdge>::const_iterator Graph::FindEdge(int v1,
                                                           int v2) const {
  int degree_1 = vertices_.at(v1).size();
  int degree_2 = vertices_.at(v2).size();

  if (degree_1 <= degree_2) {
    // Search vertex_1 adjacency list for vertex_2 as an end vertex
    for (const list<AdjacencyEdge>::iterator& edge_it : vertices_.at(v1)) {
      if (edge_it->end_.first == v2) {
        return edge_it;
      }
    }
  } else {
    // Search vertex_2 adjacency list for vertex_1 as start vertex
    for (const list<AdjacencyEdge>::iterator& edge_it : vertices_.at(v2)) {
      if (edge_it->start_.first == v1) {
        return edge_it;
      }
    }
  }

  return edges_.end();
}

bool Graph::VertexExists(int id) const {
  return vertices_.find(id) != vertices_.end();
}

size_t Graph::GetNumVertices() const { return vertices_.size(); }

size_t Graph::GetNumEdges() const { return edges_.size(); }