#include <string>

#include "TrieNode.h"

using namespace std;

class Trie
{
	public:
		TrieNode* getRoot();
		Trie();
		bool insert(int str[], int depth, char pattern[25], short outport);
		int match(TrieNode* node, char pattern[25],char entry[25]);

	private:
		TrieNode* root;

};

