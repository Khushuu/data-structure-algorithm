// couting connected components in graph using disjoint set 

// --------------------------------------------------------------------------------------------

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

int countComponents(int n, vector<pair<int, int>>& edges) {

    makeSet(n);
    int components = n;

    for (auto& edge : edges) {

        int u = edge.first, v = edge.second;
        if (find(u) != find(v)) {
            unionSet(u, v);
            components--;
        }
    }

    return components;
}

// --------------------------------------------------------------------------------------------
