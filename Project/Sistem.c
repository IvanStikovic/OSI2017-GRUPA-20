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
        provjera=fscanf(dat,"%s %s %lf %s %s %c",ime,prezime,&plata,username,pin,&radno_mjesto);
        while(provjera==6)
        {
            if((strcmp(username,usrnm)==0) && (strcmp(pin,sfr)==0))
            {
                fclose(dat);
                return true;
            }
            provjera=fscanf(dat,"%s %s %lf %s %s %c",ime,prezime,&plata,username,pin,&radno_mjesto);

        }
        fclose(dat);
    }
    return false;

}

//FUNKCIJA ZA DODAVANJE NALOGA U DATOTEKU BY #RENE
void dodajNalog()
{
    char ime[20], prezime[20],username[20];
    OSOBA *nova = (OSOBA*)malloc(sizeof(OSOBA));
    RADNIK *novi = (RADNIK*)malloc(sizeof(RADNIK));
    printf("Unesite ime radnika:");
    scanf("%s",ime);
    printf("Unesite prezime radnika:");
    scanf("%s",prezime);
    printf("Unesite platu:");
    scanf("%lf",&nova->plata);
    nova->ime=(char*)calloc(sizeof(ime)+1, sizeof(char));
    nova->prezime = (char*)calloc(sizeof(prezime)+1, sizeof(char));
    strcpy(nova->ime,ime);
    strcpy(nova->prezime,prezime);
    printf("Unesite username za radnika:");
    scanf("%s",username);
    novi->username=(char*)calloc(sizeof(username)+1, sizeof(char));
    strcpy(novi->username,username);
    printf("Unesite PIN za radnika(4 CIFRE):");
    scanf("%s",novi->pin);
    getchar();
    printf("Da li zaposleni ima privilegije administratora(a), ili analiticara(r):");
    scanf("%c",&novi->radno_mjesto);
    novi->osoba= nova;
    sacuvajNalog(novi);  //FUNKCIJA KOJA DODAJE RADNIKA U DATOTEKU
    oslobodi(novi);    //FUNKCIJA KOJA DEALOCIRA SVE DIJELOVE RADNIKA
    return;
}

void oslobodi(RADNIK *rad)
{

    free(rad->osoba->ime);
    free(rad->osoba->prezime);
    free(rad->username);
}

void sacuvajNalog(RADNIK *rad)
{
    FILE *dat;
    if(dat = fopen("RADNICI.TXT","r"))
    {
        fprintf(dat,"%s %s %lf %s %s %c\n",rad->osoba->ime, rad->osoba->prezime, rad->osoba->plata, rad->username, rad->pin, rad->radno_mjesto);
        printf("Nalog je uspjesno kreiran i sacuvan!\n");
        fclose(dat);
        return;
    }
    else
        printf("Nalog nije uspjesno kreiran i sacuvan, greska prilikom cuvanja naloga u bazi.\n");
}

void azurirajNalog()
{
    FILE *dat;
    int br_radnika=1,provjera;
    char pom[20],ime[20],prezime[20],username[20],pin[5],radno_mjesto;
    double plata;
    printf("Unesite username naloga koji zelite da azurirate!\n");
    scanf("%s",pom);
    if(dat=fopen("RADNICI.txt","r"))
    {
        provjera=fscanf(dat,"%s %s %lf %s %s %c",ime,prezime,&plata,username,pin,&radno_mjesto);
        while(provjera==6)
        {
            provjera=fscanf(dat,"%s %s %lf %s %s %c",ime,prezime,&plata,username,pin,&radno_mjesto);
            br_radnika++;
        }
        fclose(dat);
    }// NEDOVRSENO NASTAVLJAM SUTRA
}//#ByIgorS


