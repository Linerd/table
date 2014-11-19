#include <cstdlib>
#include <fstream>
#include <string>
#include <iostream>
#include "Trie.h"

using namespace std;
inline void split(string& s, string& delim, string str[], int& outport)
{
    size_t last = 0;
    size_t index = s.find_first_of(delim, last);
    int count = 0;
    while (index != string::npos)
    {
        str[count++] = s.substr(last, index - last);
        last = index + 1;
        index = s.find_first_of(delim, last);
    }
    outport = atoi(s.substr(last, index - last).c_str());
}

int main(int argc, char *argv[])
{
    ifstream table("./table.txt");

    Trie* trie = new Trie();
    string entry;
    string reg = "|";
    int count = 0;
    while (!table.eof()&&count<10)
    {
        count++;
        getline(table, entry);
        string* str = new string[6];
        int outport;
        split(entry, reg, str, outport);
        int* mask = new int[6];
        string pattern = "";
        int mark = 0;
        for (int i = 0; i < 6; i++)
        {
            if (str[i].length() > 0)
            {
                mask[i] = 1;
                mark = i;
                pattern += str[i];
		cout<<str[i];
            }
        }
        cout<<trie->insert(mask, mark, pattern, outport);
	cin.get();
	delete mask;
	delete str;
    }

    table.close();
//
//    ifstream packet("packet.txt");
//    ofstream output("output.txt");
//    while (!packet.eof())
//    {
//        getline(packet, entry);
//        string* str = new string[6];
//        output << trie->match(trie->getRoot(), str, new string(""));
//    }
    return 0;
}
