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

// T.C - O(n + m log m) => n for building result and O(mlogm) for minHeap insertion 
// worst case = O(nlongn) when m = n
// S.C - O(m) for minHeap

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

        int frequency = maxHeap.top().first;
        int element = maxHeap.top().second;
        maxHeap.pop();

        while (frequency--) {
            result.push_back(element);
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// IMPORTANT: SOLVING THIS PROBLEM USING COMPARE FUNCTION

// Instead of storing a `pair<int,int>` in the heap, you can create a custom class/struct and provide a comparator function (functor).
// For the **Frequency Sort** problem, store:

// ```cpp
// struct Node {
//     int element;
//     int frequency;
// };
// ```

// Then define a custom comparator.
// ---

// ## Using Custom Comparator

```cpp
#include <bits/stdc++.h>
using namespace std;

struct Node {
    int element;
    int frequency;
};

struct Compare {
    bool operator()(Node a, Node b) {
        return a.frequency < b.frequency;
    }
};

vector<int> frequencySort(vector<int>& nums) {

    unordered_map<int, int> freq;

    for (int num : nums)
        freq[num]++;

    priority_queue<Node, vector<Node>, Compare> maxHeap;

    for (auto &it : freq) {

        // all below approaches are equivalent and correct

        // Node curr;
        // curr.element = it.first;
        // curr.frequency = it.second;
        // maxHeap.push(curr);

        // maxHeap.push({it.first, it.second});

        maxHeap.push(Node{it.first, it.second});
    }

    vector<int> result;

    while (!maxHeap.empty()) {

        Node curr = maxHeap.top();
        maxHeap.pop();

        for (int i = 0; i < curr.frequency; i++) {
            result.push_back(curr.element);
        }
    }

    return result;
}

int main() {

    vector<int> nums = {1,1,1,3,2,2,4};

    vector<int> ans = frequencySort(nums);

    for (int x : ans)
        cout << x << " ";

    return 0;
}
```

// NOTE:
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Given:

struct Node {
    int element;
    int frequency;
};

// and

// priority_queue<Node, vector<Node>, Compare> maxHeap;

// then this line:

// maxHeap.push({it.first, it.second});

// does not create a pair.
// It uses aggregate initialization to construct a Node object.

// Equivalent to:

// Node temp;
// temp.element = it.first;
// temp.frequency = it.second;

// maxHeap.push(temp);

// or

// maxHeap.push(Node{it.first, it.second});

// Since Node has two members:

// struct Node {
//     int element;
//     int frequency;
// };

// the compiler interprets

// {it.first, it.second}

// as

// Node{it.first, it.second}

// because maxHeap.push() expects a Node.

// Example
// struct Node {
//     int x;
//     int y;
// };

// priority_queue<Node, vector<Node>, Compare> pq;

// pq.push({10, 20});

// Compiler sees:

// pq.push(Node{10, 20});

// not

// pair<int,int>{10,20}

// because the parameter type of push() is Node.

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// ## How the Comparator Works

struct Compare {
    bool operator()(Node a, Node b) {
        return a.frequency < b.frequency;
    }
};


// This means:
// Higher frequency => Higher priority

// Example:

// (1, freq=3)
// (2, freq=2)
// (3, freq=1)

// Heap top will be:
// (1, freq=3)
// because it has the largest frequency.


// ## If Tie-Breaking is Required

// Suppose the problem says:
// > If frequencies are equal, larger element comes first.
// Then:

struct Compare {
    bool operator()(Node a, Node b) {

        if (a.frequency == b.frequency)
            return a.element < b.element;

        return a.frequency < b.frequency;
    }
};

// Example:

// Input:
// [1,1,2,2,3]

// Frequencies:
// 1 -> 2
// 2 -> 2
// 3 -> 1

// Heap order:

// 2
// 1
// 3

// because frequencies are same and `2 > 1`.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NOTE:

// ### Easy Rule to Remember

// For a `priority_queue` comparator:

// return true;
// means
// "Put a below b"

// So:
// return a.element < b.element;

// ⇒ smaller element goes below larger element
// ⇒ **larger element comes first**

// while

// return a.element > b.element;

// ⇒ larger element goes below smaller element
// ⇒ **smaller element comes first**

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// ## Generic Heap Syntax with Comparator

struct Compare {
    bool operator()(Type a, Type b) {
        // return true when priority of a is lower than b
    }
};

// priority_queue<Type, vector<Type>, Compare> pq;

// This is the pattern used in many heap problems such as:

// * K Closest Numbers
// * K Closest Points to Origin
// * Top K Frequent Elements
// * Frequency Sort
// * Merge K Sorted Lists
// * Kth Largest Element

// where custom ordering is needed.


