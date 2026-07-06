// INTRO

// Shortest path on GRAPH

// Single source shortest path  
// All source shortest path


// 1. Single source shortest path on graph

// 	 unweighted > bfs  T.C = O(v + e)
// 	 weighted > +ve weights ==> dijkstra's algorithm  T.C = O(e * log v) - greedy algorithm
// 	 weighted > -ve weights ==> bellman ford algorithm  T.C = O(v * e)

// 2. All source shortest path
// 	 weighted > -ve weights ==> floyd warshall algorithm  T.C = O(v^3)

// NOTE:
//  BFS doesn't work for weighted graph as it considers all edges as same
//  without any consideration to the weight attached to the edge 

//  undirected + weighted graph (-ve weights) ==> use Bellman-Ford algorithm ==> create direct edge for both vertices

//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------

// ## Single Source Shortest Path (SSSP) on an Unweighted Tree using DFS

// In an **unweighted tree**, there is **exactly one simple path** between any two vertices.
// This unique path property is why **DFS works** for finding shortest distances in a tree.

//-------------------------------------------------------------------------------------------------------------

// ### Why does DFS work on a tree?

// Suppose the source is `1`.
// When DFS reaches a node `v` from its parent `u`, the distance is simply:

// dist[v] = dist[u] + 1

// Since there is **only one path** from the source to `v`, this is automatically the shortest path.
// No other path exists to compare with.

//-------------------------------------------------------------------------------------------------------------

// ### Example Tree

// ```
//         1
//       / | \
//      2  3  4
//        / \
//       5   6
// ```

// Source = 1

// DFS traversal:

// ```
// 1
// ├──2  dist = 1
// ├──3  dist = 1
// │   ├──5 dist = 2
// │   └──6 dist = 2
// └──4 dist = 1
// ```

// Final distances

// | Node | Distance |
// |      |          |
// | 1    | 0        |
// | 2    | 1        |
// | 3    | 1        |
// | 4    | 1        |
// | 5    | 2        |
// | 6    | 2        |

//-------------------------------------------------------------------------------------------------------------

// ## C++ Code


#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> adj;
vector<int> dist;

void dfs(int node, int parent) {

    for (int child : adj[node]) {

        if (child == parent) continue;

        dist[child] = dist[node] + 1;
        dfs(child, node);
    }
}

int main() {

    int n = 6;

    adj.resize(n + 1);
    dist.resize(n + 1);

    adj[1] = {2,3,4};
    adj[2] = {1};
    adj[3] = {1,5,6};
    adj[4] = {1};
    adj[5] = {3};
    adj[6] = {3};

    dist[1] = 0;

    dfs(1, -1);

    for (int i = 1; i <= n; i++)
        cout << "Distance to " << i << " = " << dist[i] << endl;
}


//-------------------------------------------------------------------------------------------------------------

// ## Complexity

// ### Time

// Every edge is visited exactly twice.

// For a tree,

// * Vertices = `V`
// * Edges = `V - 1`

// So,

// [O(V)]

//-------------------------------------------------------------------------------------------------------------

// ### Space

// * Distance array → `O(V)`
// * Recursion stack → `O(V)` (worst case for a skewed tree)

// Overall:

// [O(V)]

//-------------------------------------------------------------------------------------------------------------

// # Why does this NOT work on a general graph?

// A graph can have **multiple paths** between two vertices.
// DFS explores **one path first**, which may not be the shortest.
// Once a node is marked visited, DFS usually doesn't revisit it even if a shorter path is discovered later.

//-------------------------------------------------------------------------------------------------------------

// # NOTE: IMPORTANT

// # Why does BFS work on an unweighted graph?

// BFS explores nodes **level by level**.

// Level 0 : 1
// Level 1 : 2,4
// Level 2 : 3

// The first time BFS reaches a node is guaranteed to be through the shortest path (in terms of number of edges)
// because all nodes at distance `d` are processed before any node at distance `d + 1`.

// For the graph above:

// dist[1] = 0
// dist[2] = 1
// dist[4] = 1
// dist[3] = 2


// These are the correct shortest distances.

// -

// ## Summary

// | Structure              | DFS for SSSP | Reason  
// |------------------------|--------------|                                                                                                                                  |
// | Tree                   | ✅ Works      | Only one path exists between any two nodes.                                                                                               |
// | Unweighted Graph       | ❌ Fails      | Multiple paths may exist; DFS can discover a longer path before a shorter one.                                                            |
// | Unweighted Graph (BFS) | ✅ Works      | Explores vertices in increasing order of distance.                                                                                        |
// | Weighted Graph         | ❌ DFS/BFS    | Edge weights matter; use algorithms like Dijkstra's algorithm (non-negative weights) or Bellman–Ford algorithm (allows negative weights). |
