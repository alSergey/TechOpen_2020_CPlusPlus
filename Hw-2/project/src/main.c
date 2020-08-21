#include "func.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int choice = 0;

    while (choice != -1) {
        printf("please enter action\n"
            "1 enter data client:\n"
            "2 enter data transaction:\n"
            "3 update base\n\n");

        int errs = scanf("%d", &choice);

        printf("\n");

        if (errs == -1) {
            break;
        }

        switch (choice) {
            case 1: {
                int err = add_new_data(RECORD_FILE, USER_DATA);
                if (err == -1) {
                    fprintf(stderr, "%s: impossible to add data\n", RECORD_FILE);
                }
                break;
            }

            case 2: {
                int err = add_new_data(TRANSATION_FILE, TRANSACTION_DATA);
                if (err == -1) {
                    fprintf(stderr, "%s: impossible to add data\n", TRANSATION_FILE);
                }
                break;
            }

            case 3: {
                int err = black_record(RECORD_FILE, TRANSATION_FILE, BLACKRECORD_FILE);
                if (err == -1) {
                    printf("impossible to black_record\n");
                }
                break;
            }

            default: {
                printf("choose [1..3]\n");
                break;
            }
        }
    }

return 0;
}
