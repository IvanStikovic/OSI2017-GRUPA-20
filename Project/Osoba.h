#ifndef OSOBA_H_INCLUDED
#define OSOBA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct osoba
{
    char* ime;
    char* prezime;
    double plata;
} OSOBA;

OSOBA* kreirajOsobu();// TREBA PROVJERITI!!!!
void ucitajOsobu(OSOBA*);
void ispisiOsobu(OSOBA*);
void obrisiOsobu(OSOBA**);//PRIKA


#endif // OSOBA_H_INCLUDED
