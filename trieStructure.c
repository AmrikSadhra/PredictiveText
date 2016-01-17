//
// Created by Paramjit.Sadhra on 11/12/2015.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#include "trieStructure.h"

#define pigsCanFly 1
#define MAX_WORD_LENGTH 20
#define MAX_NUM_PREDICTIONS 40

/* Internal function prototypes */
void TrieAddInternal(TrieNode *base, Trie *currentTrie, char *word);
TrieNode *TraverseToEnd(TrieNode *base);
TrieNode *NodeConstructor(TrieNode *parent, char key);
void NodeDestructor(TrieNode *toDestroy);
char *ReadColumn(TrieNode *currentTrie);

/*---------------------------------------------- TrieConstructor -----
|  Function TrieConstructor
|
|  Purpose:  Allocates memory for a trie structure using malloc
|            The root node of the trie is created by calling NodeConstructor
|            with a key value of 1. A child is also added to root to avoid
|            issues with the algorithm used to add nodes.
|
|  Parameters: void
|
|  Returns:  Pointer to constructed Trie
*-------------------------------------------------------------------*/
Trie *TrieConstructor(void) {
    Trie *myTrie;

    myTrie = malloc(sizeof(Trie));
    myTrie->root = NodeConstructor(NULL, '1');
    myTrie->root->parent = NULL;
    myTrie->root->child = NodeConstructor(myTrie->root, '0');
    myTrie->count = 0;

    return myTrie;
}

