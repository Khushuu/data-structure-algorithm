// # LeetCode 733. Flood Fill

// ## Problem Statement

// You are given an `m x n` image represented by a 2D integer array `image`, where `image[i][j]` represents the color of the pixel.

// You are also given three integers:

// * `sr` → starting row
// * `sc` → starting column
// * `color` → new color

// Perform a flood fill starting from the pixel `(sr, sc)`.

// ### Rules

// * Change the color of the starting pixel.
// * Change all 4-directionally connected pixels (up, down, left, right) having the same original color as the starting pixel.
// * Return the modified image.

// --------------------------------------------------------------------------------------------------------

// # Key Interview Points

// * Save the original color before changing anything.
// * Always handle the edge case:

  
//   if (sourceColor == color)
//       return image;
  

//   Without this check, the algorithm may repeatedly revisit already-colored cells, causing an infinite loop (BFS) or infinite recursion (DFS).
// This will happen as we are not using a visited array for this 

// * Flood Fill is a classic graph traversal problem where:

//   * Each pixel is a node.
//   * Edges exist between 4-directionally adjacent pixels.
//   * BFS and DFS both correctly solve the problem by visiting each connected pixel exactly once.

// --------------------------------------------------------------------------------------------------------

// ### Example

// Input

// image = [[1,1,1],
//          [1,1,0],
//          [1,0,1]]

// sr = 1
// sc = 1
// color = 2


// Output


// [[2,2,2],
//  [2,2,0],
//  [2,0,1]]


// --------------------------------------------------------------------------------------------------------

// # Approach 1: BFS (Breadth First Search)

// ## Idea

// * Store the original color.
// * If the original color is already equal to the new color, return immediately.
// * Start from `(sr, sc)` using a queue.
// * Process one cell at a time.
// * Visit all 4 neighboring cells.
// * If a neighbor has the original color, change it to the new color and push it into the queue.
// * Continue until the queue becomes empty.

// --------------------------------------------------------------------------------------------------------

// ## BFS Algorithm

// 1. Save the starting color.
// 2. If `startingColor == color`, return image.
// 3. Push starting cell into queue.
// 4. Change its color.
// 5. While queue is not empty:

//    * Pop current cell.
//    * Visit four directions.
//    * If valid and has original color:

//      * Change color.
//      * Push into queue.
// 6. Return image.

// --------------------------------------------------------------------------------------------------------

// ## BFS C++ Code


class Solution {
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {

        int sourceColor = image[sr][sc];

        if (sourceColor == color)
            return image;

        int m = image.size();
        int n = image[0].size();

        queue<pair<int,int>> q;
        q.push({sr, sc});
        image[sr][sc] = color;

        int dr[4] = {-1, 1, 0, 0};
        int dc[4] = {0, 0, -1, 1};

        while (!q.empty()) {

            auto& [r, c] = q.front();
            q.pop();

            for (int i = 0; i < 4; i++) {

                int nr = r + dr[i];
                int nc = c + dc[i];

                if (nr >= 0 && nr < m &&
                    nc >= 0 && nc < n &&
                    image[nr][nc] == sourceColor) {

                    image[nr][nc] = color;
                    q.push({nr, nc});
                }
            }
        }

        return image;
    }
};


// --------------------------------------------------------------------------------------------------------

// ## BFS Dry Run

// Initial image

// 1 1 1
// 1 1 0
// 1 0 1

// Start = `(1,1)`

// Original color = 1

// Queue

// [(1,1)]

// Process `(1,1)`

// 2 2 1
// 2 2 0
// 1 0 1

// Queue

// (0,1), (1,0)

// Process `(0,1)`

// 2 2 2
// 2 2 0
// 1 0 1

// Queue

// (1,0), (0,0), (0,2)

// Continue until queue becomes empty.

// Final image


// 2 2 2
// 2 2 0
// 2 0 1

// --------------------------------------------------------------------------------------------------------

// ## BFS Complexity

// * Time Complexity: O(m × n)

//   * Every pixel is visited at most once.

// * Space Complexity: O(m × n)

//   * Queue may contain all pixels in the worst case.

// --------------------------------------------------------------------------------------------------------

// # Approach 2: DFS (Depth First Search)

// ## Idea

// Instead of using a queue, recursively visit neighboring cells.

// Whenever a cell:

// * is inside the grid,
// * has the original color,

// change its color and recursively visit all four directions.

// --------------------------------------------------------------------------------------------------------

