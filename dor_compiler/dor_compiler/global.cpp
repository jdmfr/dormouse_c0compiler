#include "global.h"

int line_count = 0;
int pos_num = 0;
int line_l = 0;
int error_count = 0;
ofstream mid_output_co,mid_output_real,mips_output;

bool should_back_token = false;

bool is_comp(string name) {
	return name == "bne" || name == "beq" || name == "blt" || name == "ble" \
		|| name == "bgt" || name == "bge";
}