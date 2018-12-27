#include "Targetmips.h"
#include <algorithm>    
#define  RESERVED_SIZE 40
#define TARGET_DEBUG 0
table* cur_mips_table;
table* call_table;

int RefWeight = 1;
int mid_line_count = 0;
int param_ptr=0;
string funcname;

int cur_func_tbz;

string opcode="";
string mid_a="";
string mid_b="";
string mid_c="";

string regs[] = { "$0", "$1", "$v0" , "$v1","$a0","$a1" ,"$a2" ,"$a3" ,"$t0" ,"$t1" ,"$t2" ,\
				  "$t3" ,"$t4" ,"$t5" ,"$t6" ,"$t7" ,"$s0" ,"$s1","$s2" ,"$s3" ,"$s4" ,
				  "$s5" ,"$s6" ,"$s7" ,  "$t8", "$t9", "$k0", "$k1", "$gp", \
				  "$sp", "$fp", "$ra" };
map <string, string >calop;  //加减乘除对应运算
map <int, string >Tpool;
bool mipsT[10] = { false }; //用于标记临时寄存器是否被使用
bool dirtyT[10] = { false };
temp_stack tp_stack;
int  temp_stack::top_flag = 0 ;


int reset_Regpool() {
	for (int i = 0; i < 10; i++)
	{
		mipsT[i] = false;
		dirtyT[i] = false;
		Tpool[i] = "";
	}
	return 0;
}
int reset_Reg(string reg,string name) {
	int i;
	i =  reg[2] - '0';
	mipsT[i] = false;
	dirtyT[i] = false;
	Tpool[i] = "";

	mips_output << "sw " << reg << " , " << cur_mips_table->get_addr(name) << endl;
	return 0;
}

bool is_local_var(string name) {
	for (auto &it : cur_mips_table->entries) {
		if (it.name == name)
		{
			if (it.kind == VAR ||it.kind==PARAM )
				return true;
			else return false;
		}
	}
	return false;
}

bool is_imm(string name) {
	return name[0] == '-' || (name[0] >= '0'&&name[0] <= '9');
}
bool is_cal(string op) {
	return op == "+" || op == "/" || op == "*" || op == "-";
}
void read_mid(int lc) {
	opcode = midcode[lc].opcode;
	mid_a = midcode[lc].a_op;
	mid_b = midcode[lc].b_op;
	mid_c = midcode[lc].c_op;
}
bool is_temp(string mid_element) {
	return mid_element =="0" ||(mid_element[0] == '@')||mid_element=="$RET" ;
}

//temp_stack tp_stack;



void storeT_intoStack(string name) {
	string store_T;
	int index;
	for (auto &it : Tpool) {
		if (it.second == name)
		{
			store_T = "$t" + to_string(it.first);
			index = it.first;
		}
	}
	if (dirtyT[index] == true) {
		mips_output << "sw " << store_T << ", "<<cur_mips_table->get_addr(name) << endl;  //都要存回原位置
	}
	dirtyT[index] = false;

	tp_stack.pushT(name);//这句话是有必要的，为了在第一次用一个temp或者局部变量的时候，不从内存lw
/*
	tp_stack.pushT(name);
	mips_output << "addi $sp,$sp, -4" << endl;
	mips_output << "sw " << store_T << ", 0($sp) " << endl;
*/
	return;
}
//将临时寄存器的值存入 栈中相应位置，这里要注意，如果Dirty位不是1 ，就不存了,OS思想
//不见得只存在stack里，可能存在全局里
string askT_R(string name ,int dirty = 0 ) {
	static int ask_flag = 0;
	int location=0;
	
	if (ask_flag == 10)
		ask_flag = 0;
	
	for (int i = 0; i < 10; i++) 
		if (!mipsT[i]) { 
			mipsT[i] = true; 
			Tpool[i] = name;
			if (tp_stack.find_inStack(name)) {
				mips_output << "lw " << "$t" + to_string(i) << ", " << cur_mips_table->get_addr(name) << endl;//这里也需要读栈
				if (TARGET_DEBUG)
					cout << "location :" << location << "   tablesize is:" << cur_mips_table->tablesize << "    " << endl;
			}
			if (dirty)
			{
				dirtyT[i] = true;
				tp_stack.pushT(name);
			}
			return "$t" + to_string((i++)%10) ; 
		}


	//存栈,或者存回内存 , local / temp / global
	if(dirtyT[ask_flag%10]==true )
		storeT_intoStack(Tpool[ask_flag % 10]);


	if ( tp_stack.find_inStack(name)) {
		mips_output << "lw " << "$t" + to_string(ask_flag%10) <<", "<< cur_mips_table->get_addr(name)<< endl;//把栈中的内容读进这个寄存器
		if (TARGET_DEBUG)
			cout << "location :" << location << "   tablesize is:" << cur_mips_table->tablesize << "    " << endl;

	}


	Tpool[ask_flag%10] = name ;  //赋值
	mipsT[ask_flag%10] = true;
	if (dirty == 1) {
		dirtyT[ask_flag % 10] = true;
		tp_stack.pushT(name);
	}


	return "$t"+to_string((ask_flag++) % 10);
}

