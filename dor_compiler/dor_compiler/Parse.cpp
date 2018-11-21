#include "Parse.h"
#include "LEX_ANALYSIS.h"
#include "ERR.h"
#include "signtable.h"
#include "string"
#define PARSE_DEBUG 1
int check(int tk ) {
	if (token == tk)
		return 0;
	else {
		ERR::error(tk);
		return -1;
	}
}
int skip_until(int tk) {
	while (1)
	{
		LEX_ANALYSIS::get_token();
		if (token == tk)
			break;
	}
	return 0;
}
int len = 0;

int err_count;
string newlabel() {
	static int a = 0;
	return "label" + to_string(a++);
};

string new_local_t() {
	static int b = 0;
	return "temp" + to_string(b++);
};
int Parse::program() {
	
	string g_cur_name = "$global";
	cur_table = new table( g_cur_name);
	table_set.push_back(cur_table);



	LEX_ANALYSIS::get_token();

	while(token == KW_const)
		const_decl();
	while(token == KW_char || token == KW_int || token == KW_void)
		var_function_decide_decl();
	if (token != TK_eof)
		ERR::error(14);//voerflow main

	if (PARSE_DEBUG)
		cout << "this is a program" << endl;
					
	return 0;
					
}

int Parse::var_function_decide_decl() {
	int type = token; //type decide 
	string name;
	string kind;

	LEX_ANALYSIS::get_token();

	if (token == KW_char || token == KW_int)
	{
		LEX_ANALYSIS::get_token();
		check(TK_ident);
		name = sym;

		LEX_ANALYSIS::get_token();
		if (token == TK_lparen) {
			func_decl(type, name);
		}
		else while (1)
		{
			if (token == TK_lbrack) {
				
				LEX_ANALYSIS::get_token();
				check(TK_num);
				
				len = LEX_ANALYSIS::sym_num;

				LEX_ANALYSIS::get_token();
				check(TK_rbrack);
				//insert_array
				if(!cur_table->insert_array(name, type, len)) ERR::error(27);
				LEX_ANALYSIS::get_token();
			}
			else if (token == TK_comma)
			{
				if (!cur_table->insert_var(name, type)) ERR::error(27);
				LEX_ANALYSIS::get_token();
				if (PARSE_DEBUG)
					cout << "this is a " << type << "var: " << name << endl;
				continue;
			}
			else if (token == TK_semicolon)
			{
				if (!cur_table->insert_var(name, type)) ERR::error(27);
				LEX_ANALYSIS::get_token();
				if (PARSE_DEBUG)
					cout << "this is a " << type << "var: " << name << endl;
				break;
			}


		}
	}
	else if (token == KW_void)
	{
		LEX_ANALYSIS::get_token();
		check(TK_ident);
		func_decl(type, sym);

		if (PARSE_DEBUG)
			cout << "this is a " << type << " func_decl: " << name << endl;

	}

}


int Parse::func_decl(int type, string funcname) {
	int param_count=0;
	string name="";
	int type;
	table* new_table = new table(funcname,FUNC, cur_table , funcname=="main");

	//newtable
	if (!cur_table->insert_function(funcname, FUNC, new_table, funcname == "main"))
	{
		ERR::error(27);
		skip_until(TK_lbrace);
		return -1;
	}



	LEX_ANALYSIS::get_token();
	if (check(TK_lparen)) {
		LEX_ANALYSIS::get_token();
		if (check(TK_rparen)) ERR::error(14); //不能把有参数的没参数的弄混
		else while (1)
		{
			if (token == KW_int || token == KW_char)
				type = token;
			else if (token == KW_void || token != TK_eof)
			{
				ERR::error(15, 1);//默认为int
				type = KW_int;  //local repair
			}
			
			//insert_param
			if (!new_table->insert_param(name, type)) ERR::error(28);

			LEX_ANALYSIS::get_token();
			name = sym;
			check(TK_ident);
			//insert
			param_count++;

			LEX_ANALYSIS::get_token();
			if (token == TK_lparen) break;    
			if (!check(TK_comma)) {
				ERR::error(16, 1); //
				skip_until(TK_comma);
				break;
			}
		}
	}
	new_table->func_params_count = param_count;
	cur_table = new_table;
	table_set.push_back(cur_table);
	//回填参数个数
	//curt = newt;
	//push_back curt



	//midcode添加label
	LEX_ANALYSIS::get_token();

	while (token == KW_const)
	{
		const_decl();
	}
	while (token == KW_int || token == KW_char)
	{
		var_decl();
	}
	while (token != TK_lparen) {
		statement();
	}
	if (PARSE_DEBUG)
	{
		cout << "this is a function ::" << name << endl;
	}
}

