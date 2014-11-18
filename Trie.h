#include<string>

using std::string;

class Trie {
public:
	const TrieNode& getRoot() const;
	Trie();
	void insert(int str[], int depth, string pattern, int outport);
	int match(TrieNode node, string str[], string pattern);

private:
	TrieNode root;

};

