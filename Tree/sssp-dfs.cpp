// single source shortest path for a tree using dfs
// dfs can't be used to find sssp in graph as it moves depth first 
// this can only be used in a tree

// we don't need to maintain a visited array here 
// because tree doesn't have cycles
// just ensure that the child does not call the parent

// Time Complexity: O(N): all nodes of tree are traversed
//  Space Complexity: O(N): recursion stack
//-------------------------------------------------------------------------------------------------------------

void dfs(int node, int parent, int dist, vector<vector<int>> &tree, vector<int> &distance) {

	distance[node] = dist;

    for (int child : tree[node]) {

        if (child != parent) {  // Avoid revisiting the parent

            dfs(child, node, dist + 1, tree, distance);
        }
    }
}

int main() {
    int n = 6;  // Number of nodes in tree
    vector<vector<int>> tree(n);

    // Tree edges (undirected)
    tree[0] = {1, 2};
    tree[1] = {0, 3, 4};
    tree[2] = {0, 5};
    tree[3] = {1};
    tree[4] = {1};
    tree[5] = {2};

    vector<int> distance(n, 0);
    dfs(0, -1, 0, tree, distance);  // Start DFS from root node 0

    // Print shortest distances from root (node 0)
    for (int i = 0; i < n; i++) {
        cout << "Shortest path from 0 to " << i << " is: " << distance[i] << endl;
    }

    return 0;
}

//-------------------------------------------------------------------------------------------------------------