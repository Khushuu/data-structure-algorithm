// Here is how we use **In-Time** and **Out-Time** in a **Directed Graph**.

// In a directed graph, tracking these times allows us to classify every single edge into one of four categories: 
// **Tree Edges**, 
// **Back Edges**,
// **Forward Edges**, or 
// **Cross Edges**. 

// This classification is the foundation for detecting cycles and finding topological sorts.

// ----------------------------------------------------------------------------------------------------------------

// ## 1. C++ Implementation for a Directed Graph

// We will use an additional `visited` state array (or a recursion stack array) to track whether a node is currently being explored.

// * `0`: Unvisited
// * `1`: Visiting (In-time has been recorded, but not Out-time)
// * `2`: Fully Processed (Out-time has been recorded)

#include <iostream>
#include <vector>

using namespace std;

int timer = 1;
vector<int> in_time;
vector<int> out_time;
vector<int> visited; // 0 = unvisited, 1 = visiting, 2 = fully processed
vector<vector<int>> adj;

void dfs_directed(int u) {
    visited[u] = 1;             // Mark as current visiting
    in_time[u] = timer++;       // Record entry time

    for (int v : adj[u]) {
        if (visited[v] == 0) {
            cout << "Edge " << u << " -> " << v << " is a Tree Edge\n";
            dfs_directed(v);
        } 
        else if (visited[v] == 1) {
            // v is an ancestor still on the DFS stack
            cout << "Edge " << u << " -> " << v << " is a Back Edge (CYCLE DETECTED)\n";
        } 
        else if (visited[v] == 2) {
            // v is already fully processed
            if (in_time[u] < in_time[v]) {
                cout << "Edge " << u << " -> " << v << " is a Forward Edge\n";
            } else {
                cout << "Edge " << u << " -> " << v << " is a Cross Edge\n";
            }
        }
    }

    visited[u] = 2;             // Mark as fully processed
    out_time[u] = timer++;      // Record exit time
}

int main() {
    int n = 4; // Number of nodes
    adj.resize(n + 1);
    in_time.resize(n + 1);
    out_time.resize(n + 1);
    visited.resize(n + 1, 0);

    // Defining directed edges
    adj[1] = {2, 3};
    adj[2] = {4};
    adj[3] = {4};
    adj[4] = {2}; // This creates a cycle: 2 -> 4 -> 2

    cout << "--- DFS Traversal & Edge Classification ---\n";
    for (int i = 1; i <= n; i++) {
        if (visited[i] == 0) {
            dfs_directed(i);
        }
    }

    cout << "\n--- Node Timestamps ---\n";
    for (int i = 1; i <= n; i++) {
        cout << "Node " << i << " -> In: " << in_time[i] << ", Out: " << out_time[i] << "\n";
    }

    return 0;
}

// ----------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------


// ## 2. Explanation of Edge Classifications

// When moving along a directed edge from node `u` to node `v` ($u \rightarrow v$), comparing their timestamps tells us exactly how they relate structurally:

// ----------------------------------------------------------------------------------------------------------------

// ### 1. Tree Edge

// * **What it is:** The edge leading to an unvisited node (`visited[v] == 0`). This edge becomes part of our DFS tree.
// * **Timing:** $v$ is discovered after $u$, so `in[u] < in[v]`.

// ----------------------------------------------------------------------------------------------------------------

// ### 2. Back Edge 🚨

// * **What it is:** An edge pointing from a node to one of its ancestors still residing in the active recursion stack (`visited[v] == 1`).
// * **Significance:** **The presence of even a single back edge means the graph contains a cycle.**
// * **Timing:** Since $v$ is an ancestor, it was discovered before $u$, but hasn't finished yet: `in[v] < in[u]` and `out[v]` hasn't been set.

// ----------------------------------------------------------------------------------------------------------------

// ### 3. Forward Edge

// a back edge points from a descendant to an ancestor 
// a forward edge points from an ancestor to a descendant

// * **What it is:** An edge pointing from an ancestor to a deeply nested descendant that has already been completely evaluated (`visited[v] == 2`).
// * **Timing:** Because $v$ is a descendant, it was discovered after $u$. Therefore: `in[u] < in[v]`.

// ----------------------------------------------------------------------------------------------------------------

// ### 4. Cross Edge

// a cross edge connects two connected components
// where one of the connected components is completly discovered before the other

// * **What it is:** An edge pointing between two branches of the DFS tree where neither node is an ancestor of the other (`visited[v] == 2`).
// * **Timing:** Because $v$ was in an entirely different, previously explored branch, it was discovered and completed before $u$ was ever reached. Therefore: `in[v] < in[u]`.

// ----------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------

// ## 3. Complexity Analysis

// * **Time Complexity:** {O}(V + E)$ where $V$ is vertices and $E$ is edges. Every node and edge is processed a constant number of times.
// * **Space Complexity:** {O}(V)$ due to the size of the mapping arrays (`in_time`, `out_time`, `visited`) and the maximum possible depth of the recursive call stack.