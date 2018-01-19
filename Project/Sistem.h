#ifndef SISTEM_H_INCLUDED
#define SISTEM_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdbool.h>
#include <windows.h>
#include "Radnik.h"
#include "Racun.h"
#include "Valuta.h"

#define ENTER 13
#define SPACE 32
#define BACKSPACE 8

//POKRETANJE SISTEMA
void sistemStart();

//PRIJAVA NA SISTEM
char login(); //
char provjeriNalog(char*,char*); // PROVJERAVA DA LI POSTOJI TRAZENI NALOG
void pristupNalog(); // IZ OVE FUNKCIJE SE MOGU POZVATI SLEDECE 3 OPCIJE ISPOD (1)
void dodajNalog();         //  1
void brisiNalog();        //  1
void azurirajNalog();    //  1
void sacuvajNalog(RADNIK*);  //FUNKCIJA KOJA DODAJE NALOG RADNIKA U DATOTEKU
int brojRadnika(); //VRACA BROJ RADNIKA
RADNIK** ucitajRadnike(); //UCITAVA RADNIKE I VRACA DINAMICKI ALOCIRAN NIZ POKAZIVACA NA RADNIK
void pisiRadnike(); // ISPISUJE RADNIKE
RADNIK* kopirajRadnika(char*, char*, double , char*, char*,char ); // KOPIRA RADNIKA


void obrisiProizvode(PROIZVOD* proizvodi,int broj_proizvoda,double* kolicina);



//BIRANJE OPCIJA
void optionMeni(char);
void adminMeni();
void radnikMeni();

    //admin opcije
    // +pristupNalog();
        void evidencijaZaposlenih();
        void evidencijaRacuna();
        void prikazKursneListe();

    //admin + radnik opcije
        void evidencijaRobe(char);
        void pregledPodatakaKupca(); //pregled podataka o kupcu
        void pregledProizvod(); //pregled podataka za odredjeni proizvod
        void pregledStanjaMjesec();
        void citanjeRacuna();


////GRAFICKI INTERFEJS
void loadingGrafika();
void adminMeniGrafika();
void radnikMeniGrafika();
void pristupNalogGrafika();
void izlazGrafika();

#endif // SISTEM_H_INCLUDED
