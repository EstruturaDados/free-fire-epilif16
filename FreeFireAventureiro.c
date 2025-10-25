#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define MAX_TAM 10

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// --------------------------- LISTA SEQUENCIAL (VETOR) ---------------------------

typedef struct {
    Item itens[MAX_TAM];
    int quantidade;
} MochilaVetor;

void iniciarMochilaVetor(MochilaVetor *m) {
    m->quantidade = 0;
}

void inserirVetor(MochilaVetor *m) {
    if (m->quantidade >= MAX_TAM) {
        printf("Mochila cheia!\n");
        return;
    }
    Item novo;
    printf("Nome do item: ");
    fgets(novo.nome, 30, stdin);
    novo.nome[strcspn(novo.nome, "\n")] = 0;
    printf("Tipo do item: ");
    fgets(novo.tipo, 20, stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = 0;
    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);
    getchar();
    m->itens[m->quantidade++] = novo;
    printf("Item '%s' adicionado!\n", novo.nome);
}

void listarVetor(const MochilaVetor *m) {
    if (m->quantidade == 0) {
        printf("Mochila vazia.\n");
        return;
    }
    printf("\n--- Itens (Vetor) ---\n");
    for (int i = 0; i < m->quantidade; i++) {
        printf("%d. %s (%s) - %d un.\n", i+1, m->itens[i].nome, m->itens[i].tipo, m->itens[i].quantidade);
    }
}

void removerVetor(MochilaVetor *m) {
    if (m->quantidade == 0) {
        printf("Mochila vazia.\n");
        return;
    }
    char nome[30];
    printf("Nome do item a remover: ");
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = 0;
    int i, pos = -1;
    for (i = 0; i < m->quantidade; i++) {
        if (strcmp(m->itens[i].nome, nome) == 0) {
            pos = i;
            break;
        }
    }
    if (pos == -1) {
        printf("Item não encontrado.\n");
        return;
    }
    for (i = pos; i < m->quantidade - 1; i++) {
        m->itens[i] = m->itens[i + 1];
    }
    m->quantidade--;
    printf("Item removido.\n");
}

int buscaSequencialVetor(const MochilaVetor *m, const char *nome, int *comparacoes) {
    *comparacoes = 0;
    for (int i = 0; i < m->quantidade; i++) {
        (*comparacoes)++;
        if (strcmp(m->itens[i].nome, nome) == 0) {
            return i;
        }
    }
    return -1;
}

void ordenarVetor(MochilaVetor *m) {
    for (int i = 0; i < m->quantidade - 1; i++) {
        for (int j = 0; j < m->quantidade - i - 1; j++) {
            if (strcmp(m->itens[j].nome, m->itens[j + 1].nome) > 0) {
                Item temp = m->itens[j];
                m->itens[j] = m->itens[j + 1];
                m->itens[j + 1] = temp;
            }
        }
    }
    printf("Itens ordenados alfabeticamente.\n");
}

int buscaBinariaVetor(const MochilaVetor *m, const char *nome, int *comparacoes) {
    int ini = 0, fim = m->quantidade - 1;
    *comparacoes = 0;
    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        (*comparacoes)++;
        int cmp = strcmp(m->itens[meio].nome, nome);
        if (cmp == 0) return meio;
        else if (cmp < 0) ini = meio + 1;
        else fim = meio - 1;
    }
    return -1;
}

// --------------------------- LISTA ENCADEADA ---------------------------

typedef struct No {
    Item dados;
    struct No* proximo;
} No;

typedef struct {
    No *inicio;
} MochilaLista;

void iniciarMochilaLista(MochilaLista *m) {
    m->inicio = NULL;
}

void inserirLista(MochilaLista *m) {
    Item novo;
    printf("Nome do item: ");
    fgets(novo.nome, 30, stdin);
    novo.nome[strcspn(novo.nome, "\n")] = 0;
    printf("Tipo do item: ");
    fgets(novo.tipo, 20, stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = 0;
    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);
    getchar();

    No *novoNo = (No*) malloc(sizeof(No));
    novoNo->dados = novo;
    novoNo->proximo = m->inicio;
    m->inicio = novoNo;
    printf("Item '%s' adicionado!\n", novo.nome);
}

