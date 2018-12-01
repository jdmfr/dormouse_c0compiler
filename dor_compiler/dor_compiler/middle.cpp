#include "middle.h"
#include "signtable.h"
#include<cstring>
#define MIDCODE_DEBUG  1
#define REAL_MID_OUTPUT
vector<middle> midcode;




middle::middle(string opcode, string a, string b, string c)
{
	this->opcode = opcode;
	this->a_op = a;
	this->b_op = b;
	this->c_op = c;
#ifdef REAL_MID_OUTPUT
	if (opcode == "GENLAB")
		mid_output_real << c + ":" << endl;
	else
		mid_output_real << opcode << "  " << a << "  " << b << "  " << c << endl; 
#endif
}


middle::~middle()
{
}
int middle::genmid_var_and_func(string opcode, string a, string b, string c) {
	midcode.push_back(middle(opcode, a, b, c));

#ifdef MIDCODE_DEBUG
	if (opcode == "FUNC")
	{
		mid_output_co << a << "  " << c << "()" << endl;
	}
	else if (opcode == "PARA")
	{
		mid_output_co << "para" << a << "  " << c << endl;
	}
	else if (opcode == "PUSH")
	{
		mid_output_co << "push" << "    " << c << endl;
	}
	
#endif
	return 0;
}

int middle::genmid_comp(string opcode, string a, string b, string c) {
	midcode.push_back(middle(opcode, a, b, c));
#ifdef MIDCODE_DEBUG
	mid_output_co << "if ( " << a << "  "+opcode+"  " << b << " ) "<< c <<endl;
#endif
	return 0;
}


// c[b] = a    c= a[b]
int middle::genmid_cal(string opcode, string a, string b, string c) {
	midcode.push_back(middle(opcode, a, b, c));
#ifdef MIDCODE_DEBUG
	if (opcode == "[]=")
		mid_output_co << c << "[" + b + "]" << "  =  " << a << endl;
	else if (opcode == "=[]")
		mid_output_co << c << "  =  "<< a<<"["+b+"]" <<endl;
	else mid_output_co << c << "  =  " << a << "  " + opcode + "  " << b << endl;
#endif
	return 0;
}

int middle::genmid(string opcode, string a, string b, string c) {
	midcode.push_back(middle(opcode, a, b, c));
#ifdef MIDCODE_DEBUG
	if (opcode == "GENLAB")
		mid_output_co << c + ":" << endl;
	else if(opcode =="=")
		mid_output_co << c << " = " << a << endl;
	else if (opcode == "LOOP" || opcode == "LOOPEND");
	else
		mid_output_co << opcode << "  " << a << "  " << b << "  " << c << endl;
#endif
	return 0;
}

int middle::middle_real_generate() {
	
	for (auto &i = midcode.begin(); i != midcode.end(); i++) {
		mid_output_real << i->opcode << "  " << i->a_op << "  " << i->b_op << "  " << i->c_op << "  " << endl;
	}
	return 0;

}