string getT_R(string name,int dirty=0) {
	if (name == "0") return "$0";
	if (name == "$RET")return "$v1";
	for (auto &it : Tpool){
		if (it.second == name &&mipsT[it.first]==true) {
			if (dirty)
				dirtyT[it.first] = true;
			return "$t" + to_string(it.first);
		}
	}
	return askT_R(name,dirty);
}







void save_current() {
/*	int offset = -4;
	for (int i = 8; i < 32; i++ )
	{
		if (i != 28 && i != 29 && i != 30)
		{
			mips_output << "sw " << regs[i] << " , " << offset << "($sp)" << endl;
			offset -= 4;
		}
	}
*/
	int index = 0;
	for (; index < 10; index++)
	{
		if (dirtyT[index] == true)
			mips_output << "sw $t" << index << " , " << cur_mips_table->get_addr(Tpool[index]) << endl;
		dirtyT[index] = false;
	}
	mips_output << "sw  $s0,  -4($sp)" << endl;
	mips_output << "sw  $s1,  -8($sp)" << endl;
	mips_output << "sw  $s2,  -12($sp)" << endl;
	mips_output << "sw  $s3,  -16($sp)" << endl;
	mips_output << "sw  $s4,  -20($sp)" << endl;
	mips_output << "sw  $s5,  -24($sp)" << endl;
	mips_output << "sw  $s6,  -28($sp)" << endl;
	mips_output << "sw  $s7,  -32($sp)" << endl;
	mips_output << "sw  $ra,  -36($sp)" << endl;
	mips_output << "sw  $fp,  -40($sp)" << endl;

	mips_output << "addi  $sp,$sp ," << -RESERVED_SIZE << endl;

	return;

}
void refresh_current() {
/*	int offset = 4;
	for (int i = 31; i >= 8 ; i--) {
		if (i != 28 && i != 29 && i != 30)
		{
			mips_output << "lw " << regs[i] << " , " << offset << "($fp)" << endl;
			offset += 4;
		}
	}
*/
	mips_output << "lw  $s0,  36($fp)" << endl;
	mips_output << "lw  $s1,  32($fp)" << endl;
	mips_output << "lw  $s2,  28($fp)" << endl;
	mips_output << "lw  $s3,  24($fp)" << endl;
	mips_output << "lw  $s4,  20($fp)" << endl;
	mips_output << "lw  $s5,  16($fp)" << endl;
	mips_output << "lw  $s6,  12($fp)" << endl;
	mips_output << "lw  $s7,  8($fp)" << endl;
	mips_output << "lw  $ra,  4($fp)" << endl;
	mips_output << "lw  $fp,  0($fp)" << endl;


	return;

}


void init() {
	calop.insert(pair<string, string>("+", "add"));
	calop.insert(pair<string, string>("-", "sub")); 
	calop.insert(pair<string, string>("*", "mul"));
	calop.insert(pair<string, string>("/", "div"));
	return;
}


