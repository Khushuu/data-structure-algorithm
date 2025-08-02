// SHORTEST PATH ALGORITHM - DIJKSTRA's algoirthm

// it is a greedy algorithm
// as it always picks the neighbor edge of the node with the least weight
// this is done using a min heap - priority queue of pair of weight, node 
// The priority queue ensures that the node with the shortest known distance is always processed first.
// For each node that is extracted from the priority queue, its neighbors are checked. 
// If traveling through the current node provides a shorter path to a neighboring node, the shortest time to that node is updated, and the neighbor is added to the priority queue for further processing. 
// This continues until all nodes have been processed, at which point the shortest time to each node is known.

// Sample leetcode problem: 
// 743. Network Delay Time: https://leetcode.com/problems/network-delay-time/description/

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

// The Key Insight
// The critical point is that Dijkstra can work with negative edges as long as:

    // No negative cycles exist
    // The priority queue processes nodes in order of current shortest distance
    // The statement in your comment might be too absolute. A more accurate statement would be:

// "Standard Dijkstra's algorithm is designed for non-negative weights and may not guarantee optimal results with negative edges in all implementations, though some implementations can handle negative edges without negative cycles."

// Dijkstra's algorithm doesn't work with negative weight edges because it assumes that once a node's shortest distance is finalized (processed), it will never be updated. This assumption is violated when negative weight edges exist.

// Dijkstra's Limitation: It assumes that once a node's shortest distance is finalized, it will not change.
//Negative Weight Edges: Violate this assumption as a shorter path might appear after finalizing a node.
// Alternative: Use the Bellman-Ford Algorithm for graphs with negative weight edges.

// Dijkstra's algorithm fails for a cycle with negative weights
// y
// as it will keep reducing the distance reachable for nodes in the cycle again and again
// each time it will insert min distance of node from source and try to minimize distance of its neighbor
// and this will keep going on endlessly

// Time complexity: O((N+E)logN)

// Constructing the adjacency list requires iterating over all E edges, taking O(E) time. Dijkstra's algorithm, implemented using a priority queue, processes each node at most once, and each edge is relaxed once. Since inserting and extracting from a priority queue takes O(logN) time, the total complexity of Dijkstra’s traversal is O((N+E)logN).

// The inner loop of Dijkstra's algorithm iterates over all neighboring edges of the current node. Since each edge is processed only when it is relaxed, it results in an overall complexity of O(ElogN). Combining the adjacency list construction and Dijkstra’s algorithm, the total time complexity remains O((N+E)logN).


// T.C = O((V + E).logV)
// S.C = O(V + E) with adjacency list
// he total space used is dominated by O(N+E) for storing the graph, the overall space complexity is O(N+E).t

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

        // int d = minHeap.top().first; // distance from the source node
        // int node = minHeap.top().second; // node
        auto [d, u] = minHeap.top(); // distance, node
        minHeap.pop();

		// if the distance in the minHeap for the node(from source node) is greater than distance stored in array
		// then do not go with the relaxation step
		// as it can never minimize the distance 
        
        // if the heap has stale data u do not need to look over the neighbors of that node 
        // if (d > dist[node]) continue; 
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

        for (auto& [v, weight] : graph[u]) {
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                minHeap.push({dist[v], v});
            }
        }

        // for(auto &[v, w]: graph[node])
        // for (auto& edge : graph[node]) {

        //     int neighbor = edge.first, weight = edge.second;
        //     int newDistance = dist[node] + weight;

        //     if (newDistance < dist[neighbor]) {
        //         dist[neighbor] = newDistance;
        //         minHeap.push({dist[neighbor], neighbor});
        //     }
        // }
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

