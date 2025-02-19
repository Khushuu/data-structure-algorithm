// given a grid filled with 0s and 1s
// find the number of connected components 
// only the 1s that are around each other i.e up, down, left, right are reachable from a given cell

// approach
// use a visited grid of size rows * cols 
// rows = total no. of rows 
// cols = total no. of cols

// one dfs call will cover all cells in that one connected components
// total no. of connected components = total no. of dfs calls made 
// a cell is reachable only if matrix[r][c] = 1

// T.C = O(m * n) - traversing all cells
// S.C = O(m * n) - space for visited grid
//-----------------------------------------------------------------------------------------------------------
vector<vector<int>> matrix;
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

int count = 0; // no. of connected components

for(int r = 0; r < rows; r++) {
	for(int c = 0; c < cols; c++) {

		// if the cell is reachable and is not visited call dfs for the cell
		if(matrix[r][c] == 1 && !visited[r][c]) {
			count++;
			dfs(r, c);
		}
	}
}

return count;

//-----------------------------------------------------------------------------------------------------------