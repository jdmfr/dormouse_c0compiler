#include "signtable.h"
table* cur_table = NULL;
vector<table*>table_set;
vector<string> string_set;
table * table::get_func(string name) {
	for (auto &i : table_set)
		if (i->name == name)
			return i;
	return table_set[0];
}
table_entry::table_entry(string name, int kind, int type,int addr ,int value ){
	this->kind = kind;
	this->type = type;
	this->name = name;
	this->addr = addr;
	this->value = value;
	this->belong_table = cur_table;
	this->has_reg = false;

}
table_entry::table_entry(string name, int kind, int type, table * function_table,int addr ,int value) {
	this->kind = kind;
	this->type = type;
	this->name = name;
	this->addr = addr;
	this->value = value;
	this->belong_table = function_table;
	this->has_reg = false;

}
table_entry::table_entry() {

}

table::table(string name) {
	this->name = name;
	this->tablesize = 0;
	this->func_params_count = 0;
	this->func_tag = false;
}
table::table(string name, int type, table* father, bool is_main) {
	this->name = name;
	this->tablesize = 0;
	this->func_params_count = 0;
	this->func_tag = false;
	this->type = type;
	this->father = father;
}
int table::insert_function(string name,int type, table* func,bool is_main) {
	if (already_has(name))
		return -1;
	if (1)
	{
		if (type == 0)
		{
			table_entry new_func_te = table_entry(name, FUNC, type, func,-1);
			entries.push_back(new_func_te);
		}else
		{
			table_entry new_func_te = table_entry(name, FUNC, type, func, this->tablesize);
			//this->tablesize += 4;
			entries.push_back(new_func_te);
		}
		
	}
	return 0;

}

int table::insert_const(string name, int type ,int value ) {
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
			return (i.kind == CONST) ? true : false;
		}
	if (this->father != NULL)
		return father->is_const(name);
	else return false;
}

bool table::is_array(string name)
{
	for (auto& i : this->entries)
		if (i.name == name) {
			return (i.kind == ARR) ? true : false;
		}
	if (this->father != NULL)
		return father->is_array(name);
	else return false;
}
bool table::is_func(string name) {
	for (auto& i : this->entries)
		if (i.name == name) {
			return (i.kind == FUNC) ? true : false;
		}
	if (this->father != NULL)
		return father->is_func(name);
	else return false;
}
bool table::is_var(string name) {
	for (auto& i : this->entries)
		if (i.name == name) {
			return (i.kind == VAR|| i.kind== PARAM) ? true : false;
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
	if (this->entries.empty()) return false;
	for (auto &i : this->entries)
		if (i.name == name)
			return true;
	return false;
}


/////ÐÂÔöº¯Êý
bool table::find_sreg(string name) {
	for (auto& it : this->local_s_pool) {
		if (it.second == name)
			return true;
	}
	return false;
}
string table::get_sreg(string name) {
	for (auto& it : this->local_s_pool)
	{
		if (it.second == name)
			return  "$s"+to_string(it.first) ;
	}
	return "";
}

string table::get_addr(string name) {
	for (auto& it : this->entries) {
		if (it.name == name)
			return  to_string(it.addr) + "($fp)";
	}
	if (this->father != NULL)
	{
		for (auto& it : this->father->entries)
		{
			if (it.name == name)
				return to_string(it.addr) + "($gp)";
		}
	}
	else
	{
		cout << "get addr_wrong" << endl;
		getchar();
	}
	return "";

}

int table::get_a_offset(string name) {
	for (auto& it : this->entries) {
		if (it.name == name)
			return  it.addr;
	}
}

bool table::is_local(string sname){
	for (auto &it : this->entries) {
		if (it.name == sname)
			return true;
	}
	return false;

}

int table::get_tbs(string sname) {
	for (auto &it : table_set) {
		if (it->name == sname)
			return it->tablesize;
	}
}