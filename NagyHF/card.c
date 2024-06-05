#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "rsa.h"
#include "debugmalloc.h"

typedef struct card {
	int cvc;
	int lejaratev;
	int lejaratho;
	int cardnum;
}card;

/*Létrehoz egy kártyát*/
void createCard() {
	srand(time(0));

	FILE* f;
	f = fopen("card.txt", "w");

	card* data;
	data = (card*)malloc(1 * sizeof(card));

	data->cvc = rand() % 999;
	if (data->cvc < 100)
		data->cvc += 100;

	time_t seconds = time(NULL);
	struct tm* current_time = localtime(&seconds);

	data->lejaratev = current_time->tm_year -100 + 5;					//A jelenlegi évhez képest 5 évvel később
	data->lejaratho = current_time->tm_mon+1;							//A jelenlegi hónap

	data->cardnum = rand() % 999999;
	if (data->cardnum < 100000)
		data->cardnum += 100000;

	fprintf(f, "%d,%d,%d,%d", C(data->cvc), C(data->lejaratev), C(data->lejaratho), C(data->cardnum));

	printf("\nKartya sikeresen letrehozva.\n");

	free(data);

	fclose(f);
}

/*Beolvassa és kiírja a kártyán lévő adatokat*/
void readCard() {
	FILE* f;
	f = fopen("card.txt", "r");

	if (f == NULL) {
		printf("\nElobb keszits egy kartyat!\n");
		return;
	}

	card* data;
	data = (card*)malloc(1 * sizeof(card));

	rewind(f);
	fscanf(f, "%d,%d,%d,%d", &data->cvc, &data->lejaratev, &data->lejaratho, &data->cardnum);

	printf("**********************\n");
	printf("* CVC:           %d *\n", Decode(data->cvc));
	printf("* Lejarat:     %d/%d *\n", Decode(data->lejaratev), Decode(data->lejaratho));
	printf("* Kartyaszam: %d *\n", Decode(data->cardnum));
	printf("**********************\n");


	free(data);

	fclose(f);
}