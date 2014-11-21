#include <cstdlib>
#include <fstream>
#include <string>
#include <iostream>
#include "Trie.h"
#include <cstring>

using namespace std;
int readEntry(char entry[25],int mask[6], ifstream& ifs, short* outport)
{
	ifs.read(entry,24);
	ifs.read((char*)(outport),sizeof( short));

	short boo;
	ifs.read((char*)(&boo),sizeof boo);//read the 0x0d0a

	int mark=0;

	if(((int)(*entry)<<16)+(short)(*(entry+4)))
	{
		mask[0]=1;
		mark = 0;
	}
	if(((int)(*(entry+6))<<16)+(short)(*(entry+10)))
	{
		mask[1]=1;
		mark = 1;
	}
	if((int)(*(entry+12)))
	{
		mask[2]=1;
		mark = 2;
	}
	if((int)(*(entry+16)))
	{
		mask[3]=1;
		mark = 3;
	}
	if((short)(*(entry+20)))
	{
		mask[4]=1;
		mark =4;
	}
	if((short)(*(entry+22)))
	{
		mask[5]=1;	
		mark =5;
	}
	entry[24]='\0';
	return mark;
}	

int main(int argc, char **argv)
{
	ifstream table("table.dat");

	Trie* trie = new Trie();
//	int count = 0;
	int mask[6];
	char entry[25];
	int mark = 0;
	short outport;
//	while (!table.eof()&&count<10)
	while(!table.eof())
	{
		//count++;
		memset(mask,0,6);
		mark =readEntry(entry,mask,table,&outport);

		cout<<trie->insert(mask, mark, entry, outport);
		//if(!trie->insert(mask,mark,entry,outport))
		//	cout<<"failed insertion"<<endl;
		cin.get();
	}

	table.close();

	ifstream packet("packet.dat");
	ofstream output("output.txt");
	char packetEntry[25];
	int count=0;
	while (!packet.eof())
	{
		packet.read((char*)(packetEntry),24);
		short boo;
		packet.read((char*)(&boo),sizeof boo);
		
		packetEntry[24] = '\0';
		char pattern[25]={0};
		pattern[24]='\0';
		output << trie->match(trie->getRoot(), pattern, packetEntry)<<endl;
		count++;
	}
	cout<<count<<endl;
	packet.close();
	output.close();
	
//	ifstream out("output.txt");
//	ifstream port("outport.dat");
//	while(!output.eof())
//	{
//		int a;
//		int b;
//		short boo;
//		out>>a;
//		port.read((char*)(&b),sizeof b);
//		port.read((char*)(&boo),sizeof boo);
//		
//		if(a!=b)
//		{
//			cout<<"boo!"<<endl;
//		}
//	}	
//	output.close();
//	port.close();
	return 0;
}
