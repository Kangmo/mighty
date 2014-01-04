/* Recursive descent parser for integer expressions
	which may include variables and function calls.   */
#include <setjmp.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#include "lc.h"
#include "debug.h"

#ifndef DEBUG
	#include "headers.h"
#endif
enum tok_type {DELIMITER, IDENTIFIER, NUMBER, KEYWORD, TEMP,
			 QUOTE, BLOCK};

enum tokens {ARG, CHAR, INT, STRING, File, IF, ELSE, FOR, DO, WHILE, SWITCH,
		  RETURN, EOL, FINISHED, BUFF, END};

enum double_ops {LT = 1, LE, GT, GE, EQ, NE, AND, OR};

extern char *prog; /* current location in source code */
extern char *p_buf; /* points to start of program buffer */
extern jmp_buf e_buf; /* hold environment for longjmp() */

/* This is the function call stack. */
extern struct func_type func_stack[NUM_FUNC];

/* Keyword table */
extern struct commands table[];

/* "Standard library" functions are declared here so
	they can be put into the internal function table that
	follows.
*/
print(void);
func_getln(void);
func_getline(void);
func_gettime(void);
func_getdate(void);
func_getlevel(void);
func_getpoint(void);
func_getlefttime(void);
func_getdown(void);
func_gettimebank(void);
func_setinfo(void);
func_getid(void);
func_getname(void);
func_atoi(void);
func_itoa(void);
func_delay(void);
func_randomize(void);
func_random(void);
func_execprotocol(void);
func_selectprotocol(void);
func_filepush(void);
func_clearstack(void);
func_setstr(void);
func_midstr(void);
func_strlen(void);
func_fopen(void);
func_fclose(void);
func_fgets(void);
func_fputs(void);
func_system(void);
func_getdir(void);
func_getcwd(void);
func_getch(void);
func_putch(void);
func_comgetch(void);
func_computch(void);
func_hangup(void);
func_isonline(void);
func_commsendready(void);
func_commrecvready(void);
func_siohayes(void);


struct intern_func_type {
	char *f_name;  /* function name */
	int (* p)();  /* pointer to the function */
} intern_func[] = {
	{"print", print},
	{"gets",  func_getln},
	{"getline", func_getline},
	{"gettime", func_gettime},
	{"getdate", func_getdate},
	{"GetLevel", func_getlevel},
	{"GetPoint", func_getpoint},
	{"GetLefttime", func_getlefttime},
	{"GetDown", func_getdown},
	{"GetTimebank", func_gettimebank},
	{"SetUserinfo", func_setinfo},
	{"GetId", func_getid},
	{"GetName", func_getname},
	{"atoi", func_atoi},
	{"itoa", func_itoa},
	{"delay", func_delay},
	{"randomize", func_randomize},
	{"random", func_random},
	{"ExecProtocol", func_execprotocol},
	{"SelProtocol", func_selectprotocol},
	{"FilePush", func_filepush},
	{"ClearFile", func_clearstack},
	{"setstr", func_setstr},
	{"midstr", func_midstr},
	{"strlen", func_strlen},
	{"fopen", func_fopen},
	{"fclose", func_fclose},
	{"fgets", func_fgets},
	{"fputs", func_fputs},
	{"system", func_system},
	{"GetDir", func_getdir},
	{"getcwd", func_getcwd},
	{"getch", func_getch},
	{"putch", func_putch},
	{"comgetch", func_comgetch},
	{"computch", func_computch},
	{"HangUp", func_hangup},
	{"IsOnline", func_isonline},
	{"CanSend", func_commsendready},
	{"CanRecv", func_commrecvready},
	{"Hayes", func_siohayes},
	{"", 0 } /* null terminate the list */
};

extern char token[80]; /* string representation of token */
extern char token_type; /* contains type of token */
extern char tok;  /* internal representation of token */

extern int ret_value; /* function return value */

