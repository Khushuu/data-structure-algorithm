// PROBLEM - 1
/// MAXIMUM SUM SUBARRAY OF SIZE K
// Given an array of positive numbers and a positive number K, find the maximum sum of any contiguous subarray of size K.

// Input: [2, 1, 5, 1, 3, 2], K=3 
// Output: 9
// Explanation: Subarray with maximum sum is [5, 1, 3].

// T.C - O(n)
// S.C - O(1)

class Solution {
public:
    int maxSubarraySum(vector<int> nums, int k) {

        int l = 0;
        int r = 0;
        int sum = 0;
        int result = INT_MIN;

        while (r < nums.size()) {

            sum += nums[r];

            // check window size
            if (r - l + 1 == k) {

                result = max(result, sum);
                sum -= nums[l];
                l++;
            }

            r++;
        }
        
        return result;
    }
};