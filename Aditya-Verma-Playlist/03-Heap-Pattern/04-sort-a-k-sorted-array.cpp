// PROBLEM - 1
// SORT A K-SORTED ARRAY ascending

// given a k sorted array 
// where a number can be k positions away from its sorted position
// sort the array

// e.g nums = [6, 5, 3, 2, 8, 10, 9], k = 3
// output = [2, 3, 5, 6, 8, 9, 10]

// approach - minHeap
// maintain a minheap of size k
// we are going to store the first k elements in the minHeap
// as soon as the size exceed k - remove the top element from the minHeap
// and push it to the result 

// why this works
// as the position of each element in the array can only be k positions away from its sorted position

// once all the elements in the array are traversed
// pop the elments from the min heap and put them into the result array

// T.C - O(n log k)
// S.C - O(k)

vector<int> sortKSortedArray(vector<int>& nums, int k) {

    priority_queue<int, vector<int>, greater<int>> minHeap; // min heap to store the elements
    vector<int> result;

    for(int num: nums) {

        minHeap.push(num);

        if(minHeap.size() > k) {
            result.push_back(minHeap.top());
            minHeap.pop();
        }
    }

    while(!minHeap.empty()) {
        
        result.push_back(minHeap.top());
        minHeap.pop();
    }

    return result;
}