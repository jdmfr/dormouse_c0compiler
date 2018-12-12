#include "ERR.h"
/*
#define LACK_NUM 0
#define LACK_QUOTE 1 
#define LACK_DOQUOTE 2
#define INVALID_CHAR 3
#define LACK_SEMICOLON 4
#define LACK_LBRACK 5
#define LACK_LBRACE 6
#define LACK_LPAREN 7
#define LACK_RBRACK 8
#define LACK_RBRACE 9
#define LACK_RPAREN 10

#define SH_NEQ 11
*/
string ERR::err_msg[] = {
	"error:: LACK_NUM      ",
	"error:: LACK_QUOTE    ",
	"error:: LACK_DOQUOTE  ",
	"error:: INVALID_CH    ",
	"error:: LACK_SEMICOLON",
	"error:: LACK_LBRACK   ",
	"error:: LACK_LBRACE   ",
	"error:: LACK_LPAREN   ",
	"error:: LACK_RBRACK   ",
	"error:: LACK_RBRACE   ",
	"error:: LACK_RPAREN   ",

	/////---- 0~10  ----/////
	"error:: SHOULD_NEQ    ",
	"error:: LACK_COMMA    ",
	"error:: ILLEGAL_CHAR  "
	"error:: main func voerflow"//main函数后还有语句
	"error:: should be legal type "
	"error:: should be a comma or semicolon " // var_decl/print/func 中 ，应该是一个逗号或分号
	"error:: can't assign to a const "//17 cant assign to a const  在赋值语句中触发
	"error:: illegal assign type "// 18  赋值类型不同
	"error:: call func error / params error "//19  函数调用错误
	"error:: scanf error ,maybe scanf a const"// 20 scanf error
	"error:: printf error ,maybe caused by exp error "//21 printf error
	"error:: illegal statement start "//22 fei fa yu ju
	"error:: illegal subscript "//23 非法下标
	"error:: illegal term"//24 term错误
	"error:: illegal factor"//25 非法factor
	"error:: lack params " // 26 缺少参数
	"error:: already has identity "//27 插入符号表失败
	"error:: should be a comma or semicolon "//28参数重合
	"error:: illegal expression "//29非法EXP
	"error:: only have default "//30 only default
	"error:: case type error "//31 case类型错误
	"error:: return error "//32 return 错误
	"error:: illegal ident "//33 非法标识符
};
void ERR::error(int error_num , int process_way) {

	error_count++;
	cout << err_msg[error_num] << "  At " << line_count << ":" << pos_num  << endl;
	switch (process_way) 
	{
		case 0:  return;    //local repair 
				break;

	}
	return;
}