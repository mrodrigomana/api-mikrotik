#ifndef __PARSE_TEMS_H
#define __PARSE_TEMS_H

// Struct genérica para dados
typedef struct dados {
    char **retorno;  // Array de strings com os valores
    int total;       // Quantidade de itens neste retorno
}DATA;

// Nó da lista
typedef struct No {
    DATA info;          // Dado genérico
    struct No* prox;            // Ponteiro para o próximo
} No;

// Funções da lista encadeada
No* criar_no(void);
void adicionar_no(No** head, DATA novo_dado);
void liberar_lista(No** head);
void imprimir_lista(No* head);
void imprimir_dado_especifico(No* head, int indice);

#endif