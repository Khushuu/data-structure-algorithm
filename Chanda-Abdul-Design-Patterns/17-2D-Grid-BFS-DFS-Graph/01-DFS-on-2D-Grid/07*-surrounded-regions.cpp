// # 130. Surrounded Regions (LeetCode)

// ## Problem Statement

// You are given an `m × n` board containing characters:

// * `'X'` → Blocked cell
// * `'O'` → Open cell

// A region is formed by connecting adjacent `'O'` cells (up, down, left, right).

// A region is **captured** if it is **completely surrounded by `'X'`**.

// Your task is to modify the board **in-place** by:

// * Converting all captured `'O'` cells into `'X'`.
// * Leaving all `'O'` cells that are connected to the boundary unchanged.

// ---

// ## Example

// ### Input

// ```text
// X X X X
// X O O X
// X X O X
// X O X X
// ```

// ### Output

// ```text
// X X X X
// X X X X
// X X X X
// X O X X
// ```

// ### Explanation

// The top-middle region is completely surrounded, so it becomes `'X'`.

// The bottom `'O'` is connected to the boundary, so it cannot be captured.

// ---

// # Intuition

// A common mistake is:

// > "Start DFS/BFS from every `'O'` and check whether it reaches the boundary."

// This works but repeats the same work many times.

// Instead, think in reverse.

// ### Observation

// Only `'O'` cells connected to the **boundary** are safe.

// Everything else must be captured.

// So,

// 1. Start from all boundary `'O'`.
// 2. Mark every connected `'O'` as **safe**.
// 3. Convert all remaining `'O'` to `'X'`.
// 4. Convert safe cells back to `'O'`.

// This is much more efficient.

// ---

// # Interview Takeaways

// * The key insight is **not** to search every `'O'` region individually.
// * Instead, identify the `'O'` cells that **cannot** be captured by starting from the boundary.
// * Mark all boundary-connected `'O'` cells as safe, then flip the remaining `'O'` cells.
// * Both DFS and BFS achieve **O(m × n)** time complexity, with DFS using recursion and BFS using an explicit queue.


// ---

// # Approach 1: DFS

// ## Algorithm

// ### Step 1

// Visit every boundary cell.

// If it is `'O'`, start DFS.

// ### Step 2

// During DFS,

// Mark every reachable `'O'` as

// ```text
// '#'
// ```

// which means **safe**.

// ### Step 3

// Traverse the board again.

// * `'O'` → `'X'`
// * `'#'` → `'O'`

// ---

// ## Example

// Initial board

// ```text
// X X X X
// X O O X
// X X O X
// X O X X
// ```

// Boundary DFS starts from

// ```text
// (3,1)
// ```

// Mark safe

// ```text
// X X X X
// X O O X
// X X O X
// X # X X
// ```

// Now convert

// Remaining `'O'`

// ```text
// X X X X
// X X X X
// X X X X
// X # X X
// ```

// Restore

// ```text
// X X X X
// X X X X
// X X X X
// X O X X
// ```

// ---

// # DFS Code (C++)

class Solution {
public:
    int rows;
    int cols;
    vector<int> dr = {-1, 1, 0, 0};
    vector<int> dc = {0, 0, -1, 1};

    bool isEdge(int r, int c, int rows, int cols) {
        return r == 0 || r == rows - 1 || c == 0 || c == cols - 1;
    }

    void dfs(int r, int c, vector<vector<char>>& board) {

        // mark the cell as safe
        board[r][c] = '#';

        for(int i = 0; i < 4; i++) {

            int nr = r + dr[i];
            int nc = c + dc[i];

            if(nr >= 0 && nr < rows && nc >= 0 && nc < cols &&
                board[nr][nc] == 'O') {
                    dfs(nr, nc, board);
                }
        }
    }

    void solve(vector<vector<char>>& board) {
        
        // dfs
        // connected components
        // loop over all cells of the matrix
        // if it is 'O' convert to x
        // and run dfs for its neighbor 'O'

        // if for the connected component we find any of the edge with 
        // 'O' on the edge we should backtrack

        if(board.empty()) return;

        rows = board.size();
        cols = board[0].size();

        // we can not caputre regions on the edge of the board
        // so traverse them and mark them safe
        for(int r = 0; r < rows; r++) {
            for(int c = 0; c < cols; c++) {

                if(isEdge(r, c, rows, cols) && board[r][c] == 'O')
                    dfs(r, c, board);
            }
        }

        // mark safe regions back to O
        // and O to captured reagions
        for(int r = 0; r < rows; r++) {
            for(int c = 0; c < cols; c++) {
                
                // order matters here
                // otherwise the O marked cells will again be marked as X
                if(board[r][c] == 'O') board[r][c] = 'X';
                if(board[r][c] == '#') board[r][c] = 'O';
            }
        }
    }
};