// ## DFS Algorithm

// 1. Store original color.
// 2. If original color equals new color, return.
// 3. Call DFS on `(sr, sc)`.
// 4. In DFS:

//    * Check boundaries.
//    * Ignore cells with different colors.
//    * Change color.
//    * Recur in all four directions.

// --------------------------------------------------------------------------------------------------------

// // approach

// // check what is the source color store it
// // update the color of source cell to color
// // run dfs and if the grid value is same as source color
// // then update its value to color
// // and run dfs for all its adjacent rows and cols

// // if source color and color are same no need to run dfs
// // just return the solution

// // we don't need visited array 
// // as we already covered the edge case
// // we will only do traversal for the grid where grid color
// // is same as source color

// --------------------------------------------------------------------------------------------------------

// ## DFS C++ Code


class Solution {
public:
    vector<int> dr = {-1, 1, 0, 0};
    vector<int> dc = {0, 0, -1, 1};
    int rows;
    int cols;
    int sourceColor;
    int color;
    
    void dfs(int r, int c, vector<vector<int>>& image) {

        image[r][c] = color;

        for(int i = 0; i < 4; i++) {

            int nr = r + dr[i];
            int nc = c + dc[i];

            // if cell is valid
            // and its color matches source color then run dfs 
            if(nr >= 0 && nr < rows && nc >= 0 && nc < cols &&  
                image[nr][nc] == sourceColor) 
                    dfs(nr, nc, image);
        }
    } 

    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {

        this->rows = image.size();
        this->cols = image[0].size();

        this->sourceColor = image[sr][sc];
        this->color = color;

        // all will get updated to the same color
        if(sourceColor == color) 
            return image;

        // run dfs starting from the source node
        dfs(sr, sc, image);

        return image;
    }
};

--------------------------------------------------------------------------------------------------------

// ## Solution with Visited array:

class Solution {
public:
    vector<int> dr = {-1, 1, 0, 0};
    vector<int> dc = {0, 0, -1, 1};
    vector<vector<bool>> visited;
    int rows;
    int cols;
    int sourceColor;
    int color;
    
    void dfs(int r, int c, vector<vector<int>>& image) {

        visited[r][c] = true;
        image[r][c] = color;

        for(int i = 0; i < 4; i++) {

            int nr = r + dr[i];
            int nc = c + dc[i];

            // if cell is valid, not visited
            // and its color matches source color then run dfs 
            if(nr >= 0 && nr < rows && nc >= 0 && nc < cols &&  
                !visited[nr][nc] && image[nr][nc] == sourceColor) 
                    dfs(nr, nc, image);
        }
    } 

    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
        
        // check what is the source color store it
        // update the color of source cell to color
        // run dfs and if the grid value is same as source color
        // then update its value to color
        // and run dfs for all its adjacent rows and cols

        this->rows = image.size();
        this->cols = image[0].size();

        this->sourceColor = image[sr][sc];
        this->color = color;

        // all will get updated to the same color
        if(sourceColor == color) 
            return image;

        visited.assign(rows, vector<bool>(cols));

        // run dfs starting from the source node
        dfs(sr, sc, image);

        return image;
    }
};

// --------------------------------------------------------------------------------------------------------

// ## DFS Dry Run

// Starting at `(1,1)`:

// dfs(1,1)

// Changes center to `2`

// Then recursively visits

// ↑ (0,1)
// ↓ (2,1)
// ← (1,0)
// → (1,2)


// Only neighbors with original color `1` continue the recursion.

// Eventually every connected `1` is changed to `2`.

// --------------------------------------------------------------------------------------------------------

// ## DFS Complexity

// * Time Complexity: O(m × n)

//   * Each cell is visited once.

// * Space Complexity: O(m × n) (worst case)

//   * Due to the recursion stack if the entire image is one connected component.

// --------------------------------------------------------------------------------------------------------

// # BFS vs DFS

// | Feature          | BFS                   | DFS                                |
// | ---------------- | --------------------- | ---------------------------------- |
// | Data Structure   | Queue                 | Recursion / Stack                  |
// | Traversal        | Level by level        | Goes as deep as possible           |
// | Time Complexity  | O(m × n)              | O(m × n)                           |
// | Space Complexity | O(m × n)              | O(m × n) (recursion stack)         |
// | Risk             | No recursion overflow | Stack overflow on very large grids |
// | Preferred        | Large grids           | Simple recursive implementation    |

// --------------------------------------------------------------------------------------------------------


