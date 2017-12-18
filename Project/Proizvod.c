#include "Proizvod.h"
PROIZVOD* kreirajProizvod(char *naziv, double cijena)  // JORGOS ZAVRSIO - PREGLEDATI OBAVEZNO !!!
{
    PROIZVOD* proizvod;
    proizvod=(PROIZVOD*)malloc(sizeof(PROIZVOD));
    proizvod->naziv=(char*)calloc(strlen(naziv)+1,sizeof(char));
    strcpy(proizvod->naziv,naziv);
    proizvod->cijena=cijena;
    return proizvod;
}
