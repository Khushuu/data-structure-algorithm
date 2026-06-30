// 209. Minimum Size Subarray Sum
// Dynamic sliding window

// all the elements of nums are positive
// this solution will not work for negative integers

// Given an array of positive integers nums and a positive integer target
// return the minimal length of a subarray whose sum is greater than or equal to target. 
// If there is no such subarray, return 0 instead.

// e.g nums = [2, 3, 1, 2, 4, 3], target = 7
// output = 2 (subarray with minimum length is [4, 3])

// T.C - O(n)
// S.C - O(1)

class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {

        // dynamic sliding window
        // sum >= target
        // if sum >= target try reducing the size of the window

        int l = 0;
        int r = 0;
        int sum = 0;
        int result = INT_MAX;

        while (r < nums.size()) {

            sum += nums[r];

            // minimize window to get result
            while (sum >= target) {

                result = min(result, r - l + 1);
                sum -= nums[l];
                l++;
            }

            r++;
        }

        return result == INT_MAX ? 0 : result;
    }
};

// APPROACH - 2
// T.C - O(nlogn)
// S.C - O(n)

// Prefix Sum + Binary Search solution 

// compute prefix sum for all the elements of nums
// since all the elements of nums are positive the array will be strictly increasing
// we can use binary search to find the window that has sum >= target

// Step 1: Build Prefix Sum
// Let
// prefix[i] = sum of first i elements

// where
// prefix[0] = 0

// For example,

// nums = [2,3,1,2,4,3]
// target = 7

// prefix = 0 2 5 6 8 12 15
// Notice the prefix array is strictly increasing because all numbers are positive.


// Step 2: Reformulate the Problem
// Suppose our subarray starts at index i.
// Its sum is

// prefix[j] - prefix[i]

// We need
// prefix[j] - prefix[i] >= target

// which becomes

// prefix[j] >= prefix[i] + target

// So for every starting index i, we need the smallest j satisfying

// prefix[j] >= prefix[i] + target

// Since prefix is sorted, we can binary search for this.

// Example

// target = 7
// nums = [2,3,1,2,4,3]

// prefix
// index : 0 1 2 3 4 5 6
// value : 0 2 5 6 8 12 15

// i = 0

// Need
// prefix[j] >= 7

// Binary search finds
// j = 4

// because
// prefix[4] = 8

// Length
// 4-0 = 4

// Subarray
// [2,3,1,2]


// Algorithm: 

// Compute prefix sums.
// For every starting index i
// Compute
// need = prefix[i] + target;

// Binary search the prefix array for the first value ≥ need.
// If found,
// ans = min(ans, j - i);

// Why Binary Search Works

// Since
// nums[i] > 0

// the prefix sums satisfy
// prefix[0] < prefix[1] < prefix[2] < ...

// A binary search (lower_bound) can therefore find the first valid ending position in O(log n).

// Complexity
// Prefix sum construction: O(n)
// Binary search for each index: O(log n)

// Total: O(n log n)
// Space: O(n)

class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int n = nums.size();

        vector<long long> prefix(n + 1, 0);

        for (int i = 0; i < n; i++)
            prefix[i + 1] = prefix[i] + nums[i];

        int ans = INT_MAX;

        for (int i = 0; i < n; i++) {
            long long need = prefix[i] + target;

            auto it = lower_bound(prefix.begin(), prefix.end(), need);

            if (it != prefix.end()) {
                int j = it - prefix.begin();
                ans = min(ans, j - i);
            }
        }

        return ans == INT_MAX ? 0 : ans;
    }
};