// Unbounded Knapsack
// if excluded don't process it again 
// if included don't move on to next item - process this item again 

// given
// weights of items and their values
// a maximum capacity W that the knapsack can store
// same item can be picked multiple times 
// return the maximum profit that can be achieved without exceeding the weight capacity W

// Recursive Code
// T.C: O(2^n) - exponential 
// S.C: O(n) - recusive call stack of n items
//--------------------------------------------------------------------------------------------------
int unboundedKnapsack(vector<int>& weights, vector<int>& values, int n, int W) {

	// base condition - if 0 items are there or the capacity is 0 return 0 profit
	// W will never be negative during operations as we do not select an items whose weight exceeds capacity W
    if (n == 0 || W == 0)
        return 0;

	// if the weight of the current item i.e weights[n - 1], is greater than the capacity W
	// then the item is excluded and reduce the no. of items from n to n - 1 - move on to next item
    if (weights[n - 1] > W)
        return unboundedKnapsack(weights, values, n - 1, W);

	// else consider both including and excluding the item
	// if item is included it will contribute to the profit 

	// include: values[n - 1] + unboundedKnapsack(weights, values, n, W - weights[n - 1]) 
	// n stays the same as we have the option to pick the same item again
	// since item is include the capacity is reduced from W to W - weights[n - 1]

	// exclude: unboundedKnapsack(weights, values, n - 1, W))
	// no change in the net capacity and we move on to the next object by reducing no. of item from n to n - 1
    return max(values[n - 1] + unboundedKnapsack(weights, values, n, W - weights[n - 1]),
               unboundedKnapsack(weights, values, n - 1, W));
}
//--------------------------------------------------------------------------------------------------

// Memoization Code
// T.C: O(n*W) - all combinations for n and W in function call - only unique subproblems are solved
// S.C: O(n*W) - dp matrix storage - for the dp table and recursion stack
//--------------------------------------------------------------------------------------------------
vector<vector<int>> dp(n + 1, vector<int>(W + 1, -1)); // declare this in the calling function

int unboundedKnapsack(vector<int>& weights, vector<int>& values, int n, int W, vector<vector<int>>& dp) {

	// base condition
    if (n == 0 || W == 0)
        return 0;
	
	// check if the same function call has been done before if yes return stored result
    if (dp[n][W] != -1)
        return dp[n][W];

	// exclude the item
    if (weights[n - 1] > W)
        return dp[n][W] = unboundedKnapsack(weights, values, n - 1, W, dp);
    
	// consider both choice either exclude or include the item
	// if included keep it so it can be picked again
	// return the maximum profit from both the choices
	return dp[n][W] = max(values[n - 1] + unboundedKnapsack(weights, values, n, W - weights[n - 1], dp),
                       unboundedKnapsack(weights, values, n - 1, W, dp));
}
//--------------------------------------------------------------------------------------------------

// Bottom Up 

// dp[i][w] represents the maximum value that can be achieved
// with the first i items having weight capacity w
// dp[i][0] = 0 (capacity is 0)
// dp[0][w] = 0 (no items)

// Bottom Up Code
// T.C: O(n*W) - loop run
// S.C: O(n*W) - dp space
//--------------------------------------------------------------------------------------------------
int unboundedKnapsack(vector<int>& weights, vector<int>& values, int n, int W) {

    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= W; w++) {

			// exclude the item
    		if (weights[n - 1] > W)
				dp[i][w] = dp[i - 1][w];
			else // two choices - include or exclude the item - select the one with maximum profit
                dp[i][w] = max(values[i - 1] + dp[i][w - weights[i - 1]],
                               dp[i - 1][w]);
        }
    }

    return dp[n][W];
}
//--------------------------------------------------------------------------------------------------