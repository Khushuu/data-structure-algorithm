// given a string
// generate all permutations of the string - all possible ways of arranging 
// permutation = n! / (n1! * n2! * n3! * ...)
// n = total no. of characters in a string
// n1, n2,... = no. of duplicate count of each char

// s = ABC ==> permutation = 3! / (1! * 1! * 1!) = 6 (ABC, ACB, BAC, BCA, CAB, CBA)
// s = AAB ==> permutation = 3! / (2! * 1!) = 6 / 2 = 3 (AAB, ABA, BAA)

// recursive solution 
// pass by value - generate new input output string for each call
// to pick only unique permutation - use a seen set to avoid creating the same recursive tree branch as before 

// input (remaining characters available for permutations).
// output (current permutation being built).
// Remove a character from input and add it to output in each call.
// Stop when input is empty and store the result.
// Keep track of used characters at each level to prevent duplicate recursive calls.

// Call: permuteUnique("AAB", "")
//  ├─ Pick 'A': permuteUnique("AB", "A")
//  │   ├─ Pick 'A': permuteUnique("B", "AA")
//  │   │   ├─ Pick 'B': permuteUnique("", "AAB") -> Store "AAB"
//  │   ├─ Pick 'B': permuteUnique("A", "AB")
//  │       ├─ Pick 'A': permuteUnique("", "ABA") -> Store "ABA"
//  ├─ Pick 'B': permuteUnique("AA", "B")
//      ├─ Pick 'A': permuteUnique("A", "BA")
//      │   ├─ Pick 'A': permuteUnique("", "BAA") -> Store "BAA"

// T.C = O(n * n!) 
// generating unique permutations = n!
// Each permutation requires creating substrings, which takes O(n) per call.
// ---------------------------------------------------------------------------------------------------------------

void permuteUnique(string input, string output, vector<string> &result) {
    if (input.empty()) {  // Base case: if input string is empty, add the result
        result.push_back(output);
        return;
    }

    unordered_set<char> used;  // Track characters used at this level

    for (size_t i = 0; i < input.size(); i++) {

        if (used.find(input[i]) != used.end()) continue;  // Skip duplicate characters
        used.insert(input[i]);  // Mark this character as used

        // Generate a new input string by removing the current character
        string newInput = input.substr(0, i) + input.substr(i + 1);
        
        // Append the current character to the output and recurse
        permuteUnique(newInput, output + input[i], result);
    }
}

vector<string> getUniquePermutations(string str) {
    vector<string> result;
    permuteUnique(str, "", result);
    return result;
}
// ---------------------------------------------------------------------------------------------------------------

// NOTE: 
// starting the loop from index + 1 instead of index in a backtracking permutation algorithm will produce incorrect results. 
// This is because we would be skipping valid permutations by not considering s[index] at its original position.

// backtracking method - using set for unique
// pass by reference
// instead of creating new strings at each point - swap the chars
// we also swap i with index to not miss on the recursive tree where the position of char is not changed
// either u can use sorting + skipping duplicate or 
// using set to avoid duplicate recursive calls 

// Time Complexity : O(n!×n)
// Generating permutations: O(n!)
// Each permutation takes O(n) swaps and checks

// Space Complexity O(n)
// ---------------------------------------------------------------------------------------------------------------

void permuteUnique(string &s, int index, vector<string> &result) {

    if (index == s.size() - 1) {
        result.push_back(s);
        return;
    }

    unordered_set<char> used;  // To track characters already used at this recursion level

    for (int i = index; i < s.size(); i++) {
        if (used.find(s[i]) != used.end()) continue; // Skip if character is already used
        used.insert(s[i]);  // Mark this character as used

        swap(s[index], s[i]);  // Swap characters
        permuteUnique(s, index + 1, result);  // Recur
        swap(s[index], s[i]);  // Backtrack
    }
}

vector<string> getUniquePermutations(string &str) {
    vector<string> result;
    permuteUnique(str, 0, result);
    return result;
}

// ---------------------------------------------------------------------------------------------------------------

// backtracking method - using sorting + skipping duplicates 
// Sort the string first to ensure duplicates are adjacent.
// Use backtracking with a skip condition to avoid duplicate swaps.

// Time Complexity O(n!×n)
// Generating permutations is O(n!).
// Each permutation requires O(n) swaps and checks.
// Overall complexity: O(n!×n).

// ---------------------------------------------------------------------------------------------------------------

void permuteUnique(string &s, int index, vector<string> &result) {
	
    if (index == s.size() - 1) {
        result.push_back(s);
        return;
    }

    for (int i = index; i < s.size(); i++) {
        // Skip duplicate swaps
        if (i != index && s[i] == s[index]) continue;

        swap(s[index], s[i]);  // Swap characters
        permuteUnique(s, index + 1, result);  // Recur
        swap(s[index], s[i]);  // Backtrack
    }
}

vector<string> getUniquePermutations(string &str) {
    vector<string> result;
    sort(str.begin(), str.end());  // Sort to handle duplicates efficiently
    permuteUnique(str, 0, result);
    return result;
}

// ---------------------------------------------------------------------------------------------------------------

