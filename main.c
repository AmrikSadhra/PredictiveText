#include <stdio.h>
#include <stdlib.h>
#include "trieStructure.h"

int main() {
    Trie *myTrie;
    myTrie = TrieConstructor();

    //WORD LIST MUST BE INSIDE SAME FOLDER AS EXECUTABLE
    if(FillTrie(myTrie, "words.txt") != 1){
        printf("Word list not found.");
        exit(1);
    };

    ScratchPad(myTrie);

    TrieDestructor(myTrie);

    return 0;
}



