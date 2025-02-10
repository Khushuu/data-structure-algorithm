// given the starting position of a rat 
// find all possible paths the rat can take to come out of the maze
// the maze if of size n * n
// starting (0, 0) and end (n - 1, n - 1)
// the rat can move in 4 directions - up(U), down(D), left(L), right(R)
// before moving in any direction check if that grid is valid
// isValid --> if the direction is not out of bounds & the grid is not blocked, i.e it can be visited 
// if it is valid move the rat in that direction
// add this to the path 
// when the rat reaches the end of the maze add the path to the final result 
// backtrack the path
// remove the last added direction from current path
// and again mark the path as unvisited i.e unblocked by setting it to 0 when coming out of the function

// T.C = O(3^(m * n)) --> since at each point rat can move in 3 directions -- O(3^(n*n)) - as m == n here
// y 3 --> as it will never go to the same direction from which it came


// --------------------------------------------------------------------------------------------------------------

// Global movement arrays (Down, Left, Right, Up)
int dr[] = {1, 0, 0, -1};  // Row movement
int dc[] = {0, -1, 1, 0};  // Column movement
char dir[] = {'D', 'L', 'R', 'U'};

void findPaths(vector<vector<int>> &maze, int row, int col, string &path, vector<string> &result) {
    int n = maze.size();

    // If reached the destination, store the path
    if (row == n - 1 && col == n - 1) {
        result.push_back(path);
        return;
    }

    // Mark the current cell as visited
    maze[row][col] = 0;

    // Try all 4 directions
    for (int i = 0; i < 4; i++) {

        int newRow = row + dr[i];
        int newCol = col + dc[i];

        // Check if move is valid (within bounds & open path)
        if (newRow >= 0 && newRow < n && newCol >= 0 && newCol < n && maze[newRow][newCol] == 1) {
            path.push_back(dir[i]);  // Append direction to path
            findPaths(maze, newRow, newCol, path, result);
            path.pop_back();         // Backtrack (remove last move)
        }
    }

    // Unmark the current cell (backtrack)
    maze[row][col] = 1;
}

vector<string> ratInMaze(vector<vector<int>> &maze) {
    int n = maze.size();
    vector<string> result;

    // Edge case: If start or end is blocked
    if (maze[0][0] == 0 || maze[n - 1][n - 1] == 0)
        return result;

    string path = "";
    findPaths(maze, 0, 0, path, result);
    return result;
}

int main() {
    vector<vector<int>> maze = {
        {1, 0, 0, 0},
        {1, 1, 0, 1},
        {0, 1, 0, 0},
        {1, 1, 1, 1}
    };

    vector<string> paths = ratInMaze(maze);

    if (paths.empty())
        cout << "No path found" << endl;
    else
        for (string path : paths)
            cout << path << endl;

    return 0;
}

// --------------------------------------------------------------------------------------------------------------
