#ifndef RACUN_H_INCLUDED
#define RACUN_H_INCLUDED
#include <stdio.h>
#include "Proizvod.h"

typedef struct racun
{
    PROIZVOD* proizvodi;
    double* kolicina;
    double iznos;
    int n;//BROJ PROIZVODA
} RACUN;

void uveziRacune(); //UCITAVA RACUNE I RASPOREDJUJE IH U ODNOSU NA TO DA LI SU ULAZNI ILI IZLAZNI
void sacuvajRacun(char); // SNIMA RACUN U DATOTEKU (char da se vidi da li je ulazni ili izlazni)
RACUN* ucitajRacune(char); // VRACA DINAMICKI ALOCIRAN NIZ RACUNA (char opet ista svrha)
RACUN* kreirajRacun();
void dodajProizvod(RACUN*,PROIZVOD*);
void izmjeniRacun(RACUN*);
void obrisiRacun();




#endif // RACUN_H_INCLUDED
