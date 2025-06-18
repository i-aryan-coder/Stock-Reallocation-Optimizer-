#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>
#include <unordered_map>
#include <utility>

// Type alias for graph representation: node -> list of (neighbour, weight)
using namespace std;
using Graph = unordered_map<string, vector<pair<string, double>>>;

// Function prototype for Dijkstra’s algorithm
pair<vector<string>, double> dijkstra(const Graph& graph, const string& start, const string& end);

#endif
