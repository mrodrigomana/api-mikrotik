#ifndef OPTIONS_H
#define OPTIONS_H

typedef struct {
    char *user;
    char *password;
    char *host;
    char *port;
    char *commands;
    int help;
} Config;

// Protótipos das funções
void parse_options(int argc, char *argv[], Config *config);
void free_config(Config *config);
void print_help(const char *program_name);

#endif