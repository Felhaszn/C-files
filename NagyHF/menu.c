#include <stdio.h>

/*Bejelentkezés*/
int login_menu() {
    int input;

    printf("\n1. Bejelentkezes\n");
    printf("2. Uj szamla letrehozasa\n");
    printf("0. Kilepes\n\n");
    
    scanf("%d", &input);
    
    return input;
}

/*Főmenü*/
int main_menu() {
    int input;

    printf("\n1. Utalas\n");
    printf("2. Kartyaadatok megtekintese\n");
    printf("3. Legutobbi utalas\n");
    printf("4. Szamlaszam megtekintese\n");
    printf("5. E-bank enazonosito megvaltoztatas\n");
    printf("6. Kartya letrehozas\n");
    printf("0. Kijelentkezes\n\n");

    scanf("%d", &input);

    return input;
}

