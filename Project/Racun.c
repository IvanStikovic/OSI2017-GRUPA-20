#include "Racun.h"

void ucitajRacune()
{
    FILE* dat=fopen("RACUNI.txt","r");
    if(dat)
    {

    }
}

RACUN* kreirajRacun()
{
    RACUN* racun=(RACUN*)calloc(1,sizeof(RACUN));
    return racun;
}

void dodajProizvod(RACUN* racun,PROIZVOD* proizvod)
{
    racun->proizvodi=(RACUN*)realloc(racun->proizvodi,(racun->n+1)*sizeof(PROIZVOD));
    racun->proizvodi[racun->n].cijena=proizvod->cijena;
    racun->proizvodi[racun->n].naziv=(char*)calloc(strlen(proizvod->naziv)+1,sizeof(char));
    strcpy(racun->proizvodi[racun->n].naziv,proizvod->naziv);
}
