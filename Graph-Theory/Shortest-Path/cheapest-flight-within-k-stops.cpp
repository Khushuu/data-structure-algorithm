// 787. Cheapest Flights Within K Stops

// SOLUTION 1: Modified Dijkstra (BFS + MinHeap)
// SOLUTION 2: BELLMAN-FORD ALGORITHM - better 
// SOLUTION 3: BFS with Queue and Cost Tracking

// ✅ Summary
// Approach		            Data Structure	    Time Complexity	            Space
// BFS	                    Queue	                O(k * E)	            O(n + E)
// Modified Dijkstra		MinHeap	                O(k * E log V)	        O(n + E)
// Bellman-Ford		        DP/Edge Relaxing	    O(k * E)	            O(n)

// --------------------------------------------------------------------------------------------------------------------------

// 🔁 Quick Reminder: How Regular Dijkstra Works
// Dijkstra’s algorithm:
// Finds the shortest path from a source node to all other nodes.
// Uses a min-heap (priority queue) and greedily expands the node with the least total distance.
// Once a node is visited, we don’t revisit it, because we've already found the shortest path to it.
// That last part is critical.

// 🚨 Why Dijkstra Fails for This Problem
// In this problem, there's an extra constraint:
// You can take at most k stops, i.e., at most k + 1 flights.
// But in regular Dijkstra:
// Once we reach a node with the shortest cost, we mark it as visited and never consider other paths to that node again.
// That’s fine if you care only about minimal cost, but not if the number of stops matters!

// 📌 Key Issue: Dijkstra Discards Valid Paths
// Imagine we reach node v with:
// Cost: 100
// Stops: 3

// Now Dijkstra marks v as visited — "we found the best path to v, done!"

// But maybe there’s another path to v:
// Cost: 150
// Stops: 1

// Even though the cost is worse, this second path uses fewer stops, and maybe from there we can take a very cheap edge to the destination — which would make it better overall.

// Regular Dijkstra would never explore that path, because it already marked v as visited. But in this problem, that path might lead to the best valid result (within stop limits).

// 🧠 So What Do We Need Instead?
// We need a modified Dijkstra that:

// Tracks (cost, stops, node) in the priority queue.
// Does not mark a node as visited just once.
// Allows revisiting nodes with different stop counts (as long as stops <= k).
// This way, we can explore alternative paths to a node that may have more cost but fewer hops — which can help us stay within the k stop limit.

// REGULAR DIJKSTRA ASSUMES ONCE A NODE IS VISITED, IT'S DONE.
// BUT HERE, WE NEED TO REVISIT NODES WITH DIFFERENT STOP COUNTS.
// Because if the minimum cost to a node is found, it doesn't mean it's the best path considering the number of stops allowed.
// if the cost is higher but the number of stops is lower, it might lead to a better overall path to the destination.
// So, we need to keep track of both cost and stops in our priority queue.

// this will happen in case where number of stops is the bottleneck
// and not the cost

// --------------------------------------------------------------------------------------------------------------------------

// ✅ Problem Summary
// You're given:
// n cities (numbered from 0 to n-1)
// A list of flights flights[i] = [from, to, price]
// A source city src, a destination city dst, and an integer k

// Goal:
// Find the cheapest price from src to dst with at most k stops (i.e., you can take at most k+1 flights in the path). If there is no such route, return -1.


// 💡 Solution Strategy: Modified Dijkstra (BFS + MinHeap)
// Why not classic Dijkstra?
// In classic Dijkstra, you avoid revisiting a node once it's been processed with the shortest distance.
// But here, you may reach the same node again with fewer stops, which might allow a cheaper route through it later.

// So, we need to:
// Track the current total cost, number of stops, and node.
// Revisit nodes if the number of stops is less than k + 1.
// We’ll use a min-heap (priority_queue) to always expand the cheapest path so far, similar to Dijkstra.

// 📈 Time & Space Complexity
// Time Complexity: O(E * logV)
// Where:
// E = number of edges = up to 10^4
// V = number of nodes = n up to 100

// In the worst case, each node can be visited multiple times (up to k + 1 times), so the complexity becomes:
// O(k * E * log V)
// But because k <= n, and n <= 100, this is acceptable.

// Space Complexity: O(V + E)
// O(E) for the adjacency list (graph)
// O(V) for the priority queue in the worst case

// CODE
// SOLUTION 1: Modified Dijkstra (BFS + MinHeap)
// --------------------------------------------------------------------------------------------------------------------------

class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        // Step 1: Build the graph
        vector<vector<pair<int, int>>> graph(n);  // from -> {to, price}
        for (auto& flight : flights) {
            int u = flight[0], v = flight[1], w = flight[2];
            graph[u].push_back({v, w});
        }

        // Step 2: MinHeap: {cost_so_far, stops_so_far, current_node}
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> minHeap;
        minHeap.push({0, 0, src});  // cost = 0, stops = 0, at src

        // Step 3: While heap not empty, process each node
        while (!minHeap.empty()) {
            auto [cost, stops, u] = minHeap.top();
            minHeap.pop();

            // If destination is reached within allowed stops, return cost
            if (u == dst) return cost;

            // If stops exceeded, skip
            if (stops > k) continue;

            // Explore neighbors
            for (auto& [v, price] : graph[u]) {
                minHeap.push({cost + price, stops + 1, v});
            }
        }

        // If we exhaust heap without reaching dst, return -1
        return -1;
    }
};

// --------------------------------------------------------------------------------------------------------------------------

// 🧠 Why This Works
// This algorithm always picks the path with the lowest cost first, but it doesn’t discard paths with more stops unless they exceed k.
// So even if you reach a node with a higher cost but fewer stops, it may still lead to a better solution downstream.


