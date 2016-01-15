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
void TrieAdd(TrieNode *base, Trie *currentTrie, char *word);
void TrieAddSimple(Trie *currentTrie, char *word);
void displayTrie(Trie *currentTrie);
void TrieFill(Trie *currentTrie);
