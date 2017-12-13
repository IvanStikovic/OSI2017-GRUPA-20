#include "Osoba.h"

void ucitajOsobu(OSOBA* o)
{
    printf("Ime:");
    char pom[50];
    scanf("%s",pom);
    o->ime=(char*)calloc(strlen(pom)+1,sizeof(char));
    strcpy(o->ime,pom);
    printf("Prezime:");
    char pom1[50];
    scanf("%s",pom1);
    o->prezime=(char*)calloc(strlen(pom1)+1,sizeof(char));
    strcpy(o->prezime,pom1);
    printf("\nUnesite platu:");
    scanf("%lf",&o->plata);
}

void ispisiOsobu(OSOBA* o)
{
    printf("\n%s",o->ime);
    printf("\n%s",o->prezime);
    printf("\n%lf",o->plata);
}

OSOBA* kreirajOsobu()
{
    OSOBA *o;
    o=(OSOBA*)malloc(sizeof(OSOBA));
        ucitajOsobu(o);

    return o;
}

void obrisiOsobu(OSOBA** o)
{
    free((*o)->ime);
    free((*o)->prezime);
    free(o);
}
