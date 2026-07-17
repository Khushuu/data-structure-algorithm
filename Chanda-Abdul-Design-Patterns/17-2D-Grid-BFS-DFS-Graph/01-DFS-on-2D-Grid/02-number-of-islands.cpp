// # 200. Number of Islands (LeetCode)

// ## Problem Statement

// You are given an `m x n` 2D grid where:

// * `'1'` represents land
// * `'0'` represents water

// Your task is to return the number of islands.

// An island is formed by connecting adjacent lands horizontally or vertically (not diagonally). The grid is surrounded by water.

// ---------------------------------------------------------------------------------------------------------


// ### Example 1


// Input:
// grid = [
//   ["1","1","1","1","0"],
//   ["1","1","0","1","0"],
//   ["1","1","0","0","0"],
//   ["0","0","0","0","0"]
// ]

// Output:
// 1


// ### Example 2


// Input:
// grid = [
//   ["1","1","0","0","0"],
//   ["1","1","0","0","0"],
//   ["0","0","1","0","0"],
//   ["0","0","0","1","1"]
// ]

// Output:
// 3

// ---------------------------------------------------------------------------------------------------------

// # Intuition

// Think of every island as a connected component in a graph.

// * Traverse every cell.
// * Whenever an unvisited land (`'1'`) is found:

//   * One new island is discovered.
//   * Visit all connected land cells using BFS or DFS.
//   * Mark them as visited.
// * Continue scanning until the entire grid is processed.

// ---------------------------------------------------------------------------------------------------------

// # Solution 1: BFS

// ## Algorithm

// 1. Traverse every cell.
// 2. If a cell is `'1'`:

//    * Increase island count.
//    * Push it into a queue.
//    * Mark it visited by changing it to `'0'`.
// 3. Repeatedly pop cells from the queue.
// 4. Visit all 4 neighboring cells.
// 5. If a neighbor is land, push it into the queue and mark it visited.
// 6. Continue until the queue becomes empty.

// ---------------------------------------------------------------------------------------------------------

// # Key Interview Points

// * Treat each land cell as a node in a graph.
// * An island is a connected component.
// * Increment the answer only when a new unvisited land cell is found.
// * Mark visited cells immediately (by changing `'1'` to `'0'` or using a separate `visited` array) to avoid revisiting them.
// * Explore only the 4 directions (up, down, left, right); diagonal cells are not connected.
// * Both BFS and DFS have the same time complexity: `O(M × N)`, since every cell is processed at most once.

// ---------------------------------------------------------------------------------------------------------

// ## BFS Code (C++)

// Prefer not to modify the input array and use the `visited` array instead.


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

                if(R >= 0 && R < rows && C >= 0 && C < cols &&
                    !visited[R][C] && grid[R][C] == '1') {
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


// ---------------------------------------------------------------------------------------------------------

// ## BFS Explanation

// Suppose the grid is


// 1 1 0
// 1 0 0
// 0 1 1


// Start scanning:

// * `(0,0)` is land.
// * Island count = 1.
// * Perform BFS.
// * BFS visits


// (0,0)
// (0,1)
// (1,0)


// These cells become water (`0`).

// Continue scanning.

// Next land found:


// (2,1)


// Island count = 2.

// BFS visits

// (2,1)
// (2,2)

// Traversal ends.

// Answer = 2.

// ---------------------------------------------------------------------------------------------------------

// ## BFS Complexity

// * Time: `O(M × N)`

//   * Every cell is visited at most once.

// * Space: `O(M × N)`

//   * Queue can contain all land cells in the worst case.

// ---------------------------------------------------------------------------------------------------------

// # Solution 2: DFS

// ## Algorithm

// 1. Traverse every cell.
// 2. If a land cell is found:

//    * Increase island count.
//    * Run DFS.
// 3. DFS marks the current cell visited.
// 4. Recursively visit all 4 directions.

// ---------------------------------------------------------------------------------------------------------

// ## DFS Code (C++)

class Solution {
public:
    int rows;
    int cols;
    vector<int> dr = {-1, 1, 0, 0};
    vector<int> dc = {0, 0, -1, 1};
    vector<vector<bool>> visited;

    void dfs(int r, int c, vector<vector<char>>& grid) {

        visited[r][c] = true;

        for(int i = 0; i < 4; i++) {

            int nr = r + dr[i];
            int nc = c + dc[i];
            
            // valid grid, not visited and is an island i.e cell value is 1
            if(nr >= 0 && nr < rows && nc >= 0 && nc < cols && 
                !visited[nr][nc] &&
                grid[nr][nc] == '1')
                    dfs(nr, nc, grid);
        }
    }

    int numIslands(vector<vector<char>>& grid) {
        
        // use a visited array to check what all grid are covered
        // run dfs if a grid value is 1 and is not visited
        // for one run of dfs increment the connected component count
        
        rows = grid.size();
        cols = grid[0].size();

        visited.assign(rows, vector<bool>(cols, false));

        int count = 0;

        for(int r = 0; r < rows; r++) {
            for(int c = 0; c < cols; c++) {

                if(!visited[r][c] && grid[r][c] == '1') {

                    count++;
                    dfs(r, c, grid);
                }
            }
        }

        return count;
    }
};

// ---------------------------------------------------------------------------------------------------------

// ## DFS Explanation

// Consider

// 1 1 0
// 1 0 1
// 0 1 1

// Traversal begins:

// At `(0,0)`:


// DFS(0,0)
//     ↓
// DFS(1,0)
//     ↑
// DFS(0,1)


// Entire first island is visited.

// Continue scanning.

// Next unvisited land:


// (1,2)


// DFS explores


// (1,2)
// ↓
// (2,2)
// ←
// (2,1)


// Second island is completed.

// Answer = 2.

// ---------------------------------------------------------------------------------------------------------

// ## DFS Complexity

// * Time: `O(M × N)`

//   * Each cell is visited exactly once.

// * Space: `O(M × N)` (worst case)

//   * Recursive call stack may contain all land cells in a single large island.

// ---------------------------------------------------------------------------------------------------------

// # BFS vs DFS

// | Feature          | BFS                | DFS                                |
// | ---------------- | ------------------ | ---------------------------------- |
// | Data Structure   | Queue              | Recursion / Stack                  |
// | Traversal        | Level by level     | Depth first                        |
// | Time Complexity  | `O(M × N)`         | `O(M × N)`                         |
// | Space Complexity | `O(M × N)`         | `O(M × N)` (recursive stack)       |
// | Easy to Write    | Moderate           | Very Easy                          |
// | Risk             | No recursion limit | Stack overflow on very large grids |

