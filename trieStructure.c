//
// Created by Paramjit.Sadhra on 11/12/2015.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "trieStructure.h"

#define pigsCanFly 1

int TrieSearch(Trie *currentTrie, char *word);

TrieNode *nodeConstructor(TrieNode *parent, char key);

Trie *TrieConstructor() {
    Trie *myTrie;

    myTrie = malloc(sizeof(Trie));
    myTrie->root = nodeConstructor(NULL, 'a');
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

void TrieAddSimple(Trie *currentTrie, char *word) {
    TrieAdd(currentTrie->root, currentTrie, word);
}

void TrieAdd(TrieNode *base, Trie *currentTrie, char *word) {
    int wordLength = strlen(word) - 1;

    TrieNode *temp;

    static int i;

    bool letterFound = false;

    if (word[i] == '\0') return;

    if (word[i] != word[i - 1]) {
        for (TrieNode *current = base; current != NULL; current = current->next) {
            if (current->key == word[i]) {
                letterFound = true;
                i++;
                TrieAdd(current, currentTrie, word);
            }
        }
    }
    if (letterFound == false) {
        if(base->child == NULL){
            base->child = nodeConstructor(base, word[i]);

            if (i == wordLength) base->child->isWord = true;
            currentTrie->count++;
            i++;
            TrieAdd(base->child, currentTrie, word);
        }
        else{
            temp = base->child->next;
            base->child->next = nodeConstructor(base, word[i]);
            base->child->next->next = temp;

            if (i == wordLength) base->isWord = true;
            currentTrie->count++;
            i++;
            TrieAdd(base->child->next, currentTrie, word);
        }
    }
    i = 0;
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

void displayTrie(Trie *currentTrie) {
    TrieNode *base = currentTrie->root;

    while (pigsCanFly) {
        while (pigsCanFly) {
            TrieNode *current;
            TrieNode *lastWorking;

            for (current = base; current != NULL; current = current->next) {
                printf("-%c", current->key);
                lastWorking = current;
            }
            if (current == NULL) current = lastWorking;
            base = current->child;
            printf("|\n");
            if (base == NULL) break;
        }
        base = base->next;
    }
}
