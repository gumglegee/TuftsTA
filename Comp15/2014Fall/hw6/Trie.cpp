/*
 * Trie.cpp
 *
 *  Created on: Dec 4, 2014
 *      Author: hzhang07
 */

#include "Trie.h"

//constructor
Trie::Trie() {
	root = new Node();
}

//desctuctor
Trie::~Trie() {
	//postorder delete
	postorderDelete(root);
}

// postorderDelete
// 	purpose: post-order traverse the trie and delete all nodes
// 	arguments: node pointer
// 	returns: none
void Trie::postorderDelete(Node* node) {
	if (node == NULL)
		return;

	for (int i = 0; i < node->ALPHABET_LENGTH; i++) {
		postorderDelete(node->getChildList()[i]);
	}

	node->freeList();
	delete node;
}

// addWord
// 	purpose: add the word and word freq info into the trie
// 	arguments: the word s, the WordCountNode wcNode
// 	returns: void
void Trie::addWord(string s, WordCountNode* wcNode) {
	Node* parent = root;
	Node* cur = NULL;

	for (int i = 0; i < s.length(); i++) {
		//get the child node
		cur = parent->findChild(s[i]);

		//create a node if necessary
		if (cur == NULL) {
			cur = new Node();
			cur->setCharacter(s[i]);

			//add the node into trie
			parent->appendChild(cur);
		}

		//update parent
		parent = cur;
	}

	//set work marker
	cur->setWordMarker();
	cur->addWordCount(wcNode);
}

// searchWord
// 	purpose: find one word in the trie
// 	argument: the word s
// 	returns: bool value, true if find, false otherwise
bool Trie::searchWord(string s) {
	// TODO: Student writes this function
	Node* parent = root;
	Node* cur = NULL;

	for (int i = 0; i < s.length(); i++) {
		cur = parent->findChild(s[i]);

		if (cur == NULL) {
			return false;
		}

		parent = cur;
	}

	return cur->getWordMarker();
}

// getEndNode
// 	purpose: get the word end node from the trie
// 	argument: the word s
// 	returns: Node*, pointer to the word end node
Node* Trie::getEndNode(string s) {
	Node* parent = root;
	Node* cur = NULL;

	for (int i = 0; i < s.length(); i++) {
		cur = parent->findChild(s[i]);

		if (cur == NULL) {
			return NULL;
		}

		parent = cur;
	}

	return cur;
}
