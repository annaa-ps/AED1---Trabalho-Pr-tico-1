//Anna Karolyna Pereira Santos - 12221BCC046 | Fernanda Ferreira de Melo - 12211BCC043 | Giovana M. Ferreira - 12221BCC033 | Gustavo Henrique - 12311BCC021

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXTAM 5 //depois quando tiver certo eu mudo pra mais, tipo uns 10


typedef struct produto{

    int codigo, quantidade;
    char nome_produto[20];

}PRODUTO;

typedef struct fila{

    PRODUTO elementos[MAXTAM]; // MAXTAM = 5
    int inicio, fim;

}FILA;

void inicializa_fila(FILA *f){ // 
    f->inicio = 0;
    f->fim = 0;
}
 
void adiciona_produto(PRODUTO produto_novo, FILA *f){

    if(f->fim == MAXTAM){ //tenho que verificar porque se o fim da fila for igual o tamanho do elementos significa que ela está cheia.
        printf("Fila cheia! :(\n)");
        return;

    }else{
        f->elementos[f->fim] = produto_novo;// aqui tô inserindo um elemento novo do tipo PRODUTO no final da fila;
        f->fim++; // incrementa o fim porque um produto foi adicionado na posição que era o fim (antes da inserção)
        printf("Produto adicionado!\n");
    }
}

PRODUTO remove_produtos(FILA *f){

    PRODUTO dado; // essa variável vai servir como uma espécie de "backup" da informação que eu to retirando (ela é retornada no final dessa função)

    if(f->inicio == f->fim){
        printf("Fila vazia. Nao temos elementos para serem removidos.\n"); //se não tiver uma função de fila cheia e vazia eu sempre vou ter que repetir essa verificação de forma "manual"
    }else{
        dado = f->elementos[f->inicio];
        for(int i = 0; i < f->fim -1; i++){
            f->elementos[i] = f->elementos[i+1];
        }
        f->fim--;
    }
    printf("Produto removido.\n");
    return dado;
}

void atualizar_nome(FILA *f, int codigo, char novo_nome[20]){
    int existe_produto = 0; // pra ver se existe na fila

    for(int i = f->inicio; i < f->fim; i++){
        if(f->elementos[i].codigo == codigo){
            strcpy(f->elementos[i].nome_produto, novo_nome);
            printf("Nome alterado.\n");
            existe_produto = 1;
            break;
        } else if(existe_produto == 0){
            printf("Produto nao encontrado! :(\n)");
            }
    }
}



void mostrar_fila(FILA *f){

    if(f->inicio == f->fim){
        printf("Nao ha elementos nessa fila.");
    }else{
        printf("-------------Produtos Encontrados-------------\n");
        for(int i = f->inicio; i < f->fim; i++){
            printf("Nome: %s\n", f-> elementos[i].nome_produto);
            printf("Codigo: %d\n", f->elementos[i].codigo);
            printf("Quantidade disponivel no estoque: %d\n", f->elementos[i].quantidade);
            printf("-------------\n");
            printf("\n");
        }
    }
}

int main(){
    FILA fila_embalados;
    inicializa_fila(&fila_embalados);

    int opcao;

    do {
        printf("-------------Produtos a serem embalados-------------\n");
        printf("\n");
        printf("Escolha o que deseja fazer: \n");
        printf("(1) Adicionar produto:\n(2) Remover produto\n(3) Atualizar o nome de um produto\n(4) Mostrar fila de produtos\n(0) Sair\n\n");
        scanf("%d", &opcao);

        switch(opcao){

            case 1: // Adicionar produto
            {
                PRODUTO produto_novo;

                printf("Digite o codigo do produto:\n");
                scanf("%d", &produto_novo.codigo);
                printf("Digite a quantidade que deseja adicionar:\n");
                scanf("%d", &produto_novo.quantidade);
                printf("Digite o nome:\n");
                scanf("%s", produto_novo.nome_produto);
                
                adiciona_produto(produto_novo, &fila_embalados);
                break;
            }
            
            case 2: //Remover produtos
                remove_produtos(&fila_embalados);
                break;
            
            case 3: //Alterar nome
            {
                int cdg; 
                char novo_nome[20]; 
                printf("Digite o codigo do produto que deseja alterar:\n");
                scanf("%d", &cdg);
                printf("Digite o novo nome:\n");
                scanf("%s", novo_nome);
                atualizar_nome(&fila_embalados, cdg, novo_nome);
                break;
            }

            case 4: //Mostrar fila
                mostrar_fila(&fila_embalados);
                break;
            
            case 0: //Só pra sair
                printf("Saindo...\n");
                break;

            default: // De lei
                printf("Opcao invalida! Tente novamente.");
                break;
        }
    } while (opcao != 0);

    return 0;
}