void eval_exp(CVar &var);
void eval_exp_logic(CVar &var);
void eval_exp1(CVar &var);
void eval_exp2(CVar &var);
void eval_exp3(CVar &var), eval_exp4(CVar &var);
void eval_exp5(CVar &var), atom(CVar &var);
void eval_exp0(CVar &var);
void sntx_err(int error), putback(void);
void assign_var(char *var_nme, CVar var);
int isdelim(char c), look_up(char *s), iswhite(char c);
int get_token(void);
CVar* find_var(char *name);
int internal_func(char *s);
int is_var(char *s);
char *find_func(char *name);
void call(void);

/* Entry point into parser. */
void eval_exp(CVar &var)
{
	get_token();
	/*if (!*token) {
		sntx_err(NO_EXP);
		return;
	}*/
	if (*token == ';') {
		var.SetValue(0);  /* empty expression */
		return;
	}
	eval_exp0(var);
	putback();  /* return last token read to input stream */
}

/* Process an assignment expression */
void eval_exp0(CVar &var)
{
	// Later, dynamically allocate array..
	char temp[ID_LEN];  /* holds name of var receiving the assignment */
	char* temp_prog;
	register int temp_tok, array_index=0;

	if (token_type == IDENTIFIER) {
		if (is_var(token)) {  /* if a var, see if assignment */
			 strcpy(temp, token);
			 temp_tok = token_type;

			 temp_prog = prog;

			 get_token();

			 if ( *token == '[' ) // when array identifier.
			 {
				 CVar array_num;
				 array_num.var_type = INT;
				 eval_exp( array_num );
				 array_index = array_num.value;
				 CloseArray();
				 get_token();
			 }

			 if (*token == '=') {  /* is an assignment */

				 get_token();     // to call eval_exp0...

				 eval_exp0(var);  /* get value to assign */

				 // if not an array identifier.
				 if ( array_index == 0 ) assign_var(temp, var);  /* assign the value */
				 else AccessArray(find_var(temp), array_index)->SetVar( var );

				 return;
			 }
			 else {  /* not an assignment */
				 prog = temp_prog;  /* restore original token */
				 strcpy(token, temp);
				 token_type = temp_tok;
			 }
		}
	}
	eval_exp_logic(var);
}

/* This array is used by eval_exp1(). Because
	some compilers cannot initialize an array within a
	function it is defined as a global variable.
*/
char logicops[3] = {
	AND, OR, 0
};

char relops[7] = {
	LT, LE, GT, GE, EQ, NE, 0
};

/* Process relational operators. */
void eval_exp_logic(CVar &var)
{
	CVar partial_var;
	register char op;

	eval_exp1(var);
	op = *token;
	if (strchr(logicops, op)) {
		get_token();
		eval_exp0(partial_var);
		switch(op) {   /* perform the relational operation */
	 case AND:
		 var.value = var.value && partial_var.value;
		 break;
	 case OR :
		 var.value = var.value || partial_var.value;
		 break;
		}
	}
}

/* Process relational operators. */
void eval_exp1(CVar &var)
{
	CVar partial_var;
	register char op;

	eval_exp2(var);
	op = *token;
	if (strchr(relops, op)) {
		get_token();
		eval_exp2(partial_var);
		switch(op) {   /* perform the relational operation */
	 case LT :
		 var.value = var.value < partial_var.value;
		 break;
	 case LE :
		 var.value = var.value <= partial_var.value;
		 break;
	 case GT :
		 var.value = var.value > partial_var.value;
		 break;
	 case GE :
		 var.value = var.value >= partial_var.value;
		 break;
	 case EQ :
		 if (var.var_type==STRING)
				var.value = !strcmp(var.string, partial_var.string);
		 else var.value = var.value == partial_var.value;
		 break;
	 case NE :
		 if (var.var_type==STRING)
				var.value = strcmp(var.string, partial_var.string);
		 else var.value = var.value != partial_var.value;
		 break;
		}
	}
}

