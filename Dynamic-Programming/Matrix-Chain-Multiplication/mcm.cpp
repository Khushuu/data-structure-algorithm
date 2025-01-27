// The Matrix Chain Multiplication (MCM) problem involves finding the most efficient way to multiply a given sequence of matrices. 
// The goal is to minimize the total number of scalar multiplications.

// a = [10, 20, 30, 40]
// this represents 3 matrix
// Ai = matrix i where i > 0
// Ai = a[i - 1] * a[i]
// A1 = 10 * 20, A2 = 20 * 30, A3 = 30 * 40
// the partition should happen between the matrix = A1 * A2 * A3
// partition k will happen always between matrix 
// the range of k will be from 1 to n - 2 (inclusive)
// as we have to break it in range of i to k and k + 1 to j (not inclusive - max value = n - 1)
// or i can say i to k and k + 1 to j - 1

// Recursive solution 

matrixChainRecursive(p, 1, n - 1)
int matrixChainRecursive(int p[], int i, int j) {
    if (i == j) return 0; // Base case: one matrix requires no multiplications.

    int minCost = INT_MAX;

    // Try every possible split point k
    for (int k = i; k < j; k++) {
        int cost = matrixChainRecursive(p, i, k) +
                   matrixChainRecursive(p, k + 1, j) +
                   p[i - 1] * p[k] * p[j];
        minCost = min(minCost, cost);
    }
    return minCost;
}


// Memoization solution 
// T.C: O(n^3), O(n^2) subproblems - each subproblem takes O(n) to solve (loop over k)
// S.C: O(n^2), for the memoization table dp[i][j]

matrixChainMemoized(p, 1, n - 1)
vector<vector<int>> dp;

int matrixChainMemoized(int p[], int i, int j) {
    if (i == j) return 0; // Base case: one matrix requires no multiplications.

    // Return precomputed result
    if (dp[i][j] != -1) return dp[i][j];

    int minCost = INT_MAX;

    // Try every possible split point k
    for (int k = i; k < j; k++) {
        int cost = matrixChainMemoized(p, i, k) +
                   matrixChainMemoized(p, k + 1, j) +
                   p[i - 1] * p[k] * p[j];
        minCost = min(minCost, cost);
    }

    dp[i][j] = minCost; // Store the result
    return dp[i][j];
}

