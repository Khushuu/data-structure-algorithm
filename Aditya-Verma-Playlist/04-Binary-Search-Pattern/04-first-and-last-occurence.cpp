// PROBLEM - 1
// FIRST AND LAST OCCURENCE OF AN ELEMENT 

// given an array of integers nums sorted in ascending order, find the starting and ending position of a given target value.
// if the target is not found in the array, return [-1, -1]

// e.g nums = [5, 7, 7, 8, 8, 10], target = 8
// output = [3, 4]

// T.C - O(log n)
// S.C - O(1)

// approach
// Use binary search
// write two different binary search functions
// one to find the first occurence of an element 
// other to find the last occurence of an element 

// first occurence 
// in case if mid is same as target --> it is a possbile result 
// save mid in result 
// keep looking on the left side of the array

// last occurence 
// in case if mid is same as target --> it is a possible result
// save mid in result
// keep looking on the right side of the array

int firstOccurence(vector<int>& nums, int target) {

    int l = 0;
    int r = nums.size() - 1;
    int result = -1;

    while (l <= r) { 

        if(nums[mid] == target) {

            result = mid;
            r = mid - 1;
        }

        else if (target < nums[mid]) l = mid + 1;
        else r = mid - 1;
    }

    return result;
}

int lastOccurence(vector<int>& nums, int target) {

    int l = 0;
    int r = nums.size() - 1;
    int result = -1;

    while (l <= r) { 

        if(nums[mid] == target) {

            result = mid;
            l = mid + 1;
        }

        else if (target < nums[mid]) l = mid + 1;
        else r = mid - 1;
    }

    return result;
}

vector<int> searchRange(vector<int>& nums, int target) {
    
    return {firstOccurence(nums, target), lastOccurence(nums, target)};
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// PROBLEM - 2
// COUNT OF AN ELEMENT IN A SORTED ARRAY

// given an array of integers nums sorted in ascending order, find the number of occurrences of a given target value.
// if the target is not found in the array, return 0

// e.g nums = [1, 2, 3, 3, 3, 4, 5], target = 3
// output = 3

// T.C - O(log n)
// S.C - O(1)

// approach
// Use binary search
// write two different binary search functions
// one to find the first occurence of an element 
// other to find the last occurence of an element 

// count = lastOccurence - firstOccurence + 1

int count(vector<int>& nums, int target) {
    
    return lastOccurence(nums, target) - firstOccurence(nums, target) + 1;
}