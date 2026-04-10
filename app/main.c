#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "librouteros.h"
#include "parse_items.h"

//Possível usar curl
//curl -k -u admin:admin http://192.168.0.254/rest/ip/firewall/nat

#define DEBUG 0

void send_command(struct ros_connection *conn, char *command, No** lista_resultados) {
    
    struct ros_result *res;
    ros_send_command(conn, command, NULL);
    
    int entrada = 0;
    DATA dado_atual;
    
    while (1) {
        res = ros_read_packet(conn);
        if (!res) break;
        
        // Verifica o que veio
        if (res->re) {
            entrada++;
            
            // Conta quantos itens tem neste retorno (campos com '=')
            int num_itens = 0;
            for (int i = 1; i < res->sentence->words; i++) {
                if (res->sentence->word[i][0] == '=') {
                    num_itens++;
                }
            }
            
            // Aloca espaço para os retornos
            dado_atual.total = num_itens;
            dado_atual.retorno = (char**)malloc(num_itens * sizeof(char*));
            
            if (!dado_atual.retorno) {
                printf("Erro ao alocar memória\n");
                ros_result_free(res);
                break;
            }
            
            // Preenche os dados
            int idx = 0;
            for (int i = 1; i < res->sentence->words; i++) {
                if (res->sentence->word[i][0] == '=') {
                    // Aloca e copia a string (pula o '=' inicial)
                    dado_atual.retorno[idx] = (char*)malloc((strlen(res->sentence->word[i]) + 1) * sizeof(char));
                    if (dado_atual.retorno[idx]) {
                        strcpy(dado_atual.retorno[idx], res->sentence->word[i]);
                        if(DEBUG)
                            printf("\033[30;42;6m[DADOS ANTES DE INSERIR NA LISTA]:\033[m{%s}\n", res->sentence->word[i]);
                    }
                    idx++;
                }
            }
            
            // Adiciona o dado à lista
            adicionar_no(lista_resultados, dado_atual);
            if(DEBUG)
                printf("\n");
            
            // Libera a memória temporária
            for (int i = 0; i < dado_atual.total; i++) {
                free(dado_atual.retorno[i]);
            }
            free(dado_atual.retorno);
        }
        else if (res->done) {
            printf("Total de entradas processadas: %d\n", entrada);
            ros_result_free(res);
            break;
        }
        else {
            // !trap ou !fatal
            printf("Erro: %s\n", res->sentence->word[0]);
        }
        
        ros_result_free(res);
    }
}
int main() {
    struct ros_connection *conn;
    

    char *host = "192.168.0.254";
    char *user = "admin";
    char *pass = "admin";

    conn = ros_connect(host, 8728);
    if (!conn) {
        printf("Erro ao conectar\n");
        return 1;
    }
    
    if (!ros_login(conn, user, pass)) {
        printf("Erro no login\n");
        ros_disconnect(conn);
        return 1;
    }

    printf("\033[30;42;1mConectado com sucesso ao MikroTik!\033[m\n");



    No* lista = NULL;  // Inicializa a lista vazia
    
    // Exemplo: pegar lista ARP
    //send_command(conn, "/ip/arp/print", &lista);
        
    // Imprime todos os resultados armazenados
    //printf("\n=== IMPRIMINDO TODOS OS RESULTADOS ARP ===\n");

    //imprimir_lista(lista);
    
    // Ou imprime um resultado específico (ex: o primeiro)
    //printf("\n=== PRIMEIRO RESULTADO ARP===\n");
    //imprimir_dado_especifico(lista, 0);
    
    // Libera a memória no final
    //liberar_lista(&lista);

    printf("\n=== IMPRIMINDO TODOS OS RESULTADOS FILTER ===\n");
    send_command(conn, "/ip/firewall/nat/print", &lista);

    imprimir_lista(lista);
    printf("\n=== PRIMEIRO RESULTADO FILTER ===\n");
    imprimir_dado_especifico(lista, 0);

    liberar_lista(&lista);

    printf("%s", ros_disconnect(conn) ? "Desconexão mal sucedida!!\n" : "Desconectado com sucesso!!\n");

    return 0;
}



