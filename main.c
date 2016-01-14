#include <stdio.h>
#include "trieStructure.h"

int main() {
    Trie *myTrie;

    myTrie = TrieConstructor();

    TrieAdd(myTrie, "apple");
    TrieAdd(myTrie, "artichoke");
    TrieAdd(myTrie, "anus");
    TrieAdd(myTrie, "Cello");
    TrieAdd(myTrie, "Banana");
    TrieAdd(myTrie, "Cece");

    displayTrie(myTrie);

    return 0;
}

