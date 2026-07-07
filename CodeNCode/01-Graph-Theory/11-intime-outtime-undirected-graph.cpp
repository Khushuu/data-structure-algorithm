// In graph algorithms, **In-Time** and **Out-Time** (also referred to as entry/exit time or discovery/finish time) 
// are timestamps recorded during a **Depth First Search (DFS)** traversal.

// When you traverse a graph or tree, a global counter increments each time you enter or leave a node.

// * `in[u]`: The time at which the DFS enters node `u` (it is discovered).
// * `out[u]`: The time at which the DFS completely finishes exploring node `u` and all its descendants (it backtracks).

// -------------------------------------------------------------------------------------------------------------

// ## 1. Core Concept and C++ Implementation

// These timestamps flatten a tree or graph structure into linear segments, allowing us to query ancestral relationships or structural properties in $O(1)$ time.

// ### C++ Code Implementation

#include <iostream>
#include <vector>

using namespace std;

// Global variables for tracking DFS times
int timer = 1;
vector<int> in_time;
vector<int> out_time;
vector<bool> visited;
vector<vector<int>> adj;

void dfs(int u) {
    visited[u] = true;
    in_time[u] = timer++; // Record entry time and increment

    for (int v : adj[u]) {
        if (!visited[v]) {
            dfs(v);
        }
    }

    out_time[u] = timer++; // Record exit time and increment
}

int main() {
    int n = 5; // Number of nodes (1-indexed)
    adj.resize(n + 1);
    in_time.resize(n + 1);
    out_time.resize(n + 1);
    visited.resize(n + 1, false);

    // Sample Tree Edges: 1-2, 1-3, 2-4, 2-5
    adj[1] = {2, 3};
    adj[2] = {1, 4, 5};
    adj[3] = {1};
    adj[4] = {2};
    adj[5] = {2};

    // Run DFS for all connected components
    for(int i = 1; i <= n; i++) {
        if(!visited[i]) {
            dfs(i);
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << "Node " << i << " -> In: " << in_time[i] << ", Out: " << out_time[i] << "\n";
    }
    return 0;
}

```

// ### Complexities

// * **Time Complexity:** {O}(V + E)$ where $V$ is vertices and $E$ is edges, since it's just a standard DFS traversal.
// * **Space Complexity:** {O}(V)$ to store the `in_time`, `out_time`, `visited` vectors, and the recursive call stack.

// -------------------------------------------------------------------------------------------------------------

// ## 2. Key Problems Solved Using In/Out Times

// ### Problem A: Checking if Node X is an Ancestor of Node Y ($O(1)$ Query)

// In a rooted tree, node $X$ is an ancestor of node $Y$ if and only if the DFS enters $X$ before $Y$, and leaves $X$ after $Y$.

// * **Condition:** `in[X] <= in[Y]` AND `out[X] >= out[Y]`
// * **Application:** Crucial for optimization algorithms like Binary Lifting for Lowest Common Ancestor (LCA).
// * **Complexity:**
// * *Preprocessing:* $\mathcal{O}(V)$
// * *Per Query:* $\mathcal{O}(1)$

// -------------------------------------------------------------------------------------------------------------

// ### Problem B: Subtree Queries (Flattening a Tree)

// Because of how DFS behaves, 
//the execution times of all nodes inside a node $X$'s subtree fall cleanly within the range `[in[X], out[X]]`.

// * **How it's used:** 
// If you need to perform range updates/queries on a node's subtree (e.g., *"add +5 to all nodes in node X's subtree"*),
// you map the tree nodes to an array based on their `in_time`. 

// The entire subtree of $X$ becomes a single contiguous block in that array. 
//You can then query or modify it using a **Fenwick Tree (BIT)** or **Segment Tree**.

// * **Complexity:** {O}(\log V)$ per update/query using a segment tree.

// -------------------------------------------------------------------------------------------------------------

// ### Problem C: Finding Bridges and Articulation Points in a Graph

// In general graphs (not just trees), `in_time` is utilized to find weak spots in connectivity. 
// We also track a `low_time` array: `low[u]` represents the lowest `in_time` reachable from $u$ using at most one back-edge.

// * **Bridge Condition:** 
//An edge $(u, v)$ is a bridge if `low[v] > in[u]`. 
// This means there is no back-edge from $v$'s subtree that can reach $u$ or its ancestors.

// * **Complexity:** {O}(V + E)$ time and $\mathcal{O}(V)$ space.

// -------------------------------------------------------------------------------------------------------------

// ### Problem D: Topological Sort / Edge Classification

// In a directed graph DFS, comparing `in_time` and `out_time` helps classify edges:

// * **Tree/Forward Edge:** Ancestor to descendant.
// * **Back Edge:** Descendant to ancestor (`in[v] < in[u]` and `out[v] > out[u]` while $v$ is active) $\rightarrow$ **Indicates a cycle**.
// * **Cross Edge:** No ancestral relationship.

// ----------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------

// ## Summary Table

// | Use Case | Core Principle / Formula | Query Time | Space Complexity |
// | --- | --- | --- | --- |
// | **Ancestor Check** | `in[X] <= in[Y] && out[X] >= out[Y]` | $\mathcal{O}(1)$ | $\mathcal{O}(V)$ |
// | **Subtree Queries** | Map nodes to array segment `[in[X], out[X]]` | $\mathcal{O}(\log V)$ | $\mathcal{O}(V)$ |
// | **Bridge Detection** | Find if `low[child] > in[parent]` | $\mathcal{O}(V+E)$ total | $\mathcal{O}(V)$ |
// | **Cycle Detection** | Track active nodes in recursion stack | $\mathcal{O}(V+E)$ total | $\mathcal{O}(V)$ |