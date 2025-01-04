// For recusive solutions think of three things 
// 1. Base Condition 
// 2. Choice Diagram 
// 3. How to make input small by solving smaller subproblem 

// example
// abcde - string 1
// accfke - string 2
// when the two end characters match we can just include the char as the answer of longest common substring 
// and call lcs for the rest of the two strings 
// i.e since s1 and s2 have same end char 'e' our result will definitely have e 
// hence call lcs for the rest of the string i.e return 1 + lcs("abcd", "accfk")
// new in next step the last char does not match, so we need to consider possible combination of 
// picking or not picking the end char of both the strings and take the one that returns maximum answer
// i.e return max(lcs("abcd", "accf"), lcs("abc", "accfk")) 


// Base Condition
// if any of the string has size 0 then the subsequence size will also be 0 
// if(s1.size() == 0 || s2.size() == 0) return 0;

// One choice - if end char matches for s1 and s1 
// - include the last char of both strings (1 + lcs("abcd", "accfk")) and call with rest of the string
// two choices - if end char does not match for s1 and s2
// - including last char of s1 + not including last char of s2
// - not including last char of s1 + including last char of s2
// choosing the maximum of these two 

// Recusive Code 
//------------------------------------------------------------------------------------------------------------------
int lcs(string s1, string s2, int m, int n) {

	// base condition
	if(m == 0 || n == 0) return 0;

	// one choice if char matches - return that
	if(s1[m - 1] == s2[n - 1]) return 1 + lcs(s1, s2, m - 1, n - 1);

	// two choices if end char do not match - choose the one that returns longest subsequence 
	return max(lcs(s1, s2, m - 1, n), lcs(s1, s2, m, n - 1));
}

// caller method
int longestCommonSubsequence(string s1, string s2) {
    return lcs(s1, s2, s1.size(), s2.size());
}
//-------------------------**************************************************---------------------------------------

// Top-Down Memoization

// Why is it needed??

// In case we make more than one choice we might call the function with same arguments multiple times
// And every time we will have to go till the end leaf to deduce the result - which shoots up the time complexity to exponential 
// To not deduce the result of same function again we store the result of every function call in memory
// If same function is called next time check in memory if we have the result if yes return the result from memory
// else deduce the result of the function call and save it in memory before returning it

// how to determine what size of table to choose??

// the memoized table will always be built based on the parameters whose value changes in the recursive code
// in each call of LCS we reduce the size of m and n variables 
// hence memoization will have a dp matrix of size (m + 1) * (n + 1)
// why m + 1 and n + 1 ==> since the largest result it can store is the original strings of size m and n 
// and as table is 0-index to store result of m and n we need table of size (m + 1) * (n + 1)

// how to deduce if the function call has been evaluated previously??

// initialize the dp matrix with value of -1 --> denoting initial stage --> as lowest value of lcs can be 0 hence -1
// after a function evaluates the value it will update the corresponding value in the dp matrix to some other integer
// at the start of function call check if value is not -1 then return result from matrix table 
// else deduce it, save it in table and then return it


// what would be the result??
// the problem wants lcs for original strings of size m and n hence result will be dp[m][n]

//------------------------------------------------------------------------------------------------------------------
int lcs(string s1, string s2, int m, int n, vector<vector<int>>& dp) {

	// base condition
	if(m == 0 || n == 0) return 0;

	// check if result stored in memory after base condition
	if(dp[m][n] != -1) return dp[m][n];

	// one choice if char matches - return that
	if(s1[m - 1] == s2[n - 1]) return dp[m][n] = 1 + lcs(s1, s2, m - 1, n - 1);

	// two choices if end char do not match - choose the one that returns longest subsequence 
	return dp[m][n] = max(lcs(s1, s2, m - 1, n), lcs(s1, s2, m, n - 1));
}

// caller method
int longestCommonSubsequence(string s1, string s2) {

	int m = s1.size();
	int n = s2.size();
	// memoization matrix
	vector<vector<int>> dp(m + 1, vector<int>(n + 1, -1));

    return lcs(s1, s2, s1.size(), s2.size(), dp);
}
//-------------------------**************************************************---------------------------------------

// Bottom-up Tabulation

// Why do we need it??
// Memoization does recusion with the help of a table 
// Too many function calls can lead to stack overflow so its better to build the table bottom up sometimes

// How to initialize the table
// Do it using the base condition in the recursive method 

//------------------------------------------------------------------------------------------------------------------
int longestCommonSubsequence(string s1, string s2) {

	int m = s1.size();
	int n = s2.size();
	vector<vector<int>>  dp(m + 1, vector<int>(n + 1, 0));

	// we r filling the table after initialization
	for(int i = 1; i <= m; i++) {
		for(int j = 1; j <= n; j++) {

			// the reason y we do i - 1 is although the index should be from 0 to m-1 
			// since we loop over the table from 1 to m in order to correctly pick the CURRENT CHAR
			// we should do i - 1 --> so i goes from 1 to m and chars of s goes grom 0 to m - 1
			// if current char match we do 1 + and look at previous answer of i-1 and j-1
			if(s1[i - 1] == s2[j - 1])
				dp[i][j] = 1 + dp[i - 1][j - 1];
			else 
				dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
		}
	}

	return dp[m][n];
}
//-------------------------**************************************************---------------------------------------
