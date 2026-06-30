// 643. Maximum Average Subarray I
// You are given an integer array nums consisting of n elements, and an integer k.

// Find a contiguous subarray whose length is equal to k that has the maximum average value and return this value. 
// Any answer with a calculation error less than 10-5 will be accepted.

// T.C - O(n)
// S.C - O(1)

// NOTE: 
// result will always be calculated only for valid window of size k
// max function only works for integers - declaring result as double and using max will not work
// to return double value we need to return result * 1.0

// format
// do calculation
// check if window is valid - deduce result - subtract left element from sum - shrink window from left 
// expand window from right

class Solution {
public:
    double findMaxAverage(vector<int>& nums, int k) {

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

        return (result * 1.0) / k;
    }
};