// Count subset sum
// given
// array nums of size n
// and a target sum
// return number of subsets whose sum equal to the target sum

// how is it same as subset sum
// instead of finding if subset sum is present or not 
// we have to return the count 

// Recursive Code
// T.C = O(2^n)
// S.C = O(n)
//------------------------------------------------------------------------------------------------
int countSubsetSum(vector<int>& nums, int n, int targetSum) {

	if(targetSum == 0) return 1;
	if(n == 0) return 0;

	// exclue nums if its value is more than targetSum value
	// reduce the no. of items considered
	if(nums[n - 1] > targetSum) 
		return countSubsetSum(nums, n - 1, targetSum);

	// either include or exclude the item if its value is less than targetSum sum
	// two choices to make
	// return if any one of them returns true
	// include = subsetSum(nums, n - 1, targetSum - nums[n - 1])
	// exclude = subsetSum(nums, n - 1, targetSum

	return countSubsetSum(nums, n - 1, targetSum - nums[n - 1]) + countSubsetSum(nums, n - 1, targetSum);
}
//------------------------------------------------------------------------------------------------

// Memoization Code
// n and targetSum value keep changing
// T.C = O(n*targetSum)
// S.C = O(n*targetSum)
//------------------------------------------------------------------------------------------------
// main function
vector<vector<int>> dp(n + 1, vector<int>(targetSum + 1, -1))

int countSubsetSum(vector<int>& nums, int n, int targetSum, vector<vector<int>>& dp) {

	if(targetSum == 0) return 1;
	if(n == 0) return 0;
	if(dp[n][targetSum] != -1) return dp[n][targetSum];

	// exclue nums if its value is more than targetSum value
	// reduce the no. of items considered
	if(nums[n - 1] > targetSum) 
		return dp[n][targetSum] = countSubsetSum(nums, n - 1, targetSum, dp);

	// either include or exclude the item if its value is less than targetSum sum
	// two choices to make
	// return if any one of them returns true
	// include = subsetSum(nums, n - 1, targetSum - nums[n - 1])
	// exclude = subsetSum(nums, n - 1, targetSum

	return dp[n][targetSum] = countSubsetSum(nums, n - 1, targetSum - nums[n - 1], dp) + 
								countSubsetSum(nums, n - 1, targetSum, dp);
}
//------------------------------------------------------------------------------------------------

// Bottom-up Code
// T.C = O(n*targetSum)
// S.C = O(n*targetSum)
//------------------------------------------------------------------------------------------------

int countSubsetSum(vector<int>& nums, int targetSum) {
    int n = nums.size();
    vector<vector<int>> dp(n + 1, vector<int>(targetSum + 1, 0));

    // Base case: targetSum = 0 can always be achieved with the empty set
    for (int i = 0; i <= n; i++) dp[i][0] = 1;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= targetSum; j++) {  // Start j from 0 for completeness - in case 0 also exist

            // Exclude the current number if it is greater than sum
			if(nums[i - 1] > j)
            	dp[i][j] = dp[i - 1][j];

            // Include the current number if it's less than or equal to the target
            if (nums[i - 1] <= j) {
                dp[i][j] += dp[i - 1][j - nums[i - 1]];
            }
        }
    }

    return dp[n][targetSum];
}
//------------------------------------------------------------------------------------------------


