// 1489. Find Critical and Pseudo-Critical Edges in Minimum Spanning Tree
/// VERY VERY VERY IMPORTANT PROBLEM

// given a weighted undirected connected graph with n vertices numbered from 0 to n - 1, and an array edges where edges[i] = [ai, bi, weighti] represents a bidirectional and weighted edge between nodes ai and bi. A minimum spanning tree (MST) is a subset of the graph's edges that connects all vertices without cycles and with the minimum possible total edge weight.

// Find all critical and pseudo-critical edges in the minimum spanning tree (MST) of the given graph.

// An MST edge is a critical edge if, after removing the edge, some node has no path to the other.

// A pseudo-critical edge is a critical edge, or a pair of non-critical edges that together form a cycle.

// Return an array containing all the critical and pseudo-critical edges in any order.

// > Instead of trying to classify edges directly, ask: "What happens if I force this edge?" or "What happens if I remove this edge?"

// > If it's critical, remove it. If it's pseudo-critical, force it.

// --------------------------------------------------------------------------------------------------

// # Step 1: Understand the definitions

// Suppose the MST weight is W.

// ### Critical Edge

// An edge is critical if removing it makes the MST worse.

// Either

// * graph becomes disconnected
// * OR minimum weight becomes larger than W.

// Example


// 0 --1-- 1
//  \      |
//  2      2
//   \     |
//     2
//      \
//       2


// If edge `(0,1)` with weight 1 is removed, every MST becomes heavier.

// So it is critical.

// --------------------------------------------------------------------------------------------------

// ### Pseudo-Critical Edge

// An edge is pseudo-critical if

// > It can appear in some MST but doesn't have to.

// In other words,

// If we force this edge into the MST first,
// and we can still build an MST with total weight W,
// then it is pseudo-critical.

// --------------------------------------------------------------------------------------------------

// # Step 2: Main idea

// We first compute

// original MST weight = W

// using normal Kruskal.

// Now test every edge individually.
// There are only two tests.

// --------------------------------------------------------------------------------------------------

// # Test 1 : Is it Critical?

// Ignore this edge completely.

// Run Kruskal.

// If

// new MST weight > W

// or graph cannot connect,

// then

// critical

// Why?

// Because without this edge we cannot obtain the best MST.

// --------------------------------------------------------------------------------------------------

// # Test 2 : Is it Pseudo-Critical?

// Force this edge first.

// Meaning:
// Take this edge before running Kruskal.
// Then continue Kruskal normally.

// IF

// weight == W

// then

// pseudo-critical

// Because there exists an MST containing this edge.

// --------------------------------------------------------------------------------------------------

// # Step 3: Why force first?

// Suppose edge

// A ----- B
// weight = 3

// We don't know whether MST wants it.

// So we manually include it.

// cost = 3
// union(A,B)


// Then continue Kruskal.
// If final weight is still optimal,
// then this edge can belong to an MST.

// --------------------------------------------------------------------------------------------------

// # Step 4: Need original indices

// Kruskal sorts edges.

// But answer needs original positions.
// So convert

// [u,v,w]

// into

// [u,v,w,index]

// Example

// 0 1 1
// 1 2 2
// 2 3 3

// becomes

// 0 1 1 0
// 1 2 2 1
// 2 3 3 2


// Then after sorting we never lose original indices.

// --------------------------------------------------------------------------------------------------

// # Step 5: Helper Function

// Create a function

// mst(skipEdge, forceEdge)

// Parameters

// skipEdge = edge index to ignore
// forceEdge = edge index to include first

// This function returns

// minimum MST weight

// or

// INT_MAX

// if graph cannot connect.

// --------------------------------------------------------------------------------------------------

// ## Case 1

// Normal MST

// skip = -1
// force = -1

// --------------------------------------------------------------------------------------------------

// ## Case 2

// Critical check

// skip = current edge
// force = -1

// --------------------------------------------------------------------------------------------------

// ## Case 3

// Pseudo check

// skip = -1
// force = current edge

// --------------------------------------------------------------------------------------------------

// # Step 6: Kruskal helper
// #Algorithm

// weight = 0

// if force exists

//     add it

// for every edge

//     if skipped

//         continue

//     if endpoints already connected

//         continue

//     take edge

// if not all vertices connected

//     return INF

// return weight

// --------------------------------------------------------------------------------------------------

// # Complexity

// Let

// E = edges
// V = vertices

// Each MST

// O(E α(V))

// We run it 2E + 1 times.

// Overall

// O(E² α(V))

// This is acceptable because

// E ≤ 200

// on LeetCode.

// --------------------------------------------------------------------------------------------------

// # Clean C++ Solution


class DSU {
public:
    vector<int> parent, rank;

    DSU(int n) {
        parent.resize(n);
        rank.assign(n, 0);
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);

        if (a == b) return false;

        if (rank[a] < rank[b])
            swap(a, b);

        parent[b] = a;

        if (rank[a] == rank[b])
            rank[a]++;

        return true;
    }
};

class Solution {
public:
    int kruskal(int n, vector<vector<int>>& edges, int skip, int force) {
        DSU dsu(n);
        int weight = 0;
        int used = 0;

        // Force one edge first
        if (force != -1) {
            dsu.unite(edges[force][0], edges[force][1]);
            weight += edges[force][2];
            used++;
        }

        for (int i = 0; i < edges.size(); i++) {
            if (i == skip) continue;

            if (dsu.unite(edges[i][0], edges[i][1])) {
                weight += edges[i][2];
                used++;
            }
        }

        if (used != n - 1)
            return INT_MAX;

        return weight;
    }

    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges) {

        for (int i = 0; i < edges.size(); i++)
            edges[i].push_back(i);

        sort(edges.begin(), edges.end(),
             [](auto &a, auto &b) {
                 return a[2] < b[2];
             });

        int mstWeight = kruskal(n, edges, -1, -1);

        vector<int> critical, pseudo;

        for (int i = 0; i < edges.size(); i++) {

            // Critical
            if (kruskal(n, edges, i, -1) > mstWeight) {
                critical.push_back(edges[i][3]);
            }
            // Pseudo-critical
            else if (kruskal(n, edges, -1, i) == mstWeight) {
                pseudo.push_back(edges[i][3]);
            }
        }

        return {critical, pseudo};
    }
};


// ### The pattern to remember

// Whenever you're asked whether an edge is necessary or optional in an MST, think of these two Kruskal tests:

// * Critical? → Skip the edge. If the MST becomes impossible or heavier, the edge is critical.
// * Pseudo-critical? → Force the edge first. If the resulting MST still has the original minimum weight, the edge is pseudo-critical.

// This "skip vs. force" technique is the standard approach for this problem and is useful for many MST edge-classification questions.
