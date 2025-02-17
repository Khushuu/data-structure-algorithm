// 🔹 Topological Sorting in a Directed Acyclic Graph (DAG)
// Topological sorting of a Directed Acyclic Graph (DAG) 
// is a linear ordering of vertices such that for every directed edge (u → v), 
// vertex u appears before vertex v in the ordering.

// 🔹 Applications:

// Task scheduling (e.g., course prerequisites)
// Dependency resolution (e.g., package installations)
// Compiler optimizations (e.g., instruction ordering)

// 🔹 Related LeetCode Problems
// LeetCode 207 - Course Schedule 🏫 (Check if a DAG is valid)
// LeetCode 210 - Course Schedule II 🏫 (Find a valid topological order)
// LeetCode 329 - Longest Increasing Path in a Matrix 📈 (DAG + Topological Sort)
// LeetCode 1462 - Course Schedule IV 🏫 (Reachability in a DAG)
// LeetCode 1203 - Sort Items by Groups Respecting Dependencies 🔄 (Topological Sort with constraints)

// 🔹 Methods to Find Topological Sorting
// Kahn's algorithm - BFS - Use this cleaner and better 
// DFS

// NOTE: if the problem asked for lexicographically smallest topological order instead of any valid order
// use minHeap - priority_queue<int, vector<int>, greater<int>> q -> instead of queue -
// rest of the implementation stays the same

// 1️⃣ Using Kahn's Algorithm (BFS-based)

// Maintain in-degree (number of incoming edges) for each node.
// when creating the graph - update the indegree of each node 
// if a node is directed from u->v then inDegree[v]++
// in kahn's algorithm declare a queue and insert all nodes with inDegree of 0
// these nodes have no dependency and can be processed
// until the queue is not empty pop from the front of the queue
// decrement the inDegree of the neighbor node 
// and if inDegree of neighbor node becomes 0 --> insert it into queue

// don't need to separately handle connected components as each component will have a node with indegree = 0
// for all connected components - as it is directed acyclic graph
// we loop over all nodes and already fill the queue with nodes having indegree = 0
// so from each component a node will definitely be added with indegree = 0 which will process all its neighbors

// ✅ Time Complexity: O(n + E)
// ✅ Space Complexity: O(n + E) (for adjacency list + queue)

// ------------------------------------------------------------------------------------------------------------

vector<int> topologicalSort(int n, vector<vector<int>> &graph) {

    vector<int> inDegree(n, 0);
    queue<int> q;
    vector<int> result;

    // Compute in-degree of each node
    for (int i = 0; i < n; i++) {
        for (int neighbor : graph[i]) {
            inDegree[neighbor]++;
        }
    }

    // Push nodes with in-degree 0
    for (int i = 0; i < n; i++) {
        if (inDegree[i] == 0) {
            q.push(i);
        }
    }

    while (!q.empty()) {

        int node = q.front();
        q.pop();
        result.push_back(node);

        // Reduce in-degree of neighbors
        for (int neighbor : graph[node]) {
            inDegree[neighbor]--;
            if (inDegree[neighbor] == 0) {
                q.push(neighbor);
            }
        }
    }

	// if cycle exists 
	// If all nodes are not processed, there is a cycle
    // if (result.size() != n) {
    //     cout << "Cycle detected! Topological sorting is not possible." << endl;
    //     return {};  // Return empty if a cycle is detected
    // }

    return result; 
}

int main() {
    int n = 6;
    vector<vector<int>> graph(n);

    graph[5].push_back(2);
    graph[5].push_back(0);
    graph[4].push_back(0);
    graph[4].push_back(1);
    graph[2].push_back(3);
    graph[3].push_back(1);

    vector<int> result = topologicalSort(n, graph);

    for (int node : result) {
        cout << node << " ";
    }
    return 0;
}

// ------------------------------------------------------------------------------------------------------------

// 2️⃣ Using DFS (Recursive)
// Use DFS and push nodes onto a stack after all their neighbors have been visited.
// the node which is dependent on others will be pushed first and then the calling parent
// Reverse the stack to get the topological order.

// ✅ Time Complexity: O(n + E)
// ✅ Space Complexity: O(n + E) (for adjacency list + recursion stack)

//--------------------------------------------------------------------------------------------------------------

void dfs(int node, vector<vector<int>> &graph, vector<bool> &visited, stack<int> &st) {

    visited[node] = true;

    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            dfs(neighbor, graph, visited, st);
        }
    }

    st.push(node);  // Push the node after visiting all neighbors
}

