#include "optim.h"

vector<pair<int,int>> block_table;
vector<TreeNode *> TreeNode::Forest;

void optim::optim_labels() {
	int size = (int)midcode.size();
	for (int i = 0;i+1<size;i++) 
	{
		if (midcode[i].opcode == "GENLAB" && midcode[i+1].opcode =="GENLAB")
		{
			string used_label = midcode[i].c_op;
			string thrown_label = midcode[i + 1].c_op;
			for (int j = 0; j < size; j++)
			{
				if (midcode[j].c_op == thrown_label)
					midcode[j].c_op = used_label;
			}
			midcode.erase(midcode.begin() + i);
			i--;
			size--;
		}
	}
	//第二遍，中间代码处窥孔优化一下跳转指令
	size = (int)midcode.size();
	for (int i = 0; i < size; i++)
	{
		if (midcode[i].opcode == "GOTO")
		{
			if (midcode[i + 1].opcode == "GENLAB" && midcode[i].c_op == midcode[i + 1].c_op) {
				midcode.erase(midcode.begin() + i);
				i--;
				size--;
			}
		}
	}

	return;
}
void optim::gen_block() {
	int begin=0 , end;
	int size = (int)midcode.size();
	for (int i = 0; i < size; i++)
	{

		if (midcode[i].opcode == "GENLAB")
		{
			end = i;
			block_table.push_back(make_pair(begin,end) );
			begin = i;


		}
		if (midcode[i].opcode == "FUNC")
		{
			end = i;
			block_table.push_back(make_pair(begin, end));
			begin = i;


		}
		else if (is_comp(midcode[i].opcode))
		{
			end = i + 1;
			block_table.push_back(make_pair(begin, end));
			begin = i + 1;
		}
		else if (midcode[i].opcode == "CALL")
		{
			end = i+1;
			block_table.push_back(make_pair(begin, end));
			begin = i+1;
		}
		else if (midcode[i].opcode == "RET")
		{
			end = i + 1;
			block_table.push_back(make_pair(begin, end));
			i++;
			begin = i ;
		}


	}
	if (begin != size)
	{
		block_table.push_back(make_pair(begin, size));
	}


#ifdef GEN_BLOCK_INFO
	ofstream block_info;
	block_info.open("block_info.txt");
	for (auto &i : block_table)
	{
		block_info << i.first << "   " << i.second << endl;
	}
	block_info.close();
#endif

	return;
}
static bool can_process(string name) {
	return name=="=" || name == "+" || name == "/" || name == "*" || name == "-" \
		|| name == "=[]" || name == "[]=" || name == "PRTI" || name == "PRTC"
		|| name == "SCFC" || name == "SCFI" || name == "PRTS" || name == "PUSH" ||name=="RET"||is_comp(name) ;
}
inline void erase_left_edge(TreeNode * &node) {
	if(node->Lchild!=NULL)
		for (vector<TreeNode*>::iterator it = node->Lchild->fathers.begin(); it != node->Lchild->fathers.end(); it++) {
			if (*it == node) {
				node->Lchild->fathers.erase(it);
				break;
			}
		}
}
inline void erase_right_edge(TreeNode * &node) {
	if (node->Rchild != NULL)

		for (vector<TreeNode*>::iterator it = node->Rchild->fathers.begin(); it != node->Rchild->fathers.end(); it++) {
			if (*it == node) {
				node->Rchild->fathers.erase(it);
				break;
			}
		}
}
inline void erase_array_edge(TreeNode * &node) {
	for (vector<TreeNode*>::iterator it = node->Achild->fathers.begin(); it != node->Achild->fathers.end(); it++) {
		if (*it == node) {
			node->Achild->fathers.erase(it);
			break;
		}
	}
}
void do_del_erase(string name) {
	bool flag = false;
	//remove var_c in others
	TreeNode * killer;
	flag = TreeNode::Find_Source_Oprend(name, &killer);
	if (flag == true)
		for (int j = 0; j < (int)killer->contents.size(); j++)
		{
			if (killer->contents[j] == name)
			{
				killer->contents[j] += "#";
			}
			if (killer->fathers.size() == 0) {
				killer->contents.erase(killer->contents.begin() + j);
				if (killer->contents.size() == 0)
				{
					erase_left_edge(killer);
					erase_right_edge(killer);
					for (vector<TreeNode*>::iterator it = TreeNode::Forest.begin(); it < TreeNode::Forest.end(); it++) {
						if (*it == killer)
						{
							TreeNode::Forest.erase(it);
							break;
						}
					}
				}
			}
			// ERASE THIS ONE
		}
	return;

}


