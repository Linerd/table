#include "Trie.h"

#include <bf/bloom_filter/basic.h>
#include <bf/bloom_filter.h>
#include <cstdlib>
#include <iostream>
#include <map>
#include <utility>

using namespace std;
using namespace bf;

Trie::Trie() {
	this->root = new TrieNode(-1);
}

TrieNode* Trie::getRoot() {
	return this->root;
}

void Trie::insert(int str[], int depth, string pattern, int outport) {
	if (!str) {
		cout << "Str is empty, error!" << endl;
		exit(0);
	}

	TrieNode* node = root;
	for (int i = 0, len = depth; i < len; i++) {
		int pos = str[i];
		if (!node->son) {
			node->son = new TrieNode*[Son_size];
			node->son[pos] = new TrieNode(i);
		} else if (!node->son[pos]) {
			node->son[pos] = new TrieNode(i);
		}
		node = node->son[pos];
	}

	if (node->isEnd) {
		map<int, basic_bloom_filter>::iterator bf_it;
		bf_it = node->bfs.find(outport);
		if (bf_it != node->bfs.end()) {
			bf_it->second.add(pattern);
			return;
		} else {
			basic_bloom_filter* bf = new basic_bloom_filter(0.9, 1000);
			bf->add(pattern);
			node->bfs.insert(make_pair(outport, *bf));
			return;
		}
	} else {
		node->isEnd = true;
		basic_bloom_filter* bf = new basic_bloom_filter(0.9, 1000);
		bf->add(pattern);
		node->bfs.insert(make_pair(outport, *bf));
		return;
	}
}

int Trie::match(TrieNode* node, string str[], string* pattern) {
	if (!node) {
		return 0;
	}

	if (node->isEnd) {
		for (map<int, basic_bloom_filter>::iterator bf_it = node->bfs.begin();
				bf_it != node->bfs.end(); bf_it++) {
			if (bf_it->second.lookup(pattern)) {
				return bf_it->first;
			}
		}
	}
	if (!node->son) {
		return 0;
	}

	else {
		int result1;
		return (result1 = match(node->son[0], str,
				&(*pattern + str[node->level + 1]))) > 0 ?
				result1 : match(node->son[1], str, pattern);
	}
}

