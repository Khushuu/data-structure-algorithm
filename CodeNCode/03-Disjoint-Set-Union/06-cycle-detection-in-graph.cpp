// cycle detection in undirected graph using disjoint set union

// if u r trying to connect two edges that already have the same parent
// i.e they are already part of the same connected component
// that means introduction of this edge will create a cycle in the connected component

// --------------------------------------------------------------------------------------------------

vector<int> parent, size; 

void makeSet(int n) {
    parent.resize(n);
    size.resize(n, 1);
    for (int i = 0; i < n; i++) parent[i] = i;
}

int find(int x) {
    if (parent[x] == x) return x; 
    return parent[x] = find(parent[x]); // Path Compression
}

void unionSet(int x, int y) {

    int rootX = find(x);
    int rootY = find(y);

    if (rootX == rootY) return; // Already in the same set

    if (size[rootX] > size[rootY]) {
        parent[rootY] = rootX;
        size[rootX] += size[rootY];
    } else {
        parent[rootX] = rootY;
        size[rootY] += size[rootX];
    }
    
}

bool hasCycle(int n, vector<pair<int, int>>& edges) {

    makeSet(n);

    for (auto& edge : edges) {

        int u = edge.first
		int v = edge.second;

        if (find(u) == find(v)) return true; // Cycle detected'

        unionSet(u, v);
    }

    return false;
}

// --------------------------------------------------------------------------------------------------

// BETTER APPROACH
// Reducing the number of find calls from 4 to 2 for each edge

// You're currently calling `find()` twice in `hasCycle()` and then again twice inside `unionSet()` for every edge that doesn't form a cycle.

// ### Current version

// For a non-cycle edge:

// if (find(u) == find(v))   // 2 find() calls
//     return true;

// unionSet(u, v);           // 2 more find() calls

// **Total: 4 `find()` calls per edge.**

// --------------------------------------------------------------------------------------------------

// ## Optimized version

// Modify `unionSet()` to return whether a union was performed.

bool unionSet(int x, int y) {

    int rootX = find(x);
    int rootY = find(y);

    if (rootX == rootY)
        return false;      // Already in the same set

    if (size[rootX] < size[rootY])
        swap(rootX, rootY);

    parent[rootY] = rootX;
    size[rootX] += size[rootY];

    return true;
}

// Notice that using `swap()` removes the duplicated code.
// Then `hasCycle()` becomes:


bool hasCycle(int n, vector<pair<int, int>>& edges) {

    makeSet(n);

    for (auto& edge : edges) {
        int u = edge.first;
        int v = edge.second;

        // if both u and v have the same root, it means they are already connected
        // so adding this edge will create a cycle
        if (!unionSet(u, v))
            return true;   // Cycle detected
    }

    return false;
}

// --------------------------------------------------------------------------------------------------

// ### Why this is better

// * Only **2 `find()` calls** per edge instead of 4.
// * No duplicate connectivity check.
// * `unionSet()` encapsulates all DSU logic.
// * Shorter and easier to maintain.

// This is the idiomatic way DSU is written in competitive programming and interviews. A common pattern is:

// if (!unionSet(u, v))
//     // u and v were already connected


// where the caller decides what "already connected" means (e.g., decrement nothing, report a cycle, etc.).
