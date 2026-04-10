#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "librouteros.h"
#include "parse_items.h"
#include "options.h"

//Possível usar curl
//curl -k -u admin:admin http://192.168.0.254/rest/ip/firewall/nat


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
            
            // Aloca espaço para os retornos (+1 para o ID)
            dado_atual.total = num_itens + 1;
            dado_atual.retorno = (char**)malloc(dado_atual.total * sizeof(char*));
            
            if (!dado_atual.retorno) {
                printf("Erro ao alocar memória\n");
                ros_result_free(res);
                break;
            }
            
            // Adiciona o campo ID no início
            char id_buffer[32];
            snprintf(id_buffer, sizeof(id_buffer), "=ID=%d", entrada);
            dado_atual.retorno[0] = (char*)malloc((strlen(id_buffer) + 1) * sizeof(char));
            if (dado_atual.retorno[0]) {
                strcpy(dado_atual.retorno[0], id_buffer);
                if(DEBUG)
                    printf("\033[30;42;6m[DADOS ANTES DE INSERIR NA LISTA]:\033[m{%s}\n", id_buffer);
            }
            
            // Preenche os dados originais a partir do índice 1
            int idx = 1;
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
            if(DEBUG)
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
int main(int argc, char** argv) {


        Config config;
    
    // Parse das opções
    parse_options(argc, argv, &config);
    
    // Verifica se pediu ajuda
    if (config.help) {
        print_help(argv[0]);
        free_config(&config);
        return 0;
    }

    int port = 0;

    struct ros_connection *conn;
    
    port = atoi( config.port);
    conn = ros_connect(config.host,port);
    if (!conn) {
        printf("Erro ao conectar\n");
        return 1;
    }
    
    if (!ros_login(conn,config.user,config.password)) {
        printf("Erro no login\n");
        ros_disconnect(conn);
        return 1;
    }
    if(DEBUG)
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

    if(DEBUG)
        printf("\n=== IMPRIMINDO TODOS OS RESULTADOS FILTER ===\n");
    send_command(conn, config.commands, &lista);

    imprimir_lista(lista);
    if(DEBUG){
        printf("\n=== PRIMEIRO RESULTADO FILTER === lista->info.total[%d]\n", lista->info.total);
        imprimir_dado_especifico(lista, 0, 1);
    }

    liberar_lista(&lista);

    printf("%s", ros_disconnect(conn) ? "Desconexão mal sucedida!!\n" : "Desconectado com sucesso!!\n");

    return 0;
}



