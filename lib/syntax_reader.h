#ifndef _SYNTAX_READER_H_
#define _SYNTAX_READER_H_


class SyntaxReader()
{
private:
	vector<string> syntax_line;
	string srcFilename;
	int readLines();
	int syntaxAnalyze();
	map<string, vector<string>> syntaxMap;

public:
	SyntaxReader(string file);
}

#endif /*_SYNTAX_READER_H_*/