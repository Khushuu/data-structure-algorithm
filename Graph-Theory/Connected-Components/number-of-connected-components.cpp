// Finding Number of Connected Components (Undirected Graph)
// We can use DFS or BFS to count the number of connected components.

// DFS-Based Approach
// Use a visited array to track visited nodes.
// Perform DFS from each unvisited node, marking all reachable nodes.
// Each DFS call represents a new connected component.

// Leetcode problems
// 323: Number of Connected Components in an Undirected Graph
// 547. Number of Provinces (Graph connected components)
// 200. Number of Islands (Grid-based connected components)
// 924. Minimize Malware Spread (Graph traversal & components)

// T.C = O(N + E)	
// S.C = O(N + E) (Adjacency List)
// ---------------------------------------------------------------------------------------------------

void dfs(int node, vector<vector<int>>& graph, vector<bool>& visited) {

    visited[node] = true;

    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            dfs(neighbor, graph, visited);
        }
    }
}

int countConnectedComponents(int n, vector<vector<int>>& edges) {

    vector<vector<int>> graph(n);
    vector<bool> visited(n, false);
    
    // Build adjacency list - graph
    for (auto& edge : edges) {
        graph[edge[0]].push_back(edge[1]);
        graph[edge[1]].push_back(edge[0]); // Undirected graph
    }

    int components = 0;

	// count no. of connected components
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            components++; // A new connected component found
            dfs(i, graph, visited);
        }
    }

    return components;
}

int main() {
    int n = 6;
    vector<vector<int>> edges = {{0, 1}, {1, 2}, {3, 4}, {4, 5}};

    cout << "Number of connected components: " << countConnectedComponents(n, edges) << endl;
    return 0;
}


// ---------------------------------------------------------------------------------------------------