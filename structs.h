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

// Estruturas para a tabela de lotes
typedef struct Vaccine {
    char lote[MAX_LOTE_LENGTH];
    char name[MAX_NAME_LENGTH];
    Date date;
    int doses;
    int applications; // Número de aplicações
    struct Vaccine *next; // Ponteiro para o próximo lote (para lidar com colisões)
} Vaccine;

typedef struct {
    Vaccine **table;
    int size;
    int count;
} HashTable;


// Estruturas para a tabela de vacinas
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





// Estrutura de aplicação
typedef struct Application {
    char lote[MAX_LOTE_LENGTH]; // Lote da vacina
    char vaccine_name[MAX_NAME_LENGTH]; // Nome da vacina
    Date date;                  // Data da aplicação
    struct Application *next;   // Próxima aplicação
} Application;

// Estrutura de utente
typedef struct User {
    char name[MAX_NAME_LENGTH];  // Nome do utente
    Application *applications;   // Lista de aplicações (lote e data)
    struct User *next;           // Próximo utente na tabela
} User;

// Estrutura de tabela de hash de utentes
typedef struct {
    User **table;  // Tabela de hash (lista de utentes)
    int size;      // Tamanho da tabela
    int count;     // Número de utentes cadastrados
} UserHashTable;




void print_lots_table(HashTable *table);
void print_vaccine_table(VaccineHashTable *table);
VaccineHashTable* create_vaccine_table(int size);
unsigned int hash(const char *str, int size);
int is_valid_date(int day, int month, int year);
int compare_dates(Date date1, Date date2);
HashTable* create_table(int size);
void resize_table(HashTable *table);
int insert_vaccine(HashTable *table, const char *lote, Date date, int doses, const char *name);
int remove_vaccine(HashTable *table, const char *name);
Vaccine* find_lote(HashTable *table, const char *lote);
void free_table(HashTable *table);
Lote* find_vaccine(VaccineHashTable *table, const char *vaccine_name);
int get_number_of_lots(HashTable *table);
int insert_lote(VaccineHashTable *table, const char *vaccine_name, const char *lote, HashTable *lote_table);
void free_vaccine_table(VaccineHashTable *table);


UserHashTable* create_user_table(int size);
User* find_user(UserHashTable *table, const char *name);
void free_user_table(UserHashTable *table);
void print_user_table(UserHashTable *table);
void resize_user_table(UserHashTable *table);
int insert_user(UserHashTable *table, const char *name) ;
int remove_user(UserHashTable *table, const char *name);
int add_application(UserHashTable *user_table, const char *user_name, 
    const char *vaccine_name, Date date, const char *lote);


Date get_oldest_date(VaccineHashTable *table,HashTable *lots_table, const char *vaccine_name);






#endif 