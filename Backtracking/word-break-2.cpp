// Given a string s and a dictionary of strings wordDict
// add spaces in s to construct a sentence where each words is a valid dictionary words. 
// Return all such possible sentences in any order.
// s = "catsanddog", wordDict = ["cat","cats","and","sand","dog"]
// output = ["cats and dog","cat sand dog"]

// similar to all palindrome partitions
// there all the substring were supposed to be palindrome
// here all the substrings should be present in the dictionary
// store the dict of vector into an unordered set - all words in dict are said to be unique 

// if a substring is present in dict u can do further parition
// T.C = similar to palindrome partition 
// T.C = O(n * (2^n))
// The number of possible partitions is O(2^n), as each character can be part of a partition in 2 ways (either starts a new partition or extends a previous one).
// forming of sentence = O(n)

// S.C = Space complexity: O(2^n)

// -------------------------------------------------------------------------------------------------------

class Solution {
private:
    void partition(int start, string &s, vector<string> &words, vector<string> &result, unordered_set<string> &dict) {
        // base condition
		// form sentenct from words
        if(start == s.size()) {
            string ans = "";
            for(int i = 0; i < words.size(); i++) {
                ans += words[i];
                if(i != words.size() - 1) ans += " ";
            }
            result.push_back(ans);
        }

        for(int end = start; end < s.size(); end++) {
            
            // if substring is present in dictionary
            // do further partitions
            string w = s.substr(start, end - start + 1);
            if(dict.find(w) != dict.end()) {
                words.push_back(w);
                partition(end + 1, s, words, result, dict);
                words.pop_back();
            }
        }
    }

public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        
        // partition at each point
        // for this partition from start check if this words exists in dictionary
        // put all the data of wordDict in a set
        // if the word exist in dictionary add it to temp words
        // keep partitioning for the rest of the string
        // if u reach the end of the string that means all the words were found
        // in the dict 
        // create a string with space separated and store in result
        
        unordered_set<string> dict(wordDict.begin(), wordDict.end());
        vector<string> words;
        vector<string> result;
        partition(0, s, words, result, dict);

        return result;
    }
};

// --------------------------------------------------------------------------------------------------------

// Memoized solution 
// same time and space complexity
// ✅ Backtracking generates all possible partitions.
// ✅ Memoization avoids redundant calculations.
// ✅ Time Complexity: O(n * 2^n).
// ✅ Space Complexity: O(n * 2^n + m).

// --------------------------------------------------------------------------------------------------------

class Solution {
private:
    unordered_map<int, vector<string>> memo; // Memoization map

    vector<string> partition(int start, string &s, unordered_set<string> &dict) {
        // If result for this start index is already computed, return memoized result
        if (memo.count(start)) return memo[start]; 

        // Base case: If start reaches the end of the string, return an empty string
        if (start == s.size()) return {""}; 

        vector<string> result;

        // Try every possible end index for substring s[start:end]
        for (int end = start; end < s.size(); end++) {
            string word = s.substr(start, end - start + 1); // Extract substring
            
            if (dict.find(word) != dict.end()) { // Check if it exists in wordDict
                vector<string> suffixWays = partition(end + 1, s, dict); // Recursive call
                
                // Construct sentences from current word + all suffix ways
                for (string suffix : suffixWays) {
                    result.push_back(word + (suffix.empty() ? "" : " " + suffix));
                }
            }
        }

        // Memoize result for current start index
        return memo[start] = result;
    }

public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> dict(wordDict.begin(), wordDict.end()); // Convert to unordered_set for O(1) lookup
        return partition(0, s, dict);
    }
};

// --------------------------------------------------------------------------------------------------------
