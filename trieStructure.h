//
// Created by Paramjit.Sadhra on 11/12/2015.
//

#ifndef PREDICTIVETEXT_TRIESTRUCTURE_H
#define PREDICTIVETEXT_TRIESTRUCTURE_H

#include <stdbool.h>

typedef struct TrieNode{
    char key;
    bool isWord;
    struct TrieNode *parent, *next, *child;
} TrieNode;

typedef struct Trie{
    int count;
   struct  TrieNode *root;
} Trie;


Trie *TrieConstructor();
void TrieAdd(Trie *currentTrie, char *word);
void displayTrie(Trie *currentTrie);
void TrieFill(Trie *currentTrie);

#endif //PREDICTIVETEXT_TRIESTRUCTURE_H
