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