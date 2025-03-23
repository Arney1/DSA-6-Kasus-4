#include "linked.h"
#include <stdio.h>
#include <stdlib.h>

bool isEmpty(address p) {
  // if (p == NULL) {
  //   return true;
  // }
  // return false;
  return (p == NULL);
}

void createList(address *p) {
    *p = NULL;
}

void Create_Node(address *p) {
  *p = (address)malloc(sizeof(ElmtList));
  // if (*p == NULL) {
  //     *p = NULL;
  // }
}

void Isi_Node(address *p, infotype nilai) {
  if (*p != NULL) {
    (**p).info = nilai;
    (**p).next = NULL;
  }
}

void Tampil_List(address p) {
  // while (!isEmpty(p)) {
  //   printf("%d -> ", p->info);
  //   p = p->next;
  // }
  // printf("NULL\n");
  if (isEmpty(p)) {
      printf("NULL\n");
  } else {
      printf("%d -> ", (*p).info);
      Tampil_List((*p).next);
  }
}

void Ins_Awal(address *p, address PNew) {
  (*PNew).next = *p;
  *p = PNew;
}

void Ins_Akhir(address *p, address PNew) {
  if (isEmpty(*p)) {
    *p = PNew;
  } else {
    address temp = *p;
    while (!isEmpty((*temp).next)) {
      temp = (*temp).next;
    }
    (*temp).next = PNew;
  }
}

address Search(address p, infotype nilai) {
  while (!isEmpty(p)) {
    if ((*p).info == nilai) {
      return p;
    }
    p = (*p).next;
  }
  return NULL;
}

void InsertAfter(address *pBef, address PNew) {
  (*PNew).next = (**pBef).next;
  (**pBef).next = PNew;
}

void Del_Awal(address *p, infotype *X) {
  if (!isEmpty(*p)) {
    *X = (**p).info;
    address temp = *p;
    *p = (**p).next;
    (*temp).next = NULL;
    free(temp);
    // DeAlokasi(&temp);
  }
}

void Del_Akhir(address *p, infotype *X) {
  if (!isEmpty(*p)) {
    if (isEmpty((**p).next)) {
      printf("yellow!");
      *X = (**p).info;
      free(*p);
      *p = NULL;
    } else {
      address prev;
      address last = *p;
      while (!isEmpty((*last).next)) {
        prev = last;
        last = (*last).next;
      }
      *X = (*last).info;
      free(last);
      (*prev).next = NULL;
    }
  }
}

void Del_After(address *pBef, infotype *X) {
  address temp = (**pBef).next;
  // *X = (**pBef).info;
  (**pBef).next = (*temp).next;
  *X = (*temp).info;
  (*temp).next = NULL;
  free(temp);
}

void DeAlokasi(address *p) {
  while (!isEmpty(*p)) {
    infotype i;
    Del_Awal(p, &i);
  }
}

int NbElmt(address p) {
  // int sum = 0;
  // while (!isEmpty(p)) {
  //     sum += 1;
  //     p = (*p).next;
  // }
  // return sum;
  if (isEmpty(p)) {
    return 0;
  } else {
    return 1 + NbElmt((*p).next);
  }
}

infotype Min(address p) {
  int Min = (*p).info;
  p = (*p).next;
  while (!isEmpty(p)) {
    if ((*p).info < Min) {
      Min = (*p).info;
    }
    p = (*p).next;
  }
  return Min;
}

infotype Rerata(address p) {
  int sum = 0, count = 0;
  while (!isEmpty(p)) {
    sum += (*p).info;
    count++;
    p = (*p).next;
  }
  return (count != 0) ? sum / count : 0;
}

address BalikList(address p) {
  if (!isEmpty(p)) {
    address prev = NULL;
    address this = p;
    address next = (*p).next;
    while (!isEmpty(next)) {
      (*this).next = prev;
      prev = this;
      this = next;
      next = (*this).next;
    }
    (*this).next = prev;
    p = this;
  }
  return p;
}
