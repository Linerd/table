#include "Trie.h"

#include <cstdlib>
#include <iostream>
#include <map>

#include "TrieNode.h"

using std::cout;
using std::endl;

Trie::Trie() {
	this->root = new TrieNode(-1);
}

const TrieNode& Trie::getRoot() const {
	return this->root;
}

void Trie::insert(int str[], int depth, string pattern, int outport) {
	if (!str) {
		cout << "Str is empty, error!" << endl;
		exit(0);
	}

	TrieNode node = root;
	for (int i = 0, len = depth; i < len; i++) {
		int pos = str[i];
		if (!node.son) {
			node.son = new TrieNode[Son_size];
			node.son[pos] = new TrieNode(i);
		} else if (!node.son[pos]) {
			node.son[pos] = new TrieNode(i);
		}
		node = node.son[pos];
	}

	if (node.isEnd) {
		map<int,bf::basic_bloom_filter>::iterator bf_it;
		if (bf_it!=bfs.end()) {
			bf_it.second.add(pattern);
			return;
		}
		else{
			bf::basic_bloom_filter bf = new bf::
		}
	}
}
