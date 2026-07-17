// 463. Island Perimeter
// VERY VERY IMPORTANT PROBLEM

// given a 2D grid of size N x M
// find the perimeter of the island

// land cells are represented by 1 and water cells are represented by 0

// NOTE: alway mark the note visited when processing the neighbor nodes and before pushing them into the queue
// NOTE: use auto [r,c] = q.front(); // otherwise the garbage collector will give error due to unused references of r, c

//---------------------------------------------------------------------------------------------------------------

// approach
// for each cell check if you can visit each side
// if you can not visit a connected side 
// then that will contribute to the parameter
// and if you can then the adjacent cell may or may not contribute
// to the final parameter

// so we need to check if the adjacent cell is 
// valid or not
// if cell is already visited skip it 
// if either the adjacent cell is invalid - i.e it is at the corner
// or the edge and no more movement can happen 
// or the adjacent cell is water then also 
// it is kind of no man's land and will contribute to the result

// bfs seems more intuitive will use that

//---------------------------------------------------------------------------------------------------------------

// Time Complexity: O(N*M)
// Space Complexity: O(N*M)

//---------------------------------------------------------------------------------------------------------------

// NOT THE BEST APPROACH - CHECK OTHER CODE 

class Solution {
public:
    int islandPerimeter(vector<vector<int>>& grid) {

        vector<int> dr = {-1, 1, 0, 0};
        vector<int> dc = {0, 0, -1, 1};

        int rows = grid.size();
        int cols = grid[0].size();

        vector<vector<bool>> visited(rows, vector<bool>(cols, false));
        queue<pair<int, int>> q;
        int sr = 0;
        int sc = 0;
        int count = 0;

        // find the source from where to start
        for(int r = 0; r < rows; r++) {
            for(int c = 0; c < cols; c++) {
               
                if(grid[r][c] == 1) {
                    
                    sr = r;
                    sc = c;
                    break;
                }
            }
        }

        q.push({sr, sc});
        visited[sr][sc] = true;
        
        while(!q.empty()) {

            auto [r, c] = q.front();
            q.pop();

            for(int i = 0; i < 4; i++) {

                int nr = r + dr[i];
                int nc = c + dc[i];
                
                // if cell is invalid no further movement for that edge 
                // is possible
                // it contributes to the perimeter
                // if cell is water - then also it will contribute
                if(nr < 0 || nr >= rows || nc < 0 || nc >= cols ||
                    grid[nr][nc] == 0) {
                    count++;
                    continue;
                }

                // if already visited we would have done the calculations
                if(!visited[nr][nc]) {

                    visited[nr][nc] = true;
                    q.push({nr, nc});
                }
            }
        }

        return count;
    }
};

//---------------------------------------------------------------------------------------------------------------

// Better approach

// LeetCode **463. Island Perimeter** is a very common grid traversal problem. The key is to realize that **you don't actually need DFS/BFS** because there is **exactly one island** and **no lakes** (water inside the island).

// //---------------------------------------------------------------------------------------------------------------

// # Problem

// You are given a grid where:

// * `1` = land
// * `0` = water

// Find the **perimeter** of the island.

// Example:

// ```text
// grid =
// [
//  [0,1,0,0],
//  [1,1,1,0],
//  [0,1,0,0],
//  [1,1,0,0]
// ]
// ```

// Output:

// ```text
// 16
// ```

//---------------------------------------------------------------------------------------------------------------

// # Observation

// Imagine a **single land cell**.

// ```text
// 1
// ```

// It has **4 sides**, so perimeter = **4**.

// Now suppose two land cells touch each other.

// ```text
// 1 1
// ```

// Initially:

// ```
// 4 + 4 = 8
// ```

// But they share one edge.

// ```text
//  -----
// |  |  |
//  -----
// ```

// The shared edge is counted twice.

// So:

// ```
// 8 - 2 = 6
// ```

// **Rule:**

// * Every land cell contributes **4**
// * Every shared edge removes **2**

//---------------------------------------------------------------------------------------------------------------

// # Approach 1 (Most Efficient)

// Traverse every cell.

// For each land cell:

// 1. Add `4`.
// 2. Check only **right** neighbor.
// 3. Check only **down** neighbor.

