
//declare is a nonterminal with one attribute calld attr which gives the type of variable
struct declare
{
int attr;
};


struct identifier {
char *name;
int place;
int type;


};

//place is the symbol table entry
//type is type of identifier
