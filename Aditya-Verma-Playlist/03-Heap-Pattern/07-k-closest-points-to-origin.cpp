// PROBLEM - 1
// K CLOSEST POINTS TO ORIGIN

// given an array of points on the plane and a number k, find the k closest points to the origin (0, 0)

// e.g points = [[3, 3], [5, -1], [-2, 4]], k = 2
// output = [[-2, 4], [3, 3]]

// T.C - O(n log k) because we are pushing and popping elements from the priority queue for each window of size k
// S.C - O(k) for maxHeap

// Complexities:

// Time: O(n log k)
// Space: O(k)

// For the K Closest Points to Origin problem, a max heap of size k is an efficient approach.

// Compute the squared distance of each point from the origin:

// d = x*x + y*y
// (No need to calculate the square root since relative ordering remains the same.)

// Maintain a max heap containing at most k points.
// For each point:
// Push (distance, point) into the heap.
// If heap size exceeds k, remove the top element (the farthest point among the current k+1 points).
// After processing all points, the heap contains the k closest points.

// Instead of having a maxHeap of pair<long long, vector<int>> you can have a maxHeap of pair<long long, pair<int, int>> or 
// a max heap of pair<long long, int> to store distance from origin and index of the pair 
// at the time of popping from maxheap and pusing to result vector - just insert the pair or value at index in the result array

class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        priority_queue<pair<long long, vector<int>>> maxHeap;

        for (auto& point : points) {
            long long dist = 1LL * point[0] * point[0] +
                             1LL * point[1] * point[1];

            maxHeap.push({dist, point});

            if (maxHeap.size() > k) {
                maxHeap.pop(); // remove farthest point
            }
        }

        vector<vector<int>> result;

        while (!maxHeap.empty()) {
            result.push_back(maxHeap.top().second);
            maxHeap.pop();
        }

        return result;
    }
};


// Example

// Input:

// points = {{1,3}, {-2,2}, {5,8}}
// k = 2

// Distances:

// (1,3)   -> 10
// (-2,2)  -> 8
// (5,8)   -> 89

// Heap operations:

// Push 10
// Push 8
// Push 89 -> size becomes 3 > k
// Pop 89

// Remaining points:

// (-2,2), (1,3)


// Time Complexity

// Let:
// n = number of points
// Heap size is maintained at k

// For each point:

// Push: O(log k)
// Possible pop: O(log k)

// T.C : O(nlogk)


// Space Complexity
// The heap stores at most k elements:
// O(k)


// Why Max Heap?

// A min heap would keep the closest point at the top, making it difficult to remove the farthest when the size exceeds k.
// A max heap keeps the farthest among the current k points at the top, so whenever a closer point arrives and size exceeds k, the farthest can be removed in O(log k) time.

