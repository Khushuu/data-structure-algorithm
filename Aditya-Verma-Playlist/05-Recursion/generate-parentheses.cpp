// 22. Generate Parentheses
// given an integer n
// return all valid n pair of parentheses

// n = 2
// result = (()) and ()() [2]

// n = 3
// result = ((())), (())(), ()(()), ()()(), (()())  [5]

// Approach
// lets maintain the count of opening brackets and closing brackets 
// for each position u have two choices
// either add an opening bracket
// or add a closing bracket
// an opening bracket can only be added if count of opening bracket < n
// i.e we can not have more than n opening brackets
// but a closing bracket can only be added if there is already an open bracket
// i.e count of opening bracket > count of closing bracket then only closing bracket can be added 
// when the count of both opening and bracket becomes n then we have found the result

// ------------------------------------------------------------------------------------------------------------

vector<string> result;
generate(0, 0, n, "", result);

void generate(int open, int close, int& n, string curr, vector<string>& result) {
    
	if(open == n && close == n) {
		result.push_back(curr);
		return;
	}
	
	// open and close is the count of opening and closing brackets in the string curr
	// opening bracket can only be added if open < n - as we only need n open brackets and not more
	// closing bracket can only be added if there is already an open bracket i.e open > close 
	if(open < n) generate(open + 1, close, n, curr + "(", result); 
	if(open > close) generate(open, close + 1, n, curr + ")", result);
}

// ------------------------------------------------------------------------------------------------------------