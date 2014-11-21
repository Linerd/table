#include <bf.h>
#include <map>
#include <cstring>

using namespace std;
using namespace bf;

struct TrieNode
{
	bool isEnd;
	TrieNode* son[2];
	int level;
	map<short, bloom_filter*>* bfs;

	TrieNode(int level);
	~TrieNode();
};
