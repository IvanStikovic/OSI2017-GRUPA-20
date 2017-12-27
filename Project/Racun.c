#include "Racun.h"

void parse_cmdline(int argc,char* argv[])
{
    uveziRacune(argc,argv);
}

void uveziRacune(int argc,char* argv[])
{

    DIR *directory;
    struct dirent* file;
    FILE *a;
    char ch;

    if (argc != 2)
    {
        printf("Error\n", argv[0]);
        exit(1);
    }

    directory = opendir("./RACUNI");
    if (directory == NULL)
    {
        printf("Error\n");
        exit(2);
    }
    file=readdir(directory);
    file=readdir(directory);

    while ((file=readdir(directory)) != NULL)
    {
        char c;
        printf("%s\n", file->d_name);
        int i;
        RACUN* pom;
        if(pom=format1(file->d_name,&c))
            sacuvajRacun(pom,c);
        else if(pom=format2(file->d_name,&c))
            sacuvajRacun(pom,c);
        else if(pom=format3(file->d_name,&c))
            sacuvajRacun(pom,c);
        else if(pom=format4(file->d_name,&c))
            sacuvajRacun(pom,c);
    }
    closedir(directory);
}

RACUN* kreirajRacun()
{
    RACUN* racun=(RACUN*)calloc(1,sizeof(RACUN));
    return racun;
}

void dodajProizvod(RACUN* racun,PROIZVOD* proizvod)
{
    racun->proizvodi=(PROIZVOD*)realloc(racun->proizvodi,(racun->n+1)*sizeof(PROIZVOD));
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
    for(i=0; i<(racun->n); i++)
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
    char filepath[100]={0};
    strcpy(filepath,"./RACUNI/");
    strcat(filepath,file);
    printf("%s",filepath);
    int i;
    if(dat=fopen(filepath,"r"))
    {
        RACUN* pomRacun=kreirajRacun();
        pomRacun->n=0;
        char pomString[150],naziv[30],sifra[30];
        int br=0;
        double kolicina,cijena,ukupno;
        //pomRacun->proizvodi=(PROIZVOD*)calloc(pomRacun->n,sizeof(PROIZVOD));
        //pomRacun->kolicina=(double*)calloc(pomRacun->n,sizeof(double));
        for(i=0; i<6; i++)
            fgets(pomString,150,dat);
        int sum=0;
        while(fscanf(dat,"%s %s - %lf - %lf - %lf",sifra,naziv,&kolicina,&cijena,&ukupno)==5)
        {
            if(br==pomRacun->n)
            {
                pomRacun->proizvodi=(PROIZVOD*)realloc(pomRacun->proizvodi,(pomRacun->n+1)*sizeof(PROIZVOD));
                pomRacun->kolicina=(double*)realloc(pomRacun->kolicina,(pomRacun->n+1)*sizeof(double));
                pomRacun->n+=1;
            }
            pomRacun->proizvodi[br].cijena=cijena;
            pomRacun->proizvodi[br].naziv=(char*)calloc(strlen(sifra)+1,1);
            strcpy(pomRacun->proizvodi[br].naziv,sifra);
            pomRacun->kolicina[br]=kolicina;
            sum+=ukupno;
            br++;
        }
        fscanf(dat,"%lf",&ukupno);
        if(ukupno==sum)
            return pomRacun;
        else
        {
            //obrisiRacun(pomRacun); TREBA NAPRAVITI
            return 0;
        }
    }
    else return 0;
}

