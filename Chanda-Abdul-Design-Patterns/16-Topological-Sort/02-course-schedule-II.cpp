// 210. Course Schedule II

// given a number of courses and prerequisites
// find a valid topological order of courses to take
// if not possible, return an empty array

// T.C - O(V + E)
// S.C - O(V + E)

class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        
        // [a, b] - must take course b if you want to take course a
        // i.e a is dependent on b
        // b-->a [an edge directed from b to a]

        // return order if you can finish all courses
        // else return empty array

        // using kahn's algorithm to find the topological sorting order
        // if sorting is not possible return empty array

        int n = numCourses;

        queue<int> q;
        vector<int> indegree(n);
        vector<vector<int>> graph(n);

        vector<int> result;

        // build graph and compute indegree 
        for(vector<int> &edge: prerequisites) {

            // {a, b} b -> a
            int a = edge[0];
            int b = edge[1];

            indegree[a]++;
            graph[b].push_back(a);
        }

        // put into the queue - nodes with indegree of 0
        for(int node = 0; node < n; node++)
            if(indegree[node] == 0)
                q.push(node);

        // find count of nodes for which topological order is possible
        while(!q.empty()) {

            int node = q.front();
            q.pop();

            // node has an indegree 0 - so it can be processed
            result.push_back(node);

            for(int neighbor: graph[node]) {
                
                // as the edge from node to neighbor is being removed
                // since we popped the node
                // all the nodes that have an edge from node to neighbor
                // will lose an indegree count
                indegree[neighbor]--;

                if(indegree[neighbor] == 0) 
                    q.push(neighbor);
            }
        }
        
        // if all nodes processed and had valid order return result
        // else empty array

        // cycle present
        if(result.size() != n)
            return {};

        return result;
    }
};