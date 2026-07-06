// Here's a standard implementation of **Depth First Search (DFS)** for a graph using an **adjacency list** in C++.

// ### Recursive DFS (Most Common)


#include <iostream>
#include <vector>
using namespace std;

class Graph {
    int V;
    vector<vector<int>> adj;

public:
    Graph(int vertices) {
        V = vertices;
        adj.resize(V);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u); // Remove this line for directed graph
    }

    void dfs(int node, vector<bool> &visited) {
        
        visited[node] = true;
        cout << node << " ";

        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                dfs(neighbor, visited);
            }
        }
    }
};

int main() {
    int V = 5;
    Graph g(V);

    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);

    vector<bool> visited(V, false);

    cout << "DFS Traversal: ";
    g.dfs(0, visited);

    return 0;
}


// ### Output

// DFS Traversal: 0 1 3 4 2



// ## Iterative DFS (Using Stack)


#include <iostream>
#include <vector>
#include <stack>
using namespace std;

void dfs(int start, vector<vector<int>> &adj) {
    int V = adj.size();
    vector<bool> visited(V, false);
    stack<int> st;

    st.push(start);

    while (!st.empty()) {
        int node = st.top();
        st.pop();

        if (visited[node])
            continue;

        visited[node] = true;
        cout << node << " ";

        // Push neighbors in reverse order for traversal similar to recursive DFS
        for (int i = adj[node].size() - 1; i >= 0; i--) {
            if (!visited[adj[node][i]]) {
                st.push(adj[node][i]);
            }
        }
    }
}


// # Time Complexity

// Let:

// * **V** = Number of vertices
// * **E** = Number of edges

// * **DFS Traversal:** **O(V + E)**

// **Reason:** Every vertex is visited exactly once, and every edge is explored once (twice in an undirected graph, which is still linear).

// ---

// # Space Complexity

// ### Recursive DFS

// * **Visited array:** `O(V)`
// * **Recursion stack:** `O(V)` (worst case for a skewed graph)

// **Total:** **O(V)**

// ### Iterative DFS

// * **Visited array:** `O(V)`
// * **Explicit stack:** `O(V)`

// **Total:** **O(V)**

// ---

// ## Complexity Summary

// | Implementation | Time Complexity | Space Complexity |
// | -------------- | --------------- | ---------------- |
// | Recursive DFS  | **O(V + E)**    | **O(V)**         |
// | Iterative DFS  | **O(V + E)**    | **O(V)**         |
