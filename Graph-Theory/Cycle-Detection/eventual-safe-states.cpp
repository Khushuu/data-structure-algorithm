// 802. Find Eventual Safe States

// You are given a directed graph with n nodes labeled from 0 to n-1. 
// A node is eventually safe if every possible path starting from that node leads to a terminal node
// A terminal node is a node that has no outgoing edges.
// Return an ascending sorted list of all eventual safe nodes.

// Approach
// all nodes that are part of a cycle will never be safe nodes 
// y? -- because there path will never terminate
// so the nodes which are not part of any cycle are safe nodes

// also all the nodes that are present in the stack at the time of finding cycle will be unsafe
// even if they are not part of the cycle
// y --> because there was a path that lead them to enter into a cycle - a never ending path
// and the questions ask that all path should lead to a safe node --> terminal node 

// since we return as soon as we find a cycle in a directed graph
// we do not backtrack and set inStack = false is not set
// this means all the nodes for which inStack = true are nodes present in cycle = unsafe nodes
// so at the end of traversing all the connected components --> the nodes which have inStack = false --> safe nodes
// as we use !visited to run dfs again -- nodes with inStack = true will already be visited
//  and won't be picked again for running dfs

// NOTE:
// if we start from a node that is in the cyle -- all nodes will be traversed and inStack = true for those
// now when we pick another node that leads to cycle
// isVisited will be true for cycle node and inStack will also be true
// this means the node that connects to a cycle will also have inStack = true and will return true for hasCycle call

// DFS
// T.C = O(n + e)
// S.C = O(n)
//------------------------------------------------------------------------------------------------------
bool hasCycle(int node, vector<bool>& visited, vector<bool>& inStack, vector<vector<int>>& graph) {

	visited[node] = true;
	inStack[node] = true;

	for(int neighbor: graph[node]) {
		if(!visited[neighbor]) {
			if(hasCycle(neighbor, visited, inStack, graph))
				return true;
		}
		else if(inStack[neighbor]) return true;
	}

	inStack[node] = false;
	return false;
}

vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
	
	int n = graph.size();
	vector<bool> visited(n, false);
	vector<bool> inStack(n, false);
	vector<int> result;


	for(int i = 0; i < n; i++) {
		if(!visited[i])
			hasCycle(i, visited, inStack, graph);
	}

	// if not in stack means not part of cycle - safe node
	for(int i = 0; i < n; i++) {
		if(!inStack[i])
			result.push_back(i);
	}

	return result;
}
//------------------------------------------------------------------------------------------------------

// BFS
// Kahn's algorithm - topological sorting
// terminal nodes have outdegree == 0 --> all edges directed towards them --> u
// reverse graph will have inDegree == 0 --> all edges directed from them <-- u
// so all nodes which have inDegree = 0 and can be picked for traversal will be safe nodes 

// Concept
// Reverse the graph (reverseGraph), making terminal nodes sources.
// Use Kahn’s Algorithm (BFS):
// Start with terminal nodes (no outgoing edges).
// Process their incoming edges.
// If a node has no outgoing edges left, it's safe.
// The final safe nodes are the ones we processed.

// BFS (Topological Sort)	O(V + E)	O(V + E)
//------------------------------------------------------------------------------------------------------
vector<int> eventualSafeNodes(vector<vector<int>>& graph) {

	int n = graph.size();
	vector<vector<int>> reverseGraph(n);
	vector<int> inDegree(n, 0);

	// Step 1: Reverse the graph
	for (int u = 0; u < n; u++) {
		for (int v : graph[u]) {
			reverseGraph[v].push_back(u);
			inDegree[u]++; // reverse graph inDegree
		}
	}

	// Step 2: Use BFS to process nodes with in-degree 0 (terminal nodes)
	queue<int> q;
	for (int i = 0; i < n; i++) {
		if (inDegree[i] == 0) q.push(i);
	}

	vector<int> result;
	while (!q.empty()) {

		int node = q.front();
		q.pop();
		result.push_back(node); // inDegree = 0 in reverse graph - outDegree = 0 in actual graph = safe node

		for (int neighbor : reverseGraph[node]) {
			inDegree[neighbor]--;
			if (inDegree[neighbor] == 0) {
				q.push(neighbor);
			}
		}
	}

	sort(result.begin(), result.end()); // Ensures sorted order
	return result;
}
//------------------------------------------------------------------------------------------------------

