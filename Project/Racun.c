#include "Racun.h"

void uveziRacune()
{
    char c;
    RACUN* pom;
    c=(char*)calloc(1,1);
    for(int i=1; i<=5; i++)
        if(validanRacun(argv[i]))
        {
            if(pom=format1(datoteka[i],c))
                sacuvajRacun(pom,c);
            else if(pom=format2(datoteka[i],c))
                sacuvajRacun(pom,c);
            else if(pom=format3(datoteka[i],c))
                sacuvajRacun(pom,c);
            else (pom=format4(datoteka[i],c))
                sacuvajRacun(pom,c);
        }
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
    if(dat=fopen(file,"r"))
    {
        RACUN* pomRacun=kreirajRacun();
        pomRacun.n=5;
        char pomString[150];
        int br=0;
        char naziv[30];
        double kolicina,cijena,ukupno;
        pomRacun.proizvodi=(PROIZVOD*)calloc(pomRacun.n,sizeof(PROIZVOD));
        pomRacun.kolicina=(double*)calloc(pomRacun.n,sizeof(double));
        for(i=0; i<6; i++)
            fgets(pomString,150,dat);
        while(fscanf("%s %lf %lf %lf",naziv,&kolicina,&cijena,&ukupno)==4)
        {
            if(br==(pomRacun.n-1))
            {
                pomRacun.proizvodi=realloc(pomRacun.proizvodi,n*2*sizeof(PROIZVOD*));
                pomRacun.kolicina=realloc(pomRacun.kolicina,n*2*sizeof(double));
                pomRacun.n*=pomRacun.n;
            }
            pomRacun.proizvodi[br]=kreirajProizvod(naziv,cijena);//POVRATNI TIP MODIFIKOVATI ILI NACI DRUGO RJESENJE

            int sum=0;
            for(i=0; i<pomRacun.n; i++)
                sum+=pomRacun.proizvodi[i].cijena*pomRacun.kolicina[i];

            fgets(pomString,150,dat);
            fscanf("%s %d",pomString,ukupno);
            if(ukupno==sum)
                return pomRacun;
            else
            {   obrisiRacun(pomRacun);
                return 0;
            }
        }
        else return 0;
    }
