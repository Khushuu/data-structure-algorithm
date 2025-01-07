// given two strings s1 and s2
// return if s1 is a subsequence of s2
// e.g. s1 = abc and s2 = dfgsaybnvc --> true as s1 is subsequence of s2
// e.g. s1 = pk and s2 = jhkdjprrr --> return false 

// Approach
// if the longest common subsequence of s1 and s2 is the string s1 itself then s1 is a subsequence of s2
// return lcs(s1, s2) == s1.size()
// I don't need actual lcs string to compare with s1 
// just comparing the length of lcs with s1 size is enough --> Y??
// suppose s1 = "abcd" and s2 = "anbgfcerf" --> lcs = abc (3) and 3 != 4 (abcd)
// there won't be any case where a string of same size as s1 matches with lcs of same size
// lcs will always be a subset of s1


// CODE 
// return if s1 is a subsequence of s2
// T.C = O(n*n)
// S.C = O(n*n)
//---------------------------------------------------------------------------------------------------------------
bool isSubsequence(string s1, string s2) {

	// find lcs
	int m = s1.size();
	int n = s2.size();
	vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

	for(int i = 1; i <= m; i++) {
		for(int j = 1; j <= n; j++) {

			if(s1[i - 1] == s2[j - 1])
				dp[m][n] = 1 + dp[i - 1][j - 1];
			else 
				dp[m][n] = max(dp[i - 1][j], dp[i][j - 1]);
		}
	}
	
	return dp[m][n] == s1.size() // just check if lcs(s1, s2) == s1.size()
}
//---------------------------------------------------------------------------------------------------------------
