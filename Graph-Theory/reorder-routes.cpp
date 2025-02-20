// Leetcode Problem 1466: Reorder Routes to Make All Paths Lead to the City Zero

// You are given n cities numbered from 0 to n - 1 and n - 1 roads.
//  Each road is directed, meaning it goes from a -> b.
//  Your task is to count the minimum number of edges that need to be reversed so that all paths lead to city 0.

// approach
// the graph is directed that means there won't be a path to all nodes
// to tackle this create an undirected graph but mark the original path using a pair of node, bool
// vector<vector<pair<int, bool>>> graph(n) - where bool value represent if it is the original path

// suppose edge = (1, 2) i.e 1-->2
// in graph    1 = (2, true) and 2 = (1, false) --> since 2 -> 1 is not the original path

// y we do this
// as we want to reach all the nodes and directed graph won't let that happen
// so we construct undirected graph

// we count the original paths as those cities were reachable from 0
// and we want them to be reachable from city to city 0
// so original path count gives us the result --> as those path should be reversed

// if a node is reachable from the source city 0 then it means there is a path from city 0 to that city
// we want all paths from different cities to be directed towards city 0
// that means all cities that can be reached from 0 --> there path should be reversed

// T.C = O(N) -- traverse each node once
// S.C = O(N) -- tree type structure n node and n - 1 edges

// NOTE: emplace_back is faster for inserting pair as it does not create copy 
// -------------------------------------------------------------------------------------------------

class Solution {
private:
    void dfs(int node, vector<bool>& visited, 
        vector<vector<pair<int, bool>>>& graph, int& result) {

            visited[node] = true;

            for(const auto& [child, is_original]: graph[node]) {

                if(!visited[child]) {
                    if(is_original) result++;
                    dfs(child, visited, graph, result);
                }
            }
        }
public:
    int minReorder(int n, vector<vector<int>>& connections) {
        
        vector<vector<pair<int, bool>>> graph(n);
        vector<bool> visited(n, false);
        int result = 0;

        for(const auto& edge: connections) {
            
            int a = edge[0];
            int b = edge[1];
			// graph[a].emplace_back(b, true);
            // graph[b].emplace_back(a, false);
            graph[a].push_back({b, true});
            graph[b].push_back({a, false});
        }

        dfs(0, visited, graph, result);
        return result;
    }
};

// -------------------------------------------------------------------------------------------------
