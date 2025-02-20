// Leetcode 1197: Minimum Knight Moves

// You are given a knight in an infinite chessboard, starting at (0, 0). 
// Given the coordinates (x, y), return the minimum number of moves required for the knight to reach (x, y).

// Knight's Possible Moves
// A knight in chess moves in an L-shape:

// (±2, ±1) = (2,1) (2, -1) (-2, 1) (-2, -1)
// (±1, ±2) = (1, 2) (1, -2) (-1, 2) (-1, -2)
// Since the board is infinite, negative and positive coordinates are allowed.

// 🔹 Approach: Breadth-First Search (BFS)

// Since we need the minimum number of moves, the best approach is BFS (Breadth-First Search), which finds the shortest path in an unweighted graph.

// Why BFS?
// BFS explores all possible moves level by level.
// The first time we reach (x, y), we know it's the shortest path.

// Optimizations
// Use Absolute Coordinates
// Since the board is symmetric, we can convert (x, y) → (|x|, |y|) to reduce search space.
// Use a set to track visited nodes
// This prevents cycles and redundant calculations.

// Time Complexity: O(N²)
// The BFS expands outward from (0,0).
// Each node has 8 possible moves, but due to symmetry and pruning, we only explore the necessary region.
// The worst-case scenario is around O(N²), where N is the absolute value of x or y.

// Space Complexity: O(N²)
// BFS queue and visited O(N²) set store nodes in the worst case.
// --------------------------------------------------------------------------------------------------------------

class Solution {
public:
    int minKnightMoves(int x, int y) {
        // Convert to positive coordinates (symmetry optimization)
        x = abs(x);
        y = abs(y);

        // Possible knight moves
        vector<pair<int, int>> moves = {{2, 1}, {2, -1}, {-2, 1}, {-2, -1},
                                        {1, 2}, {1, -2}, {-1, 2}, {-1, -2}};

        queue<pair<int, int>> q;
        q.push({0, 0});
        
        set<pair<int, int>> visited;
        visited.insert({0, 0});
        
        int steps = 0;

        while (!q.empty()) {
            int size = q.size();
            
            while (size--) {
                auto [curX, curY] = q.front();
                q.pop();
                
                // If we reach the target, return steps
                if (curX == x && curY == y) return steps;
                
                // Explore all possible moves
                for (auto [dx, dy] : moves) {

                    int newX = curX + dx;
                    int newY = curY + dy;

                    // Pruning: Only visit (x, y) and closer areas
                    if (!visited.count({newX, newY}) && newX >= -1 && newY >= -1) {
                        visited.insert({newX, newY});
                        q.push({newX, newY});
                    }
                }
            }
            
            steps++;
        }
        
        return -1; // Should never reach here - the knight can always reach every cell from any source
    }
};

int main() {
    Solution sol;
    cout << sol.minKnightMoves(5, 5) << endl; // Example test case
    return 0;
}
// --------------------------------------------------------------------------------------------------------------

// 🔹 Summary
// ✅ BFS is the best approach for this problem.
// ✅ Optimizations like symmetry reduction (abs(x), abs(y)) help reduce the search space.
// ✅ Pruning avoids unnecessary visits and improves efficiency.

// NOTE:

// 🔹 Why newX >= -1 && newY >= -1 Instead of >= 0?

// Edge Cases for BFS Expansion
// The knight moves in an L-shape, meaning it can jump over (0,0).
// Some moves can take the knight into negative coordinates before reaching positive ones.
// If we use >= 0, we might block valid paths, delaying reaching the target (x, y).

// Symmetry Optimization Still Requires Some Negative Region
// While we convert (x, y) to (|x|, |y|), the BFS can still pass through small negative values temporarily.
// Allowing -1 ensures we don’t cut off a valid shortest path.

// 🔹 Example Where >= 0 Would Fail

// Imagine reaching (1,1), and the BFS expands.
//  One of the knight's moves can go to (-1,2). If we force >= 0, this move is blocked, making the knight take extra moves instead of the shortest path.

// (0,0) → (1,2) → (-1,2)  ✅ (Allowed with `>= -1`)
// If we restrict to >= 0, the knight must detour, leading to suboptimal paths.

// 🔹 Why >= -1 and Not Lower?
// >= -1 provides enough flexibility while still preventing unnecessary expansion into deep negative values.
// In the worst case, (-1,-1) still connects to useful nodes while avoiding excessive branching.