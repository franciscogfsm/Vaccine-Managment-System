#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constants.h"
#include "structs.h"
#include "functions.h"

int main(int argc, char *argv[]) {
    char input[BUFSIZE];
    char lote[MAX_LOTE_LENGTH];
    char vaccine_name[MAX_NAME_LENGTH];
    char vaccine_names[BUFSIZE][MAX_NAME_LENGTH];
    char user_name[MAX_NAME_LENGTH];
    int doses;
    int portuguese = 0; // English default
    Date current_date = {1, 1, 2025};
    Date expiration_date = {1, 1, 2025};

    // Create the hashtables
    VaccineHashTable *vaccine_table = create_vaccine_table(INITIAL_SIZE);
    if (vaccine_table == NULL) {
        fprintf(stderr, "Failed to create vaccine table\n");
        return 1;
    }

    HashTable *lots_table = create_table(INITIAL_SIZE);
    if (lots_table == NULL) {
        fprintf(stderr, "Failed to create lots table\n");
        free_vaccine_table(vaccine_table);
        return 1;
    }

    UserHashTable *user_table = create_user_table(INITIAL_SIZE);
    if (user_table == NULL) {
        fprintf(stderr, "Failed to create user table\n");
        free_vaccine_table(vaccine_table);
        free_table(lots_table);
        return 1;
    }

    if (argc > 1 && strcmp(argv[1], "pt") == 0) {
        portuguese = 1;
    }

    while (1) {
        if (fgets(input, BUFSIZE, stdin) == NULL) {
            printf("Erro ao ler a entrada\n");
            continue;
        }

        // Remove o caractere de nova linha, se presente
        input[strcspn(input, "\n")] = 0;

        switch (input[0]) {
            case 'q':
                free_vaccine_table(vaccine_table);
                free_table(lots_table);
                free_user_table(user_table);
                return 0;
            case 'c':
                if (sscanf(input, "c %s %d-%d-%d %d %s", lote, &expiration_date.day, &expiration_date.month, &expiration_date.year, &doses, vaccine_name) == 6) {
                    if (check_date( expiration_date.day, expiration_date.month, expiration_date.year,
                    current_date.day, current_date.month, current_date.year)) {
                        if (portuguese) {
                            printf("data inválida\n");
                        } else {
                            printf("invalid date\n");
                        }
                        
                    }else{
                        add_lot(lote, expiration_date, doses, vaccine_name, vaccine_table, lots_table, portuguese);
                    }
                } 
                break;
            case 'l': {

                if (strlen(input) == 1) {
                    list_lots(vaccine_table, lots_table, NULL, 1,portuguese);
                } else {
                    int num_vaccines = 0;
                    char *token = strtok(input + 2, " ");
                    while (token != NULL && num_vaccines < BUFSIZE) {
                        strncpy(vaccine_names[num_vaccines], token, MAX_NAME_LENGTH);
                        vaccine_names[num_vaccines][MAX_NAME_LENGTH - 1] = '\0'; 
                        num_vaccines++;
                        token = strtok(NULL, " ");
                    }
                    if (num_vaccines > 0) {
                        for (int i = 0; i < num_vaccines; i++) {
                            list_lots(vaccine_table, lots_table, vaccine_names[i], portuguese, 0);
                        }
                    } 
                }
                break;
            }
            case 'a':
                if (sscanf(input, "a %s %s", user_name,vaccine_name) == 2) {
                    vaccinate(user_name,vaccine_name,vaccine_table, lots_table,current_date, portuguese);
                    print_lots_table(lots_table);
                }
                break;
            case 't':
                if (strlen(input) == 1) { // Verifica se o comando é apenas 't'
                    printf("%02d-%02d-%04d\n", current_date.day, current_date.month, current_date.year);
                } else if (sscanf(input, "t %d-%d-%d", &expiration_date.day, &expiration_date.month, &expiration_date.year) == 3) {
                    if (check_date(expiration_date.day, expiration_date.month, expiration_date.year,current_date.day, current_date.month, current_date.year)) {
                        if (portuguese) {
                            printf("data inválida\n");
                        } else {
                            printf("invalid date\n");
                        }
                    } else {
                        current_date = expiration_date;
                        printf("%02d-%02d-%04d\n", current_date.day, current_date.month, current_date.year);
                    }
                }
                break;
            default:
                printf("Comando desconhecido!\n");
                break;
        }
    }
}

//c A0C0 30-7-2025 210 malária
//c A0C1 31-7-2025 210 tosse_convulsa
//c A0C2 29-7-2025 210 malária
//c A0C0 31-7-2025 210 malária
//(nomeutente,nomevacina)