#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include "graph.h"

using namespace std;

// Account structure to store type and parent relationship
struct Account {
    string type;     // "source" or "demand"
    string parent;   // Parent account group (e.g., fund or institution)
};

int main() {
    // Define accounts and their relationships
    unordered_map<string, Account> accounts;
    unordered_map<string, unordered_map<string, double>> balances; // parent -> account -> stock quantity
    unordered_map<string, unordered_map<string, double>> prices;   // parent -> stock -> price
    Graph graph;

    // Example data setup
    accounts["Loc1"] = {"source", "P1"};
    accounts["Loc2"] = {"source", "P1"};
    accounts["Loc3"] = {"demand", "P1"};
    accounts["Loc4"] = {"demand", "P2"};
    accounts["Loc5"] = {"source", "P2"};

    // Graph: edges between eligible account transfers
    graph["Loc1"].push_back({"Loc2", 1});
    graph["Loc1"].push_back({"Loc3", 2});
    graph["Loc2"].push_back({"Loc3", 1});
    graph["Loc5"].push_back({"Loc4", 1});
    graph["Loc3"].push_back({"Loc4", 3});

    // Balances (positive = excess, negative = demand)
    balances["P1"]["Loc1"] = 10;
    balances["P1"]["Loc2"] = 5;
    balances["P1"]["Loc3"] = -10;
    balances["P2"]["Loc4"] = -5;
    balances["P2"]["Loc5"] = 5;

    // Prices of a sample stock
    prices["P1"]["StockX"] = 150.0;
    prices["P2"]["StockX"] = 100.0;

    // Output transfer result
    vector<tuple<string, string, string, double>> output;

    // Process each parent group separately
    for (const auto& [parent, stockMap] : balances) {
        vector<string> sources, demands;

        // Categorize accounts
        for (const auto& [acc, bal] : stockMap) {
            if (bal > 0) sources.push_back(acc);
            if (bal < 0) demands.push_back(acc);
        }

        // Prioritize source accounts by descending balance
        sort(sources.begin(), sources.end(), [&](const string& a, const string& b) {
            return balances.at(parent).at(a) > balances.at(parent).at(b);
        });

        // For each demand, try to fulfill from sources
        for (const auto& demand : demands) {
            double needed = -balances[parent][demand];

            for (const auto& source : sources) {
                if (balances[parent][source] == 0) continue;

                // Find shortest path from source to demand
                auto [path, cost] = dijkstra(graph, source, demand);
                if (path.empty()) continue;

                // Transfer as much as possible
                double transfer = min(needed, balances[parent][source]);
                output.emplace_back(parent, source, demand, transfer);

                // Update balances
                balances[parent][source] -= transfer;
                balances[parent][demand] += transfer;
                needed -= transfer;

                if (needed <= 0) break;
            }
        }
    }

    // Step 4: Output all valid reallocations
    for (auto& [parent, from, to, qty] : output) {
        cout << parent << "," << from << "," << to << "," << qty << "\n";
    }

    return 0;
}
