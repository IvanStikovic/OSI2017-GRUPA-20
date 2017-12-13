#include "Radnik.h"

void obrisiRadnika(RADNIK**r)
{

    free((*r)->username);
    obrisiOsobu(&((*r)->o));
    free(*r);
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
    printf("Radno mjesto:");
    scanf("%c", &r->radno_mjesto);
    r->osoba=kreirajOsobu();
}

RADNIK* kreirajRadnika()
{
    RADNIK*pom;
    pom=(RADNIK*)malloc(sizeof(RADNIK));
    return pom;
}

ispisiRadnika(RADNIK *r)
{

    printf("%s",r->username);
    printf("%s",r->pin);
    printf("%s",r->radno_mjesto);
    ispisiOsobu(r->osoba);
}
