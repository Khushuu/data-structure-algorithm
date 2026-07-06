// # Check if a Graph is Bipartite (C++)

// ## Theory

// A **Bipartite Graph** is a graph whose vertices can be divided into **two disjoint sets** such that **no two adjacent vertices belong to the same set**.

// Instead of explicitly creating two sets, we assign one of **two colors** to each vertex:

// * Color 0
// * Color 1

// If every edge connects vertices of **different colors**, then the graph is bipartite.

// -------------------------------------------------------------------------------------------------------------

// ## Key Property

// A graph is **Bipartite if and only if it does not contain an odd-length cycle.**

// * Even cycle → Bipartite ✅
// * Odd cycle → Not Bipartite ❌

// Example:

// ```
// 0 ----- 1
// |       |
// |       |
// 3 ----- 2
// ```

// This is a cycle of length 4 (even), so it is bipartite.

// -------------------------------------------------------------------------------------------------------------

// ```
// 0
// |\
// | \
// 1--2
// ```

// This is a cycle of length 3 (odd), so it is **not** bipartite.

// -------------------------------------------------------------------------------------------------------------

// # Algorithm (BFS Coloring)

// 1. Initially, every node is uncolored (`-1`).
// 2. Start BFS from any uncolored node.
// 3. Assign the first node color `0`.
// 4. Every adjacent node gets the opposite color (`1 - currentColor`).
// 5. If an adjacent node already has the same color as the current node, return **Not Bipartite**.
// 6. Repeat for all disconnected components.

// -------------------------------------------------------------------------------------------------------------

// # C++ Code (BFS)


#include <iostream>
#include <vector>
#include <queue>
using namespace std;

bool bfs(int start, vector<vector<int>> &adj, vector<int> &color) {
    queue<int> q;

    q.push(start);
    color[start] = 0;

    while (!q.empty()) {

        int node = q.front();
        q.pop();

        for (int neighbor : adj[node]) {

            // If neighbor is uncolored
            if (color[neighbor] == -1) {
                color[neighbor] = !color[node];
                q.push(neighbor);
            }

            // Same color on both ends
            else if (color[neighbor] == color[node]) {
                return false;
            }
        }
    }

    return true;
}

bool isBipartite(int n, vector<vector<int>> &adj) {

    vector<int> color(n, -1);

    // check for all components of the graph
    for (int i = 0; i < n; i++) {

        if (color[i] == -1) {

            if (!bfs(i, adj, color))
                return false;
        }
    }

    return true;
}

int main() {

    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n);

    for (int i = 0; i < m; i++) {

        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    if (isBipartite(n, adj))
        cout << "Graph is Bipartite";
    else
        cout << "Graph is NOT Bipartite";

    return 0;
}

----------------------------------------------------------------------------------------------------------------

// # Input Format

// ```
// Number of Vertices Number of Edges

// u1 v1
// u2 v2
// ...
// um vm
// ```

// ---

// ## Example 1

// ### Input

// ```
// 4 4
// 0 1
// 1 2
// 2 3
// 3 0
// ```

// ### Output

// ```
// Graph is Bipartite
// ```

// ### Explanation

// Color assignment:

// ```
// 0 (Red)
// |
// 1 (Blue)
// |
// 2 (Red)
// |
// 3 (Blue)
// ```

// Every edge connects opposite colors.

// -------------------------------------------------------------------------------------------------------------

// ## Example 2

// ### Input

// ```
// 3 3
// 0 1
// 1 2
// 2 0
// ```

// ### Output

// ```
// Graph is NOT Bipartite
// ```

// ### Explanation

// ```
// 0 ---- 1
//  \    /
//   \  /
//    2
// ```

// Try coloring:

// ```
// 0 → Red
// 1 → Blue
// 2 → Red
// ```

// But edge `(2,0)` connects two Red nodes.

// Hence, the graph is not bipartite.

// -------------------------------------------------------------------------------------------------------------

// # Dry Run

// Input

// ```
// 5 4

// 0 1
// 1 2
// 2 3
// 3 4
// ```

// Initially

// ```
// Color = [-1 -1 -1 -1 -1]
// ```

// Start BFS from node `0`

// ```
// Color[0] = 0

// Queue = {0}
// ```

// Visit `0`

// ```
// Neighbor = 1

// Color[1] = 1
// ```

// Queue

// ```
// {1}
// ```

// Visit `1`

// ```
// Neighbor = 2

// Color[2] = 0
// ```

// Queue

// ```
// {2}
// ```

// Visit `2`

// ```
// Neighbor = 3

// Color[3] = 1
// ```

// Visit `3`

// ```
// Neighbor = 4

// Color[4] = 0
// ```

// Final colors

// ```
// 0 1 0 1 0
// ```

// No adjacent vertices have the same color.

// Answer: **Bipartite**

// ---

// # Time Complexity

// Let:

// * **V** = Number of vertices
// * **E** = Number of edges

// ### Building Adjacency List

// ```
// O(E)
// ```

// ### BFS Traversal

// Each vertex is visited once.

// ```
// O(V)
// ```

// Each edge is examined exactly once (or twice in an undirected graph due to the adjacency list).

