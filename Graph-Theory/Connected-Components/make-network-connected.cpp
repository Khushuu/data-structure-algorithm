1319. Number of Operations to Make Network Connected

// given n nodes and edges (a, b) - a and b are connected bi-directionally
// You can extract certain cables between two directly connected computers, 
// and place them between any pair of disconnected computers to make them directly connected.
// Return the minimum number of times you need to do this in order to make all the computers connected.
// If it is not possible, return -1.

// approach
// a tree is connected with no cycles
// n nodes and n - 1 edges
// so if we have edges >= n - 1 then it can be made connected
// if no. of edges is < n - 1 graph can never be made connected
// n - 1 is the minimum number of edges that are needed to connect n nodes --> to make graph connected 

// then we only need to find the total no. of connected components
// let total connected component = count
// to connect these components we need count - 1 edges
// return count - 1

// ----------------------------------------------------------------------------------------------------

void dfs(int node, vector<bool>& visited, vector<vector<int>>& graph) {

	visited[node] = true;

	for(int neighbor: graph[node]) {
		if(!visited[neighbor])
			dfs(neighbor, visited, graph);
	}
}

int makeConnected(int n, vector<vector<int>>& connections) {
	
	int edges = connections.size();

	// graph can never be connected as not enough edges
	if(edges < n - 1) return -1;

	vector<vector<int>> graph(n);
	vector<bool> visited(n, false);
	
	for(const auto &edge: connections) {
		graph[edge[0]].push_back(edge[1]);
		graph[edge[1]].push_back(edge[0]);
	}

	// count connected components = count
	// count - 1 edges will be needed to connect them 
	// as to connect n nodes we need n - 1 edges
	int count = 0;

	for(int i = 0; i < n; i++) {
		if(!visited[i]) {
			count++;
			dfs(i, visited, graph);
		}
	}

	return count - 1;
}

// ----------------------------------------------------------------------------------------------------
