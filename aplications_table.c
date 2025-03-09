#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constants.h"
#include "structs.h"

UserHashTable* create_user_table(int size) {
    UserHashTable *table = malloc(sizeof(UserHashTable));
    table->table = malloc(sizeof(User*) * size);
    for (int i = 0; i < size; i++) {
        table->table[i] = NULL;
    }
    table->size = size;
    table->count = 0;
    return table;
}




void resize_user_table(UserHashTable *table) {
    if (table->size >= MAX_SIZE) {
        return;
    }
    int new_size = table->size * 2;
    if (new_size > MAX_SIZE) {
        new_size = MAX_SIZE;
    }

    User **new_table = malloc(sizeof(User*) * new_size);
    for (int i = 0; i < new_size; i++) {
        new_table[i] = NULL;
    }

    for (int i = 0; i < table->size; i++) {
        User *user = table->table[i];
        while (user != NULL) {
            User *next_user = user->next;
            unsigned int new_index = hash(user->name, new_size);
            user->next = new_table[new_index];
            new_table[new_index] = user;
            user = next_user;
        }
    }

    free(table->table);
    table->table = new_table;
    table->size = new_size;
}


int insert_user(UserHashTable *table, const char *name) {
    if (table->count >= MAX_SIZE) {
        return -1; // Tabela cheia
    }

    if ((float)table->count / table->size >= MAX_LOAD) {
        resize_user_table(table);
    }

    unsigned int index = hash(name, table->size);
    User *user = malloc(sizeof(User));
    if (user == NULL) {
        return -1; // Falha ao alocar memória
    }
    strcpy(user->name, name);
    user->applications = NULL;
    user->next = table->table[index];
    table->table[index] = user;
    table->count++;

    return 0; // Sucesso
}


int remove_user(UserHashTable *table, const char *name) {
    unsigned int index = hash(name, table->size);
    User *user = table->table[index];
    User *prev_user = NULL;

    while (user != NULL && strcmp(user->name, name) != 0) {
        prev_user = user;
        user = user->next;
    }

    if (user == NULL) {
        return 1; // Não encontrado
    }

    if (prev_user == NULL) {
        table->table[index] = user->next;
    } else {
        prev_user->next = user->next;
    }

    // Libera a memória das aplicações
    Application *app = user->applications;
    while (app != NULL) {
        Application *next_app = app->next;
        free(app);
        app = next_app;
    }

    free(user);
    table->count--;

    return 0; // Sucesso
}


User* find_user(UserHashTable *table, const char *name) {
    unsigned int index = hash(name, table->size);
    User *user = table->table[index];
    while (user != NULL && strcmp(user->name, name) != 0) {
        user = user->next;
    }
    return user; // Retorna NULL se não encontrado
}


void free_user_table(UserHashTable *table) {
    for (int i = 0; i < table->size; i++) {
        User *user = table->table[i];
        while (user != NULL) {
            User *next_user = user->next;
            // Libera a memória das aplicações
            Application *app = user->applications;
            while (app != NULL) {
                Application *next_app = app->next;
                free(app);
                app = next_app;
            }
            free(user);
            user = next_user;
        }
    }
    free(table->table);
    free(table);
}

void print_user_table(UserHashTable *table) {
    for (int i = 0; i < table->size; i++) {
        User *user = table->table[i];
        if (user != NULL) {
            printf("Index %d:\n", i);
            while (user != NULL) {
                printf("  Utente: %s\n", user->name);
                Application *app = user->applications;
                while (app != NULL) {
                    printf("    Aplicação: Lote %s, Data %02d-%02d-%04d\n", app->lote, app->date.day, app->date.month, app->date.year);
                    app = app->next;
                }
                user = user->next;
            }
        }
    }
}