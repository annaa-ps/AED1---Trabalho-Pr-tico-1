//Anna Karolyna Pereira Santos - 12221BCC046 | Fernanda Ferreira de Melo - 12211BCC043 | Giovana M. Ferreira - 12221BCC033 | Gustavo Henrique - 12311BCC021

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura de dados para os carros
typedef struct {
    char placa[8];
    char modelo[11];
    int anoDeFabricacao;
} Carro;

// Definição da estrutura de dados para a fila de carros
typedef struct {
    Carro* carros; // Ponteiro para a array de carros
    int tam; // Tamanho atual da fila
    int maxtam; // Capacidade máxima da fila
    int fim; // Índice do último elemento na fila
    int inicio; // Índice do primeiro elemento na fila
} Fila;

// Função para verificar se a fila está vazia
int filaVazia(Fila* f) {
    if (f == NULL) return -1;
    if (f->tam == 0) return 0;
    else return 1;
}

// Função para verificar se a fila está cheia
int filaCheia(Fila* f) {
    if (f->tam == f->maxtam) return 0;
    else return 1;
}

// Função para criar uma fila com uma capacidade máxima especificada
int criaFila(Fila* f, int maxtam) {
    f->maxtam = maxtam;
    f->carros = (Carro*)malloc(maxtam * sizeof(Carro)); // Aloca memória para a array de carros
    if (f->carros == NULL) return -1; // Retorna -1 em caso de falha na alocação de memória
    f->tam = 0;
    f->inicio = 0;
    f->fim = -1;
    return 0; // Retorna 0 em caso de sucesso na criação da fila
}

// Função para adicionar um carro à fila
int adicionarNaFila(Fila* f, Carro carro) {
    if (f == NULL) return -1;
    if (filaCheia(f) == 0) return -2; // Retorna -2 se a fila estiver cheia

    f->fim = (f->fim + 1) % f->maxtam; // Incrementa o índice do último elemento circularmente
    f->carros[f->fim] = carro; // Adiciona o carro ao final da fila
    f->tam++; // Incrementa o tamanho da fila

    return 0; // Retorna 0 em caso de sucesso na adição do carro à fila
}

// Função para remover um carro da fila
int removerDaFila(Fila* f, Carro* carroAtendido) {
    if (f == NULL) return -1;
    if (filaVazia(f) == 0) return -3; // Retorna -3 se a fila estiver vazia

    *carroAtendido = f->carros[f->inicio]; // Carro no início da fila é removido
    f->inicio = (f->inicio + 1) % f->maxtam; // Incrementa o índice do primeiro elemento circularmente
    f->tam--; // Decrementa o tamanho da fila

    if (f->tam == 0) {
        f->inicio = -1; // Se a fila estiver vazia, define o índice do primeiro elemento como -1
    }

    return 0; // Retorna 0 em caso de sucesso na remoção do carro da fila
}

// Função para buscar um carro na fila pelo número da placa
int buscarPlaca(Fila* f, char* placa, Carro* carroEncontrado) {
    if (f == NULL) return -1;
    if (filaVazia(f) == 0) return -3; // Retorna -3 se a fila estiver vazia

    for (int i = 0; i < f->tam; i++) {
        if (strcmp(f->carros[(f->inicio + i) % f->maxtam].placa, placa) == 0) {
            *carroEncontrado = f->carros[(f->inicio + i) % f->maxtam]; // Encontrou o carro com a placa especificada
            return 1; // Retorna 1 para indicar que o carro foi encontrado na fila
        }
    }

    return -1; // Retorna -1 se o carro não for encontrado na fila
}

