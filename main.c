#include <stdio.h>
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

    if(FillTrie(myTrie, "C:\\Users\\amrik\\Development\\C\\PredictiveText\\words.txt") != 1){
        printf("Word list not found.");
        exit(1);
    };

    ScratchPad(myTrie);

    TrieDestructor(myTrie);

    printf("\n\n Press any key to exit.");
    getch();

    return 0;
}