/* Add or subtract two terms. */
void eval_exp2(CVar &var)
{
	register char op;
	CVar partial_var;

	eval_exp3(var);
	while ((op = *token) == '+' || op == '-') {
		get_token();
		eval_exp3(partial_var);
		switch(op) {  /* add or subtract */
	 case '-' :
		 var.value = var.value - partial_var.value;
		 break;
	 case '+' :
		 if (var.var_type==STRING)
		 {
			  int concat_len = strlen(var.string)+strlen(partial_var.string);
			  char *tmp = new char[concat_len+1];
			  strcpy(tmp,var.string);
			  strcat(tmp,partial_var.string);
			  var.SetString(tmp);
			  delete tmp;
		 }
		 else var.value = var.value + partial_var.value;
		 break;
		}
	}
}

/* Multiply or divide two factors. */
void eval_exp3(CVar &var)
{
	register char op;
	CVar partial_var;

	eval_exp4(var);
	while ((op = *token) == '*' || op == '/' || op == '%') {
		get_token();
		eval_exp4(partial_var);
		switch(op) {  /* mul, div, or modulus */
	 case '*' :
		 var.value = var.value * partial_var.value;
		 break;
	 case '/' :
		 var.value = var.value / partial_var.value;
		 break;
	 case '%' :
		 var.value = var.value % partial_var.value;
		 break;
		}
	}
}

/* Is a unary + or -. */
void eval_exp4(CVar &var)
{
	register char op;

	op = '\0';
	if (*token == '+' || *token == '-') {
		op = *token;
		get_token();
	}
	eval_exp5(var);
	if (op)
		if (op == '-') var.value = -var.value;
}

/* Process parenthesized expression. */
void eval_exp5(CVar &var)
{
	if ((*token == '(')) {
		get_token();
		eval_exp0(var);   /* get subexpression */
		if (*token != ')') sntx_err(PAREN_EXPECTED);
		get_token();
	}
	else
		atom(var);
}

/* Find value of number, variable of function. */
void atom(CVar &var)
{
	int i;

	switch(token_type)  {
		case IDENTIFIER :
			 i = internal_func(token);
			 if (i != -1) {   /* call "standard library" function */
				 var.var_type = INT;
				 var.value = (*intern_func[i].p)();
			 }
			 else
				 if (find_func(token)) {  /* call user-defined function */

					 call();
					 var.var_type = INT;
					 var.value = ret_value;
				 }
				 else { // when IDENTIFIER - process accessing array member.


							 CVar* new_var = find_var(token);

							 get_token();
							 if ( *token == '[' ) // when array identifier.
							 {
								 CVar array_num;
								 array_num.var_type = INT;
								 eval_exp( array_num );
								 var.SetVar( *AccessArray(new_var, array_num.value) );
								 //printf("<acc:%s>",AccessArray(new_var, array_num.value)->string);
								 CloseArray();
							 }else   // when not an array identifier.
								  {
										putback();
										var.SetVar(*new_var);
								  }
						}
			 get_token();
			 return;
		case NUMBER : /* is numeric constant */

			 var.var_type = INT;
			 var.SetValue(atoi(token));
			 get_token();
			 return;
		case DELIMITER : /* see if character constant */
			 //printf("prog:%c",(int)*token);
			 if (*token == '\'') {
				 var.var_type = CHAR;

				 if (*prog == '\\')
				 {
					  switch(*(++prog))
					  {
						  case 'n' : var.SetValue((int)'\n');
										 break;
						  case 'r' : var.SetValue((int)'\r');
										 break;
						  case 't' : var.SetValue((int)'\t');
										 break;
						  case '\'': var.SetValue((int)'\'');
										 break;
						  case '\"': var.SetValue((int)'\"');
										 break;
						  case '\\': var.SetValue((int)'\\');
										 break;
					  }
				 }else var.SetValue((int)*prog);

				 prog++;

				 if (*prog != '\'') sntx_err(APOST_EXPECTED);
				 prog++;
				 get_token();
			 }
			 return;
		case QUOTE :
			 var.var_type = STRING;
			 var.SetString(token);
			 get_token();
			 return;
		default :
			 if (*token == ')') return;  /* process empty expression */
			 else sntx_err(SYNTAX);  /* syntax error */
	}
}

