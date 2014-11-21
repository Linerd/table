#include "TrieNode.h"

TrieNode::TrieNode(int level)
{
    memset(this,0,sizeof *this);
    this->level = level;
}
TrieNode::~TrieNode()
{
	for(int i=0;i<2;i++)
	{
		if(this->son[i]){
			delete this->son[i];
		}
	}
}
