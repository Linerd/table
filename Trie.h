#include <string>

#include "TrieNode.h"

using namespace std;

class Trie {
public:
	TrieNode* getRoot();
	Trie();
	void insert(int str[], int depth, string pattern, int outport);
	int match(TrieNode* node, string str[], string* pattern);

private:
	TrieNode* root;

};