// Função para exibir todos os carros na fila
void mostrarFila(Fila* f) {
    if (f == NULL || filaVazia(f) == 0) {
        printf("Fila vazia.\n");
        return;
    }

    /*
     * Dada uma fila, ele usará uma iteração condicionda pelo tamanho da fila.
     * A ideia do int indice é dado por duas partes:
     * (f->inicio + i)  -> será nosso deslocamento pela fila, dado pelo inicio mais o deslocamento de i.
     * % f->maxtam      -> é a garantia de estarmos dentro do escopo da nossa fila
     */
    for (int i = 0; i < f->tam; i++) {
        int indice = (f->inicio + i) % f->maxtam;
        printf("Placa: %s, Modelo: %s, Ano: %d\n", f->carros[indice].placa, f->carros[indice].modelo, f->carros[indice].anoDeFabricacao);
    }
}

// Função para exibir o carro mais recentemente atendido
void exibirCarroAtendidoRecente(Carro* carro) {
    printf("\nCarro atendido recentemente:\n");
    printf("Placa: %s, Modelo: %s, Ano de Fabricacao: %d\n", carro->placa, carro->modelo, carro->anoDeFabricacao);
}

// Função para exibir todos os carros atendidos
void mostrarVeiculosAtendidos(Fila *atendidos) {
    if (atendidos == NULL) {
        printf("\nNenhum carro foi atendido ainda.\n"); // Se a fila de carros atendidos estiver vazia
        return;
    }

    printf("\nCarros atendidos:\n");
    for (int i = 0; i < atendidos->tam; i++) {
        printf("Placa: %s, Modelo: %s, Ano de Fabricacao: %d\n", atendidos->carros[i].placa, atendidos->carros[i].modelo, atendidos->carros[i].anoDeFabricacao);
    }
}

// Função principal
int main() {
    Fila fila, atendidos;
    criaFila(&fila, 5); // Cria a fila de carros
    criaFila(&atendidos, 5); // Cria a fila de carros atendidos

    int opcao;
    char placa[8];
    Carro carro, carroEncontrado, carroAtendido;

    do {
        printf("\nMENU:\n");
        printf("1 - Adicionar carro na fila\n");
        printf("2 - Atender um carro\n");
        printf("3 - Verificar se um carro esta na fila\n");
        printf("4 - Exibir carros esperando atendimento\n");
        printf("5 - Exibir carros que ja foram atendidos\n");
        printf("6 - Sair\n");
        printf("Informe a opcao desejada:\n");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                printf("\nInforme a placa do carro:\n");
                fflush(stdin);
                scanf("%50[^\n]", carro.placa);
                printf("Informe o modelo do carro:\n(maximo 50 caraceteres)\n");
                fflush(stdin);
                scanf("%50[^\n]", carro.modelo);
                printf("Informe o ano de fabricacao do carro:\n");
                scanf("%d", &carro.anoDeFabricacao);
                adicionarNaFila(&fila, carro);
                break;
            case 2:
                if (removerDaFila(&fila, &carroAtendido) == 0) {
                    exibirCarroAtendidoRecente(&carroAtendido);
                    adicionarNaFila(&atendidos, carroAtendido); // Adiciona o carro atendido à fila de carros atendidos
                } else {
                    printf("\nNao ha carros na fila!\n");
                }
                break;
            case 3:
                printf("\nInforme a placa do carro:\n");
                fflush(stdin);
                scanf("%7s", placa); // Limita a entrada de placa a 7 caracteres para evitar overflow
                if (buscarPlaca(&fila, placa, &carroEncontrado) == 1) {
                    printf("\nO carro com a placa %s esta na fila\n", placa);
                } else {
                    printf("\nO carro com a placa %s nao esta na fila\n", placa);
                }
                break;
            case 4:
                printf("\nCarros esperando atendimento:\n");
                mostrarFila(&fila);
                break;
            case 5:
                mostrarVeiculosAtendidos(&atendidos);
                break;
            case 6:
                printf("\nSaindo...\n");
                break;
            default:
                printf("\nOpcao invalida!\n");
                break;
        }
    } while (opcao != 6);

    // Libera a memória alocada para as filas
    free(fila.carros);
    free(atendidos.carros);

    return 0;
}
