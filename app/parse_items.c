#include <stdio.h>
#include <string.h>
#include "parse_items.h"

#include <stdio.h>
#include <stdlib.h>

// Cria um novo nó vazio
No* criar_no(void) {
    No* novo = (No*)malloc(sizeof(No));
    if (novo) {
        novo->info.retorno = NULL;
        novo->info.total = 0;
        novo->prox = NULL;
    }
    return novo;
}

// Adiciona um novo nó no final da lista
void adicionar_no(No** head, struct dados novo_dado) {
    No* novo = (No*)malloc(sizeof(No));
    if (!novo) {
        printf("Erro ao alocar memória para novo nó\n");
        return;
    }
    
    // Copia os dados
    novo->info.total = novo_dado.total;
    novo->info.retorno = (char**)malloc(novo_dado.total * sizeof(char*));
    
    if (!novo->info.retorno) {
        printf("Erro ao alocar memória para retorno\n");
        free(novo);
        return;
    }
    
    // Copia cada string individualmente
    for (int i = 0; i < novo_dado.total; i++) {
        novo->info.retorno[i] = (char*)malloc((strlen(novo_dado.retorno[i]) + 1) * sizeof(char));
        if (novo->info.retorno[i]) {
            strcpy(novo->info.retorno[i], novo_dado.retorno[i]);
        }
    }
    
    novo->prox = NULL;
    
    // Insere no final da lista
    if (*head == NULL) {
        *head = novo;
    } else {
        No* temp = *head;
        while (temp->prox != NULL) {
            temp = temp->prox;
        }
        temp->prox = novo;
    }
}

// Libera toda a memória da lista
void liberar_lista(No** head) {
    No* atual = *head;
    while (atual != NULL) {
        No* prox = atual->prox;
        
        // Libera as strings
        for (int i = 0; i < atual->info.total; i++) {
            free(atual->info.retorno[i]);
        }
        free(atual->info.retorno);
        free(atual);
        
        atual = prox;
    }
    *head = NULL;
}

// Imprime todos os dados da lista
void imprimir_lista(No* head) {
    No* atual = head;
    int num_entrada = 0;
    
    while (atual != NULL) {
        num_entrada++;
        printf("\n=== Entrada %d (Total de itens: %d) ===\n", num_entrada, atual->info.total);
        for (int i = 0; i < atual->info.total; i++) {
            printf("  %s\n", atual->info.retorno[i]);
        }
        atual = atual->prox;
    }
}

// Imprime um dado específico da lista pelo índice
void imprimir_dado_especifico(No* head, int indice) {
    No* atual = head;
    int count = 0;
    
    while (atual != NULL && count < indice) {
        atual = atual->prox;
        count++;
    }
    
    if (atual != NULL) {
        printf("\n=== Dado %d (Total de itens: %d) ===\n", indice, atual->info.total);
        for (int i = 0; i < atual->info.total; i++) {
            printf("  %s\n", atual->info.retorno[i]);
        }
    } else {
        printf("Índice %d não encontrado na lista\n", indice);
    }
}
