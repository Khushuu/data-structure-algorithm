// PROBLEM - 1
// K LARGEST ELEMENTS

// given an array of integers nums and an integer k, find the k largest elements in the array. 
// Note that it is the k largest elements in the sorted order, not the k largest distinct elements.

// e.g nums = [3, 2, 1, 5, 6, 4], k = 2, output = [5, 6]
// e.g nums = [3, 2, 3, 1, 2, 4, 5, 5, 6], k = 4, output = [5, 6, 6, 5]

// T.C - O(n log k) because we are pushing and popping elements from the priority queue for each window of size k
// S.C - O(k) for minHeap

// Using minHeap
// push the elements of the array into the minHeap
// when the size of the array is greater than k then pop the top element from the minHeap
// push all the elements of the minHeap into the result

// Why this works
// by using minHeap to find k largest elements 
// we will maintain the size of the minHeap as k
// and keep popping all the elements less than the kth largest element from the minHeap 
// as soon as the size of minHeap becomes more than k

vector<int> kLargestElements(vector<int>& nums, int k) {

    priority_queue<int, vector<int>, greater<int>> minHeap; // min heap to store the elements
    vector<int> result;

    for(int num: nums) {

        minHeap.push(num);

        if(minHeap.size() > k) 
            minHeap.pop();
    }

    while(!minHeap.empty()) {
        
        result.push_back(minHeap.top());
        minHeap.pop();
    }

    return result;
}