/* refcount opt  begin */
typedef pair<string, int> PAIR;
bool cmp_by_value(const PAIR& lhs, const PAIR& rhs) {
	return lhs.second > rhs.second;
}
void refopt() {
	mid_line_count = 0;
	map<string, int> cnt_map;
	vector<PAIR> sort_vec;
	while (1)
	{	
		if (mid_line_count >= midcode.size())
			break;
		read_mid(mid_line_count++);

		if (opcode == "FUNC") {
			cnt_map.clear();
			sort_vec.clear();
			for (auto &t : table_set) {
				if (t->name == mid_c)
					cur_mips_table = t;
			}//找到符号表


			for(;midcode[mid_line_count].opcode != "FUNC"&&mid_line_count<midcode.size()-1; \
					mid_line_count++){
				read_mid(mid_line_count);
				if (midcode[mid_line_count].opcode == "LOOP") {
					RefWeight *= 5;
					continue;
				}
				else if (midcode[mid_line_count].opcode == "LOOPEND") {
					RefWeight /= 5;
					continue;
				}


				if (is_local_var(mid_b))
					cnt_map[mid_b]+=RefWeight;
				if (is_local_var(mid_a))
					cnt_map[mid_a]+=RefWeight;
				if (is_local_var(mid_c))
					cnt_map[mid_c]+=RefWeight;

			}
			for (auto &it : cnt_map)
				sort_vec.push_back(make_pair(it.first, it.second));
			sort(sort_vec.begin(), sort_vec.end(), cmp_by_value);

			for (int i = 0; i < 8 && i<sort_vec.size() ; i++)
			{
				cur_mips_table->local_s_pool[i] = sort_vec[i].first;
			}



		}

	}
	return;
}
/*******************
 *   这里暂时用的引用计数方法，后期也许会进行更改？
 *    不要动上面两个函数
 *
 *
 *
 *
 *
*/



