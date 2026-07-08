// PROBLEM - 1
// 904. Fruit Into Baskets
// Dynamic Sliding Window Problem
// Similar to pick toys problem - 4 in AV playlist 

// given a set of integers representing different type of fruits
// at a time only two baskets can be kept
// find the maximum number of fruits that can be collected

// e.g nums = [1, 2, 1, 2, 2]
// output = 3
// explanation: we can collect 3 fruits [1, 2, 2]

// T.C - O(n)
// S.C - O(1)

// similar to longest substring with k distinct characters problem
// here the value of k is set to 2

// approach
// maintain a freq map 
// add the fruit to the window and increment frequency of that fruit
// if the freq map size is greater than 2, remove the fruit from the window and decrement its frequency
// return the size of the window

class Solution {
public:
    int totalFruit(vector<int>& fruits) {

        int l = 0;
        int r = 0;
        int result = 0;
        unordered_map<int, int> freq;

        while (r < fruits.size()) {

            freq[fruits[r]]++;

            // make the window valid first
            while (freq.size() > 2) {

                freq[fruits[l]]--;

                if (freq[fruits[l]] == 0)
                    freq.erase(fruits[l]);

                l++;
            }

            result = max(result, r - l + 1);
            r++;
        }

        return result;
    }
};
