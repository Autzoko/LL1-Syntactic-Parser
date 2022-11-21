#ifndef _PARSER_H_
#define _PARSER_H_

#include <map>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Parser
{
private:
	map<char, vector<string>> syntax;
	vector<char> Vn;
	vector<char> Vt;

	map<char, vector<char>> FirstSets;
public:
	Parser();

	bool isVn(char symbol);
	bool isVt(char symbol);

	void findFirst(char symbol, vector<char> &firstset);
	void createFirstSet();
	void printFirstSets();

	void findFollow(char symbol, vector<char> &followset);	



};

#endif