// Given a string containing digits from '2' to '9'
// return all possible letter combinations that the number could represent. 

// 2 -> "abc"
// 3 -> "def"
// 4 -> "ghi"
// 5 -> "jkl"
// 6 -> "mno"
// 7 -> "pqrs"
// 8 -> "tuv"
// 9 -> "wxyz"

// Input: digits = "23"
// Output: ["ad","ae","af","bd","be","bf","cd","ce","cf"]

// Think of it as forming words:
// The first digit determines the first letter.
// The second digit determines the second letter.
// Continue until all digits are processed.

// Use backtracking to explore all possible combinations.
// Start at index 0, pick a letter from the first digit.
// Move to index 1, pick a letter from the second digit.
// If all digits are processed, store the result.
// Backtrack to try another letter for the previous digit.

// we don't need to specifically run a for loop to traverse all digits 
// we just use index variable
// and for each digit we choose the available char choices - append it to the path
// when the index reaches the size of the digit string - add it to the result

// T.C = O(4^n)
// Since each digit can have up to 4 choices, we can form at most 4^n words.

// S.C = O(4^n * n)
// Each string is stored in result, taking O(4^n × n) space.
// -----------------------------------------------------------------------------------------------------------
class Solution {
private:
    unordered_map<char, string> phoneMap = {
        {'2', "abc"}, {'3', "def"}, {'4', "ghi"},
        {'5', "jkl"}, {'6', "mno"}, {'7', "pqrs"},
        {'8', "tuv"}, {'9', "wxyz"}
    };

    void backtrack(int index, string &digits, string &path, vector<string>& result) {

        if(index == digits.size()) {
            result.push_back(path);
            return;
        }

        // loop over possible chars for the digits present at index --> index 
        for(char c: phoneMap[digits[index]]) {
            path.push_back(c);
            backtrack(index + 1, digits, path, result);
            path.pop_back();
        }
    }

public:
    vector<string> letterCombinations(string digits) {
        
        if(digits.empty()) return {};

        vector<string> result;
        string path = "";
        backtrack(0, digits, path, result);

        return result;
    }
};
// -----------------------------------------------------------------------------------------------------------