RACUN* format2(char* file,char* c)
{
    /char naziv[20],pomString[100];
    int sum=0,br=0,i;
    double cijena,ukupno,kolicina,sifra;
    FILE *dat;
    if((dat = fopen(file,"r")))
    {
        RACUN *pomRacun = kreirajRacun();
        pomRacun->n = 1;
        pomRacun->proizvodi = (PROIZVOD*)malloc(pomRacun->n * sizeof(PROIZVOD));
        pomRacun->kolicina = (double*)malloc(pomRacun->n * sizeof(double));
        for(i=0 ; i<9 ; i++)
            fgets(pomString,100,dat);
        while(fscanf(dat,"%s %lf - %lf - %lf - %lf",naziv,&sifra,&kolicina,&cijena,&ukupno)==5)
        {
            if(br==(pomRacun->n-1))
            {
                pomRacun->proizvodi=(PROIZVOD*)realloc(pomRacun->proizvodi,(pomRacun->n+1) * sizeof(PROIZVOD));
                pomRacun->kolicina=(double*)realloc(pomRacun->kolicina,(pomRacun->n+1)*sizeof(double));
                pomRacun->n+=1;
            }
            pomRacun->proizvodi[br].cijena=cijena;
           // strcpy(pomRacun->proizvodi[br].naziv,naziv); Ne radi,treba alocirati prvo
            pomRacun->kolicina[br]=kolicina;
            sum+=ukupno;
            br++;
        }
        fscanf(dat,"%s %lf",pomString, &ukupno);
        if(sum == ukupno)
            return pomRacun;
        else
        {
            //obrisiRacun(pomRacun);
            return 0;
        }
    }

    else return 0;
}

RACUN* format3(char* file,char* c)
{
    char naziv[20],pomString[100];
    int sum=0,br=0,i;
    double cijena,ukupno,kolicina,sifra;
    FILE *dat;
    if((dat = fopen(file,"r")))
    {
        RACUN *pomRacun = kreirajRacun();
        pomRacun->n = 1;
        pomRacun->proizvodi = (PROIZVOD*)malloc(pomRacun->n * sizeof(PROIZVOD));
        pomRacun->kolicina = (double*)malloc(pomRacun->n * sizeof(double));
        for(i=0 ; i<9 ; i++)
            fgets(pomString,100,dat);
        while(fscanf(dat,"%s %lf ====== %lf ====== %lf ====== %lf",naziv,&sifra,&kolicina,&cijena,&ukupno)==5)
        {
            if(br==(pomRacun->n-1))
            {
                pomRacun->proizvodi=(PROIZVOD*)realloc(pomRacun->proizvodi,(pomRacun->n+1) * sizeof(PROIZVOD));
                pomRacun->kolicina=(double*)realloc(pomRacun->kolicina,(pomRacun->n+1)*sizeof(double));
                pomRacun->n+=1;
            }
            pomRacun->proizvodi[br].cijena=cijena;
           // strcpy(pomRacun->proizvodi[br].naziv,naziv); Ne radi,treba alocirati prvo
            pomRacun->kolicina[br]=kolicina;
            sum+=ukupno;
            br++;
        }
        fscanf(dat,"%s %lf",pomString, &ukupno);
        if(sum == ukupno)
            return pomRacun;
        else
        {
            //obrisiRacun(pomRacun);
            return 0;
        }
    }

    else return 0;
}


RACUN* format4(char* file,char* c)
{
   FILE* dat;
    int i;
    if((dat=fopen(file,"r")))
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
                pomRacun->proizvodi=(PROIZVOD*)realloc(pomRacun->proizvodi,(pomRacun->n+1)*sizeof(PROIZVOD));
                pomRacun->kolicina=(double*)realloc(pomRacun->kolicina,(pomRacun->n+1)*sizeof(double));
                pomRacun->n+=1;
            }
            pomRacun->proizvodi[br].cijena=cijena;
            //strcpy(pomRacun->proizvodi[br].naziv,sifra); Ne radi,treba alocirati prvo
            pomRacun->kolicina[br]=kolicina;
            sum+=ukupno;
            br++;
        }
        fscanf(dat,"%lf",&ukupno);
        if(ukupno==sum)
            return pomRacun;
        else
        {
            //obrisiRacun(pomRacun);
            return 0;
        }
    }
    else return 0;
}

void sacuvajRacun(RACUN* racun,char* c)
{
    FILE *dat;
    if(dat=fopen("STORAGE.txt","w"))
    {

        fprintf(dat,"IZNOS : %lf BROJ : %d ",racun->iznos,racun->n);
    }
    fclose(dat);
}
