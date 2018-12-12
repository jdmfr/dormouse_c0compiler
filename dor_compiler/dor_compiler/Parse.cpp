#include "Parse.h"
#include "LEX_ANALYSIS.h"
#include "ERR.h"
#include "signtable.h"
#include "middle.h"
#include "string"
#include "stack"
#define PARSE_DEBUG 1

string type2str[4] = { "","void","int","char" };
char i_swap_s[10] = { 0 };
string opposite_op(string op) {
	if (op == "==")return "bne";
	if (op == "!=")return "beq";
	if (op == "<")return "bge";
	if (op == ">")return "ble";
	if (op == "<=")return "bgt";
	if (op == ">=")return "blt";
}
string op2str(string op) {
	if (op == "==") return "beq";
	if (op == "!=")return "bne";
	if (op == "<")return "blt";
	if (op == ">")return "bgt";
	if (op == "<=")return "ble";
	if (op == ">=")return "bge";
}

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
string newlabel() {
	static int a = 0;
	return "label." + to_string(a++);
}
string new_local_t() {
	static int b = 0;
	return "@dor" + to_string(b++);
}
int len = 0;
int err_count;
int already_main = 0;
int Parse::program() {
	
	string g_cur_name = "$global";
	cur_table = new table( g_cur_name);
	table_set.push_back(cur_table);



	LEX_ANALYSIS::get_token();

	while(token == KW_const)
		const_decl();
	while((token == KW_char || token == KW_int || token == KW_void)&& !already_main)
		var_function_decide_decl();
	
	if (token != TK_eof)
		ERR::error(14);//voerflow main

	if (PARSE_DEBUG)
		cout << "this is a program" << endl;
					
	return 0;
					
}

int Parse::var_function_decide_decl() {             //var 或者func  都是全局的
	int type = token; //type decide 
	string name;
	string kind;

	if (token == KW_char || token == KW_int)
	{
		LEX_ANALYSIS::get_token();
		check(TK_ident);
		name = sym;

		LEX_ANALYSIS::get_token();
		if (token == TK_lparen ||token == TK_lbrace ) {
			func_decl(type, name);
			if (PARSE_DEBUG)
				cout << "this is a func declare " << endl;
			LEX_ANALYSIS::get_token();

			return 0;
		}
		else while (1)
		{
			if (token == TK_lbrack) {  //数组
				
				LEX_ANALYSIS::get_token();
				check(TK_num);
				
				len = LEX_ANALYSIS::sym_num;

				LEX_ANALYSIS::get_token();
				check(TK_rbrack);
				//insert_array
				if (cur_table->insert_array(name, type, len) != 0)
				{
					skip_until(TK_semicolon);
					ERR::error(27);
					LEX_ANALYSIS::get_token();
					return -1;
				}
					
				itoa(len, i_swap_s ,10);
				middle::genmid_var_and_func("ARRAY", type2str[type],  name, i_swap_s );   ///gen mid code


				LEX_ANALYSIS::get_token();
				if (token == TK_comma || token == TK_semicolon)
				{

					if (token == TK_semicolon)
						break;
					else {
						LEX_ANALYSIS::get_token();
						check(TK_ident);
						name = sym;
						LEX_ANALYSIS::get_token();
						continue;
					}
				}
				else {
					error_count++;
					skip_until(TK_semicolon);
					LEX_ANALYSIS::get_token();
					return -1;
				}
			}
			else if (token == TK_comma)   //多个参数
			{
				if (cur_table->insert_var(name, type) != 0) {
					skip_until(TK_semicolon);
					ERR::error(27);
					LEX_ANALYSIS::get_token();
					return -1;
				}

				middle::genmid_var_and_func("VAR", type2str[type], "", name);   ///gen mid code 

				LEX_ANALYSIS::get_token();
				check(TK_ident);
				name = sym;
				LEX_ANALYSIS::get_token();
				continue;
			}
			else if (token == TK_semicolon)
			{
				if (cur_table->insert_var(name, type) != 0) ERR::error(27);
				middle::genmid_var_and_func("VAR", type2str[type], "", name);   ///gen mid code 

				break;
			}


		}
	}
	else if (token == KW_void)
	{
		LEX_ANALYSIS::get_token();
		if (token != TK_ident &&token!= KW_main) {
			ERR::error(33, 0);
			skip_until(TK_semicolon);
			LEX_ANALYSIS::get_token();
			return -1;
		}
		else if (token == TK_ident) {
			LEX_ANALYSIS::get_token();
			func_decl(type, sym);    //type::void类型 sym::函数名
			LEX_ANALYSIS::get_token();
		}
		else {
			LEX_ANALYSIS::get_token();
			check(TK_lparen);
			LEX_ANALYSIS::get_token();
			check(TK_rparen);
			LEX_ANALYSIS::get_token();
			func_decl(type, sym);

			LEX_ANALYSIS::get_token();
			already_main = 1;
		}
		if (PARSE_DEBUG)
			cout << "this is a func declare " << endl;
		return 0;
	}
	LEX_ANALYSIS::get_token();

	if (PARSE_DEBUG)
		cout << "this is a var statement "<< endl;
	return 0;
}

