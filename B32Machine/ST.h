
struct info {
int lineno;
int offset;
int type;
};

struct symbol
{
  char* name;
  struct info *infolist;
  struct symbol *next;
};


struct *symtab= (struct symbol *)0;
 struct symbol *identifier;
int offset=0;

struct symbol * putsym (char *sym_name)
{
struct symbol *ptr;
ptr = (symbol *) malloc (sizeof(struct symbol));
ptr->name = (char *) malloc (strlen(sym_name)+1);
strcpy (ptr->name,sym_name);
ptr->offset = offset;
ptr->next = (struct symbol *)symtab;
symtab = ptr;
offset+=4;
return ptr;
}


struct symbol * getsym (char *sym_name)
{
struct symbol *ptr;
for ( ptr = symtab;ptr != (struct symbol *) 0;ptr = (struct symbol *)ptr->next )
if (strcmp (ptr->name,sym_name) == 0)
return ptr;
return 0;
}






