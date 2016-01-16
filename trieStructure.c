//
// Created by Paramjit.Sadhra on 11/12/2015.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "trieStructure.h"

#define pigsCanFly 1

void TrieAddInternal(TrieNode *base, Trie *currentTrie, char *word);
int TrieSearch(Trie *currentTrie, char *word);
TrieNode *traverseToEnd(TrieNode *base);
TrieNode *nodeConstructor(TrieNode *parent, char key);

Trie *TrieConstructor() {
    Trie *myTrie;

    myTrie = malloc(sizeof(Trie));
    myTrie->root = nodeConstructor(NULL, '1');
    myTrie->root->parent = nodeConstructor(NULL, '-');
    myTrie->count = 0;

    return myTrie;
}

TrieNode *nodeConstructor(TrieNode *parent, char key) {
    TrieNode *myNode;

    myNode = malloc(sizeof(TrieNode));

    myNode->key = key;
    myNode->parent = parent;
    myNode->next = NULL;
    myNode->child = NULL;

    return myNode;
}

void TrieAdd(Trie *currentTrie, char *word) {
    TrieAddInternal(currentTrie->root, currentTrie, word);
}

void TrieAddInternal(TrieNode *base, Trie *currentTrie, char *word) {
    int wordLength = strlen(word) - 1;

    TrieNode *temp;

    static int i;

    if (i == wordLength + 1) return;

    //If letter is not repeated, inititiate search for letter. If repeated, assume not present and add as usual
    if (word[i] != word[i - 1]) {
        for (TrieNode *current = base; current != NULL; current = current->next) {
            if (current->key == word[i]) {
                i++;
                if (current->child == NULL) {
                    TrieAddInternal(current, currentTrie, word);
                    return;
                }
                else {
                    TrieAddInternal(current->child, currentTrie, word);
                    return;
                }
            }
        }
    }
    if (base->child == NULL) {
        base->child = nodeConstructor(base, word[i]);

        if (i == wordLength) base->child->isWord = true;
        currentTrie->count++;
        i++;
        TrieAddInternal(base->child, currentTrie, word);
    }
    else {
        TrieNode *branchEnd = traverseToEnd(base);
        branchEnd->next = nodeConstructor(base, word[i]);

        if (i == wordLength) branchEnd->next->isWord = true;
        currentTrie->count++;
        i++;
        TrieAddInternal(branchEnd->next, currentTrie, word);
    }
    i = 0;
}

TrieNode *traverseToEnd(TrieNode *base){
    TrieNode *notNull;

    for (TrieNode *current = base; current != NULL; current = current->next) {
        notNull = current;
    }

    return notNull;
}

int TrieSearch(Trie *currentTrie, char *word) {
    TrieNode *level = currentTrie->root;

    int i = 0;

    while (pigsCanFly) {
        TrieNode *current;
        TrieNode *found = NULL;

        for (current = level; current != NULL; current = current->next) {
            if (current->key == word[i]) {
                found = current;
                break;
            }
        }

        if (found == NULL) return 0;
        if (word[i] == '\0') return 1;

        level = current->child;
        i++;
    }

}