int Parse::func_decl(int type, string funcname) {
	int param_count=0;
	string name="";//var name
	table* new_table = new table(funcname,type, cur_table ,(bool) (funcname=="main"));

	//newtable
	if (cur_table->insert_function(funcname, FUNC, new_table, funcname == "main") != 0)
	{
		ERR::error(27);
		skip_until(TK_lbrace);
		return -1;
	}


	//midcode添加label
	middle::genmid_var_and_func("FUNC", type2str[type], "", funcname);
	////


	//LEX_ANALYSIS::get_token();上一阶段已经做过了，现在是 { 或者 (
	if (token==TK_lparen) {
		LEX_ANALYSIS::get_token();
		if (token == TK_rparen) ERR::error(14); //不能把有参数的没参数的弄混
		else while (1)
		{
			if (token == KW_int || token == KW_char)
				type = token;
			else if (token == KW_void || token != TK_eof)
			{
				ERR::error(15, 1);//默认为int
				type = KW_int;  //local repair
			}
			


			LEX_ANALYSIS::get_token();
			check(TK_ident);
			name = sym;
			param_count++;
			LEX_ANALYSIS::get_token();
			//insert_param
			if (new_table->insert_param(name, type) != 0) ERR::error(28);

			middle::genmid_var_and_func("PARA", type2str[type], "", name); //para midcode


			if (token == TK_rparen) {
				LEX_ANALYSIS::get_token();
				break;
			}
			if (token != TK_comma) {
				ERR::error(16, 1); //
				skip_until(TK_rparen);
				LEX_ANALYSIS::get_token();
				break;
			}
			else
			{
				LEX_ANALYSIS::get_token();
				continue;
			}
		}
	}

	new_table->func_params_count = param_count;
	cur_table = new_table;
	table_set.push_back(cur_table);
	//回填参数个数
	//curt = newt;
	//push_back curt




	check(TK_lbrace);
	LEX_ANALYSIS::get_token();

	while (token == KW_const)
	{
		const_decl();
	}
	while (token == KW_int || token == KW_char)
	{
		var_decl();
	}
	while (token != TK_rbrace) {
		statement();
	}

	check(TK_rbrace);
	cur_table = cur_table->father;
	return 0;
}

