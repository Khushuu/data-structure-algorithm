// 2️⃣ Using DFS (Recursive) 
// Acyclic graph
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

// Cyclic graph
// DFS-Based Approach
// If a node is visited again in the same recursion stack, it means there is a back edge, indicating a cycle.
// Solution: Maintain a recursion stack (inStack[]) to detect cycles.

// ✅ Uses an inStack[] array to Detect Back Edges (Cycle Detection)
// ✅ Returns false if a Cycle Exists, Otherwise Returns the Topological Order

//--------------------------------------------------------------------------------------------------------------

bool dfs(int node, vector<vector<int>> &graph, vector<bool> &visited, vector<bool> &inStack, stack<int> &st) {

    visited[node] = true;
    inStack[node] = true;  // Mark node as in current DFS path

    for (int neighbor : graph[node]) {

        if (!visited[neighbor]) {
            if (!dfs(neighbor, graph, visited, inStack, st)) {
                return false;  // Cycle found
            }
        } else if (inStack[neighbor]) {
            return false;  // Cycle detected
        }
    }

    inStack[node] = false;  // Remove from recursion stack
    st.push(node);  // Push only if it's part of a DAG
    return true;
}

vector<int> topologicalSort(int n, vector<vector<int>> &graph) {

    vector<bool> visited(n, false);
    vector<bool> inStack(n, false); // Track nodes in recursion stack
    stack<int> st;
    vector<int> result;

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            if (!dfs(i, graph, visited, inStack, st)) {
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
