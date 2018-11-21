#ifndef LEX_ANALYSIS_H
#define LEX_ANALYSIS_H
#include "global.h"
#include "ERR.h"

using namespace std;
extern ifstream infile;
extern char ch;
extern int token;
extern string sym;
extern map<string, int> WordMap;
extern string LEX_PRINT_KEYS[];
enum token_e { TK_ident,KW_void=1, KW_int ,KW_char, KW_main, KW_if, KW_else, KW_do,KW_while, KW_switch, KW_case, KW_default, KW_scanf,KW_printf,KW_return ,KW_const, \
                TK_num, TK_plus , TK_minus , TK_mul , TK_div ,TK_eq    \
                , TK_assign , TK_neq , TK_leq , TK_les , TK_geq , TK_gt ,TK_colon, TK_semicolon , TK_lbrack \
                , TK_rbrack ,TK_lparen, TK_rparen ,TK_lbrace, TK_rbrace , TK_cchar , TK_cstr , TK_comma , TK_eof, TK_invalidc };  //40
class LEX_ANALYSIS
{
    public:
  //     static int N ;
        static int id_count;
        static string cur_line;

        static int sym_num;
        LEX_ANALYSIS();
        static void get_token();
        static int getch();
        static int readfile();
		static void print();
        static void parse_identifier();
        static void parse_num();
		static bool is_compop(int token);
};


#endif // LEX_ANALYSIS_H


