//Anna Karolyna Pereira Santos - 12221BCC046 | Fernanda Ferreira de Melo - 12211BCC043 | Giovana M. Ferreira - 12221BCC033 | Gustavo Henrique - 12311BCC021

#include<stdio.h>
#include<stdlib.h>

//Struct para armazenar os dados do produto
typedef struct {
  int codigo;
  char descricao[50];
  int quantidade; 
}Estoque;

typedef struct no{
    Estoque produto;
    struct no *proximo;
}No;

//Struct para construir a pilha 
typedef struct{
  No *topo;
  int tam; 
}Pilha;

//Função para criar a pilha
void criar_pilha(Pilha *produto){
  produto->topo = NULL;
  produto->tam = 0; 
}

//Função do tipo Estoque para ler um novo produto para o estoque 
Estoque ler_produto(){
    Estoque produto; 
    printf("\nInforme o codigo do produto:\n");
    scanf("%d", &produto.codigo);
    getchar();
    printf("\nInforme a descricao do produto:\n");
    scanf("%49[^\n]", produto.descricao);
    printf("\nInforme a quantidade do produto que deseja adiacionar para estoque:\n");
    scanf("%d", &produto.quantidade); 
    return produto; 
}

//Função  para imprimir os dados do produto
void imprimir_produto(Estoque produto){
    printf("----------------------------------------");
    printf("\nCodigo: [%d]\n",produto.codigo); 
    printf("Descricao: [%s]\n", produto.descricao);
    printf("Quantidade em estoque: [%d]\n",           
    produto.quantidade); 
    printf("----------------------------------------\n");
}

//Função para a operação push(empilhar/adicionar) um novo produto ao estoque (Letra A)
void adicionar_caixa(Pilha *produto){
    No *novo = malloc(sizeof(No));
    if(novo){
      novo->produto = ler_produto();
      novo->proximo = produto->topo;
      produto->topo = novo; 
      produto->tam++;
    }else{
        printf("\nErro ao alocar memoria\n");
    }
}

//Função para a operação pop(desempilhar/remover) um produto do estoque (Letra B)
No* remover_caixa(Pilha *produto){
    if(produto->topo){
        No *remover = produto->topo;
        produto->topo = remover->proximo; 
        produto->tam--; 
        return remover;
    }else{
        printf("\nPilha vazia\n"); 
    }
    return NULL; 
}

//Função para pesquisar um produto pelo código (Letra C)
void pesquisar_codigo(Pilha *produto, int codigo){
  No *aux = produto->topo;
  int encontrado = 0;
  
  while(aux){
    if(aux->produto.codigo == codigo){
      printf("\n---------------------------------------");
      printf("\nProduto encontrado:\n");
      imprimir_produto(aux->produto);
      printf("\n");
      encontrado = 1;
      break;
    }
    aux = aux->proximo; 
  }
  if(!encontrado){
    printf("Produto nao encontrado\n"); 
  }
}

//Função para imprimir todos os produtos do estoque (Letra D) 
void imprimir_estoque(Pilha *produto){
  No *aux = produto->topo; 
  printf("\n\t\t\tESTOQUE\n");
  while(aux){
    imprimir_produto(aux->produto);
      aux = aux->proximo; 
  }
  printf("\t\t\tFIM DO ESTOQUE\n\n");
  printf("\n"); 
}

int main(){
  No *remover;
  Pilha produto;  
  int opcao, codigo; 

  criar_pilha(&produto);

  do{
    printf("\n-------------------------MENU DE OPCOES-------------------------------\n");
    printf("1 - Adicionar um novo produto\n2 - Remover um produto\n3 - Pesquisar um produto por codigo\n4 - Imprimir todo o estoque\n5 - Sair\n");
    printf("----------------------------------------------------------------------\n");
    scanf("%d", &opcao);
    getchar();
    
    switch (opcao){
      case 1:
        adicionar_caixa(&produto); 
        break;
      case 2:
        remover = remover_caixa(&produto);
        if(remover != NULL){
          printf("\n---------------------------------------");
          printf("\nProduto removido removido:\n");
          imprimir_produto(remover->produto); 
          printf("\n"); 
          free(remover);
        }else{
          printf("\nSem produto cadastrado para remover!\n");
        }
          break;
      case 3:
        printf("\nInforme o codigo do produto para pesquisar:\n");
        scanf("%d", &codigo);
        getchar();
        pesquisar_codigo(&produto, codigo);
        break;
      case 4:
        imprimir_estoque(&produto); 
        break;
      case 5:
        printf("\nFinalizando...\n");
        break;
      default:
        if (opcao != 0){
          printf("\nOpcao invalida!\n"); 
        }
        break;
    }   
  }while(opcao != 5);
  return 0;
}
