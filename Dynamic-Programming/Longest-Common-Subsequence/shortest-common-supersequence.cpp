// given two strings s1 and s2
// create a supersequence which has both s1 and s2 as its subsequence 
// find such shortest common supersequence 

// s1 = "abbcde" 
// s2 = "axybccke"
// shortest supersequence = "axybbccdke" --> write the common chars only once and in order
// this means to get the shortes supersequence if we have the longest subsequence we can deduce it

// we write lcs only once that means
// shortest common supersequence = s1.size() + s2.size() - lcs

// so to get the shortest common supersequence find the longest common subsequence
// and then return s1.size() + s2.size() - lcs	

// e.g
// s1 = "abbcde"  = 6
// s2 = "axybccke" = 8
// lcs = "abce" = 4
// result = "axybbccdke" = 10 = (6 + 8 - 4)

// STEPS

// write the code of lcs 
// return s1.size() + s2.size() - lcs

// CODE: Shortest Common Subsequence
// -------------------------------------------------------------------------------------------------------
// Time complexity: O(m * n)
// Space complexity: O(m * n)

int longestCommonSubsequence(string s1, string s2) {

    int m = s1.size();
    int n = s2.size();
    
    // DP table to store lengths of LCS
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    // Build the DP table for LCS
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {

            if (s1[i - 1] == s2[j - 1]) 
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else 
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }

    // The length of the Longest Common Subsequence
    return dp[m][n];
}

int shortestCommonSupersequenceLength(string s1, string s2) {
    // Length of SCS = (Length of s1 + Length of s2) - Length of LCS
    int lcs = longestCommonSubsequence(s1, s2);
    return s1.size() + s2.size() - lcs;
}

// -------------------------------------------------------------------------------------------------------
// SCS length = m + n - lcs
// Print SCS
// We will print the LCS - common sequence characters in both string only once and the others 1-1 time
// Similary as we were printing LCS every time s1[i - 1] == s2[j - 1] we would do result = s1[i - 1] + result
// And we would print only in case of char match
// Here we will do the LCS print and also if the chars dont match when we move in the direction of max value
// i.e we move towards either one step up or one step left 
// if we move to the left we will never see the current char again so print it i.e 
// if s1 is the rows and s2 is the columns then as we move left print the column i.e s2[j - 1] and then j--
// and if we move top as we leave the current row print the row and move top i.e s1[i - 1] and the i--

// CODE: Print Shortest Common Subsequence
// -------------------------------------------------------------------------------------------------------

int i = m;
int j = n;
string scs = "";

// this loop runs until both the strings are non-empty
// if any of the string becomes empty for scs we still need to include those chars
while(i > 0 && j > 0) { 

	// check the correct index 
	if(s1[i - 1] == s2[j - 1]) {
		scs = s1[i - 1] + scs;
		i--;
		j--;
	} 
	else {
		if(dp[i][j - 1] >= dp[i - 1][j]) {
			scs = scs + s2[j - 1]; // include the columnn char that we r leaving
			j--; // move left
		}
		else {
			scs = scs + s1[i - 1] // include the row char that we r leaving 
			i--; // move up
		}
	}
}

// if s1 is non-empty then include all its chars
while(i > 0) {
	scs = scs + s1[i - 1];
	i--;
}

// if s2 is non-empty then include all its chars
while(j > 0) {
	scs = scs + s2[j - 1];
	j--;
}

return scs;

// -------------------------------------------------------------------------------------------------------