/* Display an error messge. */
void sntx_err(int error)
{
	#ifdef DEBUG
	static char *e[] = {
		"Syntax error",                                      //SYNTAX
		"The number of \'(\' and \')\' is not equal.",       //UNBAL_PARENS
		"Expression does not exists.",                       //NO_EXP
		"\'=\' is required.",                                //EQIUALS_EXPECTED
		"Undefined variable.",                               //NOT_VAR
		"Parameter error",                                   //PARAM_ERR
		"\';\' expected at the end of sentence.",            //SEMI_EXPECTED
		"The number of \'{\' and \'}\' is not equal.",       //UNBAL_BRACES
		"Undefined function.",                               //FUNC_UNDEF
		"Unsuppoted variable type.",                         //TYPE_EXPECTED
		"Too many funcion callings.",                        //NEST_FUNC
		"Return without function call.",                     //RET_NOCALL
		"\'(\' or '\)\' is expected.",                       //PAREN_EXPECTED
		"\'while\' command is exprected.",                   //WHILE_EXPECTED
		"Untermined string. \'\"\' is expected.",            //QUOTE_EXPECTED
		"Not a string.",                                     //NOT_TEMP
		"Too many local variables.",                         //TOO_MANY_LVARS
		"Defining a variable with initializing is not supported.", //INVALID_VAR_INIT
		"Scripter's bug. send your source to programer.",    //INTERNAL_ERROR
		"Type mismatch.",                                    //TYPE_MISMATCH
		"Too long string length.",                           //NOT_ENOUGH_MEM
		"Number of parameters is not equal to function's definition.", //PARAM_NOT_CORRES
		"\',\'is required.",                                 //COMMA_EXPECTED
		"Out of string index.",                              //OUT_OF_INDEX
		"\'{\' is required.",                                //OPEN_BRACE_REQUIRED
		"File Close Failed.",                                //FILE_CLOSE_ERROR
		"Out of array index.",                               //ARRAY_OUT_OF_INDEX
		"] is required.",                                    //CLOSE_ARRAY_EXPECTED
		"Too many arguments are listed.",                 	  //TOO_MANY_ARGUMENTS
		"More arguments are required.",	                    //TOO_FEW_ARGUMENTS
		"\'}\' is required.",
		"More initializing values are required.",
		"\' is expected.",
		"Unexpected end of source file."
	};
	#else
	static char *e[] = {
		"¢…¤ó·¡ ¸i¡µ–A´ö¯s“¡”a",
		"\'(\'‰ÉÑ¡µÁ \')\'‰ÉÑ¡· ®ˆa  x»¡ ´g¯s“¡”a",
		"®¯¢(Ðq®¯¢)·¡ ¹¥¸Ða»¡ ´g¯s“¡”a",
		"\'=\'ˆa Ï©¶aÐs“¡”a",
		"¸÷·Ða»¡ ´g·e ¥e®·³“¡”a",
		"Ìaœa£¡ÈáµA µAœáˆa ·¶¯s“¡”a",
		"¢…¸w·  a»¡ bµA \';\'·i ý»¡ ´g´v¯s“¡”a",
		"\'{\'‰ÉÑ¡µÁ \'}\'‰ÉÑ¡· ®ˆa  x»¡ ´g¯s“¡”a",
		"¸÷·Ða»¡ ´g·e Ðq®·³“¡”a",
		"int ™¡“e char ™¡“e string·a¡ ¥e®· Ñw·i »¡¸÷Ðaµa´¡ Ðs“¡”a",
		"á¢  g·e Ðq®Ÿi ¦‰œö¯s“¡”a",
		"Ðq® Ñ¡Â‰·e Ða»¡•¡ ´g‰¡ return·i Ðaµv¯s“¡”a",
		"\'(\'‰ÉÑ¡a \')\'‰ÉÑ¡ˆa Ï©¶aÐs“¡”a",
		"\'while\'¢…·¡ Ï©¶aÐs“¡”a",
		"\'\"\'·i ¬a¶wÐaµa ¢…¸aµi· {·i »¡¸÷Ðaµa´¡ Ðs“¡”a",
		"¢…¸aµi·¡ ´a“³“¡”a",
		"»¡µb¥e®ˆa á¢  g¯s“¡”a",
		"¥e®¬å´å¯¡ Á¡‹¡ÑÁŸi Ði® ´ô¯s“¡”a",
		"¯aÇaŸ³Ëa ´å´á· ¤á‹a·³“¡”a. ­¡¯aŸi ¹A¸b¸aµA‰A ¥¡º­A¶a",
		"Ñw(type)·¡ ”aŸe ¥e®¬a·¡µA¬á ˆt·i Ði”wÐaµv¯s“¡”a",
		"¢…¸aµi ¥e®ˆa á¢  g¯s“¡”a",
		"Ìaœa£¡Èá· ®ˆa Ðq®¬å´å¦¦…‰Á  x»¡ ´g¯s“¡”a",
		"\',\'ˆa Ï©¶aÐs“¡”a",
		"\'{\' is required.",                                //OPEN_BRACE_REQUIRED
		"File Close Failed.",
		"Out of array index.",
		"] is required.",
		"Too many arguments are listed.",                 	  //TOO_MANY_ARGUMENTS
		"More arguments are required.",	                    //TOO_FEW_ARGUMENTS
		"\'}\' is required.",
		"More initializing values are required.",
		"\' is expected.",
		"Unexpected end of source file."
	};
	#endif
	if (error != TERMINATE_PROG)
	{
		 char *p;
		 int linecount = 0;
		 register int i;
		 p = p_buf;
		 while (p <= prog) {  /* find line number of error */
			p++;
			if (*p == '\r') {
				linecount++;
			}
		 }
		 c_hprintf("%s (%dº‰)\n\r", e[error], linecount+1);
		 for (i = 0; i < 20 && p > p_buf && *p != '\n'; i++, p--);
		 for(;*p != '\r'; p++) c_hputch(*p);

		 ReadDataFile(197); // script program is terminated
	}
	longjmp(e_buf, 1); /* return to save pointer */
}

