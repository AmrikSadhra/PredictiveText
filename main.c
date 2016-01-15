#include <stdio.h>
#include "trieStructure.h"

int main() {
    Trie *myTrie;

    myTrie = TrieConstructor();

    TrieAddSimple(myTrie, "apple");
    TrieAddSimple(myTrie, "artichoke");
    TrieAddSimple(myTrie, "anus");
    TrieAddSimple(myTrie, "Cello");
    TrieAddSimple(myTrie, "Banana");
    TrieAddSimple(myTrie, "Cece");

    displayTrie(myTrie);

    return 0;
}

