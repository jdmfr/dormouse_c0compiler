#pragma once
#include <string>
#include "global.h"
class middle
{
public:
	string opcode;
	string a_op;
	string b_op;
	string c_op;

	middle();
	middle(string opcode, string a,string b, string c);
	~middle();

	static int open_write_middle(string filename);
	static int genmid_var_and_func(string opcode, string a, string b, string c);
	static int genmid_comp(string opcode, string a, string b, string c);
	static int genmid_cal(string opcode, string a, string b, string c);
	static int genmid(string opcode, string a, string b, string c);
	static int middle_real_generate();
};


extern vector<middle> midcode;
extern vector<middle> midcode_after;