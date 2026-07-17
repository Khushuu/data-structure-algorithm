// LeetCode 542. 01 Matrix is one of the most important Multi-Source BFS problems. It teaches a pattern that appears in many graph and grid problems.

// ----------------------------------------------------------------------------------------

// # Problem

// You are given a matrix containing only `0`s and `1`s.

// For every cell containing `1`, find the distance to the nearest 0.

// Distance is calculated using only four directions:

// * Up
// * Down
// * Left
// * Right

// ----------------------------------------------------------------------------------------

// # Pattern to Remember

// Whenever a problem asks for the shortest distance from every cell to the nearest source, and there are multiple sources (such as all `0`s, all gates, all hospitals, etc.), think of Multi-Source BFS:

// 1. Push all source cells into the queue.
// 2. Mark them as distance `0`.
// 3. Perform a single BFS.
// 4. The first time a cell is reached, you've found its shortest distance.

// ----------------------------------------------------------------------------------------

// ## Example

// Input:


// [
//  [0,0,0],
//  [0,1,0],
//  [1,1,1]
// ]


// Output:


// [
//  [0,0,0],
//  [0,1,0],
//  [1,2,1]
// ]


// Explanation:


// 1 at (2,0) → nearest 0 is (1,0) → distance = 1

// 1 at (2,1) → nearest 0 is (1,1)? No (it's 1)

// Nearest 0:
// (1,0)
// (2,2)
// (0,1)

// Minimum distance = 2


// ----------------------------------------------------------------------------------------

// # First Thought (Brute Force)

// For every `1`:

// Run BFS to find the nearest `0`.

// Suppose there are

// * `m × n` cells

// For every cell we perform BFS.

// Time:

// O((m*n)*(m*n))

// = O((mn)²)

// Too slow.

// ----------------------------------------------------------------------------------------


// # Key Observation

// Instead of asking
// > Every 1 should find a 0
// Reverse the thinking.
// Ask
// > Every 0 should spread its distance to nearby 1s.
// This changes everything.

// ----------------------------------------------------------------------------------------

// # Why Reverse the Search?

// Suppose the matrix is

// 0 1 1
// 1 1 1
// 1 1 0


// Instead of starting BFS from every `1`
// Start BFS from every `0`.
// Both zeros expand simultaneously.

// 0 →→→

// ←←← 0


// The first time a `1` is reached,
// that must be the shortest distance.
// This is exactly what Multi-Source BFS does.

// ----------------------------------------------------------------------------------------

// # What is Multi-Source BFS?
// Normally BFS starts from one source.

// Example:


// A

// ↓

// B

// ↓

// C


// Queue:


// [A]

// ----------------------------------------------------------------------------------------


// In this problem,
// every `0` is a source.

// Queue initially:

// [(0,0), (2,2), ...]

// All sources start expanding together.
// Think of dropping several stones into a pond. The waves spread outward from every stone at the same speed. A cell is first reached by the closest stone, which is why the first distance assigned is the shortest.

// ----------------------------------------------------------------------------------------

// # Algorithm

// ## Step 1

// Create

// queue<pair<int,int>> q;

// Also create answer matrix.

// Initially:

// 0 cells → distance = 0

// 1 cells → distance = -1


// Why -1?

// It means
// Not visited yet.

// ----------------------------------------------------------------------------------------

// ## Step 2

// Traverse matrix.

// If
// matrix[i][j] == 0

// Push into queue.

// Example

// 0 1 1
// 1 1 1
// 1 1 0


// Queue becomes
// [(0,0),(2,2)]


// Answer matrix

// 0 -1 -1
// -1 -1 -1
// -1 -1 0


// ----------------------------------------------------------------------------------------

// ## Step 3

// Start BFS.
// Take first element.

// (0,0)

// Visit its neighbors.

// Neighbor:

// (0,1)

// Distance becomes

// 0 + 1 = 1

// Push into queue.
// Queue:

// [(2,2),(0,1)]


// ----------------------------------------------------------------------------------------


// Next neighbor
// (1,0)

// Distance
// 1


// Queue
// [(2,2),(0,1),(1,0)]


// ----------------------------------------------------------------------------------------

// Now process
// (2,2)


// Its neighbors become
// distance = 1


// Notice something interesting.
// Both zeros are expanding at the same time.

// ----------------------------------------------------------------------------------------

