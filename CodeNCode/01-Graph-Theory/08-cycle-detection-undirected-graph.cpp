// CYCLE DETECTION IN UNDIRECTED GRAPH

// back edge
// an edge that connects a node to its ancestor that is not its direct parent

// if a back edge exists in an graph that means there is cycle in graph
// y
// 
// 0 ----- 1
// |       |
// |       |
// 3 ----- 2

// consider a tree - a tree has no cycle in it and there is only one way to reach a node from the root
// now if there is more than one way to reach a node that is only possible if there is a cycle in the graph

// e.g 
// dfs traversal for above graph
// will have 1-2 as back edge and 0-1 and 2-3 as back edge
// since you reach 3 from 2 which is its direct parent but when exploring a child of 2 i.e 1
// which is not its parent means it is an ancestor which could be reached from any other node in the graph
// that is possible only when there is cycle in the graph

// There are different algorithms depending on whether the graph is **directed** or **undirected**.

// # 1. DFS (Visited + Parent) — Undirected Graph
// # 2. BFS (Parent Tracking) — Undirected Graph

// -------------------------------------------------------------------------------------------------------------

// # 1. DFS (Visited + Parent) — Undirected Graph

// ### Idea

// * Perform DFS.
// * If a visited node is encountered that is **not the parent**, then a cycle exists.

// ### C++ Code

#include <iostream>
#include <vector>
using namespace std;

bool dfs(int node, int parent, vector<vector<int>>& adj, vector<bool>& visited) {
    visited[node] = true;

    for (int neighbor : adj[node]) {
        if (!visited[neighbor]) {
            if (dfs(neighbor, node, adj, visited))
                return true;
        }
        else if (neighbor != parent) {
            return true;
        }
    }

    return false;
}

bool hasCycle(int V, vector<vector<int>>& adj) {
    vector<bool> visited(V, false);

    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            if (dfs(i, -1, adj, visited))
                return true;
        }
    }

    return false;
}

int main() {
    int V = 5;
    vector<vector<int>> adj(V);

    adj[0] = {1};
    adj[1] = {0,2,4};
    adj[2] = {1,3};
    adj[3] = {2,4};
    adj[4] = {1,3};

    cout << (hasCycle(V, adj) ? "Cycle Found" : "No Cycle");
}

// ### Complexity

// * **Time:** `O(V + E)`
// * **Space:** `O(V)` (visited + recursion stack)

// ----------------------------------------------------------------------------------------------------------------

// # 2. BFS (Parent Tracking) — Undirected Graph

// ### Idea

// Store `(node, parent)` in a queue.

// If a visited neighbor is not the parent → cycle.

// ### C++ Code


#include <iostream>
#include <vector>
#include <queue>
using namespace std;

bool bfs(int src, vector<vector<int>>& adj, vector<bool>& visited) {
    queue<pair<int,int>> q;

    visited[src] = true;
    q.push({src,-1});

    while (!q.empty()) {
        auto [node,parent] = q.front();
        q.pop();

        for (int neighbor : adj[node]) {

            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push({neighbor,node});
            }
            else if (neighbor != parent) {
                return true;
            }
        }
    }

    return false;
}

bool hasCycle(int V, vector<vector<int>>& adj) {
    vector<bool> visited(V,false);

    for(int i=0;i<V;i++) {
        if(!visited[i]) {
            if(bfs(i,adj,visited))
                return true;
        }
    }

    return false;
}

// ### Complexity

// * **Time:** `O(V + E)`
// * **Space:** `O(V)`

//----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------


// # Summary

// | Method                              | Graph Type | Time                   | Space    |
// | ----------------------------------- | ---------- | ---------------------- | -------- |
// | DFS + Parent                        | Undirected | **O(V + E)**           | **O(V)** |
// | BFS + Parent                        | Undirected | **O(V + E)**           | **O(V)** |
// | DFS + Recursion Stack               | Directed   | **O(V + E)**           | **O(V)** |
// | Kahn's Algorithm (Topological Sort) | Directed   | **O(V + E)**           | **O(V)** |
// | Union-Find (DSU)                    | Undirected | **O(E × α(V)) ≈ O(E)** | **O(V)** |

// ### Which method is preferred in interviews?

// * **Undirected graph:** DFS with parent tracking (most common), BFS with parent tracking, or DSU (especially when edges are processed incrementally).
// * **Directed graph:** DFS with recursion stack (most common) or Kahn's algorithm (especially if topological sorting is also relevant).
