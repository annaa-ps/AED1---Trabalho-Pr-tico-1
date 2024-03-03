//Anna Karolyna Pereira Santos - 12221BCC046 | Fernanda Ferreira de Melo - 12211BCC043 | Giovana M. Ferreira - 12221BCC033 | Gustavo Henrique - 12311BCC021

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *items;
    int top;
} Pilha;

typedef struct {
    int *items;
    int frente;
    int fundo;
    int tamanho;
} Fila;

void inicializarPilha(Pilha *pilha, int tamanho) {
    pilha->items = (int *)malloc(tamanho * sizeof(int));
    pilha->top = -1;
}

void empilhar(Pilha *pilha, int item) {
    pilha->items[++pilha->top] = item;
}

int desempilhar(Pilha *pilha) {
    return pilha->items[pilha->top--];
}

int pilhaVazia(Pilha *pilha) {
    return pilha->top == -1;
}

void inicializarFila(Fila *fila, int tamanho) {
    fila->items = (int *)malloc(tamanho * sizeof(int));
    fila->frente = 0;
    fila->fundo = -1;
    fila->tamanho = 0;
}

void enfileirar(Fila *fila, int item) {
    fila->items[++fila->fundo] = item;
    fila->tamanho++;
}


void transferirPilhaParaFila(Pilha *pilha, Fila *fila) {
    while (!pilhaVazia(pilha)) {
        int item = desempilhar(pilha);
        enfileirar(fila, item);
    }
}

void printPilha(Pilha *pilha) {
    printf("\n inicio ");
    for (int i = pilha->top; i >= 0; i--) {
        printf("| %d ", pilha->items[i]);
    }
    printf("| fim\n");
}

void printFila(Fila *fila) {
    printf("\n inicio ");
    for (int i = fila->frente; i <= fila->fundo; i++) {
        printf("| %d ", fila->items[i]);
    }
    printf("| fim\n");
}

int main() {
    Pilha pilha;
    Fila fila;
    int tamanho;

    printf("\nTamanho da pilha que enfileraremos:\n->");
    scanf("%d", &tamanho);

    inicializarPilha(&pilha, tamanho);
    inicializarFila(&fila, tamanho);

    printf("\n\tInsira os elementos na pilha:\n");
    for (int i = 0; i < tamanho; i++) {
        int elemento;
        printf("Elemento %d:\n->", i + 1);
        scanf("%d", &elemento);
        empilhar(&pilha, elemento);
    }

    printf("\n--- Pilha Inicial ---");
    printPilha(&pilha);

    printf("\n... Transferindo Elementos... \n");

    printf("\n--- Fila Final ---");
    transferirPilhaParaFila(&pilha, &fila);
    printFila(&fila);

    free(pilha.items);
    free(fila.items);

    return 0;
}
