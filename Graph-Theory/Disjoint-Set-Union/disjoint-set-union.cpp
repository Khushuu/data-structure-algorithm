// The Disjoint Set (also called Union-Find)
// is a data structure that efficiently handles operations related to partitioning elements into disjoint (non-overlapping) sets.
// It is widely used in graph algorithms like Kruskal’s Algorithm, cycle detection, and connected components.

// 1. Key Concepts

// Find(x): Returns the representative (root) of the set that x belongs to.
// Union(x, y): Merges the sets containing x and y.

// 2. Optimized Operations

// Path Compression (for Find): 
// Flattens the structure by making every node directly point to the root.

// Union by Rank (for Union): 
// Attaches the smaller tree under the larger tree to keep the depth small.

// Basic Implementation (Without Optimizations)
// find(x): O(N) (in the worst case, we might traverse the entire chain).
// unionSet(x, y): O(N) (as we find the root of each element).
// ------------------------------------------------------------------------------------------------

vector<int> parent, rank; 

void makeSet(int n) {
    parent.resize(n);
    for (int i = 0; i < n; i++) parent[i] = i;
}

int find(int x) {
    if (parent[x] == x) return x; // Root node
    return find(parent[x]); // Recursively find root
}

void unionSet(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY) parent[rootX] = rootY; // Merge sets
}

// ------------------------------------------------------------------------------------------------

// 3. Optimized Implementation (Using Path Compression and Union by Rank)

// To speed up operations, we introduce:
// Path Compression: Makes find() very fast by pointing nodes directly to the root.
// Union by Rank: Keeps the tree balanced by attaching the smaller tree under the larger tree.

// 🔥 Optimized DSU (Path Compression & Union by Rank)

// Path Compression (Find Optimization)
// Instead of following parent links one by one, we make nodes directly point to the root.
// Time Complexity: O(α(N)) (almost constant time).

// Union by Rank (Union Optimization)
// Always attach the smaller tree under the larger tree to keep tree shallow.
// Time Complexity: O(α(N)).

// 🔹 Time Complexity
// Find(x): O(α(N)), where α(N) (inverse Ackermann function) is nearly constant.
// Union(x, y): O(α(N)).
// Overall DSU operations: O(N α(N)) ≈ O(N) in practice.
// ------------------------------------------------------------------------------------------------

vector<int> parent, rank; 

void makeSet(int n) {
    parent.resize(n);
    rank.resize(n, 0);
    for (int i = 0; i < n; i++) parent[i] = i;
}

int find(int x) {
    if (parent[x] == x) return parent[x];
    return parent[x] = find(parent[x]); // Path Compression
}

// union by rank
void unionSet(int x, int y) {

    int rootX = find(x);
    int rootY = find(y);

    if (rootX != rootY) {
        if (rank[rootX] > rank[rootY]) 
            parent[rootY] = rootX;
        else if (rank[rootX] < rank[rootY]) 
            parent[rootX] = rootY;
        else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
}

// ------------------------------------------------------------------------------------------------

// Application					Explanation
// Kruskal’s Algorithm			Finds the Minimum Spanning Tree (MST) by checking for cycles efficiently.
// Cycle Detection in Graphs	Checks if adding an edge creates a cycle in an undirected graph.
// Connected Components			Groups nodes into connected components efficiently.
// Dynamic Connectivity			Used in network connectivity and percolation problems.
// Merging Friend Groups		Helps solve problems like friend circles (e.g., Facebook mutual friends).

// ------------------------------------------------------------------------------------------------

// 🔥 More Efficient Implementation (Using Union by Size)
// Instead of rank, we can use size to merge smaller trees under larger ones.

// 🔹 Advantages of Union by Size
// Merging smaller trees into larger ones prevents unnecessary height growth.
// Works similarly to union by rank but is often simpler.

// ------------------------------------------------------------------------------------------------

vector<int> parent, size; 

void makeSet(int n) {
    parent.resize(n);
    size.resize(n, 1);
    for (int i = 0; i < n; i++) parent[i] = i;
}

int find(int x) {

    if (parent[x] == x) return parent[x]; 
	return parent[x] = find(parent[x]); // Path Compression
}

void unionSet(int x, int y) {

    int rootX = find(x);
    int rootY = find(y);
	
    if (rootX != rootY) {
        if (size[rootX] > size[rootY]) {
            parent[rootY] = rootX;
            size[rootX] += size[rootY];
        } else {
            parent[rootX] = rootY;
            size[rootY] += size[rootX];
        }
    }
}

// ------------------------------------------------------------------------------------------------


