/* fb2-5 C cross-ref */
%option noyywrap nodefault yylineno

/* integer length */
ILEN	([Uu](L|l|LL|ll)?|(L|l|LL|ll)[Uu]?)

/* Universal Character Name */
UCN	(\\u[0-9a-fA-F]{4}|\\U[0-9a-fA-F]{8})

%{
struct symbol {
struct info *infolist;
char *name;
};

struct info {
int lineno;
int offset;
int type;
};

struct bufstack {
struct bufstack *prev;
YY_BUFFER_STATE bs;
int lineno;
char *filename;
FILE *f;
} *curbs;

//increment the count
int symcount=0;
int offset=0;

/* a variable name */
/* 01 - definition */
/* simple symtab of fixed size */
#define NHASH 9997
struct symbol symtab[NHASH];
struct symbol *lookup(char*);
void addref(int, char*, int,int);
char * curfilename;

int defining;
/* names are probably definitions */
%}
%%




int 	{ defining = 1; }

0[0-7]*{ILEN}?
[1-9][0-9]*{ILEN}?			{addref(yylineno, yytext, 1,1);}
0[Xx][0-9a-fA-F]+{ILEN}?




";"		{ defining = 0; }
"("|")"|","
"++"|"--"|"&"|"*"|"+"|"-"|"~"|"!"|"="


([_a-zA-Z]|{UCN})([_a-zA-Z0-9]|{UCN})*	{addref(yylineno, yytext, defining,0); }

[ \t\n]+




<<EOF>>		{  if(!popfile()) yyterminate(); }

.		{ printf("%d: Mystery character '%s'\n", yylineno, yytext);}
%%

int newfile(char *fn)
{
FILE *f = fopen(fn, "r");
struct bufstack *bs = malloc(sizeof(struct bufstack));
/* die if no file or no room */
if(!f) { perror(fn); return 0; }
if(!bs) { perror("malloc"); exit(1); }
/* remember state */
if(curbs)curbs->lineno = yylineno;
bs->prev = curbs;
/* set up current entry */
bs->bs = yy_create_buffer(f, YY_BUF_SIZE);
bs->f = f;
bs->filename = fn;
yy_switch_to_buffer(bs->bs);
curbs = bs;
yylineno = 1;
curfilename = fn;
return 1;
}

int
popfile(void)
{
struct bufstack *bs = curbs;
struct bufstack *prevbs;
if(!bs) return 0;
/* get rid of current entry*/
fclose(bs->f);
yy_delete_buffer(bs->bs);
/* switch back to previous */
prevbs = bs->prev;
free(bs);
if(!prevbs) return 0;
yy_switch_to_buffer(prevbs->bs);
curbs = prevbs;
yylineno = curbs->lineno;
curfilename = curbs->filename;
return 1;
}

/* hash a symbol */
static unsigned symhash(char *sym)
{
unsigned int hash = 0;
unsigned c;
while(c = *sym++) hash = hash*9 ^ c;

return hash;
}





struct symbol * lookup(char* sym)
{
struct symbol *sp = &symtab[symhash(sym)%NHASH];
int scount = NHASH;
int loc=0;
/* how many have we looked at */
while(--scount >= 0) {
if(sp->name && !strcmp(sp->name, sym)) {return sp;}
if(!sp->name) {
sp->name = strdup(sym);
sp->infolist = 0;
return sp;
}
/* new entry */
loc++;
printf("loc= %d\n",loc);
if(++sp >= symtab+NHASH) sp = symtab; /* try the next entry */
}
fputs("symbol table overflow\n", stderr);
abort(); /* tried them all, table is full */
}



int getloc(char *sym)
{
  
  int loc= symhash(sym)%NHASH,count=0;
  struct symbol *sp= &symtab[loc];
 // printf("in getloc with loc= %d and name = %s\n",loc,sp->name);
  while(++count<NHASH && loc<=NHASH && strcmp(sp->name,sym) )
  {
   //printf("loc= %d\n",loc);
   loc=(loc+1) %NHASH;
   sp=&symtab[loc];
  }
 if(count>NHASH)
   {
    printf("undefined symbol %s\n",sym);
    return -1;
   }
  else
   return loc;
 }


void addref(int lineno, char *word, int flags,int isConst)
{
struct info *i;
struct symbol *sp = lookup(word);

/* don't do dups of same line and file */
if(flags==0) return;
if(sp->infolist!=NULL ) {
 if(isConst==0)
	{printf("identifier at line number %d already declared in line number %d\n",yylineno,sp->infolist->lineno); return;}
 else
     return;
}

i = malloc(sizeof(struct info));
if(!i) {fputs("out of space\n", stderr); abort(); }

i->type=1;
i->offset=offset;
i->lineno = lineno;
sp->infolist = i;
symcount++;
offset+=4;
}

/* print the references
* sort the table alphabetically
* then flip each entry's reflist to get it into forward order
* and print it out
*/
/* aux function for sorting */
static int symcompare(const void *xa, const void *xb)
{
const struct symbol *a = xa;
const struct symbol *b = xb;
if(!a->name) {
if(!b->name) return 0;
return 1;
}
if(!b->name) return -1;
return strcmp(a->name, b->name);
}

void printrefs() {
struct symbol *sp;

//printf("location of 2: %d\n",getloc("2"));
qsort(symtab, NHASH, sizeof(struct symbol), symcompare); /* sort the symbol table */
for(sp = symtab; sp < symtab+ symcount && sp->name ; sp++) {


/* now print the word and its references */
printf("name : %10s\t", sp->name);

printf("line number: %d\t", sp->infolist->lineno);
//printf("location in symbol table: %d\t",getloc(sp->name));

printf("type %d\t", sp->infolist->type);
printf("offset %d\n", sp->infolist->offset);


}


}


int main(argc, argv)
int argc;
char **argv;
{
int i;
if(argc < 2) {
fprintf(stderr, "need filename\n");
return 1;
}
for(i = 1; i < argc; i++) {
if(newfile(argv[i]))
yylex();
}
printrefs();
return 0;
}
	









