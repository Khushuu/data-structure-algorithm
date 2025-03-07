// Prim's Algorithm 
// is a greedy algorithm used to find the Minimum Spanning Tree (MST) of a connected, weighted, undirected graph. Unlike Kruskal's Algorithm, which sorts edges and uses Union-Find,
// Prim's Algorithm builds the MST incrementally, always adding the minimum weight edge that connects a visited vertex to an unvisited vertex.

// Steps for Prim’s Algorithm
// Initialize: Start from any vertex and mark it as visited.
// Use a priority queue (min-heap) to select the smallest edge (node, neighbor, weight) where node is already in MST and neighbor is not yet included.
// Add the selected edge to the MST and mark the new vertex as visited.
// Repeat until MST contains V−1 edges.

// Leetcode problems
// 1135. Connecting Cities With Minimum Cost (Kruskal's)
// 1168. Optimize Water Distribution in a Village (Prim’s)
// 1584. Min Cost to Connect All Points (Prim’s/Kruskal’s)
// 1631. Path With Minimum Effort (Prim’s)
// 1192. Critical Connections in a Network (Kruskal’s)
// 1489. Find Critical and Pseudo-Critical Edges in MST (Kruskal’s)
// 685. Redundant Connection II (Union-Find/Kruskal’s)

// Priority Queue Operations: O(ElogV) (each insertion/removal in min-heap)
// Overall Complexity: O(ElogV) (efficient for dense graphs)
// Space Complexity: O(V+E)

// Comparison of Kruskal’s and Prim’s Algorithm

// Criterion			Kruskal’s Algorithm			Prim’s Algorithm
// Approach			Greedy, uses edges			Greedy, uses vertices
// Data Structure		Union-Find (DSU)			Min-Heap (Priority Queue)
// Graph 				Edge List					Adjacency List
// Best for			Sparse Graphs (O(ElogE))	Dense Graphs (O(ElogV))
// Time Complexity		O(ElogE)					O(ElogV)


// --------------------------------------------------------------------------------------------------



vector<pair<int, int>> prims(int n, vector<vector<pair<int, int>>>& graph) {

    vector<bool> inMST(n, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // Min-heap {weight, vertex}
    vector<pair<int, int>> mst; // Stores edges of MST
    
    pq.push({0, 0}); // Start from vertex 0
    int edgeCount = 0, totalWeight = 0;

    while (!pq.empty() && edgeCount < n - 1) {

        auto [weight, node] = pq.top();
        pq.pop();

        if (inMST[node]) continue; // Ignore if already in MST

        inMST[node] = true;
        totalWeight += weight;
        if (node != 0) mst.push_back({weight, node}); // Store edge

        for (auto [neighbor, w] : graph[node]) {
            if (!inMST[neighbor]) pq.push({w, neighbor});
        }
    }

    return mst; // MST edges
}

int main() {
    int n = 4; // Number of vertices
    vector<vector<pair<int, int>>> graph(n);
    
    graph[0].push_back({1, 10});
    graph[0].push_back({2, 6});
    graph[0].push_back({3, 5});
    graph[1].push_back({3, 15});
    graph[2].push_back({3, 4});

    vector<pair<int, int>> mst = prims(n, graph);

    cout << "Edges in MST:\n";
    for (auto [weight, neighbor] : mst) {
        cout << "0 - " << neighbor << " : " << weight << endl;
    }

    return 0;
}


// --------------------------------------------------------------------------------------------------