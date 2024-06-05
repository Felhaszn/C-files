#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "rsa.h"
#include "debugmalloc.h"
#include "account.h"

typedef struct transfer {									//Struktúrába rendezés
	int numfrom;
	int numto;
	int amount;
	struct transfer* next;
}transfer;

int transferlines() {
	FILE* f;

	f = fopen("transfers.txt", "r");
	if (f == NULL) {
		printf("Nem sikerult megnyitni a fajlt!");
		return -1;
	}
	
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

void transfering() {
	FILE* f;												//Fájl megnyitása
	
	f = fopen("transfers.txt", "a");						//Ha nincs, akkor fájl létrehozása
	if (f == NULL) {
		printf("Nem sikerult megnyitni a fajlt!");
		return;
	}

	transfer data;

	data.numfrom = accRead();

	printf("A masik szamlaszam: ");
	scanf("%d", &data.numto);

	data.amount = -1;
	while (data.amount < 0) {
		printf("Osszeg: ");
		scanf("%d", &data.amount);
	}

	fprintf(f, "%d,%d,%d\n", data.numfrom, C(data.numto), C(data.amount));
	printf("\nSikeres utalas!\n");
	
	fclose(f);												//Fájl bezárása
}

void readTransfering() {
	FILE* f;
	f = fopen("transfers.txt", "r");

	int l = transferlines();

	if (f == NULL) {
		printf("Nem sikerult megnyitni a fajlt!");
		return;
	}

	transfer elem;
	transfer* data = NULL;
	

	while (fscanf(f, "%d,%d,%d", &elem.numfrom, &elem.numto, &elem.amount) != EOF) {
		transfer* uj;
		uj = (transfer*)malloc(sizeof(transfer));
		uj->numfrom = elem.numfrom;
		uj->numto = elem.numto;
		uj->amount = elem.amount;
		uj->next = NULL;                        //értékek átadása

		if (data == NULL) {
			data = uj;                          //ha nullptr, akkor az elsőt ide szúrja be
		}
		else {
			transfer* mozgo = data;              //ha nem, akkor hozzáfűzi
			while (mozgo->next != NULL) {
				mozgo = mozgo->next;
			}
			mozgo->next = uj;
		}
	}

	transfer* srch;
	for (srch = data; srch != NULL; srch = srch->next) {
		printf("\nUtalva innen: %d\nIde: %d\nEnnyit: %dFt\n", srch->numfrom, Decode(srch->numto), Decode(srch->amount));
	}
	transfer* iter;
	iter = data;
	while (iter != NULL) {
		transfer* kov = iter->next;
		free(iter);
		iter = kov;
	}

	fclose(f);
}