int Parse::var_decl() {
	int has_count = 0;
	int type = token;
	int len = 0;
	string name = "";
	LEX_ANALYSIS::get_token();
	while (1) {
		check(TK_ident);
		name = sym ;
		
		LEX_ANALYSIS::get_token();
		if (token == TK_lbrack) {
			
			LEX_ANALYSIS::get_token();
			check(TK_num);
			len = LEX_ANALYSIS::sym_num ;
			
			LEX_ANALYSIS::get_token();
			check(TK_rbrack);  
		}
		else len = 0;

		///
		has_count++;
		///
		
		//ins table 
		if (len != 0)
		{
			if(!cur_table->insert_array(name, type, len)) ERR::error(27);
		}
		else{
			if (!cur_table->insert_var(name, type)) ERR::error(27);
		}
		//ins midcode 


		if (token == TK_semicolon) break;
		if (token != TK_comma) {
			ERR::error(16, 0);
			skip_until(TK_semicolon);
			break;
		}
		else continue;
	}


	if (PARSE_DEBUG)
		cout << "this is var_decl line" << " , and we define " << has_count << " of " << LEX_PRINT_KEYS[type] << "kind var(s)"<<endl;
	//midcode return 

	cur_table = cur_table->father;
	
	check(TK_rbrack);
	LEX_ANALYSIS::get_token();

	return 0;
}

