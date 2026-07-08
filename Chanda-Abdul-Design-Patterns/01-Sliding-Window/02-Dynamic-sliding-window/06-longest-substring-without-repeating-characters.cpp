// PROBLEM - 1
// 3. Longest Substring Without Repeating Characters
// Dynamic Sliding Window Problem
// VERY IMPORTANT PROBLEM

// Given a string s, find the length of the longest substring without repeating characters.

// e.g s = "abcabcbb"
// output = 3
// Substring = "abc"

// approach - 1

// maintain a freq map 
// add the character to the window and increment its frequency
// if the freq map size is greater than 1, remove the character from the window and decrement its frequency
// return the size of the window

// T.C - O(n)
// S.C - O(1)

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        
        // sliding window approach
        // maintain a freq map
        // if the char count is > 1 keep popping to make window valid
        // compute result for valid window 

        int l = 0;
        int r = 0;
        int result = INT_MIN;
        unordered_map<char, int> freq;

        while(r < s.size()) {

            freq[s[r]]++;

            while(freq[s[r]] > 1) {
                freq[s[l]]--;
                l++;
            }

            result = max(result, r - l + 1);
            r++;
        }

        return result == INT_MIN ? 0 : result;
    }   
};

// approach - 2
// using hash set

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        
        // using set 
        // if an item is already present in the set then contrast window
        // remove all the items that leave the window from the set
        // when the count becomes 0 for the already seen item
        // add it to the set and deduce result

        unordered_set<char> hashSet;
        int n = s.size();
        int result = 0;
        int l = 0;
        int r = 0;

        while(r < n) {
            
            // while the set has s[r] char - contrast window from left
            while(l < n && hashSet.count(s[r])) {
                hashSet.erase(s[l]);
                l++;
            }

            hashSet.insert(s[r]);
            result = max(result, r - l + 1);
            r++;
        }

        return result;
    }
};

// approach - 3
// most efficient approach

// instead of storing freq of chars, store the index of the char in the map
// if the char is already present in the map, then move the left pointer to the right
// of the last seen index of the char
// it will be the max of l and the last seen index + 1

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        
        // sliding window problem
        // keep a mapping of char and its index 
        // if a char is already present in the index 
        // then contrast the window from the left
        // l will be max of l and the new index + 1
        // and update the index for char in map

        int l = 0;
        int r = 0;
        int result = 0;
        unordered_map<char, int> hashMap;

        while(r < s.size()) {

            if(hashMap.count(s[r])) 
                l = max(l, hashMap[s[r]] + 1);

            result = max(result, r - l + 1);
            hashMap[s[r]] = r;
            r++;
        }

        return result;
    }
};