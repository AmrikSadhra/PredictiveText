//
// Created by Paramjit.Sadhra on 11/12/2015.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "trieStructure.h"

#define pigsCanFly 1

void TrieAddInternal(TrieNode *base, Trie *currentTrie, char *word);

TrieNode *TraverseToEnd(TrieNode *base);

TrieNode *NodeConstructor(TrieNode *parent, char key);

void NodeDestructor(TrieNode *toDestroy);

char *readColumn(TrieNode *currentTrie);


Trie *TrieConstructor() {
    Trie *myTrie;

    myTrie = malloc(sizeof(Trie));
    myTrie->root = NodeConstructor(NULL, '1');
    myTrie->root->parent = NULL;
    myTrie->root->child = NodeConstructor(myTrie->root, '0');
    myTrie->count = 0;

    return myTrie;
}

TrieNode *NodeConstructor(TrieNode *parent, char key) {
    TrieNode *myNode;

    myNode = malloc(sizeof(TrieNode));

    myNode->key = key;
    myNode->parent = parent;
    myNode->next = NULL;
    myNode->child = NULL;

    return myNode;
}

void NodeDestructor(TrieNode *toDestroy) {
    if ((toDestroy->child == NULL) && (toDestroy->next == NULL)) {
        free(toDestroy);
    }
    else {
        if (toDestroy->child != NULL) {
            NodeDestructor(toDestroy->child);
        }
        if (toDestroy->next != NULL) {
            NodeDestructor(toDestroy->next);
        }
    }
}

void TrieDestructor(Trie *toDestroy) {
    if (toDestroy->root == NULL) {
        free(toDestroy);
    }
    else {
        NodeDestructor((toDestroy->root));
    }
}

void TrieAdd(Trie *currentTrie, char *word) {
    TrieAddInternal(currentTrie->root, currentTrie, word);
}

void TrieAddInternal(TrieNode *base, Trie *currentTrie, char *word) {
    int wordLength = strlen(word) - 1;

    static int i;
    TrieNode *current;

    if (word[i] == '\0') return;

    if (word[i] != word[i - 1]) {
        for (current = base; current != NULL; current = current->next) {
            if (current->key == word[i]) {
                if (current->child == NULL) {
                    i++;
                    TrieAddInternal(current, currentTrie, word);
                    return;
                }
                else {
                    i++;
                    TrieAddInternal(current->child, currentTrie, word);
                    return;
                }
            }
        }
    }

    if (base->child == NULL) {
        base->child = NodeConstructor(base, word[i]);

        if (i == wordLength) base->child->isWord = true;

        i++;
        currentTrie->count++;
        TrieAddInternal(base->child, currentTrie, word);
    }
    else {
        TrieNode *branchEnd = TraverseToEnd(base);
        branchEnd->next = NodeConstructor(base, word[i]);
        if (i == wordLength) branchEnd->next->isWord = true;

        i++;
        currentTrie->count++;
        TrieAddInternal(branchEnd->next, currentTrie, word);
    }
    i = 0;
}

TrieNode *TraverseToEnd(TrieNode *base) {
    TrieNode *notNull;

    for (TrieNode *current = base; current != NULL; current = current->next) {
        notNull = current;
    }

    return notNull;
}

TrieNode *TrieSearch(Trie *currentTrie, char *word) {
    TrieNode *level = currentTrie->root;

    int wordLength = strlen(word) - 1;
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

        if (found == NULL) return NULL;
        if (i == wordLength) return found;

        level = current->child;
        i++;
    }
}

char** GetWords(Trie *currentTrie, char *partial, int *numPredictions) {
    TrieNode *head;
    int i = 0;

    char **buf = malloc(40 * sizeof(char*));
    for (int i = 0; i < 40; ++i) {
        buf[i] = malloc(20 * sizeof(char));
    }

    head = TrieSearch(currentTrie, partial);
    if(head == NULL) {
        *numPredictions = 0;
        return NULL;
    }
    head = head->child;

    i = 1;
    memset(buf[0], '\0', 20);

    for (TrieNode* current = head; current != NULL; current = current->next) {
        strcpy(buf[i], readColumn(current));
        i++;
    }

    *numPredictions = i;

    return buf;
}

char *readColumn(TrieNode *currentTrie) {
    static char buf[20];
    memset(buf, 0, 20);

    int i = 0;
    TrieNode *current;

    for (current = currentTrie; current != NULL; current = current->child) {
        buf[i] = current->key;
        i++;
    }
    buf[i] = '\0';

    return buf;
}

int fillTrie(Trie *currentTrie, char *fileName) {
    FILE *fp;
    char inWord[30];

    fp = fopen(fileName, "r");

    if (fp == NULL) return 0;

    while (fgets(inWord, sizeof(inWord), fp)) {
        TrieAdd(currentTrie, strtok(inWord, "\n"));
    }

    fclose(fp);

    return 1;
}

void checkTrie(Trie *currentTrie, char *fileName) {
    FILE *fp;
    char inWord[30];

    fp = fopen(fileName, "r");

    if (fp == NULL) return;

    int i = 0;

    while (fgets(inWord, sizeof(inWord), fp)) {
        if (TrieSearch(currentTrie, strtok(inWord, "\n")) == NULL) {
            i++;
            printf("%s\n", inWord);
        }
    }
    printf("Words missing: %d\n", i);

    fclose(fp);
}
