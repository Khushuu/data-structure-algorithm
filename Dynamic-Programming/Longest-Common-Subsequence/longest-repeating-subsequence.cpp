// given a string
// find the longest repeating subsequence 
// e.g s = "axycabdgbcda"
// repeating subsequence = ac (2 times), abd (3 times)
// longest repeating subsequence = "abd" (length: 3)

// Approach
// we need to combine each char with another same char with different index 
// so find lcs of s with s and do not pick the chars which match at the same index 
// i.e if(s1[i - 1] == s2[j - 1] && i != j) only then include the subsequence 

int longestRepeatingSubsequence(string s) {

	// find lcs of s and s with condition i != j
	int n = s.size();
	vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {

			if(s[i - 1] == s[j - 1] && i != j) // just add i != j to pick same chars from different positions
				dp[i][j] = 1 + dp[i - 1][j - 1];
			else 
				dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
		}
	}

	return dp[n][n];
}