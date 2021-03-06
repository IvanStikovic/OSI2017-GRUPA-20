#ifndef RACUN_H_INCLUDED
#define RACUN_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include "Proizvod.h"
#include "Datum.h"
#include "Valuta.h"

typedef struct racun
{
    DATUM datum;
    char* kupac;
    PROIZVOD* proizvodi;
    double* kolicina;
    double iznos;
    int n;//BROJ PROIZVODA
} RACUN;

extern VALUTA valuta;

void uveziRacune(); //UCITAVA RACUNE I RASPOREDJUJE IH U ODNOSU NA TO DA LI SU ULAZNI ILI IZLAZNI
void sacuvajRacun(RACUN*,char); // SNIMA RACUN U DATOTEKU
RACUN* ucitajRacune(int*); //
RACUN* kreirajRacun();
int validanRacun(char*);
void dodajProizvod(RACUN*,PROIZVOD*);
void izmjeniRacun(RACUN*);
void obrisiRacune(RACUN*,int);
void obrisiRacun(RACUN**);
void pisiRacun(RACUN*); // JORGOS ZAVRSENO I PROVJERENO !!!

//FORMATI RACUNA
RACUN* format1(char*,char*); // DZUNE RADIO TESTIRANO,MADA MOGLO BI SE JOS POSLIJE
RACUN* format2(char*,char*);
RACUN* format3(char*,char*);
RACUN* format4(char*,char*);
RACUN* format5(char*,char*);


#endif // RACUN_H_INCLUDED
