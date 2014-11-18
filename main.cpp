/*
 * main.cpp
 *
 *  Created on: Nov 18, 2014
 *      Author: yikai
 */

#include <iostream>
#include <map>

using std::map;
using std::cout;

int main() {
	map<int, int> map;
	map.insert(std::make_pair(1, 1));
	cout << (map.find(1) != map.end()) << " " << (map.find(2) != map.end());
	return 0;
}

