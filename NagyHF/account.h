#ifndef ACCOUNT_H_INCLUDED
#define ACCOUNT_H_INCLUDED
#include <stdbool.h>

int lines();

void accCreate(int N, int e);

int accRead();

bool accLogin();

void changeID();

#endif