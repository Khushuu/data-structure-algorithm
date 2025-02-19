// kosaraju's algorithm 

// strongly connected components 

// exist for a directed graph
// a subset of graph where there is a path from each node to each node 

// transposed graph - edge direction is reversed if graph has edge from a->b 
// transposed graph will have edge from b->a

// no. of strongly connected components in graph and transposed will be the same 

// CONDENSATION GRAPH 

// using scc of the original graph 
// each scc acts as a vertex in condensation graph 
// ther is an edge between scc_1 and scc_2 vertext in condensation graph 
// if there exists a vertext u in scc_1 and another vertex v in scc_2 such that there is an edge betwee u and v

// condensation graph does not contain any cycle 
// y --> because if there was a cycle in between the connected components acting as vertex in condensation graph
// --> then that summation of vertex will itself be a connected component
// --> which is a contradiction to the initial claim that we have each vertex as a different connected component 

// out time of each scc and their relation 

// --> if C_a and C_b are Scc and there exists an edge from C_a --> C_b
// --> that means C_a will call C_b --> C_b will be executed before C_a
// --> only after execution of C_b is completed the stack will pop C_a

// --> i.e outTime[C_a] > outTime[C_b]

// --> how 
// --> if suppose dfs is called for C_a first then only after calling the nodes in C_b --> C_a execution will be done
// --> if C_b is called first then there is no way to go to C_a -- we only have edge from C_a --> C_b
// --> so we traverse all nodes in C_b first and then move on to the next connected component
// --> in both cases outTime[C_a] > outTime[C_b]


// --> directed acyclic graph has atleast one node with inDegree = 0
// --> y --> because if the inDegree was > 1 for all that means all nodes are connected and have a cycle
// --> which means it is not a directed acyclic graph 

// --> no condensation graph is directed acyclic graph
// --> each strongly connected component is a vertex
// --> there lies edge connecting these components
// --> there will be atleast 1 strongly connected component with inDegree of 0 

// --> a vertex in condensation graph having inDegree == 0 will have outDegree == 0 in transposed graph
// --> as the direction of all edges is reversed in the transposed graph 


// Kosaraju's Algorithm - Strongly Connected Components (SCC)

// Kosaraju’s Algorithm is an efficient method to find Strongly Connected Components (SCCs) in a directed graph using two DFS traversals.
// A Strongly Connected Component (SCC) is a maximal subgraph where every node is reachable from every other node in that subgraph.

// 1️⃣ Strongly Connected Component (SCC)

// A directed graph is strongly connected if there exists a path between every pair of vertices.
// An SCC is a maximal strongly connected subgraph (i.e., if we add any more nodes, it won't be strongly connected anymore).

// 2️⃣ Transpose of a Graph
// The transpose of a graph is obtained by reversing the direction of all edges.

// Example:

// Original Graph

// Copy
// Edit
// 0 → 1 → 2
// ↑    ↓  
// 3 ←  4
// Transpose (Reverse Edges)

// Copy
// Edit
// 0 ← 1 ← 2
// ↓    ↑  
// 3 →  4

// 3️⃣ Finish Time in DFS
// In a DFS traversal, a node is marked as finished when all its adjacent nodes have been fully explored.
// We store nodes in a stack based on their finish time (the later a node finishes, the later it is processed).

// 🔹 Kosaraju's Algorithm - Step by Step
// Kosaraju’s Algorithm works in two DFS traversals:

// Step 1️⃣: Perform DFS and Store Finish Times
// Run DFS on the original graph.
// Store the nodes in a stack, ordered by their finish time (i.e., when they are completely explored).

// Step 2️⃣: Reverse the Graph
// Transpose the graph (reverse the edges).

// Step 3️⃣: Process Nodes in Decreasing Order of Finish Time
// Run DFS again, but in the order of decreasing finish time (from the stack).
// Each DFS traversal identifies a Strongly Connected Component (SCC).

// why this works
// each scc will have one link to go from scc a to scc b
// as scc are acyclic - explained before
// now if we move in the decreasing order of out time and change the graph direction
// i.e traverse the transposed graph in the decreasing order of out time
// that would mean the scc will be traversed but the connection that helped us move to another scc is reversed
// so we can only traverse a single scc one step at a time 

// 3If We Process SCCs in Wrong Order (Smallest Finish Time First)
// Suppose we pick an SCC B first instead of A.
// Some nodes of A might be reachable in the transposed graph, causing incorrect merging of SCCs.


// 🔹 Related LeetCode Problems
// LeetCode 1192 - Critical Connections in a Network 🌐 (Find Bridges in Graph)
// LeetCode 329 - Longest Increasing Path in a Matrix 🔄 (Graph SCC Concept)
// LeetCode 802 - Find Eventual Safe States 🚀 (Finding Cycles in Graph)
// LeetCode 756 - Pyramid Transition Matrix ⛏ (Graph SCC Applications)
// LeetCode 1129 - Shortest Path with Alternating Colors 🎨 (Graph Traversal)

// Time Complexity:	O(V + E)
// Space Complexity: O(V + E)
// ----------------------------------------------------------------------------------------------------------

void dfs(int node, vector<vector<int>> &graph, vector<bool> &visited, stack<int> &st) {

	visited[node] = true;
	for (int neighbor : graph[node]) {
		if (!visited[neighbor]) {
			dfs(neighbor, graph, visited, st);
		}
	}

	st.push(node);  // Store nodes in stack based on finish time
}

void reverseDFS(int node, vector<vector<int>> &transposedGraph, vector<bool> &visited) {

	visited[node] = true;

	cout << node << " ";  // Print SCC component

	for (int neighbor : transposedGraph[node]) {
		if (!visited[neighbor]) {
			reverseDFS(neighbor, transposedGraph, visited);
		}
	}
}


void findSCCs(int n, vector<vector<int>> &graph) {

	stack<int> st;
	vector<bool> visited(n, false);

	// Step 1: Perform DFS and store nodes in stack based on finish time
	for (int i = 0; i < n; i++) {
		if (!visited[i]) {
			dfs(i, graph, visited, st);
		}
	}

	// Step 2: Reverse the graph
	vector<vector<int>> transposedGraph(n);
	for (int i = 0; i < n; i++) {
		for (int neighbor : graph[i]) {
			transposedGraph[neighbor].push_back(i);  // Reverse the edge
		}
	}

	// Step 3: Process nodes in decreasing order of finish time
	fill(visited.begin(), visited.end(), false);

	cout << "Strongly Connected Components (SCCs):\n";

	while (!st.empty()) {
		int node = st.top();
		st.pop();

		if (!visited[node]) {
			reverseDFS(node, transposedGraph, visited);
			cout << endl;  // New SCC found
		}
	}
}

int main() {
    int n = 5;
    vector<vector<int>> graph(n);
    
    // Example Graph (5 vertices)
    graph[0].push_back(2);
    graph[2].push_back(1);
    graph[1].push_back(0);
    graph[0].push_back(3);
    graph[3].push_back(4);

    Solution sol;
    sol.findSCCs(n, graph);

    return 0;
}
// ----------------------------------------------------------------------------------------------------------

// 🔹 Summary
// Kosaraju’s Algorithm finds SCCs efficiently in O(V + E).
// It uses two DFS traversals:

// First DFS to get the order of finish times.
// Reverse the graph.
// Second DFS to identify SCCs.

// Handles disconnected components effectively.
// Used in dependency resolution, network analysis, and game logic.
