#include "../lib/parser.h"
using namespace std;

Parser::Parser()
{
	vector<string> _S;
	_S.push_back("V=E");
	syntax.insert(make_pair<char, vector<string>>('S', _S));

	vector<string> _E;
	_E.push_back("TR");
	syntax.insert(make_pair<char, vector<string>>('E', _E));

	vector<string> _R;
	_R.push_back("ATR");
	_R.push_back("e");
	syntax.insert(make_pair<char, vector<string>>('R', _R));

	vector<string> _T;
	_T.push_back("FP");
	syntax.insert(make_pair<char, vector<string>>('T', _T));

	vector<string> _P;
	_P.push_back("MFP");
	_P.push_back("e");
	syntax.insert(make_pair<char, vector<string>>('P', _P));

	vector<string> _A;
	_A.push_back("+");
	_A.push_back("-");
	syntax.insert(make_pair<char, vector<string>>('A', _A));

	vector<string> _M;
	_M.push_back("*");
	_M.push_back("/");
	syntax.insert(make_pair<char, vector<string>>('M', _M));

	vector<string> _V;
	_V.push_back("i");
	syntax.insert(make_pair<char, vector<string>>('V', _V));

	Vn = {'S', 'E', 'R', 'T', 'P', 'F', 'A', 'M', 'V'};
	Vt = {'=', 'e', '(', ')', 'i', '+', '-', '*', '/'};
}

bool Parser::isVn(char symbol)
{
	for(vector<char>::iterator i = Vn.begin(); i != Vn.end(); i++)
		if(symbol == *i)
			return true;
	return false;
}

bool Parser::isVt(char symbol)
{
	for(vector<char>::iterator i = Vt.begin(); i != Vt.end(); i++)
		if(symbol == *i)
			return true;
	return false;
}

int Parser::findFirst(char symbol, vector<char> &firstset)
{
	if(isVn(symbol))
	{
		auto iter = syntax.find(symbol);
		for(vector<string>::iterator i = iter->second.begin(); i != iter->second.end(); i++)
		{
			for(string::iterator j = *i.begin(); j != *i.end(); j++)
			{
				findFirst(*j, firstset);
			}
		}
	}
	else if(isVt(symbol))
	{
		firstset.push_front(symbol);
	}
	else
	{
		return -1;
	}
}