#include "trieStructure.h"

/* Internal function prototypes */
void TrieAddInternal(TrieNode *base, Trie *currentTrie, char *word);
TrieNode *TraverseToEnd(TrieNode *base);
TrieNode *NodeConstructor(TrieNode *parent, char key);
void NodeDestructor(TrieNode *toDestroy);
char *ReadColumn(TrieNode *base, bool readPast, int *isWord);

/*--------------------------------------------------------------------
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

/*--------------------------------------------------------------------
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

/*--------------------------------------------------------------------
|  Function NodeDestructor
|
|  Purpose:  Recursively frees all child and sibling nodes, then frees
|            itself
|  Parameters:
|      TrieNode *toDestroy -- Node to free
|
|  Returns:  void
*-------------------------------------------------------------------*/
void NodeDestructor(TrieNode *toDestroy) {
    /* If child and sibling are null, it is safe to free the current node */
    if ((toDestroy->child == NULL) && (toDestroy->next == NULL)) {
        free(toDestroy);
    }
    /* If either child or sibling not freem call the destructor appropriately */
    else {
        if (toDestroy->next != NULL) {
            NodeDestructor(toDestroy->next);
        }
        if (toDestroy->child != NULL) {
            NodeDestructor(toDestroy->child);
        }
    }
}

/*--------------------------------------------------------------------
|  Function TrieDestructor
|
|  Purpose:  Calls the NodeDestructor on the root node until it is null.
|            then free's the Trie
|  Parameters:
|      TrieNode *toDestroy -- Trie to free
|
|  Returns:  void
*-------------------------------------------------------------------*/
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

/*--------------------------------------------------------------------
|  Function TrieAdd
|
|  Purpose:  A wrapper for the TrieAddInternal function, to abstract the user
|            away from the root node of the Trie.
|
|  Parameters:
|      TrieNode *currentTrie -- Trie to add word to
|      char *word            -- Word to add to Trie
|
|  Returns:  void
*-------------------------------------------------------------------*/
void TrieAdd(Trie *currentTrie, char *word) {
    TrieAddInternal(currentTrie->root, currentTrie, word);
}

/*--------------------------------------------------------------------
|  Function TrieAddInternal
|
|  Purpose:  Recursive function to add word to Trie, calling itself
|            with new TrieNodes in order to add entirett of word
|
|  Parameters:
|      TrieNode *currentTrie -- Trie to add word to
|      char *word            -- Word to add to Trie
|      TrieNode *base        -- Node in which to add word[i] letter to
|
|  Returns:  void
*-------------------------------------------------------------------*/
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

/*--------------------------------------------------------------------
|  Function TraverseToEnd
|
|  Purpose:  Traverses input TrieNodes siblings until it reaches NULL
|
|  Parameters:
|      TrieNode *base        -- Node from which to start traversal from
|
|  Returns:  Node at far end of siblings of *base
*-------------------------------------------------------------------*/
TrieNode *TraverseToEnd(TrieNode *base) {
    TrieNode *notNull;

    /* Traverse nodes siblings until current->next == NULL. Return last non null node */
    for (TrieNode *current = base; current != NULL; current = current->next) {
        notNull = current;
    }

    return notNull;
}

/*--------------------------------------------------------------------
|  Function TrieSearch
|
|  Purpose: Searches the input Trie for a string, returning the location
|           of the words tail
|  Parameters:
|      TrieNode *currentTrie -- Trie to search for word in
|      char *word            -- Word to search for in Trie
|
|  Returns:  TrieNode pointer corresponding to node containing last letter in word
*-------------------------------------------------------------------*/
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

/*--------------------------------------------------------------------
|  Function GetWords
|
|  Purpose: Returns a list of predictions based upon the partial word
|           entered into function
|  Parameters:
|      TrieNode *currentTrie -- Trie to search for predictions in
|      char *word            -- Partial word to get predictions for
|      int *numPredictions   -- Allows the function to return the 2D array
|                               as well as the number of predictions
|
|  Returns:  2D array of strings containing predictions for partial word in Trie
*-------------------------------------------------------------------*/
char **GetWords(Trie *currentTrie, char *partial, int *numPredictions) {
    TrieNode *head;
    int i = 0;
    int isWord = 0;
    bool readPast = false;

    /* Allocate memory for 2D array */
    char **buf = malloc(MAX_NUM_PREDICTIONS * sizeof(char *));
    for (i = 0; i < MAX_NUM_PREDICTIONS; ++i) {
        buf[i] = malloc(MAX_WORD_LENGTH * sizeof(char));
    }

    /* Search for partial part of word */
    head = TrieSearch(currentTrie, partial);
    if (head == NULL) {
        /* If cant be found, set num predictions to zero and return NULL */
        *numPredictions = 0;
        return NULL;
    }
    head = head->child;

    /* The first entry in predictions should be a blank line. Set line 0 to terminating chars and start from i = 1 */
    i = 1;
    memset(buf[0], '\0', MAX_WORD_LENGTH);

    /* Read columns down each neighbouring node, into 2D preidctions array */
    for (TrieNode *current = head; current != NULL; current = current->next) {
        ISWORD:
        strcpy(buf[i], ReadColumn(current, readPast, &isWord));
        if(isWord == 1){
            isWord = 0;
            i++;
            readPast = true;
            goto ISWORD;
        }else{
            readPast = false;
        }
        i++;
    }

    *numPredictions = i;

    return buf;
}

