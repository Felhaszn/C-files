#ifndef RSA_H_INCLUDED
#define RSA_H_INCLUDED

int p();

int q();

long int e();

unsigned long long int N(int p, int q);

unsigned long long int fiN(int p, int q);

long long int RepSqr(long int a, long int b);

unsigned long long int C(long int msg);

unsigned long long int Creating_d();

long int Decode(long int Coded);

#endif