int Parse::statement() {
	string label_true = "";
	string label_false = "";
	if (token == KW_if)
	{
		label_false = newlabel();

		LEX_ANALYSIS::get_token();
		check(TK_lparen); // check '('

		LEX_ANALYSIS::get_token();
		condition("", label_false );
		//mid j label1
		check(TK_rparen);
		LEX_ANALYSIS::get_token();

		statement();

		if (check(KW_else))//必须有else
		{
			label_true = newlabel();
			//midcode j label2
			//midcode label1
			LEX_ANALYSIS::get_token();
			statement();
			//midcode label2


		}
		else{ 
			
			//local_repair
			;//midcode label2
		}
		if (PARSE_DEBUG)
			cout << "this is a if statement" << endl;
	}
	else if (token == KW_do) {
		label_false = newlabel();
		LEX_ANALYSIS::get_token();
		//midcode label1:

		statement();
		
		check(KW_while);   //WHILE
		LEX_ANALYSIS::get_token();
		check(TK_lparen);

		LEX_ANALYSIS::get_token();
		condition("",label_false);

		check(TK_rparen);
		LEX_ANALYSIS::get_token();
		if (PARSE_DEBUG)
			cout << "this is a while statement" << endl;
	}
	else if (token == TK_lbrace) //语句列
	{
		LEX_ANALYSIS::get_token();
		statement();
		while (!check(TK_rbrace))
			statement();
		if (PARSE_DEBUG)
			cout << "this is statement lines" << endl;
	}
	else if (token == KW_switch)
	{
		int type;
		string result;
		LEX_ANALYSIS::get_token();
		check(TK_lparen);
		if (!expression(type, result)) {
			ERR::error(29, 0); skip_until(TK_lbrace); LEX_ANALYSIS::get_token(); return -1;
		}

		check(TK_rparen);
		LEX_ANALYSIS::get_token();
		check(TK_lbrace);
		LEX_ANALYSIS::get_token();
		
		{
			if (token == KW_default)
			{
				ERR::error(30, 0); skip_until(TK_lbrace); LEX_ANALYSIS::get_token(); return -1;
			}

			check(KW_case);
			LEX_ANALYSIS::get_token();
			
			if(token != type){ ERR::error(31, 0); skip_until(TK_lbrace); LEX_ANALYSIS::get_token(); return -1; }
			LEX_ANALYSIS::get_token();
			check(TK_colon);
			LEX_ANALYSIS::get_token();
			statement();

			if (PARSE_DEBUG)
				cout << "this is a case" << endl;

			while (token == KW_case)
			{
				LEX_ANALYSIS::get_token();

				if (token != type) { ERR::error(31, 0); skip_until(TK_lbrace); LEX_ANALYSIS::get_token(); return -1; }
				else; //midcode
				LEX_ANALYSIS::get_token();
				

				check(TK_colon);
				LEX_ANALYSIS::get_token();
				statement();

				if (PARSE_DEBUG)
					cout << "this is another case" << endl;
				
			}
			if (token == KW_default)
			{
				LEX_ANALYSIS::get_token();
				check(TK_colon);
				statement();
			}

		}


		check(TK_lbrace);
		LEX_ANALYSIS::get_token();



		if (PARSE_DEBUG)
			cout << "this is a switch basket" << endl;

		return 0;

	}
	else if (token == TK_semicolon)
	{
		LEX_ANALYSIS::get_token;
		if (PARSE_DEBUG)
			cout << "this is a blank statement" << endl;
	}
	else if (token == TK_ident) {
		string name = sym;
		LEX_ANALYSIS::get_token();
		if (cur_table->is_var(name)||cur_table->is_const(name))
		{
			if (cur_table->is_const(name))
			{
				ERR::error(17, 0);
				skip_until(TK_semicolon);
				LEX_ANALYSIS::get_token();
				return -1;
			}
			else {
				LEX_ANALYSIS::get_token();
				check(TK_assign);
				int type;
				string expname;
				expression(type, expname);
				//midcode
			}
		}
		else if (cur_table->is_array(name)){
			int type;
			string subscript;
			LEX_ANALYSIS::get_token();
			check(TK_lbrack);
			LEX_ANALYSIS::get_token();
			if (expression(type, subscript) == 0){
				string expname;
				check(TK_rbrack);
				LEX_ANALYSIS::get_token();
				check(TK_assign);
				LEX_ANALYSIS::get_token();

				if (expression(type, expname) == 0){
					if (cur_table->get_type(name) !=type){
						ERR::error(18, 0);
						skip_until(TK_semicolon);
						LEX_ANALYSIS::get_token();
						return -1;
					}
					else {
						
					}//midcode s[i]=expname
				}
			}
		}
		else if (cur_table->is_func(name)/* is a func*/){
			int para_count = 0;
			//get_count
			int should_para_count = table::get_func(name)->func_params_count;
			LEX_ANALYSIS::get_token();
			if (para_count == 0)
			{
				; //midcode call func  
				
				if (check(TK_semicolon) != 0)
				{
					if (token == TK_lparen)
						ERR::error(19, 0);
					skip_until(TK_semicolon);
					LEX_ANALYSIS::get_token();
					return -1;
				}
				else LEX_ANALYSIS::get_token();
			}
			//---- 对于没有参数的函数，不能有调用符号 ----//
			else {
				if (check(TK_lparen) !=0 ) {
					skip_until(TK_semicolon);
				}
				LEX_ANALYSIS::get_token();

				para_count=params_pass(name);
				if (para_count!=should_para_count /*wrong params count */)
				{
					ERR::error(20, 0);
					skip_until(TK_semicolon);
					return -1;
				}

				check(TK_rparen);
				LEX_ANALYSIS::get_token();
			}
			if (check(TK_semicolon) != 0)
				skip_until(TK_semicolon);
			LEX_ANALYSIS::get_token();


			if (PARSE_DEBUG)
				cout << "this is an assignment or call_func" << endl;
			return 0;
		}
	}
	else if (token == KW_scanf)  //SCANF
	{
		string name;
		LEX_ANALYSIS::get_token();
		check(TK_lparen);

		LEX_ANALYSIS::get_token();
		check(TK_ident);
		name = sym;

		if (cur_table->get_type(name) == KW_int);/* check table */
		else if (cur_table->get_type(name) == KW_char);
		else {
			ERR::error(20, 0);
			skip_until(TK_semicolon);
			return -1;
		}
		LEX_ANALYSIS::get_token();
		while (token == TK_comma) {
			LEX_ANALYSIS::get_token();
			name = sym;

			if (cur_table->get_type(name) == KW_int);/* check table */
			else if (cur_table->get_type(name) == KW_char);
			else {
				ERR::error(20, 0);
				skip_until(TK_semicolon);
				return -1;
			}

			LEX_ANALYSIS::get_token();
		}
		check(TK_rparen);
		check(TK_semicolon);

		if (PARSE_DEBUG)
			cout << "this is a scanf statement" << endl;
	}
	else if (token == KW_printf) 
	{	
		string name;
		LEX_ANALYSIS::get_token();
		check(TK_lparen);
		LEX_ANALYSIS::get_token();
		name = sym;
		if (token == TK_cstr) {
			//
			//midcode
			LEX_ANALYSIS::get_token();
			if (token == TK_comma) {
				int type;
				string name;
				LEX_ANALYSIS::get_token();
				if (expression(type, name) != 0)
				{
					ERR::error(21, 4);
					return -1;
				}
				else if (type == KW_char)  /*midcode*/;
				else if (type == KW_int) /*midcode*/;
				else
				{
					ERR::error(16, 4);
					return -1;
				}
			}
		}
		else {
			int type;
			string expname;
			if (expression(type, expname) != 0) { //表达式错误
				ERR::error(21, 4);
				return -1;
			}
			else if (type == KW_char)  /*midcode*/;
			else if (type == KW_int) /*midcode*/;
			else
			{
				ERR::error(16, 4);
				return -1;
			}
		}
		check(TK_rparen);
		LEX_ANALYSIS::get_token();
		if (check(TK_semicolon) != 0)
		{
			skip_until(TK_semicolon);
			LEX_ANALYSIS::get_token();
			return -1;
		}
		else 	LEX_ANALYSIS::get_token();
		if (PARSE_DEBUG)
			cout << "this is a printf" << endl;


	}
	else {
		ERR::error(22, 0);
		skip_until(TK_semicolon);
		LEX_ANALYSIS::get_token();
		return -1;
	}
	return 0;

}

