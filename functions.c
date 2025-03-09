#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constants.h"
#include "structs.h"



int check_date(int day, int month, int year, int current_day, int current_month, int current_year) {
    // Check if month is valid
    if (month < 1 || month > 12) {
        return 1;
    }

    // Array with the number of days in each month
    int days_in_month[] = {
        31, // Janeiro
        (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) ? 29 : 28, 
        // Fevereiro verifiar ano bisexto
        31, // Março
        30, // Abril
        31, 
        30, 
        31, 
        31, 
        30, 
        31, 
        30, 
        31  
    };

    
    if (day < 1 || day > days_in_month[month - 1]) {
        return 1;
    }

    // Verificar se a data é antes de 01-01-2025
    Date current_date = {current_day, current_month, current_year};
    Date input_date = {day, month, year};
    if (compare_dates(input_date, current_date) == 1) {
        return 1;
    }

    return 0; // Date is valid
}

// Returns 0 if date1 is equal to or greater than date2, otherwise returns 1
int compare_dates(Date date1, Date date2) {
    if (date1.year > date2.year) {
        return 0;
    }
    if (date1.year < date2.year) {
        return 1;
    }
    if (date1.month > date2.month) {
        return 0;
    }
    if (date1.month < date2.month) {
        return 1;
    }
    if (date1.day >= date2.day) {
        return 0;
    }

    return 1; // date1 is less than date2
}

int check_lote(const char *lote) {
    if (strlen(lote) > MAX_LOTE_LENGTH) {
        return 1;
    }
    // Verifica se todos os caracteres são dígitos hexadecimais maiúsculos
    for (size_t i = 0; i < strlen(lote); i++) {
        if (!((lote[i] >= '0' && lote[i] <= '9') || (lote[i] >= 'A' && lote[i] <= 'F'))) {
            return 1;
        }
    }
    return 0;
}


int check_name(const char *name) {
    if (strlen(name) > MAX_NAME_LENGTH) {
        return 1;
    }
    return 0;
}