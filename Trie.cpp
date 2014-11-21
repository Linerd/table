#include "Trie.h"
#include <bf.h>
#include <cstdlib>
#include <iostream>
#include <map>
#include <utility>

using namespace std;
using namespace bf;

Trie::Trie()
{
	this->root = new TrieNode(-1);
}

TrieNode* Trie::getRoot()
{
	return this->root;
}

bool Trie::insert(int str[6], int depth, char pattern[25], short outport)
{
	if (!str)
	{
		cout << "Str is empty, error!" << endl;
		cin.get();
		exit(0);
	}

	TrieNode* node = root;
	for (int i = 0, len = depth; i <=len; i++)
	{
		int pos = str[i];
		if (!node->son[pos])
		{
			node->son[pos] = new TrieNode(i);
		}
		node = node->son[pos];
		//cout<<"level "<<i<<" pos "<<pos<<" pt: "<<node;
		//cout<<" passed level:"<<i<<" pos="<<str[i]<<endl;
	}

	if (node->isEnd)
	{
		map<short, bloom_filter*>::iterator bf_it;
		bf_it = node->bfs->find(outport);
		if (bf_it != node->bfs->end())
		{
			bf_it->second->add(pattern);
			//cout<<pattern<<endl;
			return true;
		}
		else
		{
			bloom_filter* bf = new basic_bloom_filter(0.9, 1000);
			bf->add(pattern);
			node->bfs->insert(make_pair(outport, bf));
			//cout<<pattern<<endl;
			return true;
		}
	}
	else
	{
		node->isEnd = true;
		bloom_filter* bf = new basic_bloom_filter(0.9, 1000);
		bf->add(pattern);
		node->bfs = new map<short,bloom_filter*>;
		node->bfs->insert(make_pair(outport, bf));
		//cout<<pattern<<endl;
		return true;
	}
}

inline int find_range(int level)
{
	switch(level){
		case 0:
			return 5;
		case 1:
			return 611;
		case 2:
			return 1215;
		case 3:
			return 1619;
		case 4:
			return 2021;
		case 5:
			return 2223;
		default:
			return -1;
	}
}

int Trie::match(TrieNode* node, char pattern[25], char entry[25])
{
	if (!node)
	{
		return 0;
	}

	if (node->isEnd)
	{
		for (map<short, bloom_filter*>::iterator bf_it = node->bfs->begin();
				bf_it != (node->bfs->end()); bf_it++)
		{
			if (bf_it->second->lookup(pattern))
			{
				return bf_it->first;
			}
		}
	}

	int range = find_range(node->level+1);
	for(int i=range/100;i<=range%100;i++){
		pattern[i]=entry[i];
	}
	int result1 = match(node->son[1],pattern,entry);
	if(result1>0)
		return result1;
	else{
		for(int i=range/100;i<=range%100;i++){
			pattern[i]=0;
		}
		return match(node->son[0],pattern,entry);
	}	
}

