/*
A Little C interpreter. */

#include <stdio.h>
#include <setjmp.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <alloc.h>
#include "constdef.h"
#include "lc.h"
#include "debug.h"

#ifndef DEBUG
  #include "mighty_d.h"
  extern class CDataFile *DF;
#endif

CVar* global_vars[NUM_GLOBAL_VARS];
CVar* local_var_stack[NUM_LOCAL_VARS];

struct func_type func_table[NUM_FUNC];

struct func_call call_stack[FUNC_CALLS];

enum tok_types {DELIMITER, IDENTIFIER, NUMBER, KEYWORD,
					 TEMP, QUOTE, BLOCK};

enum tokens {ARG, CHAR, INT, STRING, File, IF, ELSE, FOR, DO, WHILE,
				 SWITCH, RETURN, EOL, FINISHED, BUFF, END};

enum double_ops {LT = 1, LE, GT, GE, EQ, NE};

struct commands table[] = {  /* Commands must be entered lowercase */
	{"if", IF}, /*in this table. */
	{"else", ELSE},
	{"for", FOR},
	{"do", DO},
	{"while", WHILE},
	{"char", CHAR},
	{"int", INT},
	{"string", STRING},
	{"file",   File},
	{"return", RETURN},
	{"exit", END},
	{"", END}   /* mark end of table */
};

char *prog; /* current location in source code */
char *p_buf; /* points to start of program buffer */
jmp_buf e_buf; /* hold environment for longjmp() */

char token[80];
char token_type, tok;

//int top = 0;
struct list* namehead; /* top of call by reference argument name stack */
int functos;  /* index to top of function call stack */
int func_index;  /* index into function table */
int gvar_index;  /* index into global variable table */
int lvartos;  /* index into local variable stack */

int ret_value; /* function return value */

void print(void), prescan(void);
void decl_global(void), call(void), putback(void);
void decl_local(void), local_push(CVar var);
void eval_exp(CVar &var), sntx_err(int error);
void exec_if(void), find_eob(void), exec_for(void);
void get_params(void);
void get_args(int lvars_arg_base, int lvars_arg_top);
void exec_while(void), func_push(int i), exec_do(void);
void assign_var(char *var_name, CVar var);
int load_program(char *p, char *fname);
CVar* find_var(char *name);
void interp_block(void), func_ret(void);
int func_pop(void), is_var(char *s), get_token(void);
char *find_func(char *name);
void local_free(void);

void name_popall_and_delhead();
void name_push(CVar* cbrvar);
void name_pop(CVar* cbrvar);


// this commented implementation is for the possiblity of existing garbage
// at Global variables.
/*
#define LOCAL_VAR  1
#define GLOBAL_BAR 2
void FreeGarbage(int i, int scope)
{
	 int j, ObjectOfSameAddr = 0;
	 for (j=0; j<i; j++)
	 {
		 ObjectOfSameAddr +=
		 (((scope==GLOBAL_VAR)&&(global_vars[j]==global_vars[i]))?1:0) +
		 (((scope==LOCAL_VAR)&&(local_var_stack[j]==local_var_stack[i]))?1:0);
	 }
	 if (ObjectOfSameAddr==0)
		 switch(scope)
		 {
			 case GLOBAL_VAR:
					  FreeVar( global_vars[i] );
					  break;
			 case LOCAL_VAR:
					  FreeVar( local_var_stack[i] );
					  break;
		 }
}
void deinit_values(void)
{
	 int i;
	 if (gvar_index)
		 for (i=gvar_index-1; i>=0 ; i--) FreeGarbage(i, GLOBAL_BAR);
	 if (lvartos)
		 for (i=lvartos-1; i>=0 ; i--) FreeGarbage(i, LOCAL_VAR);
}

*/

// At local var stack,
// there can be two pointer variables which has the same address
// especally when script ended without purpose...
// and script was running call by reference function.
void FreeGarbage(int i)
{
	 int j, ObjectOfSameAddr = 0;
	 for (j=0; j<i; j++)
	 {
		 ObjectOfSameAddr +=
			 ((local_var_stack[j]==local_var_stack[i])?1:0) +
			 ((global_vars[j]==local_var_stack[i])?1:0);
	 }
	 // if there is no local vars
	 // which has the same value with local_var_stack[i],
	 // then do not delete
	 if (ObjectOfSameAddr==0) FreeVar( local_var_stack[i] );
}

