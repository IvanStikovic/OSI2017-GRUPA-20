#ifndef SISTEM_H_INCLUDED
#define SISTEM_H_INCLUDED
#include <stdio.h>
#include <stdbool.h>
#include"Radnik.h"



void sistemStart(); //URADJENO DZ
//PRIJAVA NA SISTEM
bool login(); //URADJEDNO
char provjeriNalog(char*,char*); // URADJENO
void pristupNalog(); // URADJENO
void dodajNalog();//  URADJENO
void brisiNalog();//  URADJENO
void azurirajNalog();// URADJENO
void sacuvajNalog(RADNIK*);  // URADJENO
void oslobodi(RADNIK*);  // URADJENO
int brojRadnika(); // URADJENO
void obrisiDatoteku() // URADJENO
RADNIK** ucitajRadnike() //URADJENO
RADNIK* kopirajRadnika(char*, char*, double , char*, char*,char ) //URADJENO

//BIRANJE OPCIJA
void optionMeni(char);
void adminMeni();   //URADJENO
void radnikMeni();

    //admin opcije
    // +pristupNalog();
void evidencijaZaposlenih();
void evidencijaRacuna();
void prikazKursneListe();

    //admin + radnik opcije
void evidencijaRobe();
void pregledPodatakaKupca(); //pregled podataka o kupcu
void pregledProizvod(); //pregled podataka za odredjeni proizvod
void pregledStanjaMjesec();
void citanjeRacuna();

////GRAFICKI INTERFEJS
void loading();
void adminMeniGrafika(); //Dane ZAVRSENO!!! PREGLEDATI - CHECKED
void radnikMeniGrafika(); //Dane ZAVRSENO!!! PREGLEDATI - CHECKED
void pristupNalogGrafika(); //Prika ZAVRSIO - PREGLEDATI !

            //zvjezdice pri unosu sifre


#endif // SISTEM_H_INCLUDED
