// 2226. Maximum Candies Allocated to K Children

// maximum number of candies each child can get
// given k children
// all children should get equal number of candies
// minimum number of candies a child can get 0 
// this will be if total number of candies < number of children

// the maximum number of candies that can be divided
// is dependent on the maximum value in the list
// and the lowest value is 0
// do a BS on the answer

// BS approach
// set l = 0 and r = max item in candies 
// for every mid value check how many children it can be allocated to
// i.e count += candies[i] / x --> where x = mid 
// mid ==> no. of candies that are chosen for distributing
// if count >= k return true

// now we need to maximize the value of no. of candies to be distributed
// if canBeDistributed returns true then move to right
// i.e set left = mid + 1 and also store ans
// otherwise move towards left
// return ans

// Let n be the size of the candies array and m be the greatest value in it.
// Time Complexity: O(nlogm)
// Space Complexity: O(1)

bool canBeDivided(int x, vector<int>& candies, long long k) {
	
	long long countChildren = 0;

	for(int candiesCount: candies)
		countChildren += (candiesCount / x);
	
	return countChildren >= k;
}

int maximumCandies(vector<int>& candies, long long k) {

	// Binary Search on answer
	// start with l = 1 to avoid division by 0
	// as result is initiated to 0 if not valid value is found we return 0
	int l = 1; 
	int r = *max_element(candies.begin(), candies.end());
	int result = 0;

	while(l <= r) {

		int mid = l + (r - l) / 2;

		// try to maximize the number of candies that can be distributed
		if(canBeDivided(mid, candies, k)) {
			result = mid;
			l = mid + 1;
		}
		else r = mid - 1;
	}

	return result;
}
