// Single Source Shortest Path (SSSP) for an Unweighted Graph

// 🔹 Approach
// For unweighted graphs, the shortest path from a single source node can be found using Breadth-First Search (BFS)
// BFS explores all neighbors level by level, ensuring the shortest path is found first.

// 🔹 Algorithm (Using BFS)
// Initialize a distance array with -1 (or INF) for all nodes.
// Use a queue to perform BFS starting from start node.
// Process each node, updating the shortest distance for its neighbors if not visited before.
// Continue BFS until all reachable nodes are visited.

// bfs as it traverse all connected edges at once 
// bfs will always result into shortest path

// instead of using a visited array use distance array 
// if distance for a node is -1 that means it is not visited yet
// return a distance array denoting the shortest distance of all nodes from start node 

// 🔹 Related LeetCode Problems
// LeetCode 542 - 01 Matrix (BFS for shortest distance)
// LeetCode 994 - Rotting Oranges (Multi-source BFS)
// LeetCode 1376 - Time Needed to Inform All Employees (SSSP using BFS)
// LeetCode 815 - Bus Routes (BFS in graphs)
// LeetCode 1926 - Nearest Exit in Maze (BFS for shortest path)

// Time Complexity: O(N + E) : BFS visits each node once and each edge once.
// Space Complexity: O(N + E)
// O(N + E) for adjacency list.
// O(N) for distance array.
// O(N) for BFS queue (in the worst case).

// ---------------------------------------------------------------------------------------------------
vector<int> distance(n, -1);  // Initialize distances with -1 (unreachable)
bfs(start, graph, distance);

void bfs(int start, vector<vector<int>> &graph, vector<int> &distance) {

    queue<int> q;
    q.push(start);
    distance[start] = 0;  // Distance of start node from itself is 0

    while (!q.empty()) {

        int node = q.front();
        q.pop();

        for (int neighbor : graph[node]) {

            if (distance[neighbor] == -1) {  // If not visited
                distance[neighbor] = distance[node] + 1;
                q.push(neighbor);
            }
        }
    }
}

//-----------------------------------------------------------------------------------------------------

// bfs using visited array 
void bfs(int start, vector<vector<int>> &graph, vector<bool> &visited, vector<int> &distance) {

    queue<int> q;
    q.push(start);
    distance[start] = 0;  // Distance of start node from itself is 0
	visited[start] = true; // mark start node as visited

    while (!q.empty()) {

        int node = q.front();
        q.pop();

        for (int neighbor : graph[node]) {

            if (!visted[neighbor]) {  // If not visited
                distance[neighbor] = distance[node] + 1;
				visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
}

//-----------------------------------------------------------------------------------------------------

int main() {
    int n = 6;  // Number of nodes
    vector<vector<int>> graph(n);

    // Undirected graph edges
    graph[0] = {1, 2};
    graph[1] = {0, 3, 4};
    graph[2] = {0, 5};
    graph[3] = {1};
    graph[4] = {1};
    graph[5] = {2};

    vector<int> distance(n, -1);  // Initialize distances with -1 (unreachable)
    
    int start = 0;  // Start node
    bfs(start, graph, distance);

    // Print shortest distances from start node
    for (int i = 0; i < n; i++) {
        cout << "Shortest path from " << start << " to " << i << " is: " << distance[i] << endl;
    }

    return 0;
}


// ---------------------------------------------------------------------------------------------------


