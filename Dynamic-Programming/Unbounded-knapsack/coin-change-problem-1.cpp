// given
// A list of coin denominations coins
// A target amount sum
// return total number of ways to make the sum using the coins
// NOTE: Each coin can be used an unlimited number of times

// this is an unbounded knapsack problem 
// as total no. of ways is asked do the sum of all possible ways to obtain the sum

// recursive CODE
// T.C = O(2^n) - two choices made for every call - n no. of coins
// S.C = O(n): Due to recursion stack
// -------------------------------------------------------------------------------------------------
// main
coinChangeRecursive(coins, coins.size(), sum);

int coinChangeRecursive(vector<int>& coins, int n, int sum) {

    // Base cases
    if (sum == 0) return 1; // 1 way to make sum 0: use no coins
    if (n == 0) return 0; // No way to make the sum with no coins 

	// exclude if coin value more than the sum
	if(coins[n - 1] > sum) return coinChangeRecursive(coins, n - 1, sum);

    // Include the current coin or exclude it
    return coinChangeRecursive(coins, n, sum - coins[n - 1]) + coinChangeRecursive(coins, n - 1, sum);
}
// -------------------------------------------------------------------------------------------------

// Memoization Code
// T.C = O(n×sum): Each subproblem is solved once.
// S.C = O(n×sum): For the DP table and recursion stack.
// -------------------------------------------------------------------------------------------------
// main
vector<vector<int>> dp(coins.size() + 1, vector<int>(sum + 1, -1));
coinChangeMemo(coins, coins.size(), sum, dp)

int coinChangeMemo(vector<int>& coins, int n, int sum, vector<vector<int>>& dp) {
    // Base cases
    if (sum == 0) return 1;
    if (n == 0) return 0;

    // Check if result is already computed
    if (dp[n][sum] != -1) return dp[n][sum];

	// exclude if coin value more than the sum
	if(coins[n - 1] > sum) return dp[n][sum] = coinChangeRecursive(coins, n - 1, sum);

    // Include or exclude the current coin
    return dp[n][sum] = coinChangeMemo(coins, n, sum - coins[n - 1], dp) + coinChangeMemo(coins, n - 1, sum, dp);
}
// -------------------------------------------------------------------------------------------------

// Bottom-up Code
// dp[i][j] represents the number of ways to make sum j using the first i coins
// T.C = O(n×sum): Two nested loops
// T.C = O(n×sum)
// -------------------------------------------------------------------------------------------------
int coinChangeDP(vector<int>& coins, int sum) {
    int n = coins.size();

    // Initialize a DP table
    vector<vector<int>> dp(n + 1, vector<int>(sum + 1, 0));

    // Base case: 1 way to make sum 0 (use no coins)
    for (int i = 0; i <= n; i++) dp[i][0] = 1;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= sum; j++) {

            // Exclude the coin
			if(coins[i - 1] > j)
           		dp[i][j] = dp[i - 1][j];
			else 
            	// Exclude or Include the coin
            	dp[i][j] = dp[i - 1][j] + dp[i][j - coins[i - 1]];
        }
    }

    return dp[n][sum];
}
// -------------------------------------------------------------------------------------------------