// 417. Pacific Atlantic Water Flow

// given a matrix of heights, find all cells that can flow to both oceans

// Intuition
// The problem asks us to find cells in a grid of heights from which 
// water can flow to both the Pacific Ocean (top/left edges) and the Atlantic Ocean (bottom/right edges).
// Instead of simulating water flowing from each cell to the oceans (which would be slow ❌), we reverse the process ✅:
// Start from the oceans’ borders and simulate water flowing inward (to higher or equal height cells).
// Any cell visited by both Pacific and Atlantic flows can reach both oceans.

// Approach
// Use DFS (or BFS) from all border cells touching the Pacific and Atlantic oceans.
// Pacific → top row + left column
// Atlantic → bottom row + right column
// During DFS/BFS, only move to neighbors with height ≥ current height.
// This ensures water could have flowed down into the current cell.
// Maintain two visited matrices (or sets): pacific and atlantic.
// After traversal, the answer is the intersection of these two sets.

//------------------------------------------------------------------------------------------------

// Complexity
// Time complexity : O(m * n)
// Every cell is visited at most twice (once from each ocean).

// Space complexity : O(m * n)
// For visited matrices + recursion/stack space.

//------------------------------------------------------------------------------------------------

// DFS Solution

class Solution {
private:
    vector<int> dr = {1, -1, 0, 0};
    vector<int> dc = {0, 0, -1, 1};
    int rows = 0;
    int cols = 0;

    void dfs(int r, int c, vector<vector<bool>>& visited, vector<vector<int>>& heights) {

        visited[r][c] = true;

        // visit neighbor if they are not visited and valid and
        // if height of neighbor >= height of current cell
        for(int i = 0; i < 4; i++) {

            int R = r + dr[i];
            int C = c + dc[i];

            if(R >= 0 && R < rows && C >= 0 && C < cols && 
                !visited[R][C] && heights[R][C] >= heights[r][c]) {
                    
                    dfs(R, C, visited, heights);
            }

        }
    }
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        
        // u need to find the cells which can reach both pacific and 
        // atlantic ocean
        // instead of doing dfs for all cells and checking if it reaches both
        // the oceans - better to run dfs from outer to inner direction

        // i.e run dfs for all the edges connected to both pacific and 
        // atlantic ocean
        // maintain two visited 2d arrays for both pacific and atlantic
        // u can reach a cell inside from edge if it is connected on 4 sides
        // and the value of neighbor cell is >= current cell
        // opposite condition of going from cell to ocean as we r going from
        // ocean to the cell
        // finally loop over the visited arrays and insert values for which
        // both pacific and atlantic ocean can be visited

        rows = heights.size();
        cols = heights[0].size();
        vector<vector<bool>> pacificVisited(rows, vector<bool>(cols, false));
        vector<vector<bool>> atlanticVisited(rows, vector<bool>(cols, false));
        vector<vector<int>> result;

        // loop over the cells connected to the ocean
        // looping first and last column
        for(int r = 0; r < rows; r++) {
            dfs(r, 0, pacificVisited, heights); // check if pacific visited --> column 0 is connected to pacific
            dfs(r, cols - 1, atlanticVisited, heights); // check if atlantic visited --> column last is connected to atlantic
        }

        // looping first and last row
        for(int c = 0; c < cols; c++) {
            dfs(0, c, pacificVisited, heights); // check if pacific visited --> column 0 is connected to pacific
            dfs(rows - 1, c, atlanticVisited, heights); // check if atlantic visited --> column last is connected to atlantic
        }

        for(int r = 0; r < rows; r++) {
            for(int c = 0; c < cols; c++) {

                if(pacificVisited[r][c] && atlanticVisited[r][c])
                    result.push_back({r, c});
            }
        }

        return result;
    }
};

//------------------------------------------------------------------------------------------------

// The BFS solution uses exactly the same idea as the DFS solution.

// ## Intuition

// Instead of starting from every cell and checking if water can reach an ocean, we reverse the process.

