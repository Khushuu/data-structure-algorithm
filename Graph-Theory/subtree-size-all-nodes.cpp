// Finding the Subtree Size of All Nodes in a Graph (C++)

// The subtree size of a node is the number of nodes in its subtree, including itself. 
// This can be computed efficiently using DFS (Depth First Search).

// Approach
// Use DFS to traverse the tree from the root node.
// For each node u, sum up the subtree sizes of its children.
// Store the result in an array subtree_size[u].
// Return subtree_size[u] + 1 (including the node itself).

// related problems 
// These problems involve subtree calculations, often requiring DFS:

// LeetCode 1519 - Number of Nodes in the Subtree With the Same Label
// LeetCode 1448 - Count Good Nodes in Binary Tree
// LeetCode 1372 - Longest ZigZag Path in a Binary Tree
// LeetCode 834 - Sum of Distances in Tree
// LeetCode 310 - Minimum Height Trees

// Time Complexity: O(N): Each node is visited once, and all its edges are processed once.
// Space Complexity: O(N)
//---------------------------------------------------------------------------------------------------------
vector<int> subtree_size(n, 0)
dfs(0, -1, tree, subtree_size)

void dfs(int node, int parent, vector<vector<int>> &tree, vector<int> &subtree_size) {

    subtree_size[node] = 1;  // Count the node itself

    for (int child : tree[node]) {

        if (child == parent) continue;  // Avoid visiting parent again

        dfs(child, node, tree, subtree_size);

        subtree_size[node] += subtree_size[child];  // Add child's subtree size
    }
}

int main() {
    int n = 7;  // Number of nodes
    vector<vector<int>> tree(n);

    // Undirected Tree Edges
    tree[0] = {1, 2};
    tree[1] = {0, 3, 4};
    tree[2] = {0, 5, 6};
    tree[3] = {1};
    tree[4] = {1};
    tree[5] = {2};
    tree[6] = {2};

    vector<int> subtree_size(n, 0);
    
    dfs(0, -1, tree, subtree_size);  // Assuming 0 as the root node

    // Print subtree sizes
    for (int i = 0; i < n; i++) {
        cout << "Subtree size of node " << i << ": " << subtree_size[i] << endl;
    }

    return 0;
}

//---------------------------------------------------------------------------------------------------------