// ```
// O(E)
// ```

// ### Overall Time Complexity

// [{O(V + E)}]

// ---

// # Space Complexity

// ### Adjacency List

// ```
// O(V + E)
// ```

// ### Color Array

// ```
// O(V)
// ```

// ### Queue (Worst Case)

// ```
// O(V)
// ```

// ### Overall Space Complexity

// [
// \boxed{O(V + E)}
// ]

// ---

// # Why Do We Check All Vertices?

// A graph may be **disconnected**.

// Example:

// ```
// Component 1

// 0 ---- 1


// Component 2

// 2 ---- 3
// ```

// If BFS starts only from node `0`, nodes `2` and `3` are never visited.

// Therefore, we run BFS from every uncolored vertex:

// ```cpp
// for (int i = 0; i < n; i++) {
//     if (color[i] == -1) {
//         if (!bfs(i, adj, color))
//             return false;
//     }
// }
// ```

// This ensures every connected component is checked.

// ---

// # Interview Points

// * A graph is **bipartite if it can be colored using exactly two colors**.
// * **No two adjacent vertices** should have the same color.
// * A graph is **bipartite if and only if it has no odd-length cycle**.
// * The standard solution uses **BFS or DFS with two-coloring**.
// * **Time Complexity:** `O(V + E)`
// * **Space Complexity:** `O(V + E)` (including the adjacency list), or **auxiliary space:** `O(V)` for the color array and BFS queue.

// -------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------

// // USING DFS and VISITED ARRAY

// Yes. Instead of initializing the color array with `-1`, you can use two arrays:

// * `visited[]` → checks whether a node has been visited.
// * `color[]` → stores `0` or `1` (false or true).

// This avoids using `-1` completely.

---

# C++ Code (DFS)

#include <iostream>
#include <vector>
using namespace std;

bool dfs(int node, bool currColor,
         vector<vector<int>> &adj,
         vector<bool> &visited,
         vector<bool> &color)
{
    visited[node] = true;
    color[node] = currColor;

    for (int neighbor : adj[node])
    {
        // If neighbor is not visited
        if (!visited[neighbor])
        {
            if (!dfs(neighbor, !currColor, adj, visited, color))
                return false;
        }
        // Neighbor already visited
        else
        {
            if (color[neighbor] == color[node])
                return false;
        }
    }

    return true;
}

bool isBipartite(int n, vector<vector<int>> &adj)
{
    vector<bool> visited(n, false);
    vector<bool> color(n);

    // Handle disconnected graph
    for (int i = 0; i < n; i++)
    {
        if (!visited[i])
        {
            if (!dfs(i, 0, adj, visited, color))
                return false;
        }
    }

    return true;
}

int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n);

    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    if (isBipartite(n, adj))
        cout << "Graph is Bipartite";
    else
        cout << "Graph is NOT Bipartite";

    return 0;
}


---

// ## How `!` Works

// Suppose the current node has color:

// ```cpp
// currColor = 0;
// ```

// Then

// ```cpp
// !currColor
// ```

// becomes

// ```cpp
// !0 = 1
// ```

// Similarly,

// ```cpp
// currColor = 1;
// ```

// then

// ```cpp
// !currColor
// ```

// becomes

// ```cpp
// !1 = 0
// ```

// So `!` automatically switches between the two colors:

// | Current Color | `!Current Color` |
// | ------------- | ---------------- |
// | `0`           | `1`              |
// | `1`           | `0`              |

// Instead of writing:

// ```cpp
// color[neighbor] = 1 - color[node];
// ```

// you can simply write:

// ```cpp
// dfs(neighbor, !currColor, adj, visited, color);
// ```

// ---

// ## DFS Working

// Consider the graph:

// ```
// 0 ---- 1
// |      |
// |      |
// 3 ---- 2
// ```

// Start DFS from node `0`.

// ```
// visited = [F F F F]
// ```

// Visit `0`

// ```
// visited = [T F F F]
// color   = [0 - - -]
// ```

// Go to `1`

// ```
// color[1] = !0 = 1
// ```

// ```
// visited = [T T F F]
// color   = [0 1 - -]
// ```

// Go to `2`

// ```
// color[2] = !1 = 0
// ```

// ```
// visited = [T T T F]
// color   = [0 1 0 -]
// ```

// Go to `3`

// ```
// color[3] = !0 = 1
// ```

// ```
// visited = [T T T T]
// color   = [0 1 0 1]
// ```

// Now DFS checks every already visited neighbor:

// * `0` ↔ `1` → different colors ✅
// * `1` ↔ `2` → different colors ✅
// * `2` ↔ `3` → different colors ✅
// * `3` ↔ `0` → different colors ✅

// Hence, the graph is bipartite.

// ---

// ### Complexity

// * **Time Complexity:** `O(V + E)`
// * **Space Complexity:**

//   * Adjacency list: `O(V + E)`
//   * `visited` array: `O(V)`
//   * `color` array: `O(V)`
//   * DFS recursion stack (worst case): `O(V)`

// Overall auxiliary space is `O(V)`, while the total space including the graph representation is `O(V + E)`.
