#include "Radnik.h"

void obrisiRadnika(RADNIK*r)
{

    free(r->username);
    obrisiOsobu(r->osoba);
    free(r);
}

void ucitajRadnika(RADNIK *r)
{
    printf("Username:");
    char pom[50];
    scanf("%s", pom);
    r->username=(char*)calloc(strlen(pom)+1,sizeof(char));
    strcpy(r->username,pom);
    printf("PIN:");
    scanf("%s", r->pin);
    printf("Radno mjesto (a ili r):");
    scanf(" %c", &r->radno_mjesto);
    r->osoba=kreirajOsobu();
}

RADNIK* kreirajRadnika()
{
    RADNIK* pom;
    pom=(RADNIK*)malloc(sizeof(RADNIK));
    ucitajRadnika(pom);
    return pom;
}

void ispisiRadnika(RADNIK *r)
{

    printf("%-10s %-15s %-15s %-4s %6.2lf %-15s ",r->osoba.ime,r->osoba.prezime,r->username,r->pin,r->osoba.plata,r->radno_mjesto);
}

