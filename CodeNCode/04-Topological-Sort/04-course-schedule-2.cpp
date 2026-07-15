// 210. Course Schedule II

// There are a total of numCourses courses you have to take, labeled from 0 to numCourses - 1. 
// You are given an array prerequisites where prerequisites[i] = [ai, bi] indicates that
//  you must take course bi first if you want to take course ai.

// For example, the pair [0, 1], indicates that to take course 0 you have to first take course 1.
// Return the ordering of courses you should take to finish all courses. 
// If there are many valid answers, return any of them.
// If it is impossible to finish all courses, return an empty array.

// dfs
// maintain the order in a stack
// course that need to be taken at the end will be at the end
// i.e they will be pushed first
// as dfs call for them will return first
// and then will go to caller function

// --------------------------------------------------------------------------------------------------

class Solution {
private:
    stack<int> stk;

    bool hasCycle(int node, vector<bool>& visited, vector<bool>& inStack, vector<vector<int>>& graph) {

        visited[node] = true;
        inStack[node] = true;

        for(int neighbor: graph[node]) {

            if(!visited[neighbor]) {
                if(hasCycle(neighbor, visited, inStack, graph))
                    return true;
            }
            else if(inStack[neighbor]) return true;
        }

        inStack[node] = false;
        stk.push(node);
        return false;
    }

public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        
        int n = numCourses;
        vector<bool> visited(n, false);
        vector<bool> inStack(n, false);
        vector<int> result;

        // [a, b] ==> b --> a
        // b should be taken before a
        vector<vector<int>> graph(n);

        for(auto &edge: prerequisites) {
            graph[edge[1]].push_back(edge[0]);
        }

        // do this for all connected components
        for(int i = 0; i < n; i++) {
            if(!visited[i]) {
                if(hasCycle(i, visited, inStack, graph)) // if cycle detected
                    return {};
            }
        }

        while(!stk.empty()) {
            result.push_back(stk.top());
            stk.pop();
        }

        return result;
    }
};

// --------------------------------------------------------------------------------------------------

// bfs - Kahn's algorithm

// --------------------------------------------------------------------------------------------------
vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        
	int n = numCourses;
	vector<int> inDegree(n, 0);
	vector<int> result;
	vector<vector<int>> graph(n);
	queue<int> q;

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

		result.push_back(node);

		for(int neighbor: graph[node]) {
			inDegree[neighbor]--;
			if(inDegree[neighbor] == 0)
				q.push(neighbor);
		}
	}

	// if no cycle is there the size will match to n else return {}
	if(result.size() != n) return {};

	return result;
}
// --------------------------------------------------------------------------------------------------