// 139. Word Break
// Given a string s and a dictionary of strings wordDict
// return true if s can be segmented into a space-separated sequence of one or more dictionary words.
// Note that the same word in the dictionary may be reused multiple times in the segmentation.

// s = "leetcode", wordDict = ["leet","code"]
// output =  true

// in this problem if any of the path reaches the end of the string
// that means we have found a valid partition
// store all words of wordDict into an unordered set for faster lookup
// instead of exploring all partions if any path returns true
// return true to the main function 
// also there is no need to store the actual words here
// so we do not need any temp words vector or a result vector

// Recursive solution -- gives TLE
// T.C = o(2^n)
// Space Complexity = O(n + m)
// Recursive Stack: At most O(n) calls in the recursion stack.
// Dictionary Storage: O(m), where m is the number of words in wordDict
// --------------------------------------------------------------------------------------------

class Solution {
private:
    bool partition(int start, string &s, unordered_set<string>& dict) {

        if(start == s.size()) return true;

        for(int end = start; end < s.size(); end++) {

            // check if the word from start to end exists in the dict
            // if yes go for futher partitions
            // if any call returns true return true
            string word = s.substr(start, end - start + 1);
            if(dict.find(word) != dict.end() && partition(end + 1, s, dict)) {
                return true;
            }
        }

        return false;
    }
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        
        unordered_set<string> dict(wordDict.begin(), wordDict.end());

        return partition(0, s, dict);
    }
};

// --------------------------------------------------------------------------------------------

// Memoization solution

// We can cache results of substrings using memoization, reducing redundant calculations.
// If a substring from start is already computed, return the cached result.
// we cache result for substrings starting from a fixed index - i.e start position
// Reduce function calls by iterating through the string only once.

// T.C = O(n^2)
// Space Complexity = O(n + m)
// Memoization Storage: O(n) for storing substring results.
// Dictionary Storage: O(m), where m is the number of words in wordDict

// --------------------------------------------------------------------------------------------

class Solution {
private:
    unordered_map<int, bool> memo; // Memoization to store results

    bool partition(int start, string &s, unordered_set<string> &dict) {

        if (start == s.size()) return true; // Base case: reached end of the string
        if (memo.count(start)) return memo[start]; // Return cached result

        for (int end = start; end < s.size(); end++) {

            string word = s.substr(start, end - start + 1);

            if (dict.find(word) != dict.end() && partition(end + 1, s, dict)) {
                return memo[start] = true; // Store result in memo
            }
        }
        return memo[start] = false; // Store result in memo
    }

public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> dict(wordDict.begin(), wordDict.end());
        return partition(0, s, dict);
    }
};

// -------------------------------------------------------------------------------------------


