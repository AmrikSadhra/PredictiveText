#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include "trieStructure.h"

//TODO: remove Magic numbers
//Move Textio into separate function
//Test, add asserts
//Make sure addWord is fully functional
int main() {
    Trie *myTrie;
    myTrie = TrieConstructor();

    fillTrie(myTrie, "C:\\Users\\amrik\\Development\\C\\PredictiveText\\words.txt");

    printf(".------------------- Predictive Text -------------------.\n");
    printf("| Type in a word and use the left and right arrow keys  |\n");
    printf("| to scroll through predictions. Press enter to select. |\n");
    printf("|                  and escape to quit.                  |\n");
    printf("|_______________________________________________________|\n");
    printf("\n\n                      Scratchpad:\n\n");

    int numPredictions = 0;
    int ch;
    char toPredict[20];
    int i = 0; //Counter through predictions
    int j = 0; //Counter through word to be predicted
    int k = 0; //For clearing buffers

    char **predictions;

    while ((ch = _getch()) != 27) {

        //If enter key pressed, newline and empty toPredict buffer
        if (ch == 13) {
            if (j != 0) {//Dont go to newline if no letters in buffer
                printf("\r                                                           ");
                printf("\r%s%s\n", toPredict, predictions[i]);
                for (k = 0; k <= j; k++) {
                    toPredict[k] = '\0';
                    j = 0;
                }
                i = 0;
            }
        }

        if (((ch >= 65) && (ch <= 122)) || ((ch >= 48) && (ch <= 57))) {
            if (j < 20) {//MaxWordLength
                toPredict[j] = (char) ch;
                j++;
                toPredict[j] = '\0';
                predictions = GetWords(myTrie, toPredict, &numPredictions);
                if (predictions == NULL) {
                    //If we cant find the word in the trie, return an empty prediction table
                    predictions = malloc(1 * sizeof(char *));
                    predictions[0] = malloc(20 * sizeof(char));
                    memset(predictions[0], '\0', 20);
                }
            }
            printf("\r                                                           ");
            printf("\r%s%s", toPredict, predictions[i]);
        }

        if (ch == 8) {
            if (j != 0) {//Dont backspace into uncharted territory
                i = 0;
                j--;
                toPredict[j] = '\0';
                predictions = GetWords(myTrie, toPredict, &numPredictions);
                if (predictions == NULL) {
                    //If we cant find the word in the trie, return an empty prediction table
                    predictions = malloc(1 * sizeof(char *));
                    predictions[0] = malloc(20 * sizeof(char));
                    memset(predictions[0], '\0', 20);
                }
                printf("\r                                                           ");
                printf("\r%s%s", toPredict, predictions[i]);
            }
        }

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

    printf("\n\n Press any key to exit.");
    getch();

    return 0;
}



