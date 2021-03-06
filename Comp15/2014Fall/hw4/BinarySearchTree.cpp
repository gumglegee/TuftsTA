/*
 * BinarySearchTree.cpp
 */

#include <iostream>
#include "BinarySearchTree.h"

using namespace std;

BinarySearchTree::BinarySearchTree() {
	// TODO: Students write code here
	root = NULL;
}

BinarySearchTree::~BinarySearchTree() {
	// walk tree in post-order traversal and delete
	post_order_delete(root);
}

void BinarySearchTree::post_order_delete(Node *node) {
	// TODO: students write code here
	// (hint: use a post-order traversal to remove all nodes)

	if (node == NULL)
		return;

	//recursively delete left node
	if (node->left != NULL)
		post_order_delete(node->left);

	//recursively delete right node
	if (node->right != NULL)
		post_order_delete(node->right);

	//delete the node itself
	delete node;
}

// copy constructor
BinarySearchTree::BinarySearchTree(const BinarySearchTree &source) {
	// use pre-order traversal to copy the tree
	root = pre_order_copy(source.root);
}

// assignment overload
BinarySearchTree& BinarySearchTree::operator=(const BinarySearchTree &source) {
	// TODO: Students write code here
	// check for self-assignment
	if (this != &source) {
		// delete current tree if it exists
		post_order_delete(root);

		// use pre-order traversal to copy the tree
		root = pre_order_copy(source.root);
	}

	// don't forget to "return *this"
	return *this;
}

Node * BinarySearchTree::pre_order_copy(Node *node) {
	// TODO: Students write code here
	// (hint: use a pre-order traversal to copy details from the
	// node to a new_node)
	if (node == NULL)
		return NULL;
	Node *new_node = new Node();

	//copy all the member value
	new_node->count = node->count;
	new_node->data = node->data;
	
	new_node->left = NULL;
	new_node->right = NULL;

	if (node->left != NULL)
		new_node->left = pre_order_copy(node->left);

	if (node->right != NULL)
		new_node->right = pre_order_copy(node->right);

	return new_node;
}

int BinarySearchTree::find_min() {
	if (root == NULL)
		return INT_MIN;
	return find_min(root)->data;
}

Node *BinarySearchTree::find_min(Node *node) {
	// TODO: Students write code here

	//if the node does not have the left child, it will be the minimal
	if (node->left == NULL)
		return node;
	//if the node has the left child, recursively find the minimal
	else
		return find_min(node->left);
}

int BinarySearchTree::find_max() {
	// TODO: Students write code here
	if (root == NULL)
		return INT_MAX;
	return find_max(root)->data;
}

Node *BinarySearchTree::find_max(Node *node) {
	// TODO: Students write code here

	//if the node does not have the right child, it will be the maximal
	if (node->right == NULL)
		return node;
	//if the node has the right child, recursively find the maximal
	else
		return find_max(node->right);
}

bool BinarySearchTree::contains(int value) {
	// TODO: Students write code here
	return contains(root, value);
}

bool BinarySearchTree::contains(Node *node, int value) {
	// TODO: Students write code here

	//returns false, if the node is empty
	if (node == NULL)
		return false;

	//if the data is equal to the value, returns true
	if (node->data == value)
		return true;

	//recursively search the left or right branch
	if (node->data < value)
		return contains(node->right, value);
	else
		return contains(node->left, value);
}

void BinarySearchTree::insert(int value) {
	insert(root, NULL, value);
}

void BinarySearchTree::insert(Node *node, Node *parent, int value) {
	// TODO: Students write code here

	//if the node is empty, create a new node
	if (node == NULL) {
		node = new Node();
		//initialize the details
		node->data = value;
		node->count = 1;
		node->left = NULL;
		node->right = NULL;

		//if the node is the root
		if (parent == NULL)
			root = node;
		else {
			if (parent->data > value)
				//left child
				parent->left = node;
			else
				//right child
				parent->right = node;
		}
	} else {
		// the node is not empty
		if (node->data == value)
			node->count++;
		else {
			if (node->data > value)
				//recursively insert the value into the left
				insert(node->left, node, value);
			else
				//recursively insert the value into the right
				insert(node->right, node, value);
		}
	}
}

