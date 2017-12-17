#ifndef SISTEM_H_INCLUDED
#define SISTEM_H_INCLUDED
#include <stdio.h>
#include <stdbool.h>
#include"Radnik.h"



void sistemStart(); //URADJENO DZ
//PRIJAVA NA SISTEM
bool login(); //URADJEDNO DZ
char provjeriNalog(char*,char*); //to do -IGAC
void pristupNalog(); // Ove tri ispod funkcije ce se moci samo pozvati iz ove (1)
void dodajNalog();//  1
void brisiNalog();//  1
void azurirajNalog();// 1
void sacuvajNalog(RADNIK*);  //FUNKCIJA KOJA DODAJE RADNIKA U DATOTEKU    #RH
void oslobodi(RADNIK*);  //FUNKCIJA KOJA DEALOCIRA SVE DIJELOVE RADNIKA   #RH
int brojRadnika(); //Pomocna funkcija kod azuriranja i brisanja naloga #IgorS

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
void evidencijaRobe();
void pregledPodatakaKupca(); //pregled podataka o kupcu
void pregledProizvod(); //pregled podataka za odredjeni proizvod
void pregledStanjaMjesec();
void citanjeRacuna();

////GRAFICKI INTERFEJS
void loading();
void adminMeniGrafika(); //Dane ZAVRSENO!!! PREGLEDATI
void radnikMeniGrafika(); //Dane ZAVRSENO!!! PREGLEDATI

            //zvjezdice pri unosu sifre


#endif // SISTEM_H_INCLUDED
