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
	map<char, vector<char>> FollowSets;

	string text;
	string abstractText;

	struct parserTable
	{
		char rowElement;
		char lineElement;
		char* findTarget(char rowEle, char lineEle);
		string target;
	} table;
public:
	Parser();

	bool isVn(char symbol);
	bool isVt(char symbol);

	void findFirst(char symbol, vector<char> &firstset);
	void createFirstSet();
	void printFirstSets();

	void findFollow(char symbol, vector<char> &followset);	
	void createFollowSet();
	void printFollowSets();

	void createParserTable(struct parserTable &table);
	void printParserTable();

	char* findTarget(char rowEle, char lineEle);

	void textAbstract();
	void analyzeStack();
};

#endif