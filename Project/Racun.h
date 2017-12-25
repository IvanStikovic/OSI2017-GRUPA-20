#ifndef RACUN_H_INCLUDED
#define RACUN_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include "Proizvod.h"
#include <string.h>
typedef struct racun
{
    PROIZVOD* proizvodi;
    double* kolicina;
    double iznos;
    int n;//BROJ PROIZVODA
} RACUN;

void uveziRacune(int argc,char *argv[]); //UCITAVA RACUNE I RASPOREDJUJE IH U ODNOSU NA TO DA LI SU ULAZNI ILI IZLAZNI
void parse_cmdline(int argc,char* argv[]);
void sacuvajRacun(RACUN*,char*); // SNIMA RACUN U DATOTEKU
RACUN* ucitajRacune(char); // VRACA DINAMICKI ALOCIRAN NIZ RACUNA
RACUN* kreirajRacun();
int validanRacun(char*);
void dodajProizvod(RACUN*,PROIZVOD*);
void izmjeniRacun(RACUN*);
void obrisiRacun(RACUN*);
void pisiRacun(RACUN*); // JORGOS ZAVRSENO I PROVJERENO !!!

//FORMATI RACUNA
RACUN* format1(char*,char*); // DZUNE RADIO TESTIRANO,MADA MOGLO BI SE JOS POSLIJE
RACUN* format2(char*,char*);
RACUN* format3(char*,char*);
RACUN* format4(char*,char*);


#endif // RACUN_H_INCLUDED
