#pragma once
#include <iostream>
#include <string>
#include <map>
#include<utility>
#include<stdlib.h>
#include<fstream>
#include <vector>

////////////////error/////////////
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
#define LACK_NUM 0

#define SH_NEQ 11
#define LACK_COMMA 12
#define ILLEGAL_CHAR 13
////////////////error_end/////////////
using namespace std;
extern int pos_num;
extern int line_count;
extern int line_l;
extern int error_count;

extern ofstream mid_output_co, mid_output_real, mips_output;