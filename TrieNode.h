#include <bf/bloom_filter/basic.h>
#include <map>

using namespace std;
using namespace bf;
const int Son_size = 2;

class TrieNode
{
public:
    bool isEnd;
    TrieNode** son;
    int level;
    map<int, bloom_filter*> bfs;

    TrieNode(int level);
};
