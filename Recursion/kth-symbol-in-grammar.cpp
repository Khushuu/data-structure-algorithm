// 779. K-th Symbol in Grammar
// this will be done using recursion
// lets see the pattern here
// 0 (n = 1) [1]
// 01 (n = 2) [2]
// 0110 (n = 3) [4]
// 0110 1001 (n = 4) [8]

// no. of elements in each row is equal to pow(2, n - 1)
// the first half of nth row is same as (n - 1)th row
// the second half of nth row is complement of (n - 1)th row
// using this we can form the induction step

// so if k is <= mid its value will be same as (n - 1)th row
// but if k is > mid then its value will be complement of (n - 1) row


// T.C = O(N) - each level is called once 
// S.C = O(N) - recursion stack 

// ------------------------------------------------------------------------------------------------------
int kthGrammar(int n, int k) {
	
	if(n == 1) return 0; // has 0 when only single row is there

	int mid = pow(2, n - 1) / 2; // middle of the total elements in nth row

	if(k <= mid) return kthGrammar(n - 1, k); // same as previous row

	return !kthGrammar(n - 1, k - mid); // complement of previous row
}
// ------------------------------------------------------------------------------------------------------