vector<int> topologicalSort(int n, vector<vector<int>> &graph) {

    vector<bool> visited(n, false);
    stack<int> st;
    vector<int> result;

	// all connected components have to be handled
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(i, graph, visited, st);
        }
    }

    while (!st.empty()) {
        result.push_back(st.top());
        st.pop();
    }

    return result;
}

int main() {
    int n = 6;
    vector<vector<int>> graph(n);

    graph[5].push_back(2);
    graph[5].push_back(0);
    graph[4].push_back(0);
    graph[4].push_back(1);
    graph[2].push_back(3);
    graph[3].push_back(1);

    vector<int> result = topologicalSort(n, graph);

    for (int node : result) {
        cout << node << " ";
    }
    return 0;
}
//--------------------------------------------------------------------------------------------------------------

// NOTE: 
// If the graph contains a cycle, topological sorting is not possible
// because at least one node will have an unresolved dependency 
// (i.e., there will be no valid ordering of nodes where all prerequisites are satisfied).

// NOTE:
// in case of cycle - all nodes in cycle will have indegree > 1
// no node will have indegree = 0
// hence none of the nodes which are part of the cycle will be inserted in the queue
// that's y comparing the size of the result with the no. of nodes --> determines if the cycle is there or not
// if cycle is present size of result will always be < no. of nodes 

// 🔹 Changes in Both Methods to Handle Cycles
// If the graph is not a DAG (Directed Acyclic Graph):

// Kahn’s Algorithm (BFS)
// If there is a cycle, some nodes will never have their in-degree reduced to 0,
// and the queue will not process all nodes.
// The number of nodes processed will be less than the total number of nodes n.
// Solution: At the end, check if the topological order has n nodes. If not, there is a cycle.

// ✅ Detects Cycles by Checking the Processed Node Count
// ✅ Returns an Empty Array If a Cycle Exists
//--------------------------------------------------------------------------------------------------------------

vector<int> topologicalSort(int n, vector<vector<int>> &graph) {

    vector<int> inDegree(n, 0), result;
    queue<int> q;

    // Compute in-degree of each node
    for (int i = 0; i < n; i++) {
        for (int neighbor : graph[i]) {
            inDegree[neighbor]++;
        }
    }

    // Push nodes with in-degree 0
    for (int i = 0; i < n; i++) {
        if (inDegree[i] == 0) {
            q.push(i);
        }
    }

    while (!q.empty()) {

        int node = q.front();
        q.pop();
        result.push_back(node);

        for (int neighbor : graph[node]) {
            inDegree[neighbor]--;
            if (inDegree[neighbor] == 0) {
                q.push(neighbor);
            }
        }
    }

    // If all nodes are not processed, there is a cycle
    if (result.size() != n) {
        cout << "Cycle detected! Topological sorting is not possible." << endl;
        return {};  // Return empty if a cycle is detected
    }

    return result;
}
//--------------------------------------------------------------------------------------------------------------

// DFS-Based Approach
// If a node is visited again in the same recursion stack, it means there is a back edge, indicating a cycle.
// Solution: Maintain a recursion stack (onStack[]) to detect cycles.

// ✅ Uses an onStack[] array to Detect Back Edges (Cycle Detection)
// ✅ Returns false if a Cycle Exists, Otherwise Returns the Topological Order

//--------------------------------------------------------------------------------------------------------------

bool dfs(int node, vector<vector<int>> &graph, vector<bool> &visited, vector<bool> &onStack, stack<int> &st) {

    visited[node] = true;
    onStack[node] = true;  // Mark node as in current DFS path

    for (int neighbor : graph[node]) {

        if (!visited[neighbor]) {
            if (!dfs(neighbor, graph, visited, onStack, st)) {
                return false;  // Cycle found
            }
        } else if (onStack[neighbor]) {
            return false;  // Cycle detected
        }
    }

    onStack[node] = false;  // Remove from recursion stack
    st.push(node);  // Push only if it's part of a DAG
    return true;
}

vector<int> topologicalSort(int n, vector<vector<int>> &graph) {

    vector<bool> visited(n, false);
    vector<bool> onStack(n, false); // Track nodes in recursion stack
    stack<int> st;
    vector<int> result;

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            if (!dfs(i, graph, visited, onStack, st)) {
                cout << "Cycle detected! Topological sorting is not possible." << endl;
                return {};  // Return empty if a cycle is detected
            }
        }
    }

    while (!st.empty()) {
        result.push_back(st.top());
        st.pop();
    }

    return result;
}

//--------------------------------------------------------------------------------------------------------------
