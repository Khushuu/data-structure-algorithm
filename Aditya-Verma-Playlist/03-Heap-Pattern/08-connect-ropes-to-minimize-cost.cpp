// Problem: 1
// Connect Ropes to Minimize Cost

// Given rope lengths, connect all ropes into one rope with minimum total cost.
// Cost of connecting two ropes = sum of their lengths.

// Example
// Ropes = [4, 3, 2, 6]

// Connect 2 and 3 -> cost = 5
// Ropes become [4, 5, 6]

// Connect 4 and 5 -> cost = 9
// Total cost = 5 + 9 = 14
// Ropes become [6, 9]

// Connect 6 and 9 -> cost = 15
// Total cost = 14 + 15 = 29

// Answer = 29

// Key Observation

// Whenever we connect two ropes, the resulting rope is used again in future connections.
// So if we choose a large rope early, its length contributes multiple times to the total cost.
// Therefore, we should always connect the two smallest ropes first.
// This is exactly the same greedy idea used in Huffman Coding.

// Why Connecting Smallest Ropes First Works

// Consider:

// [2, 3, 100]
// Optimal
// 2 + 3 = 5      cost = 5
// 5 + 100 = 105  cost = 105

// Total = 110
// Bad Choice
// 100 + 3 = 103   cost = 103
// 103 + 2 = 105   cost = 105

// Total = 208

// Huge difference.

// The large rope (100) got involved twice, causing much larger cost.

// Hence:

// To minimize repeated contribution of large lengths, always merge the smallest ropes first.

// Data Structure Needed
// At every step we need:
// Smallest rope
// Second smallest rope

// A Min Heap gives both efficiently.

// Operations:

// Extract Min -> O(log n)
// Insert      -> O(log n)

// Algorithm:

// Put all rope lengths into a min heap.
// While heap size > 1:
// Take two smallest ropes.
// Connect them.
// Add connection cost to answer.
// Insert the new rope back into heap.

// Return total cost.
// Dry Run

// Ropes = [4,3,2,6]

// Min Heap:

// [2,3,4,6]
// Step 1
// Take 2,3

// cost = 5
// total = 5

// Push 5

// Heap:
// [4,5,6]
// Step 2
// Take 4,5

// cost = 9
// total = 14

// Push 9

// Heap:
// [6,9]
// Step 3
// Take 6,9

// cost = 15
// total = 29

// Push 15

// Heap:
// [15]

// Stop.

// Answer:
// 29

// Time Complexity: O(n log n)
// Space Complexity: O(n)

class Solution {
public:
    long long minCost(vector<long long>& ropes) {

        // better than looping all elements of ropes and doing push on the minHeap
        // internally uses make_heap function - heapify 
        // time complexity - O(n) 
        // for push time complexity would have been O(n log n)
        priority_queue<
            long long,
            vector<long long>,
            greater<long long>
        > minHeap(ropes.begin(), ropes.end());

        long long totalCost = 0;

        while (minHeap.size() > 1) {

            long long first = minHeap.top();
            minHeap.pop();

            long long second = minHeap.top();
            minHeap.pop();

            long long cost = first + second;
            totalCost += cost;

            minHeap.push(cost);
        }

        return totalCost;
    }
};

// Time Complexity

// Let n be the number of ropes.

// Building Heap: O(n)

// Loop: Runs n - 1 times.

// Each iteration:
// 2 pops  -> O(log n)
// 1 push  -> O(log n)

// Total: O((n-1) * log n) = O(n log n)

// Overall
// Time Complexity: O(n log n)
// Space Complexity: O(n)

// Heap stores all ropes.
// Space Complexity: O(n)

// Interview Explanation (Short)

// Since every merged rope participates in future merges, we want smaller ropes to contribute multiple times 
// and delay larger ropes as much as possible. 
// Therefore, we greedily connect the two smallest ropes at every step. 
// A min heap efficiently gives the two smallest ropes in O(log n) time, leading to an overall complexity of O(n log n) and O(n) space.