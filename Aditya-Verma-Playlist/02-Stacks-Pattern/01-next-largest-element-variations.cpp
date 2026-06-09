// NOTE:
// from whichever side we are finding the next largest element, we will start iterating from that side of the array

// PROBLEM - 1
// Next largest element or Next greater element to the right

// given an array of integers, find the next largest element for each element in the array. 
// The next largest element for an element x is the first larger element on the right side of x in the array. 
// If there is no larger element on the right side, then the next largest element for x is -1.

// e.g nums = [4, 5, 2, 10], output = [5, 10, 10, -1]
// e.g nums = [3, 2, 1], output = [-1, -1, -1]
// e.g nums = [1, 3, 2, 4], output = [3, 4, 4, -1]

// T.C - O(n) because we are traversing the array once
// S.C - O(n) because we are using a stack to store the elements

//--------------------------------------------------------------------------------------------------------------
// brute force approach - O(n^2) - for each element, we can traverse the array to find the next largest element on the right side

// for(int i = 0; i < nums.size() - 1; i++) 
// for(int j = i + 1; j < nums.size(); j++) find the next largest element for nums[i]
//---------------------------------------------------------------------------------------------------------------

// OPTIMIZED APPROACH - using a stack
// since we need to find the next largest element to the right of each element 
// we will start iterating from the end of the array

// for each element we will check the top of the stack  if it is empty we will push -1 to the result 
// it means there is no larger element on the right side of the current element

// if the top of the stack is less than the current element we will keep popping from the stack until we find a larger element or the stack becomes empty
// if we find a larger element we will insert it into the result 
// and push the current element into the stack

// Intuition - we are maintaining a stack of elements in decreasing order from top to bottom
// Question: why do we pop the smaller element 
// since we are looking for the next larger element 
// as we move from right to left, if we encounter a smaller element than the current element, then it cannot be the next larger element for any of the elements to the left of the current element, so we can safely pop it from the stack

// T.C - O(n) because we are traversing the array once
// S.C - O(n) because in worst case, all the elements are in the stack when elements are in increasing order in nums array

vector<int> nextLargerElement(vector<int>& nums) { 

    stack<int> stk; // stack to store the elements in decreasing order
    vector<int> result(nums.size()); // result vector to store the next larger element for each element in the array

    for(int i = nums.size() - 1; i >= 0; i--) {

        // pop the smaller elements from the stack
        while(!stk.empty() && stk.top() <= nums[i])
            stk.pop();
        
        // if the stack is empty, then there is no larger element on the right side of the current element
        // so push -1 to the result
        if(stk.empty())
            result[i] = -1;
        else
            result[i] = stk.top(); // if we find a larger element, then insert it into the result
        
        stk.push(nums[i]); // push the current element into the stack
    }

    return result;
}

//---------------------------------------------------------------------------------------------------------------

// PROBLEM - 2
// Next largest element or Next greater element to the left

// given an array of integers, find the next largest element for each element in the array. 
// The next largest element for an element x is the first larger element on the left side of x in the array. 
// If there is no larger element on the left side, then the next largest element for x is -1.

// e.g nums = [4, 5, 2, 10], output = [-1, -1, 5, -1]   

// T.C - O(n) because we are traversing the array once
// S.C - O(n) because in worst case, all the elements are in the stack when elements 

// Since we have to find the next larger element to the left of each element
// we will start iterating from the left of the array

vector<int> nextLargestElementToLeft(vector<int>& nums) {

    stack<int> stk; // stack to store the elements in decreasing order
    vector<int> result(nums.size()); // result vector to store the next larger element for each element in the array

    for(int i = 0; i < nums.size(); i++) {

        // pop the smaller elements from the stack
        while(!stk.empty() && stk.top() <= nums[i])
            stk.pop();
        
        // if the stack is empty, then there is no larger element on the left side of the current element
        // so push -1 to the result
        if(stk.empty())
            result[i] = -1;
        else
            result[i] = stk.top(); // if we find a larger element, then insert it into the result
        
        stk.push(nums[i]); // push the current element into the stack
    }

    return result;
}

//---------------------------------------------------------------------------------------------------------------
// NOTE:
// for smaller element we only need to change the condition in the while loop from stack
// instead of popping the smaller elements from the stack, we will pop the larger elements from the stack
// so we will change the condition in the while loop from stk.top() <= nums[i] for finding larger element
// to stk.top() >= nums[i] to find the next smaller element to the left 


// PROBLEM - 3
// Nearest smallest element or Next smaller element to the left of each element in the array

// given an array of integers, find the next smaller element for each element in the array. 
// The next smaller element for an element x is the first smaller element on the left side of x in the array. 
// If there is no smaller element on the left side, then the next smaller element for x is -1.

// e.g nums = [4, 5, 2, 10], output = [-1, 4, -1, 2]    

// T.C - O(n) because we are traversing the array once
// S.C - O(n) because in worst case, all the elements are in the stack when elements

// Since we have to find the next smaller element to the left of each element
// we will start iterating from the left of the array

vector<int> nextSmallerElementToLeft(vector<int>& nums) {

    stack<int> stk; // stack to store the elements in increasing order
    vector<int> result(nums.size()); // result vector to store the next smaller element for each element in the array

    for(int i = 0; i < nums.size(); i++) {

        // pop the larger elements from the stack
        while(!stk.empty() && stk.top() >= nums[i])
            stk.pop();
        
        // if the stack is empty, then there is no smaller element on the left side of the current element
        // so push -1 to the result
        if(stk.empty())
            result[i] = -1;
        else
            result[i] = stk.top(); // if we find a smaller element, then insert it into the result
        
        stk.push(nums[i]); // push the current element into the stack
    }

    return result;
}

//---------------------------------------------------------------------------------------------------------------
// PROBLEM - 4
// Nearest smaller element to the right of each element in the array

// given an array of integers, find the nearest smaller element for each element in the array.
// The nearest smaller element for an element x is the first smaller element on the right side of x in the array. 
// If there is no smaller element on the right side, then the nearest smaller element for x is -1.

// e.g nums = [4, 5, 2, 10], output = [2, 2, -1, -1]

// T.C - O(n) because we are traversing the array once
// S.C - O(n) because in worst case, all the elements are in the stack when elements

// Since we have to find the nearest smaller element to the right of each element
// we will start iterating from the right of the array

vector<int> nearestSmallerElementToRight(vector<int>& nums) {

    stack<int> stk; // stack to store the elements in increasing order
    vector<int> result(nums.size()); // result vector to store the nearest smaller element for each element in the array

    for(int i = nums.size() - 1; i >= 0; i--) {

        // pop the larger elements from the stack
        while(!stk.empty() && stk.top() >= nums[i])
            stk.pop();
        
        // if the stack is empty, then there is no smaller element on the right side of the current element
        // so push -1 to the result
        if(stk.empty())
            result[i] = -1;
        else
            result[i] = stk.top(); // if we find a smaller element, then insert it into the result
        
        stk.push(nums[i]); // push the current element into the stack
    }

    return result;
}