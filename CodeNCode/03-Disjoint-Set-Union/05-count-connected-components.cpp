// counting connected components in graph using disjoint set 

// --------------------------------------------------------------------------------------------

// Each node is its own parent initially, and the size of each component is 1.
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

    if(rootX == rootY) return; // Already in the same set

    if (size[rootX] > size[rootY]) {
        parent[rootY] = rootX;
        size[rootX] += size[rootY];
    } else {
        parent[rootX] = rootY;
        size[rootY] += size[rootX];
    }
}

int countComponents(int n, vector<pair<int, int>>& edges) {

    makeSet(n);
    int components = n;

    for (auto& edge : edges) {

        int u = edge.first;
        int v = edge.second;

        // If u and v are in different components, union them and decrease the component count
        // as two different nodes will get merged to 1 the count of connected components will reduce by 1
        // if u and v are in the same component, no need to union them

        // this check is needed so that we don't decrement the component count unnecessarily - 
        // in case u and v are already in the same component

        if(find(u) == find(v)) continue; // already in the same component

        unionSet(u, v);
        components--;
    }

    return components;
}

// --------------------------------------------------------------------------------------------

// BETTER APPROACH
// Reducing the number of find calls

// the union method will return a boolean value indicating whether a union was performed or not
// in case a union was not performed, it means the nodes are already in the same component
// so we don't need to decrement the component count

// else we will decrement the component count as two different nodes will get merged 
// to 1 the count of connected components will reduce by 1


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

bool unionSet(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);

    if (rootX == rootY)
        return false;

    if (size[rootX] > size[rootY]) {
        parent[rootY] = rootX;
        size[rootX] += size[rootY];
    } else {
        parent[rootX] = rootY;
        size[rootY] += size[rootX];
    }

    return true;
}

int countComponents(int n, vector<pair<int, int>>& edges) {

    makeSet(n);
    int components = n;

    // union all edges
    for (auto& edge : edges) {

        // only in case a successful union is performed, we will decrement the component count
        if (unionSet(edge.first, edge.second))
            components--;
    }
    
    return components;
}