// Why only right and down?

// Because checking left/right or up/down together would count the same shared edge twice.

//---------------------------------------------------------------------------------------------------------------


// ## Dry Run

// Grid:

// ```text
// 1 1
// 1 1
// ```

// ### Cell (0,0)

// ```
// perimeter = 4
// ```

// Right is land

// ```
// 4 - 2 = 2
// ```

// Down is land

// ```
// 2 - 2 = 0
// ```

// Current perimeter = 0

//---------------------------------------------------------------------------------------------------------------

// ### Cell (0,1)

// ```
// +4 = 4
// ```

// Down is land

// ```
// 4 - 2 = 2
// ```

//---------------------------------------------------------------------------------------------------------------

// ### Cell (1,0)

// ```
// +4 = 6
// ```

// No right land? Actually yes.

// ```
// 6 - 2 = 4
// ```

//---------------------------------------------------------------------------------------------------------------

// ### Cell (1,1)

// ```
// +4 = 8
// ```

// Final answer:

// ```
// 8
// ```

// Correct.

//---------------------------------------------------------------------------------------------------------------

// # Algorithm

// ```
// perimeter = 0

// for every cell

//     if land

//         perimeter += 4

//         if right is land
//             perimeter -= 2

//         if down is land
//             perimeter -= 2

// return perimeter
// ```

//---------------------------------------------------------------------------------------------------------------

// # C++ Code

// we only check right and down because we don't want to count the same edge twice
// when we move on to the right cell we don't want to check the left cell else if will calculate the result again
// for the same shared edge which is incorrect 
// and when we move down we don't want to check the top cell
// else if will calculate the result again

class Solution {
public:
    int islandPerimeter(vector<vector<int>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();

        int perimeter = 0;

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {

                if (grid[i][j] == 1) {
                    perimeter += 4;

                    // Check right
                    if (j + 1 < cols && grid[i][j + 1] == 1)
                        perimeter -= 2;

                    // Check down
                    if (i + 1 < rows && grid[i + 1][j] == 1)
                        perimeter -= 2;
                }
            }
        }

        return perimeter;
    }
};

//---------------------------------------------------------------------------------------------------------------

// # Time Complexity

// Let

// * `m = rows`
// * `n = columns`

// We visit every cell exactly once.

// ```
// Time = O(m × n)
// ```

//---------------------------------------------------------------------------------------------------------------

// # Space Complexity

// We only use a few integer variables.

// ```
// Space = O(1)
// ```

//---------------------------------------------------------------------------------------------------------------

// # Why subtract only 2?

// Suppose two adjacent land cells exist.

// ```text
// 1 1
// ```

// Each contributes 4:

// ```
// 4 + 4 = 8
// ```

// Their common edge is internal, so it should not contribute to the perimeter.

// That edge was counted twice (once by each cell), so remove **2**.

// ```
// 8 - 2 = 6
// ```

//---------------------------------------------------------------------------------------------------------------

// # Alternative Approach (Checking All Four Directions)

// Another intuitive solution is to inspect each land cell's four neighbors. For every side that is either:

// * outside the grid, or
// * water,

// add `1` to the perimeter.


class Solution {
public:
    int islandPerimeter(vector<vector<int>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();
        int perimeter = 0;

        int dr[4] = {-1, 1, 0, 0};
        int dc[4] = {0, 0, -1, 1};

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {

                if (grid[i][j] == 1) {

                    for (int k = 0; k < 4; k++) {
                        int nr = i + dr[k];
                        int nc = j + dc[k];

                        if (nr < 0 || nr >= rows ||
                            nc < 0 || nc >= cols ||
                            grid[nr][nc] == 0)
                            perimeter++;
                    }
                }
            }
        }

        return perimeter;
    }
};

// ### Complexity

// * **Time:** `O(m × n)`
// * **Space:** `O(1)`

// //---------------------------------------------------------------------------------------------------------------

// ## Which approach is better?

// For interviews, the **first approach (4 per land cell, subtract 2 for right/down neighbors)** is often preferred because it's concise and avoids checking all four directions. The second approach is also correct and can be easier to understand because it directly counts exposed edges. Both have the same **O(m × n)** time and **O(1)** extra space complexity.

