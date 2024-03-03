//Anna Karolyna Pereira Santos - 12221BCC046 | Fernanda Ferreira de Melo - 12211BCC043 | Giovana M. Ferreira - 12221BCC033 | Gustavo Henrique - 12311BCC021

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20

// Struct dos pedidos.
typedef struct{
    int nPedido;
    char itemPedido[50];
    int mesa;
    char status[MAX];
} Pedidos;

// Struct da pilha.
typedef struct{
    Pedidos *pedidos;
    int topo;
    int fundo;
    int tam;
    int maxtam;
} Pilha;

// Checa se a pilha está vazia.
int pilhaVazia (Pilha *p){
    if (p == NULL) return -1;
    if (p->tam == 0) return 0;
    else return 1;
}

// Checa se a pilha está cheia.
int pilhaCheia(Pilha *p) {
    if (p->tam == p->maxtam) return 0;
    else return 1;
}

// Cria a pilha com a struct usada no programa.
int criarPilha (Pilha *p, int maxtam){
    if (maxtam == 0) return -6;
    p->maxtam = maxtam; // Definindo tamanho maximo da pilha
    p->pedidos = (Pedidos*)malloc(maxtam * sizeof(Pedidos));
    if (p->pedidos == NULL) return -1;
    p->topo = 0; // Colocando inicio da pilha
    p->fundo = 0; // Determinando que a pilha está vazia
    p->tam = 0; // Definindo o tamanho inicial da pilha
    return 0;
}

// Atualiza o status da pedido na pilha usando funcoes da string.h para comparar e trocar as strings.
int atualizarStatus(Pilha *p, char *s) {
    if (p == NULL) return -1;
    if (pilhaVazia(p) == 0) return -2;

    strcpy(p->pedidos[p->topo - 1].status, s);
    return 0;
}


// Funcao que adiciona um pedido a pilha de pedidos.
// Se for a criacao de um pedido para ser preparado, ponha finalidade = 0
int adicionarPedido(Pilha *p, Pedidos pedido, int finalidade){
    if (p == NULL) return -1;
    if (pilhaCheia(p) == 0) return -2;

    p->pedidos[p->topo] = pedido;

    if (finalidade == 0)
        atualizarStatus(p, "preparando");

    p->topo++;
    p->tam++;
    return 0;
}

// Funcao que apenas remove os pedidos da pilha, salva em uma variavel do tipo Pedidos para uso em outras funcoes.
int removerPedido (Pilha *p, Pedidos *pedido){
    if (p == NULL) return -1;
    if (pilhaVazia(p) == 0) return -2;

    *pedido = p->pedidos[p->topo - 1];
    atualizarStatus(p, "pronto para servir");
    p->topo--;
    p->tam--;
    return 0;
}

// Atende um pedido na pilha, isso o remove da pilha atualiza o seu status e o insere na pilha de pedidos atendidos.
int atender(Pilha *p, Pilha *pAtendidos) {
    if ((p == NULL) || (pAtendidos == NULL)) return -1;

    Pedidos paux;

    int resultadoRemocao = removerPedido(p, &paux);
    if (resultadoRemocao != 0) {
        printf("Erro ao atender pedido: %d\n", resultadoRemocao);
        return resultadoRemocao;
    }

    printf("\nO pedido de numero %d foi atendido.\n", paux.nPedido);
    adicionarPedido(pAtendidos, paux, 1);
    atualizarStatus(pAtendidos, "servido");
    return 0;
}

// Pedidos que ainda estão na pilha original, não infringe regras de pilha utilizando uma pilha auxiliar passando da original para ela
// e depois de volta para a original.
int ahAtender (Pilha *p, Pilha *aux){
    if ((p == NULL) || (aux == NULL)) return -1;
    if (pilhaVazia(p) == 0) return -2;

    Pedidos paux;
    while (pilhaVazia(p) != 0) {
        removerPedido(p, &paux);
        printf("\nO pedido de numero %d, que eh um %s, ainda precisa ser atendido e esta %s.\n", paux.nPedido, paux.itemPedido, paux.status);
        adicionarPedido(aux, paux,1);
    }
    while (pilhaVazia(aux) != 0) {
        removerPedido(aux, &paux);
        adicionarPedido(p, paux, 1);
    }
    return 0;
}

// Mostra todos os itens da pilha de atendidos, não infringe regras de pilha utilizando uma pilha auxiliar passando da original para ela
// e depois de volta para a original.
int atendidos (Pilha *pAtendidos, Pilha *aux){
    if ((pAtendidos == NULL) || (aux == NULL)) return -1;
    if (pilhaVazia(pAtendidos) == 0) return -2;

    Pedidos paux;
    while (pilhaVazia(pAtendidos) != 0){
        removerPedido(pAtendidos, &paux);
        printf("\nO pedido de numero %d, que eh um %s, ja foi %s.\n", paux.nPedido, paux.itemPedido, paux.status);
        adicionarPedido(aux, paux, 1);
    }
    while (pilhaVazia(aux) != 0){
        removerPedido(aux, &paux);
        adicionarPedido(pAtendidos, paux, 1);
    }
    return 0;
}

int main() {
    // Estruturas de dados:
    Pilha pPedidos, pAtendidos, aux;
    Pedidos pedido;

    // Variaveis de apoio:
    int opcao, maxPedidos = (MAX/2), numPedido = 1;

    printf("[ O maximo de pedido é de %d! ]\n", maxPedidos);

    // Garantir a criacao das pilhas:
    if (criarPilha(&pPedidos, maxPedidos) != 0 || criarPilha(&pAtendidos, maxPedidos) != 0 || criarPilha(&aux, maxPedidos) != 0) {
        printf("Erro ao criar as pilhas.\n");
        return -1;
    }

    do {
        printf("\nMENU:\n");
        printf("1- Adicionar Pedido;\n");
        printf("2- Atender Pedido;\n");
        printf("3- Mostrar Pedidos Pendentes;\n");
        printf("4- Mostrar Pedidos Atendidos;\n");
        printf("0- Sair;\n");
        printf("Informe a opcao desejada:\n");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Informe o item do pedido: ");
                fflush(stdin);
                scanf("%50[^\n]", pedido.itemPedido);
                pedido.nPedido = numPedido++;
                pedido.mesa = 1; // Apenas como exemplo, pode ser solicitado do usuário
                strcpy(pedido.status, "aguardando");
                if (adicionarPedido(&pPedidos, pedido,0) != 0) {
                    printf("Erro ao adicionar pedido.\n");
                }
                break;
            case 2:
                if (atender(&pPedidos, &pAtendidos) != 0) {
                    printf("Erro ao atender pedido.\n");
                }
                break;
            case 3:
                if (ahAtender(&pPedidos, &aux) != 0) {
                    printf("Aparentemente não há pendentes :D \n");
                }
                break;
            case 4:
                if (atendidos(&pAtendidos, &aux) != 0) {
                    printf("Parece que nenhum pedido foi atendido ainda!\n");
                }
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}
