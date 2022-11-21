#include "../lib/parser.h"
#include <iostream>
#include <vector>
using namespace std;

int main()
{
	Parser parser;
	vector<char> s;
	parser.findFirst('E', s);
	for(vector<char>::iterator i = s.begin(); i != s.end(); i++)
	{
		cout << *i << endl;
	}
	return 0;
}