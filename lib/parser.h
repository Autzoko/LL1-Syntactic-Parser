#ifndef _PARSER_H_
#define _PARSER_H_

#include "base.h"


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

	int findFirst(char symbol);
	map<char, vector<char>> follow(char symbol);
	map<char, vector<char>> select(char symbol);	



};

#endif