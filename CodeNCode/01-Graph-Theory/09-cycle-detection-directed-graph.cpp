
// # 1. DFS with Recursion Stack — Directed Graph
// # 2. Kahn's Algorithm (Topological Sort) — Directed Graph
// # 3. Union-Find (Disjoint Set Union) — Undirected Graph

// # 1. DFS with Recursion Stack — Directed Graph

// When detecting a cycle in a **directed graph** using Depth-First Search (DFS), we use a stack—specifically, a **recursion stack** (or a `visitedStack` tracker)—because of how directed edges work.

// In an undirected graph, simply hitting a node you've already visited means there is a cycle. But in a directed graph, that's not true. You can visit a node twice just because two different paths point to it, without any loop existing.

// To find a true cycle, you need to know if you've hit a node that is **currently active in the current DFS path**. That's exactly what the stack tracks.

// ---

// ## The Core Concept: Ancestors vs. Cousins

// To understand why the stack is necessary, you have to understand the difference between two types of nodes you might revisit:

// 1. **An Ancestor (Cycle Present):** A node that is currently in the recursion stack. If your current DFS path circles back and hits a node that is still on the stack, you've found a **back-edge**, which means a cycle exists.
// 2. **A Cross/Forward Edge (No Cycle):** A node that was visited and completely finished in a *previous* branch of the DFS. It is no longer on the stack. Hitting this node does **not** indicate a cycle.

// ### A Quick Visual

// Imagine a graph like this: `A -> B -> C` and `A -> C`.

// ```text
//     A
//    / \
//   v   v
//   B -> C

// ```

// 1. DFS starts at `A`. Stack: `[A]`
// 2. DFS moves to `B`. Stack: `[A, B]`
// 3. DFS moves to `C`. Stack: `[A, B, C]`
// 4. `C` has no neighbors. DFS backtracks. `C` is popped. Stack: `[A, B]`
// 5. `B` has no more neighbors. DFS backtracks. `B` is popped. Stack: `[A]`
// 6. From `A`, DFS tries to visit `C` via the `A -> C` edge.
// 7. `C` is already marked as visited. **Is there a cycle? No.** Because `C` is *not* in the current stack `[A]`. It's just a node we finished exploring earlier.

// If the edge was `C -> A` instead, when we were at `C`, the stack would be `[A, B, C]`. Since `A` is already on the stack, we would immediately know a cycle exists.

// ---

// ## How it Looks in C++ Code

// In C++ DFS implementations, we typically maintain two boolean arrays (or vectors):

// * `visited[]`: Tracks if a node has ever been visited in the entire lifetime of the algorithm (so we don't repeat work).
// * `inStack[]` (or `inStack[]`): Tracks if the node is in the *current* DFS recursion path.

// Here is the standard implementation:

#include <iostream>
#include <vector>
using namespace std;

bool dfs(int node,
         vector<vector<int>>& adj,
         vector<bool>& visited,
         vector<bool>& inStack) {

    visited[node] = true;
    inStack[node] = true;

    for (int neighbor : adj[node]) {

        if (!visited[neighbor]) {
            if (dfs(neighbor, adj, visited, inStack))
                return true;
        }
        else if (inStack[neighbor]) {
            return true;
        }
    }

    inStack[node] = false;
    return false;
}

bool hasCycle(int V, vector<vector<int>>& adj) {

    vector<bool> visited(V,false);
    vector<bool> inStack(V,false);

    for(int i=0;i<V;i++) {
        if(!visited[i]) {
            if(dfs(i,adj,visited,inStack))
                return true;
        }
    }

    return false;
}

// ---

// ## Summary of the Mechanism

// | Structure | What it answers | Why it's not enough on its own |
// | --- | --- | --- |
// | `visited` array | "Have I ever looked at this node before?" | Causes false positives on diamond-shaped graphs or cross-edges where no actual cycle exists. |
// | `inStack` array | "Is this node an ancestor of my current exploration path?" | Essential for isolating directed cycles; a hit here confirms a path loops back on itself. |

// By pushing a node onto the stack when we enter it, and popping it off (setting `inStack[node] = false`) when we backtrack, the stack acts as a perfect history log of the **exact path** the DFS is currently walking down.

// // ### Complexity

// // * **Time:** `O(V + E)`
// // * **Space:** `O(V)`

// ----------------------------------------------------------------------------------------------------------------

// # 2. Kahn's Algorithm (Topological Sort) — Directed Graph

// ### Idea

// * Compute indegree of every node.
// * Push nodes with indegree 0.
// * Remove them one by one.
// * If all nodes are removed → no cycle.
// * Otherwise → cycle exists.

// ### C++ Code

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

bool hasCycle(int V, vector<vector<int>>& adj) {

    vector<int> indegree(V,0);

    for(int i=0;i<V;i++)
        for(int v:adj[i])
            indegree[v]++;

    queue<int> q;

    for(int i=0;i<V;i++)
        if(indegree[i]==0)
            q.push(i);

    int count = 0;

    while(!q.empty()) {

        int node = q.front();
        q.pop();
        count++;

        for(int neighbor:adj[node]) {
            indegree[neighbor]--;

            if(indegree[neighbor]==0)
                q.push(neighbor);
        }
    }

    return count != V;
}

// ### Complexity

// * **Time:** `O(V + E)`
// * **Space:** `O(V)`

// ----------------------------------------------------------------------------------------------------------------

// # 3. Union-Find (Disjoint Set Union) — Undirected Graph

// ### Idea

// Process each edge:

// * If both vertices already belong to the same set → cycle.
// * Otherwise, union the sets.

// ### C++ Code

#include <iostream>
#include <vector>
using namespace std;

class DSU {
public:
    vector<int> parent, rank;

    DSU(int n) {
        parent.resize(n);
        rank.resize(n,0);

        for(int i=0;i<n;i++)
            parent[i]=i;
    }

    int find(int x) {
        if(parent[x]==x)
            return x;
        return parent[x]=find(parent[x]);
    }

    bool unite(int x,int y) {

        int px=find(x);
        int py=find(y);

        if(px==py)
            return false;

        if(rank[px]<rank[py])
            swap(px,py);

        parent[py]=px;

        if(rank[px]==rank[py])
            rank[px]++;

        return true;
    }
};

bool hasCycle(int V, vector<pair<int,int>>& edges) {

    DSU dsu(V);

    for(auto edge:edges) {

        int u=edge.first;
        int v=edge.second;

        if(!dsu.unite(u,v))
            return true;
    }

    return false;
}


// ### Complexity

// * **Time:** `O(E × α(V))` (almost linear, where α is the inverse Ackermann function)
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
