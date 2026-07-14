// The diameter of a tree is the length (number of edges or nodes) of the longest path between any two nodes.

// There are several approaches to find the diameter. Below are the most common methods with C++ code and complexity.

// ----------------------------------------------------------------------------------------------------------------------

// # 1. Brute Force (Run DFS/BFS from Every Node)

// ### Idea

// * Start DFS/BFS from every node.
// * Find the farthest node from each.
// * Maximum distance obtained is the diameter.

// ### C++ (DFS)


#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj;
int maxDist;

void dfs(int node, int parent, int dist) {
    maxDist = max(maxDist, dist);

    for (int child : adj[node]) {
        if (child != parent)
            dfs(child, node, dist + 1);
    }
}

int diameter(int n) {
    int ans = 0;

    for (int i = 0; i < n; i++) {
        maxDist = 0;
        dfs(i, -1, 0);
        ans = max(ans, maxDist);
    }

    return ans;
}

int main() {
    int n = 5;
    adj.resize(n);

    adj[0].push_back(1);
    adj[1].push_back(0);

    adj[1].push_back(2);
    adj[2].push_back(1);

    adj[1].push_back(3);
    adj[3].push_back(1);

    adj[3].push_back(4);
    adj[4].push_back(3);

    cout << diameter(n);
}


// ### Complexity

// * Time: O(N²)
// * Space: O(N) (DFS recursion)

----------------------------------------------------------------------------------------------------------------------

// # 2. Two DFS (Most Popular)

// ### Idea

// Step 1:

// * Run DFS from any node (say 0).
// * Find the farthest node A.

// Step 2:

// * Run DFS from A.
// * The farthest node from A gives the diameter.

// ### Why it works?

// One endpoint of the diameter is always the farthest node from any arbitrary node.

// ### C++


#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj;
int farthestNode, maxDist;

void dfs(int node, int parent, int dist) {
    if (dist > maxDist) {
        maxDist = dist;
        farthestNode = node;
    }

    for (int child : adj[node]) {
        if (child != parent)
            dfs(child, node, dist + 1);
    }
}

int diameter(int n) {

    maxDist = -1;
    dfs(0, -1, 0);

    int start = farthestNode;

    maxDist = -1;
    dfs(start, -1, 0);

    return maxDist;
}

int main() {

    int n = 5;
    adj.resize(n);

    adj[0].push_back(1);
    adj[1].push_back(0);

    adj[1].push_back(2);
    adj[2].push_back(1);

    adj[1].push_back(3);
    adj[3].push_back(1);

    adj[3].push_back(4);
    adj[4].push_back(3);

    cout << diameter(n);
}


// ### Complexity

// * Time: O(N)
// * Space: O(N)

----------------------------------------------------------------------------------------------------------------------

// # 3. Two BFS (For Unweighted Tree)

// Same logic as Two DFS.

// Instead of DFS, use BFS twice.

// ### C++


#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj;

pair<int,int> bfs(int src, int n) {

    vector<int> dist(n, -1);
    queue<int> q;

    q.push(src);
    dist[src] = 0;

    int far = src;

    while (!q.empty()) {

        int node = q.front();
        q.pop();

        for (int child : adj[node]) {

            if (dist[child] == -1) {
                dist[child] = dist[node] + 1;
                q.push(child);

                if (dist[child] > dist[far])
                    far = child;
            }
        }
    }

    return {far, dist[far]};
}

int main() {

    int n = 5;
    adj.resize(n);

    adj[0].push_back(1);
    adj[1].push_back(0);

    adj[1].push_back(2);
    adj[2].push_back(1);

    adj[1].push_back(3);
    adj[3].push_back(1);

    adj[3].push_back(4);
    adj[4].push_back(3);

    auto x = bfs(0, n);
    auto y = bfs(x.first, n);

    cout << y.second;
}


// ### Complexity

// * Time: O(N)
// * Space: O(N)

----------------------------------------------------------------------------------------------------------------------

// # 4. Tree DP (Single DFS)

// This is the standard interview approach.

// ### Idea

// For every node:

// * Compute the height of each child.
// * The diameter passing through the node is:

  
//   tallest_child + second_tallest_child
  
// * Update the global answer.

// ### C++


#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj;
int diameter = 0;

int dfs(int node, int parent) {

    int mx1 = 0;
    int mx2 = 0;

    for (int child : adj[node]) {

        if (child == parent)
            continue;

        int h = dfs(child, node) + 1;

        if (h > mx1) {
            mx2 = mx1;
            mx1 = h;
        }
        else if (h > mx2) {
            mx2 = h;
        }
    }

    diameter = max(diameter, mx1 + mx2);

    return mx1;
}

int main() {

    int n = 5;
    adj.resize(n);

    adj[0].push_back(1);
    adj[1].push_back(0);

    adj[1].push_back(2);
    adj[2].push_back(1);

    adj[1].push_back(3);
    adj[3].push_back(1);

    adj[3].push_back(4);
    adj[4].push_back(3);

    dfs(0, -1);

    cout << diameter;
}


// ### Complexity

// * Time: O(N)
// * Space: O(N)

----------------------------------------------------------------------------------------------------------------------

// # 5. DP on Binary Tree (LeetCode 543)

// For a binary tree, compute the height recursively.

// At every node:

// text
// leftHeight + rightHeight
// 

// is the longest path through that node.

// ### C++


class Solution {
public:
    int ans = 0;

    int height(TreeNode* root) {

        if (!root)
            return 0;

        int left = height(root->left);
        int right = height(root->right);

        ans = max(ans, left + right);

        return 1 + max(left, right);
    }

    int diameterOfBinaryTree(TreeNode* root) {

        height(root);

        return ans;
    }
};


// ### Complexity

// * Time: O(N)
// * Space: O(H), where H is the height of the tree (recursion stack).

// ----------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------

// # Comparison

// | Method                  | Time      | Space | Best Use                                       |
// | ----------------------- | --------- | ----- | ---------------------------------------------- |
// | DFS/BFS from every node | O(N²) | O(N)  | Small trees, brute force                       |
// | Two DFS                 | O(N)  | O(N)  | General trees, most common interview solution  |
// | Two BFS                 | O(N)  | O(N)  | Unweighted trees                               |
// | Tree DP (single DFS)    | O(N)  | O(N)  | Competitive programming, rerooting/DP problems |
// | Binary Tree DP          | O(N)  | O(H)  | Binary tree questions (e.g., LeetCode 543)     |

// ### Which method should you use?

// * General tree (adjacency list): Two DFS or Two BFS are the simplest and most widely used.
// * Need a single traversal or solving tree DP problems: Use the Tree DP approach.
// * Binary tree: Use the recursive height-based DP solution.
