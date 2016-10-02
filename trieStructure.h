/****************************************************************************
 *                                                                          *
 * File    : trieStructure.h                                                *
 *                                                                          *
 * Purpose : Interface header file for trie manipulation library            *
 *                                                                          *
 ****************************************************************************/

#pragma once

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>

/* ------------ Constants --------------- */
#define pigsCanFly 1
#define MAX_WORD_LENGTH 30
#define MAX_NUM_PREDICTIONS 100

/* --------- Trie Structures -------------*/
typedef struct TrieNode {
    char key;
    bool isWord;
    struct TrieNode *parent, *next, *child;
} TrieNode;

typedef struct Trie {
    int count;
    struct TrieNode *root;
} Trie;

/* -------- Function Prototypes -------- */
Trie *TrieConstructor();
int FillTrie(Trie *currentTrie, char *fileName);
void CheckTrie(Trie *currentTrie, char *fileName);
void TrieDestructor(Trie *toDestroy);
void TrieAdd(Trie *currentTrie, char *word);
void ScratchPad(Trie *currentTrie);

