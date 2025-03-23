#include "queue.h"
#include "linked.h"

// void Create_Node(address *p) {
//     Create_Node(p);
// }
void createQueue(address *p) {
    createList(p);
}

// void popAllAndPrint(Stack *q) {
//   while (!isEmpty(*q)) {
//     infotype X;
//     Dequeue(q, &X);
//     printf("%d", X);
//   }
//   printf("\n");
// }

void Enqueue(address *p, address pNew) {
    Ins_Akhir(p, pNew);
}

void Dequeue(address *p, infotype *X) {
    Del_Awal(p, X);
}
