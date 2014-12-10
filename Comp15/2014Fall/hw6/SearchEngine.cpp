/*
 * SearchEngine.cpp
 *
 *  Created on: Dec 2, 2014
 *      Author: hzhang07
 */

#include "SearchEngine.h"

// constructor
SearchEngine::SearchEngine() {
	//nothing
}

// destructor
SearchEngine::~SearchEngine() {
	//free memory for all the blocks allocated to songdatabase
	for (int i = 0; i < songdatabase.size(); i++) {
		delete songdatabase[i];
	}
}

//
// read_lyics
//   purpose: read in song data from a disk file
//   arguments: the name of the file, bool to ask for progress status
//   returns: nothing
//   does: calls a function each time a word is found
//
void SearchEngine::read_lyrics(char * filename, bool show_progress) {
	ifstream in(filename); // creates an input stream
	int song_count = 0; // for progress indicator
	string artist, title, word;
	Song* s;

	// -- While more data to read...
	while (!in.eof()) {
		// -- First line is the artist
		getline(in, artist);
		if (in.fail())
			break;

		// -- Second line is the title
		getline(in, title);
		if (in.fail())
			break;

		//create a new song
		s = new Song(artist, title);

		if (show_progress) {
			song_count++;
			if (song_count % 10000 == 0) {
				cout << "Read " << song_count << " songs."
						<< endl;
				cout << "At " << song_count << " Artist: "
						<< artist << " Title:" << title
						<< endl;
			}
		}
		// -- Then read all words until we hit the
		// -- special <BREAK> token

		//local variables
		vector<WordCountNode*> wordCountList;
		int wi = -1;

		//read all the words in lyrics  one by one
		while (in >> word && word != "<BREAK>") {
			//increase word index
			wi++;

			//covert the word to alpha-only
			string wordn = alpha_only(word);

			//add the original word to the lyrics of the new song
			s->addLyrics(word);

			if (wordn.compare("") == 0)
				continue;
	
			//update the count and wordindex in wordCountList
			WordCountNode* cur = findPosition(wordCountList, wordn);
			if (cur == NULL) {
				//create a new node for the word
				cur = new WordCountNode();
				cur->word = wordn;
				cur->count = 1;
				cur->songIndex = song_count - 1;
				cur->wordIndex.push_back(wi);

				//add it into the list
				wordCountList.push_back(cur);
			}
			else {
				//update the info
				cur->count += 1;
				cur->wordIndex.push_back(wi);
			}
		}

		// -- Important: skip the newline left behind
		in.ignore();

		// after read all the song info
		// 1. add the song to the songdatabase
		songdatabase.push_back(s);

		// 2. add all the WordCountNode(s) into the Trie
		for (int i = 0; i < wordCountList.size(); i++) {
			//cout << "Adding " << wordCountList[i]->word << ";"<< endl;
			wordList.addWord(wordCountList[i]->word, wordCountList[i]);
		}

	}

//	for (int i = 0; i < songdatabase.size(); i++)
//		songdatabase[i].print_song();
}

// findPosition
//   purpose: find the position of the word in the list
//   arguments: the vector of WordCountNode*, string word to search
//   returns: WordCountNode* contains word, NULL if not find the word
WordCountNode* SearchEngine::findPosition(const vector<WordCountNode*> list, string word) {
	for (int i = 0; i < list.size(); i++) {
		if (list[i]->word.compare(word) == 0)
			return list[i];
	}

	return NULL;
}

//
// alpha_only
//   purpose: converts a string to lowercase and alphabetic characters
//            only. E.g., "Bang!" becomes "bang"
//   arguments: a string
//   returns: the alpha-only string
//   does: converts the string
//
string SearchEngine::alpha_only(string s) {
	ostringstream ss;
	for (size_t i = 0; i < s.length(); i++) {
		if (isalnum(s[i])) {
			ss << (char) (tolower(s[i]));
		}
	}
	return ss.str();
}

// search
// 	purpose: search a word in the database, if found, print the context of the word
// 	arguments: the string word
// 	returns: void
void SearchEngine::search(string word) {
	//if the word is found in the database, print the context
	if (wordList.searchWord(word)) {
		//get the top rank list
		vector<WordCountNode*> topRankList = selectTop(wordList.getEndNode(word)->getWordCountList());

		//print context
		for (int i = 0; i < topRankList.size(); i++) {
//			cout << topRankList[i]->word << " " << topRankList[i]->count << "in song " << topRankList[i]->songIndex << " : ";	

			for (int j = 0; j < topRankList[i]->wordIndex.size(); j++) {
//				cout << topRankList[i]->wordIndex[j] << ", ";
				songdatabase[topRankList[i]->songIndex]->print_context(topRankList[i]->wordIndex[j]);
			}
		}

		cout << "<END-OF-REPORT>" << endl;

	}
	else {
		cout << "Can not find the word " << word << " in the database!" << endl; 
	}

}

// selectTop
// 	purpose: select the top ranked songs from the list
// 	arguments: the original unsorted list
// 	returns: the top ranked list
vector<WordCountNode*> SearchEngine::selectTop(vector<WordCountNode*> list) {
	int i,j;
	int iMax;
	
	vector<WordCountNode*> selectedList;

//	for (int k = 0; k < list.size(); k++) {
//		cout << list[k]->word << " " << list[k]->count << "in song " << list[k]->songIndex << " : ";
//		for (int l = 0; l < list[k]->wordIndex.size(); l++) {
//			cout << list[k]->wordIndex[l] << ", ";
//		}
//		cout << "\n";
//	}
//	cout << "Sorted: " << endl;


	//only find the top TOPRANK max elements
	for (j = 0; j < TOPRANK && j < list.size(); j++) {
	     	iMax = j;
		// test against elements after j to find the largest
		for (i = j + 1; i < list.size(); i++) {
			// if this element is larger, then it is the new maximum  
			if (list[i]->count > list[iMax]->count) {
				// remember its index
				iMax = i;
			}
		}

		//add it to the return list
		selectedList.push_back(list[iMax]);

		//swap the maximun to the front
		if(iMax != j) {
			WordCountNode* temp = list[iMax];
			list[iMax] = list[j];
			list[j] = temp;
		}

	}

	return selectedList;
}

