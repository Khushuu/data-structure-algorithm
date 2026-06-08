// VARIABLE SIZE SLIDING WINDOW

// PROBLEM - 1
// LONGEST SUBARRAY OF SUM K

// only applicable for non-negative integers because if there are negative integers, then we cannot be sure if we need to shrink the window or expand the window when the sum of the current window is greater than k
// given an array of integers and a number k, find the length of the longest subarray whose sum is equal to k

// e.g nums = [1, 2, 3, 4, 5], k = 5    
// output = 2 (subarray with sum k is [2, 3])

// T.C - O(n) because we are traversing the array once
// S.C - O(1) 

int largestSubarraySumK(vector<int>& nums, int k) {
    
    int l = 0;
    int r = 0;
    long long sum = 0;
    int result = 0;

    while (r < nums.size()) {
        
        sum += nums[r];

        while (l <= r && sum > k) {
            sum -= nums[l];
            l++;
        }

        if (sum == k) 
            result = max(result, r - l + 1);

        r++;
    }

    return result;
}

//----------------------------------------------------------------------------------------------------------------------
// PROBLEM - 2
// MAXIMUM SUBSTRING WITH K DISTINCT CHARACTERS

// given a string and a number k, find the length of the longest substring with k distinct characters

// s = "aabacbebebe"
// k = 3
// Output = 7
// Substring = "cbebebe"

// T.C - O(n) because we are traversing the string once
// S.C - O(1) because we are storing the frequency of characters in a hashmap and the number of distinct characters can be at most 26 (if we are considering only lowercase letters)

int longestSubstringWithKDistinctCharacters(string s, int k) {
    
    int l = 0;
    int r = 0;
    int result = 0; 

    unordered_map<char, int> freq;

    while (r < s.size()) {

        freq[s[r]]++;

        // shrink window until the number of distinct characters in the current window is less than or equal to k
        while (freq.size() > k) {

            freq[s[l]]--;

            if (freq[s[l]] == 0)
                freq.erase(s[l]);

            l++;
        }

        if(freq.size() == k)
            result = max(result, r - l + 1);

        r++;
    }

    return result;
}

//----------------------------------------------------------------------------------------------------------------------
// PROBLEM - 3
// LONGEST SUBSTRING WITHOUT REPEATING CHARACTERS

// given a string, find the length of the longest substring without repeating characters

// s = "abcabcbb"   
// Output = 3
// Substring = "abc"

// T.C - O(n) because we are traversing the string once
// S.C - O(1) because we are storing the frequency of characters in a hashmap and the number of distinct characters can be at most 26 (if we are considering only lowercase letters)    

int longestSubstringWithoutRepeatingCharacters(string s) {
    
    int l = 0;
    int r = 0;
    int result = 0; 
    unordered_map<char, int> freq;

    while (r < s.size()) {
        
        freq[s[r]]++;

        // shrink window until there are no repeating characters in the current window
        while (freq[s[r]] > 1) {

            freq[s[l]]--;

            if (freq[s[l]] == 0)
                freq.erase(s[l]);

            l++;
        }

        result = max(result, r - l + 1);

        r++;
    }

    return result;
}

//-------------------------------------------------------------------------------------------------------

// approach - 2 
// using a set to find the longest substring without repeating characters

int longestSubstringWithoutRepeatingCharacters(string s) {
    
    int l = 0;
    int r = 0;
    int result = 0; 
    unordered_set<char> set;

    while (r < s.size()) {
        
        // if the current character is already present in the set, then shrink the window from the left until the current character is not present in the set
        while (set.count(s[r]) > 0) {
            set.erase(s[l]);
            l++;
        }

        set.insert(s[r]);
        result = max(result, r - l + 1);

        r++;
    }

    return result;
}

//-------------------------------------------------------------------------------------------------------

// approach - 3 - MOST OPTIMAL
// When you see a repeated character, you don’t move l step-by-step.
// You jump it forward directly.

