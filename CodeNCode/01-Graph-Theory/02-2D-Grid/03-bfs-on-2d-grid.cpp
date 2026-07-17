// # Problem Statement

// You are given a 2D grid of size N × M and a source cell `(sr, sc)`. Your task is to find the shortest distance from the source cell to every other cell in the grid.

// You can move in 4 directions:

// * Up
// * Down
// * Left
// * Right

// Each move has a cost of 1.

// Return a 2D matrix `dist` where `dist[i][j]` represents the minimum number of moves required to reach cell `(i, j)` from the source.

// ---------------------------------------------------------------------------------------------

// # Key Points

// NOTE: alway mark the note visited when processing the neighbor nodes and before pushing them into the queue
// NOTE: use auto [r,c] = q.front(); // otherwise the garbage collector will give error due to unused references of r, c

// * Use BFS when all edges (moves) have equal weight.
// * Each cell is visited only once.
// * The first distance assigned to a cell is its shortest distance from the source.
// * This approach is widely used in grid problems involving shortest paths with uniform movement costs.

// ---------------------------------------------------------------------------------------------

// ## Example

// ### Input


// Grid Size: 3 x 4

// Source = (1, 1)


// ### Output


// 2 1 2 3
// 1 0 1 2
// 2 1 2 3


// ---------------------------------------------------------------------------------------------

// # Approach (BFS)

// Since every move has the same cost (1), Breadth First Search (BFS) always visits cells in increasing order of distance.

// ### Steps

// 1. Create a distance matrix initialized with `-1`.
// 2. Put the source cell into a queue.
// 3. Mark its distance as `0`.
// 4. While the queue is not empty:

//    * Pop the front cell.
//    * Visit all four neighboring cells.
//    * If a neighbor is inside the grid and not visited:

//      * Set its distance = current distance + 1.
//      * Push it into the queue.
// 5. Return the distance matrix.

// ---------------------------------------------------------------------------------------------

// Time Complexity: O(N × M)
// Space Complexity = O(N × M)

// ---------------------------------------------------------------------------------------------

// Using Visited Array:


#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<vector<int>> shortestDistance(int rows, int cols, int sr, int sc) {

    vector<vector<int>> dist(rows, vector<int>(cols, -1));
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));

    queue<pair<int, int>> q;

    q.push({sr, sc});
    visited[sr][sc] = true;
    dist[sr][sc] = 0;

    // Up, Down, Left, Right
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    while (!q.empty()) {

        auto [r, c] = q.front();
        q.pop();

        for (int i = 0; i < 4; i++) {

            int nr = r + dr[i];
            int nc = c + dc[i];

            // Valid and not visited
            if (nr >= 0 && nr < rows &&
                nc >= 0 && nc < cols &&
                !visited[nr][nc]) {

                visited[nr][nc] = true;
                dist[nr][nc] = dist[r][c] + 1;
                q.push({nr, nc});
            }
        }
    }

    return dist;
}

int main() {

    int rows = 3, cols = 4;
    int sr = 1, sc = 1;

    vector<vector<int>> result = shortestDistance(rows, cols, sr, sc);

    for (auto &row : result) {
        for (int x : row)
            cout << x << " ";
        cout << endl;
    }

    return 0;
}

// ---------------------------------------------------------------------------------------------

// Without using visited array

// # C++ Solution


#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<vector<int>> shortestDistance(int rows, int cols, int sr, int sc) {

    vector<vector<int>> dist(rows, vector<int>(cols, -1));
    queue<pair<int, int>> q;
    q.push({sr, sc});
    dist[sr][sc] = 0;

    // up, down, left, right
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    while (!q.empty()) {

        auto& [r, c] = q.front();
        q.pop();

        for (int i = 0; i < 4; i++) {

            int nr = r + dr[i];
            int nc = c + dc[i];
            
            // check that the cell is valid - inside the grid and not visited
            if (nr >= 0 && nr < rows &&
                nc >= 0 && nc < cols &&
                dist[nr][nc] == -1) {

                dist[nr][nc] = dist[r][c] + 1;
                q.push({nr, nc});
            }
        }
    }

    return dist;
}

int main() {
    int rows = 3, cols = 4;
    int sr = 1, sc = 1;

    vector<vector<int>> result = shortestDistance(rows, cols, sr, sc);

    for (auto &row : result) {
        for (int num : row)
            cout << num << " ";
        cout << endl;
    }

    return 0;
}


// ---------------------------------------------------------------------------------------------


// # Dry Run

// Suppose

// N = 3, M = 4

// Source = (1,1)

// Initially,

// Distance Matrix

// -1 -1 -1 -1
// -1  0 -1 -1
// -1 -1 -1 -1

// Queue:
// (1,1)


// ### Step 1

// Pop `(1,1)`

// Visit:

// * `(0,1)` → distance = 1
// * `(2,1)` → distance = 1
// * `(1,0)` → distance = 1
// * `(1,2)` → distance = 1

// Queue:

// (0,1)
// (2,1)
// (1,0)
// (1,2)


// Distance matrix

// -1 1 -1 -1
// 1  0 1 -1
// -1 1 -1 -1


// ---------------------------------------------------------------------------------------------


// ### Step 2

// Pop `(0,1)`

// New cells:

// (0,0) = 2
// (0,2) = 2

// Queue

// (2,1)
// (1,0)
// (1,2)
// (0,0)
// (0,2)


// ---------------------------------------------------------------------------------------------

// Continue similarly until all cells are visited.

// Final answer


// 2 1 2 3
// 1 0 1 2
// 2 1 2 3


// ---------------------------------------------------------------------------------------------

// # Why BFS Works

// BFS explores nodes level by level.

// * Level 0 → Source
// * Level 1 → Cells at distance 1
// * Level 2 → Cells at distance 2
// * and so on.

// Since each move costs 1, the first time a cell is reached is guaranteed to be through the shortest path.

// ---------------------------------------------------------------------------------------------

// # Time Complexity

// Let:

// * N = number of rows
// * M = number of columns

// Each cell is:

// * inserted into the queue once,
// * removed once,
// * and its four neighbors are checked.

// Therefore,

// Time Complexity: O(N × M)


// ---------------------------------------------------------------------------------------------

// # Space Complexity

// The algorithm uses:

// * Distance matrix → `O(N × M)`
// * Queue (in the worst case) → `O(N × M)`

// Hence,


// Space Complexity = O(N × M)

// ---------------------------------------------------------------------------------------------
