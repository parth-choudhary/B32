


struct symbol {
struct info *infolist;
char *name;
};

struct info {
int lineno;
int offset;
int type;
};

//increment the count
int symcount=0;
int varoffset=0;
int constoffset=0;
int tempcount=0;
extern int lineno;
extern int Symboloffset[30];
extern char Symbolname[30][30];


/* a variable name */
/* 01 - definition */
/* simple symtab of fixed size */
#define NHASH 131
struct symbol symtab[NHASH];
struct symbol *lookup(char*);
void addref(int, char*, int,int);
int getloc(char *);

int newtemp();
void itob(int n,char s[],int b);
void reverse(char s[]);
char * curfilename;

int defining;
/* names are probably definitions */
/* hash a symbol */
static unsigned symhash(char *sym)
{
unsigned int hash = 0;
unsigned c;
while(c = *sym++) hash = hash*9 ^ c;

return hash;
}


int getloc(char *sym)
{
  
  int loc= symhash(sym)%NHASH,count=0;
  struct symbol *sp= &symtab[loc];
  //printf("in getloc with loc= %d and name = %s\n",loc,sp->name);
  while(strcmp(sp->name,sym) && ++count<NHASH && loc<=NHASH )
  {
   //printf("loc= %d\n",loc);
   loc=(loc+1) %NHASH;
   sp=&symtab[loc];
  }
 if(count>=NHASH)
   {
    fputs("undefined symbol usage\n", stderr);
   abort(); /* tried them all, table is full */
   }
  else
   return loc;
 }

int getoffset(int loc)
{
 //printf("getoffset\n");
 struct symbol *sp = &symtab[loc];
 return sp->infolist->offset;
}


struct symbol * lookup(char* sym)
{

struct symbol *sp = &symtab[symhash(sym)%NHASH];
int scount = NHASH;
/* how many have we looked at */

while(--scount >= 0) {
if(sp->name && !strcmp(sp->name, sym)) return sp;
if(!sp->name) {
sp->name = strdup(sym);
sp->infolist = 0;

return sp;
}
/* new entry */
if(++sp >= symtab+NHASH) sp = symtab; /* try the next entry */
}
fputs("symbol table overflow\n", stderr);
abort(); /* tried them all, table is full */
}

int newtemp()
{
  int i=0;
  char name[20]="__temp";
  char number[5];
  itob(tempcount++,number,10);
  strcat(name,number);
  //printf("temporary name:%s\n",name);
  addref(lineno,name,1,0);
 return getloc(name);
}



void addref(int lineno, char *word, int flags,int isConst)
{
struct info *i;
struct symbol *sp = lookup(word);

/* don't do dups of same line and file */
if(flags==0) return;
if(sp->infolist!=NULL ) {
 if(isConst==0)
	{printf("identifier at line number %d already declared in line number %d\n",0,sp->infolist->lineno); return;}
 else
     return;
}

i = malloc(sizeof(struct info));
if(!i) {fputs("out of space\n", stderr); abort(); }

i->type=1;
if(isConst==0)
  i->offset=varoffset;
else
  i->offset=varoffset;

i->lineno = lineno;
sp->infolist = i;
symcount++;
if(isConst==0)
  varoffset+=2;
else
  varoffset+=2;


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
FILE *f=fopen("/home/snigdha/B32Machine/symbols.txt","w");
 char add1[6];
struct symbol *sp;
int count=0;
qsort(symtab, NHASH, sizeof(struct symbol), symcompare); /* sort the symbol table */


for(sp = symtab; sp < symtab+ symcount && sp->name ; sp++) {

/* now print the word and its references */
fputs(sp->name,f);
fputs("\n",f);
itob(sp->infolist->offset,add1,10);
fputs(add1,f);
count++;
fputs("\n",f);

}

//free(sp);
return;
}


void itob(int n,char s[],int b)
{
int i,sign=n,num=0;
long int l=0;

l=(long)n;
if(n!=INT_MIN)
{
 if((sign)<0)
    l=-n;
}
else
{
  sign=-1;
  l=-(long)n;
}

i=0;
do
  {
    
    num=l%b;
    //printf("num= %d\tl= %ld\n",num,l);
    if(num>9)
     s[i++]=(num-10)+'A';
    else
     s[i++]=num+'0';

  }while((l/=b)>0);

if(sign<0)
   s[i++]='-';
s[i]='\0';

reverse(s);
return;
}



void reverse(char s[])
{

int c,i,j;


for(i=0,j=strlen(s)-1;i<j;i++,j--)
{
c=s[i];
s[i]=s[j];
s[j]=c;
}


return;
}

