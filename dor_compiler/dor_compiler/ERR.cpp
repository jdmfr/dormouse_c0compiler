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
	"error:: ILLEGAL_CHAR  ",
	"error:: main func overflow �� main�����������" , //14 main�����������
	"error:: should be legal type ",//15
	"error:: should be a comma or semicolon ", //16 var_decl/print/func �� ��Ӧ����һ�����Ż�ֺ�
	"error:: can't assign to a const ",//17 cant assign to a const  �ڸ�ֵ����д���
	"error:: illegal assign type ",// 18  ��ֵ���Ͳ�ͬ
	"error:: call func error / params error ",//19  �������ô���
	"error:: scanf error ,maybe scanf a const",// 20 scanf error
	"error:: printf error ,maybe caused by exp error ",//21 printf error
	"error:: illegal statement start ",//22 fei fa yu ju
	"error:: illegal subscript �Ƿ��±�/����Խ�� ",//23 �Ƿ��±�
	"error:: illegal term",//24 term����
	"error:: illegal factor",//25 �Ƿ�factor
	"error:: lack params ", // 26 ȱ�ٲ���
	"error:: already has identity �Ѷ����ʶ��",//27 ������ű�ʧ��
	"error:: should be a comma or semicolon ",//28�����غ�
	"error:: illegal expression ",//29�Ƿ�EXP
	"error:: only have default ",//30 only default
	"error:: case type error ",//31 case���ʹ���
	"error:: return error ��/�޷���ֵŪ�� �� ���ش������� ",//32 return ����
	"error:: illegal ident δ�����ʶ�� ",//33 �Ƿ���ʶ��
	"error:: ��ʶ��/���Ŵ���������� -------  ",//34 check wrong
	"error:: there is no main function or wrong main func ,please edit your file ", //35û��main ����
	"error:: have same case ,please edit your code ",   //36 case �ظ�
	"error:: ����INT�͸�ֵ��char ",//37
	"error:: �޲κ���������()  ",//38
	"error:: �Ƚ��жϱ���������" , //39
	"error:: void����������Ϊ���ʽ���� "  ,//40
	"error:: case wrong "  //41
	
};
void ERR::error(int error_num , int process_way) {

	error_count++;
	cout << err_msg[error_num] << "     before " << line_count << ":" << pos_num  << endl;
	switch (process_way) 
	{
		case 0:  return;    //local repair 
				break;

	}
	return;
}