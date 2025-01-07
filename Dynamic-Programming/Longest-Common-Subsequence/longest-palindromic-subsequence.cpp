// given a string s find the longest palindromic subsequence in it
// e.g s = "abcddnmba"
// palindromic subsequences = {"abba", "abdba", "abnba", "abddba",...}
// longest palindromic subsequence = "abddba" = 5 

// how to solve it on the concept of lcs 
// lcs has always two strings s1 and s2 as parameters
// can we derive 2nd string on the basis of first here?? Maybe
// what is a palindrome == a string that reads same forward and backward 
// what if I set s2 as reverse of s1 and then find lcs for these 
// that will work

// longest palindromic subsequence = lps
// longest common subsequence = lcs 

// lps = lcs(s1, reverse(s1)) 

// Longest Palindromic Subsequence
//------------------------------------------------------------------------------------------------------
int longestPalindromicSubsequence(string s) {

	// find lcs of s and reverse of s
	string s1 = s;

	// s2 = reverse(s1);
	reverse(s1.begin(), s1.end());
	string s2 = s1;
	
	// lps = lcs(s1, s2) = lcs(s1, reverse(s1))
	int n = s.size();
	vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {

			if(s1[i - 1] == s2[j - 1]) 
				dp[i][j] = 1 + dp[i - 1][j - 1];
			else 
				dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
		}
	}

	// lps
	return dp[n][n];
}
//------------------------------------------------------------------------------------------------------

// Minimum number of deletions in a string to make it a palindrome 
// Minimum number of insertions in a string to make it a palindrome

// find the longest palindromic subsequence = lps 
// minimum number of deletions will be subtracting lps from the length of string 
// deletion =  to convert s to lps = s.size() - lps
// insertion = lps + some chars = palindrom 
// e.g s = "abca", lps = "aba", insertion = s.size() - lps = 4 - 3 = 1 (add c to make string palindrom) = acbca

// e.g 
// s = "abcddnmba" = 9
// lps = "abddba" = 6
// deletion = s.size() - lps = 9 - 6 = 3 = remove "cnm" from s to make it palindrome/
// insertion = s.size() - lps = 9 - 6 = 3 = add these chars at the right place to make string a palindrome
// since we want minimum deletion we should convert s to longest palindrome subsequence 

// CODE
// minimum number of deletion to make a given string a palindrome
// deletion = s.size() - lps
// T.C = O(n*n)
// S.C = O(n*n)
//------------------------------------------------------------------------------------------------------
int longestPalindromicSubsequence(string s) {

	// find lcs of s and reverse of s
	string s1 = s;

	// s2 = reverse(s1);
	reverse(s1.begin(), s1.end());
	string s2 = s1;
	
	// lps = lcs(s1, s2) = lcs(s1, reverse(s1))
	int n = s.size();
	vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {

			if(s1[i - 1] == s2[j - 1]) 
				dp[i][j] = 1 + dp[i - 1][j - 1];
			else 
				dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
		}
	}

	return n - dp[n][n]; // deletion = insertion = s.size() - lps 
}
//------------------------------------------------------------------------------------------------------
