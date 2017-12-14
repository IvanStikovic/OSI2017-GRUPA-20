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

bool provjeriNalog(char* usrnm ,char* sfr)
{
    char ime[20],prezime[20],username[20],pin[5],radno_mjesto;
    double plata;
    int provjera;
    FILE *dat;
    if(dat=fopen("RADNICI.txt","r"))
    {
        provjera=fscanf(dat,"%s %s %c %s %s %lf",username,pin,&radno_mjesto,ime,prezime,&plata);
        while(provjera==6)
        {
            if((strcmp(username,usrnm)==0) && (strcmp(pin,sfr)==0))
            {
                fclose(dat);
                return true;
            }
            provjera=fscanf(dat,"%s %s %c %s %s %lf",username,pin,&radno_mjesto,ime,prezime,&plata);

        }
        fclose(dat);
    }
    return false;

}


