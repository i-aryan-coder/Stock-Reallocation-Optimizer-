#include "graph.h"
#include <queue>
#include <unordered_map>
#include <limits>
#include <set>

using namespace std;

// Dijkstra's algorithm to compute shortest path from start to end
pair<vector<string>, double> dijkstra(const Graph& graph, const string& start, const string& end) {
    unordered_map<string, double> dist;         // Distance from start to node
    unordered_map<string, string> prev;         // To reconstruct path
    set<pair<double, string>> pq;               // Min-priority queue

    // Initialize distances to infinity
    for (const auto& [node, _] : graph) {
        dist[node] = numeric_limits<double>::infinity();
    }

    dist[start] = 0;
    pq.insert({0, start});

    while (!pq.empty()) {
        auto [cur_dist, node] = *pq.begin();
        pq.erase(pq.begin());

        if (node == end) break;

        for (const auto& [neighbor, weight] : graph.at(node)) {
            double new_dist = cur_dist + weight;
            if (new_dist < dist[neighbor]) {
                pq.erase({dist[neighbor], neighbor});  // Remove old if exists
                dist[neighbor] = new_dist;
                prev[neighbor] = node;
                pq.insert({new_dist, neighbor});
            }
        }
    }

    if (dist[end] == numeric_limits<double>::infinity()) {
        return {{}, -1};  // No path found
    }

    // Reconstruct path
    vector<string> path;
    for (string at = end; at != ""; at = prev.count(at) ? prev[at] : "") {
        path.insert(path.begin(), at);
    }

    return {path, dist[end]};
}
