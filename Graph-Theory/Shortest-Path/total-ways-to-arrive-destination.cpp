// You are in a city that consists of n intersections numbered from 0 to n - 1 with bi-directional roads between some intersections.
// given roads and time to reach the nodes --> [u, v, time]
// find no. of ways you can travel from intersection 0 to intersection n - 1 in the shortest amount of time.
// Return the number of ways you can arrive at your destination in the shortest amount of time. Since the answer may be large, return it modulo 109 + 7.

// Let N be the number of nodes in the graph and E be the number of edges in the given road connections.
// Time complexity: O((N+E)logN)'
// Space complexity: O(N+E)
// the total space used is dominated by O(N+E) for storing the graph, the overall space complexity is O(N+E).

class Solution {
public:
    int countPaths(int n, vector<vector<int>>& roads) {
        
        // since we need to find the shortest amount of time from 
        // source to destination node
        // use Dijkstra's algorithm
        // as we need to find the no. of ways
        // along with distance array we also use a ways array for all nodes
        
        // initially the no. of ways of reaching all nodes will be 0
        // only source will be initialized as 1 when we start finding path
        // now if u find the shortest time then update the distance of 
        // neighbor with the distance of node
        // ways[neighbor] = ways[node]
        // if u find the same time then add the time of node to that of neighbor
        // ways[neighbor] += ways[node]

        // build weighted graph 
        // node -> {node, weight} ==> u --> {v, weight}
        vector<vector<pair<int, int>>> graph(n);

        for(auto& road: roads) {

            int u = road[0];
            int v = road[1];
            int weight = road[2];

            graph[u].push_back({v, weight});
            graph[v].push_back({u, weight});
        }

        // dijkstra's algorithm
        // all distances are unreachable from the start
        // since time can a very big number use long long 
        // initiaize ways with 0 as all nodes are unreachable initially
        // only initialize source node with ways = 1
        // use minHeap for keeping min weights in the heap
        // of pair - dist, node
        int MOD = 1e9 + 7;
        vector<long long> dist(n, LLONG_MAX);
        vector<long long> ways(n, 1);
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> minHeap;

        minHeap.push({0, 0});
        dist[0] = 0;
        ways[0] = 1;

        while(!minHeap.empty()) {

            auto [d, node] = minHeap.top();
            minHeap.pop();

            if(d > dist[node]) continue; // can not be minimized

            for(auto &[neighbor, weight]: graph[node]) {

                long long newDist = dist[node] + weight;

                // shortest distance found
                if(newDist < dist[neighbor]) {
                    dist[neighbor] = newDist;
                    ways[neighbor] = ways[node];
                    minHeap.push({newDist, neighbor});
                }
                // another path found - update no. of ways
                // as shortest dist would have already been minimized
                else if(newDist == dist[neighbor]) {
                    ways[neighbor] = (ways[neighbor] + ways[node]) % MOD;
                }
            }
        }

        return ways[n - 1];
    }
};