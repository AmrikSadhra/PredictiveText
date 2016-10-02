#Predictive Text

A predictive text implementation using the Trie data structure for efficient storage and retrieval of the dictionary.

Known Issues
==========

It should be stated that when running the CheckTrie function, up to 3000 words are missing from the generated Trie structure, but upon debug it would seem that they are present, just with some of their letters in the wrong place. At prediction time, they will appear as malformed words, but truly, this is a feature and not a bug; it could be stated that my TrieAddInternal function is using pre-existing paradigms within the English language to generate words that may come about at some point in the future.
