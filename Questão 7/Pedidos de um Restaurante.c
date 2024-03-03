#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct dos pedidos.
typedef struct {
    int nPedido;
    char itemPedido[50]; // Aumentando o tamanho para acomodar descrições mais longas
    int mesa;
    char status[20];
} Pedidos;

// Struct da pilha.
typedef struct {
    Pedidos *pedidos;
    int topo;
    int fundo;
    int tam;
    int maxtam;
} Pilha;

// Função para checar se a pilha está vazia.
int pilhaVazia(Pilha *p) {
    if (p == NULL) return -1;
    if (p->tam == 0) return 0;
    else return 1;
}

// Função para checar se a pilha está cheia.
int pilhaCheia(Pilha *p) {
    if (p->tam == p->maxtam) return 0;
    else return 1;
}

// Função para criar a pilha com a struct usada no programa.
int criarPilha(Pilha *p, int maxtam) {
    if (maxtam == 0) return -6;
    p->maxtam = maxtam; // Definindo tamanho máximo da pilha
    p->pedidos = (Pedidos*)malloc(maxtam * sizeof(Pedidos));
    if (p->pedidos == NULL) return -1;
    p->topo = 0; // Colocando início da pilha
    p->fundo = 0; // Determinando que a pilha está vazia
    p->tam = 0; // Definindo o tamanho inicial da pilha
    return 0;
}

// Função para atualizar o status do pedido na pilha.
void atualizarStatus(Pilha *p, int nPedido, char *s) {
    for (int i = p->topo - 1; i >= 0; i--) {
        if (p->pedidos[i].nPedido == nPedido) {
            strcpy(p->pedidos[i].status, s);
            break;
        }
    }
}

// Função para adicionar um pedido à pilha de pedidos.
int adicionarPedido(Pilha *p, Pedidos pedido) {
    if (p == NULL) return -1;
    if (pilhaCheia(p) == 0) return -2;

    p->pedidos[p->topo] = pedido;
    p->topo++;
    p->tam++;
    return 0;
}

// Função para remover os pedidos da pilha.
int removerPedido(Pilha *p, Pedidos *pedido) {
    if (p == NULL) return -1;
    if (pilhaVazia(p) == 0) return -2;

    *pedido = p->pedidos[p->topo - 1];
    p->topo--;
    p->tam--;
    return 0;
}

// Função para atender um pedido na pilha.
int atender(Pilha *p, Pilha *pAtendidos) {
    if ((p == NULL) || (pAtendidos == NULL)) return -1;
    if (pilhaVazia(p) == 0) return -2;

    Pedidos paux;
    removerPedido(p, &paux);
    printf("\n------------------------------------------------\n");
    printf("O pedido de numero %d foi atendido.\n", paux.nPedido);
    printf("------------------------------------------------\n");
    strcpy(paux.status, "servido");
    adicionarPedido(pAtendidos, paux);
    return 0;
}

// Função para listar os pedidos que ainda precisam ser atendidos.
void listarPedidosAguardando(Pilha *p) {
    if (p == NULL) return;
    if (pilhaVazia(p) == 0) return;

    printf("\nPedidos aguardando atendimento:\n");
    printf("------------------------------------------------\n");
    for (int i = p->topo - 1; i >= 0; i--) {
        printf("Numero do pedido: %d\n", p->pedidos[i].nPedido);
        printf("Item solicitado: %s\n", p->pedidos[i].itemPedido);
        printf("Mesa do cliente: %d\n", p->pedidos[i].mesa);
        printf("Status do pedido: %s\n", p->pedidos[i].status);
        printf("------------------------------------------------\n");
    }
}

// Função para listar os pedidos servidos ao cliente.
void listarPedidosServidos(Pilha *p) {
    if (p == NULL) return;
    if (pilhaVazia(p) == 0) return;

    printf("\nPedidos servidos ao cliente:\n");
    for (int i = p->topo - 1; i >= 0; i--) {
        printf("------------------------------------------------\n");
        printf("Numero do pedido: %d\n", p->pedidos[i].nPedido);
        printf("Item solicitado: %s\n", p->pedidos[i].itemPedido);
        printf("Mesa do cliente: %d\n", p->pedidos[i].mesa);
        printf("Status do pedido: %s\n", p->pedidos[i].status);
        printf("------------------------------------------------\n");
    }
}

int main() {
    Pilha pilhaPedidos, pilhaAtendidos;
    criarPilha(&pilhaPedidos, 20);
    criarPilha(&pilhaAtendidos, 20);

    int opcao;
    Pedidos novoPedido;
    int numPedido; // Declarando numPedido aqui
    char novoStatus[20]; // Movendo a declaração para o início da função

    do {
        printf("\nMenu de Opcoes:\n");
        printf("------------------------------------------------\n");
        printf("1. Registrar um novo pedido\n");
        printf("2. Atualizar o status de um pedido\n");
        printf("3. Servir o pedido\n");
        printf("4. Exibir os pedidos aguardando atendimento\n");
        printf("5. Exibir os pedidos servidos ao cliente\n");
        printf("0. Sair\n");
        printf("------------------------------------------------\n");
        printf("Escolha uma opcao:\n");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("\nNumero do pedido: ");
                scanf("%d", &novoPedido.nPedido);
                printf("Item solicitado: ");
                scanf("%s", novoPedido.itemPedido);
                printf("Mesa do cliente: ");
                scanf("%d", &novoPedido.mesa);
                strcpy(novoPedido.status, "preparando");
                adicionarPedido(&pilhaPedidos, novoPedido);
                break;
            case 2:
                printf("\nNumero do pedido a ser atualizado:\n");
                scanf("%d", &numPedido); // Corrigindo a leitura de numPedido
                printf("Novo status:\n");
                scanf("%s", novoStatus);
                atualizarStatus(&pilhaPedidos, numPedido, novoStatus);
                printf("----------------------------------------\n");
                printf("\nStatus do pedido atualizado com sucesso!\n");
                printf("----------------------------------------\n");
                break;
            case 3:
                atender(&pilhaPedidos, &pilhaAtendidos);
                break;
            case 4:
                listarPedidosAguardando(&pilhaPedidos);
                break;
            case 5:
                listarPedidosServidos(&pilhaAtendidos);
                break;
            case 0:
                printf("\nSaindo...\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}
