#include <iostream>
#include<unistd.h>
#include<signal.h>
#include<cstdlib>

#include "Trie.h"
#include "cgiBackend.h"

using namespace std;

void alarm_callback_handler(int signum) // to catch infinite loop
{
   cout << "Content Type: text/plain\n";
   cout << "Program terminated.\n";
   // Cleanup and close up stuff here
   // Terminate program
   exit(signum);
}


// Test program
int main(int argc, char** argv)
{
	if (argc==1) {
		char username[50];
		getlogin_r(username,50);
		cout << "\nThis is a backend program for a web page.\n";
		cout << "\nTo test your program, ";
		cout << "open Firefox and go to the following web page:\n";
		cout << "\nhttp://www.cs.tufts.edu/~";
		cout << username << "/lab7/trie.html\n\n";
		return -1;
	}	
	signal(SIGALRM, alarm_callback_handler);
	
	alarm(5);
	
	string word = argv[1];
	string function = argv[2];
	string currentTrie = argv[3];

        Trie* trie = new Trie();
        functionAndWord f;
        copyToTrie(currentTrie,trie);

        // Send HTTP header
	cout << "Content Type: text/plain\n" << endl;
        if (function == "addWord") {
        	trie->addWord(word);
        	trie->printTrie();
        }
        else if (function == "searchWord") {
        	if ( trie->searchWord(word) ) {
        		cout << "Found " << word << "\n";
        	}
        	else {
        		cout << "Did not find " << word << "\n";
        	}
        }
        
        delete trie;
        return 0;
}
