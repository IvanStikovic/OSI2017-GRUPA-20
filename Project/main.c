#include <stdio.h>
#include <stdlib.h>
#include "Radnik.h"
#include "Osoba.h"
#include "Sistem.h"
#include "Racun.h"

int main(int argc, char *argv[])
{   //dodajNalog();
    parse_cmdline(argc, argv);
    sistemStart();
    return 0;
}
