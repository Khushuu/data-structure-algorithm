// PROBLEM - 1
// MAXIMUM SUM SUBARRAY OF SIZE K

// given an array of integers and a number k, find the maximum sum of a subarray of size k
// e.g nums = [2, 1, 5, 1, 3, 2], k = 3
// output = 9 (subarray with maximum sum is [5, 1, 3])

int maximumSumSubarray(vector<int>& nums, int k) {
    
    // intialize l and r to 0
    int l = 0;
    int r = 0;
    int sum = 0;
    int result = INT_MIN;

    while(r < nums.size()) {

        // add current element to sum
        // this is done at the start of the loop because we want to compute current window
        // sum before checking if window size is k
        sum += nums[r];

        // check if window size is k
        // if it is then update result and remove leftmost element from sum and move left pointer
        if(r - l + 1 == k) {

            result = max(result, sum); // compute result
            sum -= nums[l]; // remove leftmost element from sum
            l++; // move left pointer
        }

        r++; // move right pointer
    }

    return result;
}

//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// PROBLEM - 2
// FIRST NEGATIVE INTEGER IN EVERY WINDOW OF SIZE K

// given an array of integers and a number k, find the first negative integer in every window of size k. 
// If there is no negative integer in a window, then print 0 for that window.

// e.g nums = [12, -1, -7, 8, -15, 30, 16, 28], k = 3
// output = [-1, -1, -15, 0, 0]

// T.C - O(n) 
// S.C - O(k) because in worst case, all the elements in the current window can be negative, so we need to store their indices in the queue
vector<int> firstNegativeInteger(vector<int>& nums, int k) {

    int l = 0;
    int r = 0;
    vector<int> result; 

    // maintain a queue that stores indices of the negative integers 
    // if an index is out of the current window, then remove it from the queue
    queue<int> q;

    while(r < nums.size()) {

        // if the current element is negative, then add its index to the queue
        if(nums[r] < 0) 
            q.push(r);
        
        // check if the size of the window is k 
        // if yes then check if the queue has any indices of negative integers in the current window
        if(r - l + 1 == k) {

            // remove all the indices from the queue that are out of the current window
            while(!q.empty() && q.front() < l)
                q.pop();
            
            // if the queue is empty, then no negative integer is present in the current window, so add 0 to the result
            // else add the first negative integer in the current window to the result
            if(q.empty())
                result.push_back(0);
            else
                result.push_back(nums[q.front()]);
            
            l++; // move left pointer
        }

        r++; // move right pointer
    }

    return result;
}

//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// PROBLEM - 3
// COUNT OCCURRENCES OF ANAGRAMS - IMPORTANT

// given a string text and a non-empty string ptr, find the count of the occurrences of anagrams of ptr in text.

// e.g text = "forxxorfxdofr", ptr = "for"
// output = 3 (anagrams of "for" are "for", "orf", "rfo", "ofr", "fro", "rof". The anagrams of "for" present in "forxxorfxdofr" are "for", "orf", "ofr")

// T.C - O(n) 
// S.C - O(n)

// approach - 1 NOT SUGGESTED 
// CONSTANT ERASE OPERATION 

// firstly in a hashmap freq count the frequency of characters in ptr
// then loop through the text and maintain a window of size equal to the length of ptr
// for each character in the window, decrement its frequency in the hashmap
// if the frequency of any character becomes negative, theat means the current window is not an anagram of ptr 
// if the frequency of a character becomes zero, then remove it from the hashmap
// if the hashmap becomes empty, then the current window is an anagram of ptr
// now add the frequency of the leftmost character of the window back to the hashmap and move the left pointer
// return the count of the anagrams

int anagramCount(string text, string ptr) {

    unordered_map<char, int> freq;

    // count the frequency of characters in ptr
    for(char c : ptr)
        freq[c]++;
    
    int l = 0;
    int r = 0;
    int count = 0;
    int k = ptr.size();

    while(r < text.size()) {

        // decrement the frequency of the current character in the hashmap
        char c = text[r];
        freq[c]--;

        // if frequency of a character becomes 0, then remove it from the hashmap
        if(freq[c] == 0) 
            freq.erase(c);
        
        if(r - l + 1 == k) {

            // if the hashmap is empty, then the current window is an anagram of ptr
            if(freq.empty())
                count++;
            
            // add the frequency of the leftmost character of the window back to the hashmap
            char leftChar = text[l];
            freq[leftChar]++;
            
            // IMPORTANT - if frequency of a character becomes 0, then remove it from the hashmap here also 
            // because we are adding the frequency back to the hashmap, if it becomes 0, then we need to remove it from the hashmap
            if(freq[leftChar] == 0)
                freq.erase(leftChar);

            l++; // move left pointer
        }

        r++; // move right pointer
    }

    return count;
}

//----------------------------------------------------------------------------------------------------------------------

// approach - 2 BETTER APPROACH
// Using a variable to track if map size is zero or not instead of using the empty() and erase function

