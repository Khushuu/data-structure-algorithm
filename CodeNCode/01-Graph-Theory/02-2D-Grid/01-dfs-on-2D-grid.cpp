// # DFS on a 2D Grid (C++)

// DFS (Depth First Search) is one of the most common graph traversal algorithms. A 2D grid can be treated as a graph, where:

// * Each cell is a node.
// * Each cell is connected to its neighboring cells (up, down, left, right, or sometimes all 8 directions).

// DFS explores as deep as possible before backtracking.

// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// We will not be using a code where we don't use visited array
// In that case the grid that is visited will be marked as 0 i.e grid[r][c] = 0
// instead of updating visited[r][c] = true
// but this is not correct as it modifies the input array

// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// ### Key Takeaways

// * Treat each cell as a graph node.
// * Use direction arrays (`dr`, `dc`) to move to neighbors.
// * Always check boundaries before accessing a neighbor.
// * Mark cells as visited (or modify the grid) to avoid revisiting.
// * DFS explores one path completely before backtracking.
// * Time Complexity: `O(R × C)` because each cell is processed once.
// * Space Complexity: `O(R × C)` in the worst case due to the visited array and recursion stack.

// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// # Example Grid

// ```text
// 0 1 1 0
// 1 1 0 1
// 0 1 1 1
// 1 0 0 1
// ```

// Suppose we start DFS from `(0,1)`.

// Traversal order could be:

// ```text
// (0,1)
//    ↓
// (1,1)
//    ↓
// (2,1)
//    →
// (2,2)
//    →
// (2,3)
//    ↑
// (1,3)
//    ↓
// (3,3)
// ```

// DFS continues until no unvisited neighbor exists, then backtracks.

// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// # Step 1: Movement Directions

// For a 4-direction grid:

// ```cpp
// // up, down, left, right
// int dr[] = {-1, 1, 0, 0}; // row change
// int dc[] = {0, 0, -1, 1}; // column change
// ```

// Meaning

// | Direction | Row | Column |
// | --------- | --- | ------ |
// | Up        | -1  | 0      |
// | Down      | 1   | 0      |
// | Left      | 0   | -1     |
// | Right     | 0   | 1      |

// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// # Step 2: Boundary Check

// Before moving to a neighbor:

// ```cpp
// if(newRow >= 0 &&
//    newRow < rows &&
//    newCol >= 0 &&
//    newCol < cols)
// ```

// This ensures we never access outside the grid.

// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// # Step 3: Visited Array

// Without a visited array, DFS may visit the same cell repeatedly.

// ```cpp
// vector<vector<bool>> visited(rows, vector<bool>(cols, false));
// ```

// When visiting:

// ```cpp
// visited[r][c] = true;
// ```

// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// # Complete DFS Code - WITH GLOBAL VARIABLES

#include <iostream>
#include <vector>
using namespace std;

// Global variables
vector<vector<int>> grid;
vector<vector<bool>> visited;
int rows, cols;

// 4-direction movement
int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

void dfs(int r, int c)
{
    // Mark current cell as visited
    visited[r][c] = true;

    cout << "(" << r << ", " << c << ")" << endl;

    // Explore all 4 directions
    for (int i = 0; i < 4; i++)
    {
        int R = r + dr[i];
        int C = c + dc[i];

        // Boundary + Visited + Valid Cell Check
        if (R >= 0 && R < rows &&
            C >= 0 && C < cols &&
            !visited[R][C] &&
            grid[R][C] == 1)
        {
            dfs(R, C);
        }
    }
}