// ---

// ## DFS Dry Run

// Initial

// ```text
// X X X X
// X O O X
// X X O X
// X O X X
// ```

// Boundary DFS

// ```text
// Visit (3,1)
// ```

// Mark safe

// ```text
// X X X X
// X O O X
// X X O X
// X # X X
// ```

// Convert remaining

// ```text
// X X X X
// X X X X
// X X X X
// X # X X
// ```

// Restore

// ```text
// X X X X
// X X X X
// X X X X
// X O X X
// ```

// ---

// ## Time Complexity

// Every cell is visited at most once.

// **Time:** **O(m × n)**

// ## Space Complexity

// Recursive stack may contain all cells.

// **Space:** **O(m × n)** (worst case)

// ---

// # Approach 2: BFS

// Instead of recursion, we can use a queue.

// ## Algorithm

// 1. Push every boundary `'O'` into the queue.
// 2. Mark them as `'#'`.
// 3. Perform BFS.
// 4. Mark every connected `'O'` as safe.
// 5. Finally

// * `'O' → 'X'`
// * `'#' → 'O'`

// ---

// ## BFS Code (C++)

// ```cpp
class Solution {
public:
    void solve(vector<vector<char>>& board) {

        if (board.empty()) return;

        int m = board.size();
        int n = board[0].size();

        queue<pair<int,int>> q;

        // First & Last column
        for (int i = 0; i < m; i++) {

            if (board[i][0] == 'O') {
                q.push({i,0});
                board[i][0] = '#';
            }

            if (board[i][n-1] == 'O') {
                q.push({i,n-1});
                board[i][n-1] = '#';
            }
        }

        // First & Last row
        for (int j = 0; j < n; j++) {

            if (board[0][j] == 'O') {
                q.push({0,j});
                board[0][j] = '#';
            }

            if (board[m-1][j] == 'O') {
                q.push({m-1,j});
                board[m-1][j] = '#';
            }
        }

        vector<pair<int,int>> dir = {
            {1,0},{-1,0},{0,1},{0,-1}
        };

        while (!q.empty()) {

            auto [x,y] = q.front();
            q.pop();

            for (auto &d : dir) {

                int nx = x + d.first;
                int ny = y + d.second;

                if (nx < 0 || ny < 0 || nx >= m || ny >= n)
                    continue;

                if (board[nx][ny] != 'O')
                    continue;

                board[nx][ny] = '#';
                q.push({nx,ny});
            }
        }

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                if (board[i][j] == 'O')
                    board[i][j] = 'X';

                else if (board[i][j] == '#')
                    board[i][j] = 'O';
            }
        }
    }
};
// ```

// ---

// ## BFS Dry Run

// Initial Queue

// ```text
// (3,1)
// ```

// Process

// ```text
// Mark all boundary-connected cells as '#'
// ```

// Board

// ```text
// X X X X
// X O O X
// X X O X
// X # X X
// ```

// Convert

// ```text
// Remaining O -> X
// ```

// Restore

// ```text
// # -> O
// ```

// Final

// ```text
// X X X X
// X X X X
// X X X X
// X O X X
// ```

// ---

// # Why Start from the Boundary?

// Suppose we have:

// ```text
// X X X X
// X O O X
// X X O X
// X O X X
// ```

// If you start from every interior `'O'`, you'll repeatedly explore the same regions.

// Instead, by starting only from the boundary:

// * Every `'O'` reachable from the boundary is marked as **safe**.
// * Any `'O'` left unmarked must be completely enclosed by `'X'` and should be flipped.

// This reverse-thinking approach visits each cell only once and leads to an optimal **O(m × n)** solution.

// ---

// # DFS vs BFS

// | Feature          | DFS                                 | BFS                    |
// | ---------------- | ----------------------------------- | ---------------------- |
// | Traversal        | Recursive                           | Queue                  |
// | Time Complexity  | **O(m × n)**                        | **O(m × n)**           |
// | Space Complexity | **O(m × n)** (recursion stack)      | **O(m × n)** (queue)   |
// | Risk             | Stack overflow on very large boards | No recursion risk      |
// | Preferred        | Simple and concise                  | Safer for large inputs |

