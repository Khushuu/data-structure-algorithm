// 784. Letter Case Permutation
// Given a string s, you can transform every letter individually 
// to be lowercase or uppercase to create another string.
// Return a list of all possible strings we could create. Return the output in any order.

// Input: s = "a1b2"
// Output: ["a1b2","a1B2","A1b2","A1B2"]

// Approach
// for each char that is a character and not a digit we have two choices 
// to add lower case char of it or to add uppercase char of it 
// if it is a digit add the char as it is: isdigit(c)
// function for converting char to lower case = tolower(c) - c is a char
// function for converting char to upper case = toupper(c) - c is a char

// NOTE: tolower(c) and toupper(c) --> these methods return an integer 
// explicitly cast them to char i.e curr + (char)tolower(c) or curr + (char)toupper(c)

// T.C = O(2^n) - where n is the number of chars in the string
// S.C = O(n) - recursion stack space
// -------------------------------------------------------------------------------------------------------
vector<string> result;
casePermutation(0, "", s);

void casePermutation(int index, string curr, string& s) {

	if(index == s.size()) {
		result.push_back(curr);
		return;
	}

	// take digit as it is
	if(isdigit(s[index])) 
		casePermutation(index + 1, curr + s[index], s);
	else {
		casePermutation(index + 1, curr + (char)tolower(s[index]), s);
		casePermutation(index + 1, curr + (char)toupper(s[index]), s);
	}
}
// -------------------------------------------------------------------------------------------------------