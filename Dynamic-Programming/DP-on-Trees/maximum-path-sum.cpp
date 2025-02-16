// Part - 1 
// 124. Binary Tree Maximum Path Sum

// Maximum Path Sum between any node 
// Given the root of a binary tree, return the maximum path sum of any non-empty path.
// The path sum of a path is the sum of the node's values in the path.

// given a binary tree
// return the maximum path sum from any node to any node
// that means the node does not have to be leaf node always
// node values also consists of negative values

// appraoch
// each node has two choices in this problem
// either contribute to the answer 
// or become the answer itself

// when it contributes to the answer it has three options
// add left path sum to itself --> leftSum + node->val
// add right path sum to itself or  --> rightSum + node->val
// don't add any path sum to itself and just return node->val 
// node->val is returned without adding left or right path sum 
// in case (left + node) < node and (right + node) < node i.e --> left path sum < 0 and right path sum < 0
// we take the maximum out of these three options 

// when it becomes the answer itself --> just do leftSum + rightSum + node->val
// and deduce the result on the basis of this 

// intialize the result with int_min value 

// NOTE: at each point u have to update the result with the maximum of two options or the result itself 
// i.e either contribute to the answer or become the answer 

// T.C = O(N) - each node traversed once
// S.C = O(H) - H is the height of the tree - recursion stack 
// ---------------------------------------------------------------------------------------------------------
int result = INT_MIN;
pathSum(root, result);
return result;

int pathSum(TreeNode* node, int& result) {

	if(node == nullptr) return 0;

	int leftSum = pathSum(node->left, result);
	int rightSum = pathSum(node->right, result);

	// become the answer 
	int ans = leftSum + rightSum + node->val;

	// contribute to the answer 
	// 3 options 
	// left sum + node->val or rightSum + node->val or just node->val
	// if both leftSum and rightSum are negative 
	// the node will start fresh path from itself
	int temp = node->val + max({leftSum, rightSum, 0});

	// update result with the maximum of result, ans and temp 
	result = max({result, temp, ans});

	return temp;
}
// ---------------------------------------------------------------------------------------------------------

// PART - 2
// Maximum path sum between leaf node to leaf node 

// here either the node can form the answer itself = node->val + leftSum + rightSum
// or contribute to the answer

// when contributing to the answer the node has just two options
// either pick the leftSum and add node->val
// or pick the righSum and add node->val
// we can not just pick the node->val -- as the path should be from leaf to leaf node 

// ---------------------------------------------------------------------------------------------------------
int result = INT_MIN;
pathSum(root, result);
return result;

int pathSum(TreeNode* node, int& result) {

	if(node == nullptr) return 0;

	int leftSum = pathSum(node->left, result);
	int rightSum = pathSum(node->right, result);

	// become the answer 
	int ans = leftSum + rightSum + node->val;

	// contribute to the answer 
	// 2 options 
	// left sum + node->val or rightSum + node->val 
	// always either one of the two has to be picked as the path is from leaf to leaf
	int temp = node->val + max(leftSum, rightSum);

	// update result with the maximum of result, ans and temp 
	result = max({result, temp, ans});

	return temp;
}
// ---------------------------------------------------------------------------------------------------------

