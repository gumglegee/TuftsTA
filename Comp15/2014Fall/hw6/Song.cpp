/*
 * Song.cpp
 *
 *  Created on: Dec 2, 2014
 *      Author: hzhang07
 */

#include "Song.h"

// default constructor
Song::Song() {
	artist = "";
	title = "";
}

// constructor, initial the song with two arguments
Song::Song(string a, string t) {
	artist = a;
	title = t;
}

// destructor
Song::~Song() {
	//nothing
}

// addLyrics
// 	purpose: when reading the lyrics, add the word one by one
// 		to the lyrics vector<string>
// 	arguments: the word to be added
// 	returns: void
void Song::addLyrics(string word) {
	lyrics.push_back(word);
}

string Song::getArtist() {
	return artist;
}

string Song::getTitle() {
	return title;
}

// print_song
// 	purpose: print the song infromation (artist, title, lyrics) 
// 	arguments: none
// 	returns: void
void Song::print_song() {
	cout << artist << "\n" << title << "\n";

	for (int i = 0; i < lyrics.size(); i++)
		cout << lyrics[i] << " ";

	cout << "\n\n";
}

// print_context
// 	purpose: print the context (11 words: 5 before and 5 after of  a giving word)
// 	arguemnts: the index of the word in the lyrics
// 	returns: void
void Song::print_context(int wordIndex) {
	int start = (wordIndex-5)>0 ? wordIndex-5 : 0;

	int end = (wordIndex+5)<lyrics.size() ? wordIndex+5 : lyrics.size()-1;

	cout << "Title: " << title << "\n";
	cout << "Artist: " << artist << "\n";
	cout << "Context: ";

	for (int i = start; i <= end; i++) {
		cout << lyrics[i] << " ";
	}
	
	cout << "\n" << endl;
}
