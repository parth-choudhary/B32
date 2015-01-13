%{
 int ccount=0;
 int wcount=0;
 int lcount=0;
%}

%%

[a-zA-Z]+	{wcount++;ccount=strlen(yytext);}
\n		{lcount++;ccount++;}
.		{ccount++;}

%%

main(int argc,char **argv)
{
 yylex();
 printf("words=%d\ncharacters=%d\nlines=%d\n",wcount,ccount,lcount);
}
