#ifndef TABLE
#define TABLE
#include "global.h"
#include "vector"
#include "map"

using namespace std;
enum tb_e_k { FUNC, PARAM, ARR, VAR, CONST };
class table_entry;
class table {
public:
	bool func_tag;
	string name;
	table* father;
	vector<table_entry> entries;
	int tablesize;
	int type;
	int func_params_count;
	
	table(string name);
	table(string name,int type, table* father, bool is_main);


	bool is_const(string name);
	bool is_var(string name);
	bool is_func(string name);
	bool is_array(string name);
	int get_type(string name);
	
static 	table * get_func(string name);

	int insert_function(string name, int type, table* father, bool is_main);
	int insert_const(string name, int type , int value =0);
	int insert_var(string name, int type);
	int insert_param(string name, int type);
	int insert_array(string name, int type, int length);

	bool already_has(string name);
	table_entry get_et(string name);

};

class table_entry {
	public:
	table* belong_table;
	string name;
	int kind; 
	int type;
	int value;  //array length
	int addr;
	table_entry();
	table_entry(string name, int kind, int type ,int addr ,int value=0 );//func param array var const 
	table_entry(string name, int kind, int type, table* function_table ,int addr, int value =0 );
};

extern table *cur_table;
extern vector<table*>table_set;

#endif // !TABLE