// # Why is the First Distance Always Minimum?

// Suppose


// 0 . . X

// BFS expands

// Level 0
// 0

// Level 1
// 0 1

// Level 2
// 0 1 2

// Level 3
// 0 1 2 X


// The first time BFS reaches `X`
// it used the shortest possible path.
// No future path can be shorter because BFS explores level by level.
// This is the core property of BFS on an unweighted graph.

// ----------------------------------------------------------------------------------------

// # Dry Run

// Matrix


// 0 1 1
// 1 1 1
// 1 1 0


// Initially

// Queue


// [(0,0),(2,2)]


// Distance


// 0 -1 -1
// -1 -1 -1
// -1 -1 0


// ---

// Process


// (0,0)


// Update


// 0 1 -1
// 1 -1 -1
// -1 -1 0


// ---

// Process


// (2,2)


// Update


// 0 1 -1
// 1 -1 1
// -1 1 0


// ---

// Process


// (0,1)


// Update


// 0 1 2
// 1 2 1
// -1 1 0


// ---

// Process


// (1,0)


// Update


// 0 1 2
// 1 2 1
// 2 1 0


// Finished.

// ---

// # C++ Code

class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        
        // for 0 the distance of the nearest 0 is 0
        // find the distance of nearest 0 for cell with value 1
        // put all the cells in the queue
        // for each of the cell with value 1 also track the distance
        // at each step update the distance 
        // a distance of -1 means the grid is not yet visited 

        vector<int> dr = {-1, 1, 0, 0};
        vector<int> dc = {0, 0, -1, 1};

        int rows = mat.size();
        int cols = mat[0].size();

        queue<pair<int, int>> q;
        vector<vector<int>> dist(rows, vector<int>(cols, -1));

        // push all the cells with value 0 to q
        // as soon as we find a cell with value 1
        // we will update the distance grid - with distance of parent + 1
        // also update the distance for cell with value 0 to 0
        // as they are at a distance 0 from 0
        for(int r = 0; r < rows; r++) {
            for(int c = 0; c < cols; c++) {
                if(mat[r][c] == 0) {

                    dist[r][c] = 0;
                    q.push({r, c});
                }
            }
        }

        while(!q.empty()) {

            auto [r, c] = q.front();
            q.pop();

            for(int i = 0; i < 4; i++) {

                int nr = r + dr[i];
                int nc = c + dc[i];

                if(nr >= 0 && nr < rows && nc >= 0 && nc < cols &&
                    dist[nr][nc] == -1) {

                        dist[nr][nc] = dist[r][c] + 1;
                        q.push({nr, nc});
                    }
            }
        }

        return dist;
    }
};

// ----------------------------------------------------------------------------------------

// # Why do we use `dist == -1`?

// This acts as a visited marker.

// Initially:


// 0  -> already processed
// 1  -> unvisited



// dist

// 0 -1 -1
// -1 -1 -1


// When a `1` gets visited,


// dist[newRow][newCol] = dist[row][col] + 1;


// Now it is no longer `-1`.

// So it will never be added to the queue again.

// Each cell enters the queue only once.

// ---

// # Why don't we need a separate `visited` array?

// Because


// dist == -1


// already means


// Not visited


// and


// dist >= 0


// means


// Visited


// So one matrix serves both purposes.

// ---

// # Time Complexity

// Let

// * `m = rows`
// * `n = columns`

// ### Initial traversal

// We scan every cell once:


// O(m × n)


// ### BFS

// Each cell:

// * enters the queue once,
// * leaves the queue once,
// * checks four neighbors.

// So:


// O(m × n)


// Total:


// O(m × n)


// ---

// # Space Complexity

// We use:

// * Distance matrix: `O(m × n)`
// * Queue: in the worst case, it can contain up to `m × n` cells.

// Overall:


// O(m × n)


// ---

// # Why Multi-Source BFS Instead of Running BFS from Every `1`?

// Suppose there are `k` cells containing `1`.

// If you start a BFS from every `1`:

// * Each BFS may visit almost the entire matrix.
// * Time complexity becomes:


// O(k × m × n)


// In the worst case, `k ≈ m × n`, giving:


// O((m × n)²)


// With Multi-Source BFS, all `0`s are inserted into the queue at the beginning. The BFS expands outward from every `0` simultaneously, and each cell is visited only once.

// This reduces the time complexity to:


// O(m × n)


