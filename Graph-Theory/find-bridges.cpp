// To find bridges in a graph (also known as cut-edges)
// we use a DFS-based algorithm known as Tarjan’s Algorithm for bridges.

// back-edge: edge connecting a node to its ancestor which is not its direct parent
// presence of back-edge means there is cycle in the graph

// back-edge can never be a bridge
// bridge is an edge whose removal makes the graph disconnected
// even if u remove the back-edge the graph will still be connected by forward edge
// hence back-edge can never be a bridge 

// only a forward edge can be a bridge

// concept
// In an undirected graph, an edge is a bridge if removing it increases the number of connected components.
// In Time: The time when a node is first visited.
// Low Time: The earliest visited vertex (the lowest in time) reachable from the subtree rooted with that node.

// all nodes in a cycle will finally have the same low time 

// An edge (u, v) is a bridge if:
// low[v] > in[u]
// i.e low[child] > in[node]

// 1192. Critical Connections in a Network
// optimization
// u can use in time to identify if a node is visited or not
// intialize it with -1 and if a node is not visited its value will be -1
// remove using visited array then

// code
// --------------------------------------------------------------------------------------------------


int timer = 0;
vector<int> in;
vector<int> low;
vector<bool> visited;
vector<vector<int>> graph;
vector<vector<int>> bridges;

void dfs(int node, int parent) {

	visited[node] = true;
	in[u] = low[u] = timer;
	timer++;
	
	for (int child : graph[node]) {

		if (child == parent) continue; // skip the parent

		if(visited[child]) {
			// already visited then it is a back edge (child - node)
			// back edge can not be a bridge
			// minimize the low time of the node using the child node
			// since child node is the ancestor of the node 
			// why we use min - since if there r multiple back edges we want to maintain the minimum value
			low[node] = min(low[node], in[child]); 
		}
		else {

			// this child-node edge is a forward edge
			// and this node is not visited 
			// run dfs first
			// then check if it is a bridge or not - if the low time of child node is greater than the node 
			// then it is a bridge --> otherwise it means the child was connected to an ancestor 
			// hence low[child] > in[node]
			// and try to minimize the low time of the node 
			dfs(child, node);
			if(low[child] > in[node])
				bridges.push_back({child, node});
			
			low[node] = min(low[node], low[child]);
		}
	}
}

vector<vector<int>> findBridges(int n, vector<vector<int>>& edges) {

	graph.resize(n);
	in.resize(n);
	low.resize(n);
	visited.resize(n);

	// build an undirected graph
	for(vector<int> &edge: edges) {
		graph[edge[0]].push_back(edge[1]);
		graph[edge[1]].push_back(edge[0]);
	}

	// check for all connected components
	for (int i = 0; i < n; i++) {
		if (!visited[i]) {
			dfs(i, -1);
		}
	}

	return bridges;
}


// --------------------------------------------------------------------------------------------------