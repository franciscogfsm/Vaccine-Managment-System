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
    if (find_lote(lots_table, lote) != NULL) {
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
                    Vaccine *vaccine = find_lote(lots_table, lotes->lote);
                    if (vaccine != NULL) {
                        printf("%s %s %02d-%02d-%04d %d %d\n", entry->name, lotes->lote, vaccine->date.day, vaccine->date.month, vaccine->date.year, vaccine->doses, vaccine->applications);
                    } 
                    lotes = lotes->next;
                }
                entry = entry->next;
            }
        }
    } else {
        Lote *lotes = find_vaccine(vaccine_table, vaccine_name);
        if (lotes == NULL) {
            if (portuguese) {
                printf("%s: vacina inexistente\n", vaccine_name);
            } else {
                printf("%s: no such vaccine\n", vaccine_name);
            }
            return;
        }
        while (lotes != NULL) {
            Vaccine *vaccine = find_lote(lots_table, lotes->lote);
            if (vaccine != NULL) {
                printf("%s %s %02d-%02d-%04d %d %d\n", vaccine_name, lotes->lote, vaccine->date.day, vaccine->date.month, vaccine->date.year, vaccine->doses, vaccine->applications);
            }
            lotes = lotes->next;
        }
    }
}







void vaccinate(const char *user_name, const char *vaccine_name,VaccineHashTable *vaccine_table, HashTable *lots_table,Date current_date,int portuguese) {
    if (find_vaccine(vaccine_table, vaccine_name) == NULL) {
        if (portuguese) {
            printf("esgotado\n");
        } else {
            printf("no stock\n");
        }
        return;
    }
    find_lote(lots_table, vaccine_name);
    Date date = get_oldest_date(vaccine_table, lots_table, vaccine_name);
    if (compare_dates(date, current_date) == 1||date.day==0) {
        if (portuguese) {
            printf("esgotado\n");
        } else {
            printf("no stock\n");
        }
        return;
    }
    printf("%s %d-%d-%d \n",user_name,date.day,date.month,date.year);
    
    return;
}