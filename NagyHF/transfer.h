#ifndef TRANSFER_H_INCLUDED
#define TRANSFER_H_INCLUDED

typedef struct transfer {									//Struktúrába rendezés
	int numfrom;
	int numto;
	int amount;
	int* next;
}transfer;

int transferlines();

void transfering();

void readTransfering();

#endif