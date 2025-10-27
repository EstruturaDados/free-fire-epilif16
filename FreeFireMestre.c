#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define MAX_COMPONENTES 20
#define TAM_NOME 30
#define TAM_TIPO 20

typedef struct {
    char nome[TAM_NOME];
    char tipo[TAM_TIPO];
    int prioridade; // 1..10
} Componente;

typedef enum {
    NAO_ORDENADO = 0,
    ORDENADO_POR_NOME,
    ORDENADO_POR_TIPO,
    ORDENADO_POR_PRIORIDADE
} EstadoOrdenacao;

// assinaturas
void cadastrarComponente(Componente lista[], int *n);
void listarComponentes(const Componente lista[], int n);
void imprimirComponente(const Componente *c, int idx);
void removerComponente(Componente lista[], int *n); // NOVA FUNÇÃO
void bubbleSortPorNome(Componente lista[], int n, long long *comparacoes, double *tempo);
void insertionSortPorTipo(Componente lista[], int n, long long *comparacoes, double *tempo);
void selectionSortPorPrioridade(Componente lista[], int n, long long *comparacoes, double *tempo);
int buscaBinariaPorNome(const Componente lista[], int n, const char *chave, long long *comparacoes);
void flush_input();

// funçao principal
int main() {
    Componente componentes[MAX_COMPONENTES];
    int n = 0;
    EstadoOrdenacao estado = NAO_ORDENADO;
    int opcao;

    printf("=== SISTEMA DE PRIORIZACAO E MONTAGEM - TORRE DE FUGA ===\n");

    do {
        printf("\nMENU:\n");
        printf("1 - Cadastrar componente (até %d)\n", MAX_COMPONENTES);
        printf("2 - Listar componentes\n");
        printf("3 - Ordenar por NOME\n");
        printf("4 - Ordenar por TIPO\n");
        printf("5 - Ordenar por PRIORIDADE\n");
        printf("6 - Busca BINÁRIA por NOME (requer ordenação por nome)\n");
        printf("7 - Exibir montagem final e confirmar componente-chave\n");
        printf("8 - Remover componente\n"); // NOVA OPÇÃO
        printf("0 - Ativar torre de fuga\n");
        printf("Escolha: ");
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada inválida.\n");
            flush_input();
            continue;
        }
        flush_input();

        if (opcao == 1) {
            cadastrarComponente(componentes, &n);
            estado = NAO_ORDENADO;
        } else if (opcao == 2) {
            listarComponentes(componentes, n);
        } else if (opcao == 3) {
            if (n <= 1) {
                printf("Poucos componentes para ordenar.\n");
            } else {
                long long comps = 0;
                double tempo = 0.0;
                bubbleSortPorNome(componentes, n, &comps, &tempo);
                estado = ORDENADO_POR_NOME;
                printf("Bubble Sort concluído: %lld comparações, %.6f s\n", comps, tempo);
            }
        } else if (opcao == 4) {
            if (n <= 1) {
                printf("Poucos componentes para ordenar.\n");
            } else {
                long long comps = 0;
                double tempo = 0.0;
                insertionSortPorTipo(componentes, n, &comps, &tempo);
                estado = ORDENADO_POR_TIPO;
                printf("Insertion Sort concluído: %lld comparações, %.6f s\n", comps, tempo);
            }
        } else if (opcao == 5) {
            if (n <= 1) {
                printf("Poucos componentes para ordenar.\n");
            } else {
                long long comps = 0;
                double tempo = 0.0;
                selectionSortPorPrioridade(componentes, n, &comps, &tempo);
                estado = ORDENADO_POR_PRIORIDADE;
                printf("Selection Sort concluído: %lld comparações, %.6f s\n", comps, tempo);
            }
        } else if (opcao == 6) {
            if (estado != ORDENADO_POR_NOME) {
                printf("Ordene por nome antes da busca (opção 3).\n");
            } else {
                char chave[TAM_NOME];
                printf("Digite o nome do componente-chave: ");
                fgets(chave, TAM_NOME, stdin);
                chave[strcspn(chave, "\n")] = 0;
                long long comps = 0;
                int pos = buscaBinariaPorNome(componentes, n, chave, &comps);
                if (pos != -1) {
                    printf("Componente encontrado na posição %d (comparações: %lld)\n", pos, comps);
                    imprimirComponente(&componentes[pos], pos + 1);
                } else {
                    printf("Componente NÃO encontrado (comparações: %lld)\n", comps);
                }
            }
        } else if (opcao == 7) {
            if (n == 0) {
                printf("Nenhum componente cadastrado.\n");
            } else {
                printf("\n--- MONTAGEM FINAL ---\n");
                listarComponentes(componentes, n);
                char chave[TAM_NOME];
                printf("\nDigite o nome do componente-chave para confirmar: ");
                fgets(chave, TAM_NOME, stdin);
                chave[strcspn(chave, "\n")] = 0;
                bool presente = false;
                for (int i = 0; i < n; i++) {
                    if (strcmp(componentes[i].nome, chave) == 0) {
                        presente = true;
                        printf("\n>>> Componente '%s' PRESENTE na posição %d. Torre pronta!\n", chave, i + 1);
                        break;
                    }
                }
                if (!presente) {
                    printf("\n>>> Componente '%s' NÃO encontrado.\n", chave);
                }
            }
        } else if (opcao == 8) {
            removerComponente(componentes, &n);
            estado = NAO_ORDENADO;
        } else if (opcao == 0) {
            printf("Encerrando sistema...\n");
        } else {
            printf("Opção inválida.\n");
        }

    } while (opcao != 0);

    return 0;
}

