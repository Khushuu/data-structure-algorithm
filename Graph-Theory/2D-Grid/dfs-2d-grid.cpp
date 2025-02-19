// cell in a grid == node
// sides --> up + down + left + right = edges
// or sides + diagonals = edges 

// use a visited grid of size n * m to check if the cell is visited
// to travarse edges --> declare direction array for all edges 
// dr = {-1, 1, 0, 0} 
// dc = {0, 0, -1, 1}
// represent --> up, down, left, right

// check if the cell is valid and not visited before running dfs call 
// distance initialised with -1 can also be used in placed of visited array to see if cell is visited or not
// when a cell is visited its distance also gets updated 

// T.C = O(m * n) - traversing all cells
// S.C = O(m * n) - space for visited grid
//-----------------------------------------------------------------------------------------------------------
vector<vector<int>> matrix;
vector<vector<bool>> visited(rows, vector<bool>(cols, false));
vector<vector<int>> distance(rows, vector<int>(cols, 0));
queue<pair<int, int>> q;

vector<int> dr = {-1, 1, 0, 0} 
vector<int> dc = {0, 0, -1, 1}

// r, c - source cell
void bfs(int row, int col) {

	q.push({row, col});
	visited[row][col] = true;
	distance[row][col] = 0

	while(!q.empty()) {
		
		int r = q.front().first;
		int c = q.front().second;
		q.pop();

		// traverse connected edges if cell is valid 
		for(int i = 0; i < 4; i++) {

			int R = dr[i] + r;
			int C = dc[i] + c;

			// check if (R,C) is a valid cell in range of rows and cols
			// and this cell (R, C) is not visited 
			if(R >= 0 && R < rows && C >= 0 && C < cols && !visited[R][C]) {
				visited[R][C] = true;
				distance[R][C] = distance[r][c] + 1;
				q.push({R, C});
			}
		}
	}
}

//-----------------------------------------------------------------------------------------------------------