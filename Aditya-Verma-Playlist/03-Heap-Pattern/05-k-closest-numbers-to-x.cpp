// PROBLEM - 1
// K CLOSEST NUMBERS TO X

// Given a sorted array arr[] of size n, an integer k, and a target value x
// find the k numbers in the array that are closest to x.
// If two numbers have the same absolute difference from x, prefer the smaller number.
// Return the k closest numbers in ascending order.

// input
// arr = [1, 2, 3, 4, 5]
// k = 4
// x = 3

// output
// [1, 2, 3, 4]

// | Number | Difference |
// | ------ | ---------- |
// | 1      | 2          |
// | 2      | 1          |
// | 3      | 0          |
// | 4      | 1          |
// | 5      | 2          |

// The 4 closest elements are 3, 2, 4, 1.
// After sorting: [1, 2, 3, 4].

// approach

// Maintain a max heap of size k.

// For every element:
// Compute its difference from x = num - x
// Push {abs(difference), value} into the max heap.
// If heap size becomes greater than k, remove the top element (the farthest element).

// At the end, the heap contains exactly the k closest numbers.
// since we need to return answer in sorted order - sort result and return 

// T.C = O(n log k + k log k) [nlogk - for heap operating, klogk - for sorting]
// S.C = O(k)

vector<int> kClosest(vector<int>& nums, int k, int x) {
    priority_queue<pair<int, int>> maxHeap;

    for (int num : nums) {
        maxHeap.push({abs(num - x), num});

        if (maxHeap.size() > k) {
            maxHeap.pop();
        }
    }

    vector<int> result;

    while (!maxHeap.empty()) {
        result.push_back(maxHeap.top().second);
        maxHeap.pop();
    }

    // do not sort if order is not required
    sort(result.begin(), result.end());

    return result;
}