void deinit_values(void)
{
	 int i;
	 if (lvartos)
		 for (i=lvartos-1; i>=0 ; i--) FreeGarbage(i);
	 if (gvar_index)
		 for (i=gvar_index-1; i>=0 ; i--) FreeVar(global_vars[i]);
	 name_popall_and_delhead();
}
/*
void deinit_values(void)
{
	 int i;
	 if (lvartos)
		 for (i=lvartos-1; i>=0 ; i--) FreeVar(local_var_stack[i]);
	 if (gvar_index)
		 for (i=gvar_index-1; i>=0 ; i--) FreeVar(global_vars[i]);

	 name_popall_and_delhead();
}*/

void RunScript(char *fname)
{
	/* allocate memory for the program */
	/* load the program to execute */

	MEMTEST
	if ((p_buf = new char[PROG_SIZE]) == NULL) {
		 ReadDataFile(195); // script file is too long
	}
	MEMTEST
	if (!load_program(p_buf, fname))
	{
		 ReadDataFile(196); // can't run script program.
		 delete p_buf;
		 return;
	}
	MEMTEST
	if (setjmp(e_buf)) /* initialize long jump buffer */
	{
		 //deinit_values();

		 delete p_buf;
		 return;
	}
	MEMTEST
	/* set program pointer to start of program buffer */
	prog = p_buf;
	gvar_index = 0; /* initialze global variabl index */

	prescan(); /* find the location of all functions and global variables in the program */
	MEMTEST

	lvartos = 0;  /* initialize local variable stack index */
	functos = 0;  /* initialize the CALL stack index */

	namehead = new struct list; /* initialize the cbr argument name stack index */
	namehead->next = NULL;

	/* setup call to main() */
	prog = find_func("main");  /* find progrma starting point */
	MEMTEST
	prog--;  /* back up to opening ( */
	strcpy(token, "main");

	MEMTEST
	// this function is cause of 20 kilobytyes disappearing.
	call();  /* call main() to start interpreting */
	MEMTEST

	deinit_values();
	MEMTEST

	delete p_buf;
	MEMTEST
}

/* Interpret a single statement or block of code. When
	interp_block() returns from int initial call, the final
	brace (or a return) in main() has been encountered.
*/
void interp_block(void)
{
	CVar var;
	char block = 0;

	do {
		token_type = get_token();
		/* If interpreting single statement, return of first semicolon. */

		/* see what kind of token is up */
		if (token_type == IDENTIFIER)
		{
			/* Not a keyword, so process expression. */
			 putback();  /* restore token to input stream for
								 further processing by eval_exp() */
			 eval_exp(var);  /* process the expression */

			 if (*token != ';') sntx_err(SEMI_EXPECTED);
		}
		else if (token_type == BLOCK)  // after function call , and so on..
		{   /* if block delimiter */
			 if (*token == '{') /* is a block */
				 block = 1;  /* interpreting block, not statement */
			 else return;  /* is a }, so return */
		}
		else /* is keyword */
			 switch(tok) {
				 case File :
				 case STRING :
				 case CHAR :
				 case INT :   /* declare local variables */
						putback();
						decl_local();
						break;
				 case RETURN :    /* return from function call */
						func_ret(); // get return value if any.
						func_return();   // inform function call stack that function is returned.
						return;
				 case IF : /* process an if statement */
						exec_if();
						break;
				 case ELSE :  /* process an else statement */
						find_eob();/* find end of else block and continue execution */
						break;
				 case WHILE : /* process a while loop */
						exec_while();
						break;
				 case DO :  /* process a do-while loop */
						exec_do();
						break;
				 case FOR :
						exec_for();
						break;
				 case END :
						OpenParen();
						CloseParen();
						sntx_err(TERMINATE_PROG);
		}
		if (is_func_returned()) return;

	} while (tok != FINISHED && block);
}
/* Load a program. */
load_program(char *p, char *fname)
{
	FILE *fp;
	long i = 0, size;
	if ((fp = fopen(fname, "rb")) == NULL)
	{
		return 0;
	}
	fseek( fp, 0L, SEEK_END);
	size = ftell(fp);
	fseek( fp, 0L, SEEK_SET);

	do {
		*p = getc(fp);
		p++; i++;
	} while ( i < size && i < PROG_SIZE);
	*p = '\0';  /* null terminate the program */
	fclose(fp);
	return 1;
}

