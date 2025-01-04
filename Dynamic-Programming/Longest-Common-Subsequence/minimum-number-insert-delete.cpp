// minimum number of insertion and deletion that should be done
// to convert string s1 to string s2 
// s1 = "lover"
// s2 = "poet"
// lcs = "oe"
// delete = s1.size() - lcs = 5 - 2 = 3 (chars that should be removed from s1 to form lcs) = ("lvr")
// insert = s2.size() - lcs = 4 - 2 = 2 (chars that should be added to lcs to form s2) = ("pt")
// total operations = delete + insert = 3 + 2 
// total = m - lcs + n - lcs = (m + n - 2 * lcs)

// two step process for s1 ==> s2
// s1 ==> lcs (deletion) = m - lcs ==> lover ==> oe (remove lvr)
// lcs ==> s2 (insertion) = n - lcs ==> oe ==> poet (insert pt)

// to convert s1 to s2 
// firstly delete some chars from s1
// and then add some chars from s2 
// how to identify what all chars to delete and insert
// the common chars can be retained - longest common subsequence 

//---------------------------------------------------------------------------------------------------------
// code return {delete, insert} as pair
// bottom-up tabulation
vector<int> lcs(string s1, string s2) {

	int m = s1.size();
	int n = s2.size();
	vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

	for(int i = 1; i <= m; i++) {
		for(int j = 1; j <= n; j++) {

			if(s1[i - 1] == s2[j - 1]) 
				dp[i][j] = 1 + dp[i - 1][j - 1];
			else 
				dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
		}
	}

	int lcs = dp[m][n];
	int deletions = m - lcs;
	int insertions = n - lcs;

	return {deletions, insertions};
}
//---------------------------------------------------------------------------------------------------------