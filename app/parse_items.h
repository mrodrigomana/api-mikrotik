#ifndef __PARSE_TEMS_H
#define __PARSE_TEMS_H

// Struct genérica para dados (pode ser alterada conforme necessidade)
typedef struct {
    int id;
    char nome[50];
    float valor;
} Dado;

// Nó da lista
typedef struct No {
    Dado info;          // Dado genérico
    struct No* prox;    // Ponteiro para o próximo
} No;

typedef struct api_parse_s{
    char name[32];
    int id;
}API_PARSE_S;

void print_items();
#endif