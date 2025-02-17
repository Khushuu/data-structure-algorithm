// We have n queries where we need to determine if a given node u lies in the subtree of another node v in a tree.

// If a DFS traversal order is maintained, we can keep track of:

// Entry Time (in[u]) → When node u is first visited.
// Exit Time (out[u]) → When node u is completely processed (all its descendants are visited).

// Subtree Condition:
// If node u is in the subtree of node v, then:
// in[u] > in[v] && out[u] < out[v]
// This means u is visited after v starts and before v finishes.

// -----------------------------------------------------------------------------------------------------

class Tree {
private:
    vector<vector<int>> adj;
    vector<int> in, out;
    int timer = 0;

    void dfs(int node, int parent) {

        in[node] = timer++; // Mark entry time

        for (int child : adj[node]) {
            if (child != parent) {
                dfs(child, node);
            }
        }

        out[node] = timer++ ; // Mark exit time
    }

public:
    Tree(int n) {
        adj.resize(n + 1);
        in.resize(n + 1);
        out.resize(n + 1);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u); // Since it's an undirected tree
    }

    void preprocess(int root) {
        dfs(root, -1);
    }

	// u is subtree of v 
    bool isSubtree(int u, int v) {
        return in[u] > in[v] && out[u] < out[v];
    }
};

int main() {
    int n = 7; // Number of nodes
    Tree tree(n);

    // Adding edges (forming a tree)
    tree.addEdge(1, 2);
    tree.addEdge(1, 3);
    tree.addEdge(2, 4);
    tree.addEdge(2, 5);
    tree.addEdge(3, 6);
    tree.addEdge(3, 7);

    // Preprocess to calculate entry and exit times
    tree.preprocess(1); // Assume node 1 as root

    // Queries
    vector<pair<int, int>> queries = {{4, 2}, {6, 3}, {5, 1}, {7, 2}};

    cout << "Results of queries:\n";
    for (auto [u, v] : queries) {
        cout << "Is " << u << " in subtree of " << v << "? "
             << (tree.isSubtree(u, v) ? "Yes" : "No") << endl;
    }

    return 0;
}


// -----------------------------------------------------------------------------------------------------