//
//  Trie.cpp
//  trie
//
//  Created by Chris Gregg on 3/29/14.
//  Copyright (c) 2014 Chris Gregg. All rights reserved.
//

#include "Trie.h"

Trie::Trie()
{
        root = new Node();
}

Trie::~Trie()
{
        // Free memory
}

void Trie::addWord(string s)
{
        // TODO: Student writes this function
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
}


bool Trie::searchWord(string s)
{
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

void Trie::printTrie(){
        root->printNode(0);
}

void Trie::addPreNodes(vector<preNode> preNodes) {
	root->addPreNodes(preNodes,0,1);
}