/* Find the location of all functions in the program
	and store global variables. */
void prescan(void)
{
	char *p;
	char temp[32];
	int brace = 0; /* When 0, this var tells us that current source
							position is outside of any function. */
	p = prog;
	func_index = 0;
	do {
		while (brace) {  /* bypass code inside functions */
			  get_token();
			  if (*token == '{') brace++;
			  if (*token == '}') brace--;
			  //printf("< %s, %i >", token, brace);
			  //getch();
		}

		get_token();

		if (tok == CHAR || tok == INT || tok == STRING) {  /* is global var */
			  putback();
			  decl_global();
		}
		else if (token_type == IDENTIFIER) {
			 strcpy(temp, token);
			 get_token();
			 if (*token == '(') {  /* must be assume a function */
				 func_table[func_index].loc = prog;              /*      v-loc */
				 strcpy(func_table[func_index].func_name, temp); /* haha(int a)*/
				 func_index++;
				 while (*prog != ')') prog++;
				 prog++;
				 /* prog points to opening curly brace of function */
			 }
			 else putback();
		}
		else if (*token == '{') brace++;
	} while ( tok != FINISHED );
	prog = p;
}

/* Return the entry point of the specified function.
	Return NULL if not found.
*/
char *find_func(char *name)
{
	register int i;

	for (i = 0; i < func_index; i++)
		if (!strcmp(name, func_table[i].func_name))
	 return func_table[i].loc;
	return NULL;
}

void MakeArray_Init_Var(CVar* var)
{
	get_token();
	switch(*token)
	{
		case '=': eval_exp( *var );
					 break;
		case '[':
					 CVar array_num;
					 array_num.var_type = INT;
					 eval_exp( array_num );
					 AllocArray( var, array_num.value );
					 CloseArray();

					 get_token();
					 if ( *token == '=' ) //sntx_err( INVALID_VAR_INIT );
					 {
							int  index=0;
							CVar *el;

							OpenBrace();

							do
							{
								 //get_token();                        //
								 //printf("<1st %s>", token);          //
								 el = AccessArray( var, index++);
								 eval_exp( *el );
								 get_token(); // get comma.
								 //printf("<2nd %s>", token);          //
							} while (*token==',');
							if (!el->isTail()) sntx_err(TOO_FEW_INIT_VALUES);
							if (*token != '}') sntx_err(CLOSE_BRACE_REQUIRED);
					 } else putback();
					 break;
		default : putback();
	}
}
/* Declare a global variable. */
void decl_global(void)
{

	get_token();  /* get type */
	int type = tok;
	do {  /* process comma-separated list */

		global_vars[gvar_index] = new CVar();
		global_vars[gvar_index]->var_type = type;
		//printf("<1:%i>",var_type);
		get_token();   /* get name */
		global_vars[gvar_index]->SetName(token);

		MakeArray_Init_Var( global_vars[gvar_index] );
		get_token();

		gvar_index++;
	} while (*token == ',');
	if (*token != ';') sntx_err(SEMI_EXPECTED);
}

/* Declard a local variable. */
void decl_local(void)
{
	CVar* i;
	int type;

	get_token();  /* get type */
	//printf("< tok : %i >",tok);
	type = tok;
	do {  /* process comma-separated list */
		i = new CVar();
		i->var_type = type;
		get_token();  /* get var name */
		//printf("< token : %s >",token);
		i->SetName(token);
		//printf("123");
		local_push(*i);
		//printf("456");
		delete i; // i is absolutely not array.

		get_token();
		//printf("< token : %s >",token);
	} while (*token == ',');
	if (*token != ';') sntx_err(SEMI_EXPECTED);
}
/* Push local variable */
void local_push(CVar var)
{
	//printf("<i.cbr:%i>",i.cbr);
	if (lvartos > NUM_LOCAL_VARS) sntx_err(TOO_MANY_LVARS);
	local_var_stack[lvartos]=new CVar();
	//printf("[1]");
	local_var_stack[lvartos]->var_type = var.var_type;
	//printf("[2]");

	local_var_stack[lvartos]->SetName(var.var_name);
	//printf("[3]");
	local_var_stack[lvartos]->cbr = var.cbr;
	//if (i.cbr) local_var_stack[lvartos]->cbrvar=1;

	// allocate array...
	MakeArray_Init_Var(local_var_stack[lvartos]);

	lvartos++;
	//printf("[4]");

}

