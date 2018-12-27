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
	int tablesize;
	int stacksize;
	int type;
	int func_params_count;
	vector<table_entry> entries;
	vector<string> temp_set;

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

	
	////目标代码生成阶段的新增函数

	string get_const_value(string name);

	map <int,string>  local_s_pool;
	bool find_sreg(string name);
	string get_sreg(string name);
	string get_addr(string name);
	int get_a_offset(string name);
	bool is_local(string sname);
	static int get_tbs(string sname);
};

class table_entry {
	public:
	string name;
	int kind;
	int type;
	int value;  //array length
	int addr;
	table* belong_table;
	
	bool has_reg;
	string reg;

	table_entry();
	table_entry(string name, int kind, int type ,int addr ,int value=0 );//func param array var const 
	table_entry(string name, int kind, int type, table* function_table ,int addr, int value =0 );
};

extern table *cur_table;
extern vector<table*>table_set;
extern vector<string> string_set;
#endif // !TABLE

