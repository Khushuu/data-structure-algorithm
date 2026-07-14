// 2685. Count the Number of Complete Components

// given an undirected graph
// find the number of complete connected components in the graph

// A complete connected component is a connected component where all nodes are reachable from each other.

class DSU {
public:
    vector<int> parent;
    vector<int> size;

    DSU(int n) {

        parent.resize(n);
        size.resize(n, 1);
        iota(parent.begin(), parent.end(), 0); // sets parent[i] = i;   
    }

    int find(int a) {
        if(parent[a] == a) return a;
        return parent[a] = find(parent[a]); // path compression
    }

    void unite(int a, int b) {

        int rootA = find(a);
        int rootB = find(b);

        if(rootA == rootB) return;

        if(size[rootA] < size[rootB])
            swap(rootA, rootB);
        
        parent[rootB] = rootA;
        size[rootA] += size[rootB];
    }
};

class Solution {
public:
    int countCompleteComponents(int n, vector<vector<int>>& edges) {
        
        // DSU appraoch
        // join all the nodes that are connected
        // for each parent track how many edges are present 
        // and track what is the number of nodes in each component
        // if n is the number of nodes in a component 
        // then number of edges = n * (n - 1) / 2

        // all the components that satisfy this condition will form
        // complete connected component

        // no need to create graph
        // we can loop over the edges 
        DSU dsu(n);

        // connect the nodes
        for(vector<int>& edge: edges) {
            dsu.unite(edge[0], edge[1]);
        }

        // find the number of edges that belong to each component
        // for each parent of a component save the number of edges
        unordered_map<int, int> componentEdgeCount;

        for(vector<int>& edge: edges) {
            // since both nodes are connected - both will have same parent
            // we will update the edgecount after identifying parent of the node
            int root = dsu.find(edge[0]);
            componentEdgeCount[root]++;
        }

        int completeComponentCount = 0;
        // for each node check if it is the parent and is complete
        for(int node = 0; node < n; node++) {
            
            // if not a parent don't process
            if(node != dsu.find(node)) continue;

            int componentNodesCount = dsu.size[node];
            int expectedEdgeCount = 
                        (componentNodesCount * (componentNodesCount - 1)) / 2;
            
            if(expectedEdgeCount == componentEdgeCount[node])
                completeComponentCount++;
        }

        return completeComponentCount;
    }
};


// Complexity Analysis
// Let n be the number of vertices and m be the number of edges in the given graph.

// Time complexity: O(n+mα(n))

// The solution uses a Union-Find data structure with path compression and union by size. Building the Union-Find structure takes O(n) time for initialization. Processing all edges through union operations takes O(mα(n)) time, where α(n) is the inverse Ackermann function, which grows extremely slowly and is practically constant.

// Counting edges in each component requires iterating through all edges again, taking O(m) time. Finally, checking if each component is complete involves iterating through all vertices once, taking O(n) time.

// Therefore, the overall time complexity is O(n+mα(n)), which is essentially linear in practice.

// Space complexity: O(n)

// The Union-Find data structure uses two arrays of size n for parent pointers and component sizes, requiring O(n) space. The edge count map stores at most n entries (one for each potential component root), requiring O(n) space. Therefore, the overall space complexity is O(n).

