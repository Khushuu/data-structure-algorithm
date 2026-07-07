// To calculate the subtree size of every node in a tree, perform a single Depth First Search (DFS) starting from the root.

// ### Idea

// * Initialize `subtreeSize[node] = 1` (count the node itself).
// * Visit each child.
// * After returning from the child, add its subtree size to the current node.

// ### C++ Code


#include <iostream>
#include <vector>
using namespace std;

const int N = 100005;

vector<int> adj[N];
int subtreeSize[N];

void dfs(int node, int parent) {
    subtreeSize[node] = 1; // Count itself

    for (int child : adj[node]) {
        if (child == parent) continue;

        dfs(child, node);
        subtreeSize[node] += subtreeSize[child];
    }
}

int main() {
    int n;
    cin >> n;

    // Input edges
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Assuming node 1 is the root
    dfs(1, 0);

    cout << "Subtree sizes:\n";
    for (int i = 1; i <= n; i++) {
        cout << "Node " << i << ": " << subtreeSize[i] << "\n";
    }

    return 0;
}


// ### Example

// Input

// ```
// 5
// 1 2
// 1 3
// 2 4
// 2 5
// ```

// Tree:

// ```
//       1
//      / \
//     2   3
//    / \
//   4   5
// ```

// Output

// ```
// Node 1: 5
// Node 2: 3
// Node 3: 1
// Node 4: 1
// Node 5: 1
// ```

// ### Time Complexity

// * DFS visits each node exactly once and each edge exactly twice (once from each endpoint).
// * Time Complexity: O(N)

// ### Space Complexity

// * Adjacency list: O(N) (more precisely O(N + E), and for a tree (E = N - 1))
// * `subtreeSize` array: O(N)
// * DFS recursion stack: O(H), where `H` is the tree height.

//   * Worst case (skewed tree): O(N)
//   * Balanced tree: O(log N)

// Overall Space Complexity: O(N).

// ----------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------

// # Subtree Size in a Graph?

// In general, **no**. The concept of a **subtree** is defined only for a **tree**, not for an arbitrary graph.

// Here's why:

// ### In a Tree

// A tree has:

// * No cycles.
// * Exactly one path between any two nodes.
// * A unique parent for every node (except the root).

// So, if node `u` is the root of some branch, its **subtree** is:

// > `u` and all of its descendants.

// Example:

// ```
//       1
//      / \
//     2   3
//    / \
//   4   5
// ```

// * Subtree of 2 = {2, 4, 5}
// * Size = 3

// ---

// ### In a General Graph

// A graph can have:

// * Cycles
// * Multiple paths
// * No designated root
// * A node may be reachable from multiple directions

// Example:

// ```
// 1 -- 2
// |  / |
// 3 -- 4
// ```

// What is the subtree of node `2`?

// There is no unique answer because:

// * Which node is its parent?
// * Which nodes are its descendants?
// * Cycles make "descendant" ambiguous.

// Hence, **subtree is not defined for general graphs**.

// ---

// ## Exception: DFS Tree / BFS Tree

// When you run DFS or BFS on a graph, you create a **spanning tree** (or DFS tree/BFS tree).

// Example graph:

// ```
// 1 -- 2
// |    |
// 3 -- 4
// ```

// A DFS from `1` may produce:

// ```
// 1
// |
// 2
// |
// 4
// |
// 3
// ```

// Now this **DFS tree** has subtrees.

// For example:

// * Subtree of `2` = {2, 4, 3}
// * Size = 3

// Notice this is the subtree **in the DFS tree**, **not** in the original graph.

// ---

// ## Summary

// | Structure                | Subtree Exists? |
// | ------------------------ | --------------- |
// | Tree                     | ✅ Yes           |
// | Rooted Tree              | ✅ Yes           |
// | Directed Tree            | ✅ Yes           |
// | General Undirected Graph | ❌ No            |
// | General Directed Graph   | ❌ No            |
// | DFS Tree of a Graph      | ✅ Yes           |
// | BFS Tree of a Graph      | ✅ Yes           |

// So, when algorithms talk about "subtree sizes" on a graph (such as in bridge-finding, Euler tours, or Lowest Common Ancestor), 
// they almost always mean the subtree in the **DFS tree** or another rooted spanning tree constructed from the graph.
