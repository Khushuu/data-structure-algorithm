// PROBLEM - 1
// kth smallest element 

// given an array of integers nums and an integer k, find the kth smallest element in the array. 
// Note that it is the kth smallest element in the sorted order, not the kth distinct element.

// e.g nums = [3, 2, 1, 5, 6, 4], k = 2, output = 5
// e.g nums = [3, 2, 3, 1, 2, 4, 5, 5, 6], k = 4, output = 4

// T.C - O(n log k) because we are pushing and popping elements from the priority queue for each window of size k
// S.C - O(k) because in worst case, all the elements in the current window 

// Using maxHeap 

// push the elements of the array into the maxHeap
// if the size of the array is greater than k then pop the top element from the maxHeap
// return the top element of the maxHeap

// why this works
// because we keep popping the elements greater than the kth smallest element from the maxHeap
// and then the kth smallest element will be the top element of the maxHeap

int kthSmallest(vector<int>& nums, int k) {

    priority_queue<int> maxHeap; // max heap to store the elements

    for(int num: nums) {

        maxHeap.push(num);

        if(maxHeap.size() > k) 
            maxHeap.pop();
    }

    return maxHeap.top();
}