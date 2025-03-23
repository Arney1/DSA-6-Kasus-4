// #include "linked.h"
#include "convention.h"
#include "linked.h"
#include "queue.h"
#include "stack.h"
#include <stdio.h>
#include <string.h>

#define MAX_TEXT 100

void addText(Queue *history, LList *textList, Stack *undo, char *text) {
  address newNode;
  Create_Node(&newNode);
  Isi_Node_Str(&newNode, !isEmpty(*textList) ? (*textList)->info.strValue : "");
  Push(undo, newNode);

  Create_Node(&newNode);
  Isi_Node_Str(&newNode, text);
  Enqueue(history, newNode);

  Create_Node(&newNode);
  Isi_Node_Str(&newNode, text);
  Ins_Awal(textList, newNode);
}

void deleteText(LList *textList, Stack *undo) {
  if (isEmpty(*textList)) {
    return;
  }
  address newNode;
  Create_Node(&newNode);
  Isi_Node_Str(&newNode, (*textList)->info.strValue);
  Push(undo, newNode);

  infotype X;
  Del_Awal(textList, &X);
}

void undo(LList *textList, Stack *undo, Stack *redo, Queue *history) {
  if (isEmpty(*undo)) {
    return;
  }
  address newNode;
  Create_Node(&newNode);
  Isi_Node_Str(&newNode, !isEmpty(*textList) ? (*textList)->info.strValue : "");
  Push(redo, newNode);

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

void redo(LList *textList, Stack *undo, Stack *redo, Queue *history) {
  if (isEmpty(*redo)) {
    return;
  }
  address newNode;
  Create_Node(&newNode);
  Isi_Node_Str(&newNode, !isEmpty(*textList) ? (*textList)->info.strValue : "");
  Push(undo, newNode);

  infotype nextState;
  Pop(redo, &nextState);
  if (strlen(nextState.strValue) > 0) {
    address tempNode;
    Create_Node(&tempNode);
    Isi_Node_Str(&tempNode, nextState.strValue);
    Ins_Awal(textList, tempNode);
  }
}

void rollback(LList *textList, Queue *history) {
  if (isEmpty(*history)) {
    printf("Tidak ada history untuk rollback.\n");
    return;
  }
  infotype oldState;
  Dequeue(history, &oldState);
  if (strlen(oldState.strValue) > 0) {
    address tempNode;
    Create_Node(&tempNode);
    Isi_Node_Str(&tempNode, oldState.strValue);
    Ins_Awal(textList, tempNode);
    printf("Rollback berhasil ke: %s\n", oldState.strValue);
  }
}

void displayText(LList textList) {
  if (isEmpty(textList)) {
    printf("Teks kosong.\n");
    return;
  }
  printf("Teks saat ini: %s\n", textList->info.strValue);
}

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
    printf("6. Rollback\n");
    printf("7. Keluar\n");
    printf("Pilih: ");
    scanf("%d", &choice);
    getchar();

    switch (choice) {
    case 1:
      printf("Masukkan teks: ");
      fgets(input, MAX_TEXT, stdin);
      input[strcspn(input, "\n")] = 0;
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
      rollback(&text, &history);
      break;
    case 7:
      printf("Keluar dari editor.\n");
      break;
    default:
      printf("Pilihan tidak valid.\n");
    }
  } while (choice != 7);
}

int main() {
  menu();
  return 0;
}
