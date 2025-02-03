// Recursive Function to find the minimum number of 
// cuts needed for palindrome partitioning
// eg. s = "nitik" 
// min cuts = 2 --> n, iti, k
// all the strings are palindrom
// base case - if the string is empty or already a palindrom - no futher division is needed
// otherwise break the string at each char and check both string i to k and k + 1 to j to find no. of partitions
// select the min result of all paritions


// Function to Check if a substring is a palindrome
bool isPalindrome(string& s, int i, int j) {
    while (i < j) {
        if (s[i] != s[j])
            return false;
        i++;
        j--;
    }
    return true;
}

// Recursive solution

// O(n * 2^n) Time and O(n) Space
minCuts(s, 0, s.size() - 1);
int minCuts(string& s, int i, int j) {
  
    // Base case: If the substring is empty or 
      // a palindrome, no cuts needed
    if (i >= j || isPalindrome(s, i, j))
        return 0;

    int res = INT_MAX, cuts;

    // Iterate through all possible partitions and 
      // find the minimum cuts needed
	  // 1 is added for the current cut
    for (int k = i; k < j; k++) {
        cuts = 1 + minCuts(s, i, k)
                    + minCuts(s, k + 1, j);
        res = min(res, cuts);
    }

    return res;
}


// memoized solution
// store the result of each cut
// check memo before base condition - this is done so that we don't have to check palindrom string 
// even when the result is already stored 

// (Memoization) – O(n^3) Time and O(n^2) Space

int minCuts(string& s, int i, int j, 
                        vector<vector<int>>& memo) {
      
      // check in memo for 
      if (memo[i][j] != -1) 
          return memo[i][j];
  
    // Base case: If the substring is empty or 
      // a palindrome, no cuts needed
    if (i >= j || isPalindrome(s, i, j))
        return memo[i][j] = 0;

    int res = INT_MAX, cuts;

    // Iterate through all possible partitions and 
      // find the minimum cuts needed
    for (int k = i; k < j; k++) {
        cuts = 1 + minCuts(s, i, k, memo)
                + minCuts(s, k + 1, j, memo);
        res = min(res, cuts);
    }

    return memo[i][j] = res;
}

int palPartition(string &s) {
      int n = s.size();
  
      // declare a memo array to store the result
      // and initialise it with -1
      vector<vector<int>> memo(n, vector<int> (n, -1));
  
      return minCuts(s, 0, n - 1, memo);
}