bool BinarySearchTree::remove(int value) {
	return remove(root, NULL, value);
}

bool BinarySearchTree::remove(Node *node, Node *parent, int value) {
	// TODO: Students write code here
	// (cannot be a lazy removal)

	if (node == NULL) 
		return false;

	//if the node contains the value
	if (node->data == value) {
		//duplicate node
		if (node->count > 1) {
			node->count--;
			return true;
		} else { //only one count
			if (node->left == NULL && node->right == NULL) {
				//the node is a leaf

				delete node; //delete the node

				if (parent == NULL) {
					cout << "leaf & root" << endl;
					//the tree only contains one node: root
					//update root
					root = NULL;
				} else {
					cout << "leaf" << endl;
					if (value < parent->data) {
						//the node is the left child of its parent
						parent->left = NULL;
					} else {
						//the node is the right child of its parent
						parent->right = NULL;
					}
				}

				return true;
			} //end if leaf

			if (node->left == NULL || node->right == NULL) {
				//the node has only one child

				if (parent == NULL) {
					//the node is the root
					cout << "one child & root" << endl;
					if (node->left != NULL)
						root = node->left;
					else
						root = node->right;
				}
				else {
					//the node is not the root
					cout << "one child" << endl;
					if (node->left != NULL) {
						//the node has a left child
						if (node->data < parent->data) {
							//the node is the left child of its parent
							parent->left = node->left;
						} else {
							//the node is the rifht child of its parent
							parent->right = node->left;
						}
					} else {
						//the node has a right child
						if (node->data < parent->data) {
							//the node is the left child of its parent
							parent->left = node->right;
						} else {
							//the node is the rifht child of its parent
							parent->right = node->right;
						}
					} //end else right child
				}
				
				delete node;

				return true;
			} else {
				//the node has two children
				cout << "two children" << endl;

				//find the minimal value of the right child
				Node *rmin = find_min(node->right);

				//find the parent of the minimal node
				Node *rminparent = find_parent(node, rmin);

				//update the node details using rmin's detail
				node->data = rmin->data;
				node->count = rmin->count;
				rmin->count = 1;

				//remove the rmin from the bst
				return remove(rmin, rminparent, node->data);

			}

		}// end else only one count
	} //end if contains the value
	else { //the node does not contain the value
		if (node->data > value) {
			//search the left branch
			return remove(node->left, node, value);
		} else {
			//search the right branch
			return remove(node->right, node, value);
		}
	}
}

int BinarySearchTree::tree_height() {
	return tree_height(root);
}

int BinarySearchTree::tree_height(Node *node) {
	// TODO: Students write code here

	//returns 0, if the node is empty
	if (node == NULL)
		return 0;

	//get the height of both branches
	int lheight = tree_height(node->left);
	int rheight = tree_height(node->right);

	int max = lheight >= rheight ? lheight : rheight;

	return max + 1;
}

// returns the total number of nodes
int BinarySearchTree::node_count() {
	return node_count(root);
}

int BinarySearchTree::node_count(Node *node) {
	// TODO: Students write code here

	//returns 0 if the node is empty
	if (node == NULL)
		return 0;

	//get the counts of both branches
	int lcount = node_count(node->left);
	int rcount = node_count(node->right);

	return lcount + rcount + node->count;
}

// return the sum of all the node values (including duplicates)
int BinarySearchTree::count_total() {
	return count_total(root);
}

int BinarySearchTree::count_total(Node *node) {
	// TODO: Students write code here:
	//returns 0 if the node is empty
	if (node == NULL)
		return 0;

	//get the total of both branches
	int ltotal = count_total(node->left);
	int rtotal = count_total(node->right);

	return ltotal + rtotal + node->count * node->data;
}

// use the printPretty helper to make the tree look nice
void BinarySearchTree::print_tree() {
	printPretty(root, 1, 0, std::cout);
}

Node *BinarySearchTree::find_parent(Node *node, Node *child) {
	if (node == NULL)
		return NULL;

	// if either the left or right is equal to the child,
	// we have found the parent
	if (node->left == child || node->right == child) {
		return node;
	}

	// Use the binary search tree invariant to walk the tree
	if (child->data > node->data) {
		return find_parent(node->right, child);
	} else {
		return find_parent(node->left, child);
	}
}
