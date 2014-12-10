/*
 * Song.h
 *
 *  Created on: Dec 2, 2014
 *      Author: hzhang07
 */

#ifndef SONG_H_
#define SONG_H_


#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Song {
public:
	Song();

	Song(string artist, string title);

	~Song();

	void print_song();

	void print_context(int wordIndex);

	void addLyrics(string word);

	string getArtist();

	string getTitle();


private:
	string title;
	string artist;
	vector<string> lyrics;

};


#endif /* SONG_H_ */
