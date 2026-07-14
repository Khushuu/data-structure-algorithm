// given a string s 
// return all possible subsets of string s
// if a set has n items then total no. of subset is 2^n

// s = "ab" (n = 2)
// subsets of s (2^2 = 4)= {"", "a", "b", "ab"}

// s = "abc" (n = 3)
// subsets of s(2^3 = 8) = {"", "a", "b", "c", "ab", "bc", "ac", "abc"}

// Approach
// for each char of string we have two choices
// either to include char in the sub string or not include it 
// once this decision is made we move on to the next index in the string
// once index reaches the end of the string s add the sub string to the result 

// T.C = O(2^n) - to generate all possible substrings
// S.C = O(n) - recusion stack space
// --------------------------------------------------------------------------------------------------

vector<string> result;

// subset(0, "", "abc")
void subset(int index, string sub, string& s) {

	if(index == s.size()) {
		result.push_back(sub);
		return;
	}

	subset(index + 1, sub, s); // don't include char to the substring
	subset(index + 1, sub + s[index], s); // include char to substring 
}

// result will have all possible substrings 
// --------------------------------------------------------------------------------------------------

