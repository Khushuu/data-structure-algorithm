// 200. Number of Islands
// Given an m x n 2D binary grid grid which represents a map of '1's (land) and '0's (water)
// return the number of islands.
// An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically.
// You may assume all four edges of the grid are all surrounded by water.

// approach
// we need to find the total no. of connected components
// the no. of times we run bfs or dfs call will be one island
// in 1 chain of dfs or bfs call 1 island will be visited 

// dfs
// Time Complexity: O(N×M)
// Space Complexity: O(N×M) 
// ------------------------------------------------------------------------------------------------------------

class Solution {
private:
    int rows, cols;
    vector<int> dr = {-1, 1, 0, 0};
    vector<int> dc = {0, 0, -1, 1};

    void dfs(int r, int c, vector<vector<bool>>& visited, vector<vector<char>>& grid) {
        visited[r][c] = true;

        // Explore 4 directions
        for (int i = 0; i < 4; i++) {

            int R = r + dr[i];
            int C = c + dc[i];

            // Check if in bounds, is land ('1'), and not visited
            if (R >= 0 && R < rows && C >= 0 && C < cols && grid[R][C] == '1' && !visited[R][C]) {
                dfs(R, C, visited, grid);
            }
        }
    }

public:
    int numIslands(vector<vector<char>>& grid) {
        int count = 0;
        rows = grid.size();
        cols = grid[0].size();
        vector<vector<bool>> visited(rows, vector<bool>(cols, false));

        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if (!visited[r][c] && grid[r][c] == '1') {
                    count++; // Found a new island
                    dfs(r, c, visited, grid);
                }
            }
        }

        return count;
    }
};

// ------------------------------------------------------------------------------------------------------------

// bfs
// ------------------------------------------------------------------------------------------------------------

class Solution {
private:
    vector<int> dr = {-1, 1, 0, 0};
    vector<int> dc = {0, 0, -1, 1};
    int rows, cols;

    void bfs(int row, int col, vector<vector<bool>>& visited, vector<vector<char>>& grid) {

        queue<pair<int, int>> q; // to store r,c
        q.push({row, col});
        visited[row][col] = true;

        while(!q.empty()) {

            auto [r, c] = q.front();
            q.pop();

            for(int i = 0; i < 4; i++) {

                int R = r + dr[i];
                int C = c + dc[i];

                if(R >= 0 && R < rows && C >= 0 && C < cols && !visited[R][C] && grid[R][C] == '1') {
					q.push({R, C});
					visited[R][C] = true;
                }
            }
        }
    }
public:
    int numIslands(vector<vector<char>>& grid) {
        
        // bfs 
        // count number of connected components
        // run bfs for land 

        rows = grid.size();
        cols = grid[0].size();

        vector<vector<bool>> visited(rows, vector<bool>(cols, false));
        int count = 0;

        for(int r = 0; r < rows; r++) {
            for(int c = 0; c < cols; c++) {

                if(!visited[r][c] && grid[r][c] == '1') {
                    count++;
                    bfs(r, c, visited, grid);
                }
            }
        }

        return count;
    }
};
// ------------------------------------------------------------------------------------------------------------