char* before_prog;
/* Get a token. */
get_token(void)
{

	register char *temp;

	token_type = 0; tok = 0;

	temp = token;
	*temp = '\0';

	/* skip over white space */
	while (iswhite(*prog) && *prog) ++prog;

	if (*prog == '\r') {
		++prog;
		++prog;
		/* skip over white space */
		while (iswhite(*prog) && *prog) ++prog;
	}

	/* look for comments */
	if (*prog == '/')
		if (*(prog + 1) == '*') {  /* is a comment */
	 prog += 2;
		do {  /* find end of comment */
	 while (*prog != '*') prog++;
	 prog++;
		} while (*prog != '/');
		prog++;
	}

	before_prog = prog; // save prog for putback function.

	if (*prog == '\0') {  /* end of file */
		*token = '\0';
		tok = FINISHED;
		return (token_type = DELIMITER);
	}

	if (strchr("{}", *prog)) {  /* block delimiters */
		*temp = *prog;
		temp++;
		*temp = '\0';
		prog++;
		return (token_type = BLOCK);
	}


	if (strchr("!<>=|&", *prog)) {  /* is or might be a relation(logical) operator */
		switch(*prog) {
	 case '|' :
		 if (*(prog + 1) == '|') {
			 prog++; prog++;
			 *temp = OR;
			 temp++; *temp = OR; temp++;
			 *temp = '\0';
		 }
		 break;
	 case '&' :
		 if (*(prog + 1) == '&') {
			 prog++; prog++;
			 *temp = AND;
			 temp++; *temp = AND; temp++;
			 *temp = '\0';
		 }
		 break;
	 case '=' :
		 if (*(prog + 1) == '=') {
			 prog++; prog++;
			 *temp = EQ;
			 temp++; *temp = EQ; temp++;
			 *temp = '\0';
		 }
		 break;
	 case '!' :
		 if (*(prog + 1) == '=') {
			 prog++; prog++;
			 *temp = NE;
			 temp++; *temp = NE; temp++;
			 *temp = '\0';
		 }
		 break;
	 case '<' :
		 if (*(prog + 1) == '=') {
			 prog++; prog++;
			 *temp = LE; temp++; *temp = LE;
		 }
		 else {
			 prog++;
			 *temp = LT;
		 }
		 temp++;
		 *temp = '\0';
		 break;
	 case '>' :
		 if (*(prog + 1) == '=') {
			 prog++; prog++;
			 *temp = GE; temp++; *temp = GE;
		 }
		 else {
			 prog++;
			 *temp = GT;
		 }
		 temp++;
		 *temp = '\0';
		 break;
		}
		if (*token) return (token_type = DELIMITER);
	}

	if (strchr("+-*^/%=;()[],\'&", *prog)) {  /* delimiter */
		*temp = *prog;
		prog++;  /* advance to next position */
		temp++;
		*temp = '\0';
		return (token_type = DELIMITER);
	}

	if (*prog == '"') {  /* quoted string */
		prog++;
		while (*prog != '"' && *prog != '\r' && *prog) *temp++ = *prog++;
		if (*prog == '\r' || !*prog) sntx_err(QUOTE_EXPECTED);
		prog++; *temp = '\0';
		//printf("<quote string : %s>", token);
		return (token_type = QUOTE);
	}

	if (isdigit(*prog)) { /* number */
		while (!isdelim(*prog) && *prog) *temp++ = *prog++;
		if (!*prog) sntx_err(UNEXPECTED_END);
		*temp = '\0';
		return (token_type = NUMBER);
	}

	if (!iswhite(*prog) && *prog!='\n' && *prog!='\r')
	{
		while (!isdelim(*prog) && *prog) *temp++ = *prog++;
		if (!*prog) sntx_err(UNEXPECTED_END);
		token_type = TEMP;
	}
	*temp = '\0';

	/* see if a string is a command or a variable */
	if (token_type == TEMP) {
		tok = look_up(token); /* convert to internal rep */
		if (tok) token_type = KEYWORD;  /* is a keyword */
		else token_type = IDENTIFIER;
	}
	return token_type;
}

