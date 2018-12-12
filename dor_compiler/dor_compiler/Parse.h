#pragma once
#include "global.h"


class Parse
{
public:
	static int const_sea(int & type, int & result);
	static int program();
	static int func_decl(int type ,string name );
	static int const_decl();
	static int var_decl();
	static int statement();
	static int condition();
	static int factor(int & type , string & result);
	static int term(int& type , string &result);
	static int call();
	static int parse_return();
	static int parse_print();
	static int parse_scanf();
	static int parse_statlist();
	static int var_function_decide_decl();
	static int condition(string label_true, string label_false);
	static int expression(int & type, string &name);
	static int params_pass(string name);
	static int param_push_midgen(string name,int count);
};

