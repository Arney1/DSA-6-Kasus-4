// #include "linked.h"
#include "convention.h"
#include "linked.h"
#include "queue.h"
#include "stack.h"
#include <stdio.h>
// #include <stdlib.h>
#include <string.h>

#define MAX_TEXT 100

// // Struktur untuk Linked List (Menyimpan teks utama)
// typedef struct Node {
//     char text[MAX_TEXT];
//     struct Node* next;
// } Node;

// // // Struktur untuk Stack (Undo & Redo)
// // typedef struct Stack {
// //     char text[MAX_TEXT];
// //     struct Stack* next;
// // } Stack;

// Node* textHead = NULL;  // Linked list utama
// Stack* undoStack = NULL; // Stack untuk Undo
// Stack* redoStack = NULL; // Stack untuk Redo

// Fungsi untuk push ke Stack
// void push(Stack stack, char* text) {
//     Stack newNode = (Stack)malloc(sizeof(Stack));
//     strcpy(newNode, text);
//     newNode->next = *stack;
//     *stack = newNode;
// }

// Fungsi untuk pop dari Stack
// char* pop(Stack** stack) {
//     if (*stack == NULL) return NULL;
//     Stack* temp = *stack;
//     char* text = strdup(temp->text);
//     *stack = (*stack)->next;
//     free(temp);
//     return text;
// }

// Fungsi untuk menambahkan teks ke Linked List
void addText(Queue *history, LList *textList, Stack *undo, char *text) {
  address newNode;
  Create_Node(&newNode);
  Isi_Node_Str(&newNode, !isEmpty(*textList) ? (*textList)->info.strValue : "");
  Push(undo, newNode);

  Create_Node(&newNode);
  Isi_Node_Str(&newNode, text);
  // Push(undo, newNode);
  Enqueue(history, newNode);

  // push(&undoStack, textHead ? textHead->text : ""); // Simpan ke undoStack
  // sebelum perubahan

  // Node* newNode = (Node*)malloc(sizeof(Node));
  Create_Node(&newNode);
  Isi_Node_Str(&newNode, text);
  Ins_Awal(textList, newNode);
}

// Fungsi untuk menghapus teks terbaru
void deleteText(LList *textList, Stack *undo) {
  if (isEmpty(*textList)) {
    return;
  }
  address newNode;
  Create_Node(&newNode);
  Isi_Node_Str(&newNode, (*textList)->info.strValue);
  Push(undo, newNode); // Simpan ke undoStack sebelum perubahan

  // address temp = textHead;
  // textHead = textHead->next;
  // free(temp);
  infotype X;
  Del_Awal(textList, &X);
}

// Fungsi untuk melakukan Undo
void undo(LList *textList, Stack *undo, Stack *redo, Queue *history) {
  if (isEmpty(*undo)) {
    return;
  }
  address newNode;
  Create_Node(&newNode);
  Isi_Node_Str(&newNode, !isEmpty(*textList) ? (*textList)->info.strValue : "");
  Push(redo, newNode); // Simpan state saat ini ke redoStack

  infotype lastState;
  Pop(undo, &lastState);
  if (strlen(lastState.strValue) > 0) {
    printf("[DEBUG] Undo to: %s\n", lastState.strValue);

    address newNode;
    Create_Node(&newNode);
    Isi_Node_Str(&newNode, lastState.strValue);

    Ins_Awal(textList, newNode);
  }
}

// Fungsi untuk melakukan Redo
void redo(LList *textList, Stack *undo, Stack *redo, Queue *history) {
  if (isEmpty(*redo)) {
    return;
  }
  address newNode;
  Create_Node(&newNode);
  Isi_Node_Str(&newNode, !isEmpty(*textList) ? (*textList)->info.strValue : "");
  Push(undo,
       newNode); // Simpan state saat ini ke undoStack

  infotype nextState;
  Pop(redo, &nextState);
  if (strlen(nextState.strValue) > 0) {
    addText(history, textList, undo, nextState.strValue);
  }
}

// Fungsi untuk menampilkan teks saat ini
void displayText(LList textList) {
  if (isEmpty(textList)) {
    printf("Teks kosong.\n");
    return;
  }
  printf("Teks saat ini: %s\n", textList->info.strValue);
}

// Menu utama
void menu() {
  int choice;
  char input[MAX_TEXT];
  Queue history;
  LList text;
  Stack undoStack, redoStack;
  createQueue(&history);
  createList(&text);
  createStack(&undoStack);
  createStack(&redoStack);

  do {
    printf("\n--- Editor Teks ---\n");
    printf("1. Tambah Teks\n");
    printf("2. Hapus Teks\n");
    printf("3. Undo\n");
    printf("4. Redo\n");
    printf("5. Tampilkan Teks\n");
    printf("6. Keluar\n");
    printf("Pilih: ");
    scanf("%d", &choice);
    getchar(); // Menghindari masalah newline

    switch (choice) {
    case 1:
      printf("Masukkan teks: ");
      fgets(input, MAX_TEXT, stdin);
      input[strcspn(input, "\n")] = 0; // Hapus newline
      addText(&history, &text, &undoStack, input);
      break;
    case 2:
      deleteText(&text, &undoStack);
      printf("Teks terakhir dihapus.\n");
      break;
    case 3:
      undo(&text, &undoStack, &redoStack, &history);
      printf("Undo berhasil.\n");
      break;
    case 4:
      redo(&text, &undoStack, &redoStack, &history);
      printf("Redo berhasil.\n");
      break;
    case 5:
      displayText(text);
      break;
    case 6:
      printf("Keluar dari editor.\n");
      break;
    default:
      printf("Pilihan tidak valid.\n");
    }
  } while (choice != 6);
}

int main() {
  menu();
  return 0;
}
