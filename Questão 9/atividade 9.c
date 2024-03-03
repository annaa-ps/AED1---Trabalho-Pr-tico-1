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

int desenfileirar(Fila *fila) {
    int item = fila->items[fila->frente++];
    fila->tamanho--;
    return item;
}

int filaVazia(Fila *fila) {
    return fila->tamanho == 0;
}

void transferirPilhaParaFila(Pilha *pilha, Fila *fila) {
    while (!pilhaVazia(pilha)) {
        int item = desempilhar(pilha);
        enfileirar(fila, item);
    }
}

int main() {
    Pilha pilhaInicial;
    inicializarPilha(&pilhaInicial, 5);
    empilhar(&pilhaInicial, 1);
    empilhar(&pilhaInicial, 2);
    empilhar(&pilhaInicial, 4);
    empilhar(&pilhaInicial, 8);
    empilhar(&pilhaInicial, 9);

    Fila filaDesejada;
    inicializarFila(&filaDesejada, 5);

    printf("Pilha inicial: ");
    for (int i = pilhaInicial.top; i >= 0; i--) {
        printf("%d ", pilhaInicial.items[i]);
    }
    printf("\n");

    transferirPilhaParaFila(&pilhaInicial, &filaDesejada);

    printf("Fila desejada: ");
    while (!filaVazia(&filaDesejada)) {
        printf("%d ", desenfileirar(&filaDesejada));
    }
    printf("\n");

    return 0;
}
