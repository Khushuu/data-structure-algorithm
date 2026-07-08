// PROBLEM - 1
// VERY IMPORTANT
// Longest Substring with at most K Distinct Characters 
// Dynamic Sliding Window Problem


// https://leetcode.com/problems/longest-substring-with-at-most-k-distinct-characters/

// Given a string, find the length of the longest substring in it with no more than K distinct characters.
// You can assume that K is less than or equal to the length of the given string.

// e.g s = "eceba", k = 2
// output = 3
// Substring = "ece"

// Intuition

// We need the longest valid window.
// Whenever the window contains more than k distinct characters, it becomes invalid, so we shrink it from the left until it becomes valid again.
// This is a classic Sliding Window problem.

// Approach

// Maintain:

// left → left boundary of the window
// right → right boundary
// Hash map storing frequency of characters inside the current window.

// As we expand the window:

// Add the current character.
// If the number of distinct characters becomes greater than k,
// Remove characters from the left.
// Erase a character from the map when its frequency becomes zero.
// Update the maximum window size.

// T.C = O(n)
// S.C = O(k)

class Solution {
public:
    int lengthOfLongestSubstringKDistinct(string s, int k) {

        int l = 0;
        int r = 0;
        unordered_map<char, int> freq;
        int result = 0;

        while (r < s.size()) {

            freq[s[r]]++; // add to the window

            while (freq.size() > k) {

                freq[s[l]]--;

                if (freq[s[l]] == 0)
                    freq.erase(s[l]);

                l++;
            }

            // deduce result
            result = max(result, r - l + 1);

            r++;
        }

        return result;
    }
};