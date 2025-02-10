// 131. Palindrome Partitioning
// Given a string s, partition s such that every substring of the partition is a palindrome.
// Return all possible palindrome partitioning of s.
// Input: s = "aab"
// Output: [["a", "a", "b"], ["aa", "b"]] - all substrings are palindromes

// backtracking
// Since we need to generate all possible palindrome partitions, backtracking is an effective approach.

// Steps:
// Start from the beginning of the string and try to partition it at every possible index.
// s = aabc, all cuts ==> a, (abc) | aa, (bc) | aab, (c) | aabc
// Before making a cut, check if the substring is a palindrome.
// if the subtring is not a palindrome don't make any other calls for the rest of the string 
// aab and aabc are not palindrome -- we prune their recursive trees 

// If it's a palindrome, recursively partition the remaining string.
// recursively call for (abc) and (bc) --> both can be partitioned into 1 char to get final result of
// result = [a, a, b, b] and [aa, b, c]
// If we reach the end of the string, we store the partition.
// Backtrack by removing the last added partition and explore other possibilities. 

// T.C = O(n * (2^n))
// The number of possible partitions is O(2^n), as each character can be part of a partition in 2 ways (either starts a new partition or extends a previous one).
// palindrome check: Each substring check takes O(n)

// S.C =  O(n * 2^n)
// There are O(2^n) partitions, and each takes O(n) space.
// ---------------------------------------------------------------------------------------------------------

void backtrack(int start, string &s, vector<string> &currentPartition, vector<vector<string>> &result) {

	if (start == s.size()) {
		result.push_back(currentPartition);
		return;
	}
	
	for (int end = start; end < s.size(); end++) {
		if (isPalindrome(s, start, end)) {
			currentPartition.push_back(s.substr(start, end - start + 1));
			backtrack(end + 1, s, currentPartition, result);
			currentPartition.pop_back();  // Backtrack
		}
	}
}

bool isPalindrome(string &s, int left, int right) {
	while (left < right) {
		if (s[left++] != s[right--]) {
			return false;
		}
	}
	return true;
}

vector<vector<string>> partition(string s) {
	vector<vector<string>> result;
	vector<string> currentPartition;
	backtrack(0, s, currentPartition, result);
	return result;
}

// ---------------------------------------------------------------------------------------------------------

