/*
 * Node.h
 *
 *  Created on: Dec 4, 2014
 *      Author: hzhang07
 */

#ifndef __trie__Node__
#define __trie__Node__

#include <iostream>
#include <vector>

using namespace std;

struct WordCountNode {
	string word;
	int count;	// the number of the word appears in the song
	int songIndex;	// the index of the song in 'songdatabase'
	vector<int> wordIndex;	// index of the word in lyrics
};

class Node {
public:
	static const int ALPHABET_LENGTH = 36; //a-z, 0-9
        Node();
        ~Node();
	void freeList();
        char content() { return theCharacter; }
        void setCharacter(char c) { theCharacter = c; }
        bool getWordMarker() { return wordMarker; }
        void setWordMarker() { wordMarker = true; }
        vector<WordCountNode*> getWordCountList() { return detailInfoList;}
	Node** getChildList() {return children;}
        Node* findChild(char c);
        void appendChild(Node* child);
        void addWordCount(WordCountNode* wcNode);
        
private:
        char theCharacter;
        bool wordMarker;
        Node* children[ALPHABET_LENGTH];
        vector<WordCountNode*> detailInfoList;
};


#endif /* defined(__trie__Node__) */
