#pragma once
#include "LEX_ANALYSIS.h"
#include "global.h"
#include "ERR.h"
using namespace std;



class ERR
{
public:
	static string err_msg[];
	static void error(int error_num, int process_way=0);

};

