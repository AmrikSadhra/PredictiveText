#pragma once

#include <stdbool.h>

typedef struct TrieNode {
    char key;
    bool isWord;
    struct TrieNode *parent, *next, *child;
} TrieNode;

typedef struct Trie {
    int count;
    struct TrieNode *root;
} Trie;


Trie *TrieConstructor();

void TrieDestructor(Trie *toDestroy);

void TrieAdd(Trie *currentTrie, char *word);

int FillTrie(Trie *currentTrie, char *fileName);

TrieNode *TrieSearch(Trie *currentTrie, char *word);

char **GetWords(Trie *currentTrie, char *partial, int *numPredictions);

void ScratchPad(Trie *currentTrie);
