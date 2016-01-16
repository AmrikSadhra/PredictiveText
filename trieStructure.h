//
// Created by Paramjit.Sadhra on 11/12/2015.
//

#pragma once

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
void TrieDestructor();

void TrieAdd(Trie *currentTrie, char *word);
int TrieSearch(Trie *currentTrie, char *word);
