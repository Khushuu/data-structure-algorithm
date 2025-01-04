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


