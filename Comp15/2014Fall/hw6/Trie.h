/*
 * Trie.h
 *
 *  Created on: Dec 4, 2014
 *      Author: hzhang07
 */

#ifndef __trie__Trie__
#define __trie__Trie__

#include <iostream>
#include "Trie.h"
#include "Node.h"

using namespace std;

class Trie {
public:
        Trie();
        ~Trie();
        void addWord(string s, WordCountNode* wcNode);
        bool searchWord(string s);
        Node* getEndNode(string s);
        void deleteWord(string s);
        void printTrie();

private:
	void postorderDelete(Node* node);

        Node* root;

};

#endif /* defined(__trie__Trie__) */
