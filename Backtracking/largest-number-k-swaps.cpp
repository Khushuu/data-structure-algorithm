// give a string s of number
// and a value k
// form the greatest number by doing at most k swaps 

// greedy approach thinking
// suppose s = "2377" and k = 2
// to form greatest number we pick the max number from right of current digit
// and place it at that position 
// do this repeatedly if any number greater than current is found 
// s = "2377" 
// swap(0, 2) --> as 7 is the greatest to the right of 2 ==> s = "7327"
// swap(1, 3) --> as 7 is the greatest to the right of 3 ==> s = "7723"
// so the result = "7723" // incorrect
// this is because the greatest number after at most k swaps would have been = "7732"

// greedy approach won't work if there are duplicate digits in the string
// u need to do swap will all the maximum values to the right of current digit and then deduce the maximum
// so explore both recursive trees --> swapping 2 with both 7s to the right of it 

// after each swap u reduce the value of k 
// base condition --> if k == 0 or index == s.size() - 1 then return 

// if the current digit has no maximum to the right of it then move to the next index 
// the value of k won't be decremented in this case as didn't do any swap for this position
// suppose s = "845613" for 8 --> there is no greater digit to its right 
// so just call recursive method with index + 1 and k 


// T.C = O(n^2 * k)
// ------------------------------------------------------------------------------------------------------

void findLargest(string &num, int k, string &maxNum, int index) {
    if (k == 0 || index == num.size() - 1) return;  // Base case: No swaps left OR reached last digit

    char maxDigit = num[index];

    // Find the maximum digit from index+1 to end
    for (int i = index + 1; i < num.size(); i++) {
        if (num[i] > maxDigit) {
            maxDigit = num[i];
        }
    }

    // If no larger digit is found, move to the next position
    if (maxDigit == num[index]) {
        findLargest(num, k, maxNum, index + 1);
        return;
    }

    // Try swapping the current index with any occurrence of maxDigit (from left to right)
    for (int i = index + 1; i < num.size(); i++) {

        if (num[i] == maxDigit) {  // Swap only with maxDigit occurrences
            swap(num[index], num[i]);  // Swap

            // Update maxNum if we found a larger number
            if (num > maxNum) {
                maxNum = num;
            }

            // Recur with reduced k
            findLargest(num, k - 1, maxNum, index + 1);

            swap(num[index], num[i]);  // Backtrack
        }
    }
}

string getLargestNumber(string num, int k) {
    string maxNum = num;
    findLargest(num, k, maxNum, 0);
    return maxNum;
}

// ------------------------------------------------------------------------------------------------------
