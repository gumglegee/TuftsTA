#
# Makefile for Trie lab
#
CXX = clang++
FLAGS = -O0 -g3 -Wall

trie: main.cpp Node.cpp Node.h Trie.cpp Trie.h cgiBackend.cpp cgiBackend.h runTrie.pl
	${CXX} ${FLAGS} -o trie main.cpp Node.cpp Trie.cpp cgiBackend.cpp
	chmod a+rx trie
clean:
	rm -f trie
	
provide:
	provide comp15 lab7 main.cpp Node.cpp Node.h Trie.cpp Trie.h \
	  Makefile cgiBackend.h cgiBackend.cpp
