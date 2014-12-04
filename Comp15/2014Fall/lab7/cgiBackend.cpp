#include "cgiBackend.h"

using namespace std;
//using namespace cgicc;

void copyToTrie(string s,Trie *trie) {
	// the string will be a newline-separated list of 3-tuples (comma separated)
	vector<preNode> preNodes;
	size_t charCount,prevCount;
	bool done=false;
	preNode pn;
	while (!done) {
		// get first token in tuple
		charCount = s.find(',');
		if (charCount == string::npos) break;
		pn.level = atoi(s.substr(0,charCount).c_str());
		//cout << "level:" << pn.level << "..." << endl;
		
		// second token
		prevCount = charCount+1;
		charCount = s.find(',',prevCount);
		pn.c = s.substr(prevCount,charCount-prevCount)[0];
		//cout << "char:" << pn.c << "..." << endl;
		
		// third token
		prevCount = charCount+1;
		charCount = s.find('\n',prevCount);
		pn.wordMarker = 
		   (atoi(s.substr(prevCount,charCount-prevCount).c_str()) ? true : false);
		//cout << "wordMarker:" << pn.wordMarker << "..." << endl;
		
		s = s.substr(charCount+1);		
		preNodes.push_back(pn);
	}
	trie->addPreNodes(preNodes);	
}

