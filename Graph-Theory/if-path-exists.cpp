// Leetcode 1971 - Find if Path Exists in Graph
// given a graph - with nodes from 0 to n - 1
// source node and a destination node
// return true if there is a path from source to destination 

// DFS and BFS both have same time and space complexity
// Time Complexity: O(N+E)
// We visit each node and edge at most once.
// Space Complexity: O(N+E)
// Adjacency list takes O(N+E).

// DFS
//---------------------------------------------------------------------------------------------------------------

class Solution {
private:
    bool dfs(int node, int destination, vector<bool>& visited, vector<vector<int>>& graph) {

        if(node == destination) return true;

        visited[node] = true;

        for(int neighbor: graph[node]) {
            if(!visited[neighbor]) {
                if(dfs(neighbor, destination, visited, graph))
                    return true;
            }
        }

        return false;
    }
public:
    bool validPath(int n, vector<vector<int>>& edges, int source, int destination) {
        
        // use dfs
        // every time u reach a node
        // just check if it is equal to destination node
        // if yes - just return true from the method
        // we just need to check if path is there or not and not explore all nodes
        // hence we return from the function call

        vector<bool> visited(n, false);
        vector<vector<int>> graph(n);

        for(auto& edge: edges) {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }

        return dfs(source, destination, visited, graph);
    }
};

//---------------------------------------------------------------------------------------------------------------

// BFS
// Time Complexity: O(N+E)
// Space Complexity: O(N+E)
//---------------------------------------------------------------------------------------------------------------
class Solution {
public:
    bool validPath(int n, vector<vector<int>>& edges, int source, int destination) {
        
        // use bfs
        // every time u reach a node
        // just check if it is equal to destination node
        // if yes - just return true 

        vector<bool> visited(n, false);
        vector<vector<int>> graph(n);

        // create graph
        for(auto& edge: edges) {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }

        queue<int> q;
        q.push(source);
        visited[source] = true;

        while(!q.empty()) {

            int node = q.front();
            q.pop();

            if(node == destination) return true;

            for(int neighbor: graph[node]) {
                if(!visited[neighbor]) {
                    q.push(neighbor);
                    visited[neighbor] = true;
                }
            }
        }

        return false;
    }
};
//---------------------------------------------------------------------------------------------------------------
