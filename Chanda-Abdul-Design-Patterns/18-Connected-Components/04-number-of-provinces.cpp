// 547. Number of Provinces

// There are n cities. Some of them are connected, while some are not. 
// If city a is connected directly with city b, and city b is connected directly with city c, then city a is connected indirectly with city c.

// A province is a group of directly or indirectly connected cities and no other cities outside of the group.

// You are given an n x n matrix isConnected where isConnected[i][j] = 1 if the ith city and the jth city are directly connected, and isConnected[i][j] = 0 otherwise.

// Return the total number of provinces.

// Input: isConnected = [[1,1,0],[1,1,0],[0,0,1]]
// Output: 2

//----------------------------------------------------------------------------------------------------------

// Instead of giving the edge list or the adjacency list, we are given the adjacency matrix.
// We can use DFS to find the number of provinces.

// T.C: O(n * n) - matrix traversal
// S.C: O(n)

//----------------------------------------------------------------------------------------------------------
// DFS SOLUTION

class Solution {
private:
    void dfs(int node, vector<bool>& visited, vector<vector<int>>& isConnected) {

        // mark node as visited
        visited[node] = true;

        // call for the neighbors of node that are not visited 
        // isConnected[node][i] = 1 = neighbor of node 
        for(int i = 0; i < isConnected.size(); i++) {
            if(isConnected[node][i] && !visited[i])
                dfs(i, visited, isConnected);
        }
    }
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        
        // isConnected is an adjacency matrix
        // where isConnected[i][j] = 1 
        // if the ith city and the jth city are directly connected,
        // and isConnected[i][j] = 0 otherwise.

        // now loop over all the edges in isConnected matrix
        // and run dfs if the vertex is not visited and isConnected = 1
        // and increment the connect components count
        // idea is for one component - one dfs call will visit all vertices

        // undirected graph
        int n = isConnected.size();
        vector<bool> visited(n, false);
        int count = 0;

        // count number of connected components
        for(int i = 0; i < n; i++) {
            if(!visited[i]) {
                count++;
                dfs(i, visited, isConnected);
            }
        }

        return count;
    }
};

//----------------------------------------------------------------------------------------------------------
// BFS SOLUTION

class Solution {
public:
    void bfs(int node, vector<vector<int>>& isConnected, vector<bool>& visit) {
        queue<int> q;
        q.push(node);
        visit[node] = true;

        while (!q.empty()) {
            node = q.front();
            q.pop();

            for (int i = 0; i < isConnected.size(); i++) {
                if (isConnected[node][i] && !visit[i]) {
                    q.push(i);
                    visit[i] = true;
                }
            }
        }
    }

    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size();
        int numberOfComponents = 0;
        vector<bool> visit(n);

        for (int i = 0; i < n; i++) {
            if (!visit[i]) {
                numberOfComponents++;
                bfs(i, isConnected, visit);
            }
        }

        return numberOfComponents;
    }
};



//----------------------------------------------------------------------------------------------------------

