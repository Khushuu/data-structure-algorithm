// PROBLEM - 1
// MAXIMUM SUM SUBARRAY OF SIZE K
// given an array of integers and a number k, find the maximum sum of a subarray of size k


int maximumSumSubarray(vector<int>& nums, int k) {
    
    // intialize l and r to 0
    int l = 0;
    int r = 0;
    int sum = 0;
    int result = INT_MIN;

    while(r < nums.size()) {

        // add current element to sum
        // this is done at the start of the loop because we want to compute current window
        // sum before checking if window size is k
        sum += nums[r];

        // check if window size is k
        // if it is then update result and remove leftmost element from sum and move left pointer
        if(r - l + 1 == k) {

            result = max(result, sum); // compute result
            sum -= nums[l]; // remove leftmost element from sum
            l++; // move left pointer
        }

        r++; // move right pointer
    }

    return result;
}

//----------------------------------------------------------------------------------------------------------------------



//----------------------------------------------------------------------------------------------------------------------



