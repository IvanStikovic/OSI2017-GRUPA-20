#ifndef PROIZVOD_H_INCLUDED
#define PROIZVOD_H_INCLUDED

typedef struct proizvod
{
    char *naziv;
    double cijena;
} PROIZVOD;

PROIZVOD* kreirajProizvod(char*,double); // JORGOS ZAVRSIO - PREGLEDATI OBAVEZNO !!!
void obrisiProizvod(PROIZVOD*); //JORGINHO


#endif // PROIZVOD_H_INCLUDED
