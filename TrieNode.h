#include<bf.h>
#include<map>

const int Son_size = 2;

class TrieNode {
public:
	bool isEnd;
	TrieNode* son[];
	int level;
	std::map<int, bf::basic_bloom_filter> bfs;

	TrieNode(int level);
};
