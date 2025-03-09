#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constants.h"
#include "structs.h"
#include "functions.h"


void add_lot(const char *lote, Date date, int doses, const char *vaccine_name, VaccineHashTable *vaccine_table, HashTable *lots_table, int portuguese) {
    if (get_number_of_lots(lots_table) >= MAX_SIZE) {
        if (portuguese) {
            printf("demasiadas vacinas\n");
        } else {
            printf("too many vaccines\n");
        }
        return;
    }
    if (find_vaccine(lots_table, lote) != NULL) {
        if (portuguese) {
            printf("número de lote duplicado\n");
        } else {
            printf("duplicate batch number\n");
        }
        return;
    }
    if (check_lote(lote) == 1) {
        if (portuguese) {
            printf("lote inválido\n");
        } else {
            printf("invalid batch\n");
        }
        return;
    }
    if (check_name(vaccine_name) == 1) {
        if (portuguese) {
            printf("nome inválido\n");
        } else {
            printf("invalid name\n");
        }
        return;

    }
    if (doses < 1){
        if (portuguese) {
            printf("quantidade inválida\n");
        } else {
            printf("invalid quantity\n");
        }
        return;
    }
    
    insert_vaccine(lots_table, lote, date, doses,vaccine_name);
    insert_lote(vaccine_table, vaccine_name, lote, lots_table);
    printf("%s\n",lote);

}


void list_lots(VaccineHashTable *vaccine_table, HashTable *lots_table, const char *vaccine_name, int print_all, int portuguese) {
    if (print_all) {
        for (int i = 0; i < vaccine_table->size; i++) {
            VaccineEntry *entry = vaccine_table->table[i];
            if (entry == NULL) continue;  
    
            while (entry != NULL) {
                Lote *lotes = entry->lotes;
                if (lotes == NULL) continue; 
    
                while (lotes != NULL) {
                    Vaccine *vaccine = find_vaccine(lots_table, lotes->lote);
                    if (vaccine != NULL) {
                        printf("%s %s %02d-%02d-%04d %d %d\n", entry->name, lotes->lote, vaccine->date.day, vaccine->date.month, vaccine->date.year, vaccine->doses, vaccine->applications);
                    } 
                    lotes = lotes->next;
                }
                entry = entry->next;
            }
        }
    } else {
        Lote *lotes = find_lotes(vaccine_table, vaccine_name);
        if (lotes == NULL) {
            if (portuguese) {
                printf("%s: vacina inexistente\n", vaccine_name);
            } else {
                printf("%s: no such vaccine\n", vaccine_name);
            }
            return;
        }

        printf("%s:\n", vaccine_name);

        // Cria uma lista de lotes para ordenação
        Lote *sorted_lotes = NULL;
        while (lotes != NULL) {
            Lote *new_lote = malloc(sizeof(Lote));
            if (new_lote == NULL) {
                fprintf(stderr, "Erro ao alocar memória\n");
                return;
            }
            strcpy(new_lote->lote, lotes->lote);
            new_lote->next = NULL;

            // Insere o lote na lista ordenada
            Lote **current = &sorted_lotes;
            while (*current != NULL) {
                Vaccine *details_current = find_vaccine(lots_table, (*current)->lote);
                Vaccine *details_new = find_vaccine(lots_table, new_lote->lote);
                if (details_current != NULL && details_new != NULL) {
                    Date date_current = details_current->date;
                    Date date_new = details_new->date;
                    if (compare_dates(date_current, date_new) > 0 || 
                        (compare_dates(date_current, date_new) == 0 && strcmp((*current)->lote, new_lote->lote) > 0)) {
                        break;
                    }
                }
                current = &(*current)->next;
            }
            new_lote->next = *current;
            *current = new_lote;

            lotes = lotes->next;
        }

        // Imprime a lista ordenada de lotes
        while (sorted_lotes != NULL) {
            Vaccine *vaccine = find_vaccine(lots_table, sorted_lotes->lote);
            if (vaccine != NULL) {
                printf("%s %s %02d-%02d-%04d %d %d\n", vaccine_name, sorted_lotes->lote, vaccine->date.day, vaccine->date.month, vaccine->date.year, vaccine->doses, vaccine->applications);
            }
            Lote *temp = sorted_lotes;
            sorted_lotes = sorted_lotes->next;
            free(temp);
        }
    }
}