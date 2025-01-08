// Subset Sum
// given
// an array nums of size n
// and a targetSum sum - targetSum
// Return true if there exists a subset of nums whose sum is equal to targetSum, and false otherwise

// Recursive Code
// base condition - if targetSum is 0 then it is possible to get that sum by selecting an empty set 
// if there are no items to select from and targt is not 0 return false
// n is the no. of items considered
// T.C = O(2^n)
// S.C = O(n)
//------------------------------------------------------------------------------------------------
bool subsetSum(vector<int>& nums, int n, int targetSum) {

	if(targetSum == 0) return true;
	if(n == 0) return false;

	// exclue nums if its value is more than targetSum value
	// reduce the no. of items considered
	if(nums[n - 1] > targetSum) 
		return subsetSum(nums, n - 1, targetSum);

	// either include or exclude the item if its value is less than targetSum sum
	// two choices to make
	// return if any one of them returns true
	// include = subsetSum(nums, n - 1, targetSum - nums[n - 1])
	// exclude = subsetSum(nums, n - 1, targetSum

	return subsetSum(nums, n - 1, targetSum - nums[n - 1]) || subsetSum(nums, n - 1, targetSum);
}
//------------------------------------------------------------------------------------------------

// Memoization Code
// n and targetSum value keep changing
// T.C = O(n*targetSum)
// S.C = O(n*targetSum)
//------------------------------------------------------------------------------------------------
// main function
vector<vector<int>> dp(n + 1, vector<int>(targetSum + 1, -1))

bool subsetSum(vector<int>& nums, int n, int targetSum, vector<vector<int>>& dp) {

	if(targetSum == 0) return true;
	if(n == 0) return false;
	if(dp[n][targetSum] != -1) return dp[n][targetSum];

	// exclue nums if its value is more than targetSum value
	// reduce the no. of items considered
	if(nums[n - 1] > targetSum) 
		return dp[n][targetSum] = subsetSum(nums, n - 1, targetSum, dp);

	// either include or exclude the item if its value is less than targetSum sum
	// two choices to make
	// return if any one of them returns true
	// include = subsetSum(nums, n - 1, targetSum - nums[n - 1])
	// exclude = subsetSum(nums, n - 1, targetSum

	return dp[n][targetSum] = subsetSum(nums, n - 1, targetSum - nums[n - 1], dp) || 
								subsetSum(nums, n - 1, targetSum, dp);
}
//------------------------------------------------------------------------------------------------

// Bottom-up Code
// T.C = O(n*targetSum)
// S.C = O(n*targetSum)
//------------------------------------------------------------------------------------------------
bool subsetSum(vector<int>& nums, int targetSum) {

    int n = nums.size();
    vector<vector<bool>> dp(n + 1, vector<bool>(targetSum + 1, false));

    // Base case: targetSum = 0 is always true - u can select empty set
    for (int i = 0; i <= n; i++) dp[i][0] = true;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= targetSum; j++) {

			// exclude the num
            if (nums[i - 1] > j) 
                dp[i][j] = dp[i - 1][j];
            else  // incldue or exclude
                dp[i][j] = dp[i - 1][j] || dp[i - 1][j - nums[i - 1]];
        }
    }

    return dp[n][targetSum];
}
//------------------------------------------------------------------------------------------------

