#include "signtable.h"
table* cur_table = NULL;
vector<table*>table_set;
table * table::get_func(string name) {
	for (auto &i : table_set)
		if (i->name == name)
			return i;
}
table_entry::table_entry(string name, int kind, int type,int addr ,int value =0 ){
	this->kind = kind;
	this->type = type;
	this->name = name;
	this->addr = addr;
	this->value = value;
	this->belong_table = cur_table;
}
table_entry::table_entry(string name, int kind, int type, table * function_table,int addr ,int value =0) {
	this->kind = kind;
	this->type = type;
	this->name = name;
	this->addr = addr;
	this->value = value;
	this->belong_table = function_table;

}

table::table(string name) {
	this->name = name;
	this->tablesize = 0;
	this->func_params_count = 0;
	this->func_tag = false;
}

int table::insert_function(string name,int type, table* func,bool is_main) {
	if (already_has(name))
		return -1;
	if (!is_main)
	{
		if (type == 0)
		{
			table_entry new_func_te = table_entry(name, FUNC, type, func,-1);
			entries.push_back(new_func_te);
		}else
		{
			table_entry new_func_te = table_entry(name, FUNC, type, func, this->tablesize);
			this->tablesize += 4;
			entries.push_back(new_func_te);
		}
		
	}
	return 0;

}

int table::insert_const(string name, int type ,int value =0 ) {
	if (already_has(name)) return -1;

	table_entry new_const_te = table_entry(name, CONST, type,this->tablesize ,value );
	this->tablesize += 4;
	entries.push_back(new_const_te);
	return 0;
}

int table::insert_var(string name, int type) {
	if (already_has(name)) return -1;
	table_entry new_var_te = table_entry(name, VAR, type, this->tablesize);
	this->tablesize += 4;
	entries.push_back(new_var_te);
	return 0;
}

int table::insert_array(string name, int type, int length) {
	if (already_has(name))return -1;
	table_entry new_arr_te = table_entry(name, ARR, type, this->tablesize, length);
	this->tablesize += length * 4;
	entries.push_back(new_arr_te);
	return 0;
}

int table::get_type(string name) {
	for (auto& i : this->entries)
		if (i.name == name)
			return i.type;
	if (this->father != NULL)
		return father->get_type(name);
	else return -1;
}
table_entry table::get_et(string name) {
	for (auto& i : this->entries)
		if (i.name == name)
			return i;
	if (this->father != NULL)
		return father->get_et(name);
	else return table_entry();
}


bool table::is_const(string name) {
	for(auto& i : this->entries)
		if (i.name == name) {
			return (i.type == CONST) ? true : false;
		}
	if (this->father != NULL)
		return father->is_const(name);
	else return false;
}

bool table::is_array(string name)
{
	for (auto& i : this->entries)
		if (i.name == name) {
			return (i.type == ARR) ? true : false;
		}
	if (this->father != NULL)
		return father->is_array(name);
	else return false;
}
bool table::is_func(string name) {
	for (auto& i : this->entries)
		if (i.name == name) {
			return (i.type == FUNC) ? true : false;
		}
	if (this->father != NULL)
		return father->is_func(name);
	else return false;
}
bool table::is_var(string name) {
	for (auto& i : this->entries)
		if (i.name == name) {
			return (i.type == VAR|| i.type== PARAM) ? true : false;
		}
	if (this->father != NULL)
		return father->is_var(name);
	else return false;
}

int table::insert_param(string name, int type) {
	if (already_has(name))return -1;
	table_entry new_param_te = table_entry(name, PARAM, type, this->tablesize);
	this->tablesize +=  4;
	entries.push_back(new_param_te);
	return 0;
}

bool table::already_has(string name) {
	for (auto &i : this->entries)
		if (i.name == name)
			return true;
	return false;
}