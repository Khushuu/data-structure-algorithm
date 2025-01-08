// Given an array nums of size n
// find if it can be partitioned into two subsets with equal sums

// since the nums array has to be partitioned into two sets with equal sums
// if the sum of the array is odd it can never be partitioned into equal sum with integer values
// only if the total sum of the array is even it can be divided into equal sum

// If the total sum of the array is odd, it's impossible to divide it into two subsets with equal sums
// Reason: Two equal integers add up to an even number

// targetSum = sum / 2
// equal sum partition = subsetSum(nums, n, sum / 2)

// CODE
// T.C = O(n*targetSum)
// S.C = O(n*targetSum)
// ---------------------------------------------------------------------------------------------
bool subsetSum(vector<int>& nums, int targetSum) {

	int n = nums.size();
	vector<vector<int>> dp(n + 1, vector<int>(targetSum + 1, false));

	// if targetSum is 0 empty set can be selected
	for(int i = 0; i < n; i++) dp[i][0] = true;

	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= targetSum; j++) {
			
			// exclude if nums value is greater than targetSum - j
			if(nums[i - 1] > j) 
				dp[i][j] = dp[i - 1][j];
			else // include or exclude whichever gives true
				dp[i][j] = dp[i - 1][j - nums[i - 1]] || dp[i - 1][j];
		}
	}

	return dp[n][targetSum];
}

bool equalPartition(vector<int>& nums) {

	int sum = accumulate(nums.begin(), nums.end());

	// equal sum partition not possible for odd sum
	if(sum % 2) return false;

	return subsetSum(nums, sum / 2);
}
// ---------------------------------------------------------------------------------------------

