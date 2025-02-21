// 2360. Longest Cycle in a Graph

// You are given a directed graph of n nodes numbered from 0 to n - 1, 
// where each node has at most one outgoing edge.
// The graph is represented with a given 0-indexed array edges of size n, indicating that there is a directed edge from node i to node edges[i]. 
// If there is no outgoing edge from node i, then edges[i] == -1.
// Return the length of the longest cycle in the graph. If no cycle exists, return -1.
// A cycle is a path that starts and ends at the same node.

// approach
// use cycle detection algorithm in directed graph - dfs
// save timer in the inStack array
// every time u insert array in stack --> make a dfs call to it - update the timer
// when a cycle is detected i.e the inStack[node] > 0 then update the longest cycle path
// cycle length = inStack[node] - inStack[neighbor] + 1 

// suppose there is a cycle of length 4 ==> 2 --> 3 --> 4 --> 5 --> 2
// inStack value of these will be --> 2, 3, 4, 5 --> now when u see 2 again
//  do inStack[node] - inStack[neighbor] + 1 ==> 5 - 2 + 1

// for backtracking step set the inStack value to 0
// also there can be atmost 1 neighbor for each node so we don't need to run a for loop for neighbors

// T.C = O(n)
// S.C = O(n)
//-----------------------------------------------------------------------------------------------


int maxLen;
int timer;

void hasCycle(int node, vector<bool>& visited, vector<int>& inStack, vector<int>& edges) {

	timer++;
	visited[node] = true;
	inStack[node] = timer;

	// no neighbor
	int neighbor = edges[node];
	
	if(neighbor != -1) {

		if(!visited[neighbor]) {
			hasCycle(neighbor, visited, inStack, edges);
		}
		else if(inStack[neighbor] > 0) {
			maxLen = max(maxLen, inStack[node] - inStack[neighbor] + 1);
		}
	}

	inStack[node] = 0;
}

int longestCycle(vector<int>& edges) {
	
	int n = edges.size();
	vector<bool> visited(n, false);
	vector<int> inStack(n, 0); // keep track of timer for each node
	maxLen = -1;
	timer = 0;

	// one component can have only once cycle
	// as there are maximum of 1 outgoing edge from each node
	// run for all components
	for(int i = 0; i < n; i++) {
		if(!visited[i])
			hasCycle(i, visited, inStack, edges);
	}

	return maxLen;
}

//-----------------------------------------------------------------------------------------------