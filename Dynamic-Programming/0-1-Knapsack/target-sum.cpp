// given
// an integer array nums
// a target sum 
// u can assign either + or - infront of each integer and then compute all of their sum
// find the count of different expressions that have sum = targetSum

// this is just another variation of: count subset sum with given difference
// how?
// just divide the array in two sets => s1 and s1
// s1 has all integers with + assigned and s2 has all integers with - assigned
// if we do (1 + 2 + 4 + 5 + ....) + (- 2 - 4 - 1 - 5....) = targetSum
// it is same as (1 + 2 + 4 + 5 + ....) - (2 + 4 + 1 + 5....) = targetSum
// s1 - s2 = targetSum

// Bottom up CODE
// T.C = O(n*targetSum)
// S.C = O(n*targetSum)
//-------------------------------------------------------------------------------------------
int countSubsetsWithDifference(vector<int>& nums, int targetSum) {

    int totalSum = 0;
    for (int num : nums) totalSum += num;

	int diff = targetSum;
	int n = nums.size();
    // If (totalSum + diff) is odd or diff is invalid, return 0
    if (totalSum + diff < 0 || (totalSum + diff) % 2 != 0) return 0;

    int targetSum = (totalSum + diff) / 2;

    // DP array to store the number of subsets with a given sum
    vector<vector<int>> dp(n + 1, vector<int>(targetSum + 1, 0));

    // Base case: There's always 1 way to make sum 0 (empty subset)
    for (int i = 0; i <= n; i++) dp[i][0] = 1;

    // Fill the DP table
    for (int i = 1; i <= n i++) {
        for (int j = 0; j <= targetSum; j++) { // starts from 0 to also consider a sum of 0 contributed by 0 + 0
            if (nums[i - 1] > j) {
                // Current number cannot be included
                dp[i][j] = dp[i - 1][j];
            } else {
                // Include or exclude the current number
                dp[i][j] = dp[i - 1][j] + dp[i - 1][j - nums[i - 1]];
            }
        }
    }

    return dp[nums.size()][targetSum];
}
// ---------------------------------------------------------------------------------------------