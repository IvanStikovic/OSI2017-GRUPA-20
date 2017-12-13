#include <stdio.h>
#include <stdlib.h>
#include "Radnik.h"
#include "Osoba.h"

int main()
{
    RADNIK *r=kreirajRadnika();
    ispisiRadnika(r);
    obrisiRadnika(r);
    return 0;
}