/*------------------------------------------------- NodeConstructor -----
|  Function NodeConstructor
|
|  Purpose:  Allocates memory for a node structure using malloc
|            The key property of the structure is set equal to the
|            key parameter, and the parent of the node is set to the
|            parent parameter
|
|  Parameters:
|      TrieNode *parent -- The parent node of the node being created
|      char key         -- The letter to be stored within the constructed
|                          node
|
|  Returns:  Pointer to constructed node
*-------------------------------------------------------------------*/
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
    /* If child and sibling are null, it is safe to free the current node */
    if ((toDestroy->child == NULL) && (toDestroy->next == NULL)) {
        free(toDestroy);
    }
    /* If either child or sibling not freem call the destructor appropriately */
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
    /* If the root node has been destroyed by NodeDestructor, it is safe to free the Trie */
    if (toDestroy->root == NULL) {
        free(toDestroy);
    }
    /* Call the node destructor on the root */
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

    /* If at the end of the word, return */
    if (word[i] == '\0') return;

    /* If the letter is not repeated, perform a search along the branch
     * for a node with a key value matching our position in the word.
     * If it is repeated, skip the search and add letter as child */
    if (word[i] != word[i - 1]) {
        for (current = base; current != NULL; current = current->next) {
            /* If found key matching word letter, check if it has a child
             * If it doesnt, recurse the function using the current node as the base.
             * If it does, recurse the function using the current nodes child as the base */
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
    /* If the node has no children, construct a node of current position in word
     * as its child. Then recurse the function with the base->child as the base. */
    if (base->child == NULL) {
        base->child = NodeConstructor(base, word[i]);

        if (i == wordLength) base->child->isWord = true;

        i++;
        currentTrie->count++;
        TrieAddInternal(base->child, currentTrie, word);
    }
    /* If the node has children, move to the end of the branch, and add node of current position in word
     * as the sibling. Then recurse the function with the branch end->next as the base */
    else {
        TrieNode *branchEnd = TraverseToEnd(base);
        branchEnd->next = NodeConstructor(base, word[i]);
        if (i == wordLength) branchEnd->next->isWord = true;

        i++;
        currentTrie->count++;
        TrieAddInternal(branchEnd->next, currentTrie, word);
    }
    /* Reset static position in word counter for next word */
    i = 0;
}

TrieNode *TraverseToEnd(TrieNode *base) {
    TrieNode *notNull;

    /* Traverse nodes siblings until current->next == NULL. Return last non null node */
    for (TrieNode *current = base; current != NULL; current = current->next) {
        notNull = current;
    }

    return notNull;
}

TrieNode *TrieSearch(Trie *currentTrie, char *word) {
    TrieNode *level = currentTrie->root;

    int wordLength = strlen(word) - 1;
    int i = 0;

    /* Traverse nodes sideways until letter in word is found, when found, set level to child of node
     * and repeat traversal until wordlength reached. If node is null, not found, else pointer to found returned */
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

char **GetWords(Trie *currentTrie, char *partial, int *numPredictions) {
    TrieNode *head;
    int i = 0;

    char **buf = malloc(MAX_NUM_PREDICTIONS * sizeof(char *));
    for (i = 0; i < MAX_NUM_PREDICTIONS; ++i) {
        buf[i] = malloc(MAX_WORD_LENGTH * sizeof(char));
    }

    head = TrieSearch(currentTrie, partial);
    if (head == NULL) {
        *numPredictions = 0;
        return NULL;
    }
    head = head->child;

    i = 1;
    memset(buf[0], '\0', MAX_WORD_LENGTH);

    for (TrieNode *current = head; current != NULL; current = current->next) {
        strcpy(buf[i], ReadColumn(current));
        i++;
    }

    *numPredictions = i;

    return buf;
}

char *ReadColumn(TrieNode *currentTrie) {
    static char buf[MAX_WORD_LENGTH];
    memset(buf, 0, MAX_WORD_LENGTH);

    int i = 0;

    TrieNode *current;

    for (current = currentTrie; current != NULL; current = current->child) {
        buf[i] = current->key;
        i++;
    }
    buf[i] = '\0';

    return buf;
}

int FillTrie(Trie *currentTrie, char *fileName) {
    FILE *fp;
    char inWord[MAX_WORD_LENGTH];

    fp = fopen(fileName, "r");

    if (fp == NULL) return 0;

    while (fgets(inWord, sizeof(inWord), fp)) {
        TrieAdd(currentTrie, strtok(inWord, "\n"));
    }

    fclose(fp);

    return 1;
}

void CheckTrie(Trie *currentTrie, char *fileName) {
    FILE *fp;
    char inWord[MAX_WORD_LENGTH];

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

void ScratchPad(Trie *currentTrie) {
    printf(".------------------- Predictive Text -------------------.\n");
    printf("| Type in a word and use the left and right arrow keys  |\n");
    printf("| to scroll through predictions. Press enter to select. |\n");
    printf("|                  and escape to quit.                  |\n");
    printf("|_______________________________________________________|\n");
    printf("\n\n                      Scratchpad:\n\n");

    int numPredictions = 0;
    int ch;
    char toPredict[MAX_WORD_LENGTH];
    int i = 0; //Counter through predictions
    int j = 0; //Counter through word to be predicted
    int k = 0; //For clearing buffers

    char **predictions;

    /* While input character is not equal to ESCAPE */
    while ((ch = _getch()) != 27) {

        /* If enter key pressed and not in 0th position in word buffer, newline and empty toPredict buffer
         * Prediction counter set to 0 so as to show blank prediction */
        if (ch == 13) {
            /* Dont go to newline if no letters in buffer */
            if (j != 0) {
                printf("\r                                                           ");
                printf("\r%s%s\n", toPredict, predictions[i]);
                for (k = 0; k <= j; k++) {
                    toPredict[k] = '\0';
                    j = 0;
                }
                i = 0;
            }
        }

        /* If alphanumeric key pressed, and we dont have MAX_WORD_LENGTH chars in buffer, set toPredict[j]
         * equal to inputted key, increment j and append string terminating char to buffer. Then retrieve
         * 2D string array of predictions from GetWords function. If its NULL, then fill the array with terminating chars
         * So no predictions. Then print inputted word + prediction at i */
        if (((ch >= 65) && (ch <= 122)) || ((ch >= 48) && (ch <= 57))) {
            if (j < MAX_WORD_LENGTH) {
                toPredict[j] = (char) ch;
                j++;
                toPredict[j] = '\0';
                predictions = GetWords(currentTrie, toPredict, &numPredictions);
                if (predictions == NULL) {
                    //If we cant find the word in the trie, return an empty prediction table
                    predictions = malloc(1 * sizeof(char *));
                    predictions[0] = malloc(MAX_WORD_LENGTH * sizeof(char));
                    memset(predictions[0], '\0', MAX_WORD_LENGTH);
                }
            }
            printf("\r                                                           ");
            printf("\r%s%s", toPredict, predictions[i]);
        }

        /* If backspace pressed and not at 0th position in buffer, set i to 0 so that prediction is blank, decrement
         * input word counter and append terminating char. Get predictions for new shortened word. */
        if (ch == 8) {
            if (j != 0) {//Dont backspace into uncharted territory
                i = 0;
                j--;
                toPredict[j] = '\0';
                predictions = GetWords(currentTrie, toPredict, &numPredictions);
                if (predictions == NULL) {
                    //If we cant find the word in the trie, return an empty prediction table
                    predictions = malloc(1 * sizeof(char *));
                    predictions[0] = malloc(MAX_WORD_LENGTH * sizeof(char));
                    memset(predictions[0], '\0', MAX_WORD_LENGTH);
                }
                printf("\r                                                           ");
                printf("\r%s%s", toPredict, predictions[i]);
            }
        }

        /* If arrow key pressed, repeat a getch to grab arrow key. If right arrow pressed,
         * and not at limit of number of predictions, increment prediction counter i
         * so that a new prediction will appear (prediction[i+1]). If left arrow pressed, and not at 0th prediction,
         * decrement prediction counter i (prediction[i-1]). Then print inputted word and prediction at new location */
        if (ch == 0 || ch == 224) {
            ch = _getch();
            if (j != 0) {
                if (ch == 77) {//Right arrow
                    if (i < numPredictions - 1) i++;

                }
                if (ch == 75) {//Left arrow
                    if (i != 0) i--;
                }
                printf("\r                                                           ");
                printf("\r%s%s", toPredict, predictions[i]);
            }
        }
    }
}