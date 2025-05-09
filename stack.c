#include "stack.h"
#include "linked.h"

// void Create_Node(address *p) {
//     Create_Node(p);
// }
void createStack(address *p) { createList(p); }

void popAllAndPrint(Stack *q) {
  while (!isEmpty(*q)) {
    infotype X;
    Pop(q, &X);
    if ((**q).type == INTEGER) {

      printf("%d", X.intValue);
    } else {
      printf("%s", X.strValue);
    }
  }
  printf("\n");
}

void Push(address *p, address pNew) { Ins_Awal(p, pNew); }

void Pop(address *p, infotype *X) { Del_Awal(p, X); }
