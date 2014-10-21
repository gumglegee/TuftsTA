/*
 * BinarySearchTree.cpp
 */

#include <iostream>
#include "BinarySearchTree.h"

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

	node = NULL;
}

// copy constructor
BinarySearchTree::BinarySearchTree(const BinarySearchTree &source) {
	// use pre-order traversal to copy the tree
	root = pre_order_copy(source.root);
}

// assignment overload
BinarySearchTree& BinarySearchTree::operator=
		(const BinarySearchTree &source) {
	// TODO: Students write code here
	// check for self-assignment

	// delete current tree if it exists

	// use pre-order traversal to copy the tree

	// don't forget to "return *this"
}

Node * BinarySearchTree::pre_order_copy(Node *node) {
	// TODO: Students write code here
	// (hint: use a pre-order traversal to copy details from the
	// node to a new_node)
	if (node == NULL) return NULL;
	Node *new_node = new Node();

	//copy all the member value
	new_node->count = node->count;
	new_node->data = node->data;

	if (node->left != NULL)
		node->left = pre_order_copy(node->left);

	if (node->right != NULL)
		node->right = pre_order_copy(node->right);

	return new_node;
}

int BinarySearchTree::find_min() {
	if (root == NULL) return INT_MIN;
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
	if (root == NULL) return INT_MAX;
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

bool contains(Node *node, int value) {
	// TODO: Students write code here

	//returns false, if the node is empty
	if (node == NULL)
		return false;

	//if the data is equal to the value, returns true
	if (node->data == value)
		return true;

	//recursively search the left or right branch
	if (node->data < value)
		return contains(node->right);
	else
		return contains(node->left);
}

void BinarySearchTree::insert(int value) {
	insert(root,NULL,value);
}

void BinarySearchTree::insert(Node *node,Node *parent, int value) {
	// TODO: Students write code here
}

bool BinarySearchTree::remove(int value) {
	return remove(root,NULL,value);
}

bool BinarySearchTree::remove(Node *node, Node *parent, int value) {
	// TODO: Students write code here
	// (cannot be a lazy removal)
}

int BinarySearchTree::tree_height() {
	return tree_height(root);
}

int BinarySearchTree::tree_height(Node *node) {
	// TODO: Students write code here
}

// returns the total number of nodes
int BinarySearchTree::node_count() {
	return node_count(root);
}

int BinarySearchTree::node_count(Node *node) {
	// TODO: Students write code here
}

// return the sum of all the node values (including duplicates)
int BinarySearchTree::count_total() {
	return count_total(root);
}

int BinarySearchTree::count_total(Node *node) {
	// TODO: Students write code here:
}

// use the printPretty helper to make the tree look nice
void BinarySearchTree::print_tree() {
	printPretty(root, 1, 0, std::cout);
}

Node *BinarySearchTree::find_parent(Node *node,Node *child) {
	if (node==NULL) return NULL;

	// if either the left or right is equal to the child,
	// we have found the parent
	if (node->left==child || node->right == child) {
		return node;
	}

	// Use the binary search tree invariant to walk the tree
	if (child->data > node->data) {
		return find_parent(node->right,child);
	}
	else {
		return find_parent(node->left,child);
	}
}
