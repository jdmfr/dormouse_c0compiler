#pragma once
#include "global.h"
#include "middle.h"
#include "stack"
extern vector<pair<int,int> > block_table;

class optim
{
public:
	
	void static optim_labels();
	void static gen_block(); //this is only for dag;
	void static DAG_optim();
	void static Find_Source_Oprend();
	void static Find_Target_Opcode();
	void static data_flow_analysis();


};


class TreeNode {
public:
	string value;
	vector<string> contents;
	vector<TreeNode *> fathers;
	TreeNode * Lchild;
	TreeNode * Rchild;	
	TreeNode * Achild;  //array child
	string representer;
	bool is_killed;
	bool is_array;
	static vector<TreeNode *> Forest;
	bool static Find_Source_Oprend(string name , TreeNode** var );
	bool static Find_Target_Opcode(string name , TreeNode* var_a,TreeNode *var_b , string c_op);
	bool static Find_Arrt_Opcode( TreeNode* var_a, TreeNode *var_b, TreeNode *var_c);
};

class Block {
	vector<string> def;
	vector<string> use;
	vector<string> in;
	vector<string> out;
	bool in_change;
	
	vector<Block*> ahead;
	vector<Block*> after;

	int in_length;
	int out_length;

};

extern vector<Block*> df_block_array;