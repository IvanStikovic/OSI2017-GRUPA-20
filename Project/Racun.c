#include "Racun.h"

void uveziRacune()
{
    DIR *directory;
    struct dirent* file;
    directory = opendir("./RACUNI");
    if (directory == NULL)
    {
        printf("Error\n");
        return;
    }
    file=readdir(directory);
    file=readdir(directory);
    while ((file=readdir(directory)) != NULL)
    {
        char c='0';
        RACUN* pom;
        if((pom=format1(file->d_name,&c)))
            sacuvajRacun(pom,c);
        else if((pom=format2(file->d_name,&c)))
            sacuvajRacun(pom,c);
        else if((pom=format3(file->d_name,&c)))
            sacuvajRacun(pom,c);
        else if((pom=format4(file->d_name,&c)))
            sacuvajRacun(pom,c);
        //  else if((pom=format5(file->d_name,&c)))
        //      sacuvajRacun(pom,c);
        else if((pom && c=='0'))
            obrisiRacun(&pom);
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
    printf("\n");
    racun->iznos=0.0;
    printf("||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n\n");
    printf("Kupac: %s\n", racun->kupac);
    printf("------------------------------------------------------\n");
    printf("Datum: %d/%d/%d\n", racun->datum.dan,racun->datum.mjesec,racun->datum.godina);
    printf("------------------------------------------------------\n");
    printf("Broj proizvoda na racunu: %d\n", racun->n);
    printf("------------------------------------------------------\n");
    printf("RB. NAZIV PROIZVODA           CIJENA KOLICINA UKUPNO\n");
    printf("--- ------------------------- ------ -------- ------\n");
    for(i=0; i<(racun->n); i++)
    {
        printf("%2d. %-25s %6.2lf %8.2lf %6.2lf\n", i+1, racun->proizvodi[i].naziv, racun->proizvodi[i].cijena*valuta.kurs, racun->kolicina[i], (racun->proizvodi[i].cijena)*(racun->kolicina[i])*valuta.kurs);
        (racun->iznos)+=((racun->proizvodi[i].cijena)*(racun->kolicina[i]));
    }
    printf("------------------------------------------------------\n");
    printf("                                  ____________________ \n");
    printf("\n");
    printf("      HVALA NA POVJERENJU         UKUPAN IZNOS: %.2lf  \n", (racun->iznos)*valuta.kurs);
    printf(" SVE CIJENE SU IZRAZENE U : %s    ____________________\n",valuta.oznaka);
    printf("\n");
    printf("------------------------------------------------------\n\n\n");
}

RACUN* format1(char* file,char* c)
{
    FILE* dat;
    char filepath[100]= {0};
    strcpy(filepath,"./RACUNI/");
    strcat(filepath,file);
    int i;
    if((dat=fopen(filepath,"r")))
    {
        RACUN* pomRacun=kreirajRacun();
        pomRacun->n=0;
        char pomString[150],naziv[30],kupac[30];
        int br=0;
        double sifra,kolicina,cijena,ukupno;
        fscanf(dat,"%s %s\n",pomString,kupac);
        pomRacun->kupac=(char*)calloc(strlen(kupac)+1,sizeof(char));
        strcpy(pomRacun->kupac,kupac);
        fscanf(dat,"%s %d/%d/%d\n",pomString,&pomRacun->datum.dan,&pomRacun->datum.mjesec,&pomRacun->datum.godina);
        for(i=0; i<3; i++)
            fgets(pomString,150,dat);
        int sum=0;
        while(fscanf(dat,"%s %lf - %lf - %lf - %lf",naziv,&sifra,&kolicina,&cijena,&ukupno)==5)
        {
            if(br==pomRacun->n)
            {
                pomRacun->proizvodi=(PROIZVOD*)realloc(pomRacun->proizvodi,(pomRacun->n+1)*sizeof(PROIZVOD));
                pomRacun->kolicina=(double*)realloc(pomRacun->kolicina,(pomRacun->n+1)*sizeof(double));
                pomRacun->n+=1;
            }
            pomRacun->proizvodi[br].cijena=cijena;
            pomRacun->proizvodi[br].sifra=sifra;
            pomRacun->proizvodi[br].naziv=(char*)calloc(strlen(naziv)+1,1);
            strcpy(pomRacun->proizvodi[br].naziv,naziv);
            pomRacun->kolicina[br]=kolicina;
            sum+=ukupno;
            br++;
        }
        fscanf(dat,"%s %lf",pomString,&ukupno);
        if(ukupno==sum)
        {
            *c='s';
            fclose(dat);
            return pomRacun;
        }
        else
        {
            fclose(dat);
            return 0;
        }
    }
    else
        return 0;
}

RACUN* format2(char* file,char* c)
{
    char filepath[100]= {0};
    strcpy(filepath,"./RACUNI/");
    strcat(filepath,file);
    char naziv[20],pomString[100],kupac[20];
    int sum=0,br=0,i;
    double cijena,ukupno,kolicina,sifra;
    FILE *dat;
    if((dat = fopen(filepath,"r")))
    {
        RACUN *pomRacun = kreirajRacun();
        pomRacun->n = 0;
        for(i=0 ; i<5 ; i++)
            fgets(pomString,100,dat);
        fscanf(dat,"%s %s\n",pomString,kupac);
        if(strcmp(pomString,"Proizvod")==0) //PROVJERA da se ne format4 ne pomijesa
            return 0;
        pomRacun->kupac=(char*)calloc(strlen(kupac)+1,sizeof(char));
        strcpy(pomRacun->kupac,kupac);
        for(i=0 ; i<2 ; i++)
            fgets(pomString,100,dat);
        while(fscanf(dat,"%s %lf - %lf - %lf - %lf",naziv,&sifra,&kolicina,&cijena,&ukupno)==5)
        {
            if(br==(pomRacun->n))
            {
                pomRacun->proizvodi=(PROIZVOD*)realloc(pomRacun->proizvodi,(pomRacun->n+1) * sizeof(PROIZVOD));
                pomRacun->kolicina=(double*)realloc(pomRacun->kolicina,(pomRacun->n+1)*sizeof(double));
                pomRacun->n+=1;
            }
            pomRacun->proizvodi[br].cijena=cijena;
            pomRacun->proizvodi[br].sifra=sifra;
            pomRacun->proizvodi[br].naziv=(char*)calloc(strlen(naziv)+1,1);
            strcpy(pomRacun->proizvodi[br].naziv,naziv);
            pomRacun->kolicina[br]=kolicina;
            sum+=ukupno;
            br++;
        }
        fscanf(dat,"%s %lf\n",pomString, &ukupno);
        for(i=0 ; i<2 ; i++)
            fgets(pomString,100,dat);
        fscanf(dat,"%s %d/%d/%d\n",pomString,&pomRacun->datum.dan,&pomRacun->datum.mjesec,&pomRacun->datum.godina);
        if(sum == ukupno)
        {
            *c='s';
            fclose(dat);
            return pomRacun;
        }
        else
        {
            fclose(dat);
            return 0;
        }
    }

    else return 0;
}

RACUN* format3(char* file,char* c)
{
    char filepath[100]= {0};
    strcpy(filepath,"./RACUNI/");
    strcat(filepath,file);
    char naziv[20],pomString[100],kupac[20];
    int sum=0,br=0,i;
    double cijena,ukupno,kolicina,sifra;
    FILE *dat;
    if((dat = fopen(filepath,"r")))
    {
        RACUN *pomRacun = kreirajRacun();
        pomRacun->n = 0;
        for(i=0 ; i<2 ; i++)
            fgets(pomString,100,dat);
        fscanf(dat,"%s %s\n",pomString,kupac);
        pomRacun->kupac=(char*)calloc(strlen(kupac)+1,sizeof(char));
        strcpy(pomRacun->kupac,kupac);
        fscanf(dat,"%s %d/%d/%d\n",pomString,&pomRacun->datum.dan,&pomRacun->datum.mjesec,&pomRacun->datum.godina);
        for(i=0 ; i<4 ; i++)
            fgets(pomString,100,dat);
        while(fscanf(dat,"%s %lf ====== %lf ====== %lf ====== %lf",naziv,&sifra,&kolicina,&cijena,&ukupno)==5)
        {
            if(br==(pomRacun->n))
            {
                pomRacun->proizvodi=(PROIZVOD*)realloc(pomRacun->proizvodi,(pomRacun->n+1) * sizeof(PROIZVOD));
                pomRacun->kolicina=(double*)realloc(pomRacun->kolicina,(pomRacun->n+1)*sizeof(double));
                pomRacun->n+=1;
            }
            pomRacun->proizvodi[br].cijena=cijena;
            pomRacun->proizvodi[br].sifra=sifra;
            pomRacun->proizvodi[br].naziv=(char*)calloc(strlen(naziv)+1,1);
            strcpy(pomRacun->proizvodi[br].naziv,naziv);
            pomRacun->kolicina[br]=kolicina;
            sum+=ukupno;
            br++;
        }
        fscanf(dat,"%s %lf",pomString, &ukupno);
        if(sum == ukupno)
        {
            *c='s';
            fclose(dat);
            return pomRacun;
        }
        else
        {
            fclose(dat);
            return 0;
        }
    }

    else return 0;
}


RACUN* format4(char* file,char* c)
{
    char filepath[100]= {0};
    strcpy(filepath,"./RACUNI/");
    strcat(filepath,file);
    FILE* dat;
    int i;
    if((dat=fopen(filepath,"r")))
    {
        RACUN* pomRacun=(RACUN*)calloc(1,sizeof(RACUN));
        pomRacun->n=0;
        char pomString[150],naziv[30],kupac[20];
        int br=0;
        double kolicina,cijena,ukupno,sifra;
        fscanf(dat,"%s %s\n",pomString,kupac);
        pomRacun->kupac=(char*)calloc(strlen(kupac)+1,sizeof(char));
        strcpy(pomRacun->kupac,kupac);
        fscanf(dat,"%s %d/%d/%d\n",pomString,&pomRacun->datum.dan,&pomRacun->datum.mjesec,&pomRacun->datum.godina);
        for(i=0; i<4; i++)
            fgets(pomString,150,dat);
        int sum=0;
        while(fscanf(dat,"%s %lf - %lf - %lf - %lf",naziv,&sifra,&kolicina,&cijena,&ukupno)==5)
        {
            if(br==(pomRacun->n))
            {
                pomRacun->proizvodi=(PROIZVOD*)realloc(pomRacun->proizvodi,(pomRacun->n+1)*sizeof(PROIZVOD));
                pomRacun->kolicina=(double*)realloc(pomRacun->kolicina,(pomRacun->n+1)*sizeof(double));
                pomRacun->n+=1;
            }
            pomRacun->proizvodi[br].cijena=cijena;
            pomRacun->proizvodi[br].sifra=sifra;
            pomRacun->proizvodi[br].naziv=(char*)calloc(strlen(naziv)+1,1);
            strcpy(pomRacun->proizvodi[br].naziv,naziv);
            pomRacun->kolicina[br]=kolicina;
            sum+=ukupno;
            br++;
        }
        fscanf(dat,"%s %lf",pomString,&ukupno);
        if(ukupno==sum)
        {
            *c='s';
            fclose(dat);
            return pomRacun;
        }
        else
        {
            fclose(dat);
            return 0;
        }
    }
    else
        return 0;
}

RACUN* format5(char* file,char* c)
{
    	char provjera[5];
	int i=0;
	int len = strlen(file);
	for(i=0 ; i<3 ; i++)
		provjera[i] = file[len-3+i];
	if(!strcmp(provjera,"csv"))
	{
    	FILE* dat;
    	char filepath[100]= {0};
    	strcpy(filepath,"./RACUNI/");
    	strcat(filepath,file);
    	if((dat=fopen(filepath,"r")))
    	{
        	RACUN* pomRacun=kreirajRacun();
        	pomRacun->n=0;
        	char pomString[150],kupac[30] = "Nepoznat";
        	int br=0;
        	double sifra,kolicina,cijena,ukupno;
        	pomRacun->kupac=(char*)calloc(strlen(kupac)+1,sizeof(char));
        	strcpy(pomRacun->kupac,kupac);
        	fgets(pomString,150,dat);
        	while(fscanf(dat,"%lf, %lf, %lf, %lf\n",&sifra,&kolicina,&cijena,&ukupno)==4)
        	{
        		char naziv[20] = "Nepoznat";
            	if(br==pomRacun->n)
            	{
                	pomRacun->proizvodi=(PROIZVOD*)realloc(pomRacun->proizvodi,(pomRacun->n+1)*sizeof(PROIZVOD));
                	pomRacun->kolicina=(double*)realloc(pomRacun->kolicina,(pomRacun->n+1)*sizeof(double));
                	pomRacun->n+=1;
            	}
            	pomRacun->proizvodi[br].cijena=cijena;
            	pomRacun->proizvodi[br].sifra=sifra;
            	pomRacun->proizvodi[br].naziv=(char*)calloc(strlen(naziv)+1,1);
            	strcpy(pomRacun->proizvodi[br].naziv,naziv);
            	pomRacun->kolicina[br]=kolicina;
            	br++;
        	}
        	*c = 's';
        	fclose(dat);
        	return pomRacun;
    	}
    	else
    		return 0;
    }
    else
    return 0;
}

void getSifra(FILE *f,char *pom)
{
    char c;
    int i=0;
    do
    {
        c = getc(f);
        if(c == -1)
            return;
        pom[i++] = c;
    }
    while(c != ',');
}

void sacuvajRacun(RACUN* racun,char c)
{
    FILE *dat;
    char validni[100]= {"SKLADISTE.txt"};
    char nevalidni[100]= {"ERROR.txt"};
    char pom[100]= {0};
    if(c=='s')
        strcpy(pom,validni);
    else if(c=='e')
        strcpy(pom,nevalidni);
    if((dat=fopen(pom,"a")))
    {
        int i;
        fprintf(dat,"-------------------------------------------------------------------------\n");
        fprintf(dat,"%s\n","RACUN");
        fprintf(dat,"%s %s\n","KUPAC:",racun->kupac);
        fprintf(dat,"%s %d/%d/%d\n","DATUM:",racun->datum.dan,racun->datum.mjesec,racun->datum.godina);
        fprintf(dat,"%s %d\n","BROJ:",racun->n);
        for(i=0; i<racun->n; i++)
            fprintf(dat,"%s %3.0lf %4.2lf %4.2lf\n",racun->proizvodi[i].naziv,racun->proizvodi[i].sifra,racun->kolicina[i],racun->proizvodi[i].cijena);
        fprintf(dat,"-------------------------------------------------------------------------\n");
        obrisiRacun(&racun);
        fclose(dat);
    }

}

RACUN* ucitajRacune(int* broj)
{
    FILE *dat;
    if((dat=fopen("SKLADISTE.txt","r")))
    {
        RACUN *racuni;
        char pomString[100],kupac[20];
        int br=0;
        while(!feof(dat))
        {
            fgets(pomString,100,dat);
            if(strcmp(pomString,"RACUN\n")==0)
            {
                if(br==0)
                    racuni=(RACUN*)calloc(1,sizeof(RACUN));
                racuni=(RACUN*)realloc(racuni,(br+1)*sizeof(RACUN));
                fscanf(dat,"%s %s\n",pomString,kupac);
                racuni[br].kupac=(char*)calloc(strlen(kupac)+1,sizeof(char));
                strcpy(racuni[br].kupac,kupac);
                fscanf(dat,"%s %d/%d/%d\n",pomString,&racuni[br].datum.dan,&racuni[br].datum.mjesec,&racuni[br].datum.godina);
                fscanf(dat,"%s %d",pomString,&racuni[br].n);
                racuni[br].proizvodi=(PROIZVOD*)calloc(racuni[br].n,sizeof(PROIZVOD));
                racuni[br].kolicina=(double*)calloc(racuni[br].n,sizeof(double));
                racuni[br].iznos=0;
                int j;
                for(j=0; j<racuni[br].n; j++)
                {
                    char naziv[20];
                    fscanf(dat,"%s %lf %lf %lf",naziv,&racuni[br].proizvodi[j].sifra,&racuni[br].kolicina[j],&racuni[br].proizvodi[j].cijena);
                    racuni[br].proizvodi[j].naziv=(char*)calloc(strlen(naziv)+1,sizeof(char));
                    strcpy(racuni[br].proizvodi[j].naziv,naziv);
                    racuni[br].iznos+=racuni[br].kolicina[j]*racuni[br].proizvodi[j].cijena;
                }
                br++;
            }
        }
        *broj=br;
        return racuni;
    }
    else
        return NULL;
}

void obrisiRacune(RACUN *racuni,int broj_racuna)
{
    int i,j;
    for(i=0; i<broj_racuna; i++)
    {
        for(j=0; j<racuni[i].n; j++)
            free(racuni[i].proizvodi[j].naziv);
        free(racuni[i].proizvodi);
        free(racuni[i].kolicina);
        free(racuni[i].kupac);
    }
    free(racuni);
}
void obrisiRacun(RACUN **racun)
{
    int i;
    free((*racun)->kolicina);
    for(i=0; i<(*racun)->n; i++)
        free((*racun)->proizvodi[i].naziv);
    free((*racun)->proizvodi);
    free(*racun);
}