bool TreeNode::Find_Target_Opcode(string name, TreeNode* var_a, TreeNode *var_b, string c_op) {
	TreeNode * cur_node;
	for (int i = 0; i < TreeNode::Forest.size(); i++)
	{	
		cur_node = TreeNode::Forest[i] ;
		if (cur_node->value == name && cur_node->Lchild == var_a && cur_node->Rchild == var_b) {
			if (cur_node->value == "=[]" && cur_node->is_killed == true)
				return false; // if array is changed

			for (int j = 0; j < (int)cur_node->contents.size(); j++)
			{
				if (cur_node->contents[j] == c_op)
					return true;
			}
			do_del_erase(c_op);
			cur_node->contents.push_back(c_op);
		}
		else if (name == "*" || name == "+") {
			if (cur_node->value == name && cur_node->Rchild == var_a && cur_node->Lchild == var_b) {
				for (int j = 0; j < TreeNode::Forest.size(); j++)
				{
					if (cur_node->contents[j] == c_op)
						return true;
				}
				do_del_erase(c_op);
				cur_node->contents.push_back(c_op);
			}
		}
	}
	return false;
}
bool TreeNode::Find_Source_Oprend(string name, TreeNode** var) {
	TreeNode * cur_node;
	for (int i = 0; i < TreeNode::Forest.size(); i++)
	{
		cur_node = TreeNode::Forest[i];
		for (int j = 0; j < cur_node->contents.size(); j++) {
			if (cur_node->contents[j] == name)
			{
				*var = cur_node;
				return true;
			}
		}
	}
	return false;
}

bool TreeNode::Find_Arrt_Opcode(TreeNode* var_a, TreeNode *var_b, TreeNode *var_c) {
	TreeNode * cur_node;
	for (int i = 0; i < TreeNode::Forest.size(); i++)
	{
		cur_node = TreeNode::Forest[i];
		if (cur_node->value == "[]=" && cur_node->Achild == var_c && cur_node->Lchild == var_a && cur_node->Rchild == var_b) {
			return true;
		}
	}
	return false;
}

