#include "linked.h"
#include <stdbool.h>

// typedef bool infotype;
typedef address Queue;
bool isEmpty(address p);
void Tampil_List(address p);
// void popAllAndPrint(Stack *q);
void createQueue(address *p);
void Create_Node(address *p);
void Isi_Node(address *p, infotype nilai);
void Enqueue(address *p, address pNew);
void Dequeue(address *p, infotype *X);
