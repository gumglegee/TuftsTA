//
//  cgiBackend.h

#ifndef __cgiBackend__
#define __cgiBackend__

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

//#include "cgicc/Cgicc.h"
//#include "cgicc/HTTPHTMLHeader.h"
//#include "cgicc/HTMLClasses.h"
#include "Trie.h"

struct functionAndWord {
	string function;
	std::string word;
};

void copyToTrie(std::string s,Trie *trie);

#endif /* defined(__cgiBackend__) */
