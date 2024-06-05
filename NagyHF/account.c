#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#include "menu.h"
#include "rsa.h"
#include "debugmalloc.h"

typedef struct account {
    int ID;
    int num;
    int pin;
    int e;
    struct account* next;
}account;

int lines() {
	FILE* f;
	f = fopen("account.txt", "a");
    fclose(f);
    f = fopen("account.txt", "r");

	int c, line = 0;
	do {                                                //Megszámolja a sortöréseket, ebből következtet a számlára
		c = fgetc(f);
		if (c == '\n') {
			line += 1;
		}
	} while (c != EOF);

	fclose(f);

	return line;
}

/*Létrehoz egy számlát*/
void accCreate(int N, int e) {
    FILE* f;
    
    //f = fopen("account.txt", "w");                      //Létrehoz egy fájlt, ha még nincs
    //fclose(f);

    account* szamla;                                     //Dinamikus tömb létrehozása a számlaadatok tárolására
    szamla = (account*)malloc(1 * sizeof(account));

    int ID = 0;
    printf("\nEnazonosito(6 karakterbol allo szam): ");         //ID létrehozása
    if (scanf("%d", &ID) > 100000) {
        printf("%d", ID);
    }

    srand(time(0));
    int epin = rand() % 9999;                            //Random ePIN kód létrehozása
    if (epin < 1000) {
        epin += 1000;
    }

    f = fopen("account.txt", "a");                       //Fájl megnyitása

    if (f == NULL) {
        printf("\nNem lehetett megnyitni a fajlt.");
        return;
    }

    szamla->ID = C(ID);
    szamla->num = N;
    szamla->pin = C(epin);
    szamla->e = e;

    //rewind(f);  
    fprintf(f, "%d,%d,%d,%d\n", szamla->ID, szamla->num, szamla->pin, szamla->e);                      //Fájlba írás
    
    fclose(f);                                              //Fájl bezárása

    free(szamla);                                     //Tömb felszabadítása

    printf("Az ePIN kodod: %d", epin);
    printf("\nA szamlaszamod a kovetkezo: %d", N);
}

/*Beolvassa a számlát*/
int accRead() {
    FILE* f;
    
    f = fopen("account.txt", "r");

    if (f == NULL) {                                           //Fájl megnyitása, ellenőrzés
        printf("\nNem lehetett megnyitni a fajlt.");
        return -1;
    }

    if (lines() == 0) {                                    //Ha a sortörések száma 0, akkor nincs számla
        printf("Meg nem hoztal letre szamlat! ");
        fclose(f);
        return -1;
    }

    account szamla;                                        //Számlaadatok tárolása
    //szamla = (account*)malloc(lines() * sizeof(account));

    //rewind(f);
    fscanf(f, "%d,%d,%d,%d", &szamla.ID, &szamla.num, &szamla.pin, &szamla.e);          //Fájl beolvasása
    
    fclose(f);

    int szamlaszam = szamla.num;

    //free(szamla);                                       //Tömb felszabadítása

    return szamlaszam;
}

//Bejelentkezés a számlába
bool accLogin() {
    FILE* f;

    f = fopen("account.txt", "r");

    if (f == NULL) {                                           //Fájl megnyitása, ellenőrzés
        printf("\nNem lehetett megnyitni a fajlt.");
        return -1;
    }

    int l = lines();
    
    account new_element;        //info nevű lista (egyelőre nullptr) és new_element létrehozása
    account* info = NULL;

    //fájlból a listába írás
    while (fscanf(f, "%d,%d,%d,%d\n", &new_element.ID, &new_element.num, &new_element.pin, &new_element.e) != EOF) {
        new_element.ID = Decode(new_element.ID);

        account* uj;
        uj = (account*)malloc(sizeof(account));
        uj->ID = new_element.ID;
        uj->e = new_element.e;
        uj->num = new_element.num;
        uj->pin = new_element.pin;
        uj->next = NULL;                        //értékek átadása

        if (info == NULL) {
            info = uj;                          //ha nullptr, akkor az elsőt ide szúrja be
        }
        else {
            account* mozgo = info;              //ha nem, akkor hozzáfűzi
            while (mozgo->next != NULL) {
                mozgo = mozgo->next;
            }
            mozgo->next = uj;
        }
    }

    fclose(f);

    int ID = 0;
    //énazonosító bekérése
    printf("Enazonosito: ");
    if (scanf("%d", &ID)) {
        ;
    }
    
    //keresés a számlák között egyező énazonosítóért, ha megvan, akkor visszatér igazzal, miután felszabadította a listát
    account* srch;
    for (srch = info; srch != NULL; srch = srch->next) {
        if (ID == srch->ID) {
            account* iter;
            iter = info;
            while (iter != NULL) {
                account* kov = iter->next;
                free(iter);
                iter = kov;
            }

            return true;

        }
    }

    //lista felszabadítása, akkor is, ha hamissal kell visszatérni
    account* iter;
    iter = info;
    while (iter != NULL) {
        account* kov = iter->next;
        free(iter);
        iter = kov;
    }
    
    return false;
}

void changeID() {
    FILE* f;
    f = fopen("account.txt", "r");
    
    account data;
    

    rewind(f);
    fscanf(f, "%d,%d,%d,%d", &data.ID, &data.num, &data.pin, &data.e);

    data.ID = Decode(data.ID);

    fclose(f);

    f = fopen("account.txt", "w");

    int ID = 0;

    printf("Uj enazonosito(6 szamjegy): ");
    scanf("%d", &ID);

    data.ID = C(ID);

    fprintf(f, "%d,%d,%d,%d\n", data.ID, data.num, data.pin, data.e);

    printf("\nAz uj enazonositod: %d", Decode(data.ID));

    fclose(f);
}
