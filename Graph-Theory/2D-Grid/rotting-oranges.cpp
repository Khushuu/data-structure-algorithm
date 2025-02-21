// 994. Rotting Oranges

// 0 - empty cell
// 1 - fresh orange
// 2 - rotten orange

// every minute a fresh orange 4-directionally adjacent 
// to a rotten orange becomes rotten.
// return minimum number of minutes that must elapse
// so that no cell has fresh orange
// if impossible - return -1

// since minimum minutes are asked - run bfs
// push all oranges that are rotten into q
// track the level count in bfs for minutes
// initialize level count with -1
// as first level is of rotten oranges 
// and for already rotten oranges time will become 0 after time++

// instead of using a visited array grid can be used
// as a fresh orange becomes rotten mark it as 2

// it will be impossible to convert all fresh to rotten if
// there is more than one connected component of fresh orange
// that is not connected to rotten

// ----------------------------------------------------------------------------------------------------------

class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        
        vector<int> dr = {-1, 1, 0, 0};
        vector<int> dc = {0, 0, -1, 1};

        queue<pair<int, int>> q;
        int rows = grid.size();
        int cols = grid[0].size();

        // initialize queue with rotten oranges
        for(int r = 0; r < rows; r++) {
            for(int c = 0; c < cols; c++) {
                if(grid[r][c] == 2)
                    q.push({r, c});
            }
        }

        int timer = -1;

        while(!q.empty()) {

            timer++;
            int n = q.size();

            // process cells at each level
            while(n--) {

                auto [r, c] = q.front();
                q.pop();

                for(int i = 0; i < 4; i++) {
                    
                    int R = r + dr[i];
                    int C = c + dc[i];

                    // fresh oranges will be rotten if connected to rotten
                    if(R >= 0 && R < rows && C >= 0 && C < cols && grid[R][C] == 1) {
						grid[R][C] = 2;
						q.push({R, C});
					}
                }
            }
        }

        // if still a fresh orange is present return -1
        for(int r = 0; r < rows; r++) {
            for(int c = 0; c < cols; c++)
                if(grid[r][c] == 1)
                    return -1;
        }

        if(timer == -1) return 0;

        return timer;
    }
};
// ----------------------------------------------------------------------------------------------------------

// another approach
// instead of checking the grid again for fresh orange
// precalculate the number of fresh oranges 
// each time a fresh orange rots reduce count of fresh oranges
// at the end if still fresh oranges are present return -1

// -----------------------------------------------------------------------------------------------------------

class Solution {
private:
    vector<int> dr = {-1, 1, 0, 0};
	vector<int> dc = {0, 0, -1, 1};

public:
    int orangesRotting(vector<vector<int>>& grid) {
        
        int rows = grid.size();
        int cols = grid[0].size();
        int fresh = 0;
        queue<pair<int, int>> q;

        // push all rotten oranges in the queue
        for(int r = 0; r < rows; r++) {
            for(int c = 0; c < cols; c++) {
                if(grid[r][c] == 2) {
                    q.push({r, c});
                }
                else if(grid[r][c] == 1)
                    fresh++;
            }
        }

        int timer = -1;
        while(!q.empty()) {

            int n = q.size();
            
            for(int i = 0; i < n; i++) {
                
                int r = q.front().first;
                int c = q.front().second;
                q.pop();
                
                for(int j = 0; j < 4; j++) {
                    int R = r + dr[j];
                    int C = c + dy[j];

                    if(R >= 0 && R < rows && C >= 0 && C < cols && grid[R][C] == 1) {
                        grid[R][C] = 2;
                        q.push({R, C});
                        fresh--;
                    }
                }
            }

            timer++;
        }

        if(fresh > 0) return -1;
        if(timer == -1) return 0;

        return timer;
    }
};

// -----------------------------------------------------------------------------------------------------------
