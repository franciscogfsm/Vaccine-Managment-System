#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "structs.h"
int compare_dates(Date date1, Date date2);
int check_date(int day, int month, int year,int current_day, int current_month, int current_year);
int check_name(const char *name);
int check_lote(const char *lote);
void add_lot(const char *lote, Date date, int doses, const char *vaccine_name, VaccineHashTable *vaccine_table, HashTable *lots_table, int portuguese);
void list_lots(VaccineHashTable *vaccine_table, HashTable *lots_table,const char *vaccine_name,int all,int  portuguese);
void vaccinate(const char *user_name, const char *vaccine_name,VaccineHashTable *vaccine_table, HashTable *lots_table,Date current_date,int  portuguese);

#endif // FUNCTIONS_H