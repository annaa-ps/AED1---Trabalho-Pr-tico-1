//Anna Karolyna Pereira Santos - 12221BCC046 | Fernanda Ferreira de Melo - 12211BCC043 | Giovana M. Ferreira - 12221BCC033 | Gustavo Henrique - 12311BCC021

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int matricula;
    char nome[50];
    char curso[50];
    char situacao[20];
} Aluno;

typedef struct No {
    Aluno aluno;
    struct No *prox;
} No;

typedef struct {
    No *inicio;
    No *fim;
} Fila;

int proximaMatricula = 1;

void inicializarFila(Fila *fila) {
    fila->inicio = NULL;
    fila->fim = NULL;
}

void enfileirarAluno(Fila *fila, Aluno aluno) {
    No *novoNo = (No *)malloc(sizeof(No));
    novoNo->aluno = aluno;
    novoNo->prox = NULL;

    if (fila->fim == NULL) {
        fila->inicio = novoNo;
        fila->fim = novoNo;
    } else {
        fila->fim->prox = novoNo;
        fila->fim = novoNo;
    }
}

No *buscarAluno(Fila *fila, int matricula) {
    No *atual = fila->inicio;

    while (atual != NULL) {
        if (atual->aluno.matricula == matricula) {
            return atual;
        }
        atual = atual->prox;
    }

    return NULL;
}

void atualizarAluno(Fila *fila, int matricula, Aluno novoAluno) {
    No *alunoEncontrado = buscarAluno(fila, matricula);

    if (alunoEncontrado != NULL) {
        strcpy(alunoEncontrado->aluno.nome, novoAluno.nome);
        strcpy(alunoEncontrado->aluno.curso, novoAluno.curso);
        strcpy(alunoEncontrado->aluno.situacao, novoAluno.situacao);
    } else {
        printf("Aluno com matricula %d não encontrado.\n", matricula);
    }
}

void moverParaFormados(Fila *filaAlunos, Fila *filaFormados, int matricula) {
    No *alunoEncontrado = buscarAluno(filaAlunos, matricula);

    if (alunoEncontrado != NULL) {
        strcpy(alunoEncontrado->aluno.situacao, "formado");

        enfileirarAluno(filaFormados, alunoEncontrado->aluno);
    } else {
        printf("Aluno com matricula %d nao encontrado.\n", matricula);
    }
}

void moverParaDesistentes(Fila *filaAlunos, Fila *filaDesistentes, int matricula) {
    No *alunoEncontrado = buscarAluno(filaAlunos, matricula);

    if (alunoEncontrado != NULL) {

        strcpy(alunoEncontrado->aluno.situacao, "desistente");

        enfileirarAluno(filaDesistentes, alunoEncontrado->aluno);
    } else {
        printf("Aluno com matricula %d nao encontrado.\n", matricula);
    }
}

void listarAlunos(Fila *fila) {
    No *atual = fila->inicio;

    printf("Lista de alunos matriculados:\n");
    while (atual != NULL) {
        printf("Matricula: %d, Nome: %s, Curso: %s, Situacao: %s\n", atual->aluno.matricula, atual->aluno.nome, atual->aluno.curso, atual->aluno.situacao);
        atual = atual->prox;
    }
    printf("\n");
}

void listarDesistentes(Fila *fila) {
    No *atual = fila->inicio;

    printf("Lista de alunos desistentes:\n");
    while (atual != NULL) {
        if (strcmp(atual->aluno.situacao, "desistente") == 0) {
            printf("Matricula: %d, Nome: %s, Curso: %s\n", atual->aluno.matricula, atual->aluno.nome, atual->aluno.curso);
        }
        atual = atual->prox;
    }
    printf("\n");
}

void listarFormados(Fila *fila) {
    No *atual = fila->inicio;

    printf("Lista de alunos formados:\n");
    while (atual != NULL) {
        if (strcmp(atual->aluno.situacao, "formado") == 0) {
            printf("Matricula: %d, Nome: %s, Curso: %s\n", atual->aluno.matricula, atual->aluno.nome, atual->aluno.curso);
        }
        atual = atual->prox;
    }
    printf("\n");
}

int main() {
    Fila filaAlunos, filaFormados, filaDesistentes;
    inicializarFila(&filaAlunos);
    inicializarFila(&filaFormados);
    inicializarFila(&filaDesistentes);

    int opcao;
    do {
        printf("Escolha a opcao:\n");
        printf("1 - Inserir aluno\n");
        printf("2 - Atualizar dados do aluno\n");
        printf("3 - Formar aluno\n");
        printf("4 - Desistir do aluno\n");
        printf("5 - Listar todos os alunos matriculados\n");
        printf("6 - Listar alunos desistentes\n");
        printf("7 - Listar alunos formados\n");
        printf("0 - Sair\n");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                Aluno novoAluno;
                printf("Matricula: ");
                scanf("%d", &novoAluno.matricula);
                printf("Nome: ");
                scanf("%s", novoAluno.nome);
                printf("Curso: ");
                scanf("%s", novoAluno.curso);
                printf("Situacao (cursando/formado/desistente): ");
                scanf("%s", novoAluno.situacao);

                enfileirarAluno(&filaAlunos, novoAluno);
                printf("Aluno matriculado com sucesso!\n");
                break;
            }
            case 2: {
                int matricula;
                printf("Informe a matricula do aluno a ser atualizado: ");
                scanf("%d", &matricula);

                Aluno novoAluno;
                printf("Novo nome: ");
                scanf("%s", novoAluno.nome);
                printf("Novo curso: ");
                scanf("%s", novoAluno.curso);
                printf("Nova situacao (cursando/formado/desistente): ");
                scanf("%s", novoAluno.situacao);

                atualizarAluno(&filaAlunos, matricula, novoAluno);
                break;
            }
            case 3: {
                int matricula;
                printf("Informe a matricula do aluno a ser formado: ");
                scanf("%d", &matricula);

                moverParaFormados(&filaAlunos, &filaFormados, matricula);
                printf("Aluno formado com sucesso!\n");
                break;
            }
            case 4: {
                int matricula;
                printf("Informe a matricula do aluno a desistir: ");
                scanf("%d", &matricula);

                moverParaDesistentes(&filaAlunos, &filaDesistentes, matricula);
                printf("Aluno desistente removido com sucesso!\n");
                break;
            }
            case 5:
                listarAlunos(&filaAlunos);
                break;
            case 6:
                listarDesistentes(&filaDesistentes);
                break;
            case 7:
                listarFormados(&filaFormados);
                break;
            case 0:
                printf("Programa encerrado.\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 0);

    return 0;
}