/*  refcount_opt  end */
int Targetmips::generator(string filename){
	int total_midcount = midcode.size();
	

	mips_output.open(filename);
	
	
	init();


	refopt();
	cur_mips_table = table_set[0];// point to global
	
	mid_line_count = 0;


	mips_output << ".data" << endl;
	for (auto &item : cur_mips_table->entries) {
		if (item.kind == VAR)
			mips_output << item.name << ":" << "  .space  4" << endl;
		else if (item.kind == ARR)
			mips_output << item.name << ":" << "  .space  " << item.value * 4 << endl;
		else if (item.kind == CONST)
			mips_output << item.name << ":" << "  .word   " << item.value << endl;
	}
	int i=0;
	for (auto &str : string_set) {
		mips_output << "$string" + to_string(i) << "  :  " << ".asciiz  " << "\"" << str << "\"" << endl;
		i++;
	}



	mips_output << ".text" << endl;
	mips_output << "li $gp ,0x10010000" << endl;
	mips_output << "j main" << endl << endl << endl ;
	
	////reset
	tp_stack.reset();
	reset_Regpool();
	////reset

	for (mid_line_count = 0; mid_line_count < total_midcount; mid_line_count++) {
	//	read_mid(mid_line_count);
	//	if (opcode == "CONST")
	//	{
	//		mips_output <<"li"
	//	}
	//
		if (midcode[mid_line_count].opcode == "FUNC")
			break;
	}
	//开始进入函数
	while (mid_line_count < total_midcount) {
		read_mid(mid_line_count++);//每次读入一行，这里读的是第一行 func
		for (auto &t : table_set) {
			if (t->name == mid_c)
			{
				cur_mips_table = t;
				break;
			}
		}//找到符号表
		
		////reset 看好函数的头，就可以实现刷新寄存器们，因为不能保证return 函数只有一个
		tp_stack.reset();
		reset_Regpool();
		////reset

		mips_output << mid_c << ":" << endl;//函数标签		
		mips_output << "add $fp,$sp,$0 " << endl;  //!!!!fp0 是第一个参数
		
		int all_size = cur_mips_table->tablesize + cur_mips_table->stacksize;
		if(all_size!=0)
			mips_output << "addi $sp ,$sp , -" << all_size << endl;
		
		


		for (int i = 0; i < (int) cur_mips_table->entries.size(); i++) {
			string name;
			if (cur_mips_table->entries[i].kind == PARAM)
			{
				name = cur_mips_table->entries[i].name;
				if (cur_mips_table->find_sreg(name))
					mips_output << "lw " << cur_mips_table->get_sreg(name) << " , " << cur_mips_table->get_addr(name) << endl;
			}
		}//先读取参数到寄存器中
		while ( mid_line_count < total_midcount) {
			read_mid(mid_line_count++);  //readline
			if (opcode == "FUNC") {
				mid_line_count--;
				/////reset
				tp_stack.reset();
				reset_Regpool();
				/////reset
				break;//读到另一个函数的开始，退出

			}
			//如果是运算符
			if (is_cal(opcode))// + - * /
			{
				string reg1,reg2,reg3;
				string target;
				if (mid_a == "$RET")	reg1 = "$v1";
				else if ( is_imm(mid_a) ) {
					reg1 = "$a3";
					mips_output << "li   $a3 ,  " << mid_a << endl;
				}//如果是立即数
				else if (cur_mips_table->find_sreg(mid_a)) {
					reg1 = cur_mips_table->get_sreg(mid_a) ;
				}
				else if (is_temp(mid_a)) {   //代表已经存进 Tpool 中
					reg1 = getT_R(mid_a);
				}//temp 
				else {
					//reg1 = "$a3";
					reg1 = getT_R(mid_a);
					mips_output << "lw  " << reg1 << " , " << cur_mips_table->get_addr(mid_a) << endl;
				}
				if (mid_b == "$RET") reg2 = "$v1";
				else if (is_imm(mid_b)) reg2 = mid_b;
				else if (cur_mips_table->find_sreg(mid_b)) {
					reg2 = cur_mips_table->get_sreg(mid_b);
				}
				else if (is_temp(mid_b)) { reg2 = getT_R(mid_b); }
				else {
					reg2 = getT_R(mid_b);//这里要改,应该是把其他的改成这个
					mips_output << "lw  " << reg2 << " , " << cur_mips_table->get_addr(mid_b) << endl;
				}
				//
				if (is_temp(mid_c)) {
					reg3 = getT_R(mid_c,1); //insert
					mips_output << calop[opcode] << "  " << reg3 << " , " << reg1 << " , " << reg2 << endl;

				}
				else if (cur_mips_table->find_sreg(mid_c)) {
					reg3 = cur_mips_table->get_sreg(mid_c);
					mips_output << calop[opcode] << "  " << reg3 << " , " << reg1 << " , " << reg2 << endl;
				}
				else {
					reg3 = getT_R(mid_c, 1);
					mips_output << calop[opcode] << "  "<<  reg3 << " , " << reg1 << " , " << reg2 << endl;
					reset_Reg(reg3, mid_c);
					//mips_output << "sw  $a3 , " << cur_mips_table->get_addr(mid_c) << endl;
				}



			}

			else if (opcode == "=") {  //assgin   1. c= return  2. c= imm 3. c= $ 4.  c= memory   
				bool flag = false;
				string reg3, reg1;
				if (is_temp(mid_c)) {
					reg3 = getT_R(mid_c, 1);
				}
				else if (cur_mips_table->find_sreg(mid_c)) {
					reg3 = cur_mips_table->get_sreg(mid_c);
				}
				else {
					reg3 = "$a2";
					flag = true;
				}

				if (mid_a == "$RET")
					reg1 = "$v1";
				else if (is_imm(mid_a)) {
					reg1 = mid_a;
					mips_output << "li " << reg3 << " , " << mid_a << endl;
					if (flag)
						mips_output << "sw $a2," << cur_mips_table->get_addr(mid_c) << endl;
					continue;
				}
				else if (cur_mips_table->find_sreg(mid_a))
					reg1 = cur_mips_table->get_sreg(mid_a);
//					mips_output << "move " << reg3 << " , " << cur_mips_table->get_sreg(mid_a) << endl;
				else if (is_temp(mid_a))
				{
					reg1 = getT_R(mid_a);
				}
				else {
					mips_output << "lw " << reg3 << " , " << cur_mips_table->get_addr(mid_a) << endl;
					if (flag)
						mips_output << "sw $a2," << cur_mips_table->get_addr(mid_c) << endl;
					continue;
				}
				
				mips_output << "move " << reg3 << " , " << reg1 << endl;
				if (flag)
					mips_output << "sw $a2," << cur_mips_table->get_addr(mid_c) << endl;


			}
			//no problem

			else if (opcode == "PRTI") {
				if (is_imm(mid_c))
					mips_output << "li $a0, " << mid_c << endl;
				else if (is_temp(mid_c))
					mips_output << "move $a0, " << getT_R(mid_c) << endl;
				else if (cur_mips_table->find_sreg(mid_c))
					mips_output << "move $a0, " << cur_mips_table->get_sreg(mid_c) << endl;
				else
					mips_output << "lw $a0, " << cur_mips_table->get_addr(mid_c) << endl;
				mips_output << "li $v0 , 1" << endl;
				mips_output << "syscall" << endl;
			}
/*			else if (opcode == "CONST") {
			
					mips_output << "li $a3 ," <<mid_c << endl;
					mips_output << "sw $a3 ,"  << cur_mips_table ->get_addr(mid_b) << endl;
			}   要在生成中间代码阶段做这件事情
*/
			else if (opcode == "PRTC") {
				if (is_imm(mid_c))
					mips_output << "li $a0, " <<mid_c<< endl;
				else if (is_temp(mid_c))
					mips_output << "move $a0, " << getT_R(mid_c) << endl;
				else if (cur_mips_table->find_sreg(mid_c))
					mips_output << "move $a0, " << cur_mips_table->get_sreg(mid_c) << endl;
				else
					mips_output << "lw $a0, " << cur_mips_table->get_addr(mid_c) << endl;
				mips_output << "li $v0,11" << endl;
				mips_output << "syscall" << endl;
			}
			else if (opcode == "PRTS") {
				
				mips_output << "la $a0," << mid_c << endl;
				mips_output << "li $v0,4" << endl;
				mips_output << "syscall" << endl;
			}
			else if (opcode == "SCFC") {
				mips_output << "li $v0 ,12" << endl;
				mips_output << "syscall" << endl;
				mips_output << "move $v1, $v0" << endl;
				if (cur_mips_table->find_sreg(mid_c)) 
					mips_output << "move " << cur_mips_table->get_sreg(mid_c) << " , $v1 " << endl;
				else
					mips_output << "sw $v1 ," << cur_mips_table->get_addr(mid_c) << endl;
			}
			else if (opcode == "SCFI") {
				mips_output << "li $v0, 5" << endl;
				mips_output << "syscall" << endl;
				mips_output << "move $v1, $v0" << endl;
				if (cur_mips_table->find_sreg(mid_c))
					mips_output << "move " << cur_mips_table->get_sreg(mid_c) << ", $v1"<<endl;
				else
					mips_output << "sw $v1, " << cur_mips_table->get_addr(mid_c) << endl;
			}
			else if (opcode == "GOTO") {
				mips_output << "j " << mid_c << endl;
			}
			else if (opcode == "GENLAB") {
				mips_output << mid_c + ":" << endl;
			}
			else if (opcode == "=[]")
			{
				bool flag=false;
				string reg2 ,reg3;  //中间变量 或者 普通变量  或者 全局变量
				if (is_temp(mid_c))
				{
					reg3 = getT_R(mid_c,1);
				}
				else if (cur_mips_table->find_sreg(mid_c))
				{
					reg3 = cur_mips_table->get_sreg(mid_c);
				}
				else {
					reg3 = "$a2";
					flag = true;
				}//get  reg3 
				

				if(cur_mips_table->is_local(mid_a))
					mips_output << "addi $a3 , $fp , " << cur_mips_table->get_a_offset(mid_a) << endl;
				else {
					mips_output << "la $a3 ,  " << mid_a << endl;
				}

				if (is_imm(mid_b))
				{
					mips_output << "lw "<<reg3 <<" , " << stoi(mid_b) * 4 <<"($a3)" <<endl;
					if (flag)
						mips_output << "sw $a2," << cur_mips_table->get_addr(mid_c) << endl;
					continue;
				}
				else if (is_temp(mid_b)) {/////需要处理
					reg2 = getT_R(mid_b);//找到临时变量的寄存器
				}
				else if (cur_mips_table->find_sreg(mid_b))
				{
					reg2 = cur_mips_table->get_sreg(mid_b);
				}
				else {
					reg2 = getT_R(mid_b);
					mips_output << "lw "<<reg2<<" , " << cur_mips_table->get_addr(mid_b) << endl;
				}
				mips_output << "sll $a2, " << reg2 << ",2" << endl;
				mips_output << "add $a3,$a2,$a3" << endl;
				mips_output << "lw " << reg3 << " , " << "0($a3)" << endl;
				if (flag)
					mips_output << "sw $a2," << cur_mips_table->get_addr(mid_c) << endl;
			}
/*待优化 []= 具体方法为imm时的 存取*/
			else if (opcode == "[]="){
				string reg1,reg2;

				if(cur_mips_table->is_local(mid_c))
					mips_output << "addi $a3 ,$fp ," << cur_mips_table->get_a_offset(mid_c) << endl;
				else mips_output << "la $a3 ,   " << mid_c << endl;
				// c is local or global array
				if (is_imm(mid_b) && mid_b!="0" ) {
					mips_output << "addi $a3 , $a3 , " << stoi(mid_b)*4 << endl;
				}
				else if (is_temp(mid_b)) {
					reg2 = getT_R(mid_b);
					mips_output << "sll $a2," << reg2 << ",2" << endl;
					mips_output << "add $a3,$a3,$a2" << endl;
				}
				else if (cur_mips_table->find_sreg(mid_b)) {
					reg2 = cur_mips_table->get_sreg(mid_b);
					mips_output << "sll $a2, " << reg2 << " , 2" << endl;
					mips_output << "add $a3,$a3,$a2" << endl;
				}
				else {
					reg2 = getT_R(mid_b);
					mips_output << "lw " << reg2 << " , " << cur_mips_table->get_addr(mid_b) << endl;
					mips_output << "sll $a2, $a2, 2" << endl;
					mips_output << "add $a3,$a3,$a2" << endl;
				}
				//b is temp or sreg or imm or global&local 

				if (is_imm(mid_a))
				{
					mips_output << "li $a2," << mid_a << endl;
					mips_output << "sw $a2,0($a3)"   << endl;
				}
				else if (cur_mips_table->find_sreg(mid_a)) {
					reg1 = cur_mips_table->get_sreg(mid_a);
					mips_output << "sw "<< reg1 <<" , 0($a3)" << endl;
				}
				else if(is_temp(mid_a)){//是临时变量}
					reg1 = getT_R(mid_a) ;
					mips_output << "sw " << reg1 << " , 0($a3)" << endl;
				}
				else {
					mips_output << "lw $a2," << cur_mips_table->get_addr(mid_a) << endl;
					
					mips_output << "sw $a2,0($a3)" << endl;
				}
			}
			else if (opcode == "RET")
			{
				if (mid_c != "") {
					if (is_imm(mid_c))
					{
						mips_output << "li $v1 ," << mid_c << endl;
					}
					else if (cur_mips_table->find_sreg(mid_c))
					{
						mips_output << "move $v1 ," << cur_mips_table->get_sreg(mid_c) << endl;
					}
					else if (is_temp(mid_c))
					{
						mips_output<<"move $v1, "<<getT_R(mid_c)<<endl;
					}
					else {
						mips_output << "lw $v1 , " << cur_mips_table->get_addr(mid_c) << endl;
					}
				}
				if (cur_mips_table->name != "main")
				{
					mips_output <<"addi $sp , $fp ,"<<RESERVED_SIZE << endl;
					mips_output << "jr $ra" << endl;
				}
				else {
					mips_output << "li $v0 ,10" << endl << "syscall" << endl;
				}

			 }
			else if (is_comp(opcode)) {
			string reg1;
			string reg2;
				if (is_imm(mid_a)) {
					mips_output << "li $a3 , " << mid_a << endl;
					reg1 = "$a3";
				}
				else if (cur_mips_table->find_sreg(mid_a))
				{
					reg1 = cur_mips_table->get_sreg(mid_a);
				}
				else if (is_temp(mid_a)) {
					reg1 = getT_R(mid_a);
				}
				else {
					reg1 = getT_R(mid_a);
					mips_output << "lw "<<reg1<<" , " << cur_mips_table->get_addr(mid_a) << endl;
				}//rs
				if (is_imm(mid_b)) {
					mips_output<< opcode <<" "<<reg1 <<" , "<< mid_b <<" ," <<mid_c<<endl;

					continue;
				}
				else if (cur_mips_table->find_sreg(mid_b))
				{
					reg2= cur_mips_table->get_sreg(mid_b);
				}
				else if (is_temp(mid_b)) {
					reg2 = getT_R(mid_b);
				}
				else {
					reg2 = getT_R(mid_b);
					mips_output << "lw "<<reg2<< " , " << cur_mips_table->get_addr(mid_b) << endl;
				}
				mips_output << opcode << " " << reg1 << " , " << reg2 << " , " << mid_c << endl;

			}
			else if (opcode == "CALL") {
				int args_count;
				int stack_size;
				for (auto &t : table_set) {
					if (t->name == mid_c)
					{
						call_table = t; break;
					}
				}
				args_count = call_table->func_params_count;
				stack_size = call_table->tablesize;

				save_current();

				//这里只reset寄存器pool，因为记录第一次调用的pool依然有用
				reset_Regpool();
				//reset

				mips_output << " jal " << mid_c << endl;
				refresh_current();
				

				param_ptr = 0;//important

			}
			else if (opcode == "PUSH") {
				string reg3;
				if (is_imm(mid_c)) {
					mips_output << "li $a3 , " << mid_c << endl;
					reg3 = "$a3";
				}
				else if (is_temp(mid_c))
				{
					reg3 = getT_R(mid_c);
				}
				else if (cur_mips_table->find_sreg(mid_c))
				{
					reg3 = cur_mips_table->get_sreg(mid_c);
				}
				else {
					reg3 = "$a3";
					mips_output << "lw $a3 , " << cur_mips_table->get_addr(mid_c) << endl;
				}
				param_ptr -= 4;//		
				mips_output<<"sw "<<reg3<<" , "<< to_string( param_ptr-RESERVED_SIZE ) + "($sp)" << endl;
				
					
			}
			
		}

		mips_output << "addi $sp , $fp ,"<<RESERVED_SIZE << endl;
		if (cur_mips_table->name == "main") {//函数结束
			mips_output << "li $v0 ,10" << endl << "syscall" << endl;
		}
		else {
			mips_output << "jr $ra" << endl;
		}

	}
	

	mips_output.close();
	return 0;
}


void temp_stack::pushT(string name)
{
	if (top_flag == 100)
		cout << "太多临时变量，增加数组容量!\n" << endl;
	for (int index = 0; index < top_flag; index++) {
		if (temp_name[index] == name)
			return;
	}
	temp_name[top_flag++] = name ;
	return;
}
void temp_stack::reset()
{
	this->top_flag = 0;
	return;
}
bool temp_stack::find_inStack(string name)
{
	for (int i = 0; i < this->top_flag; i++) {
		if (temp_name[i] == name)
			return  true ;
	}
	return false;
}
