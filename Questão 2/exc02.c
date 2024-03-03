//Anna Karolyna Pereira Santos - 12221BCC046 | Fernanda Ferreira de Melo - 12211BCC043 | Giovana M. Ferreira - 12221BCC033 | Gustavo Henrique - 12311BCC021

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAMANHO 5

typedef struct livro{
    int codigo;
    char titulo[30];
    char autor[30];
}LIVRO;

typedef struct pilha{
    int topo;
    LIVRO livro[TAMANHO];

}PILHA;

void inicializar_pilha(PILHA *p){
    p->topo = 0;
}


void adicionar_livro(LIVRO novo_livro, PILHA *p){
    if(p->topo == TAMANHO){
        printf("Pilha cheia! :(\n");
    }else{
         p->livro[p->topo] = novo_livro;
         printf("Livro adicionado!\n");
         p-> topo++;
         return;
        }
}

void remover_livro(PILHA *p){
    if(p-> topo == 0){
        printf("Nao ha livros para remover!\n");
        return;
    }else{
        p-> topo--;
        printf("%s foi removido da pilha!\n", p->livro[p->topo].titulo);
    }
}

void mostrar_pilha(PILHA *p){
    if(p-> topo == 0){
        printf("Pilha vazia :(\n)");
    }else{
        printf("-------------Pilha de livros-------------\n");
        printf("\n");
        for(int i = 0; i < p-> topo; i++){
        printf("Titulo: %s\n", p-> livro[i].titulo);
        printf("Autor: %s\n", p-> livro[i].autor);
        printf("Codigo: %d\n", p->livro[i].codigo);
    }
    }
    
}


int main(){
    PILHA livros_biblioteca;
    inicializar_pilha(&livros_biblioteca);

    int opcao;

    do {
        printf("-------------Biblioteca virtual-------------\n");
        printf("\n");
        printf("Escolha o que deseja fazer: \n");
        printf("(1) Adicionar livro:\n(2) Remover livro\n(3) Mostrar livros na pilha\n(0) Sair\n");
        scanf("%d", &opcao);

        switch(opcao){

            case 1: // Adicionar livro
            {
                LIVRO novo_livro;

                printf("Digite o codigo do livro:\n");
                scanf("%d", &novo_livro.codigo);
                fflush(stdin);
                printf("Digite o titulo:\n");
                scanf("%s", novo_livro.titulo);
                fflush(stdin);
                printf("Digite o nome do autor:\n");
                scanf("%s", novo_livro.autor);
                fflush(stdin);
                
                adicionar_livro(novo_livro, &livros_biblioteca);
                break;
            }
            
            case 2: //Remover livro
                remover_livro(&livros_biblioteca);
                break;
            
            case 3: //Mostrar livros
            {
                mostrar_pilha(&livros_biblioteca);
                break;
            }

            case 0: //Só sair
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida! Tente novamente.");
                break;
        }
    } while (opcao != 0);

    return 0;
}
