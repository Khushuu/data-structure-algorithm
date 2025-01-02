class MedianFinder {
public:
    // use two heaps - maxHeap and minHeap
    // maxHeap can have one extra element 
    // maxHeap.size() - minHeap.size() <= 1
   
     priority_queue<int> maxHeap;
     priority_queue<int, vector<int>, greater<int>> minHeap;   

    void addNum(int num) {
        
		// push to maxHeap first
        maxHeap.push(num);
        int top = maxHeap.top();
        maxHeap.pop();

		// reshuffle and push to minHeap
        minHeap.push(top);

		// maxHeap stores the extra element 
		// if size of minHeap becomes more than maxHeap extract the item and put in maxHeap
        if(minHeap.size() > maxHeap.size()) {
            top = minHeap.top();
            minHeap.pop();
            maxHeap.push(top);
        }
    }
    
    double findMedian() {
        
        int size = minHeap.size() + maxHeap.size();

        if(size % 2) return maxHeap.top() * 1.0;

        return (minHeap.top() + maxHeap.top()) / 2.0;
    }
};
