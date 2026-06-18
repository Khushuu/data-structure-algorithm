// CONCEPT
// BINARY SEARCH ALGORITHM

// given a sorted array find the index of an element in the array
// if the element is not present in the array return -1

// e.g nums = [1, 2, 3, 4, 5], target = 3
// index output = 2

// T.C - O(log n)
// S.C - O(1)

// approach
// since the array is sorted
// every time we check the middle element of the array
// and identify if the target element is present on the left side or right side of the middle element
// if the target element matches the middle element we return the middle element index 
// if the target element is less than the middle element we search the left window
// else we search the right window

// since each time we reduce the search window by half
// the time complexity is O(log n)

// NOTE: 
// a simple iterative search would have a time complexity of O(n)
// but it does not use the fact that the array is sorted
// binary search reduces the time complexiy from O(n) to O(log n)

int binarySearch(vector<int>& nums, int target) {

    int l = 0, r = nums.size() - 1;

    // <= because we have to check all the elements of the array
    while (l <= r) {

        int mid = l + (r - l) / 2;

        if (nums[mid] == target) return mid;
        else if (target < nums[mid]) r = mid - 1;
        else l = mid + 1;

    }

    return -1;
}

// PROBLEM - 2
// BINARY SEARCH ON A REVERSE SORTED ARRAY

// given a reverse sorted array find the index of an element in the array
// if the element is not present in the array return -1

// just reverse the condition for binary search to search for the element

// e.g nums = [5, 4, 3, 2, 1], target = 3
// index output = 2

// T.C - O(log n)
// S.C - O(1)

int reverseBinarySearch(vector<int>& nums, int target) {

    int l = 0, r = nums.size() - 1;

    while (l <= r) {

        int mid = l + (r - l) / 2;

        if (nums[mid] == target) return mid;
        else if (target > nums[mid]) r = mid - 1; // just reverse this condition
        else l = mid + 1;

    }

    return -1;
}
