#include "Racun.h"

/*void uveziRacune()
{
    int i;
    char *c;
    RACUN* pom;
    c=(char*)calloc(1,1);
    for(i=1; i<=5; i++)
            if(pom=format1(argv[i],c))
                sacuvajRacun(pom,c);
            else if(pom=format2(argv[i],c))
                sacuvajRacun(pom,c);
            else if(pom=format3(argv[i],c))
                sacuvajRacun(pom,c);
            else (pom=format4(argv[i],c))
                sacuvajRacun(pom,c);
}
*/
RACUN* kreirajRacun()
{
    RACUN* racun=(RACUN*)calloc(1,sizeof(RACUN));
    return racun;
}

void dodajProizvod(RACUN* racun,PROIZVOD* proizvod)
{
    racun->proizvodi=(RACUN*)realloc(racun->proizvodi,(racun->n+1)*sizeof(PROIZVOD));
    racun->proizvodi[racun->n].cijena=proizvod->cijena;
    racun->proizvodi[racun->n].naziv=(char*)calloc(strlen(proizvod->naziv)+1,sizeof(char));
    strcpy(racun->proizvodi[racun->n].naziv,proizvod->naziv);
}

void pisiRacun(RACUN* racun) // JORGOS ZAVRSENO I PROVJERENO !!!
{
    int i;
    racun->iznos=0.0;
    printf("\n");
    printf("------------------------------------------------------\n");
    printf("Broj proizvoda na racunu: %d\n", racun->n);
    printf("------------------------------------------------------\n");
    printf("RB. NAZIV PROIZVODA           CIJENA   KOLICINA UKUPNO\n");
    printf("--- ------------------------- ------ -------- ------\n");
    for(i=0;i<(racun->n);i++)
    {
        printf("%2d. %-25s %6.2lf %8.2lf %6.2lf\n", i+1, racun->proizvodi[i].naziv, racun->proizvodi[i].cijena, racun->kolicina[i], (racun->proizvodi[i].cijena)*(racun->kolicina[i]));
        (racun->iznos)+=((racun->proizvodi[i].cijena)*(racun->kolicina[i]));
    }
    printf("------------------------------------------------------\n");
    printf("                                  ____________________ \n");
    printf("\n");
    printf("                                  UKUPAN IZNOS: %.2lf  \n", (racun->iznos));
    printf("                                  ____________________\n");
    printf("\n");
    printf("------------------------------------------------------\n");
}

RACUN* format1(char* file,char* c)
{
    FILE* dat;
    int i;
    if(dat=fopen(file,"r"))
    {
        RACUN* pomRacun=kreirajRacun();
        pomRacun->n=1;
        char pomString[150],naziv[30],sifra[30];
        int br=0;
        double kolicina,cijena,ukupno;
        pomRacun->proizvodi=(PROIZVOD*)calloc(pomRacun->n,sizeof(PROIZVOD));
        pomRacun->kolicina=(double*)calloc(pomRacun->n,sizeof(double));
        for(i=0; i<6; i++)
            fgets(pomString,150,dat);
            int sum=0;
        while(fscanf(dat,"%s %s - %lf - %lf - %lf",sifra,naziv,&kolicina,&cijena,&ukupno)==5)
        {
            if(br==(pomRacun->n-1))
            {
                pomRacun->proizvodi=realloc(pomRacun->proizvodi,(pomRacun->n+1)*sizeof(PROIZVOD*));
                pomRacun->kolicina=realloc(pomRacun->kolicina,(pomRacun->n+1)*sizeof(double));
                pomRacun->n+=1;
            }
            pomRacun->proizvodi[br].cijena=cijena;
            strcpy(pomRacun->proizvodi[br].naziv,sifra);
            pomRacun->kolicina[br]=kolicina;
            sum+=ukupno;
            br++;
        }
            fscanf(dat,"%lf",&ukupno);
            if(ukupno==sum)
                return pomRacun;
            else
            {   //obrisiRacun(pomRacun); TREBA NAPRAVITI
                return 0;
            }
        }
        else return 0;
}

RACUN* format4(char* file,char* c)
{
    FILE* dat;
    int i;
    if(dat=fopen(file,"r"))
    {
        RACUN* pomRacun=(RACUN*)calloc(1,sizeof(RACUN));
        pomRacun->n=1;
        char pomString[150],naziv[30],sifra[30];
        int br=0;
        double kolicina,cijena,ukupno;
        pomRacun->proizvodi=(PROIZVOD*)calloc(pomRacun->n,sizeof(PROIZVOD));
        pomRacun->kolicina=(double*)calloc(pomRacun->n,sizeof(double));
        for(i=0; i<7; i++)
            fgets(pomString,150,dat);
            int sum=0;
        while(fscanf(dat,"%s %s - %lf - %lf - %lf",sifra,naziv,&kolicina,&cijena,&ukupno)==5)
        {
            if(br==(pomRacun->n-1))
            {
                pomRacun->proizvodi=realloc(pomRacun->proizvodi,(pomRacun->n+1)*sizeof(PROIZVOD*));
                pomRacun->kolicina=realloc(pomRacun->kolicina,(pomRacun->n+1)*sizeof(double));
                pomRacun->n+=1;
            }
            pomRacun->proizvodi[br].cijena=cijena;
            strcpy(pomRacun->proizvodi[br].naziv,sifra);
            pomRacun->kolicina[br]=kolicina;
            sum+=ukupno;
            br++;
        }
            fscanf(dat,"%lf",&ukupno);
            if(ukupno==sum)
                return pomRacun;
            else
            {   //obrisiRacun(pomRacun);
                return 0;
            }
        }
        else return 0;
}
