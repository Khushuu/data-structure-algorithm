// 1857. Largest Color Value in a Directed Graph

// given n nodes and m edges
// nodes are numbered from 0 to n - 1
// each node has a color given by colors string 
// colors[i] is a lowercase English letter representing the color of the ith node in this graph (0-indexed). 
// find the highest frequency of a color along any path
// if there is a cycle return -1

// approach
// better to traverse in a sequential manner
// so that path that is common is traversed once
// this can be done using topological sort
// also for each path when u go to a certain node - pass all the frequency it has till now to the neighbor path
// so initially nodes with indegree = 0 are traversed

// the color values - freq they hold till that point are passed on to their neighbors
// also a neighbor might already have same color from some other path
// take the maximum of the color that neighbor already holds and of the one passed from the parent
// and directly add the color that the node holds to the color freq array
// as for the new path forming it will ahve this color

// since colors is in lower case we can have a vector of size 26 to track freq of each color for the path
// use a n * 26 size array for holding 26 colors for all n nodes
// and keep updating the color array every time a neighbor node is encountered with the color of parent node

// at each point find the max frequency found till that point
// also maintain a count for checking processed nodes
// if count is not equal to n that means there was a cycle - return -1 then
// otherwise return the result - max freq of color

// T.C = O(26 * (n + e))
// S.C = O(26 * n)
// ------------------------------------------------------------------------------------------------------

class Solution {
public:
    int largestPathValue(string colors, vector<vector<int>>& edges) {
        
        // topological sort - Kahn's algorithm
        // have a color array of size 26 for each node
        // i.e size n * 26 
        // when u pop a node from a q with indegree 0
        // that node is traversed
        // the freq of color it holds will be updated in its color array 
        // and the freq color array of its neighbors will be updated
        // it will be the max of the freq of neighbor and the node
        // also keep updating the result with max freq color seen so far

        int n = colors.size();
        vector<int> inDegree(n, 0);
        vector<vector<int>> graph(n);
        vector<vector<int>> colorFreq(n, vector<int>(26, 0));

        // prepare graph
        for(const auto& edge: edges) {
            graph[edge[0]].push_back(edge[1]);
            inDegree[edge[1]]++;
        }

        // push all nodes with inDegree = 0 in q
        queue<int> q;
        for(int i = 0; i < n; i++) {
            if(inDegree[i] == 0)
                q.push(i);
        }

        // process nodes with indegree = 0
        // if count != n at the end it means there is cycle in graph
        // return -1 in case of cycle
        int count = 0; // no of nodes with indegree = 0
        int result = 0; // max freq of color seen so far

        while(!q.empty()) {

            int node = q.front();
            q.pop();

            count++; // no. of nodes with indegree = 0

            // add the color of node to the colorFreq array
            int index = colors[node] - 'a';
            colorFreq[node][index]++;

            // update the result with max freq 
            result = max(result, colorFreq[node][index]);

            for(int neighbor: graph[node]) {

                inDegree[neighbor]--;
                if(inDegree[neighbor] == 0)
                    q.push(neighbor);
                
                // update the neighbor color freq with
                // max of its and nodes color freq

                for(int i = 0; i < 26; i++) {
                    colorFreq[neighbor][i] =
                        max(colorFreq[neighbor][i], colorFreq[node][i]);
                }
            }
        }

        return count == n ? result : -1;
    }
};

// ------------------------------------------------------------------------------------------------------