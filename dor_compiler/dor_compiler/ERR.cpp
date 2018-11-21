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
	//
	"error:: should be legal type "
	//17 cant assign to a const
	// 18  ��ֵ���Ͳ�ͬ
	//19  �������ô���
	// 20 scanf error
	//21 printf error
	//22 fei fa yu ju
	//23 �Ƿ��±�
	//24 term����
	//25 �Ƿ�factor
	//26 ȱ�ٲ���
	//27 ������ű�ʧ��
	//28�����غ�
	//29�Ƿ�EXP
	//30 only default
	//31 case���ʹ���
};
void ERR::error(int error_num , int process_way=0) {

	error_count++;
	cout << err_msg[error_num] << "  At " << line_count << ":" << pos_num  << endl;
	switch (process_way) 
	{
		case 0:  return;    //local repair 
				break;

	}
	return;
}