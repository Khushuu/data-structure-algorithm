// 1631. Path With Minimum Effort

class Solution {
using pii = pair<int, pair<int, int>>;
vector<int> dr = {-1, 1, 0, 0};
vector<int> dc = {0, 0, -1, 1};

public:
    int minimumEffortPath(vector<vector<int>>& heights) {
        

        // dijkstra's algorithm

        // maintain a minHeap
        // create a 2d distance array with distance of (0,0) as 0
        // push the first cell in the heap
        // use a pair<int, pair<int, int>> for maintaining dist, cell
        // while the q is not empty
        // pop the first item that is at least distance
        // if it is stale data ignore it
        // else loop over the neighbors
        // for that path find the maximum height
        // if current diff between par and node height is more than that of 
        // height until parent then that will be ur newDist
        // if neighbor is storing something bigger replace it with newDist 
        // push to the heap

        int rows = heights.size();
        int cols = heights[0].size();

        vector<vector<int>> dist(rows, vector<int>(cols, INT_MAX));
        priority_queue<pii, vector<pii>, greater<pii>> minHeap;
        minHeap.push({0, {0, 0}});

        while(!minHeap.empty()) {

            auto [d, cell] = minHeap.top();
            auto [r, c] = cell;
            minHeap.pop();

            // if minHeap has stale data skip it
            if(dist[r][c] < d) continue;

            // loop over neighbors
            for(int i = 0; i < 4; i++) {
                
                int R = r + dr[i];
                int C = c + dc[i];

                // if row is invalid skip it
                if(R < 0 || R >= rows || C < 0 || c >= cols) continue;

                int newDist = max(d, abs(heights[r][c] - heights[R][C]));
                if(newDist < dist[R][C]) {
                    dist[R][C] = newDist;
                    minHeap.push({dist[R][C], {R, C}});
                }
            }
        }

        return dist[rows - 1][cols - 1];
    }
};