
#include "structs.h"

int check_date(int day, int month, int year);
int compare_dates(Date date1, Date date2);
int check_name(const char *name);
int check_lote(const char *lote);
int check_date(int day, int month, int year);
void add_lot(const char *lote, Date date, int doses, const char *vaccine_name, VaccineHashTable *vaccine_table, HashTable *lots_table, int portuguese);
void list_lots(VaccineHashTable *vaccine_table, HashTable *lots_table,const char *vaccine_name,int all,int  portuguese);
