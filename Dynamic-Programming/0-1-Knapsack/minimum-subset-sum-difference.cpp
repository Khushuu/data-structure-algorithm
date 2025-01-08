// Given 
// an array nums of integers
// divide it into two sets S1 and S2 such that the absolute difference between their sums is minimum
// i.e 
// diff = abs(sum(s1) - sum(s2)) - find the minimum value of diff possible

// S1 = sum of s1
// S2 = sum of s2
// diff = s2 - s1
// sum = s1 + s2 (total sum of the array)
// diff = (sum - s1) - s1 = sum - 2*s1
// minimize (sum - 2*s1) - the minimum value can be 0 considering s1 < s2
// so if we find the maximum value of s1 which is less than equal to sum / 2 
// we will get the minimum difference

// so find the maximum value of s1 possible in the range 0 to sum / 2 [inclusive]
// if s1 = sum / 2 is possible min value of diff will be 0

// follow the subset sum approach
// for the last row of the dp find the max sum value that is less <= sum / 2
// return sum - s1 --> where s1 is the max value - that is ur answer

// Recursive code
// T.C = O(2^n)
// S.C = O(n)
// -------------------------------------------------------------------------------------------------

int minSubsetSumDiff(vector<int>& nums, int n, int sum1, int totalSum) {

    if (n == 0) {
        // Return the absolute difference between two subset sums
        return abs((totalSum - sum1) - sum1);
    }

    // Include the current element in subset 1
    int include = minSubsetSumDiff(nums, n - 1, sum1 + nums[n - 1], totalSum);

    // Exclude the current element from subset 1
    int exclude = minSubsetSumDiff(nums, n - 1, sum1, totalSum);

    // Return the minimum difference
    return min(include, exclude);
}

// main
for (int num : nums) totalSum += num;
minSubsetSumDiff(nums, nums.size(), 0, totalSum)
// ---------------------------------------------------------------------------------------------------

// Memoized code
// T.C = O(n * totalSum)
// S.C = O(n * totalSum)
// -------------------------------------------------------------------------------------------------

int minSubsetSumDiff(vector<int>& nums, int n, int sum1, int totalSum, vector<vector<int>>& dp) {
    if (n == 0) {
        return abs((totalSum - sum1) - sum1);
    }

    if (dp[n][sum1] != -1) {
        return dp[n][sum1];
    }

    // Include the current element in subset 1
    int include = minSubsetSumDiff(nums, n - 1, sum1 + nums[n - 1], totalSum, dp);

    // Exclude the current element from subset 1
    int exclude = minSubsetSumDiff(nums, n - 1, sum1, totalSum, dp);

    // Store the result in the memoization table
    return dp[n][sum1] = min(include, exclude);
}

// main
for (int num : nums) totalSum += num;
int n = nums.size();
vector<vector<int>> dp(n + 1, vector<int>(totalSum + 1, -1));
minSubsetSumDiff(nums, n, 0, totalSum, dp)
// ---------------------------------------------------------------------------------------------------

// Bottom-Up
// find the subset sum of only totalSum / 2
// then find th max subset sum for which dp is true - check from end
// this will give the min difference 

// ---------------------------------------------------------------------------------------------------
int minSubsetSumDiff(vector<int>& nums) {

    int totalSum = 0;
    for (int num : nums) totalSum += num;

    int n = nums.size();
    int target = totalSum / 2;

    // DP table: dp[i][j] indicates if a subset with sum j can be formed using the first i elements
    vector<vector<bool>> dp(n + 1, vector<bool>(target + 1, false));

    // Base case: A sum of 0 is always possible - select no element - empty set
    for (int i = 0; i <= n; i++) dp[i][0] = true;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= target; j++) {
            if (nums[i - 1] > j) {
                dp[i][j] = dp[i - 1][j];
            } else {
                dp[i][j] = dp[i - 1][j] || dp[i - 1][j - nums[i - 1]];
            }
        }
    }

    // Find the largest `j` such that dp[n][j] is true
    int sum1 = 0;
    for (int j = target; j >= 0; j--) {
        if (dp[n][j]) {
            sum1 = j;
            break;
        }
    }

    int sum2 = totalSum - sum1;
    return abs(sum2 - sum1); // minimum subset sum difference
}
// ---------------------------------------------------------------------------------------------------