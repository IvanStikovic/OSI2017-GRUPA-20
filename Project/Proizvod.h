#ifndef PROIZVOD_H_INCLUDED
#define PROIZVOD_H_INCLUDED

typedef struct proizvod
{
    char *naziv;
    double cijena;
    double sifra;
} PROIZVOD;

PROIZVOD* kreirajProizvod(char*,double); // URADJENO I PREGLEDANO !
void obrisiProizvod(PROIZVOD*); // URADJENO I PREGLEDANO !


#endif // PROIZVOD_H_INCLUDED
