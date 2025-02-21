// 207. Course Schedule
// 210. Course Schedule II

// course schedule 
// given order of courses return if it is possible to complete all courses
// There are a total of numCourses courses you have to take, labeled from 0 to numCourses - 1. 
// You are given an array prerequisites where prerequisites[i] = [ai, bi] indicates that 
// you must take course bi first if you want to take course ai.

// For example, the pair [0, 1], indicates that to take course 0 you have to first take course 1.
// Return true if you can finish all courses. Otherwise, return false.

// approach
// since we only need to check if it is possible to complete all course
// cycle detection in directed graph should suffice

// dfs
// --------------------------------------------------------------------------------------------------

class Solution {
private:
    bool hasCycle(int node, vector<bool>& visited, vector<bool>& inStack, vector<vector<int>>& graph) {

        visited[node] = true;
        inStack[node] = true;

        // check all neighbors
        // if any one returns cycle - return from method
        for(int neighbor: graph[node]) {
            if(!visited[neighbor]) {
                if(hasCycle(neighbor, visited, inStack, graph))
                    return true;
            }
            else if(inStack[neighbor]) return true;
        }

        inStack[node] = false;
        return false;
    }
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        
        // dfs 
        // if there is a cycle in the directed graph courses can not be finished
        // write code to detect cycle in graph
        // if a cycle is found return false
        // if after traversal no cycle is found return true

        int n = numCourses;
        vector<bool> visited(n, false);
        vector<bool> inStack(n, false);

        // [a, b] ==> b --> a
        // b should be taken before a
        vector<vector<int>> graph(n);

        for(auto &edge: prerequisites) {
            graph[edge[1]].push_back(edge[0]);
        }

        // do this for all connected components
        for(int i = 0; i < n; i++) {
            if(!visited[i]) {
                if(hasCycle(i, visited, inStack, graph))
                    return false;
            }
        }

        return true;
    }
};

// --------------------------------------------------------------------------------------------------

// BFS - Kahn's algorithm

// --------------------------------------------------------------------------------------------------

class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        
        // cycle detection using kahn's algorithm
        // count the number of nodes with inDegree 0
        // this count should be equal to number of courses
        // y --> that would mean presence of no cycle in directed graph

        int n = numCourses;
        vector<int> inDegree(n, 0);
        vector<vector<int>> graph(n);
        queue<int> q;
        int count = 0;

        // [a, b] ==> b --> a
        for(auto &edge: prerequisites) {
            int a = edge[0];
            int b = edge[1];
            graph[b].push_back(a);
            inDegree[a]++;
        }

        // insert nodes with indegree = 0 in the queue
        for(int i = 0; i < n; i++) {
            if(inDegree[i] == 0)
                q.push(i);
        }

        while(!q.empty()) {

            int node = q.front();
            q.pop();

            count++;

            for(int neighbor: graph[node]) {
                inDegree[neighbor]--;
                if(inDegree[neighbor] == 0)
                    q.push(neighbor);
            }
        }

        return count == n;
    }
};

// --------------------------------------------------------------------------------------------------