// cell in a grid == node
// sides --> up + down + left + right = edges
// or sides + diagonals = edges 

// use a visited grid of size n * m to check if the cell is visited
// to travarse edges --> declare direction array for all edges 
// dr = {-1, 1, 0, 0} 
// dc = {0, 0, -1, 1}
// represent --> up, down, left, right

// check if the cell is valid and not visited before running dfs call 

// T.C = O(m * n) - traversing all cells
// S.C = O(m * n) - space for visited grid
//-----------------------------------------------------------------------------------------------------------
vector<vector<bool>> visited(rows, vector<bool>(cols, false));
vector<int> dr = {-1, 1, 0, 0} 
vector<int> dc = {0, 0, -1, 1}

void dfs(int r, int c) {

	visited[r][c] = true;
	cout << r << " " << c << endl;

	// traverse connected edges if cell is valid 
	for(int i = 0; i < 4; i++) {

		int R = dr[i] + r;
		int C = dc[i] + c;

		// check if (R,C) is a valid cell in range of rows and cols
		// and this cell (R, C) is not visited 
		if(R >= 0 && R < rows && C >= 0 && C < cols && !visited[R][C])
			dfs(R, C);
	}
}

//-----------------------------------------------------------------------------------------------------------