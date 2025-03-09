#include "structs.h"

unsigned int hash(const char *str, int size) {
    unsigned int hash = 0;
    while (*str) {
        hash = (hash * 31) + *str++;
    }
    return hash % size;
}

VaccineHashTable* create_vaccine_table(int size) {
    VaccineHashTable *table = malloc(sizeof(VaccineHashTable));
    if (table == NULL) {
        return NULL; // Falha ao alocar memória
    }
    table->table = malloc(sizeof(VaccineEntry*) * size);
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

void resize_vaccine_table(VaccineHashTable *table) {
    if (table->size >= MAX_SIZE) {
        return;
    }

    int new_size = table->size * 2;
    if (new_size > MAX_SIZE) {
        new_size = MAX_SIZE;
    }

    VaccineEntry **new_table = malloc(sizeof(VaccineEntry*) * new_size);
    if (new_table == NULL) {
        return; // Falha ao alocar memória
    }
    for (int i = 0; i < new_size; i++) {
        new_table[i] = NULL;
    }

    for (int i = 0; i < table->size; i++) {
        VaccineEntry *entry = table->table[i];
        while (entry != NULL) {
            VaccineEntry *next = entry->next;
            unsigned int new_index = hash(entry->name, new_size);
            entry->next = new_table[new_index];
            new_table[new_index] = entry;
            entry = next;
        }
    }

    free(table->table);
    table->table = new_table;
    table->size = new_size;
}

int insert_lote(VaccineHashTable *table, const char *vaccine_name, const char *lote, HashTable *lote_table) {
    if (table->count >= MAX_SIZE) {
        return -1; // Tabela cheia
    }

    if ((float)table->count / table->size >= MAX_LOAD) {
        resize_vaccine_table(table);
    }

    unsigned int index = hash(vaccine_name, table->size);
    VaccineEntry *entry = table->table[index];
    
    while (entry != NULL && strcmp(entry->name, vaccine_name) != 0) {
        entry = entry->next;
    }
    
    if (entry == NULL) {
        entry = malloc(sizeof(VaccineEntry));
        if (entry == NULL) {
            return -1; // Falha ao alocar memória
        }
        strcpy(entry->name, vaccine_name);
        entry->lotes = NULL;
        entry->next = table->table[index];
        table->table[index] = entry;
        table->count++;
    }
    
    Lote *new_lote = malloc(sizeof(Lote));
    if (new_lote == NULL) {
        return -1; // Falha ao alocar memória
    }
    strcpy(new_lote->lote, lote);
    new_lote->next = NULL;

    // Inserir o lote na lista ordenada por data
    Lote **current = &entry->lotes;
    while (*current != NULL) {
        Vaccine *details_current = find_vaccine(lote_table, (*current)->lote);
        Vaccine *details_new = find_vaccine(lote_table, lote);
        if (details_current != NULL && details_new != NULL) {
            Date date_current = details_current->date;
            Date date_new = details_new->date;
            if (compare_dates(date_current, date_new) > 0) {
                break;
            }
        }
        current = &(*current)->next;
    }
    new_lote->next = *current;
    *current = new_lote;

    return 0; // Sucesso
}

Lote* find_lotes(VaccineHashTable *table, const char *vaccine_name) {
    unsigned int index = hash(vaccine_name, table->size);
    VaccineEntry *entry = table->table[index];
    
    while (entry != NULL && strcmp(entry->name, vaccine_name) != 0) {
        entry = entry->next;
    }
    
    if (entry == NULL) {
        return NULL; // Não encontrado
    }
    
    return entry->lotes; // Encontrado

}

void free_vaccine_table(VaccineHashTable *table) {
    for (int i = 0; i < table->size; i++) {
        VaccineEntry *entry = table->table[i];
        while (entry != NULL) {
            VaccineEntry *next_entry = entry->next;
            Lote *lote = entry->lotes;
            while (lote != NULL) {
                Lote *next_lote = lote->next;
                free(lote);
                lote = next_lote;
            }
            free(entry);
            entry = next_entry;
        }
    }
    free(table->table);
    free(table);
}