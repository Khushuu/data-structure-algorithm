// PROBLEM - 1
// SEARCH IN NEARLY SORTED ARRAY

// given a nearly sorted array where each element is 1 position to the left or right of its correct position
// find the index of an element in the array
// if the element is not present in the array return -1

// approach
// along with comparing mid with target we also compare it with left or right adjacent elements
// this will help to find the correct position of the target element

// why we do mid > low and mid < high
// 

int searchNearlySorted(vector<int>& arr, int target) {
    int low = 0, high = arr.size() - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        // Check mid
        if (arr[mid] == target)
            return mid;

        // Check adjacent positions
        if (mid > low && arr[mid - 1] == target)
            return mid - 1;

        if (mid < high && arr[mid + 1] == target)
            return mid + 1;

        // Decide which half to search
        if (target < arr[mid])
            high = mid - 2;  // skip mid and mid-1
        else
            low = mid + 2;   // skip mid and mid+1
    }

    return -1; // Not found
}

// this works too - but we are checking outside the window range of low and high
if (mid > 0 && arr[mid - 1] == target)
    return mid - 1;

if (mid < n - 1 && arr[mid + 1] == target)
    return mid + 1;

// mid > low --> guarantees that mid - 1 is still inside the active search interval.
// arr = [10, 3, 40, 20, 50, 80, 70]
// target = 70

// After a few iterations, you might have:

// low = 6
// high = 6
// mid = 6

// The current search space contains only index 6.

// If you write:
// if (mid > 0 && arr[mid - 1] == target)
// you will check:
// arr[5]

// even though index 5 is outside the current search range.
// In this particular algorithm it won't necessarily produce a wrong answer, but you're examining an element that you've already ruled out.

// Using:
// mid > low
// guarantees that mid - 1 is still inside the active search interval.

