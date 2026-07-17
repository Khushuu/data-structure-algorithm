// 994. Rotting Oranges

// You are given an m x n grid where each cell can have one of three values:

// 0 representing an empty cell,
// 1 representing a fresh orange, or
// 2 representing a rotten orange.
// Every minute, any fresh orange that is 4-directionally adjacent to a rotten orange becomes rotten.

// Return the minimum number of minutes that must elapse until no cell has a fresh orange. If this is impossible, return -1.

// ----------------------------------------------------------------------------------------------------------

// T.C. - O(N * M)
// S.C. - O(N * M)

// BFS Solution

class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        
        // all rotten oranges will start rotting at once
        // intialize the queue with all the rotten oranges 
        // track the level of number of elements processed at once
        // so in min 0 all rotten oranges are put
        // so we process all the rotten oranges and keep pushing the 
        // adjacent oranges to the rotten oranges in the queue
        // we will increment time level by level

        // if an orange becomes rotten from fresh update it with 2
        // we will only process fresh oranges - value - 1
        // and ignore the empty cells with value - 0

        // if no fresh orange is connected to the rotten orange
        // then the minutes value will be 0
        // once the fresh oranges start rotting the minutes will start from 1

        // there is a possibility that still some fresh oranges are left
        // in that case return -1

        int minutes = -1;
        int rows = grid.size();
        int cols = grid[0].size();

        vector<int> dr = {-1, 1, 0, 0};
        vector<int> dc = {0, 0, -1, 1};

        queue<pair<int, int>> q;

        for(int r = 0; r < rows; r++) {
            for(int c = 0; c < cols; c++) {

                if(grid[r][c] == 2)
                    q.push({r, c}); 
            }
        }


        while(!q.empty()) {

            minutes++;
            int size = q.size();

            // process level by level 
            // in 1 minute process all the oranges at distance 1
            // from the rotten orange
            for(int i = 0; i < size; i++) {

                auto [r, c] = q.front();
                q.pop();

                for(int i = 0; i < 4; i++) {

                    int nr = r + dr[i];
                    int nc = c + dc[i];

                    // we only process the fresh oranges
                    // when an orange is fresh - mark it rotten
                    // as it came in touch with another rotten orange
                    if(nr >= 0 && nr < rows && nc >= 0 && nc < cols &&
                        grid[nr][nc] == 1) {
                            
                            grid[nr][nc] = 2;
                            q.push({nr, nc});
                    }
                }
            }
        }   

        for(int r = 0; r < rows; r++) {
            for(int c = 0; c < cols; c++) {
                if(grid[r][c] == 1)
                    return -1;
            }
        }
        
        // if no rotten orange is there or grid is empty
        if(minutes == -1) return 0;

        return minutes; 
    }
};