#ifndef SISTEM_H_INCLUDED
#define SISTEM_H_INCLUDED
#include <stdio.h>
#include <stdbool.h>
#include"Radnik.h"



void sistemStart(); //URADJENO DZ
//PRIJAVA NA SISTEM
bool login(); //URADJEDNO DZ
bool provjeriNalog(char*,char*); //to do -IGAC
void pristupNalog(); // Ove tri ispod funkcije ce se moci samo pozvati iz ove (1)
void dodajNalog();//  1
void brisiNalog();//  1
void azurirajNalog();// 1
void sacuvajNalog(RADNIK*);  //FUNKCIJA KOJA DODAJE RADNIKA U DATOTEKU    #RH
void oslobodi(RADNIK*);  //FUNKCIJA KOJA DEALOCIRA SVE DIJELOVE RADNIKA   #RH

//BIRANJE OPCIJA
void optionMenu();



////GRAFICKI INTERFEJS
void loading();

            //zvjezdice pri unosu sifre


#endif // SISTEM_H_INCLUDED
