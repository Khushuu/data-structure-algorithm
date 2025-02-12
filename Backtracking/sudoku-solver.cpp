// before solving the actual sudoku solver problem 
// lets solve this problem first 36. Valid sudoku

// determine if 9 x 9 Sudoku board is valid
// Only the filled cells need to be validated, the cell can either have char digit or be empty '.'

// same digit should not be present in a row, col or grid 

// check if the cells filled are valid or not 
// a digit should not be repeated in the same row
// not in same column and nor in same grid of 3 * 3

// Approach
// have a vector of unordered set for each row, col and grid
// loop over the board
// if the char already exist in rth row or cth col return false
// 9 grids are possible 
// how do u find the correct grid number based on r, c
// index of grid to be checked ((r / 3) * 3 + (col / 3))

// one more condition -- only check the cells where digit is present
// for . just continue

// 36. Valid Sudoku
// ----------------------------------------------------------------------------------------------------

class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        
        int n = board.size();
        vector<unordered_set<char>> row(n);
        vector<unordered_set<char>> col(n);
        vector<unordered_set<char>> grid(n);

        for(int r = 0; r < n; r++) {
            for(int c = 0; c < n; c++) {
                
                // if not a filled cell - skip check
                if(board[r][c] == '.') continue;

                // if already present in row, col or grid return false
                char digit = board[r][c];
                int index = ((r / 3) * 3 + (c / 3));
                if(row[r].count(digit) || 
                    col[c].count(digit) || 
                    grid[index].count(digit)) {
                    return false;
                }
                
                // otherwise insert char in row, col and grid
                row[r].insert(digit);
                col[c].insert(digit);
                grid[index].insert(digit);
            }
        }

        return true;
    }
};

// 37. Sudoku solver
// ----------------------------------------------------------------------------------------------------

// Approach

// We r going to use same sets for tracking if the char is present or not 
// keep modifying the given board
// have a method that returns true if the board can be solved 
// it is guaranteed that a solution exists
// if we do not find a solution for the choices made backtrack

// for each empty cell we can fill a number between 1 to 9
// check if this number can be placed in the cell or not
// if the same number is not present in the row, col or grid
// it can be placed in the selected cell

// isValid function
// instead of looping over the cells row and col and grid every time
// maintain an unordered set for each row, col and grid 
// for quick lookup
// initially fill all the chars in the rows col and grid

// try each choice from 1 to 9 for the cell
// row by row traversal 
// if u reach the end of the col i.e col == n then call for next row
// and return 
// if u reach the end of the row i.e row == n that means all cell 
// are traversed, in this case return true

// Time complexity:	O(9^m)- where m is the number of free cells
// Space complexity: O(1) (81 elements)

// ----------------------------------------------------------------------------------------------------
class Solution {
private:
    vector<unordered_set<char>> rowSet;
    vector<unordered_set<char>> colSet;
    vector<unordered_set<char>> gridSet;

    bool solve(int row, int col, vector<vector<char>>& board) {

        if(row == 9) return true;
        if(col == 9) return solve(row + 1, 0, board);
        // skip filled cells
        if (board[row][col] != '.') return solve(row, col + 1, board); 

        int index = (row / 3) * 3 + (col / 3);

        for(char digit = '1'; digit <= '9'; digit++) {
			
			// not a valid digit to be placed in the cell
            if(rowSet[row].count(digit) || colSet[col].count(digit) || gridSet[index].count(digit)) 
                continue; 

            // place digit 
            board[row][col] = digit;
            rowSet[row].insert(digit);
            colSet[col].insert(digit);
            gridSet[index].insert(digit);

            if(solve(row, col + 1, board)) return true;

            // backtrack
            board[row][col] = '.';
            rowSet[row].erase(digit);
            colSet[col].erase(digit);
            gridSet[index].erase(digit);
        }
        
        return false;
    }

public:
    void solveSudoku(vector<vector<char>>& board) {

        rowSet.resize(9);
        colSet.resize(9);
        gridSet.resize(9);
        // prefill all the row, col and grid for pre-existing digits
        for(int r = 0; r < 9; r++) {
            for(int c = 0; c < 9; c++) {
                
                char digit = board[r][c];
                int index = (r / 3) * 3 + (c / 3); // grid index
                if(digit == '.') continue;

                rowSet[r].insert(digit);
                colSet[c].insert(digit);
                gridSet[index].insert(digit);
            }
        }

        solve(0, 0, board);

    }
};

// ----------------------------------------------------------------------------------------------------


