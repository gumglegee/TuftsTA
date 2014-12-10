/*
 * SearchEngine.h
 *
 *  Created on: Dec 2, 2014
 *      Author: hzhang07
 */

#ifndef SEARCHENGINE_H_
#define SEARCHENGINE_H_

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "Song.h"
#include "Trie.h"

using namespace std;

class SearchEngine {
public:
	static const int TOPRANK = 10;

	SearchEngine();

	~SearchEngine();

	// read the lyrics from a file
	void read_lyrics(char * filename, bool show_progress);

	// search a word
	void search(string word);

private:

	vector<Song*> songdatabase;
	Trie wordList;

	WordCountNode* findPosition(const vector<WordCountNode*> list, string word);
	string alpha_only(string s);

	vector<WordCountNode*> selectTop(vector<WordCountNode*> list);
};

#endif /* SEARCHENGINE_H_ */
