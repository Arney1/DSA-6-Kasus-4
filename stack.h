#include "linked.h"
#include <stdbool.h>

// typedef bool infotype;
typedef address Stack;
bool isEmpty(address p);
void Tampil_List(address p);
void popAllAndPrint(Stack *q);
void createStack(address *p);
void Create_Node(address *p);
void Isi_Node(address *p, infotype nilai);
void Push(address *p, address pNew);
void Pop(address *p, infotype *X);
