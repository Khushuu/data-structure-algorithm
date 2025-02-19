// Tarjan’s Algorithm
// an efficient method to find Strongly Connected Components (SCCs) in a directed graph using DFS (Depth First Search). It finds all SCCs in O(V + E) time 

// Low-Link Values
// The low-link value of a node u, low[u], represents:
// The smallest discovery time of any node reachable from u, including back edges.

// This helps in identifying SCCs.

// Stack to Track Nodes in SCC
// Tarjan’s Algorithm uses a stack to track nodes currently in the SCC being explored.
// Once an SCC is found, all its nodes are popped from the stack.

// Back Edges & Root Nodes
// Back Edge: If a node u connects to an already visited ancestor in the DFS tree, it forms a cycle.
// The "root" node of an SCC is the earliest node in the DFS from which all SCC nodes are reachable.


// 🔹 Tarjan’s Algorithm (Step-by-Step)
// Initialize arrays:

// disc[u]: Stores discovery time of node u (-1 if unvisited).
// low[u]: Stores lowest reachable discovery time from u.
// inStack[u]: Boolean array to check if u is in the stack.

// Perform DFS Traversal:
// Assign discovery time and low-link value to each node.
// Push node to stack.
// Visit all neighbors:
// If unvisited, call DFS recursively.
// If visited and still in stack, update low[u].
// After DFS completes for a node:
// If low[u] == disc[u], a new SCC root is found.
// Pop all nodes in this SCC from the stack.

// Time Complexity	O(V + E) → Each node is visited once, and each edge is processed once.
// Space Complexity	O(V + E) → Adjacency list, stack, and arrays (disc, low, inStack).
// --------------------------------------------------------------------------------------------------------------

#include <bits/stdc++.h>
using namespace std;

class TarjanSCC {
private:
    int time; // Time counter
    vector<int> disc, low;
    vector<bool> inStack;
    stack<int> stk;
    vector<vector<int>> graph;
    vector<vector<int>> sccs; // Store all SCCs

    void dfs(int u) {
        disc[u] = low[u] = time++; // Set discovery time and low-link value
        stk.push(u);
        inStack[u] = true;

        for (int v : graph[u]) {
            if (disc[v] == -1) { // If v is unvisited
                dfs(v);
                low[u] = min(low[u], low[v]); // Update low-link value
            }
            else if (inStack[v]) { // If v is in stack, it's a back edge
                low[u] = min(low[u], disc[v]);
            }
        }

        // If u is the root of an SCC
        if (low[u] == disc[u]) {
            vector<int> scc;
            while (true) {
                int v = stk.top(); stk.pop();
                inStack[v] = false;
                scc.push_back(v);
                if (v == u) break;
            }
            sccs.push_back(scc);
        }
    }

public:
    TarjanSCC(int n, vector<vector<int>>& edges) {

        time = 0;
        graph.resize(n);
        disc.assign(n, -1);
        low.assign(n, -1);
        inStack.assign(n, false);

        // Build adjacency list
        for (auto& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
        }

        // Run DFS for all unvisited nodes
        for (int i = 0; i < n; i++) {
            if (disc[i] == -1) {
                dfs(i);
            }
        }
    }

    vector<vector<int>> getSCCs() {
        return sccs;
    }
};

// Driver code
int main() {
    int n = 5; // Number of nodes
    vector<vector<int>> edges = {{0, 2}, {2, 1}, {1, 0}, {1, 3}, {3, 4}};

    TarjanSCC solver(n, edges);
    vector<vector<int>> sccs = solver.getSCCs();

    cout << "Strongly Connected Components:\n";
    for (auto& scc : sccs) {
        for (int node : scc) {
            cout << node << " ";
        }
        cout << endl;
    }
    return 0;
}

// ---------------------------------------------------------------------------------------------------------------