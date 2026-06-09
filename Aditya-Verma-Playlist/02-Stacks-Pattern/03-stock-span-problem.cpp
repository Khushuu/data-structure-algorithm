// PROBLEM - 1
// STOCK SPAN PROBLEM
// NOTE: Variation of next greater element to the left problem

// given an array of stock prices, find the span of each day in the array
// for each day, the span is the number of consecutive days (starting from that day) for which the stock price is less than or equal to the current day's stock price

// e.g stockPrices = [100, 80, 60, 70, 60, 75, 85]
// output = [1, 1, 1, 2, 1, 4, 6]

// for 75 with index 5 the span is 4 why?
// because starting from index 5 for 75 you keep checking values that are less than or equal to 75
// 60, 60, 70, 60 are all less than 75
// so the span is 4

// Stack approach 
// we can find the index of the **next greater element** to the left for each element in the array
// then we can find the span by subtracting the index of the next greater element from the current index 
// that will give us the range in which the stock price is less than or equal to the current stock price

// T.C - O(n) because we are traversing the array once
// S.C - O(n) because in worst case, all the elements are in the stack when elements are in increasing order in nums array

// since we have to find the next greater element to the left of each element
// we will start iterating from the left of the array

vector<int> stockSpan(vector<int>& stockPrices) {

    stack<int> stk; // stack to store the index of the elements 
    vector<int> result(stockPrices.size()); // result vector to store the span for each element in the array

    for(int i = 0; i < stockPrices.size(); i++) {  

        // pop the smaller elements from the stack
        while(!stk.empty() && stockPrices[stk.top()] <= stockPrices[i])
            stk.pop();
        
        // if the stack is empty, then there is no greater element on the left side of the current element
        // so push 1 to the result counting just the current element
        if(stk.empty())
            result[i] = 1;
        else
            result[i] = i - stk.top(); // if we find a greater element, then insert it into the result
        
        stk.push(i); // push the current element into the stack
    }

    return result;
}