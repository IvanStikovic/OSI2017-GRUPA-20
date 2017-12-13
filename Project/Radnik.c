#include "Radnik.h"

void obrisiRadnika(RADNIK**r)
{

    free((*r)->username);
    obrisiOsobu(&((*r)->o));
    free(*r);
}
