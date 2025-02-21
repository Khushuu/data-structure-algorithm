// 733. Flood Fill

// given a 2d grid with some colors in it
// and a target color
// color the source cell with target color
// and all other cells which are adjacent to it - 4 sides -> up, down, left, right
// the color will be update for a cell if it has the same color as source cell

// approach
// if the source cell has the same color as target 
// return the matrix as it is
// as we will update all the cells which have same color as source cell
// with target color 

// otherwise run a dfs or bfs and if the cell has color of 
// source cell then update it with that target color
// the call will happen in 4 directios - up, down, left, right
// this will only be done for 1 connected component
// in which the source cell lies 
// as we r only asked to traverse cells adjacent to it on sides

// use a visited 2d matrix to check if a cell is visited or not
// NOTE:
// it is not necessary to use a visited matrix
// checking the color of the cell is sufficient
// y ? -- because the color of a visited cell will already be changed to target color
// checking condition if color of cell is same as source color is sufficient

// Time Complexity: O(N×M) 
// Space Complexity: O(N×M) 

// dfs
//------------------------------------------------------------------------------------------------------

class Solution {
private:
    vector<int> dr = {-1, 1, 0, 0};
    vector<int> dc = {0, 0, -1, 1};
    int rows, cols;

    void dfs(int r, int c, int sourceColor, int targetColor, vector<vector<bool>>& visited, vector<vector<int>>& image) {

        visited[r][c] = true;   // mark cell as visited
        image[r][c] = targetColor; // fill with target color

        // loop over the adjacent nodes - 4 sides
        // if the cell is valid
        // if cell is not visited
        // if color of cell matches that of source - call dfs for this cell
        for(int i = 0; i < 4; i++) {
            
            int R = r + dr[i];
            int C = c + dc[i];

            if(R >= 0 && R < rows && C >= 0 && C < cols && !visited[R][C] && image[R][C] == sourceColor) 
                dfs(R, C, sourceColor, targetColor, visited, image);
        }
    }
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
        
        if(image[sr][sc] == color) return image;

        rows = image.size();
        cols = image[0].size();

        vector<vector<bool>> visited(rows, vector<bool>(cols, false));

        dfs(sr, sc, image[sr][sc], color, visited, image);

        return image;
    }
};

//------------------------------------------------------------------------------------------------------

// bfs
//------------------------------------------------------------------------------------------------------

class Solution {
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
        
		if(image[sr][sc] == color) return image;

        int rows = image.size();
        int cols = image[0].size();
        vector<vector<bool>> visited(rows, vector<bool>(cols));

        int dr[4] = {0, 0, -1, 1};
        int dc[4] = {-1, 1, 0, 0};
        queue<pair<int, int>> q;

        int sourceColor = image[sr][sc];

        image[sr][sc] = color;
        visited[sr][sc] = true;
        q.push({sr, sc});

        while(!q.empty()) {

            int r = q.front().first;
            int c = q.front().second;
            q.pop();

            for(int i = 0; i < 4; i++) {

                int R = r + dr[i];
                int C = c + dc[i];
				
                if( R >= 0 && R < rows && 
                    C >= 0 && C < cols && 
                    !visited[R][C] && 
                    image[R][C] == sourceColor
                ) {
                    image[R][C] = color;
                    visited[R][C] = true;
                    q.push({R, C});
                }
            }
        }

        return image;
    }
};

//------------------------------------------------------------------------------------------------------

// NOTE: without visited matrix
// it is not necessary to use a visited matrix
// checking the color of the cell is sufficient
// y ? -- because the color of a visited cell will already be changed to target color
// and we only have to traverse the cell which have same color as source color
// checking condition if color of cell is same as source color is sufficient
// and we won't traverse already visited cell
//------------------------------------------------------------------------------------------------------

class Solution {
private:
    vector<int> dr = {-1, 1, 0, 0};
    vector<int> dc = {0, 0, -1, 1};
    int rows, cols;

    void dfs(int r, int c, int sourceColor, int targetColor,   vector<vector<int>>& image) {

        image[r][c] = targetColor; // fill with target color

        for(int i = 0; i < 4; i++) {
            
            int R = r + dr[i];
            int C = c + dc[i];

            if(R >= 0 && R < rows && C >= 0 && C < cols 
                && image[R][C] == sourceColor) {
                    dfs(R, C, sourceColor, targetColor, image);
                }
        }
    }
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
     
        if(image[sr][sc] == color) return image;

        rows = image.size();
        cols = image[0].size();

        dfs(sr, sc, image[sr][sc], color, image);

        return image;
    }
};
//------------------------------------------------------------------------------------------------------