/* Return a token to input stream. */
void putback(void)
{
	prog = before_prog;
}

/* Look up a token's internal representation in the token table. */
look_up(char *s)
{
	register int i;

	for (i = 0; *table[i].command; i++)
	{
		if (!strcmp(table[i].command, s)) return table[i].tok;
	}
	return 0;  /* unknown command */
}

/* Return index of internal library function or -1 if not found. */
internal_func(char *s)
{
	int i;

	for (i = 0; intern_func[i].f_name[0]; i++) {
		if (!strcmp(intern_func[i].f_name, s))
			 return i;
	}
	return -1;
}

/* Return true if c is a delimiter. */
isdelim(char c)
{
	if (strchr(" !;,+-<>'/*%^=()[]&|", c) || c == 9 ||
		 c == '\r' || c == 0) return 1;
	return 0;
}

/* Return 1 if c is space or tab. */
iswhite(char c)
{
	if (c == ' ' || c == '\t') return 1;
	else return 0;
}

void OpenParen()
{
	get_token();
	if (*token != '(') sntx_err(PAREN_EXPECTED);
}

void CloseParen()
{
	get_token();
	if (*token != ')') sntx_err(PAREN_EXPECTED);
}

void Semicolon()
{
	get_token();
	if (*token != ';') sntx_err(SEMI_EXPECTED);
	putback();
}

void Comma()
{
	get_token();
	if (*token!=',') sntx_err(PARAM_NOT_CORRES);
}

// if token is not open array, returns 0 and putback();
// else return 1.
/*
int OpenArray()
{
	get_token();
	if (*token != '[') return 1;
	else
	{
		 putback();
		 return 0;
	}
}*/

// This function is called only when open array is found.
// So, if Close Array is not found, it is error.
void CloseArray()
{
	get_token();
	if (*token != ']') sntx_err(CLOSE_ARRAY_EXPECTED);
}
void OpenBrace()
{
	get_token();
	if (*token!='{') sntx_err( OPEN_BRACE_REQUIRED );
}
/*
void CloseBrace()
{
	get_token();
	if (*token!='}') sntx_err( CLOSE_BRACE_REQUIRED );
}*/