// given a graph
// return true or false if there exists a cycle in the graph

// parent --> node that calls the dfs function
// back edge --> edge that connects a node to its ancestor which is not its direct parent

// if u found a node that is already visited 
// and this node was visited from some other path
// i.e if u reach current node via parent always like a tree --> it won't have cycle
// as there will only be one path to reach a node via its parent
// but if u find a node that is already visited and 
// there is an edge between this visited node which is not the parent of current node that means 
// more than 1 path exists and there is a cycle in the graph 


// Undirected Graph 
// A cycle is detected if we visit a previously visited node that is not the parent of the current node.

// Cycle Detection in an Undirected Graph
// Approach: Using DFS
// Maintain a visited array.
// Keep track of the parent node to avoid counting the immediate previous node as a cycle.
// If we encounter a visited node that is not the parent, a cycle is detected.

// Undirected Graph → Use DFS with parent tracking.
// Directed Graph (DFS) → Use recursion stack tracking.
// Directed Graph (BFS - Kahn’s Algorithm) → Use Topological Sorting.
// Time Complexity → O(N + E) in all cases.

// Time Complexity: O(N + E) → DFS traverses each node and edge once.
// Space Complexity: O(N + E) → Adjacency list storage + recursion stack.
//----------------------------------------------------------------------------------------------
class Solution {
private:
    bool dfs(int node, int parent, vector<vector<int>>& graph, vector<bool>& visited) {

        visited[node] = true;

        for (int neighbor : graph[node]) {

            if (!visited[neighbor]) { // not visited - run dfs for neighbor
                if (dfs(neighbor, node, graph, visited)) return true;
            } 
            else { // visited
				if (neighbor != parent)  // If visited and not the parent, cycle found
                	return true;
			}
        }
        return false;
    }

public:
    bool hasCycle(int n, vector<vector<int>>& edges) {

        vector<vector<int>> graph(n);
        vector<bool> visited(n, false);

        // Build the adjacency list
        for (auto& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]); // Since undirected graph
        }

        // Check for cycle in all components
		// initially the parent will be -1
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                if (dfs(i, -1, graph, visited)) return true;
            }
        }

        return false;
    }
};
//----------------------------------------------------------------------------------------------

// Cycle Detection in a Directed Graph

// Approach: Using DFS with Recursion Stack

// Maintain two arrays:
// visited[] → To mark visited nodes.
// recStack[] → To track nodes in the current DFS path.
// If we revisit a node already in the recursion stack, a cycle is found.

// Time Complexity: O(N + E) → DFS processes each node and edge once.
// Space Complexity: O(N + E) → Adjacency list storage + recursion stack.
//----------------------------------------------------------------------------------------------
class Solution {
private:
    bool dfs(int node, vector<vector<int>>& graph, vector<bool>& visited, vector<bool>& recStack) {

        visited[node] = true;
        recStack[node] = true;

        for (int neighbor : graph[node]) {
            if (!visited[neighbor]) {
                if (dfs(neighbor, graph, visited, recStack)) return true;
            } 
            else if (recStack[neighbor]) { // If node is already in recursion stack, cycle found
                return true;
            }
        }

        recStack[node] = false; // Remove from recursion stack when backtracking
        return false;
    }

public:
    bool hasCycle(int n, vector<vector<int>>& edges) {

        vector<vector<int>> graph(n);
        vector<bool> visited(n, false);
        vector<bool> recStack(n, false);

        // Build adjacency list
        for (auto& edge : edges) {
            graph[edge[0]].push_back(edge[1]); // Directed graph
        }

        // Check for cycles in all components
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                if (dfs(i, graph, visited, recStack)) return true;
            }
        }

        return false;
    }
};

//----------------------------------------------------------------------------------------------