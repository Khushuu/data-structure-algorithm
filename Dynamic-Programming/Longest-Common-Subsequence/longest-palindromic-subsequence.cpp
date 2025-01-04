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

//------------------------------------------------------------------------------------------------------
// code 
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
