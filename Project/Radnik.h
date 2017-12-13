#ifndef RADNIK_H_INCLUDED
#define RADNIK_H_INCLUDED
#include "Osoba.h"

typedef struct radnik
{
    char* username;
    char pin[5];
    char radno_mjesto;
    OSOBA* osoba;
} RADNIK;

RADNIK* kreirajRadnika();
void ucitajRadnika(RADNIK*);
void ispisiRadnika(RADNIK*);
void obrisiRadnika(RADNIK*);

#endif // RADNIK_H_INCLUDED
