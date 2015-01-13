%{

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<limits.h>

#include "codegenerator.h"

#include "types.h"


int errors=0;
extern  int yylex();
extern  int yyparse();
extern  FILE *yyin;
extern int line_num;
 
int lineno=1;



%}



%union value
{
 char* intval;
 struct identifier id;
 int attr;
 
}

%start block
%token <intval> NUMBER
%token <id> ID
%token ASSOP 
%token UADD
%token INT


%type <attr> dec
%type <id> A E


%left '+'
%nonassoc UADD

%%


block :	'{'
	 declarations	{allocate();}
	  assignments	 {codegen(); YYACCEPT;}
	'}'

 
;

declarations :	dec';'
		| declarations dec ';'
;

dec :	 INT  ID	{addref(lineno,$2.name,1,0);$2.place=getloc($2.name);$2.type=1;}
	|dec ',' ID		{addref(lineno,$3.name,1,0);$3.place=getloc($3.name); $3.type=$1; $$=$1;}
	|dec ';'		{$$=$1;}
;

assignments :	 A ';'
		| assignments A ';'
;

A:		ID ASSOP E	{$1.place=getloc($1.name); gen('=',$3.place,-1,$1.place);}
;

E:		E UADD		{addref(lineno,"1",1,1);int t=newtemp();int loc=getloc("1"); $$.place=t;gen('+',$1.place,loc, $$.place 					);}		
		|E'+'E		{int t=newtemp(); $$.place=t;gen('+',$1.place,$3.place,$$.place);}
		|'('E')'	{$$.place=$2.place;}
		
		| ID		{$1.place=getloc($1.name); $$.place=$1.place;}
		| NUMBER	{addref(lineno,$1,1,1); $$.place=getloc($1);}
;


%%


int main(int argc, char *argv[])
{
 extern FILE *yyin;
 argv++;

yyin = fopen(argv[0], "r" );

/*yydebug = 1;*/
errors = 0;

yyparse ();





printrefs();
fclose(yyin);
exit(0);
}

yyerror ( char *s ) /* Called by yyparse on error */
{
errors++;
printf ("%s\n at line no %d\n", s,lineno);
}



