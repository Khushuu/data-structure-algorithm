// 543. Diameter of Binary Tree
// given the root of the binary tree
// return the diameter of the binary tree
// The diameter of a binary tree is the length of the longest path between any two nodes in a tree.
// This path may or may not pass through the root.
// The length of a path between two nodes is represented by the number of edges between them.

// O(n*n) approach thinking
// traverse each node 
// find the height of left subtree and right subtree from this node - add these to get diameter from this node
// keep track of maximum diameter found so far
// since for each node we again traverse left and right subtree to find the height
//  and to deduce diameter from this node
// time complexity: O(n*n)

// approach 
// each node has two options
// either it becomes the head of the diameter with left and right subtree and becomes the result 
// or it contributes left or right subtree of it to the result 
// when the node decides to become the decision maker we deduce the result
// when it doesn't decide to be the answer itself but contribute to the result 

// diameter of the tree is defined as the length of the path - the longest path
// so if we have a root node with two child one on left an one on right
// the diameter of the tree will be 2 --> as there are two edges connecting nodes with the child

// when a node wants to be the answer it makes a diameter of = leftheight + rightHeight
// when a node contributes to the diameter it also gives an edge that connectes it to the parent node 
// hence it returns = 1 + max(leftHeight, rightHeight);

// Time Complexity: O(N) - each node is visited once 
// Space Complexity: O(H) - Recursive stack depth is equal to the height of the tree
// Worst case (Skewed Tree): O(N) (if tree is like a linked list)
// Best case (Balanced Tree): O(log N)
// -------------------------------------------------------------------------------------------------------
int result = 0;
diameter(root, result);

int diameter(TreeNode* node, int& result) {

	if(node == nullptr) return 0;

	int left = diameter(node->left, result);
	int right = diameter(node->right, result);

	result = max(result, left + right); // wants to be the diameter

	return 1 + max(left, right); // contributes to the diameter
}
// -------------------------------------------------------------------------------------------------------

// NOTE: in this case the temp, ans logic won't work directly 
// for calculating temp we add 1 to max(left, right) --> but this should only be done if there is a calling function
// if there is no one to call this function adding an extra node will not work and give incorrect result 

// modify the logic to add 1 when returning to the temp
// NOT ADVISED
// -------------------------------------------------------------------------------------------------------

int diameter(TreeNode* node, int& result) {

	if(node == nullptr) return 0;

	int left = diameter(node->left, result);
	int right = diameter(node->right, result);

	int ans = left + right; // become the answer
	int temp = max(left, right); // contribute to the answer 

	// deduce result using max of temp, ans and result
	result = max({result, temp, ans});

	return 1 + temp;
}

// -------------------------------------------------------------------------------------------------------
