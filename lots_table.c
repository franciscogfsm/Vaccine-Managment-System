#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constants.h"
#include "structs.h"

unsigned int hash(const char *str, int size) {
    unsigned int hash = 0;
    while (*str) {
        hash = (hash * 31) + *str++;
    }
    return hash % size;
}

HashTable* create_table(int size) {
    HashTable *table = malloc(sizeof(HashTable));
    table->table = malloc(sizeof(Vaccine*) * size);
    for (int i = 0; i < size; i++) {
        table->table[i] = NULL;
    }
    table->size = size;
    table->count = 0;
    return table;
}

void resize_table(HashTable *table) {
    if (table->size >= MAX_SIZE) {
        return;
    }
    // Duplica o tamanho da tabela
    int new_size = table->size * 2;
    if (new_size > MAX_SIZE) {
        new_size = MAX_SIZE;
    }

    Vaccine **new_table = malloc(sizeof(Vaccine*) * new_size);
    for (int i = 0; i < new_size; i++) {
        new_table[i] = NULL;
    }

    for (int i = 0; i < table->size; i++) {
        if (table->table[i] != NULL) {
            unsigned int new_index = hash(table->table[i]->name, new_size);
            new_table[new_index] = table->table[i];
        }
    }

    free(table->table);
    table->table = new_table;
    table->size = new_size;
}

int insert_vaccine(HashTable *table, const char *name, Date date, int doses) {
    if (table->count >= MAX_SIZE) {
        return -1; // Tabela cheia
    }

    if ((float)table->count / table->size >= MAX_LOAD) {
        resize_table(table);
    }

    unsigned int index = hash(name, table->size);
    if (table->table[index] != NULL) {
        return -1; // Lote já existente
    }

    Vaccine *entry = malloc(sizeof(Vaccine));
    if (entry == NULL) {
        return -1; // Falha ao alocar memória
    }
    strcpy(entry->name, name);
    entry->date = date;
    entry->doses = doses;
    table->table[index] = entry;
    table->count++;

    return 0; // Sucesso
}

int remove_vaccine(HashTable *table, const char *name) {
    unsigned int index = hash(name, table->size);
    if (table->table[index] == NULL) {
        return 1; // Não encontrado
    }

    free(table->table[index]);
    table->table[index] = NULL;
    table->count--;

    return 0; // Sucesso
}

Vaccine* find_vaccine(HashTable *table, const char *name) {
    unsigned int index = hash(name, table->size);
    if (table->table[index] == NULL) {
        return NULL; // Não encontrado
    }

    return table->table[index]; // Encontrado
}

void free_table(HashTable *table) {
    for (int i = 0; i < table->size; i++) {
        if (table->table[i] != NULL) {
            free(table->table[i]);
        }
    }
    free(table->table);
    free(table);
}

int get_number_of_lots(HashTable *table) {
    return table->count;
}