int Parse::condition(string true_label, string false_label) {
	int type;
	string expname1;
	string expname2;
	if (expression(type, expname1) != 0)
	{
		skip_until(TK_rparen);
		return  -1;
	}

	if (LEX_ANALYSIS::is_compop(token))// daiding  gaicheng yunsuanfu
	{
		
		LEX_ANALYSIS::get_token();
		if (expression(type, expname1) != 0)
		{
			skip_until(TK_rparen);
			//这里没有LEX_ANALYSIS::get_token();

			return  -1;
		}
		if (true_label != "")
			; // midcode
		if (false_label != "")
			; // midcode
	}
	else {
		if (true_label != "")
			; // midcode
		if (false_label != "")
			; // midcode
	}

	if (PARSE_DEBUG)
		cout << "this is an inside condition " << endl;
	return 0;
}

int Parse::expression(int &type, string &result) {
	string opcode;
	string a;
	string term1;
	string term2;
	result = "";

	if (token == TK_plus || token == TK_minus) {
		type = KW_int;
		if (token == TK_plus) {
			LEX_ANALYSIS::get_token();
			if (term(type, term1) != 0) 
				return -1;
			if (term1 != "")
			{
				;//midcode
			}
		}
		else if (token == TK_minus)
		{
			LEX_ANALYSIS::get_token();
			if (term(type, term1) != 0)
				return -1;
			if (term1 != "")
			{
				;//midcode
			}
		} 
	}
	else {
		if (term(type, term1) != 0) return -1;
	}
	while (token == TK_plus || token == TK_minus) {
		type = KW_int;
		if (token == TK_plus) {
			LEX_ANALYSIS::get_token();
			if (term(type, term1) != 0)
				return -1;
			if (term1 != "")
			{
				;//midcode
				continue;
			}
		}
		else if (token == TK_minus)
		{
			LEX_ANALYSIS::get_token();
			if (term(type, term1) != 0)
				return -1;
			if (term1 != "")
			{
				;//midcode
				continue;
			}
		}
	}

	if (PARSE_DEBUG)
		cout << "this is a expression " << endl;
	return 0;
}


