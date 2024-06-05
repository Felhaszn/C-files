#include <stdio.h>
#include <time.h>
#include <stdbool.h>

#include "rsa.h"
#include "menu.h"
#include "account.h"
#include "debugmalloc.h"
#include "card.h"
#include "transfer.h"

int main() {
    printf("%d\n", 378049 % 7);
    int coded = C(123, e());
    printf("%d", coded);
    int decoded = Decode(coded);
    /*
    bool done = false;
    bool progdone = false;

    while (progdone == false) {
        while (done == false) {
            switch (login_menu()) {
            case 1:
                if (lines() == 0) {
                    printf("Elobb hozz letre szamlat!");
                }
                else {
                    if (accLogin() == true) {
                        done = true;
                        break;
                    }
                    else {
                        printf("Nem megfelelo enazonosito!");
                        break;
                    }
                }

            case 2:
                accCreate(N(p(), q()), e());
                break;
            case 0:
                progdone = true;
                return 0;
                break;
            default:
                printf("Nem megfelelo valasz!");
                break;
            }
        }

        done = false;

        while (done == false) {
            switch (main_menu()) {
            case 1:
                transfering();
                break;
            case 2:
                readCard();
                break;
            case 3:
                readTransfering();
                break;
            case 4:
                printf("A szamlaszamod: %d", accRead());
                break;
            case 5:
                changeID();
                break;
            case 6:
                createCard();
                break;
            case 0:
                done = true;
                break;
            default:
                printf("Nem megfelelo valasz!");
                break;
            }
        }

        done = false;
    }
    */
    return 0;
}