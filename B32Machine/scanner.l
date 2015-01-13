%option yylineno noyywrap

%{
#include<string.h>
#include<stdlib.h>
#include "types.h"
#include"parser.tab.h"
extern int lineno;
YYSTYPE yylval;
%}

DIGIT	[0-9]
ID	[a-z][a-z0-9]*
int defining=0;

%%
"="		 {return ASSOP;}
"++"		 {return UADD;}
int    		 {return INT;}
{DIGIT}+	 { yylval.intval =(char *) strdup(yytext);return(NUMBER);}
{ID}		 { yylval.id.name = (char *) strdup(yytext);return(ID);}
[ \t]+		 /* eat up whitespace */
\n		 {lineno=yylineno;newlinegen();}
.		 { return(yytext[0]);}

%%