int Parse::const_decl()
{
	int value;
	int type;
	LEX_ANALYSIS::get_token();
	type = token;
	if (token == KW_int)
	{
		LEX_ANALYSIS::get_token();
		while (1) {
			string name;
			int flag = 1;
			check(TK_ident);
			name = sym;   //const int xxxx 
			LEX_ANALYSIS::get_token();
			check(TK_assign);
			LEX_ANALYSIS::get_token();
			if (token == TK_plus || token == TK_minus)
			{
				flag = (token == TK_plus) ? 1 : -1;
				LEX_ANALYSIS::get_token();
			}
			check(TK_num);
			value = LEX_ANALYSIS::sym_num;
			value = value * flag;
			if (cur_table->insert_const(name, type, value) != 0)
			{
				ERR::error(27, 0); skip_until(TK_semicolon); LEX_ANALYSIS::get_token(); return -1;
			}

			{//local  const   decl
				char i_a[15] = {0};
				itoa(value, i_a,10);
				middle::genmid_var_and_func("CONST", type2str[type], name, i_a);  
			}

			LEX_ANALYSIS::get_token();
			if (token == TK_comma)
			{
				LEX_ANALYSIS::get_token();
				continue;
			}
			else if (token == TK_semicolon)
			{
				LEX_ANALYSIS::get_token();
				break;
			}
			else { ERR::error(5); return -1; }
		}
	}
	else if (token == KW_char)
	{
		LEX_ANALYSIS::get_token();
		string name;
		while (1) {
			name = sym;
			LEX_ANALYSIS::get_token();
			check(TK_assign);
			LEX_ANALYSIS::get_token();
			if (token == TK_cchar)
				value = LEX_ANALYSIS::sym_num;
			if (cur_table->insert_const(name, type, value) != 0) {
				ERR::error(27, 0); skip_until(TK_semicolon); LEX_ANALYSIS::get_token(); return -1;
			}
			
			
			//local  const char  decl
			middle::genmid_var_and_func("CONST", type2str[type], name,to_string( LEX_ANALYSIS::sym_num) );  //update at 12.1 这里一定要传值 ，才能中间代码转换
			

			LEX_ANALYSIS::get_token();
			if (token == TK_comma)
			{
				LEX_ANALYSIS::get_token();
				continue;
			}
			else if (token == TK_semicolon)
			{
				LEX_ANALYSIS::get_token();
				break;

			}
			else { ERR::error(5); return -1; }
		}
	}
	if (PARSE_DEBUG)
		cout << "this is a const declarement statement" << endl;
	return 0;
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
			LEX_ANALYSIS::get_token();
		}
		else len = 0;

		///
		has_count++;
		///
		
		//ins table 
		if (len != 0)
		{
			if(cur_table->insert_array(name, type, len)!=0) ERR::error(27);
			else middle::genmid("ARRAY", type2str[type], "", name);
		}
		else{
			if (cur_table->insert_var(name, type) != 0) ERR::error(27);
			else middle::genmid("VAR", type2str[type], "", name);
		}
		
		
		//ins midcode 

		




		if (token == TK_semicolon) break;
		if (token != TK_comma) {
			ERR::error(16, 0);
			skip_until(TK_semicolon);
			break;
		}
		else {
			LEX_ANALYSIS::get_token();
			continue;
		}
	}


	if (PARSE_DEBUG)
		cout << "this is var_decl line" << " , and we define " << has_count << " of " << LEX_PRINT_KEYS[type] << "kind var(s)"<<endl;
	//midcode return 

	//暂时不要
	
	
	LEX_ANALYSIS::get_token();

	return 0;
}

