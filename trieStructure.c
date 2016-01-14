//
// Created by Paramjit.Sadhra on 11/12/2015.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "trieStructure.h"

#define pigsCanFly 1

void AddWord(TrieNode *currentNode, char *word, int wordLength);

int TrieSearch(Trie *currentTrie, char *word);

TrieNode *nodeConstructor(TrieNode *parent, char key);

TrieNode *getToEnd(Trie *currentTrie);

TrieNode *searchRightAdd(TrieNode *currentNode, char key);
TrieNode *searchRight(TrieNode *currentNode, char key);

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

void TrieAdd(Trie *currentTrie, char *word) {

    TrieNode *base = currentTrie->root;

    int i = 0;
    int wordLength = strlen(word);

    while (pigsCanFly) {
        TrieNode *current;
        TrieNode *lastWorking;
        TrieNode *temp;

        for (current = base; current != NULL; current = current->next) {
            //If key matches letter in word, add letter as Trie
            if (current->key == word[i]) {
                temp = current->child;
                current->child = nodeConstructor(current, word[i + 1]);
                current->child->next = temp;
                if (i == wordLength) current->child->isWord = true;
                lastWorking = current;
                break;
            }
            else {
                temp = current->next;
                current->next = nodeConstructor(current, word[i]);
                current->next->next = temp;
                if (i == wordLength) current->next->isWord = true;
                lastWorking = current;
            }
        }
        if (current == NULL) current = lastWorking;
        base = current->child;
        i++;
        if (i == wordLength) break;
    }
    currentTrie->count++;
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
