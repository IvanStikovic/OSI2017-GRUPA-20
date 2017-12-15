#include "Sistem.h"

void sistemStart()
{
    loading();
    if(login())
        optionMeni();
    else
        return;
}

bool login()
{
    char c;
    do
    {
    printf("Unesite username :");
    char username[20],sifra[20];
    scanf("%s",username);
    printf("\nUnesite sifru :");
    scanf("%s",sifra);
    if(provjeriNalog(username,sifra))
        return true;
    else
        {
            printf("\nPogresan username ili sifra !!!");
            printf("\nZa ponovo logovanje na sistem unesite 1.");
            printf("\nZa prekid prijavljivanja unesite 0.");
            scanf(" %c",&c);
        }
    }while(c);
    return false;
}

