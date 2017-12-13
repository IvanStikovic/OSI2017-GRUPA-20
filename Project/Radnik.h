#ifndef RADNIK_H_INCLUDED
#define RADNIK_H_INCLUDED
#include "Osoba.h"

typedef struct radnik
{
    char* username;
    char pin[4];
    char radno_mjesto;
    OSOBA* osoba;
} RADNIK;

RADNIK* kreirajRadnika(); //JELA
void ucitajRadnika(RADNIK*); //PRIKA
void ispisiRadnika(RADNIK*);//JELA
void obrisiRadnika(RADNIK**);//TREBA PROVJERITI

#endif // RADNIK_H_INCLUDED
