// Bipartite Graph
// A Bipartite Graph is a graph whose vertices can be divided
// into two independent sets such that no two adjacent nodes belong to the same set. 

// A graph is bipartite if it can be colored with two colors such that no adjacent nodes have the same color.

// Example of a Bipartite Graph
//    1 -- 2
//    |    |
//    3 -- 4
// Here, we can divide the graph into two sets:

// Set 1: {1, 4}
// Set 2: {2, 3}
// No two nodes in the same set are connected, making it bipartite.

// Methods to Check for a Bipartite Graph
// Using BFS (Breadth-First Search)
// Using DFS (Depth-First Search)

// Properties of Bipartite Graph
// A graph is bipartite if and only if it does not contain an odd-length cycle. - no odd cycle in graph
// All trees are bipartite graphs because they can always be colored in two sets. - as no cycle is there 

// Leetcode problems
// 785. Is Graph Bipartite? 
// 886. Possible Bipartition --> nodes from 1 to n so create color of size n + 1, convert dislikes - edges to graph adjacency list --> check for each connected component by looping from 1 to n

// NOTE
// we are not using any visited array
// a color vector will be used even to identify unvisited state
// it can have 3 values --> initialize all nodes with value of -1 --> denoting node is not visited
// if a node is colored with 1 --> color its neighboring node with color 0

//  1. Checking Bipartiteness Using BFS (Breadth-First Search)

// We use a coloring approach:
// Assign one color (0) to the starting node.
// Assign the opposite color (1) to its neighbors.
// If we find any adjacent node already colored with the same color, the graph is not bipartite.

// T.C = O(V + E) (Each node and edge is processed once)
// S.C = O(V) (For queue and color array)
// -----------------------------------------------------------------------------------------------------
bool isBipartiteBFS(int start, vector<vector<int>> &graph, vector<int> &color) {

    queue<int> q;
    q.push(start);
    color[start] = 0;  // Assign first color as 0

    while (!q.empty()) {

        int node = q.front();
        q.pop();

        for (int neighbor : graph[node]) {
                
			// If not colored, assign the opposite color
            if (color[neighbor] == -1) {  
                color[neighbor] = !color[node];
                q.push(neighbor);
            } else if (color[neighbor] == color[node]) {
                return false; // Found same color on adjacent nodes
            }
        }
    }

    return true;
}

bool isGraphBipartite(vector<vector<int>> &graph, int n) {
    vector<int> color(n, -1); // -1 indicates uncolored nodes

    for (int i = 0; i < n; i++) { 
        if (color[i] == -1) {  // Check for every component
            if (!isBipartiteBFS(i, graph, color)) {
                return false;
            }
        }
    }
    return true;
}
// -----------------------------------------------------------------------------------------------------

// 2. Checking Bipartiteness Using DFS (Depth-First Search)
// We recursively assign colors to nodes and check if adjacent nodes have different colors.
// If an adjacent node has the same color, the graph is not bipartite.

// T.C = O(V + E)
// S.C = O(V) (For recursion stack and color array)
// -----------------------------------------------------------------------------------------------------

bool isBipartiteDFS(int node, int col, vector<vector<int>> &graph, vector<int> &color) {

    color[node] = col;  // Assign current node a color

    for (int neighbor : graph[node]) {

        // If the node is not colored, assign the opposite color
        if (color[neighbor] == -1) { 
            if (!isBipartiteDFS(neighbor, !col, graph, color))
                return false;
        } else if (color[neighbor] == color[node]) {
            return false; // Found same color on adjacent nodes
        }
    }

    return true;
}

bool isGraphBipartite(vector<vector<int>> &graph, int n) {
    vector<int> color(n, -1);  // -1 indicates uncolored nodes

    for (int i = 0; i < n; i++) { 
        if (color[i] == -1) {  // Check for every component
            if (!isBipartiteDFS(i, 0, graph, color)) {
                return false;
            }
        }
    }
    return true;
}

// -----------------------------------------------------------------------------------------------------