int Parse::term(int &type, string &result) {
	string opcode;
	string fact1;
	string fact2;
	result = "";
	
	if (factor(type, fact1) != 0) return -1;
	result = fact1;
	
	while (token == TK_mul || token == TK_div) {
		LEX_ANALYSIS::get_token();
		if (factor(type, fact2) != 0) return -1;

		result = new_local_t();
		//midcode
		fact1 = result;
	}

	if (PARSE_DEBUG)
		cout << "this is a term " << endl;
}

int Parse::factor(int &type, string &result) {
	string name;
	string subscript;
	int offset;
	int before_errc = err_count;
	if (token == TK_ident) {
		name = sym;
		

		if (cur_table->is_array(name)) //is_array
		{
			LEX_ANALYSIS::get_token();
			check(TK_lbrack);
			if (expression(type, subscript) != 0) {
				ERR::error(23, 0);
				skip_until(TK_rbrack);
				LEX_ANALYSIS::get_token();
				return -1;
			}
			offset = LEX_ANALYSIS::sym_num;

			/*如果数组溢出,要报错*/
			if (offset >= (cur_table->get_et(name)).value)
			{
				ERR::error(23, 0);
				skip_until(TK_rbrack);
				//这里不能有 LEX_ANALYSIS::get_token();
				return -1;
			}
			/*overflow end*/
			result = new_local_t();
			//midcode
			LEX_ANALYSIS::get_token();
			check(TK_rbrack);
			LEX_ANALYSIS::get_token();
		}
		else if (cur_table->is_var(name))//is_var
		{
			type = cur_table->get_type(name);
			result = name;
			LEX_ANALYSIS::get_token();
		}
		else if(cur_table->is_func(name)) // is_func
		{
			int should_para_num = 0;
			int params_num = 0;
			string temp;

			table * func_t = table::get_func(name);
			type = func_t->type;
			should_para_num = func_t->func_params_count;
			//找到表项
			//type
			// should_para_num  已完成
			LEX_ANALYSIS::get_token();
			//检查param个数
			if (should_para_num != 0) {
				check(TK_lparen);
				LEX_ANALYSIS::get_token();

				params_num = params_pass(name);
				if (params_num != should_para_num)//传参个数不一样
				{
					ERR::error(26, 4);
					skip_until(TK_semicolon);
					return -1;
				}
				check(TK_lparen);
				LEX_ANALYSIS::get_token();

			}
			//midcode callfunc
			//assign


			result = temp;
		}
		else
		{
			ERR::error(24);
			skip_until(TK_semicolon);
			//LEX_ANALYSIS::get_token();
			return -1;
		}
	}
	else if (token == TK_plus || token == TK_minus) {
		int flag = 0;
		type = KW_int;
		if (token == TK_minus)
			flag = 1;
		LEX_ANALYSIS::get_token();
		if (check(TK_num) != 0) result = "0";
		else if (flag)
			result = "-" + to_string(LEX_ANALYSIS::sym_num);
		LEX_ANALYSIS::get_token();

	}
	else if (token == TK_lparen) {
		LEX_ANALYSIS::get_token();
		if (expression(type, result) != 0) 
		
		check(TK_rparen);
		LEX_ANALYSIS::get_token();

	}
	else if (token == TK_cchar)
	{
		type = KW_char;
		result = LEX_ANALYSIS::sym_num;
		LEX_ANALYSIS::get_token();
	}
	else
	{
		ERR::error(25, 4);
	}
	if (before_errc != err_count)
		return -1;
	if (PARSE_DEBUG)
		cout << "this is a factor" << endl;
	return 0;
}

int Parse::params_pass(string name) {
	int type;
	int param_num=0;
	string expname;
	if (token == TK_rparen) {
		return param_num;
	}
	if(expression(type, expname)!=0) return -1;
	// 查表项
	//midcode
	param_num++;
	while (token == TK_comma)
	{
		LEX_ANALYSIS::get_token();
		expression(type, expname);
		param_num++;
		//midcode
	}
	return param_num;
}





