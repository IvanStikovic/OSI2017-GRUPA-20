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

RADNIK* kreirajRadnika(); // KREIRA DINAMICKI ALOCIRANU PROMJENLJIVU TIPA RADNIK
void ucitajRadnika(RADNIK*); // UCITAVA RADNIKA SA PODACIMA KOJI SE UNOSE SA STANDARDNOG ULAZA
void obrisiRadnika(RADNIK*);  // OSLOBADJA MEMORIJSKI PROSTOR ALOCIRANE PROMJENLJIVE TIPA RADNIK

#endif // RADNIK_H_INCLUDED