// Why this works

// Suppose:
// s = "abba"

// When we reach index 2 ('b' again), we already saw 'b' at index 1.
// So the valid window cannot include that old 'b'.

// We must ensure:
// l > last_seen['b']

// So we do:

// l = max(l, last_seen['b'] + 1);
// Important trick: max(l, ...)

// We use max because:
// l should never move backwards
// Sometimes the previous occurrence is already outside the window

// T.C - O(n) because we are traversing the string once
// S.C - O(1) because we are storing the last seen index of characters in a vector
int lengthOfLongestSubstring(string s) {

    vector<int> lastSeen(256, -1);

    int l = 0;
    int r = 0;
    int result = 0;

    while(r < s.size()) {

        l = max(l, lastSeen[s[r]] + 1); // move the left pointer to the right of the last seen index of the current character
        lastSeen[s[r]] = r; // update the last seen index of the current character
        result = max(result, r - l + 1);
    }

    return result;
}

// -----------------------------------------------------------------------------------------------------------------------

// PROBLEM - 4
// PICK TOYS

// given an array of integers representing the types of toys and a number k, find the length of the longest subarray that contains at most k distinct types of toys

// e.g toys = aabacc, k = 2
// output = 4 (subarray with at most 2 distinct types of toys is "aaba")

// T.C - O(n) because we are traversing the array once
// S.C - O(1) because we are storing the frequency of toys in a hashmap and the number of distinct toys can be at most 26 (if we are considering only lowercase letters)

// just a variation of the longest substring with k distinct characters problem

int pickToys(string toys) {
    
    int l = 0;
    int r = 0;
    int result = 0; 
    unordered_map<char, int> freq;

    while (r < toys.size()) {
        
        freq[toys[r]]++;

        // shrink window until there are no more than 2 distinct toys in the current window
        while (freq.size() > 2) {

            freq[toys[l]]--;

            if (freq[toys[l]] == 0)
                freq.erase(toys[l]);

            l++;
        }

        if(freq.size() == 2)
            result = max(result, r - l + 1);

        r++;
    }

    return result;
}

//-----------------------------------------------------------------------------------------------------------------------

// Very IMPORTANT PROBLEM 
// PROBLEM - 5
// MINIMUM WINDOW SUBSTRING

// given a string s and a string t, find the minimum window in s which will contain all the characters in t

// s = "ADOBECODEBANC"
// t = "ABC"
// Output = "BANC"

// T.C - O(n) because we are traversing the string once
// S.C - O(1) because we are storing the frequency of characters in a hashmap and the number of distinct characters can be at most 26 (if we are considering only lowercase letters)

// approach
// We maintain a window [l, r] on s and track:
// How many required characters we have matched
// Shrink window when valid
// Expand when invalid

string minWindow(string text, string ptr) {

    unordered_map<char, int> freq;

    // count frequency of characters in ptr
    for (char c : ptr)
        freq[c]++;

    int l = 0;
    int r = 0;

    int distinctCharsAvailableCount = freq.size();
    int result = INT_MAX;   // stores min length (instead of number of matches)
    int start = 0;         // starting index of answer window

    while (r < text.size()) {

        char c = text[r];

        // expand window: reduce freq if character is needed
        if (freq.count(c) > 0) {
            freq[c]--;

            if (freq[c] == 0)
                distinctCharsAvailableCount--;
        }

        // WHEN WINDOW IS VALID (all required chars satisfied)
        while (distinctCharsAvailableCount == 0) {

            // update answer (min window)
            if (r - l + 1 < result) {
                result = r - l + 1;
                start = l;
            }

            char leftChar = text[l];

            // shrink window from left
            if (freq.count(leftChar) > 0) {
                freq[leftChar]++;

                if (freq[leftChar] == 1)
                    distinctCharsAvailableCount++;
            }

            l++;
        }

        r++;
    }

    return (result == INT_MAX) ? "" : text.substr(start, result);
}