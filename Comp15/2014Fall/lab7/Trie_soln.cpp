//
//  Trie.cpp
//  trie
//
//  Created by Chris Gregg on 3/29/14.
//  Copyright (c) 2014 Chris Gregg. All rights reserved.
//

#include "Trie.h"

Trie::Trie()
{
        root = new Node();
}

Trie::~Trie()
{
        // Free memory
}

void Trie::addWord(string s)
{
        Node* tmp = root;
        
        for ( size_t i = 0; i < s.length(); i++ )
        {
                Node* child = tmp->findChild(s[i]);
                if ( child != NULL )
                {
                        tmp = child;
                }
                else
                {
                        Node* childNode = new Node();
                        childNode->setCharacter(s[i]);
                        tmp->appendChild(childNode);
                        tmp = childNode;
                }
                if ( i == s.length() - 1 )
                        tmp->setWordMarker();
        }
}


bool Trie::searchWord(string s)
{
        Node* tmp = root;
        
        while ( tmp != NULL )
        {
                for ( size_t i = 0; i < s.length(); i++ )
                {
                        Node* child = tmp->findChild(s[i]);
                        if ( child == NULL )
                                return false;
                        tmp = child;
                }
                
                if ( tmp->getWordMarker() )
                        return true;
                else
                        return false;
        }
        
        return false;
}

void Trie::printTrie(){
        root->printNode(0);
}

void Trie::addPreNodes(vector<preNode> preNodes) {
	root->addPreNodes(preNodes,0,1);
}
