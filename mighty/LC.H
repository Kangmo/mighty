#include <stdio.h>


#define MAXSTRLEN 300
#define NUM_FUNC	300
#define NUM_GLOBAL_VARS 200
#define NUM_LOCAL_VARS  400
#define NUM_BLOCK	100
#define ID_LEN		30
#define FUNC_CALLS		200
#define NUM_PARAMS       31
#define PROG_SIZE	    20000
#define LOOP_NEST	       31
#define TERMINATE_PROG  999
enum error_msg
	{SYNTAX, UNBAL_PARENS, NO_EXP, EQIUALS_EXPECTED,
	 NOT_VAR, PARAM_ERR, SEMI_EXPECTED,
	 UNBAL_BRACES, FUNC_UNDEF, TYPE_EXPECTED,
	 NEST_FUNC, RET_NOCALL, PAREN_EXPECTED,
	 WHILE_EXPECTED, QUOTE_EXPECTED, NOT_TEMP,
	 TOO_MANY_LVARS, INVALID_VAR_INIT,
	 INTERNAL_ERROR, TYPE_MISMATCH, NOT_ENOUGH_MEM,
	 PARAM_NOT_CORRES, COMMA_EXPECTED, OUT_OF_INDEX,
	 OPEN_BRACE_REQUIRED, FILE_CLOSE_ERROR,
	 ARRAY_OUT_OF_INDEX, CLOSE_ARRAY_EXPECTED,
	 TOO_MANY_ARGUMENTS, TOO_FEW_ARGUMENTS,
	 CLOSE_BRACE_REQUIRED, TOO_FEW_INIT_VALUES,
	 APOST_EXPECTED, UNEXPECTED_END};

/* An array of these structures will hold the info
	associated with global variables.
*/

class CVar {
	 public :
		  int cbr;   // this value is asserted only when used as function's cbr parameter.
						 // when this gets argument, cbr is asserted only when argument's is.
		  char *var_name; // contains var's name
		  int var_type;   // contains var's type
		  int value;      // contains var's value  (int, char)
		  char *string;   // contains var's string (string)
		  FILE *file;     // contains var's file   (file)
		  CVar *next;
		  CVar *prev;
	 CVar();
	 CVar(CVar &var);
	 ~CVar();
	 void SetFile(FILE* fp);
	 void SetString(char *str);
	 void SetName(char *str);
	 void SetVar(class CVar var);
	 void AssignVar(class CVar var);
	 void SetValue(int *val);
	 void SetValue(int val);
	 CVar* GetTail();

	 int  isTail() { return next==NULL?1:0; }
	 int  isHead() { return prev==NULL?1:0; }

};

struct func_type {
	char func_name[ID_LEN];
	char *loc;   /* location of function entry point in file */
};

struct func_call {
	int lvartos;        // because the token return is found,
							  // interp_block func is called once or more. (recursion)
	int is_terminated;  // is this function terminated?
};

void func_return();
int is_func_returned();

struct commands {  /* keyword lookup table */
	char command[20];
	char tok;
};

struct list{
	char*  data;
	struct list* next;
};

assign_stack(struct var_type &dest, struct var_type src);


// this function assumes that head is already allocated.
int AllocArray(CVar* head, int el_num);

// this function does not free head.
void FreeArray(CVar* head);

// this function free all array members including head.
void FreeVar(CVar* var);

// returns pointer of object : when success
// returns null : when fail (out of array index)
CVar* AccessArray(CVar* head, int index);


void OpenParen();
void CloseParen();
void Semicolon();
void Comma();
//int OpenArray();
void CloseArray();
void OpenBrace();
//void CloseBrace();

