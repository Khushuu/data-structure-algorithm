// 1011. Capacity To Ship Packages Within D Days

// u have to minimize the capacity of the ship
// such that all weights can be delivered within days given

// maximum capacity of the ship can be some of all weights
// in this case in a single day all weights can be delivered
// so the maximum capacity = sum of all weights

// u need to find the minimum capacity
// condition of validity of picking a capacity is
// it should be delivered with given days
// u need a way to divide the weights such that it falls in the range

// use a helper function and pass it potential weight of the ship
// try to add a weight to the current day 
// if sum does not exceed the capacity of ship
// if it exceeds then increase the day count
// the counted number of days should be <= given days
// for the selected capacity to be valid

// if the capacity is not valid - increment it 
// otherwise if valid save it as the answer and try to minimize it

// time complexity = O(nlogm) --> m is the sum of all capacities
// space complexity = O(1)

class Solution {
private:
    bool isValidCapacity(int capacity, vector<int>& weights, int days) {

        int count = 1;
        int sum = 0;

        for(int weight: weights) {
            
            // it can never be added on any day
            if(weight > capacity) return false;

            if(sum + weight <= capacity) sum += weight;
            else {
                // move to next day and reset sum
                count++;
                sum = weight;
            }
        }


        return count <= days;
    }
public:
    int shipWithinDays(vector<int>& weights, int days) {

        int l = 0; 
        int r = accumulate(weights.begin(), weights.end(), 0);
        int result = 0;

        while(l <= r) {

            int mid = l + (r - l) / 2;

            if(isValidCapacity(mid, weights, days)) {
                result = mid;
                r = mid - 1;
            }
            else l = mid + 1;
        }

        return result;
    }
};