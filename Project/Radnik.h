#ifndef RADNIK_H_INCLUDED
#define RADNIK_H_INCLUDED
#include "Osoba.h"

typedef struct radnik
{
    char* username;
    char pin[4];
    char radno_mjesto;
    OSOBA osoba;
} RADNIK;


#endif // RADNIK_H_INCLUDED
