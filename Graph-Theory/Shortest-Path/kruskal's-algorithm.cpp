// Kruskal's algorithm for Minimum Spanning Tree
// Minimum Spanning tree - tree formed from a weighted graph with minimum sum of weight

// Kruskal’s algorithm is a greedy algorithm used to find the Minimum Spanning Tree (MST) of a connected, weighted, and undirected graph.

// 1. Key Concepts

// Minimum Spanning Tree (MST)
// A spanning tree is a subset of edges that connects all vertices of the graph without forming any cycles.
// The minimum spanning tree (MST) is the spanning tree with the minimum possible total edge weight.

// Greedy Approach in Kruskal’s Algorithm
// Kruskal’s algorithm greedily picks the smallest weight edge that does not form a cycle until all vertices are connected.


// 2. Steps of Kruskal’s Algorithm

// Sort all edges in ascending order of their weights.
// Use the Union-Find (Disjoint Set) data structure to keep track of connected components.
// Iterate through the sorted edges:
// If adding the edge does not form a cycle, add it to the MST.
// Otherwise, discard the edge.
// Repeat until the MST contains (V - 1) edges (where V is the number of vertices).

// 4. Explanation of Code

// Edge Representation: We use a structure Edge to store (u, v, weight).
// Sorting Edges: We sort edges in ascending order of weight.
// Union-Find (Disjoint Set) Implementation:
// find() with path compression to optimize parent lookup.
// unionSet() with union by rank to merge sets efficiently.

// Building the MST:
// Traverse sorted edges.
// If two endpoints belong to different sets, include the edge and merge the sets.
// Stop when we have V - 1 edges.

// 🔥 Time Complexity
// Operation					Complexity
// Sorting edges				O(E log E)
// Find with Path Compression	O(α(N)) (almost constant)
// Union by Size				O(α(N))

// Total Kruskal’s Algorithm	O(E log E)
Total Space Complexity: O(E+V)

// ----------------------------------------------------------------------------------------------
#include <bits/stdc++.h>
using namespace std;

vector<int> parent, sizeSet;

// 🔹 Initialize Disjoint Set Union (DSU)
void makeSet(int n) {
    parent.resize(n);
    sizeSet.resize(n, 1);  // Initialize size of each set as 1
    for (int i = 0; i < n; i++) parent[i] = i;
}

// 🔹 Find with Path Compression
int find(int x) {
    if (parent[x] == x) return x; 
    return parent[x] = find(parent[x]);  // Path compression
}

// 🔹 Union function using **Union by Rank**
void unionSet(int x, int y) {

    int rootX = find(x);  // Find root of x
    int rootY = find(y);  // Find root of y

    if (rootX != rootY) {  // Merge only if they belong to different components
        if (rankSet[rootX] < rankSet[rootY]) {
            parent[rootX] = rootY;  // Attach smaller tree under larger tree
        } 
        else if (rankSet[rootX] > rankSet[rootY]) {
            parent[rootY] = rootX;
        } 
        else {
            parent[rootY] = rootX;  // If ranks are equal, attach one and increase rank
            rankSet[rootX]++;
        }
    }
}

// 🔹 Kruskal’s Algorithm for Minimum Spanning Tree (MST)
int kruskal(int n, vector<vector<int>>& edges) {

    makeSet(n);
    
    // Sort edges by weight
    sort(edges.begin(), edges.end(), [](auto& a, auto& b) { return a[2] < b[2]; });

    int mstCost = 0, edgeCount = 0;
    
    for (auto& edge : edges) {

        int u = edge[0], v = edge[1], w = edge[2];

        int rootU = find(u);
        int rootV = find(v);

        if (rootU != rootV) {  // If different components, merge them
            unionSet(rootU, rootV);  
            mstCost += w; // Add edge weight to MST
            edgeCount++;
            if (edgeCount == n - 1) break;  // Stop early if MST is complete
        }
    }

    return (edgeCount == n - 1) ? mstCost : -1;  // Return -1 if MST is not possible
}

int main() {
    int n = 5;  // Number of nodes
    vector<vector<int>> edges = {
        {0, 1, 10}, {0, 2, 6}, {0, 3, 5}, {1, 3, 15}, {2, 3, 4}
    };

    int mstWeight = kruskal(n, edges);
    if (mstWeight != -1) 
        cout << "Minimum Cost of MST: " << mstWeight << endl;
    else 
        cout << "MST not possible" << endl;

    return 0;
}

// ------------------------------------------------------------------------------------------------