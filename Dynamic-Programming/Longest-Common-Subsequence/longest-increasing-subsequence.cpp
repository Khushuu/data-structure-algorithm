// Given an integer array nums
// return the length of the longest strictly increasing subsequence
// come up with an algorithm that runs in O(n log(n)) time complexity?

// e.g 
// nums = [10,9,2,5,3,7,101,18]
// nums = [10,9,2,5,3,7,101,18]
// longest increasing subsequence = [2,3,7,101] = 4

// base condition = if m == 0 || n == 0 return 0
// if (nums[m - 1] < nums[n - 1]) return 1 + lis(nums, m - 1, n - 1)
// return max(lis(nums, m - 1, n), lis(nums, m, n - 1))


