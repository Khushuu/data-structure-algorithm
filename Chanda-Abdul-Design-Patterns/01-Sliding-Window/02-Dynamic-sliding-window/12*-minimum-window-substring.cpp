// 76. Minimum Window Substring
// VERY VERY IMPORTANT PROBLEM
// Dynamic Sliding Window Problem

// Given two strings s and t of lengths m and n respectively, return the minimum window substring of s such that every character in t (including duplicates) is included in the window. If there is no such substring, return the empty string "".
// The testcases will be generated such that the answer is unique.

// A substring is a contiguous sequence of characters within the string.

// e.g s = "ADOBECODEBANC", t = "ABC"
// output = "BANC"
// Substring = "BANC"

// T.C - O(m + n)
// S.C - O(m + n)

class Solution {
public:
    string minWindow(string s, string t) {
        
        // similar to 567. Permutation in String & 
        // 438. Find All Anagrams in a String
        // only difference is instead of window of fixed size
        // this is a dynamic sliding window 

        // here in case we find the result we will keep trying to shrink window
        // to get the minimum window substring 
        // and keep updating result for each valid answer 

        unordered_map<char, int> freq;
        for(char c: t) freq[c]++;

        // dynamic sliding window
        int l = 0;
        int r = 0;
        int distinctCharsAvailable = freq.size();
        int startIndex = -1;
        int minLength = INT_MAX;

        while(r < s.size()) {

            if(freq.count(s[r])) {

                freq[s[r]]--;
                if(freq[s[r]] == 0)
                    distinctCharsAvailable--;
            }
            
            // shrink window until result is valid
            while(distinctCharsAvailable == 0) {
                
                // calculate result
                if(r - l + 1 < minLength) {
                    minLength = r - l + 1;
                    startIndex = l;
                }

                // shrink window
                if(freq.count(s[l])) {

                    freq[s[l]]++;
                    if(freq[s[l]] == 1)
                        distinctCharsAvailable++;
                }

                l++;
            }

            r++;
        }

        // if substring does not exist return empty string
        return startIndex == -1 ? "" : s.substr(startIndex, minLength);
    }
};