// --------------------------------------------------------------------------------------------------------------------------

// SOLUTION 2: BELLMAN-FORD ALGORITHM - better

// 🔁 Bellman-Ford Algorithm Recap
// Bellman-Ford is a shortest-path algorithm that works on:
// Graphs with negative weights
// Without requiring priority queues
// It allows up to V-1 edge relaxations

// It works by:
// Repeating edge relaxation multiple times (up to the number of edges in the longest path)
// Each time improving the best known distance to each node

// 🤔 Why Bellman-Ford Works for This Problem?
// We're asked to find the minimum cost to reach from src to dst using at most k stops.
// A path with k stops means k+1 edges (flights).
// So, if we relax all edges k + 1 times, we can cover all paths of at most k+1 edges.
// This fits perfectly into the Bellman-Ford framework.

// CODE
// Time Complexity: O(k × E)
// We do k + 1 iterations
// In each iteration, we scan all E edges (flights)
// So total = O((k + 1) * E)

// Space Complexity: O(n)
// Only two arrays of size n: prev and curr
// --------------------------------------------------------------------------------------------------------------------------

class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        // Initialize distances to all nodes as infinity
        vector<int> prev(n, INT_MAX);
        prev[src] = 0;

        // Repeat edge relaxation up to k + 1 times (max k stops = k+1 flights)
        for (int i = 0; i <= k; ++i) {
            // Make a copy so we don't update distances for this round based on this round
            vector<int> curr = prev;

            for (auto& flight : flights) {
                int u = flight[0];
                int v = flight[1];
                int price = flight[2];

                if (prev[u] != INT_MAX) {
                    curr[v] = min(curr[v], prev[u] + price);
                }
            }

            prev = curr;
        }

        return prev[dst] == INT_MAX ? -1 : prev[dst];
    }
};

// --------------------------------------------------------------------------------------------------------------------------

// 🧠 How It Works
// Let’s break it down:
// prev[i] stores the minimum cost to reach node i in the previous round
// In each of the k + 1 iterations:
// We create a fresh curr array to hold updated distances
// We go through all flights, and relax edges if possible
// After the round, we update prev = curr
// At the end:
// prev[dst] holds the minimum cost to reach dst with at most k + 1 edges

// 🧪 Example
// n = 3
// flights = [[0,1,100],[1,2,100],[0,2,500]]
// src = 0, dst = 2, k = 1
// Iteration 0:
// Initial distances: [0, INF, INF]
// Relax:
// 0 -> 1: 100 → dist[1] = 100
// 0 -> 2: 500 → dist[2] = 500

// New distances: [0, 100, 500]

// Iteration 1:
// Relax:
// 1 -> 2: 100 + 100 = 200 → dist[2] = 200 (better than 500)
// Final distances: [0, 100, 200]
// Return 200 ✅

// --------------------------------------------------------------------------------------------------------------------------

// 🧠 Why BFS Works
// In this problem, the "depth" of the BFS tree corresponds to the number of stops used.
// So:
// BFS level 0: src
// BFS level 1: neighbors of src (1 stop)
// ...
// BFS level k + 1: max path depth (up to k stops allowed)

// We track the minimum cost to reach each node and allow reaching a node again if we find a cheaper cost at the same or fewer stops.

// ✅ Approach Summary (BFS)
// Build an adjacency list of flights.
// Use a queue of (node, cost, stops) to process nodes level by level.
// Track the minimum cost to reach each node with at most k stops.
// For each node, enqueue its neighbors with updated cost and stop count (if within the limit).

// ✅ C++ Code: BFS

// ⏱ Time Complexity: O(k * E)
// Each edge can be relaxed up to k + 1 times.
// In worst-case, each node is visited k + 1 times → O(k * E)

// 🧠 Space Complexity: O(n + E)
// O(E) for the graph adjacency list
// O(n) for the minCost array
// O(k * n) for the queue in the worst case
// --------------------------------------------------------------------------------------------------------------------------


class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        // Step 1: Build graph
        vector<vector<pair<int, int>>> graph(n);
        for (auto& flight : flights) {
            int u = flight[0], v = flight[1], w = flight[2];
            graph[u].push_back({v, w});
        }

        // Step 2: Queue for BFS: {current_node, cost_so_far, stops_so_far}
        queue<tuple<int, int, int>> q;
        q.push({src, 0, 0});

        // Step 3: Track minimum cost to reach each node with at most k stops
        vector<int> minCost(n, INT_MAX);
        minCost[src] = 0;

        while (!q.empty()) {
            auto [u, cost, stops] = q.front();
            q.pop();

            // If stops exceed limit, skip this path
            if (stops > k) continue;

            // Visit all neighbors
            for (auto& [v, price] : graph[u]) {
                int newCost = cost + price;

                // Only proceed if it's cheaper OR hasn't been visited with fewer stops
                if (newCost < minCost[v]) {
                    minCost[v] = newCost;
                    q.push({v, newCost, stops + 1});
                }
            }
        }

        return minCost[dst] == INT_MAX ? -1 : minCost[dst];
    }
};

// --------------------------------------------------------------------------------------------------------------------------

// 🔍 Important Notes
// We don’t stop BFS early at dst, because we might find a cheaper path later.
// We prune paths if stops exceed k.
// We only proceed to a neighbor if it improves the cost (or is unvisited).

// 🧪 Example
// Input:
// n = 3, flights = [[0,1,100],[1,2,100],[0,2,500]],
// src = 0, dst = 2, k = 1
// Paths:

// 0 -> 2: cost = 500 (0 stops)
// 0 -> 1 -> 2: cost = 200 (1 stop)

// We explore both paths. BFS finds the 200 path ✅

// --------------------------------------------------------------------------------------------------------------------------

