#include <string.h>
#include <alloc.h>
#include "lc.h"
#include <stdio.h>
#include <conio.h>
//#include <conio.h>
void sntx_err(int error);
enum tokens {ARG, CHAR, INT, STRING, File, IF, ELSE, FOR, DO, WHILE,
				 SWITCH, RETURN, EOL, FINISHED, BUFF, END};

CVar::CVar()
{

	 var_type =-1;
	 var_name =NULL;
	 file   = NULL;

	 string = NULL;
	 SetString("");


	 value = 0;
	 cbr = 0;

	 next = NULL;
	 prev = NULL;
}

// be careful..  it can go through recursion.
// do not use AssignVar, SetVar.. and so on.
// which makes to run this function again.
// these functions gets argment with the CVar type...
// and calls this function again.
CVar::CVar(CVar &var)
{
	 value = 0;
	 file   = NULL;
	 string = NULL;
	 var_name = NULL;
	 cbr  = var.cbr;
	 var_type = var.var_type;
	 SetName(var.var_name);

	 next = var.next;
	 prev = var.prev;

	 switch(var_type)
	 {
		  case INT    :
		  case CHAR   : SetValue(var.value);
							 break;
		  case STRING : SetString(var.string);
							 break;
		  case File   : SetFile(var.file);
							 break;
		  default :  sntx_err(INTERNAL_ERROR);
	 }
}

CVar::~CVar()
{
	 // to delete var_name, var must not be copied object.
	 if (var_name) delete var_name;
	 if (string) delete string;
}

/* in case of file, CVar do not concern about opening and closing files.*/
void CVar::SetFile(FILE* fp)
{
	 file = fp;
}
void CVar::SetString(char *str)
{

	 // if memory is allocated, and not copied object, dealloc memory.
	 if (string) delete string;

	 string = new char[strlen(str)+1];
	 if (!string)
	 {
		  sntx_err(NOT_ENOUGH_MEM);
	 }
	 strcpy(string, str);
}
void CVar::SetName(char *str)
{

	 if ( var_name ) delete var_name;
	 var_name = new char[ strlen(str)+1 ];
	 if ( !var_name ) sntx_err(NOT_ENOUGH_MEM);
	 strcpy(var_name, str);
}

void CVar::SetValue(int val)
{
	 value = val;
}

void CVar::SetVar(class CVar var)
{
	 var_type = var.var_type;
	 AssignVar(var);
}

void CVar::AssignVar(class CVar var)
{
	 switch(var_type)
	 {
		  case INT    :
		  case CHAR   : SetValue(var.value);
							 break;
		  case STRING : SetString(var.string);
							 break;
		  case File  : SetFile(var.file);
		  default : sntx_err(INTERNAL_ERROR);
	 }
}

// if this is not array, this function returns 'this' pointer.
CVar* CVar::GetTail()
{
	 CVar* var = this;
	 while( !var->isTail() ) var = var->next;
	 return var;
}

// returns 1 : when success
// returns 0 : when fail (not enough memory)
// name of new variable which follows head is NULL.
// this assume head is already allocated.
int AllocArray(CVar* head, int el_num)
{
	 CVar* var=head;

	 while( --el_num > 0 )
	 {
		  var->next = new CVar();
		  var->next->prev = var;
		  var->next->var_type = var->var_type;

		  var = var->next;
	 }
	 var->next = NULL; //make the last element tail.
}

// this function does not free head.
void FreeArray(CVar* head)
{
	 CVar* var = head->GetTail();
	 CVar* prev_var;
	 while(!var->isHead())
	 {
		 prev_var = var->prev;
		 delete var;
		 var = prev_var;
	 }
}

// this function free all array members including head.
void FreeVar(CVar* var)
{
	 FreeArray(var);
	 delete var;
}

// returns pointer of object : when success
// returns null : when fail (out of array index)
CVar* AccessArray(CVar* head, int index)
{
	 CVar* var=head;

	 while(--index >= 0)
	 {
		 var = var->next;
		 if (var->isTail()) break;
	 }
	 // if input of index is 0, index becomes -1
	 // if input of index is 1, index becomes 0
	 // if input of index is 2, index becomes 0
	 // if input of index is greater or equal than number of array elements,
	 // index becomes ---> index > 0
	 if (index <= 0) return var;
	 else sntx_err(ARRAY_OUT_OF_INDEX);
	 return NULL;
}
