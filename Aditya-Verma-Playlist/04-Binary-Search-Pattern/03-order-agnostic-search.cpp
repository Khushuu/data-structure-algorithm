// PROBLEM - 1
// ORDER AGNOSTIC BINARY SEARCH

// Order Agnostic Binary Search means the array is sorted, 
// but you don't know whether it's sorted in **ascending** or **descending** order. 
// The goal is to find a target in **O(log n)** time.

// Approach

// 1. Determine the order:

//    bool isAsc = arr[0] < arr[n - 1];

// 2. Perform normal binary search.
// 3. Reverse the comparison logic if the array is descending.

// ---

int orderAgnosticBinarySearch(vector<int>& arr, int target) {

    int l = 0;
    int r = arr.size() - 1;

    bool isAsc = arr[l] < arr[r];

    while (l <= r) {
        int mid = l + (r - l) / 2;

        if (arr[mid] == target)
            return mid;

        if (isAsc) {
            if (target < arr[mid])
                r = mid - 1;
            else
                l = mid + 1;
        } else {
            if (target < arr[mid])
                l = mid + 1;
            else
                r = mid - 1;
        }
    }

    return -1;
}

---

## Example 1 (Ascending)

vector<int> arr = {2, 4, 6, 8, 10, 12};
cout << orderAgnosticBinarySearch(arr, 8);

Output: 3

