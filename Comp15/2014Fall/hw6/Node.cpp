/*
 * Node.cpp
 *
 *  Created on: Dec 4, 2014
 *      Author: hzhang07
 */

#include "Node.h"


// constructor
Node::Node() { 
	// initialization
	theCharacter = ' '; 
	wordMarker = false; 
	for (int i=0;i<ALPHABET_LENGTH;i++) children[i]=NULL;
}

// destructor
Node::~Node() {
	//nothing
}

// freeList
// 	purpose: free the memory of the WordCountNode list
// 	arguments: none
// 	returns: void
// 	use: called in the destructor of Trie
void Node::freeList() {
	//delete the detailInfoList if the Node has the list
	if (wordMarker) {
		for (int i = 0; i < detailInfoList.size(); i++) {
			delete detailInfoList[i];
	   	}        
	}
}

// appendChild
// 	purpose: append one child to the current node
// 	arguments: node pointer to the node to be appended
// 	returns: void
void Node::appendChild(Node* child) {
	if (isalpha(child->theCharacter))
		children[child->theCharacter - 'a'] = child;
	if (isdigit(child->theCharacter))
		children[child->theCharacter - '0' + 26] = child;
}

// findChild
// 	purpose: find the child node contains a given char
// 	arguments: char c
// 	returns: node pointer to the child, NULL if not find
Node* Node::findChild(char c){
	if (isalpha(c)) {
		return children[c - 'a'];
	}

	if (isdigit(c)) {
		return children[c - '0' + 26];
	}

	return NULL;
}

// addWordCount
// 	purpose: add a word freq info for the current node
// 	arguments: WordCountNode pointer
// 	returns: void
void Node::addWordCount(WordCountNode* wcNode) {
	detailInfoList.push_back(wcNode);
}