int isCallByRef(CVar* pVar)
{
	register int i;
	/* first, see if it's a local variable */
	for(i = 0; i < lvartos; i++) if (local_var_stack[i] == pVar) return 1;
	for(i = 0; i < gvar_index; i++) if (global_vars[i] == pVar) return 1;
	return 0;
}

/* free a dynamically allocated local variable memory*/
void local_free(void)
{
	lvartos--;
	if (lvartos < 0) sntx_err(INTERNAL_ERROR);
	if (isCallByRef(local_var_stack[lvartos])) // restore original name.
	{
		 name_pop(local_var_stack[lvartos]);
	}
	else FreeVar(local_var_stack[lvartos]);
}

/* Call a function.
	haha(a, b);
		 ^
		 |
		loc
*/

void call(void)
{
	char *loc, *temp, *functemp;
	// if arg_base is 3, arg_top is 6.. then
	// local_var_stack[3] ~ local_var_stack[6] is the argument

	int lvartemp, arg_base, arg_top;
									 /* token is the name of function.*/
	loc = find_func(token);  /* find entry point of function */
	if (loc == NULL)
	{
		sntx_err(FUNC_UNDEF);  /* function not defined */
	}
	else {
		lvartemp = lvartos;  /* save local var stack index */
		temp = prog;         /* save return location */
		prog = loc;          /* reset prog to start of function */
		arg_base=lvartos;    /* save local var stack index as
										1st argument's index of local_var_stack*/
		get_params();        /* load the function's parameters with */
		arg_top=lvartos-1;   /* save local var stack index -1 as
										last argument's index of local_var_stack*/
		functemp= prog;
		prog = temp;
		get_args(arg_base, arg_top); /* get function arguments. start from '(' */
		temp = prog;         /* save return location */
		func_push(lvartemp); /* save local var stack index */
		prog = functemp;
		interp_block();      /* interpret the function */
		prog = temp;         /* reset the program pointer */
		while(lvartos > lvartemp) local_free(); /*local variable mem free */
		lvartos = func_pop();  /* reset the local var stack */
	}
}

/* Push the arguments to a function onto the local variable stack.

	 haha(a,b)
		  ^
		  |
		 start
*/
void get_params(void)
{
	CVar* temp;
		/* process a comma-separated list of values */
	do {
			 get_token();
			 //printf("<1st token:%s>\n", token);
			 if (*token != ')') {
				  if (tok != INT && tok != CHAR && tok != STRING && tok != File)
						sntx_err(TYPE_EXPECTED);
				  temp = new CVar();
				  temp->var_type = tok;
				  get_token();

				  //printf("<2nd token:%s>\n", token);

				  if (*token =='&')
				  {
						temp->cbr =1;
						get_token();
				  } // defalut is not cbr.
				  /* link parameter name with argument already on local var stack */
				  temp->SetName(token);

				  local_push(*temp);
				  delete temp;

				  get_token();

				  //printf("<3rd token:%s>\n", token);

			 }
			 else break;
	} while (*token == ',');
	if (*token != ')') sntx_err(PAREN_EXPECTED);

}

