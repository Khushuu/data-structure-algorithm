// # 695. Max Area of Island (LeetCode)

// ## Problem Statement

// You are given an `m x n` binary matrix `grid` where:

// * `1` represents land.
// * `0` represents water.

// An **island** is formed by connecting adjacent lands **horizontally or vertically** (not diagonally).

// Return the **maximum area** of an island in the grid. If there is no island, return `0`.

// ### Example

// ```text
// Input:
// grid = [
//  [0,0,1,0,0],
//  [1,1,1,0,1],
//  [0,1,0,0,1],
//  [0,0,0,1,1]
// ]

// Output: 5
// ```
// -----------------------------------------------------------------------------------------------------------------

// # Interview Takeaways

// * Model each island as a connected component in a graph.
// * Traverse each connected component using either **DFS** or **BFS**.
// * Mark cells as visited (or use a separate `visited` array) to ensure each cell is processed only once.
// * The overall optimal complexity is:

//   * **Time:** `O(m × n)`
//   * **Space:** `O(m × n)` (worst case)

// -----------------------------------------------------------------------------------------------------------------

// # Approach 1: DFS (Optimal)

// ## Idea

// * Traverse every cell.
// * Whenever we find an unvisited land (`1`), start a **Depth First Search (DFS)**.
// * Count all connected land cells.
// * Keep updating the maximum area.

// We mark visited cells by changing `1 → 0` to avoid revisiting. - no we use a visited 2d array

// -----------------------------------------------------------------------------------------------------------------

// ## DFS Code (C++)

class Solution {
public:
    int rows;
    int cols;
    vector<vector<bool>> visited;
    vector<int> dr = {-1, 1, 0, 0};
    vector<int> dc = {0, 0, -1, 1};

    void dfs(int& r, int& c, int& size, vector<vector<int>>& grid) {

        visited[r][c] = true;
        size++;

        for(int i = 0; i < 4; i++) {

            int nr = r + dr[i];
            int nc = c + dc[i];

            // valid cell & not visited & is land
            if(nr >= 0 && nr < rows && nc >= 0 && nc < cols &&
                !visited[nr][nc] &&
                grid[nr][nc] == 1) {
                    dfs(nr, nc, size, grid);
                }
        }
    }

    int maxAreaOfIsland(vector<vector<int>>& grid) {
        
        // here along with iterating over the connected components
        // we need to track the size of each connected component
        // and return the maximum as result

        rows = grid.size();
        cols = grid[0].size();

        visited.assign(rows, vector<bool>(cols, false));

        int result = 0;

        for(int r = 0; r < rows; r++) {
            for(int c = 0; c < cols; c++) {

                if(!visited[r][c] && grid[r][c] == 1) {
                    
                    int size = 0;
                    dfs(r, c, size, grid);

                    result = max(result, size);
                }
            }
        }

        return result;
    }
};

// -----------------------------------------------------------------------------------------------------------------

// ## DFS Complexity

// * **Time:** `O(m × n)`

//   * Every cell is visited only once.

// * **Space:** `O(m × n)` (worst case recursion stack if the whole grid is land)

// -----------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------


// # Approach 2: BFS

// ## Idea

// Instead of recursion, use a **queue**.

// Whenever a land cell is found:

// 1. Push it into the queue.
// 2. Pop one cell.
// 3. Visit its 4 neighbors.
// 4. Count the area.
// 5. Repeat until the queue becomes empty.

// -----------------------------------------------------------------------------------------------------------------

// ## BFS Code (C++)

// ## Without using a visited array and modifying the grid - not advised

// ```cpp
class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        int ans = 0;

        vector<pair<int, int>> dir = {
            {1, 0}, {-1, 0}, {0, 1}, {0, -1}
        };

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                if (grid[i][j] == 1) {

                    queue<pair<int, int>> q;
                    q.push({i, j});
                    grid[i][j] = 0;

                    int area = 0;

                    while (!q.empty()) {

                        auto [x, y] = q.front();
                        q.pop();
                        area++;

                        for (auto &d : dir) {
                            int nx = x + d.first;
                            int ny = y + d.second;

                            if (nx >= 0 && ny >= 0 &&
                                nx < m && ny < n &&
                                grid[nx][ny] == 1) {

                                grid[nx][ny] = 0;
                                q.push({nx, ny});
                            }
                        }
                    }

                    ans = max(ans, area);
                }
            }
        }

        return ans;
    }
};
// ```

// -----------------------------------------------------------------------------------------------------------------


// ## BFS Complexity

// * **Time:** `O(m × n)`
// * **Space:** `O(m × n)` (queue can hold all land cells in the worst case)

// -----------------------------------------------------------------------------------------------------------------

// # Why Time Complexity is `O(m × n)`?

// Suppose the grid has:

// * `m` rows
// * `n` columns

// Total cells = `m × n`

// Although DFS/BFS explores neighbors, **each land cell is visited exactly once** because it is marked as visited (`grid[i][j] = 0`) immediately after being processed.

// Therefore,

// ```
// Total work = Number of cells
//            = O(m × n)
// ```

// -----------------------------------------------------------------------------------------------------------------

// # Why Space Complexity is `O(m × n)`?

// In the worst case:

// ```
// 1 1 1
// 1 1 1
// 1 1 1
// ```

// The entire grid is one island.

// * **DFS:** recursion stack may contain all `m × n` cells.
// * **BFS:** queue may also hold up to `m × n` cells.

// Hence,

// ```
// Space = O(m × n)
// ```

// ---

// # Which Solution is Better?

// | Approach        | Time       | Space      | Notes                                               |
// | --------------- | ---------- | ---------- | --------------------------------------------------- |
// | DFS (Recursive) | `O(m × n)` | `O(m × n)` | Shorter and easier to write                         |
// | BFS             | `O(m × n)` | `O(m × n)` | Avoids recursion stack overflow on very large grids |


