#include <stdio.h>
#include <stdlib.h>
#include "Radnik.h"
#include "Osoba.h"
#include "Sistem.h"
#include "Racun.h"

int main(int argc, char *argv[])
{
    //parse_cmdline(argc, argv);
    //remove("SKLADISTE.txt");
    remove("SKLADISTE.txt");
    sistemStart();
    return 0;
}
