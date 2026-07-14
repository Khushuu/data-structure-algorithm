// Given the root node of a tree return its height
// so if only one node is there the height will be 1
// if a root node has only one child height will be 1 (root) + 1 (child)

// Approach
// if we add 1 for the height contribution of current node 
// and call height() function for the child node we can get the height of the tree
// also we will always pick the max height returned by left and right child
// as max height of the child determines the actual height of the tree

// base condition
// if a node is null then its height is 0
// if a node has no child it still contributes a height of 1 for itself

// T.C = O(n) - all nodes are traversed to get the height
// S.C = O(n) - call stack - if a binary tree follows linked list structure
int height(TreeNode* node) {

	if(node == nullptr) return 0;

	int leftHeight = height(node->left);
	int rightHeight = height(node->right);

	// 1 for current node and max(leftHeight, rightHeight) for height of children nodes
	return 1 + max(leftHeight, rightHeight); 
}

