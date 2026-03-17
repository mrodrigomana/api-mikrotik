#include <stdio.h>
#include <string.h>
#include "librouteros.h"
#include "parse_items.h"


void send_command( struct ros_connection *conn, char * command){
    
    struct ros_result *res;
    ros_send_command(conn, command, NULL);

    // Lê TODAS as sentenças até o !done
    int entrada = 0;

    while (1) {
        res = ros_read_packet(conn);  // Lê uma sentença
        
        if (!res) break;
        
        // Verifica o que veio
        if (res->re) {
            entrada++;
            printf("\nEntrada retorno %d:\n", entrada);
            for (int i = 1; i < res->sentence->words; i++) {
                if (res->sentence->word[i][0] == '=') {
                    printf("  %s\n", res->sentence->word[i]);
                }
            }
        }
        else if (res->done) {
            printf("\nTotal de retorno: %d\n", entrada);
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
    

    char *host = "192.168.88.254";
    char *user = "admin";
    char *pass = "#Legiurba45231565";

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

    printf("\033[30;32;6mConectado com sucesso ao MikroTik!\033[m\n");

    printf("\n=== Tabela mangle ===\n");
    send_command(conn, "/ip/firewall/mangle/print");
    // Envia o comando
    printf("\n=== System Identity ===\n");
    send_command(conn, "/system/identity/print");

    // Envia o comando
    printf("\n=== ARP table ===\n");
    send_command(conn, "/ip/arp/print");

    ros_disconnect(conn);
    print_items();
    return 0;
}