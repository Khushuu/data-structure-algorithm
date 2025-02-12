// The n-queens puzzle is the problem of placing n queens on an n x n chessboard such that no two queens attack each other.
// Given an integer n, return all distinct solutions to the n-queens puzzle. You may return the answer in any order.

// n = 4
// result =  [[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]

// distinct solution to N-queens puzzle
// i suppose all solutions will be distinct only 
// no need for any additional check

// we will do column by column traversal
// in each column place a queen if it is valid position
// and then move to the next column
// when u reach the end of column i.e col == N that means u find right sol
// if a queen can not be placed at a position
// check the next row for that col 
// also valid or not valid solution - backtrack the queen
// remove the queen from where it was placed
// this is done as we want to explore all possible solutions

// how to maintain board 
// let's have a N * N board of type char
// when a queen is placed at a position update it with 'Q'
// when a solution is found form the vector string and push to result

// isValid method
// as we keep the queens from the left we only need to check left side
// check the left side of the row where queen will be placed
// also check the upper left diagonal and down left diagonal
// if any queen is already present it is not a valid position

// use condition c >= 0 instead of c--
// return after a solution is found
// backtracking solution 

// Time Complexity	O(N!) (Each row choice reduces options for the next row, leading to factorial complexity).
// Space Complexity	O(N^2), due to the board and result storage.

// backtracking solution with valid function to check if current position is valid or not for queen

// instead of using vector vector of char for board use string - more clear 
// --------------------------------------------------------------------------------------------------------------
class Solution {
private: 
    vector<vector<string>> result;
    int N;

    bool isValid(int &row, int &col, vector<vector<char>>& board) {

        // check left side of the row
        int r = row;
        int c = col - 1;
        while(c >= 0) {
            if(board[r][c] == 'Q') return false;
            c--;
        }

        // check left up diagonal
        r = row - 1;
        c = col - 1;
        while(r >= 0 && c >= 0) {
            if(board[r][c] == 'Q') return false;
            r--; 
            c--;
        }

        // check left down diagonal
        r = row + 1;
        c = col - 1;
        while(r < N && c >= 0) {
            if(board[r][c] == 'Q') return false;
            r++; 
            c--;
        }

        return true;
    }

    void placeQueens(int col, vector<vector<char>>& board) {

        // base condition 
        // valid solution found - form result
        if(col == N) {
            vector<string> positions;
            for(int r = 0; r < N; r++) {
                string s = "";
                for(int c = 0; c < N; c++) {
                    s += board[r][c];
                }
                positions.push_back(s);
            }
            result.push_back(positions);
            return;
        }

        // loop over all rows of given column
        // if position is valid - place queen
        // backtrack after call is done

        for(int r = 0; r < N; r++) {
            if(isValid(r, col, board)) {
                board[r][col] = 'Q';
                placeQueens(col + 1, board);
                board[r][col] = '.';
            }
        }
    }
public:
    vector<vector<string>> solveNQueens(int n) {

        N = n;
        vector<vector<char>> board(N, vector<char>(N, '.'));
        placeQueens(0, board);

        return result;
    }
};

// modifying the data type
// isValid logic stays the same
// --------------------------------------------------------------------------------------------------------------

 	void solve(int col, vector<string>& board) {
        if (col == N) { // Found a valid solution
            result.push_back(board);
            return;
        }

        for (int row = 0; row < N; row++) {
            if (isValid(row, col, board)) {
                board[row][col] = 'Q';
                solve(col + 1, board);
                board[row][col] = '.';  // Backtrack
            }
        }
    }

	vector<vector<string>> solveNQueens(int n) {
        N = n;
        vector<string> board(N, string(N, '.')); // Initialize board as vector<string>
        solve(0, board);
        return result;
    }

// --------------------------------------------------------------------------------------------------------------

// Optmized appraoch
// bactracking with set for checking the position of queen 

// ✅ 2. Optimized Backtracking (Using Hash Sets)

// Approach
// Use Hash Sets to track:
// cols: Columns where queens are placed.
// diagonal1: row + col for upper-left to bottom-right diagonal.
// diagonal2: row - col for bottom-left to top-right diagonal.
// Eliminates the need to check validity manually.


// explanation why does this work --> 
// Understanding row + col and row - col in the Set-based N-Queens Solution
// When using sets to track conflicts in the N-Queens problem, we store:

// Columns occupied: set<int> cols
// Main diagonal (\) occupied: set<int> mainDiag
// Anti-diagonal (/) occupied: set<int> antiDiag
// These diagonals are uniquely identified by:

// Main diagonal (\) → row - col
// Anti-diagonal (/) → row + col

// Why Does This Work?
// Let's break it down visually:

