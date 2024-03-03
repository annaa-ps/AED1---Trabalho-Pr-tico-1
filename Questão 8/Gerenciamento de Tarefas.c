//Anna Karolyna Pereira Santos - 12221BCC046 | Fernanda Ferreira de Melo - 12211BCC043 | Giovana M. Ferreira - 12221BCC033 | Gustavo Henrique - 12311BCC021

#include<stdio.h>
#include<stdlib.h>

// Definindo constantes para representar os status das tarefas
#define A_FAZER 0
#define EM_ANDAMENTO 1
#define CONCLUIDA 2

//Struct para armazenar os dados do produto
typedef struct {
  char nome[50];
  char data[11];
  char prazo[11];
  int status; 
}Tarefa;

typedef struct no{
    Tarefa tarefa;
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
Tarefa ler_tarefa(){
    Tarefa tarefa; 
    printf("\nInforme o nome da tarefa:\n");
    scanf("%49[^\n]", tarefa.nome);
    getchar();
    printf("\nInforme a data de criacao (dd/mm/aaaa):\n");
    scanf("%10s", tarefa.data);
    printf("\nInforme o prazo para a conclusao (dd/mm/aaaa):\n");
    scanf("%10s",tarefa.prazo);
    printf("\nInforme o status da tarefa (0 - A fazer, 1 - Em andamento, 2 - Concluída):\n");
    scanf("%d", &tarefa.status);
    return tarefa; 
}

//Função para a operação push(empilhar/adicionar) um novo produto ao estoque (Letra A)
void adicionar_tarefa(Pilha *pilha, Tarefa tarefa){
    No *novo = malloc(sizeof(No));
    if(novo){
      novo->tarefa = tarefa;
      novo->proximo = pilha->topo;
      pilha->topo = novo; 
      pilha->tam++;
    }else{
        printf("\nErro ao alocar memoria\n");
    }
}

//Função para a operação pop(desempilhar/remover) um produto do estoque (Letra B)
Tarefa remover_tarefa(Pilha *pilha){
    if(pilha->topo == NULL){
      printf("Pilha vazia!\n");
      Tarefa tarefaVazia = {"","", A_FAZER};
      return tarefaVazia;
    }
  No *remover = pilha->topo; 
  Tarefa tarefaRemovida = remover->tarefa;
  pilha->topo = remover->proximo;
  free(remover);
  pilha->tam--;
  return tarefaRemovida; 
}

//Função para exibir as tarefas
void imprimirTarefas(Pilha *pilha, int status){
  printf("----------------------------------------\n");
  printf("Status: ");
  switch(status){
    case A_FAZER:
      printf("A fazer\n");
      break;
    case EM_ANDAMENTO:
      printf("Em amdamento\n");
        break;
    case CONCLUIDA:
      printf("Concluida\n");
      break;
  }
  printf("----------------------------------------");
  No *aux = pilha->topo;
  while(aux){
    if(aux->tarefa.status == status){
      printf("\nTarefa: %s\n", aux->tarefa.nome);
      printf("Data de criação: %.2s/%.2s/%.4s\n", aux->tarefa.data, &aux->tarefa.data[3], &aux->tarefa.data[6]);
      printf("Prazo para a conclusão: %.2s/%.2s/%.4s\n", aux->tarefa.prazo, &aux->tarefa.prazo[3], &aux->tarefa.prazo[6]);
      printf("----------------------------------------\n");
    }
    aux = aux->proximo; 
  }
}

//Função para iniciar uma tarefa
void iniciarTarefa(Pilha *origem, Pilha *destino){
  Tarefa tarefaIniciada = remover_tarefa(origem);
  tarefaIniciada.status = EM_ANDAMENTO;
  adicionar_tarefa(destino, tarefaIniciada);
  printf("\nTarefa iniciada com sucesso!\n");
}

//Função para concluir uma tarefa
void concluirTarefa(Pilha *origem, Pilha *destino){
  Tarefa tarefaConcluida = remover_tarefa(origem);
  tarefaConcluida.status = CONCLUIDA;
  adicionar_tarefa(destino, tarefaConcluida);
  printf("Tarefa concluida com sucesso!\n");
}

int main(){
  Pilha aFazer, emAndamento, concluida;
  int opcao;
  Tarefa novaTarefa; 
  
  criar_pilha(&aFazer);
  criar_pilha(&emAndamento);
  criar_pilha(&concluida);

  do{
    printf("\n-------------------------MENU DE OPCOES-------------------------------\n");
    printf("1 - Adicionar uma nova tarefa\n2 - Iniciar uma tarefa\n3 - Concluir uma tarefa\n");
    printf("4 - Exibir todas as tarefas pendentes\n5 - Exibir as tarefas em andamento\n");
    printf("6 - Exibir tarefas concluídas\n7 - Sair\n");
    printf("----------------------------------------------------------------------\n");
    scanf("%d", &opcao);
    getchar();

    switch (opcao){
      case 1:
        novaTarefa = ler_tarefa();
        adicionar_tarefa(&aFazer, novaTarefa);
        break;
      case 2:
        if(aFazer.topo != NULL){
          iniciarTarefa(&aFazer, &emAndamento);
        }else{
          printf("Nao ha tarefas pendentes para iniciar!\n");
        }
        break;
      case 3:
        if(emAndamento.topo !=  NULL){
          concluirTarefa(&emAndamento, &concluida);
        }else{
          printf("Nao ha tarefas em andamento para concluir!\n");
        }
        break;
      case 4:
        imprimirTarefas(&aFazer, A_FAZER); 
        break;
      case 5:
        imprimirTarefas(&emAndamento, EM_ANDAMENTO);
        break;
    case 6:
      imprimirTarefas(&concluida, CONCLUIDA);
      break;;
    case 7:
      printf("Saindo...\n");
      break;
    default:
          printf("\nOpcao invalida!\n"); 
        break;
    }  
  }while(opcao != 7);
  return 0;
}
