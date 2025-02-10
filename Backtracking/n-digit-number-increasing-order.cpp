// given a digit n
// form all numbers with n digits such that the digits are in increasing sequence
// e.g n = 2 so result can have 12, 13, 14, ....23, 24, 25, 25..., 34, 35, 36, ....
// 12 13 14 15 16 17 18 19 23 24 25 26 27 28 29 34 35 36 37 38 39 45 46 47 48 49 56 57 58 59 67 68 69 78 79 89

// approach
// always call the backtrack method for the next bigger digit then the current one that is already added
// use a string num and pass it by reference 
// always modify and revert changes in this string
// when the size of num == n then convert the string to number and add to the result 

// generateNumbers(n, i + 1, num, result);
// we always do i + 1 and not start + 1 because it is possible that start = 3 and i = 6 currently 
// then recursize call with start + 1 will be 4 and we would have already added i in num 
// i.e num.push_back(i + '0') = "6" --> start + 1 will make the number "64" --> which is incorrect  

// or u can just always run the loop from 1 to 9 and just ensure that i > num.back()

// T.C = O(n⋅C(9,n)) as we choose n digits from 9 digits and convert string to number for each call
// stoi(num) to convert and store → O(n)
// Since we generate C(9, n) numbers, the total work done is: O(n)×C(9,n)

// time complexity would have been 9^n if all combinations were asked and not just increasing 
// --------------------------------------------------------------------------------------------------------------

void generateNumbers(int n, int start, string &num, vector<int> &result) {

    if (num.size() == n) {  // Base case: Found an n-digit number
        result.push_back(stoi(num));  // Convert string to integer and store
        return;
    }

    // Loop from the current digit (start) to 9
    for (int i = start; i <= 9; i++) {
        num.push_back(i + '0');  // Append current digit - converting integer i to char using i + '0
        generateNumbers(n, i + 1, num, result);  // Recursive call
        num.pop_back();  // Backtrack: Remove last added digit
    }
}

vector<int> generateIncreasingNumbers(int n) {
    vector<int> result;
    string num;  // Mutable string passed by reference
    generateNumbers(n, 1, num, result);  // Start from digit 1
    return result;
}

// --------------------------------------------------------------------------------------------------------------

// MORE INTUITIVE SOLUTION 

// if (num.empty() || i > num.back() - '0')
// if it is the first digit u can push any digit else always push a digit greater than last digit in number
// --------------------------------------------------------------------------------------------------------------

void generateNumbers(int n, string &num, vector<int> &result) {

    if (num.size() == n) {  // Base case: Found an n-digit number
        result.push_back(stoi(num));  // Convert string to integer and store
        return;
    }

    for (int i = 1; i <= 9; i++) {  // Loop from 1 to 9
        if (num.empty() || i > num.back() - '0') {  // Ensure increasing order 
            num.push_back(i + '0');  // Append digit
            generateNumbers(n, num, result);  // Recursive call
            num.pop_back();  // Backtrack
        }
    }
}

vector<int> generateIncreasingNumbers(int n) {
    vector<int> result;
    string num;
    generateNumbers(n, num, result);
    return result;
}

// --------------------------------------------------------------------------------------------------------------