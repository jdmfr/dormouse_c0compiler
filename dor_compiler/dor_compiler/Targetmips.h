#pragma once
#include "middle.h"
#include "signtable.h"
class Targetmips
{
public:
	Targetmips();
	~Targetmips();
	static int generator();
};

/*
class temp_item {
	string temp_name;
	bool has_reg;
	int temp_reg;
	vector<int> exist_record;

	temp_item(string name) {
		this->temp_name = name;
		this->has_reg = false;
		this->temp_reg = 0;

	}

};
*/


class temp_stack 
{
public:	
	string temp_name[100];
	static int top_flag;

	void reset();
	void pushT(string name);
	int getT_addr_inStack(string name);
};

