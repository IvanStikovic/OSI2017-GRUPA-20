#include "Sistem.h"

void sistemStart()
{   char c;
    loading();
    if(c=login())
        optionMeni(c);
    else
        return;
}

char login()
{
    char c,r_mjesto;
    do
    {
    printf("Unesite username :");
    char username[20],sifra[20];
    scanf("%s",username);
    printf("\nUnesite sifru :");
    scanf("%s",sifra);
    if(r_mjesto=provjeriNalog(username,sifra))
        return r_mjesto;
    else
        {
            printf("\nPogresan username ili sifra !!!");
            printf("\nZa ponovo logovanje na sistem unesite 1.");
            printf("\nZa prekid prijavljivanja unesite 0.");
            scanf(" %c",&c);
        }
    }while(c);
    return 0;
}


char provjeriNalog(char* usrnm ,char* sfr)
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
                return radno_mjesto;// TEST izmjena- da se vrati radno mjesto kako bi se znalo koji opcioni meni da mu se prikaze
            }
            provjera=fscanf(dat,"%s %s %lf %s %s %c",ime,prezime,&plata,username,pin,&radno_mjesto);

        }
        fclose(dat);
    }
    return 0;

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
    int br_radnika,provjera,i=0;
    char pom[20],ime[20],prezime[20],username[20],pin[5],radno_mjesto;
    double plata;
    RADNIK *radnici;

    printf("Unesite username naloga koji zelite da azurirate!\n");
    scanf("%s",pom);
    br_radnika=brojRadnika();
    radnici=(RADNIK*)calloc(br_radnika,sizeof(RADNIK));
    if(dat=fopen("RADNICI.txt","r")
    {
        for(i=0;i<br_radnika;i++)
        {
            provjera=fscanf(dat,"%s %s %lf %s %s %c",ime,prezime,&plata,username,pin,&radno_mjesto);
            if(provjera==6)
                {
                    strcpy(radnici[i]->osoba->ime,ime);
                    strcpy(radnici[i]->osoba->prezime,prezime);
                    radnici[i]->osoba->plata=plata;
                    strcpy(radnici[i]->username,username)
                    strcpy(radnici[i]->pin,pin);
                    radnici[i]->radno_mjesto=radno_mjesto;
                }
        }
        fclose(dat);
    }

}//#ByIgorS

void optionMeni(char c)
{
    if(c=='a')
        adminMeni();
    else
        radnikMeni();
}

void adminMeni()
{
    char c;
    do
    {
     adminMeniGrafika();
        scanf("%c",&c);
        switch(c)
        {
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        }
    }while(c)
    izlazGrafika();
}

void radnikMeni()
{
    char c;
    do
    {
     radnikMeniGrafika();
        scanf("%c",&c);
        switch(c)
        {
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        }
    }while(c)
    izlazGrafika();
}

int brojRadnika()
{
    FILE *fp;
    int br=0,p;
    double plata;
    char pom[20],ime[20],prezime[20],username[20],pin[5],radno_mjesto;
    if(fp=fopen("RADNICI.txt","r"))
    {
        p=fscanf(fp,"%s %s %lf %s %s %c",ime,prezime,&plata,username,pin,&radno_mjesto);
        if(p==6)
            br++;
        while(p==6)
        {
            p=fscanf(fp,"%s %s %lf %s %s %c",ime,prezime,&plata,username,pin,&radno_mjesto);
            br++;
        }
        fclose(fp);
    }
    return br;
}
