/*
 * main.cpp
 *
 */

#include <string>
#include <sstream>

#include "SearchEngine.h"

using namespace std;


int main(int argc, char *argv[])
{
	string filename;
	SearchEngine searcher;

	if (argc == 2) { // if there is a filename on the command line
		searcher.read_lyrics(argv[1],true);
	}
	else { // use a pre-defined filename
		filename = "/h/hzhang07/GitHub/TuftsTA/Comp15/2014Fall/hw6/rick_db.txt";
		//filename = "lyrics_fulldb.txt";
		char* cfilename = const_cast<char*>(filename.c_str());
	        searcher.read_lyrics(cfilename,true);
	}

	while (1) {
		string word;
		cout << "Input a word:" << endl;
		cin >> word;
		if (word.compare("quit") != 0) {
			searcher.search(word);
		}
		else {
			break;
		}
	}

        return 0;
}
