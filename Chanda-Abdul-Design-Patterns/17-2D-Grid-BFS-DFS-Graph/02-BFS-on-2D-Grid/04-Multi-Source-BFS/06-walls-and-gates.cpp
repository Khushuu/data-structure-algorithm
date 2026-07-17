// # 286. Walls and Gates (LeetCode)

// ## Problem Statement

// You are given an `m × n` 2D grid `rooms` initialized with these three possible values:

// * `-1` → A wall or obstacle.
// * `0` → A gate.
// * `INF (2147483647)` → An empty room.

// Fill each empty room with the distance to its **nearest gate**.

// If it is impossible to reach a gate, leave the room as `INF`.

// ----------------------------------------------------------------------------------------

// # Interview Takeaways

// * Since **all gates are sources**, this is a classic **Multi-Source BFS** problem.
// * BFS guarantees the first time a room is reached is via the shortest path in an unweighted grid.
// * DFS works only with careful pruning and may revisit cells multiple times, making it less efficient.
// * **Preferred solution:** **Multi-Source BFS** with **O(m × n)** time and **O(m × n)** space.

// ----------------------------------------------------------------------------------------

// ### Example

// **Input**


// [
//   [2147483647,-1,0,2147483647],
//   [2147483647,2147483647,2147483647,-1],
//   [2147483647,-1,2147483647,-1],
//   [0,-1,2147483647,2147483647]
// ]


// **Output**


// [
//   [3,-1,0,1],
//   [2,2,1,-1],
//   [1,-1,2,-1],
//   [0,-1,3,4]
// ]


// ---

// # Intuition

// Each room needs the distance to its **nearest gate**.

// A naive approach would be:

// * For every empty room, run BFS until a gate is found.
// * This would be extremely slow.

// Instead, notice:

// * We already know the starting points (all gates).
// * Run **Multi-Source BFS** by inserting every gate into the queue initially.
// * The first time a room is visited, it is guaranteed to be the shortest distance from any gate.

// ---

// # Approach 1: Multi-Source BFS (Optimal)

// ## Idea

// 1. Push all gates (`0`) into the queue.
// 2. Expand simultaneously from every gate.
// 3. Whenever an adjacent room is `INF`, update it with:


// current distance + 1


// 4. Push that room into the queue.

// Since BFS explores level by level, the first distance assigned is the shortest.

// ---

// ## Example

// Initial queue:


// Gate at (0,2)
// Gate at (3,0)


// Processing:


// Level 0:
// Gates

// Level 1:
// Neighbors become 1

// Level 2:
// Neighbors become 2

// Level 3:
// Neighbors become 3
// ...


// No room is processed twice.

// ----------------------------------------------------------------------------------------

// T.C: O(mn)
// S.C: O(mn)

// ## BFS Code (C++)


class Solution {
public:
    void wallsAndGates(vector<vector<int>>& rooms) {

        if (rooms.empty()) return;

        int rows = rooms.size();
        int cols = rooms[0].size();

        queue<pair<int,int>> q;

        // Push all gates into queue
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if (rooms[r][c] == 0)
                    q.push({r, c});
            }
        }

        vector<pair<int,int>> dr = {
            {1,0}, {-1,0}, {0,1}, {0,-1}
        };

        while (!q.empty()) {

            auto [x, y] = q.front();
            q.pop();

            for (auto &d : dr) {

                int nr = r + dr.first;
                int nc = c + dr.second;

                if (nr < 0 || nc < 0 || nr >= m || nc >= n)
                    continue;

                if (rooms[nr][nc] != INT_MAX)
                    continue;
                
                // we only process the rooms with INT_MAX
                // i.e the ones for which the distance is not yet calculate
                // distance of current room from the gate will be distance of the room that was processed earlier + 1
                rooms[nr][nc] = rooms[r][c] + 1;
                q.push({nr, nc});
            }
        }
    }
};


// ----------------------------------------------------------------------------------------


// ## BFS Dry Run

// Initial grid


// INF  -1   0  INF
// INF INF INF -1
// INF -1 INF -1
//  0  -1 INF INF


// Queue


// (0,2)
// (3,0)


// Process `(0,2)`


// INF -1 0 1
// INF INF 1 -1
// INF -1 INF -1
// 0 -1 INF INF


// Process `(3,0)`


// INF -1 0 1
// 2 INF 1 -1
// 1 -1 INF -1
// 0 -1 INF INF


// Continue until queue becomes empty.

// Final answer


// 3 -1 0 1
// 2  2 1 -1
// 1 -1 2 -1
// 0 -1 3 4


// ---

// ## Time Complexity

// Each cell enters the queue at most once.

// * **Time:** **O(m × n)**

// ## Space Complexity

// Queue may contain all cells.

// * **Space:** **O(m × n)**

// ----------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------


// # Approach 2: DFS

// Although BFS is the optimal solution, DFS can also solve this problem.

// ## Idea

// Start DFS from every gate.

// While visiting a room:

// * If the current distance is **greater than the value already stored**, stop.
// * Otherwise update the room.
// * Continue exploring.

// The pruning condition prevents unnecessary revisits.

// ---

// ## DFS Code (C++)


class Solution {
public:
    void dfs(vector<vector<int>>& rooms, int i, int j, int dist) {

        int m = rooms.size();
        int n = rooms[0].size();

        if (i < 0 || j < 0 || i >= m || j >= n)
            return;

        if (rooms[i][j] < dist)
            return;

        rooms[i][j] = dist;

        dfs(rooms, i + 1, j, dist + 1);
        dfs(rooms, i - 1, j, dist + 1);
        dfs(rooms, i, j + 1, dist + 1);
        dfs(rooms, i, j - 1, dist + 1);
    }

    void wallsAndGates(vector<vector<int>>& rooms) {
        if (rooms.empty()) return;

        int m = rooms.size();
        int n = rooms[0].size();

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (rooms[i][j] == 0) {
                    dfs(rooms, i, j, 0);
                }
            }
        }
    }
};


// ---

// ## Why does the DFS condition work?

// The key condition is:


// if (rooms[i][j] < dist)
//     return;


// Suppose a room already contains distance `3`.

// Later another DFS reaches it with distance `5`.


// Existing = 3
// New = 5


// Since `3 < 5`, the current path is worse, so we stop.

// If another DFS reaches it with distance `2`:


// Existing = 3
// New = 2


// We update:


// rooms[i][j] = 2


// and continue exploring because we've found a shorter path.

// ---

// ## DFS Time Complexity

// Let:

// * `G` = number of gates
// * `m × n` = grid size

// In the worst case, multiple DFS traversals may revisit cells before pruning.

// * **Worst-case Time:** **O(G × m × n)**

// If there are many gates, this can approach **O((m × n)²)**.

// ---

// ## DFS Space Complexity

// Recursion stack:

// * **O(m × n)** in the worst case.

// ---

// # BFS vs DFS

// | Feature                            | BFS          | DFS                            |
// | ---------------------------------- | ------------ | ------------------------------ |
// | Finds shortest distance naturally? | ✅ Yes        | ❌ Needs pruning                |
// | Starts from all gates together     | ✅ Yes        | ❌ No                           |
// | Time Complexity                    | **O(m × n)** | **O(G × m × n)** worst case    |
// | Space Complexity                   | **O(m × n)** | **O(m × n)** (recursion stack) |
// | Recommended                        | ✅ Optimal    | ⚠️ Accepted but less efficient |

// ---
