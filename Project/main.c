#include <stdio.h>
#include <stdlib.h>
#include "Radnik.h"
#include "Osoba.h"

int main()
{
    OSOBA *o=(OSOBA*)malloc(sizeof(OSOBA));
    ucitajOsobu(o);
    ispisiOsobu(o);
    o=kreirajOsobu();
    return 0;
}
