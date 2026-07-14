// The concepts of 
//**In-Time (Entry Time)** and **Out-Time (Exit Time)** 
// are among the most powerful DFS techniques used in trees and graphs. 

// They are used in many advanced algorithms like 
// **Euler Tour**, 
// **Binary Lifting**, 
// **LCA**, 
// **Subtree Queries**, 
// **Bridges & Articulation Points**,
// **Strongly Connected Components**, etc.

// --------------------------------------------------------------------------------------------------------------

// # What are In-Time and Out-Time?

// During DFS:

// * **In-Time** = The moment you first enter (visit) a node.
// * **Out-Time** = The moment you finish processing all its children and leave the node.

// We maintain a global timer.

// ```
// timer = 1
// ```

// Every time we enter or leave a node, we increment it.

// --------------------------------------------------------------------------------------------------------------

// # Example

// Consider this tree

// ```
//         1
//       / | \
//      2  3  4
//        / \
//       5   6
// ```

// DFS Order

// ```
// dfs(1)

//     dfs(2)

//     dfs(3)
//         dfs(5)
//         dfs(6)

//     dfs(4)
// ```

// Final Table

// | Node | In | Out |
// | ---- | -- | --- |
// | 1    | 1  | 12  |
// | 2    | 2  | 3   |
// | 3    | 4  | 9   |
// | 4    | 10 | 11  |
// | 5    | 5  | 6   |
// | 6    | 7  | 8   |

// --------------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------------

// # C++ Code


#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> adj;
vector<int> inTime, outTime;
int timer = 1;

void dfs(int node, int parent)
{
    inTime[node] = timer++;

    for (int child : adj[node])
    {
        if (child != parent)
            dfs(child, node);
    }

    outTime[node] = timer++;
}

int main()
{
    int n = 6;

    adj.resize(n + 1);
    inTime.resize(n + 1);
    outTime.resize(n + 1);

    adj[1] = {2,3,4};
    adj[2] = {1};
    adj[3] = {1,5,6};
    adj[4] = {1};
    adj[5] = {3};
    adj[6] = {3};

    dfs(1,-1);

    for(int i=1;i<=n;i++)
        cout<<i<<" : "<<inTime[i]<<" "<<outTime[i]<<endl;
}

// ### Time Complexity: O(V+E)
// ### Space Complexity: O(V)

// --------------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------------

// # Why is it useful?

// The biggest property is:

// > A node's entire subtree is visited before DFS exits that node.

// Therefore,

// in[parent] < in[child]
// and
// out[parent] > out[child]

// ------------------------------------------------------------------------------------------------------------

// # Problem 1: Check if one node is ancestor of another

// Suppose someone asks

// Is node u an ancestor of node v ?

// Instead of traversing the tree,
// just check

// if(in[u] <= in[v] && out[u] >= out[v])

// Example

// ```
//         1
//       /   \
//      2     3
//           / \
//          5   6
// ```

// ```
// Node 3

// in = 4
// out = 9

// Node 5

// in = 5
// out = 6
// ```

// Check

// ```
// 4 <= 5

// 9 >= 6
// ```

// True

// Therefore

// ```
// 3 is ancestor of 5
// ```

// This is

// ```
// O(1)
// ```

// instead of

// ```
// O(N)
// ```

// -----------------------------------------------------------------------------------------------------------

// # Problem 2: Euler Tour

// Suppose subtree

// ```
//         1
//       /   \
//      2     3
//           / \
//          5   6
// ```

// DFS order

// ```
// 1 2 3 5 6
// ```

// Every subtree becomes a continuous segment.

// Example
// Subtree of 3

// 3 5 6

// continuous.
// This allows

// * Segment Tree
// * Fenwick Tree

// to answer subtree queries efficiently.

// -----------------------------------------------------------------------------------------------------------

// Example problem

// Add +10 to every node in subtree of x.

// Instead of visiting every node,
// convert tree into array using Euler Tour.
// Then update one range.

// -----------------------------------------------------------------------------------------------------------

// # Problem 3: Lowest Common Ancestor (LCA)

// Most Binary Lifting implementations first compute

// in[]
// out[]

// Then
// isAncestor(u,v)
// becomes

// return in[u]<=in[v] && out[u]>=out[v];

// This check is repeatedly used while climbing ancestors.

// -----------------------------------------------------------------------------------------------------------

// # Problem 4: Bridge and Articulation Point

// Tarjan's Algorithm stores

// tin[]: (Time of Entry)
// and
// low[]

// Although it doesn't use out-time, the idea of recording DFS timestamps starts here.
// Used in

// * Bridges
// * Cut Vertices

// -----------------------------------------------------------------------------------------------------------

// # Problem 5: Strongly Connected Components

// Kosaraju's Algorithm performs DFS and pushes nodes **after finishing them**.
// That finishing order corresponds to decreasing **out-time**.
// The node with the largest out-time is processed first in the second DFS.

// -----------------------------------------------------------------------------------------------------------

// # Problem 6: Topological Sort

// DFS Topological Sort also works because
// A node is added to the stack **after all its descendants are processed**, which is effectively based on its exit (out) time.

// -----------------------------------------------------------------------------------------------------------

// # Problem 7: Subtree Sum Queries

// Suppose

// ```
//         1
//       / | \
//      2  3  4
//        / \
//       5   6
// ```

// Values

// ```
// 1 5
// 2 3
// 3 2
// 4 7
// 5 8
// 6 1
// ```

// Euler Tour
// 1 2 3 5 6 4

// Subtree of node 3 becomes
// 3 5 6

// Now
// Subtree Sum = Range Sum
// using Segment Tree.

// -----------------------------------------------------------------------------------------------------------

// # Problem 8: Flatten Tree

// Competitive programming often says
// Flatten the tree.

// Meaning Convert Tree into Array using inTime
// Now every subtree occupies one continuous interval.

// --------------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------------

// # Most Common Interview Uses

// | Problem               | Uses In-Time | Uses Out-Time         |
// | --------------------- | ------------ | --------------------- |
// | Ancestor Query        | ✅            | ✅                     |
// | Binary Lifting (LCA)  | ✅            | ✅                     |
// | Euler Tour            | ✅            | Sometimes             |
// | Flatten Tree          | ✅            | Sometimes             |
// | Subtree Queries       | ✅            | ✅                     |
// | Segment Tree on Trees | ✅            | ✅                     |
// | Fenwick Tree on Trees | ✅            | ✅                     |
// | Kosaraju SCC          | ❌            | ✅ (finish time order) |
// | DFS Topological Sort  | ❌            | ✅ (exit order)        |
// | Bridges (Tarjan)      | ✅ (`tin`)    | ❌                     |
// | Articulation Points   | ✅ (`tin`)    | ❌                     |

// --------------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------------

//NOTE:

// ### Key intuition

// Think of DFS as placing **parentheses** around each node's subtree:

// ```
// 1(
//     2()
//     3(
//         5()
//         6()
//     )
//     4()
// )
// ```

// * **In-time** is when you write the opening parenthesis `(`.
// * **Out-time** is when you write the closing parenthesis `)`.

// This nesting property guarantees that for any ancestor `u` and descendant `v`:

// ```
// in[u] < in[v] < out[v] < out[u]
// ```

// This single property is the foundation for many advanced tree algorithms, because every subtree becomes a well-defined interval that can be queried or updated efficiently.
