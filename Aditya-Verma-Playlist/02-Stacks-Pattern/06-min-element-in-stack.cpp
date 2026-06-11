// PROBLEM - 1
// MINIMUM ELEMENT IN STACK

// design a data structure that supports the following operations:
// push(x) - Add an element x to the stack.
// pop() - Remove the top element from the stack.   
// getMin() - Return the minimum element in the stack.  

// T.C - O(1) for all the operations
// S.C - O(n) - using minstack as extra space

// approach - 1 - using extra space - stack 
// maintain another stack to store the minimum elements

// intuition
// if the stack is empty then push the current element to the minimum stack 
// if the current element is less than the top of the minimum stack then push the current element to the minimum stack
// else push the top of the minimum stack to the stack

// Two ways you can either keep pushing the same element to the top of minstack multiple times 
// or push a pair on the top of min stack with minimum element value and minimum element count 

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Using Two Stacks (Most Common Interview Solution)

// Maintain:

// Main stack → stores all elements.
// Min stack → stores minimum element till that point.
// Idea

// When pushing:

// If min stack is empty OR current element ≤ min stack top
// → push into min stack as well.

// When popping:

// If popped element equals min stack top
// → pop from min stack too.

////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// Method - 1
// Pushing minimum element to the top of stack multiple times 

stack<int> minstack;
stack<int> stack;

void push(int num) {
    
    stack.push(num);
    
    if(minstack.empty() || minstack.top() >= num)
        minstack.push(num);
}

void pop() {
    
    if(stack.empty())
        return;

    int top = stack.top();
    stack.pop();
    
    if(top == minstack.top())
        minstack.pop();
}

int getMin() {
    
    return minStack.empty() ? -1 : minstack.top();
}

//-------------------------------------------------------------------------------------------------------------

// Method - 2
// Pushing a pair on the top of min stack with minimum element value and minimum element count 

void push(int num) {
    
    stack.push(num);

    if(minstack.empty() || minstack.top().first > num) {
        minstack.push({num, 1});
    }
    else if(minstack.top().first == num) {
        minstack.top().second++;
    }
}

void pop() {
    
    if(stack.empty())
    return;

    int top = stack.top();
    stack.pop();
    
    if(top == minstack.top().first) {
        minstack.top().second--;
        if(minstack.top().second == 0)
            minstack.pop();
    }
}

int getMin() {
    
    return minStack.empty() ? -1 : minstack.top();
}
//-------------------------------------------------------------------------------------------------------------

// BETTER APPROACH
// each time when popping from stack check if it is the min element or not 
// if yes then pop the top element from minstack
// otherwise only pop from the stack 
// only push to the min stack if current element is less than top of the stack 

// ISSUE WITH THIS APPRAOCH
// if all the elements in the stack are the same 
// we will keep pushing the same element to the minstack

void push(int num) {
    
    stack.push(num);

    // only push when the element is lower than top of minstack 
    if(minstack.empty() || minstack.top() >= num)
        minstack.push(num);
}

void pop() {
    
    if(stack.empty())
        return;

    int top = stack.top();
    stack.pop();
    
    if(top == minstack.top()) {
        minstack.pop();
    }
}

int getMin() {
    
    return minStack.empty() ? -1 : minstack.top();
}

// METHOD - 4
// IMPROVEMENT TO THE ABOVE APPROACH

// push the element to the minstack only when it is smaller than top of minstack along with its count 
// so push a pair to the minstack 

// maintains strictly increasing stack from top to bottom
// equal elements will just have different counts
void push(int num) {
    
    stack.push(num);
    
    if(minstack.empty() || minstack.top().first > num) {
        minstack.push({num, 1});
    }
    else if(minstack.top().first == num) {
        minstack.top().second++;
    }
}

void pop() {
    
    if(stack.empty())
        return;

    int top = stack.top();
    stack.pop();
    
    if(top == minstack.top().first) {
        minstack.top().second--;
        if(minstack.top().second == 0)
            minstack.pop();
    }
}

int getMin() {
    
    return minStack.empty() ? -1 : minstack.top();
}

//------------------------------------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// USING SINGLE STACK
// Store Pair {Element, Current Minimum}

// Instead of two stacks, store:

// {value, minimum_so_far}

// at each position.

// Example
// Push 5 -> {5,5}
// Push 2 -> {2,2}
// Push 8 -> {8,2}
// Push 1 -> {1,1}

// Minimum is always stored with the top element.

// Space Complexity: O(n)

void push(int x) {
    if (st.empty()) {
        st.push({x, x});
    } else {
        st.push({x, min(x, st.top().second)});
    }
}

void pop() {
    if (!st.empty())
        st.pop();
}

int top() {
    return st.top().first;
}

int getMin() {
    return st.top().second;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Optimal (Single Stack, O(1) Extra Space)

// This is the most optimized interview solution.
// on stack instead of storing the actual num store an top value
// this encoded value can be used to find the previous min value, let the be ecoded_value
// and new minimum value will be stored in new_min
// so top_value is pushed on stack and current min is maintained in new_min integer 

// now when a new value arrives if it is greater than curr_min then push it as it is on top of the stack 
// but if the value is smaller than curr_min then push the value as top_value = 2 * new_min - prev_min

// in case of pop - if the top value is greater than curr_min then pop it --> we don't need to update curr_min
// but if the top value is less than curr_min then pop it and update curr_min to prev_min which will be 

// we need to find the value of prev_min when the top value is less than curr_min and is getting popped
// so prev_min = 2 * new_min - top_value


// Idea
// Maintain:

// stack<long long> st;
// long long mini;

// When a new minimum arrives:

// encodedValue = 2*x - mini
// Store encoded value instead of actual value.

// Update:

// mini = x

// While popping:

// If top value is less than mini,
// it means it is encoded.

// Recover previous minimum:

// previousMin = 2*mini - encodedValue
// Example
// Push 5
// mini = 5

// Push 2
// encoded = 2*2 - 5 = -1
// mini = 2

// Stack:
// 5 -1

// Current min = 2



private:
    stack<long long> st;
    long long mini;

public:
    void push(int x) {

        if (st.empty()) {
            mini = x;
            st.push(x);
        }
        else if (x >= mini) {
            st.push(x);
        }
        else {
            st.push(2LL * x - mini);
            mini = x;
        }
    }

    void pop() {

        if (st.empty()) return;

        long long curr = st.top();
        st.pop();

        if (curr < mini) {
            mini = 2 * mini - curr;
        }
    }

    int top() {

        long long curr = st.top();

        if (curr < mini)
            return mini;

        return curr;
    }

    int getMin() {
        return mini;
    }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Reason why last one is O(1) extra space 
// Not O(1) total space 

// The key idea is that space complexity analysis usually separates the space required for the data structure itself from the extra (auxiliary) space used to support operations.

// Memory used = 2N integers. for single stack with pairs or two stacks

// Again:
// O(2N)=O(N)
// So space complexity is O(N).


// For N elements:

// Stack stores exactly N values.
// One extra variable mini.

// Memory:
// N+1

// The stack itself is necessary because we're implementing a stack. The additional memory beyond the stack is just one variable.
// Therefore:

// Total data structure space = O(N)
// Extra/Auxiliary space = O(1)

// This is why many books and interviewers say:
// "O(1) extra space"
// not
// "O(1) total space"