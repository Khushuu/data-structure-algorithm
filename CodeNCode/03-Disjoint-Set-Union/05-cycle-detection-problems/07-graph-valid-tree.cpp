// # Graph Valid Tree

// This is one of the most common **Disjoint Set Union (DSU)** interview questions.

// ## Problem Statement

// Given:

// * `n` nodes labeled from `0` to `n-1`
// * A list of undirected edges

// Determine whether these edges form a **valid tree**.

// Example:

// ```text
// n = 5

// edges = {
// (0,1),
// (0,2),
// (0,3),
// (1,4)
// }
// ```

// Output:

// ```text
// true
// ```

// because the graph is

// ```text
//       0
//     / | \
//    1  2  3
//    |
//    4
// ```

// Every node is connected and there is no cycle.

// -------------------------------------------------------------------------------------------------------------

// # What is a Tree?

// A graph is a tree **if and only if**:

// 1. It is **connected**
// 2. It has **no cycles**

// Both conditions are required.

// -------------------------------------------------------------------------------------------------------------

// ## Example 1 (Valid)

// ```text
// 0
// |
// 1
// |
// 2
// |
// 3
// ```

// Properties

// * Connected ✔
// * No cycle ✔

// Answer = **True**

// -------------------------------------------------------------------------------------------------------------

// ## Example 2 (Cycle exists)

// ```text
// 0
// |\
// | \
// 1--2
// ```

// Properties

// * Connected ✔
// * Cycle ❌

// Answer = **False**

// -------------------------------------------------------------------------------------------------------------

// ## Example 3 (Disconnected)

// ```text
// 0--1

// 2--3
// ```

// Properties

// * Connected ❌
// * No cycle ✔

// Answer = **False**

// -------------------------------------------------------------------------------------------------------------

// # Important Observation

// A tree with `n` vertices always has exactly

// ```text
// n - 1 edges
// ```

// For example

// | Vertices | Edges |
// | -------- | ----- |
// | 2        | 1     |
// | 3        | 2     |
// | 5        | 4     |
// | 10       | 9     |

// So the first check is

// ```cpp
// if (edges.size() != n - 1)
//     return false;
// ```

// This immediately eliminates many cases.

// -------------------------------------------------------------------------------------------------------------

// # DSU Solution

// Initially every node is its own component.

// ```text
// 0

// 1

// 2

// 3

// 4
// ```

// -------------------------------------------------------------------------------------------------------------

// Process every edge.

// Suppose edge

// ```text
// 0 - 1
// ```

// Different components?

// Yes

// Union them.

// ```text
// 0
// |
// 1

// 2

// 3

// 4
// ```

// -------------------------------------------------------------------------------------------------------------

// Next edge

// ```text
// 1 - 2
// ```

// Different?

// Yes

// Union

// ```text
// 0
// |\
// 1 2

// 3

// 4
// ```

// -------------------------------------------------------------------------------------------------------------

// Suppose next edge

// ```text
// 2 - 0
// ```

// Now

// ```cpp
// find(2) == find(0)
// ```

// Same component.

// Adding this edge creates

// ```text
// 0
// |\
// | \
// 1--2
// ```

// Cycle detected.

// Return **false**.

// -------------------------------------------------------------------------------------------------------------

// If all edges are processed without finding a cycle, and we already know the graph has exactly `n - 1` edges, then the graph must be connected, so it is a valid tree.

// -------------------------------------------------------------------------------------------------------------


// # Why don't we need a separate connectivity check?

// Suppose

// ```text
// Vertices = 5
// ```

// A tree must have

// ```text
// Edges = 4
// ```

// If:

// * there is **no cycle**, and
// * there are exactly **4 edges**,

// then the graph **must** be connected.

// If it were disconnected, at least one extra edge would be needed to connect the components.

// Therefore,

// ```cpp
// edges.size() == n-1
// ```

// plus

// ```cpp
// No cycle
// ```

// is sufficient.

// -------------------------------------------------------------------------------------------------------------

// # Algorithm

// 1. If number of edges ≠ `n-1`, return false.
// 2. Initialize DSU.
// 3. For every edge:

//    * If both endpoints have the same root → cycle → return false.
//    * Otherwise union them.
// 4. If all edges are processed, return true.

// -------------------------------------------------------------------------------------------------------------

// # C++ Implementation

// ```cpp
#include <bits/stdc++.h>
using namespace std;

class DSU {
    vector<int> parent, size;

public:
    DSU(int n) {
        parent.resize(n);
        size.assign(n, 1);

        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int find(int x) {
        if (parent[x] == x)
            return x;

        return parent[x] = find(parent[x]);
    }

    bool unite(int a, int b) {
        int rootA = find(a);
        int rootB = find(b);

        if (rootA == rootB)
            return false;

        if (size[rootA] < size[rootB])
            swap(rootA, rootB);

        parent[rootB] = rootA;
        size[rootA] += size[rootB];

        return true;
    }
};

bool validTree(int n, vector<vector<int>>& edges) {

    // A tree must have exactly n-1 edges
    if (edges.size() != n - 1)
        return false;

    DSU dsu(n);

    for (auto &edge : edges) {

        int u = edge[0];
        int v = edge[1];

        // Cycle detected
        if (!dsu.unite(u, v))
            return false;
    }

    return true;
}
// ```

// -------------------------------------------------------------------------------------------------------------


// # Dry Run

// Input

// ```text
// n = 5

// edges

// 0-1
// 0-2
// 0-3
// 1-4
// ```

// Initially

// ```text
// 0

// 1

// 2

// 3

// 4
// ```

// After

// ```text
// 0-1
// ```

// ```text
// 0
// |
// 1

// 2

// 3

// 4
// ```

// After

// ```text
// 0-2
// ```

// ```text
//   0
//  / \
// 1   2

// 3

// 4
// ```

// After

// ```text
// 0-3
// ```

// ```text
//     0
//  /  |  \
// 1   2   3

// 4
// ```

// After

// ```text
// 1-4
// ```

// ```text
//     0
//  /  |  \
// 1   2   3
// |
// 4
// ```

// No cycle.

// Edges = 4 = n−1.

// Answer = **True**.

// ---

// # Example with a Cycle

// ```text
// n = 5

// 0-1
// 1-2
// 2-3
// 3-0
// ```

// When processing

// ```text
// 3-0
// ```

// we find:

// ```cpp
// find(3) == find(0)
// ```

// Both vertices are already in the same connected component, so adding this edge would create a cycle.

// Return **false**.

// ---

// # Time Complexity

// Let:

// * `V` = number of vertices

// * `E` = number of edges

// * Edge count check: **O(1)**

// * Process each edge once: **O(E)**

// * Each `find()`/`union()` operation: **O(α(V))** amortized with path compression and union by size/rank

// Overall:

// **O(E · α(V))**, which is effectively **O(E)** in practice. 
// The inverse Ackermann function, α(n), grows extremely slowly, so for all practical purposes, it can be considered constant time.

// Since a valid tree has `E = V - 1`, this is often written as **O(V)**.

// ---

// # Space Complexity

// * `parent` array: **O(V)**
// * `size` array: **O(V)**

// Total auxiliary space: **O(V)**.

// ---

// # Interview Tip

// A common interview optimization is to recognize the `n - 1` edge property immediately. If `edges.size() != n - 1`, you can return `false` without constructing the DSU or traversing the edges. This both simplifies the solution and avoids unnecessary work.
