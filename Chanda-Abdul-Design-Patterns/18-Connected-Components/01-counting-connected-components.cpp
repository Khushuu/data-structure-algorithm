// Introduction to Connected Components and Strongly Connected Components in Graphs

// Connected and Strongly Connected Components in a Graph

// Connected Components: Undirected Graph
// Strongly Connected Components: Directed Graph
// DFS/BFS are efficient for O(N + E) solution.

// Union-Find (Best for Large Graphs)

// -------------------------------------------------------------------------------------------------------------
// 1️⃣ Connected Components (Undirected Graph)

// A connected component is a maximal set of vertices where there is a path between any two vertices.

// If a node is reachable from another node, they belong to the same connected component.
// Any node not reachable from a component forms a separate component.

// ✅ Example:
// Graph with 6 nodes (0 to 5)

//   0 -- 1    3 -- 4
//   |           |
//   2          5


// 👉 This graph has two connected components:

// {0, 1, 2}
// {3, 4, 5}

// -------------------------------------------------------------------------------------------------------------

// 2️⃣ Strongly Connected Components (Directed Graph)

// A Strongly Connected Component (SCC) in a directed graph is a maximal subset of nodes where every node can reach every other node in the component.

// ✅ Example:


//   A → B
//   ↑   ↓
//   D ← C
// 👉 {A, B, C, D} forms one SCC, since every node can reach every other.

// ⏩ Finding SCCs: Kosaraju's Algorithm and Tarjan's Algorithm (both O(N + E))

// -------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------

// PROBLEM and CODE

// Finding Number of Connected Components (Undirected Graph)
// We can use DFS or BFS to count the number of connected components.

// DFS-Based Approach
// Use a visited array to track visited nodes.
// Perform DFS from each unvisited node, marking all reachable nodes.
// Each DFS call represents a new connected component.

// T.C = O(N + E)	
// S.C = O(N + E) (Adjacency List)
// ---------------------------------------------------------------------------------------------------

void dfs(int node, vector<vector<int>>& graph, vector<bool>& visited) {

    visited[node] = true;

    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            dfs(neighbor, graph, visited);
        }
    }
}

int countConnectedComponents(int n, vector<vector<int>>& edges) {

    vector<vector<int>> graph(n);
    vector<bool> visited(n, false);
    
    // Build adjacency list - graph
    for (auto& edge : edges) {
        graph[edge[0]].push_back(edge[1]);
        graph[edge[1]].push_back(edge[0]); // Undirected graph
    }

    int components = 0;

	// count no. of connected components
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            components++; // A new connected component found
            dfs(i, graph, visited);
        }
    }

    return components;
}

int main() {
    int n = 6;
    vector<vector<int>> edges = {{0, 1}, {1, 2}, {3, 4}, {4, 5}};

    cout << "Number of connected components: " << countConnectedComponents(n, edges) << endl;
    return 0;
}


// ---------------------------------------------------------------------------------------------------

// Leetcode problems
// 323: Number of Connected Components in an Undirected Graph
// 547. Number of Provinces (Graph connected components)
// 200. Number of Islands (Grid-based connected components)
// 924. Minimize Malware Spread (Graph traversal & components)