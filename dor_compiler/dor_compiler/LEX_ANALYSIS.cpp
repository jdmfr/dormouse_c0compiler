#pragma once
#include "LEX_ANALYSIS.h"
map<string,int> WordMap;
int LEX_ANALYSIS::id_count=0;
int LEX_ANALYSIS::sym_num=0;

ifstream infile;
string LEX_ANALYSIS::cur_line = "";
string sym = "";
int token = 0 ;
char ch=' ';


 string LEX_PRINT_KEYS[]={"IDENT","VOID","INT","CHAR","MAIN","IF" , "ELSE" ,"DO","WHILE","SWITCH","CASE","DEFAULT","SCANF","PRINTF","RETURN ","CONST" \
                            ,"NUM" , "plus" ,"minus","mul","div","eq","assign", "neq","leq","les","geq","gt","colon","semicolon" \
                            ,"lbrack" , "rbrack", "lparen", "rparen", "lbrace", "rbrace", "C_CHAR" , "C_STRING" , "comma" , "EOF","invalid"};

 void to_lower(string& str) {
	 for (auto &s : str)
		 s = tolower(s);
	 return;
 }


void LEX_ANALYSIS::print(){
	 if (token == 0 || token == TK_cchar || token == TK_cstr)
		 std::cout << id_count++ << " " << LEX_PRINT_KEYS[token] << " " << sym << std::endl;
	 else if (token == TK_num)
		 std::cout << id_count++ << " " << LEX_PRINT_KEYS[token] << " " << sym_num << std::endl;
	 else if (token != TK_invalidc)
		 std::cout << id_count++ << " " << LEX_PRINT_KEYS[token] << std::endl;
	 return;
 }
LEX_ANALYSIS::LEX_ANALYSIS()
{
   // WordMap.insert(<string,int>(0,"IDENT"));

    ch=' ';
    return ;
}

bool LEX_ANALYSIS::is_compop(int token) {
	return token == TK_geq || token == TK_gt || token == TK_leq  \
		|| token == TK_les || token == TK_neq || token == TK_eq;
}

void LEX_ANALYSIS::get_token(){
    while(ch==' '||ch=='\t'||ch=='\n' )
    {
        getch();
    }
    if( isalpha(ch)||ch=='_'){
        parse_identifier();
        //insert
        return ;
    }
    else if( isdigit(ch)){
        parse_num();
        token=TK_num;
    }
    else switch(ch){
    case '+':
        token= TK_plus;
        getch();
        break;
    case '-':
        token= TK_minus;
        getch();
        break;
    case '*':
        token= TK_mul;
        getch();
        break;
    case '/':
        token= TK_div;
        getch();
        break;
    case '=':
        getch();
        if(ch== '=')
        {
            token= TK_eq ;
            getch();
            break;
        }
        else token=TK_assign ;
        break;
    case '!':
        getch();
        if(ch=='=')
        {
            getch();
            token=TK_neq;
            break;
        }
        else{
			ERR::error(SH_NEQ, 0);
			token=TK_neq;//error
		}
        break;
    case '<':
        getch();
        if(ch=='=')
        {
            getch();
            token=TK_leq;
        }
        else token=TK_les;
        break;
    case '>':
        getch();
        if(ch=='=')
        {
            getch();
            token=TK_geq;
        }
        else token=TK_gt;
        break;
    case ':':
        getch();
        token=TK_colon;
    case ';':
        getch();
        token=TK_semicolon;
        break;
    case '[':
        getch();
        token=TK_lbrack ;
        break;
    case ']':
        getch();
        token=TK_rbrack ;
        break;
    case '(':
        getch();
        token=TK_lparen ;
        break;
    case ')':
        getch();
        token=TK_rparen ;
        break;
    case '{':
        getch();
        token=TK_lbrace ;
        break;
    case '}':
        getch();
        token=TK_rbrace ;
        break;
    case '\'':
        sym="";
        getch();
        if(isalpha(ch)||isdigit(ch)||ch=='+'||ch=='-'||ch=='*'||ch=='/'||ch=='_')
        {
            sym+= ch;
			LEX_ANALYSIS::sym_num = (int)ch;
            getch();
        }
		else
		{
			ERR::error(ILLEGAL_CHAR, 0);
			sym=" ";
			getch();
		}
		token = TK_cchar;

		if (ch != '\'')
		{
			ERR::error(LACK_QUOTE, 0);
			//local repair 
			if (ch == '\"')
				getch();
		}
		else
		{
			getch();
		}
        break;
    case '\"':
        sym= "";
        getch();
        while(ch==32||ch==33||(ch>=35&&ch<=126))
        {
            sym+=ch;
			getch();
        }
        if(ch!='\"')
        {
            //error;
			ERR::error(LACK_DOQUOTE, 0);
			token = TK_cstr;
        }
        else{
            token = TK_cstr;
			getch();
        }

        break;
    case ',':
        getch();
        token = TK_comma;
        break;
    case EOF:
        token = TK_eof;
        break;
    default:
        ERR::error(INVALID_CHAR,0);
		token = TK_invalidc;
        getch();
        break;
    }
    return ;
}




int LEX_ANALYSIS::getch(){
	if ( infile.eof() && pos_num == line_l )
	{
		ch = EOF;
		return -1;
	}
	if( pos_num <line_l )
    {
        ch = cur_line[pos_num++];
    }
    else{
        while(getline(infile,LEX_ANALYSIS::cur_line))
        {
			pos_num = 0;
            line_count++;
            if(cur_line=="\n" ||cur_line=="")
                continue;
            else  break;
        }

		if (cur_line != "") {
			line_l = cur_line.length();
			ch = cur_line[pos_num++];
		}
		else ch = EOF;
		return -1;

    }
    return 0;
}//getch 中不对sym操作，保证了sym的干净

void LEX_ANALYSIS::parse_identifier(){
    map<string,int>::iterator it;

    sym= "";
    sym= sym+ ch;
    getch();
    while(isalpha(ch)||isdigit(ch)||ch=='_'){
        sym+=ch;
        getch();
    }
 //   cout<<sym<<endl;
	to_lower(sym);
//	cout << sym << endl;
    it = WordMap.find(sym);
    if(it!=WordMap.end())
    {
        token= it->second;
    }
    else {
        token = TK_ident ;
        //table insert
    }
    return ;

}
void LEX_ANALYSIS::parse_num(){
    sym = "";
    sym += ch;
    getch();
    while(isdigit(ch))
    {
        sym += ch ;
        getch();
    }

    sym_num=atoi(sym.data());
    return ;
}

int LEX_ANALYSIS::readfile()
{
	string fname;
	cout << "input your test.txt ：" << endl;
	cin >> fname;
	infile.open(fname, ios::in);//文件名
	if (!infile)
	{
		cout <<fname<< "not exist this filename " << endl;
		return -1;
	}
	return 0;
}