// * Start BFS from all **Pacific border** cells.
// * Start another BFS from all **Atlantic border** cells.
// * While traversing, we can only move to a neighbor whose height is **greater than or equal to** the current cell because we are moving in the reverse direction of water flow.
// * The cells visited by **both** BFS traversals are the answer.

// ---

// ## BFS Algorithm

// 1. Create two `visited` matrices:

//    * `pacificVisited`
//    * `atlanticVisited`

// 2. Initialize two queues:

//    * Pacific queue contains

//      * first row
//      * first column
//    * Atlantic queue contains

//      * last row
//      * last column

// 3. Run BFS for Pacific.

// 4. Run BFS for Atlantic.

// 5. Cells visited in both arrays are the answer.

// ---

// ## C++ Code

class Solution {
private:
    vector<int> dr = {1, -1, 0, 0};
    vector<int> dc = {0, 0, -1, 1};
    int rows, cols;

    void bfs(queue<pair<int,int>>& q,
             vector<vector<bool>>& visited,
             vector<vector<int>>& heights) {

        while (!q.empty()) {

            auto [r, c] = q.front();
            q.pop();

            for (int i = 0; i < 4; i++) {

                int nr = r + dr[i];
                int nc = c + dc[i];

                if (nr >= 0 && nr < rows &&
                    nc >= 0 && nc < cols &&
                    !visited[nr][nc] &&
                    heights[nr][nc] >= heights[r][c]) {

                    visited[nr][nc] = true;
                    q.push({nr, nc});
                }
            }
        }
    }

public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {

        rows = heights.size();
        cols = heights[0].size();

        vector<vector<bool>> pacificVisited(rows, vector<bool>(cols, false));
        vector<vector<bool>> atlanticVisited(rows, vector<bool>(cols, false));

        queue<pair<int,int>> pacificQ;
        queue<pair<int,int>> atlanticQ;

        // Left and Right columns
        for (int r = 0; r < rows; r++) {

            pacificVisited[r][0] = true;
            pacificQ.push({r, 0});

            atlanticVisited[r][cols - 1] = true;
            atlanticQ.push({r, cols - 1});
        }

        // Top and Bottom rows
        for (int c = 0; c < cols; c++) {

            if (!pacificVisited[0][c]) {
                pacificVisited[0][c] = true;
                pacificQ.push({0, c});
            }

            if (!atlanticVisited[rows - 1][c]) {
                atlanticVisited[rows - 1][c] = true;
                atlanticQ.push({rows - 1, c});
            }
        }

        bfs(pacificQ, pacificVisited, heights);
        bfs(atlanticQ, atlanticVisited, heights);

        vector<vector<int>> result;

        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if (pacificVisited[r][c] && atlanticVisited[r][c]) {
                    result.push_back({r, c});
                }
            }
        }

        return result;
    }
};

// ---

// ## Why do we mark `visited` before pushing?

// ```cpp
// visited[nr][nc] = true;
// q.push({nr, nc});
// ```

// This ensures a cell is added to the queue **only once**.

// If we marked it after popping, multiple neighbors could push the same cell, leading to duplicate work.

// ---

// ## Time Complexity

// * Initializing border cells: **O(m + n)**
// * Pacific BFS: **O(m × n)**
// * Atlantic BFS: **O(m × n)**
// * Final traversal: **O(m × n)**

// Overall:

// **Time:** **O(m × n)**

// Each cell is visited at most once in each BFS.

// ---

// ## Space Complexity

// * Two visited arrays: **O(m × n)**
// * Queue: **O(m × n)** in the worst case

// Overall:

// **Space:** **O(m × n)**

// ---

// ### DFS vs BFS

// | DFS                                  | BFS                              |
// | ------------------------------------ | -------------------------------- |
// | Uses recursion                       | Uses queue                       |
// | Recursive stack can reach `O(m × n)` | Queue can reach `O(m × n)`       |
// | Simpler to write                     | Avoids recursion depth limits    |
// | Same time complexity: `O(m × n)`     | Same time complexity: `O(m × n)` |

// Both approaches are equally optimal for this problem; BFS is often preferred in languages where deep recursion can cause stack overflow.