int Parse::const_sea(int &type, int &result) {
	int flag = 1;
	if (token == TK_plus || token == TK_minus)
	{
		flag = (token == TK_plus) ? 1 : -1;
		LEX_ANALYSIS::get_token();
		if (token == TK_num)
		{
			result = LEX_ANALYSIS::sym_num *flag;
			LEX_ANALYSIS::get_token();
			type = KW_int;
			return 0;
		}
	}
	else if (token == TK_num) {
		result = LEX_ANALYSIS::sym_num;
		LEX_ANALYSIS::get_token();
		type = KW_int;
		return 0;
	}
	else if (token == TK_cchar)
	{
	
		result = LEX_ANALYSIS::sym_num;
		type = KW_char;
		LEX_ANALYSIS::get_token();
		return 0;
	}
	else return -1;
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

		//middle::genmid("GOTO","","",label)

		check(TK_rparen);
		LEX_ANALYSIS::get_token();

		statement();

		if (check(KW_else)==0)//必须有else
		{
			label_true = newlabel();
			//midcode j label2
			//midcode label1

			middle::genmid("GOTO", "", "", label_true);
			middle::genmid("GENLAB", "", "", label_false);


			LEX_ANALYSIS::get_token();
			statement();
			//midcode label2
			middle::genmid("GENLAB", "", "", label_true);

		}
		else{ 
			
			//local_repair
			;//midcode label2
		}
		if (PARSE_DEBUG)
			cout << "this is a if statement" << endl;
	}
	else if (token == KW_do) {
		label_true = newlabel();
		LEX_ANALYSIS::get_token();


		//midcode label1:
		middle::genmid("LOOP", "", "", "");
		middle::genmid("GENLAB", "", "", label_true);

		statement();
		
		check(KW_while);   //WHILE
		LEX_ANALYSIS::get_token();
		check(TK_lparen);

		LEX_ANALYSIS::get_token();
		condition(label_true,"");
		middle::genmid("LOOPEND", "", "", "");
		check(TK_rparen);
		LEX_ANALYSIS::get_token();
		if (PARSE_DEBUG)
			cout << "this is a while statement" << endl;
	}
	else if (token == TK_lbrace) //语句列
	{
		LEX_ANALYSIS::get_token();
		statement();
		while (token !=TK_rbrace)
			statement();
		LEX_ANALYSIS::get_token();

		if (PARSE_DEBUG)
			cout << "this is statement lines" << endl;
	}
	else if (token == KW_switch)
	{
		int type;
		string result;
		string label_case;
		string label_over = newlabel();
		LEX_ANALYSIS::get_token();
		check(TK_lparen);
		LEX_ANALYSIS::get_token();
		if (expression(type, result)!=0) {
			ERR::error(29, 0); skip_until(TK_lbrace); LEX_ANALYSIS::get_token(); return -1;
		}

		check(TK_rparen);
		LEX_ANALYSIS::get_token();
		check(TK_lbrace);
		LEX_ANALYSIS::get_token();
		
		{
			string name;
			int const_value;
			int const_type = 0;

			if (token == KW_default)
			{
				ERR::error(30, 0); skip_until(TK_rbrace); LEX_ANALYSIS::get_token(); return -1;
			}

			check(KW_case);
			LEX_ANALYSIS::get_token();
			
			const_sea(const_type, const_value);
			//midcode
			if(const_type != type)
			{ ERR::error(31, 0); 
				skip_until(TK_rbrace); LEX_ANALYSIS::get_token(); return -1; }
			else {
				label_case = newlabel();
				itoa(const_value, i_swap_s, 10);
				middle::genmid("bne", result, i_swap_s, label_case);
			} //midcode

			check(TK_colon);
			LEX_ANALYSIS::get_token();
//			while (token != KW_case&&token!=KW_default)
//			{
				statement();
//			}
				middle::genmid("GOTO","","",label_over);
				middle::genmid( "GENLAB", "", "", label_case);


			if (PARSE_DEBUG)
				cout << "this is a case" << endl;

			while (token == KW_case)
			{
				LEX_ANALYSIS::get_token();

				const_sea(const_type, const_value);
				//midcode
				if (const_type != type) { ERR::error(31, 0); skip_until(TK_rbrace); LEX_ANALYSIS::get_token(); return -1; }
				else {
					label_case = newlabel();
					itoa(const_value, i_swap_s, 10);
					middle::genmid("bne", result, i_swap_s, label_case);
				}//midcode   case if not
				
				check(TK_colon);
				LEX_ANALYSIS::get_token();

			//	while (token != KW_case && token != KW_default)
			//	{
					statement();
			//	}
				middle::genmid("GOTO", "", "", label_over);
				middle::genmid("GENLAB", "", "", label_case);

				if (PARSE_DEBUG)
					cout << "this is another case" << endl;
				
			}
			if (token == KW_default)
			{
				LEX_ANALYSIS::get_token();
				check(TK_colon);
				LEX_ANALYSIS::get_token();
				statement();
			}
			middle::genmid( "GENLAB", "", "", label_over);

		}


		check(TK_rbrace);
		LEX_ANALYSIS::get_token();



		if (PARSE_DEBUG)
			cout << "this is a switch basket" << endl;

		return 0;

	}
	else if (token == TK_semicolon)
	{
		LEX_ANALYSIS::get_token();
		if (PARSE_DEBUG)
			cout << "this is a blank statement" << endl;
	}
	else if (token == TK_ident) {    //处理赋值语句
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
				
				check(TK_assign);
				LEX_ANALYSIS::get_token();
				int type;
				string expname;
				expression(type, expname);
				//midcode

				middle::genmid("=", expname, "", name);

			}
		}
		else if (cur_table->is_array(name)){
			int type;
			string subscript;
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
						middle::genmid_cal("[]=", expname, subscript, name);
					}//midcode s[i]=expname
				}
			}
		}
		else if (cur_table->is_func(name)/* is a func*/){
			int para_count = 0;
			//get_count
			int should_para_count = table::get_func(name)->func_params_count;
			if (should_para_count == 0)
			{
				middle::genmid("CALL","","",name); //midcode call func  



				if (check(TK_semicolon) != 0)
				{
					if (token == TK_lparen)
						ERR::error(19, 0);
					skip_until(TK_semicolon);
					LEX_ANALYSIS::get_token();
					return -1;
				}
				else ;
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
				else if (para_count != 0)
				{
					param_push_midgen(name, para_count);
				}

				middle::genmid("CALL", "", "", name); //midcode call func  


				check(TK_rparen);
				LEX_ANALYSIS::get_token();
			}
			
		}
		if (check(TK_semicolon) != 0)
			skip_until(TK_semicolon);
		LEX_ANALYSIS::get_token();


		if (PARSE_DEBUG)
			cout << "this is an assignment or call_func" << endl;
		return 0;
	}
	else if (token == KW_scanf)  //SCANF
	{
		string name;
		LEX_ANALYSIS::get_token();
		check(TK_lparen);

		LEX_ANALYSIS::get_token();
		check(TK_ident);
		name = sym;

		if (cur_table->get_type(name) == KW_int)   middle::genmid("SCFI","","",name);/* check table */
		else if (cur_table->get_type(name) == KW_char) middle::genmid("SCFC", "", "", name);
		else {
			ERR::error(20, 0);
			skip_until(TK_semicolon);
			return -1;
		}
		LEX_ANALYSIS::get_token();
		while (token == TK_comma) {
			LEX_ANALYSIS::get_token();
			name = sym;

			if (cur_table->get_type(name) == KW_int)middle::genmid("SCFI", "", "", name);/* check table */
			else if (cur_table->get_type(name) == KW_char)middle::genmid("SCFC", "", "", name);
			else {
				ERR::error(20, 0);
				skip_until(TK_semicolon);
				return -1;
			}

			LEX_ANALYSIS::get_token();
		}
		check(TK_rparen);
		LEX_ANALYSIS::get_token();
		check(TK_semicolon);
		LEX_ANALYSIS::get_token();

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
			int flag = 0;
			int index = 0;
			string res_str;
			for (auto  &it : string_set){
				if ( it == name) {
					flag = 1;
					break;
				}
				index++;
			}
			if (flag)
				res_str = "$string" + to_string(index);
			else {
				res_str = "$string" + to_string(string_set.size());
				string_set.push_back(name);
			}
			middle::genmid("PRTS", "", "", res_str);
			//这里缺少相应语句
			if (PARSE_DEBUG)
				cout << "this is a printf-ing string" << endl;
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

				else if (type == KW_char)
				{
					middle::genmid("PRTC", "", "", name) /*midcode*/;
				}
				else if (type == KW_int) middle::genmid("PRTI", "", "", name)/*midcode*/;
				else
				{
					ERR::error(16, 4);
					return -1;
				}
			}
		}
		else {
			int type;
			string expname;  //这个是expname
			if (expression(type, expname) != 0) { //表达式错误
				ERR::error(21, 4);
				return -1;
			}
			else if (type == KW_char)  middle::genmid("PRTC", "", "", expname)/*midcode*/;
			else if (type == KW_int) middle::genmid("PRTI", "", "", expname)/*midcode*/;
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
	else if (token == KW_return) {
		LEX_ANALYSIS::get_token();
		int type;
		string expname;

		if (cur_table->type == KW_void)
		{
			if(check(TK_semicolon)!=0)
			{
				ERR::error(32, 0);
				skip_until(TK_semicolon);
				LEX_ANALYSIS::get_token();
				return -1;
			}
			LEX_ANALYSIS::get_token();

			middle::genmid("RET", "", "", "");
		}
		else {
			if (check(TK_lparen)!=0) {
				ERR::error(32, 0);
				skip_until(TK_semicolon);
				LEX_ANALYSIS::get_token();
				return -1;
			}
			LEX_ANALYSIS::get_token();
			if (expression(type, expname)!=0 ){
				ERR::error(32, 0);
				skip_until(TK_semicolon);
				LEX_ANALYSIS::get_token();
				return -1;
			}
			else if (cur_table->type != type) {
				ERR::error(32, 0);
				skip_until(TK_semicolon);
				LEX_ANALYSIS::get_token();
				return -1;
			}

			check(TK_rparen);
			LEX_ANALYSIS::get_token();
			check(TK_semicolon);
			LEX_ANALYSIS::get_token();

			middle::genmid("RET", "", "", expname);//midcode
		}
		if (PARSE_DEBUG)
			cout << "this is a return statement" << endl;

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
	string op;
	string expname1;
	string expname2;
	string op_op;
	if (expression(type, expname1) != 0)
	{
		skip_until(TK_rparen);
		return  -1;
	}

	if (LEX_ANALYSIS::is_compop(token))// daiding  gaicheng yunsuanfu
	{
		op = op2str(sym);
		op_op = opposite_op(sym);

		LEX_ANALYSIS::get_token();
		if (expression(type, expname2) != 0)
		{
			skip_until(TK_rparen);
			//这里没有LEX_ANALYSIS::get_token();

			return  -1;
		}
		if (true_label != "")
			middle::genmid_comp(op,expname1,expname2,true_label); // midcode
		else
			middle::genmid_comp(op_op,expname1,expname2,false_label); // midcode
	}
	else {
		if (true_label != "")
			middle::genmid("bne",expname1,"0",true_label); // midcode
		if (false_label != "")
			middle::genmid("beq",expname1,"0",false_label); // midcode
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
	int uselesstype;
	if (token == TK_plus || token == TK_minus) {

		if (token == TK_plus) {
			LEX_ANALYSIS::get_token();
			if (term(type, term1) != 0) 
				return -1;
			if (term1 != "")
			{
				result = new_local_t();
				middle::genmid_cal("+",term1,"0",result) ;//midcode
			}
		}
		else if (token == TK_minus)
		{
			LEX_ANALYSIS::get_token();
			if (term(type, term1) != 0)
				return -1;
			if (term1 != "")
			{
				result = new_local_t();
				middle::genmid_cal("-","0",term1, result);
				;//midcode
			}
		} 
		type = KW_int;
		term1 = result;
	}
	else {
		if (term(type, term1) != 0) return -1;
		result = term1;
	}
	while (token == TK_plus || token == TK_minus) {
		type = KW_int;
		if (token == TK_plus) {
			LEX_ANALYSIS::get_token();
			if (term(uselesstype, term2) != 0)
				return -1;
			if (term1 != "")
			{
				result = new_local_t();
				middle::genmid_cal("+", term1, term2, result);
				term1 = result;//midcode
				continue;
			}
		}
		else if (token == TK_minus)
		{
			LEX_ANALYSIS::get_token();
			if (term(uselesstype, term2) != 0)
				return -1;
			if (term1 != "")
			{
				result = new_local_t();
				middle::genmid_cal("-", term1, term2, result);
				term1 = result;//midcode
				continue;
			}
		}
	}
/*
	if (PARSE_DEBUG)
		cout << "this is a expression " << endl;*/
	
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
		opcode = sym;
		LEX_ANALYSIS::get_token();
		if (factor(type, fact2) != 0) return -1;

		result = new_local_t();
		//midcode
		middle::genmid_cal(opcode, fact1, fact2, result);
		fact1 = result;

		type = KW_int;
	}
	/*
	if (PARSE_DEBUG)
		cout << "this is a term " << endl;
	*/
	return 0;
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
			int  type1=0;
			LEX_ANALYSIS::get_token();
			type = cur_table->get_type(name);
			check(TK_lbrack);
			LEX_ANALYSIS::get_token();
		    if (expression(type1, subscript) != 0) {
				ERR::error(23, 0);
				skip_until(TK_rbrack);
				LEX_ANALYSIS::get_token();
				return -1;
			}
			offset = LEX_ANALYSIS::sym_num;  //这里稍微有问题

			/*如果数组溢出,要报错*/
			/*if (offset >= (cur_table->get_et(name)).value)
			{
				ERR::error(23, 0);
				skip_until(TK_rbrack);
				//这里不能有 LEX_ANALYSIS::get_token();
				return -1;
			} */
			/*overflow end*/
			result = new_local_t();
			//midcode
			middle::genmid_cal("=[]", name, subscript, result);

			check(TK_rbrack);
			LEX_ANALYSIS::get_token();
		}
		else if (cur_table->is_var(name)|| cur_table->is_const(name))//is_var
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
				else if (params_num != 0)
				{
					param_push_midgen(name,params_num);
				}

				check(TK_rparen);
				LEX_ANALYSIS::get_token();
				//这里千万注意别重复读下一个字符

			}
			//midcode callfunc
			//assign

			middle::genmid("CALL", "", "", func_t->name);
			result = new_local_t();
			middle::genmid("=", "$RET", "", result);
			
		}
		else
		{
			ERR::error(24);
			skip_until(TK_semicolon);
			//LEX_ANALYSIS::get_token();
			return -1;
		}
	}
	else if (token == TK_plus || token == TK_minus) {   //整数
		int flag = 0;
		type = KW_int;
		if (token == TK_minus)
			flag = 1;
		LEX_ANALYSIS::get_token();
		if (check(TK_num) != 0) result = "0";//TODO
		else if (flag)
			result = "-" + to_string(LEX_ANALYSIS::sym_num);
		else result = to_string(LEX_ANALYSIS::sym_num);
		LEX_ANALYSIS::get_token();

	}
	else if (token == TK_num) {
		result = to_string(LEX_ANALYSIS::sym_num);
		type = KW_int;
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
		result = to_string(LEX_ANALYSIS::sym_num);
		LEX_ANALYSIS::get_token();
	}
	else
	{
		ERR::error(25, 4);
	}
	if (before_errc != err_count)
		return -1;
	/*
	if (PARSE_DEBUG)
		cout << "this is a factor" << endl;
	*/
	return 0;
}


stack<string> param_stack_in, param_stack_out;
int Parse::params_pass(string name) {
	int type;
	int param_num=0;
	string expname;
	if (token == TK_rparen) {
		return param_num;
	}
	if(expression(type, expname)!=0) return -1;
	// 查表项
	
	param_stack_in.push(expname);

	//middle::genmid_var_and_func("PUSH", "", name, expname);

	param_num++;
	while (token == TK_comma)
	{
		LEX_ANALYSIS::get_token();
		expression(type, expname);
		param_num++;
		param_stack_in.push(expname);
		//middle::genmid_var_and_func("PUSH", "", name, expname);
		//midcode
	}
	return param_num;
}
int Parse::param_push_midgen(string name,int count) {
	string temp;
	for (int i = 0; i < count; i++)
	{
		temp = param_stack_in.top();
		param_stack_in.pop();
		param_stack_out.push(temp);
	}
	while (!param_stack_out.empty()) {
		temp = param_stack_out.top();
		middle::genmid_var_and_func("PUSH", "", name, temp);
		param_stack_out.pop();
	}
	return 0;
}




