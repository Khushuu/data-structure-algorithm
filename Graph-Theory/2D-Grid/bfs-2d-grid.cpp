// bfs on 2d grid
// find the shortest path of all nodes from a given cell

// approach
// push all reachable cells from the source cell into a queue
// declare a queue of pair<int, int> storing row and cell 
// pop from the front of the queue
// and push all valid cells that are not visited to the end of the queue
// update the distane of the cell 

// T.C = O(m * n) - traversing all cells
// S.C = O(m * n) - space for visited grid
//-----------------------------------------------------------------------------------------------------------
vector<vector<bool>> visited(rows, vector<bool>(cols, false));
vector<int> dr = {-1, 1, 0, 0} 
vector<int> dc = {0, 0, -1, 1}


//-----------------------------------------------------------------------------------------------------------