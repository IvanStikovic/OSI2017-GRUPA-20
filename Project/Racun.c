#include "Racun.h"

void uveziRacune()
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
            {   obrisiRacun(pomRacun);
                return 0;
            }
        }
        else return 0;
    }