/*--------------------------------------------------------------------
|  Function ReadColumn
|
|  Purpose: Traverse every child from base node and append their keys
|           to a buffer, reads a column of letters.
|
|  Parameters:
|      TrieNode *currentTrie -- Trie to search for word in
|      char *word            -- Word to search for in Trie
|
|  Returns: String of all keys concatenated from base node downwards
*-------------------------------------------------------------------*/
char *ReadColumn(TrieNode *base, bool readPast, int *isWord) {
    static char buf[MAX_WORD_LENGTH];
    memset(buf, 0, MAX_WORD_LENGTH);

    int i = 0;

    TrieNode *current;

    /* Traverse nodes downwards, appending the key value of each to a buffer, with the buffer returned */
    for (current = base; current != NULL; current = current->child) {
        buf[i] = current->key;
        i++;
        if((current->isWord == true)&&(readPast == false)){
            *isWord = 1;
            break;
        }
    }
    buf[i] = '\0';

    return buf;
}

/*--------------------------------------------------------------------
|  Function FillTrie
|
|  Purpose: Fills the trie with a wordlist contained within the file
|           specified by fileName
|  Parameters:
|      TrieNode *currentTrie -- Trie to fill with words
|      char *fileName        -- Filename of file containing words to add to trie
|
|  Returns:  Number corresponding to success of opening file handle (0 = fail, 1 = success)
*-------------------------------------------------------------------*/
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

/*--------------------------------------------------------------------
|  Function CheckTrie
|
|  Purpose: Checks generated Trie for all words contained in fileName.
|           Prints missing words and increments a counter for every missing word.
|  Parameters:
|      TrieNode *currentTrie -- Trie to check for presence of words in
|      char *fileName        -- Filename of file containing words check for
|
|  Returns:  void
*-------------------------------------------------------------------*/
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

/*--------------------------------------------------------------------
|  Function ScratchPad
|
|  Purpose: Allows user to test predictive text capabilities on Trie
|           Dynamically updates prediction list and allows easy entry and
|           scroll through of data. Asks user if they wish to save their
|           predicted words.
|  Parameters:
|      TrieNode *currentTrie -- Trie to read for predicted words
|
|  Returns:  void
*-------------------------------------------------------------------*/
void ScratchPad(Trie *currentTrie) {
    printf(".------------------- Predictive Text -------------------.\n");
    printf("| Type in a word and use the left and right arrow keys  |\n");
    printf("| to scroll through predictions. Press enter to select. |\n");
    printf("|                  and escape to quit.                  |\n");
    printf("|_______________________________________________________|\n");
    printf("\n\n                      Scratchpad:\n\n");

    FILE *fp;
    fp = fopen("Predictions.txt", "w");
    fprintf(fp, "Predictions:\n");

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
                fprintf(fp, "\r                                                           ");
                fprintf(fp, "\r%s%s\n", toPredict, predictions[i]);
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
                i = 0;
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
            fprintf(fp, "\r                                                           ");
            fprintf(fp, "\r%s%s", toPredict, predictions[i]);
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
                fprintf(fp, "\r                                                           ");
                fprintf(fp, "\r%s%s", toPredict, predictions[i]);
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
                fprintf(fp, "\r                                                           ");
                fprintf(fp, "\r%s%s", toPredict, predictions[i]);
            }
        }
    }

    printf("\nDo you wish to save? Y/N    \n");
    ch = _getch();

    if((ch == 'y')||(ch == 'Y')){
        fclose(fp);
        printf("Saved to Predictions.txt. Press any key to exit.\n");
        _getch();
    }
    if((ch == 'n')||(ch = 'N')){
        fclose(fp);
        remove("Prediction.txt"); //Clean up
    }


}