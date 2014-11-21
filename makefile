objects = main.o Trie.o TrieNode.o 
output : $(objects)
	g++ -Wall -std=c++11 -o main $(objects) /usr/local/lib/libbf.so

main.o :Trie.h TrieNode.h
	g++ -Wall -c main.cpp -std=c++11
Trie.o :Trie.h TrieNode.h 
	g++ -Wall -c Trie.cpp -std=c++11
TrieNode.o :TrieNode.h
	g++ -Wall -c TrieNode.cpp -std=c++11
.PHONY : clean
clean :
	-rm main $(objects)
