#include "../lib/syntax_reader.h"
using namespace std;

SyntaxReader::SyntaxReader(string filename)
{
	this.srcFilename = filename;
}

int SyntaxReader::readLines()
{
	fstream syntaxFile;
	syntaxFile.open(srcFilename.c_str(), ios::in);
	string tmp = new tmp;
	while(!syntaxFile.eof())
	{
		tmp.clean();
		syntaxFile.getline(tmp, 1024);
		syntax_line.push_back(tmp);
	}
	delete tmp;
	return 0;
}

int SyntaxReader::syntaxAnalyze()
{
	string tmp_left;
	vector<string> tmp_right;
	string right;
	for(vector<string>::iterator i = syntax_line.begin(); i != syntax_line.end(); i++)
	{
		tmp_left.clean();
		tmp_right.clean();
		string right;
		for(string::iterator j = *i.begin(); j != *i.end(); j++)
		{
			if(*(j + 1) != '-' && *(j + 2) != '>' && *j != ' ')
			{
				tmp_left.push_back(*j);
				continue;
			}
			if(*j == '-' && *(j + 1) == '>')
			{
				j += 2;
				continue;
			}
			if(*j != '|' && *j != ' ')
			{
				right.push_back(*j);
				continue;
			}
			if(*j == '|')
			{
				tmp_right.push_back(right);
				right.clean();
				continue;
			}
			syntaxMap.insert(pair<tmp_left, tep_right>);
		}
	}
}