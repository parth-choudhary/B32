struct quad {
int op;
int arg1;
int arg2;
int target;
};


#define QSIZE 1000
struct quad quadarray[QSIZE];
int qcount=0;

//gen adds a tuple to the quad array
//op is the operation code
//arg1,arg2,arg3 are symbol table entries
void gen(int op,int arg1,int arg2,int target)
{
  quadarray[qcount].op=op;
quadarray[qcount].arg1=arg1;
quadarray[qcount].arg2=arg2;
quadarray[qcount].target=target;
qcount++;
  
}

void newlinegen()
{
quadarray[qcount].op='%';
quadarray[qcount].arg1=-1;
quadarray[qcount].arg2=-1;
quadarray[qcount].target=-1;
qcount++;
}
void printarr()
{
 int i;
 printf("qcount=%d\n",qcount);
  for(i=0;i<qcount;i++)
  printf("op code:%d\targ1: %d\targ2: %d\ttarget: %d\n",quadarray[i].op,quadarray[i].arg1,quadarray[i].arg2,quadarray[i].target);


}
