// DFS (Depth-First Search) is a graph traversal algorithm 
// that explores as far as possible along each branch before backtracking.

// It works using recursion (stack) and is mainly used for:

// Detecting cycles in graphs
// Finding connected components
// Topological sorting
// Solving maze and puzzle problems
// Pathfinding algorithms

// Adjacency List	

// T.C = O(N + E)	
// N = Number of nodes (vertices)
// E = Number of edges
// Each node (vertex) is visited once → O(N)
// Each edge is processed once (in an adjacency list) → O(E)
// Total operations = O(N) + O(E) = O(N + E)

// S.C = O(N) 
// DFS Traversal (Iterative): 0 3 2 1
// ------------------------------------------------------------------------------------------------------------
void dfs(int node, vector<vector<int>> &graph, vector<bool> &visited) {

    visited[node] = true; // Mark as visited

    cout << node << " ";  // Process the node (print or store)

    for (int neighbor : graph[node]) {

        if (!visited[neighbor]) 
            dfs(neighbor, graph, visited);
    }
}

int main() {

    int n = 4; // Number of nodes
    vector<vector<int>> graph(n);
    vector<bool> visited(n, false);
    
    // Creating an undirected graph
    graph[0] = {1, 3};
    graph[1] = {0, 2};
    graph[2] = {1, 3};
    graph[3] = {0, 2};
	
    cout << "DFS Traversal: ";
    dfs(0, graph, visited);
}

// ------------------------------------------------------------------------------------------------------------
