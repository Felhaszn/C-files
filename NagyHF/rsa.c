#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>

#include "debugmalloc.h"

int p() {
    return 353;
}

int q() {
    return 359;
}

long int e() {
    return 7;
}

/*N szám elkészítése*/
unsigned long long int N(int p, int q) {
    return p * q;
}

/*Fí N szám elkészítése*/
unsigned long long int fiN(int p, int q) {
    return (p - 1) * (q - 1);
}

/*Ismételt négyzetre emelés*/
long long int RepSqr(long int a, long int b) {
    long long int alap = a;
    long long int maradek = 1;

    for (int i = 1; i <= b; i++){
        alap = maradek * a;
        maradek = alap % N(p(), q());
        alap = maradek;
    }

    return alap;
}

/*Üzenet kódolása*/
unsigned long long int C(long int message) {
    unsigned long long int c = RepSqr(message, e());
    return c % N(p(), q());
}

/*d visszafejtő kulcs elkészítése*/
unsigned long long int Creating_d() {
    unsigned long long int d;
    int a = p();
    int b = q();
    long int fi = fiN(a, b);
    for (int k = 1; k < fi; k++) {
        if ((k * fi + 1) % e() == 0) {
            d = (k * fi + 1) / e();
            return d;
        }
    }

    return -1;
}

/*Az üzenet dekódolása*/
long int Decode(long int Coded) {
    long int message;
    message = RepSqr(Coded, Creating_d());
    return message;
}