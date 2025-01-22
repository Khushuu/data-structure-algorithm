// given a weighted graph (directed / undirected)
// and a source node
// find shortest path from source node to every other node

// we use a minHeap to know which node is at the minimum distance from the source node
// push a pair of distance and node number into the minHeap
// we pick the node at min distance from source node for traversing and is connected to this node
// initialize the distance of each node from source node as INFINITY that is unreachable - INT_MAX
// the distance of source node from itself will be 0

// priority queue - T.C: insertion: O(logn), deletion: O(logn), top: O(1)

// kind of same as bfs, instead of inserting in a queue we insert in a priority queue
// how to set distance
// if(dist[neighbor] > dist[node] + weight 
// (existing distance to reach this node from source > processing node + distance between the two nodes)

// Initialization:
// Set the distance to the source node to 0 and all other nodes to infinity.
// Use a priority queue (min-heap) to store nodes by their current shortest distance.

// Relaxation:
// Extract the node with the smallest distance from the minHeap.
// For each neighbor of the current node, calculate the distance through the current node.
// If the calculated distance is less than the current known distance to that neighbor, update it and push the neighbor into the queue.

// Termination:
// Continue the process until all nodes are visited or the priority queue is empty.

// Limitations:
// Does not work with graphs containing negative weight edges (use Bellman-Ford instead)
// Not ideal for unweighted graphs (use BFS for shortest path)

// T.C = O((V + E).logV)
// S.C = O(V + E) with adjacency list

const int INF = numeric_limits<int>::max();

void dijkstra(int source, vector<vector<pair<int, int>>>& graph) {

	// n = no. of nodes in the graph
    int n = graph.size();
	// initialization with INF means all nodes are unreachable
    vector<int> dist(n, INF);
	// minHeap of a pair of distance, node
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap; 

	// disatance
    dist[source] = 0;
    minHeap.push({0, source});

    while (!minHeap.empty()) {

        int d = minHeap.top().first; // distance from the node 
        int u = minHeap.top().second; // neighbor node
        minHeap.pop();

		// if the distance in the minHeap for the node is greater than distance stored in array
		// then do not go with the relaxation step
		// as it can never minimize the distance 
        if (d > dist[u]) continue; 

		// loop over all the connected nodes of u
		// if a node v connected to u --> has dist[v] > dist[u] + weight of edge connecting u and v
		// then we can reach v via u with less distance
		// update the distance of v from source
		// if path was also required u could have updated the parent of v to u
		// dist array denotes the distance of each node from the source node 
		// and our intention is to minimize this distance
		// when the distance is updated this node can again be picked as it can relax the distance of nodes connected to it
		// it won't be picked again bcoz we always pick the small distance
		// it is possible that one or more copy of the node and distance are there in minHeap
		// but always the smallest distance is picked and each node is processed just once
		// hence push the new distance and the node to u
        for (auto& edge : graph[u]) {
            int v = edge.first, weight = edge.second;
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                minHeap.push({dist[v], v});
            }
        }
    }

    for (int i = 0; i < n; i++) {
        cout << "Distance to node " << i << ": " << (dist[i] == INF ? -1 : dist[i]) << endl;
    }
}

int main() {
    int n, m;
    cin >> n >> m; // Number of nodes and edges
	// create adjacency list with edge and the weight
    vector<vector<pair<int, int>>> graph(n);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w; // Edge from u to v with weight w
        graph[u].emplace_back(v, w);
        graph[v].emplace_back(u, w); // For undirected graph
    }

    int source;
    cin >> source;
    dijkstra(source, graph);

    return 0;
}
