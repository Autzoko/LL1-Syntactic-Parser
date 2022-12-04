#include "../lib/parser.h"
#include <iostream>
#include <vector>
using namespace std;

int main()
{
	Parser parser;
	parser.createFirstSet();
	parser.printFirstSets();
	parser.createFollowSet();
	parser.printFollowSets();
}