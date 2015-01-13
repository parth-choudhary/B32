#include<stdio.h>


void foo()
{
printf("in foo\n");
}
int main()
{
  FILE *fp,*fp2;
 char c;
  foo();
  fp=fopen("test.c","a+");
  fp2=fopen("error.txt","a+");
  if(!fp)
  {   printf("no input\n");}
  else{
   printf("file opened for input\n");}
  if(!fp2)
   {printf("no output\n");}
  else{
   printf("file opened for output\n");}
  while(!feof(fp))
  {
   c=getc(fp);
   putc(c,fp2);
  }
/*putc('\0',fp2);*/
 printf("hello world");
//fclose(fp);
//fclose(fp2);
return 0;
}
