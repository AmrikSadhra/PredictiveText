#include <stdio.h>
#include <string.h>
#include "trieStructure.h"

int main() {
    FILE *fp;
    Trie *myTrie;
    myTrie = TrieConstructor();
    char inWord[30];

   fp = fopen("/Users/amriksadhra/Google Drive/Development/C/Data Structures/PredictiveText/words.txt", "r");

    while (fgets(inWord, sizeof(inWord), fp)) {
        TrieAdd(myTrie, strtok(inWord, "\n"));
    }

    fclose(fp);

    int wordFound = TrieSearch(myTrie, "1st");

    if(wordFound == 1){
        printf("Word found!");
    }
    else{
        printf("Cant find.")
    }


    //displayTrie(myTrie);

    return 0;
}

