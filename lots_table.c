#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constants.h"
#include "structs.h"


HashTable* create_table(int size) {
    HashTable *table = malloc(sizeof(HashTable));
    if (table == NULL) {
        return NULL; // Falha ao alocar memória
    }
    table->table = malloc(sizeof(Vaccine*) * size);
    if (table->table == NULL) {
        free(table);
        return NULL; // Falha ao alocar memória
    }
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

    int new_size = table->size * 2;
    if (new_size > MAX_SIZE) {
        new_size = MAX_SIZE;
    }

    Vaccine **new_table = malloc(sizeof(Vaccine*) * new_size);
    if (new_table == NULL) {
        return; // Falha ao alocar memória
    }
    for (int i = 0; i < new_size; i++) {
        new_table[i] = NULL;
    }

    for (int i = 0; i < table->size; i++) {
        Vaccine *entry = table->table[i];
        while (entry != NULL) {
            Vaccine *next = entry->next;
            unsigned int new_index = hash(entry->lote, new_size);
            entry->next = new_table[new_index];
            new_table[new_index] = entry;
            entry = next;
        }
    }

    free(table->table);
    table->table = new_table;
    table->size = new_size;
}

int insert_vaccine(HashTable *table, const char *lote, Date date, int doses, const char *name) {
    if (table->count >= MAX_SIZE) {
        return -1; // Tabela cheia
    }

    if ((float)table->count / table->size >= MAX_LOAD) {
        resize_table(table);
    }

    unsigned int index = hash(lote, table->size);
    Vaccine *entry = table->table[index];
    while (entry != NULL) {
        if (strcmp(entry->lote, lote) == 0) {
            return -1; // Lote já existente
        }
        entry = entry->next;
    }

    entry = malloc(sizeof(Vaccine));
    if (entry == NULL) {
        return -1; // Falha ao alocar memória
    }
    strcpy(entry->lote, lote);
    entry->date = date;
    entry->doses = doses;
    entry->applications = 0; // Inicializa o número de aplicações como 0
    strcpy(entry->name, name); // Armazena o nome da vacina
    entry->next = table->table[index];
    table->table[index] = entry;
    table->count++;

    return 0; // Sucesso
}

int remove_vaccine(HashTable *table, const char *lote) {
    unsigned int index = hash(lote, table->size);
    Vaccine *entry = table->table[index];
    Vaccine *prev = NULL;

    while (entry != NULL && strcmp(entry->lote, lote) != 0) {
        prev = entry;
        entry = entry->next;
    }

    if (entry == NULL) {
        return 1; // Não encontrado
    }

    if (prev == NULL) {
        table->table[index] = entry->next;
    } else {
        prev->next = entry->next;
    }

    free(entry);
    table->count--;

    return 0; // Sucesso
}

Vaccine* find_lote(HashTable *table, const char *lote) {
    unsigned int index = hash(lote, table->size);
    Vaccine *entry = table->table[index];
    while (entry != NULL && strcmp(entry->lote, lote) != 0) {
        entry = entry->next;
    }
    return entry; // Retorna NULL se não encontrado
}

void free_table(HashTable *table) {
    for (int i = 0; i < table->size; i++) {
        Vaccine *entry = table->table[i];
        while (entry != NULL) {
            Vaccine *next = entry->next;
            free(entry);
            entry = next;
        }
    }
    free(table->table);
    free(table);
}

int get_number_of_lots(HashTable *table) {
    return table->count;
}

void print_lots_table(HashTable *table) {
    for (int i = 0; i < table->size; i++) {
        Vaccine *entry = table->table[i];
        while (entry != NULL) {
            printf("Index %d:\n", i);
            printf("Lote: %s, Data: %02d-%02d-%04d, Doses: %d, Nome: %s, Aplicações: %d\n", entry->lote, entry->date.day, entry->date.month, entry->date.year, entry->doses, entry->name, entry->applications);
            entry = entry->next;
        }
    }
}