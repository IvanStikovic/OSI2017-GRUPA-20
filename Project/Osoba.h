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

OSOBA* kreirajOsobu(); // KREIRA DINAMICKI ALOCIRANU PROMJENLJIVU TIPA OSOBA
void ucitajOsobu(OSOBA*);   // UCITAVA OSOBU SA PODACIMA KOJI SE UNOSE SA STANDARDNOG ULAZA
void ispisiOsobu(OSOBA*);   //ISPISUJE PROMJENLJIVU TIPA OSOBA
void obrisiOsobu(OSOBA*); // OSLOBADJA MEMORIJSKI PROSTOR ALOCIRANE PROMJENLJIVE TIPA OSOBA


#endif // OSOBA_H_INCLUDED
