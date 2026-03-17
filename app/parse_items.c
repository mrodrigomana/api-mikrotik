#include <stdio.h>
#include <string.h>
#include "parse_items.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



// Criar um novo nó com dados
No* criarNo(int id, char* nome, float valor) {
    No* novo = (No*)malloc(sizeof(No));
    if (novo != NULL) {
        novo->info.id = id;
        strcpy(novo->info.nome, nome);
        novo->info.valor = valor;
        novo->prox = NULL;
    }
    return novo;
}

// Adicionar no final da lista
No* adicionar(No* cabeca, int id, char* nome, float valor) {
    No* novo = criarNo(id, nome, valor);
    
    if (novo == NULL) {
        printf("Erro: memória insuficiente!\n");
        return cabeca;
    }
    
    // Se a lista estiver vazia
    if (cabeca == NULL) {
        return novo;
    }
    
    // Percorre até o final
    No* atual = cabeca;
    while (atual->prox != NULL) {
        atual = atual->prox;
    }
    
    // Adiciona no final
    atual->prox = novo;
    return cabeca;
}

// Acessar do primeiro ao último (percorrer)
void acessarTodos(No* cabeca) {
    if (cabeca == NULL) {
        printf("Lista vazia!\n");
        return;
    }
    
    printf("\n=== Percorrendo a lista ===\n");
    No* atual = cabeca;
    int cont = 1;
    
    while (atual != NULL) {
        printf("Elemento %d:\n", cont);
        printf("  ID: %d\n", atual->info.id);
        printf("  Nome: %s\n", atual->info.nome);
        printf("  Valor: %.2f\n", atual->info.valor);
        printf("  ---\n");
        
        atual = atual->prox;
        cont++;
    }
    printf("Fim da lista (%d elementos)\n\n", cont-1);
}

// Destruir toda a lista
No* destruirLista(No* cabeca) {
    No* atual = cabeca;
    int cont = 0;
    
    while (atual != NULL) {
        No* temp = atual;
        atual = atual->prox;
        free(temp);
        cont++;
    }
    
    printf("Lista destruída! %d elementos liberados.\n", cont);
    return NULL;  // Retorna NULL para a nova cabeça
}

#if 0
// Função principal
int main() {
    No* lista = NULL;  // Inicia com lista vazia
    
    printf("=== CRIANDO LISTA ENCADEADA SIMPLES ===\n\n");
    
    // Adicionando elementos no final
    lista = adicionar(lista, 1, "João", 10.5);
    lista = adicionar(lista, 2, "Maria", 20.3);
    lista = adicionar(lista, 3, "Pedro", 15.8);
    lista = adicionar(lista, 4, "Ana", 30.0);
    
    // Acessando do primeiro ao último
    acessarTodos(lista);
    
    // Destruindo a lista
    lista = destruirLista(lista);
    
    // Tentando acessar depois de destruir
    acessarTodos(lista);
    
    return 0;
}

#endif
void print_items(){

 API_PARSE_S items = {"Maycon", 1234};
 printf("items[%s] [%d]\n", items.name, items.id);

}