// PRINT UNIQUE SUBSETS

// s = abb
// subsets = "", "a", "b", "b", "ab", "bb", "ab", "abb"
// unique subsets = "", "a", "b", "ab","bb", "abb" - 6

// SUBSTRING - continuous characters 
// s = "abc" --> substrings = a, b, c, ab, bc, abc 
// [ac - won't be a substring as it is not conitnuous]

// SUBSEQUENCE - pick some or not characters from a string --> order should be maitained
// s = "abc" --> subsequence = a, b, c, ab, ac, bc, abc
// [cb - won't be subsequence as the order of chars in incorrect]

// SUBSET - power set - order doesn't matter - print any one of the possible combination of chars 
// - picking all possibe subsets --> if n is length --> subsets = 2^n


// Approach

// Using Set
// one way is to store all the subsets in a set and then return result 
// set will only store one copy of a subset and not duplicate

// Sorting + skipping approach
// -- only in cases of exclude will u get duplicates --> in case when u r including duplicate char
// -- it will still lead to diff subsets as the count of char will increase 
// -- so u want to pick only one choice of excluding the chars

// Sort the string to ensure duplicate characters appear consecutively.
// Use recursion to generate subsets.
// Skip duplicate elements to avoid generating duplicate subsets.

// Time Complexity: With Sorting: O(2ⁿ + n log n) = O(2ⁿ)

// -------------------------------------------------------------------------------------------------------
sort(s.begin(), s.end());
vector<string> result;
generateUniqueSubsets(s, "", 0, result);

void generateUniqueSubsets(string &s, string sub, int index, vector<string> &result) {
    if (index == s.length()) {
        result.push_back(sub);
        return;
    }

    // Include the current character
    generateUniqueSubsets(s, sub + s[index], index + 1, result);

    // Skip all occurrences of the current character to avoid duplicates
    while (index + 1 < s.length() && s[index] == s[index + 1]) {
        index++;
    }

    // Exclude the current character and move to the next distinct character
    generateUniqueSubsets(s, sub, index + 1, result);
}
// -------------------------------------------------------------------------------------------------------