void optim::DAG_optim() {
	int cml=0;//current midcode line
	int cb_end;//current_block_end
	int block_count = (int)block_table.size();
	for (int z = 0; z < block_count; z++) {
		cml = block_table[z].first;
		cb_end = block_table[z].second;
		if ( cml + 1 == cb_end) {
			midcode_after.push_back(midcode[cml]);
			continue;
		}
		while (cml<cb_end&&!can_process(midcode[cml].opcode))
		{
			midcode_after.push_back(midcode[cml]);
			cml++;
		}

		while (cml < cb_end) {
			if (midcode[cml].opcode == "+" || midcode[cml].opcode == "-" || midcode[cml].opcode == "*" || midcode[cml].opcode == "/" || midcode[cml].opcode == "=[]")
			{ // can_calculate
				bool flag = false;
				TreeNode * var_a;
				flag = TreeNode::Find_Source_Oprend(midcode[cml].a_op, &var_a);
				if (flag == false)
				{
					var_a = new TreeNode;
					var_a->value = midcode[cml].a_op;
					var_a->Achild = NULL;
					var_a->is_array = false; 
					var_a->contents.push_back(midcode[cml].a_op);
					TreeNode::Forest.push_back(var_a);
				}

				TreeNode * var_b;
				flag = TreeNode::Find_Source_Oprend(midcode[cml].b_op, &var_b);
				if (flag == false)
				{
					var_b = new TreeNode;
					var_b->value = midcode[cml].b_op;
					var_b->Achild = NULL;
					var_b->is_array = false; 
					var_b->contents.push_back(midcode[cml].b_op);
					TreeNode::Forest.push_back(var_b);
				}
				
				TreeNode *var_c;
				flag = TreeNode::Find_Target_Opcode(midcode[cml].opcode, var_a, var_b, midcode[cml].c_op);
				if (flag == false)
				{
					var_c = new TreeNode;
					
					do_del_erase(midcode[cml].c_op);

					var_c->value = midcode[cml].opcode;
					var_c->contents.push_back(midcode[cml].c_op);
					var_c->Lchild = var_a;
					var_c->Rchild = var_b;
					var_a->fathers.push_back(var_c);
					var_b->fathers.push_back(var_c);
					TreeNode::Forest.push_back(var_c);
				}
				

			}
			else if (midcode[cml].opcode == "=") {
				bool flag = false;
				TreeNode * var_a;
				flag = TreeNode::Find_Source_Oprend(midcode[cml].a_op, &var_a);
				if (flag == false)
				{
					var_a = new TreeNode;
					var_a->value = midcode[cml].a_op;
					var_a->Achild = NULL;
					var_a->is_array = false;
					var_a->contents.push_back(midcode[cml].a_op);
					TreeNode::Forest.push_back(var_a);
				}
				do_del_erase(midcode[cml].c_op);
				var_a->contents.push_back(midcode[cml].c_op);

			}
			else if (midcode[cml].opcode == "[]=") {
				bool flag = false;
				TreeNode * array_node; //in fact ,it is c_op
				if (TreeNode::Find_Source_Oprend(midcode[cml].c_op, &array_node)) {
					for (auto &i : array_node->fathers)
					{
						i->is_killed = true;
					}
				}
				else {
					array_node = new TreeNode;

					array_node->Achild = NULL;
					array_node->value = midcode[cml].c_op;
					array_node->contents.push_back(midcode[cml].c_op);
					TreeNode::Forest.push_back(array_node);
				}



				TreeNode * var_b;
				flag = TreeNode::Find_Source_Oprend(midcode[cml].b_op, &var_b);
				if (flag == false)
				{
					var_b = new TreeNode;
					var_b->value = midcode[cml].b_op;
					var_b->Achild = NULL;
					var_b->is_array = false; //TODO: jiaru shuzu panduan
					var_b->contents.push_back(midcode[cml].b_op);
					TreeNode::Forest.push_back(var_b);
				}

				TreeNode * var_a;
				flag = TreeNode::Find_Source_Oprend(midcode[cml].a_op, &var_a);
				if (flag == false)
				{
					var_a = new TreeNode;
					var_a->value = midcode[cml].a_op;
					var_a->Achild = NULL;
					var_a->is_array = false; //TODO: jiaru shuzu panduan
					var_a->contents.push_back(midcode[cml].a_op);
					TreeNode::Forest.push_back(var_a);
				}

				TreeNode * var_target;
				flag = TreeNode::Find_Arrt_Opcode( var_a, var_b, array_node);
				if (flag == false)
				{
					var_target = new TreeNode;
					var_target->value = "[]=";
					var_target->Lchild = var_a;
					var_target->Rchild = var_b;
					var_target->Achild = array_node;
					array_node->fathers.push_back(var_target);
					var_a->fathers.push_back(var_target);
					var_b->fathers.push_back(var_target);
					TreeNode::Forest.push_back(var_target);
				}
			}

			else if (midcode[cml].opcode == "PUSH" || midcode[cml].opcode == "PRTI" || midcode[cml].opcode == "PRTS" || midcode[cml].opcode == "PRTC" ){
				bool flag = false;
				TreeNode * var_c;
				flag = TreeNode::Find_Source_Oprend(midcode[cml].c_op, &var_c);
				if (flag == false)
				{
					var_c = new TreeNode;
					var_c->value = midcode[cml].c_op;
					var_c->Achild = NULL;
					var_c->is_array = false; //TODO: jiaru shuzu panduan
					var_c->contents.push_back(midcode[cml].c_op);
					TreeNode::Forest.push_back(var_c);
				}
				TreeNode * var_target = new TreeNode;
				{
					var_target->value = midcode[cml].opcode;
					var_target->Lchild = var_c;   //Lchild
					var_c->fathers.push_back(var_target);
					var_c->is_array = false;
					TreeNode::Forest.push_back(var_target);
				}
			}
			else if (midcode[cml].opcode == "SCFI" || midcode[cml].opcode == "SCFC") {
			/*
				bool flag = false;
				TreeNode * var_c;
				flag = TreeNode::Find_Source_Oprend(midcode[cml].c_op, &var_c);
				if (flag == false)
				{
					var_c = new TreeNode;
					var_c->value = midcode[cml].c_op;
					var_c->Achild = NULL;
					var_c->is_array = false; //TODO: jiaru shuzu panduan
					var_c->contents.push_back(midcode[cml].c_op);
					TreeNode::Forest.push_back(var_c);
				}
				else {
					TreeNode *killer = var_c;
					for (int j = 0; j < (int)killer->contents.size(); j++)
					{
						if (killer->contents[j] == midcode[cml].c_op)
						{
							killer->contents[j] += "#";
						}
						if (killer->fathers.size() == 0)
						{
							killer->contents.erase(killer->contents.begin() + j);
							//ERASE THIS ONE
							if (killer->contents.size() == 0)
							{

							}
						}
					}
				}
				*/
				do_del_erase(midcode[cml].c_op);
				
				TreeNode * var_target = new TreeNode;
				{
					var_target->value = midcode[cml].opcode;
					var_target->contents.push_back(midcode[cml].c_op);
					var_target->is_array = false;
					TreeNode::Forest.push_back(var_target);
				}	
			}
			else if (midcode[cml].opcode == "RET") { //for ret
				TreeNode * var_c;
				TreeNode * var_target = new TreeNode;
				{
					var_target->value = midcode[cml].opcode;
				//	var_target->contents.push_back(midcode[cml].c_op);
					var_target->is_array = false;
					TreeNode::Forest.push_back(var_target);
				}
				if (midcode[cml].c_op != "") {
					bool flag = false;
					flag = TreeNode::Find_Source_Oprend(midcode[cml].c_op, &var_c);
					if (flag == false)
					{
						var_c = new TreeNode;
						var_c->value = midcode[cml].c_op;
						var_c->Achild = NULL;
						var_c->is_array = false; //TODO: jiaru shuzu panduan
						var_c->contents.push_back(midcode[cml].c_op);
						TreeNode::Forest.push_back(var_c);
					}
					var_target->Lchild = var_c;
				}
				else {
					var_target->Lchild = NULL;
				}


			}
			else if (is_comp(midcode[cml].opcode)) {
				bool flag = false;
				TreeNode* var_a;
				flag = TreeNode::Find_Source_Oprend(midcode[cml].a_op, &var_a);
				if (flag == false)
				{
					var_a = new TreeNode;
					var_a->value = midcode[cml].a_op;
					var_a->Achild = NULL;
					var_a->is_array = false;
					var_a->contents.push_back(midcode[cml].a_op);
					TreeNode::Forest.push_back(var_a);
				}
				TreeNode* var_b;
				flag = TreeNode::Find_Source_Oprend(midcode[cml].b_op, &var_b);
				if (flag == false)
				{
					var_b = new TreeNode;
					var_b->value = midcode[cml].b_op;
					var_b->Achild = NULL;
					var_b->is_array = false;
					var_b->contents.push_back(midcode[cml].b_op);
					TreeNode::Forest.push_back(var_b);
				}
				TreeNode* var_target = new TreeNode;
				var_target->value = midcode[cml].opcode;
				var_target->Lchild = var_a;
				var_target->Rchild = var_b;
				var_target->contents.push_back(midcode[cml].c_op);
				TreeNode::Forest.push_back(var_target);
			}
			else {
				break;
			}
			cml++;
		}//while read end
		//process DAG

		//ENSURE THE MAIN TYPE-KEY
		for (int i = 0; i < (int)TreeNode::Forest.size(); i++)
		{
			TreeNode * cur_node = TreeNode::Forest[i];
			if ((cur_node->value[0] >= '0'&&cur_node->value[0] <= '9') || (cur_node->value[0] == '-' && cur_node->value!="-") )
				cur_node->representer = cur_node->value;
	/*		{
				for (int cc = 1; cc < (int)cur_node->contents.size();cc++) {
					string content = cur_node->contents[cc];
					if (content[0] != '@'&& content[content.length()-1] != '#')
						cur_node->representer = content;
				}
			}*/
			else if (is_comp(cur_node->value))
				cur_node->representer = cur_node->contents[0];
			else if (cur_node->value == "RET");  //nothing to do 
			else { // current content
				bool flag = true;
				for (auto &cc : cur_node->contents) {
					if (cc[0] != '@'&& cc[cc.length()-1] != '#'){
						cur_node->representer = cc;
						flag = false;
						break;
					}
				}
				if (flag&&!cur_node->contents.empty()) {
					string first = cur_node->contents[0];
					if (first[first.length()-1] == '#')
						first = first.substr(0, first.length() - 1);
					cur_node->representer = first;
				}
			}
		}

		//END ENSURE

		stack<middle> temp_stack;
		TreeNode * cur_node;
		int index = TreeNode::Forest.size()-1;

		while(TreeNode::Forest.size()>0)
		{
			cur_node = TreeNode::Forest[index];
			//judge
			if (cur_node->value == "PUSH" || cur_node->value == "PRTI" || cur_node->value == "PRTS" || cur_node->value == "PRTC" )
			{
				temp_stack.push(middle(cur_node->value , "" , "", cur_node->Lchild->representer));
				
				erase_left_edge(cur_node);

				TreeNode::Forest.erase(TreeNode::Forest.begin() + index);
				index = TreeNode::Forest.size() - 1;
			}
			else if (cur_node->value == "SCFI" || cur_node->value == "SCFC") {
				temp_stack.push(middle(cur_node->value, "", "", cur_node->representer));
				TreeNode::Forest.erase(TreeNode::Forest.begin() + index);
				index = TreeNode::Forest.size() - 1;
			}
			else if (cur_node->value == "[]=") {
				temp_stack.push(middle(cur_node->value, cur_node->Lchild->representer, cur_node->Rchild->representer, cur_node->Achild->representer ));
				erase_left_edge(cur_node);
				erase_right_edge(cur_node);
				erase_array_edge(cur_node);
				TreeNode::Forest.erase(TreeNode::Forest.begin() + index);
				index = TreeNode::Forest.size() - 1;
			}
			else if (cur_node->value == "+" || cur_node->value == "-" || cur_node->value == "*" || cur_node->value == "/" || cur_node->value == "=[]") {
				if (cur_node->representer[0] != '@')
				{
					for (auto &it : cur_node->contents) {
						if (it[0]!='@'&& it!= cur_node->representer && it[it.length()-1] != '#')
						{
							temp_stack.push(middle("=", cur_node->representer , "", it ));
						}
					}
				}
				temp_stack.push(middle(cur_node->value, cur_node->Lchild->representer, cur_node->Rchild->representer, cur_node->representer));
				erase_left_edge(cur_node);
				erase_right_edge(cur_node);
				/*
				int index1=0;
				for (int i = 0; i < TreeNode::Forest.size(); i++)
				{
					if (TreeNode::Forest[i] == cur_node->Lchild)
					{
						index1 = i;
						break;
					}
				}
				*/
				TreeNode::Forest.erase(TreeNode::Forest.begin() + index);
				index = TreeNode::Forest.size() - 1;

			}
			else if(is_comp(cur_node->value) )
			{
				temp_stack.push(middle(cur_node->value, cur_node->Lchild->representer, cur_node->Rchild->representer, cur_node->representer));
				TreeNode::Forest.erase(TreeNode::Forest.begin() + index);
				index = TreeNode::Forest.size() - 1;
			}
			else if (cur_node->value == "RET") {
				if (cur_node->Lchild == NULL)
					temp_stack.push(middle("RET", "", "",""));
				else 
					temp_stack.push(middle("RET", "", "", cur_node->Lchild->representer));
				TreeNode::Forest.erase(TreeNode::Forest.begin() + index);
				index = TreeNode::Forest.size() - 1;
			}
			else {
				for (auto &it : cur_node->contents) {
					if (it[0] != '@' && it[it.length()-1] != '#' && it != cur_node->value)
					{
						temp_stack.push(middle("=", cur_node->representer, "", it));
					}
				}


				TreeNode::Forest.erase(TreeNode::Forest.begin() + index);
				index = TreeNode::Forest.size() - 1;
			}
		}
		middle transfer;
		while (!temp_stack.empty()) {
			transfer = temp_stack.top();
			midcode_after.push_back(transfer);
			temp_stack.pop();
		}
	/*	if (!can_process(midcode[cml - 1].opcode)) {
			midcode_after.push_back(midcode[cml - 1]);
		}
	*/	//TODO:这么加纯粹多余且错，但不加上也许对，待验证

		//验证结果
		if (cml < cb_end) {	
			midcode_after.push_back(midcode[cml]);
		}
	}

#ifdef GEN_BLOCK_INFO
	ofstream new_mid_real;
	new_mid_real.open("new_mid_real.txt");
	for (auto &i : midcode_after)
	{
		new_mid_real << i.opcode << "   " << i.a_op << "   " << i.b_op << "   " << i.c_op << endl;
	}
	new_mid_real.close();
#endif

	return;
}




void optim::data_flow_analysis() {
	


}