/* Get function parameters. */
void get_args(int lvars_arg_base, int lvars_arg_top)
{
	int i;
	CVar* param;
	get_token();

	if (*token != '(') sntx_err(PAREN_EXPECTED);

	get_token();
	if (*token != ')')
	{
		 putback();
		 i = lvars_arg_base; /* lvartos is local variable stack index */
		 /* process a comma-separated list of values */
		 do {
				if (i > lvars_arg_top) sntx_err(TOO_MANY_ARGUMENTS);

				// when parameter is array, process as call by reference..
				// if call by reference parameter or array parameter...
				// this will not be deleted cuz a variable which has the same
				// address to this exists, and.. local parameter deleting
				// routine will do not delete this.
				//printf("<i:%i>", i);
				if (local_var_stack[i]->cbr || !local_var_stack[i]->isTail())
				{
					get_token(); // get argument(a variable)'s name.

					CVar* real_var = find_var(token);

					name_push(real_var);
					real_var->SetName( local_var_stack[i]->var_name );

					FreeVar( local_var_stack[i] );

					local_var_stack[i] = real_var;
				}
				else eval_exp( *local_var_stack[i] );
				//printf("<after eval>");
				get_token();
				i++;
		 } while (*token == ',');

		 // in fact the last i is equal to lvars_arg_top. but i was increased by 1.
		 if (i != lvars_arg_top+1) sntx_err(TOO_FEW_ARGUMENTS);
	}
}

/* Return from a function. */
void func_ret(void)
{
	CVar var;
	/* get retrun value, if any */
	eval_exp(var);
	ret_value = var.value;
}

/* free all dynamically allocated global variable memory*/
/* Pop index into local variable stack. */
func_pop(void)
{
	functos--;
	if (functos < 0) sntx_err(RET_NOCALL);
	return (call_stack[functos].lvartos);
}

/* Push index of local variable stack. */
void func_push(int i)
{
	if (functos > FUNC_CALLS)
		sntx_err(NEST_FUNC);
	call_stack[functos].lvartos = i;
	call_stack[functos].is_terminated = 0;
	functos++;
}
void func_return()
{
	call_stack[functos-1].is_terminated = 1;
}
int is_func_returned()
{
	return call_stack[functos-1].is_terminated == 1;
}
//namehead is the head of name stack's implemented list..
//namehead is also top of name stack's top..
//namehead is initialized as shown below..
//namehead.next = NULL;

/*
char name[10][100];

void name_push(CVar* cbrvar)
{
	  strcpy(name[top], cbrvar->var_name);
	  top++;
}
void name_pop(CVar* cbrvar)
{
	  top--;
	  cbrvar->SetName( name[top] );
}*/

void name_push(CVar* cbrvar)
{
	 struct list* new_head = new struct list;
	 new_head->next = namehead;
	 new_head->data = new char[strlen(cbrvar->var_name)+1];
	 strcpy(new_head->data, cbrvar->var_name);
	 //printf("<pushing name : %s\n>", cbrvar->var_name);
	 //getch();
	 namehead = new_head;
}
void name_pop(CVar* cbrvar)
{
	 struct list* t;
	 if (namehead->next == NULL) sntx_err(INTERNAL_ERROR);

	 //printf("<poping name : %s\n>", namehead->data);
	 //getch();

	 cbrvar->SetName(namehead->data);
	 delete namehead->data;
	 t = namehead;
	 namehead = namehead->next;
	 delete t;
}
void name_popall_and_delhead()
{
	 CVar v;
	 while(namehead->next != NULL) name_pop(&v);
	 delete namehead;
}
/* Assign a value to a variable. */
void assign_var(char *var_name, CVar var)
{
	register int i;
	/* first, see if it's a local variable */
	for (i = lvartos - 1; i >= call_stack[functos - 1].lvartos; i--) {
		//printf("<%s, %s>",local_var_stack[i]->var_name, var_name);
		if (!strcmp(local_var_stack[i]->var_name, var_name)) {
			 local_var_stack[i]->AssignVar(var);
			 return;
		}
	}
	/* if not local, try global var table */
	for (i = 0; i < gvar_index; i++)
		if (!strcmp( global_vars[i]->var_name, var_name)) {
			global_vars[i]->AssignVar(var);
			return;
		}
	printf("1");
	sntx_err(NOT_VAR);  /* variable not found */
	printf("2");
}