int main()
{
    grid = {
        {0, 1, 1, 0},
        {1, 1, 0, 1},
        {0, 1, 1, 1},
        {1, 0, 0, 1}
    };

    rows = grid.size();
    cols = grid[0].size();

    // Initialize visited
    visited.assign(rows, vector<bool>(cols, false));

    // Start DFS from (0,1)
    dfs(0, 1);

    return 0;
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// # Complete DFS Code - WITHOUT GLOBAL VARIABLES

#include <iostream>
#include <vector>
using namespace std;

int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

void dfs(int r, int c,
         vector<vector<int>>& grid,
         vector<vector<bool>>& visited)
{
    int rows = grid.size();
    int cols = grid[0].size();

    visited[r][c] = true;

    cout << "(" << r << "," << c << ")" << endl;

    for(int i = 0; i < 4; i++)
    {
        int nr = r + dr[i];
        int nc = c + dc[i];

        if(nr >= 0 && nr < rows &&
           nc >= 0 && nc < cols &&
           !visited[nr][nc] &&
           grid[nr][nc] == 1)
        {
            dfs(nr, nc, grid, visited);
        }
    }
}

int main()
{
    vector<vector<int>> grid =
    {
        {0,1,1,0},
        {1,1,0,1},
        {0,1,1,1},
        {1,0,0,1}
    };

    int rows = grid.size();
    int cols = grid[0].size();

    vector<vector<bool>> visited(rows, vector<bool>(cols, false));

    dfs(0, 1, grid, visited);

    return 0;
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------


// # Dry Run

// Initial call:

// ```cpp
// dfs(0,1)
// ```

// Visited:

// ```text
// F T F F
// F F F F
// F F F F
// F F F F
// ```

// From `(0,1)` check:

// ### Up

// ```text
// (-1,1)
// ```

// Outside grid

// Ignore.

// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// ### Down

// ```text
// (1,1)
// ```

// Valid
// Not visited

// grid == 1

// Call DFS.

// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// ### Left

// ```text
// (0,0)
// ```

// grid = 0

// Ignore.

// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// ### Right

// ```text
// (0,2)
// ```

// grid = 1

// Will be explored after returning from `(1,1)`.

// This is the essence of DFS: go as deep as possible before exploring the next branch.

// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// # Why Does DFS Use Recursion?

// When DFS goes deeper:

// ```text
// A
// |
// B
// |
// C
// |
// D
// ```

// The function calls look like:

// ```text
// dfs(A)
//     dfs(B)
//         dfs(C)
//             dfs(D)
// ```

// After `D` finishes:

// ```text
// return to C

// return to B

// return to A
// ```

// The recursion stack automatically remembers the path.

// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// # Time Complexity

// Suppose the grid size is

// ```text
// R × C
// ```

// Total cells:

// ```text
// R * C
// ```

// Each cell is visited only once.

// Each visit checks at most 4 neighbors.

// So,

// ```text
// Time = O(R × C)
// ```

// because the constant factor (4) is ignored in Big-O notation.

// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// # Space Complexity

// ## 1. Visited Array

// ```cpp
// visited[R][C]
// ```

// takes

// ```text
// O(R × C)
// ```

// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// ## 2. Recursion Stack

// In the worst case (e.g., all cells are connected), recursion depth can reach:

// ```text
// R × C
// ```

// So,

// ```text
// Stack Space = O(R × C)
// ```

// ---

// Total auxiliary space:

// ```text
// O(R × C)
// ```

// If you modify the grid directly (for example, change visited `1`s to `0`s), you can eliminate the visited array, but the recursion stack still remains.

// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// # 8-Direction DFS

// Some problems consider diagonal neighbors too.

// ```cpp
// int dr[] = {-1,-1,-1,0,0,1,1,1};
// int dc[] = {-1,0,1,-1,1,-1,0,1};
// ```

// Now each cell has up to 8 neighbors.

// -----------------------------------------------------------------------------------------------------------------------------------------------------------

// # Common Applications of DFS on a Grid

// DFS on a 2D grid is widely used in problems such as:

// * Number of Islands (count connected groups of `1`s).
// * Flood Fill (paint all connected cells of the same color).
// * Surrounded Regions (mark regions connected to the border).
// * Count Connected Components.
// * Maximum Area of an Island.
// * Path Existence in a Maze.
// * Shortest Bridge (combined with BFS).
// * Capture Regions and many other grid traversal problems.

// -----------------------------------------------------------------------------------------------------------------------------------------------------------


