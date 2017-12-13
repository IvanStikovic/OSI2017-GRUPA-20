#ifndef SISTEM_H_INCLUDED
#define SISTEM_H_INCLUDED
#include <stdio.h>
#include <stdbool.h>

void sistemStart();
bool login();
bool provjeriNalog(char*,char*);
void pristupNalog(); // Ove tri ispod funkcije ce se moci samo pozvati iz ove (1)
void dodajNalog();//  1
void brisiNalog();//  1
void azurirajNalog();// 1





#endif // SISTEM_H_INCLUDED
