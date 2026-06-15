# Identification

- some value k
- and asked to find smallest or largest value 
- Involves sorting in ascending or descending order 

- kth smallest element = maxHeap
- kth largest element = minHeap 

- Time complexity improves from nlogn for sorting to nlogk
- Y - because we maintain a heap of size k --> heapify for k elements will take nlogk time complexity

- kth largest element = minHeap 
    --> you only keep the top k largest elements - in min heap the smallest one is at the top
    --> so when only k largest element are filtered 
    --> the kth largest will be at the last 
    --> if this data is put in a min Heap - kth largest will be at the top of minHeap 

# how is it achieved
    --> we push the element in the min Heap
    --> if the size of the heap exceeds k then we pop the top element which will be the smallest
    --> this maintains the size of k
    --> at the end all the element smaller than the kth largest element and it will be the only one left
    --> making it the smallest in the n - k largest elements and as a result at the top of the minHeap

# NOTE: at all time we maintain the size of the heap as k to filter the top k elements 

####################################################################################################################

## Questions:

- kth smallest element
- return k largest elements

- sort a k sorted array - sort nearly sorted array 

- **k closest numbers** - **Important** - save pair of abs difference and num in maxheap
- **top k frequent numbers** - **Important** - save pair of freq of each number in minHeap 
- **frequency sort** - **VV Important**

- k closest points to origin
- connect ropes to minimize the cost 
- sum of elements between k1 smallest and k2 smallest numbers 

####################################################################################################################

# This is the pattern used in many heap problems such as:

* K Closest Numbers
* K Closest Points to Origin
* Top K Frequent Elements
* Frequency Sort
* Merge K Sorted Lists
* Kth Largest Element

where custom ordering is needed.