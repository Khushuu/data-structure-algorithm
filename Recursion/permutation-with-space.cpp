// given a string
// return all possible permutations of string having space at different positions between chars
// s = abc
// result = a bc, ab c, a b c, abc [4]

// Approach
// for each gap between two chars u have two choices
// either to add a space 
// or to not add a space 
// u will always pick the character
// choice is for adding space or not
// also u can not add space if the end is already reached
// or if there is no char in the string 
// a space can be added only after first char is picked 
// call recursive function with or without space 

// T.C = O(2^(n - 1)) --> if n is the length of the string 2^(n - 1) choices can be made for the space 
// S.C = O(n) - recursive stack

// -------------------------------------------------------------------------------------------------------
string s = "abc";
permutationSpace(0, "", s);
// NOTE: string also have push_back function to push a char to it --> s.push_back('a')

void permutationSpace(int index, string sub, string& s) {

	if(index == s.size()) {
		result.push_back(sub);
		return;
	}

	// space can only be added only if there is atleast 1 char in the sub string
	if(sub.size() > 0) permutationSpace(index + 1, sub + " " + s[index], s); // include space 
	permutationSpace(index + 1, sub + s[index], s); // don't include space
}
// -------------------------------------------------------------------------------------------------------