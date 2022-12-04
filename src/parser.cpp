#include "../lib/parser.h"
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

Parser::Parser()
{
	vector<string> _S;
	_S.push_back("V=E");
	syntax.insert(make_pair('S', _S));

	vector<string> _E;
	_E.push_back("TR");
	syntax.insert(make_pair('E', _E));

	vector<string> _R;
	_R.push_back("ATR");
	_R.push_back("e");
	syntax.insert(make_pair('R', _R));

	vector<string> _T;
	_T.push_back("FP");
	syntax.insert(make_pair('T', _T));

	vector<string> _P;
	_P.push_back("MFP");
	_P.push_back("e");
	syntax.insert(make_pair('P', _P));

	vector<string> _F;
	_F.push_back("(E)");
	_F.push_back("i");
	syntax.insert(make_pair('F', _F));

	vector<string> _A;
	_A.push_back("+");
	_A.push_back("-");
	syntax.insert(make_pair('A', _A));

	vector<string> _M;
	_M.push_back("*");
	_M.push_back("/");
	syntax.insert(make_pair('M', _M));

	vector<string> _V;
	_V.push_back("i");
	syntax.insert(make_pair('V', _V));

	Vn = {'S', 'E', 'R', 'T', 'P', 'F', 'A', 'M', 'V'};
	Vt = {'=', 'e', '(', ')', 'i', '+', '-', '*', '/'};
}

bool Parser::isVn(char symbol)
{
	for (vector<char>::iterator i = Vn.begin(); i != Vn.end(); i++)
		if (symbol == *i)
			return true;
	return false;
}

bool Parser::isVt(char symbol)
{
	for (vector<char>::iterator i = Vt.begin(); i != Vt.end(); i++)
		if (symbol == *i)
			return true;
	return false;
}

void Parser::findFirst(char symbol, vector<char> &firstset)
{
	if (isVn(symbol))
	{
		auto iter = syntax.find(symbol);
		for (vector<string>::iterator i = iter->second.begin(); i != iter->second.end(); i++)
		{
			string tmp = *i;
			findFirst(tmp[0], firstset);
		}
	}
	else if (isVt(symbol))
	{
		firstset.push_back(symbol);
	}
	else
	{
		return;
	}
}

void Parser::createFirstSet()
{
	vector<char> tmpSet;
	for (vector<char>::iterator iter = Vn.begin(); iter != Vn.end(); iter++)
	{
		tmpSet.clear();
		findFirst(*iter, tmpSet);
		FirstSets.insert(make_pair(*iter, tmpSet));
	}
}

void Parser::printFirstSets()
{
	cout << "Nonterminal\t\t\tFirstSet\t\t\t" << endl;
	string tmp;
	char lb = '{', rb = '}', tab = '\t', pin = ',';
	for (map<char, vector<char>>::iterator i = FirstSets.begin(); i != FirstSets.end(); i++)
	{
		tmp.clear();
		tmp.push_back(i->first);
		tmp.push_back(tab);
		tmp.push_back(tab);
		tmp.push_back(tab);
		tmp.push_back(tab);
		tmp.push_back(lb);
		for (vector<char>::iterator j = i->second.begin(); j != i->second.end(); j++)
		{
			tmp.push_back(*j);
			tmp.push_back(pin);
		}
		tmp.pop_back();
		tmp.push_back(rb);
		tmp.push_back(tab);
		tmp.push_back(tab);
		tmp.push_back(tab);
		cout << tmp << endl;
	}
}

void Parser::findFollow(char symbol, vector<char> &followset)
{
	if (symbol == 'S')
	{
		followset.push_back('#');
	}

	for (map<char, vector<string>>::iterator iter = syntax.begin(); iter != syntax.end(); iter++)
	{
		vector<string> genes = iter->second;
		for (vector<string>::iterator i = genes.begin(); i != genes.end(); i++)
		{
			string gene = *i;
			int symbolIndex = gene.find(symbol);
			if (symbolIndex < gene.size() - 1)
			{
				char followSymbol = gene[symbolIndex];
				if (isVt(followSymbol))
				{
					followset.push_back(followSymbol);
				}
				if (isVn(followSymbol))
				{
					vector<char> firstset = FirstSets[followSymbol];
					if (firstset.size() == 1 && firstset[0] == 'e')
					{
						char key = iter->first;
						if (FollowSets[key].empty())
						{
							findFollow(key, FollowSets[key]);
						}
						vector<char> inFollow = FollowSets[key];
						for (vector<char>::iterator n = inFollow.begin(); n != inFollow.end(); n++)
						{
							followset.push_back(*n);
						}
						continue;
					}
					for (vector<char>::iterator j = firstset.begin(); j != firstset.end(); j++)
					{
						if (*j != 'e')
						{
							followset.push_back(*j);
						}
					}
				}
			}
			else if (symbolIndex == gene.size() - 1)
			{
				char key = iter->first;
				if (FollowSets[key].empty())
				{
					findFollow(key, FollowSets[key]);
				}
				vector<char> inFollow = FollowSets[key];
				for (vector<char>::iterator n = inFollow.begin(); n != inFollow.end(); n++)
				{
					followset.push_back(*n);
				}
			}
			else
			{
				continue;
			}
		}
	}
}

void Parser::createFollowSet()
{
	for(vector<char>::iterator iter = Vn.begin(); iter != Vn.end(); iter++)
	{
		if(FollowSets[*iter].empty())
		{
			findFollow(*iter, FollowSets[*iter]);
		}
	}
}

void Parser::printFollowSets()
{
	cout << "Nonterminal\t\t\tFollowSet\t\t\t" << endl;
	string tmp;
	char lb = '{', rb = '}', tab = '\t', pin = ',';
	for (map<char, vector<char>>::iterator i = FollowSets.begin(); i != FollowSets.end(); i++)
	{
		tmp.clear();
		tmp.push_back(i->first);
		tmp.push_back(tab);
		tmp.push_back(tab);
		tmp.push_back(tab);
		tmp.push_back(tab);
		tmp.push_back(lb);
		for (vector<char>::iterator j = i->second.begin(); j != i->second.end(); j++)
		{
			tmp.push_back(*j);
			tmp.push_back(pin);
		}
		tmp.pop_back();
		tmp.push_back(rb);
		tmp.push_back(tab);
		tmp.push_back(tab);
		tmp.push_back(tab);
		cout << tmp << endl;
	}
}