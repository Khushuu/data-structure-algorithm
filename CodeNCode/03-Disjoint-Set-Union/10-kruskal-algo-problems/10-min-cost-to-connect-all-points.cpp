// 1584. Min Cost to Connect All Points
// Inefficient Solution - O(n^2 log n) - Using Kruskal's Algorithm
// Use Prim's Algorithm for O(n^2) solution

// You are given an array points representing integer coordinates of some points on a 2D-plane, where points[i] = [xi, yi]. The cost of connecting two points [xi, yi] and [xj, yj] is the manhattan distance between them: |xi - xj| + |yi - yj|.

// Return the minimum cost to make all points connected. All points are connected if there is exactly one simple path between any two points.

// Example
// Input: points = [[0,0],[2,2],[3,10],[5,2],[7,0]]
// Output: 20
// Explanation: 
// We can connect the points as shown above to get the minimum cost of 20.
// Notice that there is a unique path between every pair of points.

// T.C - O(E log E) where E is the number of edges in the graph
// S.C - O(E) where E is the number of edges in the graph

// Kruskal's Algorithm SOLUTION


class Solution {
public:
    vector<int> parent;
    vector<int> size;
    // sort on the basis of weight
    static bool comp(const vector<int>& a, const vector<int>& b) {
        return a[2] < b[2];
    }

    void makeSet(int n) {

        parent.resize(n);
        size.resize(n, 1);

        for(int i = 0; i < n; i++)
            parent[i] = i;
    }

    int find(int a) {

        if(parent[a] == a) return a;
        return parent[a] = find(parent[a]);
    }

    bool unite(int a, int b) {

        int rootA = find(a);
        int rootB = find(b);

        if(rootA == rootB)  
            return false;
        
        if(size[rootA] < size[rootB])
            swap(rootA, rootB);
        
        parent[rootB] = rootA;
        size[rootA] += size[rootB];

        return true;
    }

    int minCostConnectPoints(vector<vector<int>>& points) {
        
        // minimum spanning tree problem
        // use kruskal's algorithm 

        // let us mark or identify each point with its index 
        // we need to build a weighted edge list 
        // where weight is the distance between the two points 

        // once this weighted edge list is build we can use Kruskal's algo
        // sort all the edges on the basis of weight 
        // loop over the edge list 
        // if two nodes are connected alredy skip them
        // else note the cost of adding them 

        // (a, b, w) --> connect a and b point with weight w
        vector<vector<int>> edges;
        int sum = 0;

        // build edgeList
        for(int i = 0; i < points.size(); i++) {

            int x1 = points[i][0];
            int y1 = points[i][1];

            for(int j = i + 1; j < points.size(); j++) {

                int x2 = points[j][0];
                int y2 = points[j][1];

                int dist = abs(x2 - x1) + abs(y2 - y1);

                edges.push_back({i, j, dist});
            }
        }

        sort(edges.begin(), edges.end(), comp);

        // with all the points 
        makeSet(points.size());

        for(vector<int> edge: edges) {

            // if both the points were connected add the sum
            if(unite(edge[0], edge[1]))
                sum += edge[2];
        }

        return sum;
    }
};