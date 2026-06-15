// PROBLEM - 1
// TOP K FREQUENT ELEMENTS

// given an array of integers nums and an integer k, return the k most frequent elements. 
// You may return the answer in any order.

// e.g nums = [1, 1, 1, 2, 2, 3], k = 2, output = [1, 2]
// e.g nums = [1], k = 1, output = [1]

// T.C - O(n log k) because we are pushing and popping elements from the priority queue for each window of size k
// S.C - O(k) for minHeap

// Using minHeap
// push a pair of frequency of element and element into the minHeap
// when the size of the array is greater than k then pop the top element from the minHeap
// push all the elements of the minHeap into the result - the ones with the higher frequency will be at the top

// why this works
// because we keep popping the elements with lower frequency from the minHeap
// and the top element of the minHeap will be the element with the k highest frequency

// T.C - O(n log k) because we are pushing and popping elements from the priority queue for each window of size k
// S.C - O(k) for minHeap 

vector<int> topKFrequent(vector<int>& nums, int k) {

    unordered_map<int, int> freq; // map to store the frequency of each element
    // min heap to store the elements
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap; 
    vector<int> result;

    for(int num: nums) 
        freq[num]++;
    
    for(auto &[num, count]: freq) {

        minHeap.push({count, num});

        if(minHeap.size() > k) 
            minHeap.pop();
    }

    while(!minHeap.empty()) {
        
        result.push_back(minHeap.top().second);
        minHeap.pop();
    }

    return result;
    
}

// PROBLEM - 2
// FREQUENCY SORT

// Given an array of integers nums, sort the elements in decreasing order of their frequency.
// If two numbers have the same frequency, the order between them can be arbitrary (unless the problem specifies otherwise).
// Return the array after sorting according to frequency.

// Example
// nums = [1, 1, 1, 3, 2, 2, 4]
// Output
// [1, 1, 1, 2, 2, 3, 4]

// T.C - O(n log k) because we are pushing and popping elements from the priority queue for each window of size k
// S.C - O(k) for minHeap

// Heap Approach
// Count the frequency of every element using a hash map.
// Store (frequency, element) in a max heap.
// Continuously extract the element with the highest frequency.
// Insert that element into the answer frequency times.

#include <bits/stdc++.h>
using namespace std;

vector<int> frequencySort(vector<int>& nums) {
    unordered_map<int, int> freq;

    // Count frequencies
    for (int num : nums) {
        freq[num]++;
    }

    // Max Heap {frequency, element}
    priority_queue<pair<int, int>> maxHeap;

    for (auto &it : freq) {
        maxHeap.push({it.second, it.first});
    }

    vector<int> result;

    while (!maxHeap.empty()) {

        int count = maxHeap.top().first;
        int num = maxHeap.top().second;
        maxHeap.pop();

        while (count--) {
            result.push_back(num);
        }
    }

    return result;
}

int main() {
    vector<int> nums = {1, 1, 1, 3, 2, 2, 4};

    vector<int> ans = frequencySort(nums);

    for (int x : ans) {
        cout << x << " ";
    }

    return 0;
}

