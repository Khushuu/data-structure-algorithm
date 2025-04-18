// Longest Common Subsing
// s1 = "abdfej"
// s2 = "akdferej"
// common subsing = {a, dfe, ej}
// longest common subsing = dfe = 3

// since we need to pick continuous characters 
// at any stage if the chars do not match just restart from 0 hence set dp[i][j] = 0
// since by default all values in dp are initialized to 0 the else part is not needed

// NOTE: you need to track the maximum length of common substrings encountered as you iterate through all the positions in the two strings
// as the longest common substring can end before and not necessarily at the end char 

// Bottom up - tabulation
//------------------------------------------------------------------------------------------------------------------
// T.C = O(m*n) and S.C = O(m*n)

int longestCommonSubsing(sing s1, sing s2) {

    int m = s1.size();
    int n = s2.size();
    int result = 0;

    // Create a 2D DP table to store lengths of longest common suffixes
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    // Build the DP table
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            // If characters match, update the DP table
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
				result = max(result, dp[i][j]);
			}
            else 
				dp[i][j] = 0; // redundant
        }
    }

    return result;
}
//-------------------------**************************************************---------------------------------------

// Space optimized solution
// since only previous rows and its column data is needed 
// we can have just two arrays to store current and previous rows data 

//------------------------------------------------------------------------------------------------------------------
// T.C = O(m*n) and S.C = O(n)

int longestCommonSubstring(string str1, string str2) {

    int m = str1.size();
    int n = str2.size();
    int result = 0;

    // Create two rows for DP (previous and current)
    vector<int> prev(n + 1, 0), current(n + 1, 0);

    // Build the DP table
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {

            if (str1[i - 1] == str2[j - 1]) {
                current[j] = prev[j - 1] + 1;
                result = max(result, current[j]); // Track the maximum length
            } else {
                current[j] = 0;
            }
        }

        prev = current; // Move current row to previous
    }

    return result; // Return the maximum length of the common substring found
}
//-------------------------**************************************************---------------------------------------

// Printing Longest Common Substring 
// we just need to identify the index of maximum value in the dp
// we already have the length of the longest common substring 
// once we get the endIndex we can form the substring by picking the result characters in the left direction

// u can pick the endIndex of any string 
// but be sure to then form the lcs from that string only
// -------------------------------------------------------------------------------------------------------
int endIndex = 0;
int maxLength = 0;

for(int i = 1; i <= m; i++) {
	for(int j = 1; j <= n; j++) {
		if(dp[i][j]  > maxLength) {
			maxLength = dp[i][j];
			endIndex = i - 1; // we r picking endIndex from s1, i - 1 is done since we iterate from 1 to m
		}
	}
}
// + 1 is done to include the startIndex correctly 
// abcdef --> if cde is lc substring then endIndex = 4 and maxLength = 3 
// startIndex should be 2, we get that by endIndex - maxLength + 1
// and then pick maxLength no. of chars from string 
return s1.substr(endIndex - maxLength + 1, maxLength);
// -------------------------------------------------------------------------------------------------------

// NOTE: this code can be easily integrated in the dp code of lc substring 
// just add the if condition in print lcs code in place of result = max(result, dp[i][j]) in the lcs code