// ISSUES - you do not need to add the chars which are not there in the ptr string to the hashmap
// also you do not need to use empty() and erase function all the time but maintain a variable to check 
// if freq of all characters in the map is zero or not 

// also initialize the count variable with size of the freq map  
// only when the freq of a character becomes zero, we will decrement the count variable 
// which essentialy represents that the char got deleted instead of actually deleting from the map 
// and when the freq of a character becomes 1 when it leaves the window then increase the counter 

// NOTE:
// think of it like - variable represents - chars that can be used 
// use distinctCharsAvailableCount variable to show how many ditinct chars we still have with us that can be used to form an anagram
// when this becomes 0 it means in the window we have all the chars that we need to form an anagram and when it becomes 1 it means we are missing one char to form an anagram

int anagramCount(string text, string ptr) {
    
    unordered_map<char, int> freq;

    // count the frequency of characters in ptr
    for(char c : ptr)
        freq[c]++;
    
    int l = 0;
    int r = 0;
    int distinctCharsAvailableCount = freq.size(); // count of distinct characters in ptr
    int count = 0;
    int k = ptr.size();

    while(r < text.size()) {

        char c = text[r];

        // if the current character is present in the hashmap, then decrement its frequency
        if(freq.count(c) > 0) {
            freq[c]--;

            // if frequency of a character becomes 0, then decrement the count variable
            if(freq[c] == 0)
                distinctCharsAvailableCount--;
        }

        if(r - l + 1 == k) {

            // if count variable is 0, then the current window is an anagram of ptr
            // deduce result - all chars have been used to form an anagram
            if(distinctCharsAvailableCount == 0)
                count++;
            
            char leftChar = text[l];

            // shrink the window from the left and 
            // add the frequency of the leftmost character of the window back to the hashmap
            // if the leftmost character of the window is present in the hashmap, then increment its frequency
            if(freq.count(leftChar) > 0) {
                freq[leftChar]++;

                // if frequency of a character becomes 1, then increment the distinctCharsAvailableCount variable
                if(freq[leftChar] == 1)
                    distinctCharsAvailableCount++;
            }

            l++; // move left pointer
        }

        r++; // move right pointer
    }

    return count;
}

//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------

// PROBLEM - 4
// MAXIMUM OF ALL SUBARRAYS OF SIZE K
// given an array of integers and a number k, find the maximum of all subarrays of size k

// e.g nums = [1, 3, -1, -3, 5, 3, 6, 7], k = 3
// output = [3, 3, 5, 5, 6, 7]

// approach - 1 - NOT SUITABLE 
// sliding window approach - Using max heap (priority queue) to find the maximum of each window of size k
// store the element and its index in the max heap 
// when the size of the window is k then push the element at the top of the max heap to the result 
// also remove the elements from the max heap that are out of the current window
// store (value, index) in the max heap 
// keep popping the stale index elements from the heap

// T.C - O(n log k) because we are pushing and popping elements from the priority queue for each window of size k
// S.C - O(k) because in worst case, all the elements in the current window

vector<int> maximumOfAllSubarrays(vector<int>& nums, int k) {

    priority_queue<pair<int, int>> maxHeap; // max heap to store (value, index)
    vector<int> result;

    int l = 0;
    int r = 0; 

    while(r < nums.size()) {

        maxHeap.push({nums[r], r}); 

        // when the size of the window is k then move the stale data from the max heap 
        // push the element at the top of the max heap to the result 

        if(r - l + 1 == k) {

            while(!maxHeap.empty() && maxHeap.top().second < l) // remove the elements from the max heap that are out of the current window
                maxHeap.pop();
            
            result.push_back(maxHeap.top().first);
            l++; // move left pointer
        }

        r++; // move right pointer
    }

    return result;
}

//-------------------------------------------------------------------------------------------------------
// approach - 2 - BETTER APPROACH
// using a deque to find the maximum of each window of size k

// maintain a deque that stores the indices of the elements in the current window of size k
// the elements in the deque are in decreasing order of their values in the nums array
// keep popping the elements from the back of the deque if they are smaller than the current element 
// why 
// because they cannot be the maximum of the current window or any future window if they are smaller than the current element
// when the size of the window is k then push the element at the front of the deque to the result 
// also remove the elements from the front of the deque that are out of the current window

// T.C - O(n) because we are pushing and popping elements from the deque for each window of size k
// S.C - O(k) because in worst case, all the elements in the current window

vector<int> maximumOfAllSubarrays(vector<int>& nums, int k) {

    deque<int> dq;
    vector<int> result;

    int l = 0, r = 0;

    while (r < nums.size()) {

        // Remove indices outside current window
        while (!dq.empty() && dq.front() < l)
            dq.pop_front();

        while (!dq.empty() && nums[dq.back()] <= nums[r])
            dq.pop_back();

        dq.push_back(r);

        if (r - l + 1 == k) {
            result.push_back(nums[dq.front()]);
            l++;
        }

        r++;
    }

    return result;
}

//-----------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------  
