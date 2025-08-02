// 496. Next Greater Element I

// given
// given two arrays nums1 and nums2
// find first greater element to the right of current element
// nums1 subset of nums2
// if not next greater element - result is -1

// approach
// use a map to store next greater element for nums2
// loop over from right to left of nums2
// use a stack to find the next greater element
// store result in map
// create a result array - store result by loop nums1

// concept
// start from the right of nums2 to find next greater element
// if the stack is empty - no next greater element
// if the current element is greater than the top of the stack - pop the stack
// if the current element is less than the top of the stack - store the top of the stack as next greater element
// push the current element to the stack
// we do this as the current element can be possible solution for the next greater element of the left elements

// time complexity - O(n + m) where n is the size of nums1 and m is the size of nums2
// space complexity - O(n + m) for the map and stack

class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        
        unordered_map<int, int> nextGreater;
        stack<int> stk;
        vector<int> result;

        // find nextGreater for all in nums2
        for(int i = nums2.size() - 1; i >= 0; i--) {

            int num = nums2[i];

            while(!stk.empty() && num > stk.top())
                stk.pop();
            
            if(stk.empty()) nextGreater[num] = -1;
            else nextGreater[num] = stk.top();

            stk.push(num);
        }

        // fill result
        for(int num: nums1) 
            result.push_back(nextGreater[num]);

        return result;
    }
};

// ----------------------------------------------------------------------------------------------------------

// 503. Next Greater Element II

// find next greater element in a cricular array
// which means next element of nums[n - 1] is nums[0]

// this means if there is no next greater element on the right
// the only difference of this problem wiht NGL 1 is
// even if u reach the end u keep looking from index 0
// until u reach index - 1

// consider this like the substring problem
// just add the same nums array after current nums array
// instead of practically doing this
// loop the array twice and deduce result

// process every element twice from right to left 
// to get the next greater element in circular manner

class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        
        int n = nums.size();
        stack<int> stk;
        vector<int> result(n, -1);
        
        for(int i = 2 * n - 1; i >= 0; i--) {
            
            int index = i % n;
            int num = nums[index];

            while(!stk.empty() && num >= stk.top()) stk.pop();

            // if stack is not empty push top element
            if(!stk.empty()) result[index] = stk.top();

            stk.push(num);
        }

        return result;
    }
};