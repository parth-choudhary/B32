#include "ILQuad.h"
#include "symboltable.h"

int stackPointer=1000;
int dataPointer=500;
void itob(int n,char s[],int b);

void codegen()
{
 int i;
 char add1[6],add2[6],add3[6],temp[20];
 FILE *f=fopen("/home/snigdha/B32Machine/ICode.asm","w");
 //printf("codegen\n");
 fputs("START:\n",f); 
//fprintf(f,"START:\n");
 for(i=0;i<qcount;i++)
  {
   int op=quadarray[i].op;
   switch(op)
	{
	  case '%':
  	     fputs("\tWAIT\n",f);
   	     break;
	  case '=':
 	     itob((getoffset(quadarray[i].arg1)+stackPointer),add1,10);
 	     fputs("\tLDA ",f);
	     fputs(add1,f);
	     fputs("\n",f);
	     itob((getoffset(quadarray[i].target)+stackPointer),add2,10);
 	     fputs("\tLDX #",f);
	     fputs(add2,f);
	     fputs("\n",f);
	     fputs("\tSTA , X\n",f);
	     break;
	  case '+':
	     itob((getoffset(quadarray[i].arg1)+stackPointer),add1,10);
 	     fputs("\tLDA ",f);
	     fputs(add1,f);
	     fputs("\n",f);
	     itob((getoffset(quadarray[i].arg2)+stackPointer),add2,10);
 	     fputs("\tLDX ",f);
	     fputs(add2,f);
	     fputs("\n",f);
	     fputs("\tADD A,X\n",f);
	     itob((getoffset(quadarray[i].target)+stackPointer),add3,10);
 	     fputs("\tLDX #",f);
	     fputs(add3,f);
	     fputs("\n",f);
	     fputs("\tSTA , X\n",f);
	     
	     
	     break;
	}
   }
 fputs("\tEND START\n",f);
 fclose(f);
 return;

}

void allocate()
{
 stackPointer=0;
 return;
}




