#include "global.h"
#include "LEX_ANALYSIS.h"
#include <iostream>

using namespace std;

void pregroess(){
	WordMap.insert(pair<string, int>("void", 1));
	WordMap.insert(pair<string, int>("int", 2));
	WordMap.insert(pair<string, int>("char", 3));
	WordMap.insert(pair<string, int>("main", 4));
	WordMap.insert(pair<string, int>("if", 5));
	WordMap.insert(pair<string, int>("else", 6));
	WordMap.insert(pair<string, int>("do", 7));
	WordMap.insert(pair<string, int>("while", 8));
	WordMap.insert(pair<string, int>("switch", 9));
	WordMap.insert(pair<string, int>("case", 10));
	WordMap.insert(pair<string, int>("default", 11));
	WordMap.insert(pair<string, int>("scanf", 12));
	WordMap.insert(pair<string, int>("printf", 13));
	WordMap.insert(pair<string, int>("return", 14));
	WordMap.insert(pair<string, int>("const", 15));
	return;
}
 

int main()
{
	error_count = 0;
	pregroess();
	if (LEX_ANALYSIS::readfile() == 0)
		while (1)
		{
			LEX_ANALYSIS::get_token();
			LEX_ANALYSIS::print();
			if (token==TK_eof)
				break;
		}
	getchar();
	getchar();
	return 0;

}
