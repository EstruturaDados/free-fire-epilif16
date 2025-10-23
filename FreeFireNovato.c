#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_TAM 10
#define MAX_STR 50

// Estrutura de cada item
typedef struct {
    char nome[MAX_STR];
    char tipo[MAX_STR];
    int quantidade;
} Item;

// Estrutura da lista de itens (mochila)
typedef struct {
    Item dados[MAX_TAM];
    int quantidade;
} lista;

// Inicializa a lista
void iniciarlista(lista *itens) {
    itens->quantidade = 0;
}

// Insere um novo item
void inserirlista(lista *itens, const char* nome, const char* tipo, int quantidade) {
    if (itens->quantidade == MAX_TAM) {
        printf("Sua mochila está cheia!\n");
        return;
    }

    strcpy(itens->dados[itens->quantidade].nome, nome);
    strcpy(itens->dados[itens->quantidade].tipo, tipo);
    itens->dados[itens->quantidade].quantidade = quantidade;
    itens->quantidade++;

    printf("Item '%s' do tipo '%s' (x%d) coletado!\n", nome, tipo, quantidade);
}

// Remove um item pelo nome
void removeritem(lista *itens, const char* nome) {
    int i, pos = -1;

    for (i = 0; i < itens->quantidade; i++) {
        if (strcmp(itens->dados[i].nome, nome) == 0) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        printf("Item '%s' não encontrado na mochila!\n", nome);
        return;
    }

    for (i = pos; i < itens->quantidade - 1; i++) {
        itens->dados[i] = itens->dados[i + 1];
    }

    itens->quantidade--;
    printf("Item '%s' removido!\n", nome);
}

// Lista todos os itens da mochila
void listaritens(const lista *itens) {
    if (itens->quantidade == 0) {
        printf("Mochila está vazia!\n");
        return;
    }

    printf("\n=== ITENS NA MOCHILA ===\n");
    for (int i = 0; i < itens->quantidade; i++) {
        printf("%d. Nome: %s | Tipo: %s | Quantidade: %d\n",
               i + 1,
               itens->dados[i].nome,
               itens->dados[i].tipo,
               itens->dados[i].quantidade);
    }
    printf("=========================\n");
}

// Busca sequencial por nome
void buscaritem(const lista *itens, const char* nome) {
    if (itens->quantidade == 0) {
        printf("A mochila está vazia.\n");
        return;
    }

    for (int i = 0; i < itens->quantidade; i++) {
        if (strcmp(itens->dados[i].nome, nome) == 0) {
            printf("\nItem encontrado!\n");
            printf("Nome: %s\n", itens->dados[i].nome);
            printf("Tipo: %s\n", itens->dados[i].tipo);
            printf("Quantidade: %d\n", itens->dados[i].quantidade);
            return;
        }
    }

    printf("Item '%s' não encontrado na mochila.\n", nome);
}

// Menu principal 
void menulista() {
    lista itens;
    iniciarlista(&itens);
    int opcao;
    char nome[MAX_STR], tipo[MAX_STR];
    int qtd;

    do {
        printf("\n=== MENU ===\n");
        printf("1. Cadastrar item\n");
        printf("2. Remover item\n");
        printf("3. Mostrar mochila\n");
        printf("4. Buscar item por nome\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // limpa o buffer

        switch (opcao) {
            case 1:
                if (itens.quantidade == MAX_TAM) {
                    printf("A mochila está cheia, não é possível adicionar mais itens.\n");
                    break;
                }
                printf("Digite o nome do item: ");
                fgets(nome, MAX_STR, stdin);
                nome[strcspn(nome, "\n")] = 0;

                printf("Digite o tipo do item (ex: arma, munição, cura): ");
                fgets(tipo, MAX_STR, stdin);
                tipo[strcspn(tipo, "\n")] = 0;

                printf("Digite a quantidade: ");
                scanf("%d", &qtd);
                getchar();

                inserirlista(&itens, nome, tipo, qtd);
                break;

            case 2:
                printf("Digite o nome do item para removê-lo: ");
                fgets(nome, MAX_STR, stdin);
                nome[strcspn(nome, "\n")] = 0;
                removeritem(&itens, nome);
                break;

            case 3:
                listaritens(&itens);
                break;

            case 4:
                printf("Digite o nome do item para buscar: ");
                fgets(nome, MAX_STR, stdin);
                nome[strcspn(nome, "\n")] = 0;
                buscaritem(&itens, nome);
                break;

            case 0:
                printf("Saindo do inventário...\n");
                break;

            default:
                printf("Opção inválida!\n");
                break;
        }

    } while (opcao != 0);
}

int main() {
    printf(">>>>>>> INVENTÁRIO FREE FIRE <<<<<<<<\n");
    menulista();
    return 0;
}