// 1️⃣ Main Diagonal (\) → row - col
// A main diagonal (top-left to bottom-right) consists of positions where the difference between row and column remains constant.

// Example for N = 4:

// scss
// Copy
// Edit
// (0,0)   (0,1)   (0,2)   (0,3)
// (1,0)   (1,1)   (1,2)   (1,3)
// (2,0)   (2,1)   (2,2)   (2,3)
// (3,0)   (3,1)   (3,2)   (3,3)
// Calculate row - col:

// Copy
// Edit
//  0      -1      -2      -3
//  1       0      -1      -2
//  2       1       0      -1
//  3       2       1       0

// Notice how each main diagonal has a unique row - col value.
// If we store row - col in a set, we can efficiently check if a queen already exists in that diagonal.


// 2️⃣ Anti-Diagonal (/) → row + col
// An anti-diagonal (bottom-left to top-right) consists of positions where the sum of row and column remains constant.

// Example for N = 4, computing row + col:

// Copy
// Edit
//  0      1      2      3
//  1      2      3      4
//  2      3      4      5
//  3      4      5      6

// Each anti-diagonal has a unique row + col value.
// Storing row + col in a set allows quick diagonal conflict detection.

// How Do We Use This in the Code?
// Placing a Queen
// Before placing a queen at (row, col), check:

// If col is occupied in cols
// If row - col is occupied in mainDiag
// If row + col is occupied in antiDiag
// Backtracking (Removing the Queen)
// After exploring, remove (row, col) from the sets to backtrack.

// Time Complexity	O(N!) (same as naive backtracking).
// Space Complexity	O(N) (instead of O(N^2) due to hash sets).

// --------------------------------------------------------------------------------------------------------------

#include <vector>
#include <unordered_set>
#include <string>

using namespace std;

class Solution {
private:
    vector<vector<string>> result;
    unordered_set<int> rows, diagonal, antiDiagonal;
    int N;

    void placeQueens(int col, vector<string>& board) {

        // base condition
        // reached the end 
        if(col == N) {
            result.push_back(board);
            return;
        }

        // loop over all rows of col
        for(int row = 0; row < N; row++) {

            // if not valid position - skip placing queen
            if(rows.count(row) || diagonal.count(row - col) ||
                antiDiagonal.count(row + col))
            continue;

            // place the queen and check for next col
            board[row][col] = 'Q';
            rows.insert(row);
            diagonal.insert(row - col);
            antiDiagonal.insert(row + col);

            placeQueens(col + 1, board);

            // backtrack to explore other solutions
            board[row][col] = '.';
            rows.erase(row);
            diagonal.erase(row - col);
            antiDiagonal.erase(row + col);
        }
    }

public:
    vector<vector<string>> solveNQueens(int n) {
        
        // instead of using isValid function - optimize it 
        // and use unordered set for row, diagonal and anti diagonal
        // all cells that lie in same diagonal will have row - col equal
        // all cells that lie in the same anti-diaognal will have equal row + col
        // we also have a set for row to check if that row has a queen or not

        N = n;
        vector<string> board(N, string(N, '.'));
        placeQueens(0, board);

        return result;
    }
};


// --------------------------------------------------------------------------------------------------------------

// N-Queens 2
// The n-queens puzzle is the problem of placing n queens on an n x n chessboard such that no two queens attack each other.
// Given an integer n, return the number of distinct solutions to the n-queens puzzle.

// in this problem we don't need actual configuration
// only the count of solutions is needed
// each solution or configurtion will always be unique
// so just do count++ every time u reach the end of the column
// don't use int board because int has more size than char
// board of string will be more space efficient

// Time Complexity	O(N!) (same as naive backtracking).
// Space Complexity	O(N) due to hash sets.
// --------------------------------------------------------------------------------------------------------

class Solution {
private:
    int N;
    int count; 
    unordered_set<int> rows, diagonal, antiDiagonal;

    void placeQueens(int col, vector<string>& board) {

        // base condition
        if(col == N) {
            count++;
            return;
        }

        for(int row = 0; row < N; row++) {

            if(rows.count(row) || diagonal.count(row - col) ||
                antiDiagonal.count(row + col))
            continue;

            // place queen
            board[row][col] = 'Q';
            rows.insert(row);
            diagonal.insert(row - col);
            antiDiagonal.insert(row + col);

            placeQueens(col + 1, board);

            // backtrack
            board[row][col] = '.';
            rows.erase(row);
            diagonal.erase(row - col);
            antiDiagonal.erase(row + col);
        }
    }

public:
    int totalNQueens(int n) {
        
        N = n;
        vector<string> board(N, string(N, '.'));
        placeQueens(0, board);

        return count;
    }
};

// --------------------------------------------------------------------------------------------------------