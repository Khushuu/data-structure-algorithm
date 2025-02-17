
// dfs approach - 2 dfs calls
// to find the diameter of the graph
// find the node at the maximum distance from the start node by calling dfs on start
// run another dfs call from the farthest node to get the diameter of the graph

// T.C = O(N + E) --> traverse all nodes and edges
// V.C = O(N + E) --> adjacency list 

// ---------------------------------------------------------------------------------------------------

int maxDist;
int farthest;

void dfs(int node, int dist, vector<bool>& visited, vector<vector<int>>& graph) {
	
	visited[node] = true;

	if(maxDist < dist) {
		maxDist = dist;
		farthest = node;
	}

	for(int neighbor: graph[node]) {
		if(!visited[neighbor])
			dfs(neighbor, dist + 1, visited, graph);
	}
}

// graph is adjacency list
int diameter(int start, vector<vector<int>>& graph) {

	int n = graph.size();
	vector<bool> visited(n, false);
	
	maxDist = 0;
	farthest = 0;
	dfs(start, 0, visited, graph); // first dfs call from start node

	maxDist = 0;
	// reset the visited array to false
	for(int i = 0; i < n; i++) visited[i] = false;
	dfs(farthest, 0, visited, graph); // dfs call from the farthest node to get the diameter 

	return maxDist;
}



// ---------------------------------------------------------------------------------------------------