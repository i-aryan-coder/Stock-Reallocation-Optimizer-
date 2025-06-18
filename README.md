# Graph-Based Stock Reallocation Optimization Using Dijkstra’s Algorithm

A C++ application that models and optimizes stock transfers between hedge‑fund accounts. It uses Dijkstra’s algorithm on a weighted directed graph to minimize transaction costs while satisfying client demands and pledging excess stock to triparty accounts.

---

## Features

- **Graph‑based modeling** of eligible stock flows:  
  - Nodes represent accounts.  
  - Directed, weighted edges represent allowed stock transfers (intra‑parent moves cost less than inter‑parent).  
- **Dijkstra’s shortest‑path algorithm** to compute minimal‑cost transfer routes.  
- **Demand‑supply matching**: excess holdings are routed to cover deficits first, then any remaining supply is sent to triparty accounts.  
- **Priority ordering**: stocks processed in descending order of price to maximize cash realization.  

---

## File Structure
- ├── main.cpp # Entry point: sets up sample data, runs matching & routing
- ├── graph.h # Graph type alias & Dijkstra function declaration
- ├── graph.cpp # Dijkstra’s algorithm implementation using a min‑priority queue
- └── README.md # This documentation

## How It Works

### Data Setup
- Define accounts with types (“source” vs “demand”) and parent groups.
- Populate a graph of eligible flows with custom edge weights.
- Provide balance map:  
  - Positive values = supply  
  - Negative values = demand

### Source–Demand Matching
- Sort source accounts by descending supply.
- For each demand node, run Dijkstra from each source to find the cheapest path.
- Transfer as much as possible along that path.

###  Excess Pledging
- After all demands are met, any remaining supply is routed to “triparty” accounts using shortest‑path logic.

---

## ⏱ Complexity

- **Dijkstra’s algorithm (single run):** `O(M log N)`
- **Total matching & routing:** `O(N_sources × N_demands × M log N)`
- **Space Complexity:**  
  - `O(N + M)` for the graph  
  - `O(N)` for distance & predecessor maps
- **Lookup Times:**  
  - `unordered_map` average: `O(1)`  
  - Iterating adjacency list: `O(degree(node))`

---
