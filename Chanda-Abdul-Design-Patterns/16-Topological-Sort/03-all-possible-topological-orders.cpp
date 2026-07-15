// Find All Possible Topological Orders

// There are N tasks, labeled from 0 to N-1. 
// Each task can have some prerequisite tasks which need to be completed before it can be scheduled. 
// Given the number of tasks and a list of prerequisite pairs, write a method to print all possible ordering of tasks meeting all prerequisites.

// This is a classic extension of **Topological Sorting**.

// The difference from the normal topological sort is:

// * **Normal topological sort:** Find **one** valid ordering.
// * **This problem:** Find **all possible** valid orderings.

// A simple BFS (Kahn's algorithm) won't work because whenever there are multiple nodes with indegree `0`, you must explore **every possible choice**.

// ## Idea: Backtracking + Kahn's Algorithm

// 1. Build the graph and indegree array.
// 2. At every step:

//    * Find **all** vertices with indegree `0` that haven't been used yet.
//    * For each such vertex:

//      * Choose it.
//      * Add it to the current ordering.
//      * Reduce indegree of its neighbors.
//      * Recurse.
//      * Undo the changes (backtrack).
// 3. When the ordering contains all `N` tasks, print it.

// ----------------------------------------------------------------------------------------------------------------

// ## Example

// ```
// Tasks = 4

// Prerequisites:
// 3 -> 2
// 3 -> 0
// 2 -> 0
// 2 -> 1
// ```

// Initially

// ```
// Indegree

// 0 : 2
// 1 : 1
// 2 : 1
// 3 : 0
// ```

// Only `3` has indegree 0.

// Choose `3`

// Now

// ```
// 0 : 1
// 1 : 1
// 2 : 0
// ```

// Only `2` is available.

// Choose `2`

// Now

// ```
// 0 : 0
// 1 : 0
// ```

// Now there are **two choices**:

// ```
// 3 2 0 1
// ```

// or

// ```
// 3 2 1 0
// ```

// Backtracking explores both.

// ----------------------------------------------------------------------------------------------------------------


// ## C++ Code

#include <bits/stdc++.h>
using namespace std;

void allTopologicalSorts(vector<vector<int>>& graph,
                         vector<int>& indegree,
                         vector<bool>& visited,
                         vector<int>& order) {

    bool found = false;

    for (int i = 0; i < graph.size(); i++) {

        if (!visited[i] && indegree[i] == 0) {

            visited[i] = true;
            order.push_back(i);

            for (int child : graph[i])
                indegree[child]--;

            allTopologicalSorts(graph, indegree, visited, order);

            // Backtrack
            for (int child : graph[i])
                indegree[child]++;

            visited[i] = false;
            order.pop_back();

            found = true;
        }
    }

    // No more choices
    if (!found) {
        if (order.size() == graph.size()) {
            for (int x : order)
                cout << x << " ";
            cout << endl;
        }
    }
}

int main() {

    int N = 4;

    vector<pair<int,int>> prereq = {
        {3,2},
        {3,0},
        {2,0},
        {2,1}
    };

    vector<vector<int>> graph(N);
    vector<int> indegree(N,0);

    for (auto &p : prereq) {
        graph[p.first].push_back(p.second);
        indegree[p.second]++;
    }

    vector<bool> visited(N,false);
    vector<int> order;

    allTopologicalSorts(graph, indegree, visited, order);
}

// ----------------------------------------------------------------------------------------------------------------

// ## Why Backtracking?

// Suppose the current zero-indegree nodes are:

// ```
// Queue = {1, 4, 7}
// ```

// A normal Kahn's algorithm picks one (depending on queue order) and produces **one** topological order.

// To generate **all** orders, you must explore:

// ```
// Choose 1
//     recurse

// Choose 4
//     recurse

// Choose 7
//     recurse
// ```

// This branching is exactly what backtracking does.

// ----------------------------------------------------------------------------------------------------------------

// ## Time Complexity

// Let:

// * `V` = number of tasks
// * `E` = number of prerequisite relations
// * `K` = number of valid topological orderings

// For each valid ordering, we process all vertices and edges:

// * Updating indegrees: **O(E)**
// * Building one ordering: **O(V)**

// Overall: O(K * (V + E))}

// In the worst case (no edges), every permutation is valid:

// * (K = V!)

// so the worst-case complexity becomes: O(V! * V)}

// (up to constant-factor differences in implementation).

// ### Space Complexity

// * Graph: **O(V + E)**
// * Indegree array: **O(V)**
// * Visited array: **O(V)**
// * Current ordering (recursion path): **O(V)**
// * Recursion stack: **O(V)**

// Overall auxiliary space: O(V + E)}

// excluding the space needed to output all orderings.
