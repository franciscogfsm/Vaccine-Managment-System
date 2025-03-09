#ifndef STRUCT_H
#define STRUCT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constants.h"


typedef struct {
    int day;
    int month;
    int year;
} Date;


typedef struct {
    char name[MAX_NAME_LENGTH];
    Date date;
    int doses;
} Vaccine;

typedef struct {
    Vaccine **table;
    int size;
    int count;
} HashTable;



typedef struct Lote {
    char lote[MAX_LOTE_LENGTH];
    struct Lote *next;
} Lote;

typedef struct VaccineEntry {
    char name[MAX_NAME_LENGTH];
    Lote *lotes;
    struct VaccineEntry *next;
} VaccineEntry;

typedef struct {
    VaccineEntry **table;
    int size;
    int count;
} VaccineHashTable;








unsigned int hash(const char *str, int size);
int is_valid_date(int day, int month, int year);
int compare_dates(Date date1, Date date2);
HashTable* create_table(int size);
void resize_table(HashTable *table);
int insert_vaccine(HashTable *table, const char *name, Date date, int doses);
int remove_vaccine(HashTable *table, const char *name);
Vaccine* find_vaccine(HashTable *table, const char *name);
void free_table(HashTable *table);
Lote* find_lotes(VaccineHashTable *table, const char *vaccine_name);


#endif 