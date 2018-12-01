#include "Targetmips.h"
#include <algorithm>    
#define  RESERVED_SIZE 96 

table* cur_mips_table;
table* call_table;

bool mipsT[10] = { false };
int RefWeight = 1;
int mid_line_count = 0;
int param_ptr=0;
string funcname;

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





int reset_Regpool() {
	for (int i = 0; i < 10; i++)mipsT[i] = false;
	return 0;
}
int reset_Reg(string reg) {
	int i;
	i =  reg[2] - '0';
	mipsT[i] = false;
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
bool is_comp(string name) {
	return name == "bne" || name == "beq" || name == "blt" || name == "ble" \
		||name =="bgt" || name == "bge";
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


string askT_R(string name ) {
	static int ask_flag = 0;
	for (int i = 0; i < 10; i++) if (!mipsT[i]) { mipsT[i] = true; Tpool[ask_flag] = name; return "$t" + to_string((ask_flag++)%10) ; }

	
	Tpool[ask_flag%10] = name ;  //赋值
	mipsT[ask_flag%10] = true;

	return "$t"+to_string((ask_flag++) % 10);

}
string getT_R(string name) {
	if (name == "0") return "$0";
	if (name == "$RET")return "$v0";
	for (auto &it : Tpool){
		if (it.second == name)
			return "$t" + to_string(it.first);
	}
	return askT_R(name);
}

void save_current() {
	int offset = -4;
	for (int i = 8; i < 32; i++ , offset-=4)
	{
		if(i != 28 && i!=29)
			mips_output << "sw " << regs[i] << " , " << offset << "($sp)" << endl;
	}
	return;

}
void refresh_current() {
	int offset = 0;
	for (int i = 31; i >= 8 ; i--, offset += 4) {
		if (i != 28 && i != 29)
			mips_output << "lw " << regs[i] << " , " << offset<<"($sp)" << endl;
	}
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

/*  refcount_opt  end */
int Targetmips::generator(){
	int total_midcount = midcode.size();
	init();
	reset_Regpool();
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

	while (mid_line_count < total_midcount) {
		read_mid(mid_line_count++);


		for (auto &t : table_set) {
			if (t->name == mid_c)
			{
				cur_mips_table = t;
				break;
			}
		}//找到符号表
		mips_output << mid_c << ":" << endl;
		mips_output << "subi $sp ,$sp , " << cur_mips_table->tablesize<<endl;
		mips_output << "move $fp,$sp" << endl;

	//	mips_output << funcname << "move $fp,$sp" << endl;
	//	mips_output << "add  $sp , $sp ,-" << cur_mips_table->tablesize<<endl;
		for (int i = 0; i < (int) cur_mips_table->entries.size(); i++) {
			string name;
			if (cur_mips_table->entries[i].kind == PARAM)
			{
				name = cur_mips_table->entries[i].name;
				if (cur_mips_table->find_sreg(name))
					mips_output << "lw " << cur_mips_table->get_sreg(name) << " , " << cur_mips_table->get_addr(name) << endl;
			}
		}
		while ( mid_line_count < total_midcount) {
			read_mid(mid_line_count++);  //readline
			if (opcode == "FUNC") {
				mid_line_count--;
				break;
			}

			if (is_cal(opcode))// + - * /
			{
				string reg1,reg2,reg3;
				string target;
				if (mid_a == "$RET")	reg1 = "$v0";
				else if ( is_imm(mid_a) ) {
					reg1 = "$a3";
					mips_output << "li   $a3 ,  " << mid_a << endl;
				}
				else if (cur_mips_table->find_sreg(mid_a)) {
					reg1 = cur_mips_table->get_sreg(mid_a) ;
				}
				else if (is_temp(mid_a)) {
					reg1 = getT_R(mid_a);
				}//temp
				else {
					reg1 = "$a3";
					mips_output << "lw  " << reg1 << " , " << cur_mips_table->get_addr(mid_a) << endl;
				}
				if (mid_b == "$RET") reg2 = "$v0";
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
					reg3 = getT_R(mid_c); //insert
					mips_output << calop[opcode] << "  " << reg3 << " , " << reg1 << " , " << reg2 << endl;
				}
				else if (cur_mips_table->find_sreg(mid_c)) {
					reg3 = cur_mips_table->get_sreg(mid_c);
					mips_output << calop[opcode] << "  " << reg3 << " , " << reg1 << " , " << reg2 << endl;
				}
				else {
					mips_output << calop[opcode] << "  $a3 , " << reg1 << " , " << reg2 << endl;
					mips_output << "sw  $a3 , " << cur_mips_table->get_addr(mid_c) << endl;
				}
			}

			else if (opcode == "=") {  //assgin   1. c= return  2. c= imm 3. c= $ 4.  c= memory   
				string reg3, reg1;
				bool flag=false;


				if (is_temp(mid_c)) {
					reg3 = getT_R(mid_c);
					if (mid_a == "$RET")
						mips_output << "move  " << reg3 << " , " << "$v0" << endl;
					else if (is_imm(mid_a)) {
						mips_output << "li  " << reg3 << " , " << mid_a << endl;
					}
					else if (cur_mips_table->find_sreg(mid_a))
						mips_output << "move " << reg3 << " , " << cur_mips_table->get_sreg(mid_a) << endl;
					else if (is_temp(mid_a))
					{
						//这里是一步优化
						mips_output << "move " << reg3 << " , " << getT_R(mid_a) << endl;
					}
					else
						mips_output << "lw " << reg3 << " , " << cur_mips_table->get_addr(mid_a)<<endl;
				}
				else if (cur_mips_table->find_sreg(mid_c)) {
					reg3 = cur_mips_table->get_sreg(mid_c);
					if (mid_a == "$RET")
						mips_output << "move  " << reg3 << " , " << "$v0" << endl;
					else if (is_imm(mid_a)) {
						mips_output << "li  " << reg3 << " , " << mid_a << endl;
					}
					else if (cur_mips_table->find_sreg(mid_a))
						mips_output << "move " << reg3 << " , " << cur_mips_table->get_sreg(mid_a) << endl;
					else if (is_temp(mid_a))
					{
						mips_output << "move " << reg3 << " , " << getT_R(mid_a) << endl;
					}
					else
						mips_output << "lw " << reg3 << " , " << cur_mips_table->get_addr(mid_a) << endl;
				}
				else {
					flag = true;
					reg3 = "$a3";
					if (mid_a == "$RET")
						mips_output << "move  " << reg3 << " , " << "$v0" << endl;
					else if (is_imm(mid_a)) {
						mips_output << "li  " << reg3 << " , " << mid_a << endl;
					}
					else if (cur_mips_table->find_sreg(mid_a))
						mips_output << "move " << reg3 << " , " << cur_mips_table->get_sreg(mid_a) << endl;
					else if (is_temp(mid_a))
					{
						reg3 = getT_R(mid_a); //这里是一步优化
					}
					else
						mips_output << "lw " << reg3 << " , " << cur_mips_table->get_addr(mid_a) << endl;
				}
				if (flag)
				{
					mips_output << "sw  "<<reg3<< " , " << cur_mips_table->get_addr(mid_c) << endl;

				}
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
			else if (opcode == "CONST") {
			
					mips_output << "li $a3 ," <<mid_c << endl;
					mips_output << "sw $a3 ,"  << cur_mips_table ->get_addr(mid_b) << endl;
			}

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
				if (cur_mips_table->find_sreg(mid_c)) 
					mips_output << "move " << cur_mips_table->get_sreg(mid_c) << " , $v0 " << endl;
				else
					mips_output << "sw $v0 ," << cur_mips_table->get_addr(mid_c) << endl;
			}
			else if (opcode == "SCFI") {
				mips_output << "li $v0, 5" << endl;
				mips_output << "syscall" << endl;
				if (cur_mips_table->find_sreg(mid_c))
					mips_output << "move " << cur_mips_table->get_sreg(mid_c) << ", $v0"<<endl;
				else
					mips_output << "sw $v0, " << cur_mips_table->get_addr(mid_c) << endl;
			}
			else if (opcode == "GOTO") {
				mips_output << "j " << mid_c << endl;
			}
			else if (opcode == "GENLAB") {
				mips_output << mid_c + ":" << endl;
			}
			else if (opcode == "=[]")
			{
				bool flag;
				string reg2 ,reg3;  //中间变量 或者 普通变量  或者 全局变量
				if (is_temp(mid_c))
				{
					reg3 = getT_R(mid_c);
				}
				else if (cur_mips_table->find_sreg(reg3))
				{
					reg3 = cur_mips_table->get_sreg(reg3);
				}
				else {
					reg3 = "$a1";
				}//get  reg3 
				

				if(cur_mips_table->is_local(mid_a))
					mips_output << "addi $a3 , $fp , " << cur_mips_table->get_a_offset(mid_a) << endl;
				else {
					mips_output << "la $a3 ,  " << mid_a << endl;
				}

				if (is_imm(mid_b))
				{
					mips_output << "lw "<<reg3 <<" , " << stoi(mid_b) * 4 <<"($a3)" <<endl;
				}
				else if (is_temp(mid_b)) {/////需要处理
					reg2 = getT_R(mid_b);//找到临时变量的寄存器
					mips_output << "sll $a2, " << reg2 << ",2" << endl;
					mips_output << "add $a3,$a2,$a3" << endl;
					mips_output << "lw " << reg3 << " , " << "0($a3)" << endl;
					
				}
				else if (cur_mips_table->find_sreg(mid_b))
				{
					reg2 = cur_mips_table->get_sreg(mid_b);
					mips_output << "sll $a2 , " << reg2 << ",2" << endl;
					mips_output << "add $a3,$a2,$a3" << endl;
					mips_output << "lw " << reg3 << " , " << "0($a3)" << endl;

				}
				else {
					mips_output << "lw $a2 , " << cur_mips_table->get_addr(mid_b) << endl;
					mips_output << "sll $a2,$a2,2" << endl;
					mips_output << "add $a3,$a2,$a3" << endl;
					mips_output << "lw " << reg3 << " , " << "0($a3)" << endl;
				}
				//store
				if (reg3=="$a1") {
					mips_output << "sw " << reg3 << " , " << cur_mips_table->get_addr(mid_c) << endl;
				}
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
					mips_output << "lw $a2 , " << cur_mips_table->get_addr(mid_b) << endl;
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
						mips_output << "li $v0 ," << mid_c << endl;
					}
					else if (cur_mips_table->find_sreg(mid_c))
					{
						mips_output << "move $v0 ," << cur_mips_table->get_sreg(mid_c) << endl;
					}
					else if (1);
					else {
						mips_output << "lw $v0 , " << cur_mips_table->get_sreg(mid_c) << endl;
					}
				}
				if (cur_mips_table->name != "main")
				{
					mips_output << "addi $sp,$sp," << cur_mips_table->tablesize << endl;
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
					mips_output << "lw $a3, " << cur_mips_table->get_addr(mid_a) << endl;
					reg1 = "$a3";
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
					mips_output << "lw $a2 , " << cur_mips_table->get_addr(mid_b) << endl;
					reg2 = "$a2";
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
				for (int i = args_count ; i > 0; i -- )
				{
					mips_output << "lw  $a3 , " << -i * 4 << "($sp)" << endl;
					mips_output << "sw  $a3 , " << -RESERVED_SIZE + i * 4 - table::get_tbs(mid_c) -4 << "($sp)" << endl;
				}
				save_current();
				mips_output << "subi  $sp,$sp ," << RESERVED_SIZE << endl;
				mips_output << " jal " << mid_c << endl;
				refresh_current();
				mips_output << "addi $sp,$sp , " << RESERVED_SIZE << endl;

				param_ptr = 0;//important

			}
			else if (opcode == "PUSH") {
				string reg3;
				if (is_imm(mid_c)) {
					mips_output << "li $a3 , " << mid_c << endl;
					reg3 = "$a3";
					//	mips_output << "sw $a3 , " << to_string(param_ptr) + "($sp)" << endl;
				//	param_ptr -= 4;
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
				mips_output<<"sw "<<reg3<<" , "<< to_string( param_ptr ) + "($sp)" << endl;
				
					
			}
			
		}
		
		mips_output << "add $sp, $sp, " << cur_mips_table->tablesize << endl;
		if (cur_mips_table->name == "main") {//函数结束
			mips_output << "li $v0 ,10" << endl << "syscall" << endl;
		}
		else {
			mips_output << "jr $ra" << endl;
		}

	}
	
	return 0;
}