// ---------- funções auxiliares ----------

void flush_input() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void cadastrarComponente(Componente lista[], int *n) {
    if (*n >= MAX_COMPONENTES) {
        printf("Limite máximo de componentes atingido (%d).\n", MAX_COMPONENTES);
        return;
    }

    Componente c;
    printf("Nome do componente: ");
    fgets(c.nome, TAM_NOME, stdin);
    c.nome[strcspn(c.nome, "\n")] = 0;

    if (strlen(c.nome) == 0) {
        printf("Nome inválido.\n");
        return;
    }

    printf("Tipo do componente (ex: controle, suporte, propulsao): ");
    fgets(c.tipo, TAM_TIPO, stdin);
    c.tipo[strcspn(c.tipo, "\n")] = 0;
    if (strlen(c.tipo) == 0) strcpy(c.tipo, "desconhecido");

    printf("Prioridade (1 a 10): ");
    int p;
    if (scanf("%d", &p) != 1) {
        printf("Entrada inválida.\n");
        flush_input();
        return;
    }
    flush_input();
    if (p < 1) p = 1;
    if (p > 10) p = 10;
    c.prioridade = p;

    lista[*n] = c;
    (*n)++;
    printf("Componente '%s' cadastrado.\n", c.nome);
}

void listarComponentes(const Componente lista[], int n) {
    if (n == 0) {
        printf("Nenhum componente cadastrado.\n");
        return;
    }
    printf("\n--- Lista de Componentes (%d) ---\n", n);
    for (int i = 0; i < n; i++) {
        imprimirComponente(&lista[i], i + 1);
    }
}

void imprimirComponente(const Componente *c, int idx) {
    printf("%2d) Nome: %-28s | Tipo: %-12s | Prioridade: %d\n", idx, c->nome, c->tipo, c->prioridade);
}

// ---------- NOVA FUNÇÃO: REMOVER COMPONENTE ----------

void removerComponente(Componente lista[], int *n) {
    if (*n == 0) {
        printf("Nenhum componente para remover.\n");
        return;
    }

    char nome[TAM_NOME];
    printf("Digite o nome do componente a remover: ");
    fgets(nome, TAM_NOME, stdin);
    nome[strcspn(nome, "\n")] = 0;

    int pos = -1;
    for (int i = 0; i < *n; i++) {
        if (strcmp(lista[i].nome, nome) == 0) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        printf("Componente '%s' não encontrado.\n", nome);
        return;
    }

    // desloca os elementos seguintes
    for (int i = pos; i < *n - 1; i++) {
        lista[i] = lista[i + 1];
    }
    (*n)--;

    printf("Componente '%s' removido com sucesso.\n", nome);
}

// ---------- Funções de ordenação e busca ----------

void bubbleSortPorNome(Componente lista[], int n, long long *comparacoes, double *tempo) {
    *comparacoes = 0;
    clock_t ini = clock();
    for (int i = 0; i < n - 1; i++) {
        bool trocou = false;
        for (int j = 0; j < n - i - 1; j++) {
            (*comparacoes)++;
            if (strcmp(lista[j].nome, lista[j + 1].nome) > 0) {
                Componente tmp = lista[j];
                lista[j] = lista[j + 1];
                lista[j + 1] = tmp;
                trocou = true;
            }
        }
        if (!trocou) break;
    }
    *tempo = (double)(clock() - ini) / CLOCKS_PER_SEC;
}

void insertionSortPorTipo(Componente lista[], int n, long long *comparacoes, double *tempo) {
    *comparacoes = 0;
    clock_t ini = clock();
    for (int i = 1; i < n; i++) {
        Componente chave = lista[i];
        int j = i - 1;
        while (j >= 0 && strcmp(lista[j].tipo, chave.tipo) > 0) {
            (*comparacoes)++;
            lista[j + 1] = lista[j];
            j--;
        }
        lista[j + 1] = chave;
    }
    *tempo = (double)(clock() - ini) / CLOCKS_PER_SEC;
}

void selectionSortPorPrioridade(Componente lista[], int n, long long *comparacoes, double *tempo) {
    *comparacoes = 0;
    clock_t ini = clock();
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            (*comparacoes)++;
            if (lista[j].prioridade < lista[min].prioridade) {
                min = j;
            }
        }
        if (min != i) {
            Componente tmp = lista[i];
            lista[i] = lista[min];
            lista[min] = tmp;
        }
    }
    *tempo = (double)(clock() - ini) / CLOCKS_PER_SEC;
}

int buscaBinariaPorNome(const Componente lista[], int n, const char *chave, long long *comparacoes) {
    int ini = 0, fim = n - 1;
    *comparacoes = 0;
    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        (*comparacoes)++;
        int cmp = strcmp(lista[meio].nome, chave);
        if (cmp == 0) return meio;
        else if (cmp < 0) ini = meio + 1;
        else fim = meio - 1;
    }
    return -1;
}
