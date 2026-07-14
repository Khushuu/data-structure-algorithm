// given n number of disks and 3 towers named A, B, C
// all the disks are kept in increasing order of size in tower A
// move all the disk from A to C using tower B
// Only one disk can be moved at a time.
// A disk cannot be placed on top of a smaller disk.
// Only the top disk of a rod can be moved.

// A - source 
// B - helper
// C - destination

// print steps for movement of disk to move from A to C

// Contraints
// only one disk can be picked at once
// at no time a bigger disk is kept on top of smaller disk
// even while moving alway keep the smaller disk only of top of bigger disk

// Approach

// Step 1
// firstly lets move n - 1 disks from A to B using C
// why do we do this --> we want only the biggest plate in A to be left --> and rest of plates should be in B
// now we can place the nth disk on C

// Step 2
// now n - 1 disks are in B 
// we have to move these n - 1 disks from B to C using A 

// Base condition
// if only one disk is there in A, move it directly from A to C --> write the step movement
// u can also count the number of steps using global variable count and do count++ in the recursive call

// n, source, destination, helper
// Move (N-1) disks from source (A) → auxiliary (B) using C.
// Move the largest disk from source (A) → destination (C).
// Move (N-1) disks from auxiliary (B) → destination (C).

// Time Complexity: T(n) = O(2^n)
// Recurrence relation: T(n) = 2T(n - 1) + O(1)
// Solving this recurrence gives: T(n) = O(2^n)
// Exponential Time Complexity O(2^n) since each recursive call creates two more calls.

// Space Complexity: O(n) due to recursive function call stack.

// NOTE: Since Tower of Hanoi inherently requires O(2^n) moves, there's no faster approach.
// ----------------------------------------------------------------------------------------
void towerOfHanoi(int n, char A, char C, char B) {

	if(n == 1) {
		cout << "Move disk 1 from " << A << " to " << C << endl;
		return;
	}

	// this n - 1 is done because we want to move the nth last disk from A to C using B
	towerOfHanoi(n - 1, A, B, C); 
	cout << "Move disk " << n << " from " << A << " to " << C << endl;

	// recalling the same function for n - 1 disks
	// this n - 1 is done because we now have (n - 1) disks left which need to be moved from B to C using A
	towerOfHanoi(n - 1, B, C, A); 
}
// ----------------------------------------------------------------------------------------

// result for towerOfHanoi(3, 'A'. 'B', 'C')
// Move disk 1 from A to C
// Move disk 2 from A to B
// Move disk 1 from C to B
// Move disk 3 from A to C
// Move disk 1 from B to A
// Move disk 2 from B to C
// Move disk 1 from A to C