void listarLista(const MochilaLista *m) {
    if (m->inicio == NULL) {
        printf("Mochila vazia.\n");
        return;
    }
    printf("\n--- Itens (Lista Encadeada) ---\n");
    No *atual = m->inicio;
    int i = 1;
    while (atual != NULL) {
        printf("%d. %s (%s) - %d un.\n", i++, atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
        atual = atual->proximo;
    }
}

void removerLista(MochilaLista *m) {
    if (m->inicio == NULL) {
        printf("Mochila vazia.\n");
        return;
    }
    char nome[30];
    printf("Nome do item a remover: ");
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = 0;

    No *atual = m->inicio, *anterior = NULL;
    while (atual != NULL && strcmp(atual->dados.nome, nome) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }
    if (atual == NULL) {
        printf("Item não encontrado.\n");
        return;
    }
    if (anterior == NULL)
        m->inicio = atual->proximo;
    else
        anterior->proximo = atual->proximo;
    free(atual);
    printf("Item removido.\n");
}

int buscaSequencialLista(const MochilaLista *m, const char *nome, int *comparacoes) {
    *comparacoes = 0;
    No *atual = m->inicio;
    while (atual != NULL) {
        (*comparacoes)++;
        if (strcmp(atual->dados.nome, nome) == 0)
            return 1;
        atual = atual->proximo;
    }
    return 0;
}

void liberarLista(MochilaLista *m) {
    No *atual = m->inicio;
    while (atual != NULL) {
        No *temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    m->inicio = NULL;
}

// --------------------------- MENU PRINCIPAL ---------------------------

int main() {
    MochilaVetor mochilaV;
    MochilaLista mochilaL;
    iniciarMochilaVetor(&mochilaV);
    iniciarMochilaLista(&mochilaL);

    int opcao;
    do {
        printf("\n===== MENU =====\n");
        printf("1. Inserir item (vetor)\n");
        printf("2. Inserir item (lista)\n");
        printf("3. Listar itens (vetor)\n");
        printf("4. Listar itens (lista)\n");
        printf("5. Remover item (vetor)\n");
        printf("6. Remover item (lista)\n");
        printf("7. Ordenar vetor e buscar (binária)\n");
        printf("8. Buscar item (sequencial em ambas)\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        char nome[30];
        int compV, compL;

        switch (opcao) {
            case 1: inserirVetor(&mochilaV); break;
            case 2: inserirLista(&mochilaL); break;
            case 3: listarVetor(&mochilaV); break;
            case 4: listarLista(&mochilaL); break;
            case 5: removerVetor(&mochilaV); break;
            case 6: removerLista(&mochilaL); break;
            case 7:
                ordenarVetor(&mochilaV);
                printf("Nome para busca binária: ");
                fgets(nome, 30, stdin);
                nome[strcspn(nome, "\n")] = 0;
                int pos = buscaBinariaVetor(&mochilaV, nome, &compV);
                if (pos != -1)
                    printf("Item encontrado no vetor em %d comparações.\n", compV);
                else
                    printf("Item não encontrado (%d comparações).\n", compV);
                break;
            case 8:
                printf("Nome para busca sequencial: ");
                fgets(nome, 30, stdin);
                nome[strcspn(nome, "\n")] = 0;
                int posSeq = buscaSequencialVetor(&mochilaV, nome, &compV);
                int achouLista = buscaSequencialLista(&mochilaL, nome, &compL);
                printf("Vetor -> %s (%d comparações)\n", posSeq != -1 ? "Encontrado" : "Não encontrado", compV);
                printf("Lista -> %s (%d comparações)\n", achouLista ? "Encontrado" : "Não encontrado", compL);
                break;
            case 0:
                liberarLista(&mochilaL);
                printf("Encerrando...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }

    } while (opcao != 0);

    return 0;
}
