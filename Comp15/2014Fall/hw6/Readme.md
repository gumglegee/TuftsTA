Homework 6 - Song Search

Solution (Trie):
The lyrics file is huge, including 17,000 songs with a total of 40 million words. Thus, it is impossible to traverse the song list one by one, when searching for a given word. If we create a word list, it will be faster than loop though the song list.
We want the search time as little as possible. How about O(1)? Two possible data structures: Trie and Hash-table. 
For Hash-table, it will take some time to expand the table when reaching the load-factor; For Trie, when adding a new word, one or more nodes will be appending to the tree (max #nodes = length of the word).
In this assignment, I choose Trie.

After finding the matched word, we have to “rank the matching songs and present only the top10 best matching songs”. This time, I pick selection sort, because we only want the top10. The time complexity is O(10n), not O(n^2).

The time for reading the entire database is ~3m30s. ~5G memory are used.

The program contains 4 classes:
SearchEngine: The class handles all the tasks such as reading the lyrics and searching the word.
Song: This class represents a song object.
Trie: The word list.
Node: This class represents the node in the Trie. If the node is an end-word-node, it will contain a list of WordCountNodes stores word-freq information.

