#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "options.h"

void parse_options(int argc, char *argv[], Config *config)
{
    int opt;

    // Inicializa a estrutura com valores padrão
    config->user = NULL;
    config->password = NULL;
    config->host = NULL;
    config->port = NULL;
    config->commands = NULL;
    config->help = 0;

    // Processa as opções usando getopt
    while ((opt = getopt(argc, argv, "u:s:i:p:c:h")) != -1)
    {
        switch (opt)
        {
        case 'u':
            config->user = strdup(optarg);
            break;
        case 's':
            config->password = strdup(optarg);
            break;
        case 'i':
            config->host = strdup(optarg);
            break;
        case 'p':
            config->port = strdup(optarg);
            break;
        case 'c':
            config->commands = strdup(optarg);
            break;
        case 'h':
            config->help = 1;
            break;
        case '?':
            // Opção desconhecida
            fprintf(stderr, "Opção inválida. Use -h para ajuda.\n");
            break;
        }
    }

    // Define porta padrão se não foi informada
    if (!config->user) {
        config->user = strdup("admin");
    }

    if (!config->password) {
        config->password = strdup("admin");
    }

    if (!config->host) {
        config->host = strdup("192.168.0.254");
    }

    if (!config->port) {
        config->port = strdup("8728");
    }

    if (!config->commands) {
        config->commands = strdup("/system/identity/print");
    }
}

void free_config(Config *config)
{
    if (config->user)
        free(config->user);
    if (config->password)
        free(config->password);
    if (config->host)
        free(config->host);
    if (config->port)
        free(config->port);
    if (config->commands)
        free(config->commands);
}

void print_help(const char *program_name)
{
    printf("Uso: %s [opções]\n", program_name);
    printf("\nOpções:\n");
    printf("  -u USUARIO     Nome do usuário do MikroTik\n");
    printf("  -s SENHA       Senha do usuário do MikroTik\n");
    printf("  -i IP          Endereço IP do MikroTik\n");
    printf("  -p PORTA       Porta da API (padrão: 8728)\n");
    printf("  -c COMANDOS    Comandos a serem executados (separados por ponto e vírgula)\n");
    printf("  -h             Mostra esta ajuda\n");
    printf("\nExemplos:\n");
    printf("  %s -u admin -s minhasenha -i 192.168.88.1 -c \"/ip/firewall/nat/print\"\n", program_name);
    printf("  %s -u admin -s senha123 -i 10.0.0.1 -p 8728 -c \"/ip/firewall/nat/print;/ip/arp/print\"\n", program_name);
    printf("\nNota: Múltiplos comandos devem ser passados entre aspas e separados por ponto e vírgula.\n");
}