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
	"error:: main func voerflow"//main�����������
	"error:: should be legal type "
	"error:: should be a comma or semicolon " // var_decl/print/func �� ��Ӧ����һ�����Ż�ֺ�
	"error:: can't assign to a const "//17 cant assign to a const  �ڸ�ֵ����д���
	"error:: illegal assign type "// 18  ��ֵ���Ͳ�ͬ
	"error:: call func error / params error "//19  �������ô���
	"error:: scanf error ,maybe scanf a const"// 20 scanf error
	"error:: printf error ,maybe caused by exp error "//21 printf error
	"error:: illegal statement start "//22 fei fa yu ju
	"error:: illegal subscript "//23 �Ƿ��±�
	"error:: illegal term"//24 term����
	"error:: illegal factor"//25 �Ƿ�factor
	"error:: lack params " // 26 ȱ�ٲ���
	"error:: already has identity "//27 ������ű�ʧ��
	"error:: should be a comma or semicolon "//28�����غ�
	"error:: illegal expression "//29�Ƿ�EXP
	"error:: only have default "//30 only default
	"error:: case type error "//31 case���ʹ���
	"error:: return error "//32 return ����
	"error:: illegal ident "//33 �Ƿ���ʶ��
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