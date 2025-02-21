// 2608. Shortest Cycle in a Graph
// use bfs 
// dfs wouldn't work as it doesn't return the shortest cycle 
// cycle length = dist[node] + dist[neighbor] + 1

// 🔹 Explanation
// Build the Graph

// Use an adjacency list from the given edges.
// Run BFS for Each Node

// A dist array tracks distances from the current BFS start node.
// A queue<pair<int, int>> stores (node, parent), eliminating the need for a parent array.
// Detect Cycles

// If a node is revisited and it's not the parent, a cycle is detected.
// Compute cycle length as dist[node] + dist[neighbor] + 1.
// Update minCycle accordingly.
// Return Result

// If no cycle is found, return -1.

// Time Complexity: O(N+M) per BFS call, worst case runs for every node → O(N×(N+M))
// Space Complexity: O(N+M) (adjacency list) + O(N) (dist array) + O(N) (queue) → O(N+M)
//--------------------------------------------------------------------------------------------------------------

class Solution {
public:
    int findShortestCycle(int n, vector<vector<int>>& edges) {
        vector<vector<int>> graph(n);
        
        // Build the adjacency list
        for (const auto& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }

        int minCycle = INT_MAX;

        // Try BFS from every node (handling disconnected components)
        for (int start = 0; start < n; start++) {

            vector<int> dist(n, -1);  // Stores shortest distance from start
            queue<pair<int, int>> q;  // Stores (node, parent)
            
            dist[start] = 0;
            q.push({start, -1});  // Start BFS from node with no parent

            while (!q.empty()) {

                auto [node, parent] = q.front();
                q.pop();

                for (int neighbor : graph[node]) {
                    if (dist[neighbor] == -1) { 
                        // If neighbor is unvisited, push it in queue
                        dist[neighbor] = dist[node] + 1;
                        q.push({neighbor, node});
                    } else if (neighbor != parent) {
                        // Cycle detected: neighbor is visited and not the parent
                        minCycle = min(minCycle, dist[node] + dist[neighbor] + 1);
                    }
                }
            }
        }

        return (minCycle == INT_MAX) ? -1 : minCycle;
    }
};

//--------------------------------------------------------------------------------------------------------------

// 🔹 Key Takeaways
// Why use dist[node] + dist[neighbor] + 1?

// It correctly computes the length of the detected cycle.
// Why use min()?

// To ensure we store the shortest cycle encountered.
// Why does this work?

// Since BFS explores level by level, it ensures we find the shortest cycle first.

// 🔹 What Are dist[node] and dist[neighbor]?
// dist[node] → Distance of node from the starting node of BFS.
// dist[neighbor] → Distance of neighbor from the starting node of BFS.
// +1 → The edge between node and neighbor is part of the cycle.

//    0 —— 1
//    |    |
//    3 —— 2

// start node = 0
// Cycle length = dist[3] + dist[2] + 1 = 1 + 2 + 1 = 4