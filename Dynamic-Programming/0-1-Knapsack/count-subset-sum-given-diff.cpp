// given
// array nums of integers 
// a difference diff
// divide the array into two sets such that their difference is equal to diff
// count how many such combination of two sets is possible

// eg 
// nums = [1, 1, 2, 3] and diff = 1
// combinations 
// {1,3} and {1,2} diff = 4 - 3 = 1 
//  {1,1,2} and 3 diff = 4 - 3 = 1
// count = 2

// Approach
// totalSum = s1 + s2 
// diff = s2 - s1 (consider s2 >= s1)
// diff = (totalSum - s1) - s1 = (totalSum - 2*s1)
// 2 * s1 = totalSum - diff
// s1 = (totalSum - diff) / 2
// s2 = (totalSum + diff) / 2

// so just find the count of sets for which the targetSum is either s1 or s2 
// i.e (totalSum - diff) / 2 or  (totalSum + diff) / 2
// this also means that (totalSum - diff) or (totalSum + diff) should be an even integer

// problem reduces to count subset sum for s1 or s2
// better find count subset sum for (totalSum - diff) / 2 to avoid potential integer overflow

// WRONG
// EDGE CASES 
// If totalSum < diff: No valid partition is possible
// if (totalSum - diff) % 2 != 0 no valid subset sum exists 
// hence find targetSum = (totalSum + diff) / 2


// CODE
// T.C = O(n*targetSum)
// S.C = O(n*targetSum)
//-------------------------------------------------------------------------------------------
int countSubsetsWithDifference(vector<int>& nums, int diff) {

    int totalSum = 0;
    for (int num : nums) totalSum += num;

    // If (totalSum + diff) is odd or diff is invalid, return 0
    if ((totalSum + diff) % 2 != 0 || totalSum < diff) return 0;

    int targetSum = (totalSum + diff) / 2;

    // DP array to store the number of subsets with a given sum
    vector<vector<int>> dp(nums.size() + 1, vector<int>(targetSum + 1, 0));

    // Base case: There's always 1 way to make sum 0 (empty subset)
    for (int i = 0; i <= nums.size(); i++) dp[i][0] = 1;

    // Fill the DP table
    for (int i = 1; i <= nums.size(); i++) {
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
// -----------------------------------------------------------------------------------------------
