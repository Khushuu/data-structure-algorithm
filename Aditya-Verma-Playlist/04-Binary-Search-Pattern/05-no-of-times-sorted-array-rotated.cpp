// PROBLEM - 1
// NUMBER OF TIMES A SORTED ARRAY IS ROTATED

// THIS SOLUTION IS FOR DISTINCT ELEMENTS 

// given an array of integers nums sorted in ascending order, find the number of times the array is rotated
// if the array is not rotated return 0

// e.g nums = [1, 2, 3, 4, 5], output = 0
// e.g nums = [5, 6, 1, 2, 3, 4], output = 1
// e.g nums = [1, 2, 3, 4, 5, 6], output = 0

// T.C - O(log n)
// S.C - O(1)

// arr = {15, 18, 2, 3, 6, 12}
// The minimum element 2 is at index 2, so the array is rotated 2 times.

// approach
// A sorted array rotated k times has its minimum element at index k.
// In a rotated sorted array:
// The minimum element is the only element smaller than its previous element.
// Use Binary Search to find that minimum element.

// at each mid you need to identify if in which window you are 
// the result will be in second half of the window if the array is rotated
// to find which half you are in compare the middle element with the last element

// for the second half all elements will be <= to the last element 
// for the first half all the elements will be > to the last element

// Elements in the right sorted part are <= nums[n-1]
// Elements in the left sorted part are > nums[n-1]

// ONLY WORKS FOR DISTINCT ELEMENTS 

int numberOfTimesRotated(vector<int>& nums) {

    int n = nums.size();
    int l = 0, r = n - 1;

    // not rotated
    if(nums[l] <= nums[r])
        return 0;

    while(l <= r) {

        int mid = l + (r - l) / 2;

        if(mid == 0 || nums[mid] < nums[mid - 1])
            return mid;
        
        // second half - this will contain the minimum element
        if(nums[mid] <= nums[n - 1])
            r = mid - 1;
        else 
            l = mid + 1;
    }

    return 0;
}

// CLEANER SOLUTION WITH RESULT APPROACH
// ONLY WORKS FOR DISTINCT ELEMENTS

// Referring to Errichto's video
// Consider the elements are partitioned into a set of True and False
// Now we need to find the first True which satisfies the condition of less than the last element
// 5 6 7 1 2 3 
// F F F T T T 
// when the condition is - is the current element less than the last element?
// if we are in the second half - we save the result - can be a possible answer and keep looking on the left side
// if we are in the first half - answer will be in the right side - so me move to the right side 

int numberOfTimesRotated(vector<int>& nums) {

    int n = nums.size();
    int l = 0;
    int r = n - 1;
    int result = -1;

    if(nums[0] < nums[n - 1]) return 0;

    while(l <= r) {

        int mid = l + (r - l) / 2;

        // we are in the second half of the array
        // this can be a possible answer 
        // we can still find smallest element on the left side
        // keep looking on the left side
        if(mid > 0 && nums[mid] < nums[n - 1]) {
            result = mid;
            r = mid - 1;
        }
        else 
            l = mid + 1;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
// PROOBLEM - 2
// FIND AN ElEMENT IN ROTATED SORTED ARRAY

// given an array of integers nums rotated at some index
// find the index of an element target if it is in nums

// approach
// on the basis of above logic find the index at which the array got rotated
// look for the target element in that window

// for the second half all elements will be <= to the last element 
// for the first half all the elements will be > to the last element

int search(vector<int>& nums, int target) {

    int pivot = numberOfTimesRotated(nums);
    int n = nums.size();

    int l, r;

    if (pivot == 0) {
        l = 0;
        r = n - 1;
    }
    else if (target <= nums[n - 1]) {
        l = pivot;
        r = n - 1;
    }
    else {
        l = 0;
        r = pivot - 1;
    }

    // regular binary search
    while (l <= r) {
        int mid = l + (r - l) / 2;

        if (nums[mid] == target)
            return mid;
        else if (nums[mid] < target)
            l = mid + 1;
        else
            r = mid - 1;
    }

    return -1;
}