/* Find the value of a variable. */
CVar* find_var(char *name)
{
	register int i;

	//printf("<%s>",name);
	/* first, see if it's a local variable */
	for (i = call_stack[functos - 1].lvartos; i <= lvartos - 1; i++)
		if (!strcmp(local_var_stack[i]->var_name, name))
			return local_var_stack[i];
	/* otherwise, try global vars */
	//printf("<%i>",gvar_index);
	for (i = 0; i < gvar_index; i++)
		if (!strcmp(global_vars[i]->var_name, name))
			return global_vars[i];
	//printf("3");
	sntx_err(NOT_VAR);  /* variable not found */
	//printf("4");
}


/* Determine if an identifier is a variable. Return 1
	if variable is found; 0 otherwise.
*/
int is_var(char *s)
{
	register int i;

	/* first, see if it's a local variable */
	for (i = lvartos - 1; i >= call_stack[functos - 1].lvartos; i--)
		if (!strcmp(local_var_stack[i]->var_name, s))
			return 1;
	/* otherwise, try global vars */
	for (i = 0; i < gvar_index; i++)
		if (!strcmp(global_vars[i]->var_name, s))
			return 1;
	return 0;
}
/* Execute an IF statement. */
void exec_if(void)
{
	CVar cond;
	//printf("[starting if]");
	eval_exp(cond);  /* get left expression */

	if (cond.value) {  /* is true so process target of IF */
		 //printf("[running if]");
		 interp_block();
	}
	else {  /* otherwise skip around IF block and
				  process the ELSE, if present */
	  find_eob();  /* find start of next line */
	  //printf("<prog:%s>",prog);

	  get_token();
	  if (tok != ELSE) {
			putback();  /* restore token if no ELSE is present */
			return;
	  }
	  interp_block(); /* do else interpretation*/
	}
}

/* Execute a while loop. */
void exec_while(void)
{
	CVar cond;
	char *temp;

	putback();
	temp = prog;  /* save location of top of while loop */
	get_token();
	eval_exp(cond);  /* check the conditional expression */
	if (cond.value) interp_block();  /* if true, interpret */
	else {  /* otherwise, skip around loop */
		find_eob();
		return;
	}
	prog = temp;  /* loop back to top */
}

/* Execute a do loop. */
void exec_do(void)
{
	CVar cond;
	char *temp;

	putback();
	temp = prog;  /* save location of top of do loop */

	get_token();  /* get start of loop */
	interp_block();  /* interpret loop */
	get_token();
	if (tok != WHILE) sntx_err(WHILE_EXPECTED);
	eval_exp(cond);  /* check the loop condition */
	if (cond.value) prog = temp; /* if true loop; otherwise, continue on */
}

/*  original... find_eob..
void find_eob(void)
{
	int brace;

	get_token();
	brace = 1;
	do {
		get_token();
		if (*token == '{') brace++;
		else if (*token == '}') brace--;
	} while (brace);
}*/
/* Find the end of a block. */
void find_eob(void)
{
	int brace;
	int brace_found=0;

	get_token();
	brace=1;
	if (*token=='{') brace_found=1;
	do {
			get_token();
			//printf("<b:%i,p:%i,%s>",brace,paren_found,token);
			if (*token == '{') brace++;
			else if (*token == '}') brace--;
			if (!brace_found && *token==';') break;
	} while (brace);// || (brace_found || *token!=';') );
	//printf("[end]"); getch();
}

/* Execute a while loop. */
void exec_for(void)
{
	CVar cond;
	char *temp, *temp2;
	int brace;

	get_token();
	eval_exp(cond);  /* initialization expression */
	if (*token != ';') sntx_err(SEMI_EXPECTED);
	prog++; /* get past the ; */
	temp = prog;
	for (;;) {
		eval_exp(cond);  /* check the condition */
		if (*token != ';') sntx_err(SEMI_EXPECTED);
		prog++;  /* get past the ;  */
		temp2 = prog;

		/* find the start of the for block */
		brace = 1;
		while (brace) {
			 get_token();
			 if (*token == '(') brace++;
			 if (*token == ')') brace--;
		}

		if (cond.value) interp_block();  /* if true, interpret */
		else {  /* otherwise, skip around loop */
			 find_eob();
			 return;
		}
		prog = temp2;
		eval_exp(cond);  /* do the increment */
		prog = temp;  /* loop back to top */
	}
}
