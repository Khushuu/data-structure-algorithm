// To determine whether an **undirected graph is a tree**, the graph must satisfy **both** conditions:

// 1. It has exactly **`n - 1` edges**.
// 2. It is **connected** (every node is reachable from any other node).

// NOTE: 
// a tree has n-1 edges and is connected. i.e it has exactly one connected component.
// so if m == n-1 and the graph is connected, then it is a tree.

// A DFS (or BFS) traversal can be used to check connectivity.

// -------------------------------------------------------------------------------------------------------------

// approach
// run dfs on the root node 
// now check the visited array and if there is any node i.e not visited return false
// a not visited node means the graph is not connected and hence it is not a tree

// ## C++ Code (Using DFS)

#include <iostream>
#include <vector>
using namespace std;

void dfs(int node, vector<vector<int>> &adj, vector<bool> &visited) {
    visited[node] = true;

    for (int neighbor : adj[node]) {
        if (!visited[neighbor]) {
            dfs(neighbor, adj, visited);
        }
    }
}

bool isTree(int n, int m, vector<pair<int, int>> &edges) {

    // Condition 1: Tree must have exactly n-1 edges
    if (m != n - 1)
        return false;

    // Build adjacency list
    vector<vector<int>> adj(n);

    for (auto edge : edges) {
        int u = edge.first;
        int v = edge.second;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Check connectivity using DFS
    vector<bool> visited(n, false);
    dfs(0, adj, visited);

    for (bool nodeVisited : visited) {
        if (!nodeVisited)
            return false;
    }

    return true;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<pair<int, int>> edges;

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        edges.push_back({u, v});
    }

    if (isTree(n, m, edges))
        cout << "Graph is a Tree\n";
    else
        cout << "Graph is NOT a Tree\n";

    return 0;
}

-------------------------------------------------------------------------------------------------------------------

// ## Input Format

// ```
// Number of Nodes Number of Edges
// u1 v1
// u2 v2
// ...
// um vm
// ```

// ### Example 1

// **Input**

// ```
// 5 4
// 0 1
// 0 2
// 1 3
// 1 4
// ```

// **Output**

// ```
// Graph is a Tree
// ```

// ---

// ### Example 2

// **Input**

// ```
// 5 5
// 0 1
// 1 2
// 2 3
// 3 4
// 4 0
// ```

// **Output**

// ```
// Graph is NOT a Tree
// ```

// ---

// ## Explanation

// ### Step 1: Check Number of Edges

// A tree with `n` nodes **must** have exactly:

// ```
// Edges = n - 1
// ```

// If this condition fails, the graph cannot be a tree.

// ---

// ### Step 2: Build the Adjacency List

// For every edge `(u, v)`:

// ```cpp
// adj[u].push_back(v);
// adj[v].push_back(u);
// ```

// This stores all neighbors of each node.

// ---

// ### Step 3: Perform DFS

// Start DFS from node `0`.

// ```cpp
// dfs(0, adj, visited);
// ```

// DFS marks every reachable node as visited.

// ---

// ### Step 4: Check Connectivity

// If any node is still unvisited after DFS:

// ```cpp
// for(bool x : visited)
//     if(!x)
//         return false;
// ```

// the graph is disconnected, so it is **not** a tree.

// If:

// * `m == n - 1`, and
// * all nodes are visited,

// then the graph is connected and acyclic, so it is a tree.

// ---

// ## Time Complexity

// | Operation            | Complexity   |
// | -------------------- | ------------ |
// | Build adjacency list | **O(E)**     |
// | DFS traversal        | **O(V + E)** |
// | Check visited array  | **O(V)**     |

// Overall:

// [{O(V + E)}]

// Since a tree has `E = V - 1`, this simplifies to:

// [{O(V)}]

// ---

// ## Space Complexity

// | Data Structure      | Space                 |
// | ------------------- | --------------------- |
// | Adjacency list      | **O(V + E)**          |
// | Visited array       | **O(V)**              |
// | DFS recursion stack | **O(V)** (worst case) |

// Overall:

// [{O(V + E)}]

// For a tree (`E = V - 1`), this simplifies to:

// [{O(V)}]

// -------------------------------------------------------------------------------------------------------------------

// ### Interview Tip

// For an **undirected graph**, you can conclude it is a tree if and only if:

// * Number of edges = `n - 1`
// * The graph is connected

// Checking these two conditions is sufficient; 
// a separate cycle detection step is unnecessary because any connected graph with exactly `n - 1` edges is guaranteed to be acyclic.
