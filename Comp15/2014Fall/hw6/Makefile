#
# Makefile for List_linked_list
#
CXX = clang++
FLAGS =  -g -Wall 
   
cards_linked_list: Node.cpp Node.h Trie.cpp Trie.h Song.cpp Song.h \
	SearchEngine.cpp SearchEngine.h main.cpp
	${CXX} ${FLAGS} -o songsearch Node.cpp main.cpp \
	        Trie.cpp Song.cpp SearchEngine.cpp
clean:
	rm -f hw6

make provide:
	provide comp15 hw6 main.cpp Node.cpp Node.h Trie.cpp Trie.h \
		Song.cpp Song.h SearchEngine.cpp SearchEngine.h \
		Makefile
