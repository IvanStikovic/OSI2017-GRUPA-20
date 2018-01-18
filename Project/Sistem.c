#include "Sistem.h"

VALUTA valuta= {"KM",1}; // PODRAZUMIJEVANA VALUTA

void sistemStart()
{
    char c;
    remove("SKLADISTE.txt");
    uveziRacune();
    //loadingGrafika();
    if((c=login()))
        optionMeni(c);
    else
    {
        izlazGrafika();
        return;
    }
    izlazGrafika();
}

char login()
{
    char c,r_mjesto;
    do
    {
        system("cls");
        printf("Unesite username :");
        char username[20],pin[5];
        scanf("%s",username);
        int i=0;
        char pom;
        printf("\nUnesite pin:");
        while(1)
        {
            pom=getch();
            if(pom==ENTER)
            {
                pin[i]='\0';
                break;
            }
            else if(pom==SPACE)
                continue;
            else if(pom==BACKSPACE)
            {
                if(i>0)
                {
                    i--;
                    printf("\b \b");
                }
            }

            else
            {
                pin[i]=pom;
                i++;
                printf("*");
            }
        }
        if((r_mjesto=provjeriNalog(username,pin)))
            return r_mjesto;
        else
        {
            printf("\nPogresan username ili sifra !!!");
            printf("\nZa ponovo logovanje na sistem unesite 1.");
            printf("\nZa prekid prijavljivanja unesite 0.");
            printf("\nVas odabir : \n");
            fflush(stdin);
            scanf(" %c",&c);
        }
    }
    while(c!='0');
    return 0;
}


void pristupNalog()
{
    char c;
    do
    {
        system("cls");
        pristupNalogGrafika();
        fflush(stdin);
        scanf("%c",&c);
        system("cls");
        switch(c)
        {
        case '1':
            dodajNalog();
            break;
        case '2':
            azurirajNalog();
            break;
        case '3':
            brisiNalog();
            break;
        case '0':
            break;
        }
    }
    while(c!='0');
    system("cls");
}

char provjeriNalog(char* usrnm,char* sfr)
{
    char ime[20],prezime[20],username[20],pin[5],radno_mjesto;
    double plata;
    int provjera;
    FILE *dat;
    if((dat=fopen("RADNICI.txt","r")))
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


void optionMeni(char c)
{
    if(c=='a')
        adminMeni();
    else
        radnikMeni();
}

void adminMeni()
{
    system("cls");
    char c;
    do
    {
        adminMeniGrafika();
        fflush(stdin);
        scanf("%c",&c);
        system("cls");
        switch(c)
        {
        case '1':
            pristupNalog();
            break;
        case '2':
            pisiRadnike();
            printf("\n\n\n");
            break;
        case '3':
            evidencijaRobe('0');
            printf("\n\n\n");
            break;
        case '4':
            evidencijaRacuna();
            printf("\n\n\n");
            break;
        case '5':
            prikazKursneListe();
            break;
        case '6':
            pregledPodatakaKupca();
            printf("\n\n\n");
            break;
        case '7':
            evidencijaRobe('p');
            printf("\n\n\n");
            break;
        case '8':
            pregledStanjaMjesec();
            printf("\n\n\n");
            break;
        case '0':
            break;
        }
    }
    while(c!='0');
}

void radnikMeni() //Dane ZAVRSENO!!! TREBA PREGLEDATI
{
    system("cls");
    char c;
    do
    {
        system("cls");
        radnikMeniGrafika();
        fflush(stdin);
        scanf("%c",&c);
        switch(c)
        {
        case '1':
            evidencijaRobe('0');
            break;
        case '2':
            pregledPodatakaKupca();
            break;
        case '3':
            evidencijaRobe('p');
            break;
        case '4':
            evidencijaRacuna();
            break;
        case '5':
            pregledStanjaMjesec();
            break;
        case '0':
            break;
        }
    }
    while(c!='0');
}

void evidencijaRobe(char c)
{
    int i,j,k,p,br=0,broj_racuna;
    RACUN* racuni=ucitajRacune(&i);
    broj_racuna=i;
    PROIZVOD* proizvodi=(PROIZVOD*)calloc(1,sizeof(PROIZVOD));
    double* kolicina=(double*)calloc(1,sizeof(double));
    for(j=0; j<i; j++)
    {
        for(k=0; k<racuni[j].n; k++)
        {
            int provjera=0;
            for(p=0; p<=br; p++)
                if(racuni[j].proizvodi[k].sifra==proizvodi[p].sifra && br!=0)
                {
                    kolicina[p]+=racuni[j].kolicina[k];
                    provjera=1;
                }
            if(provjera!=1)
            {
                if(br==0)
                {
                    proizvodi=(PROIZVOD*)calloc(br+1,sizeof(PROIZVOD));
                    kolicina=(double*)calloc(br+1,sizeof(double));
                }
                else
                {
                    proizvodi=(PROIZVOD*)realloc(proizvodi,br*sizeof(PROIZVOD));
                    kolicina=(double*)realloc(kolicina,br*sizeof(double));
                }
                proizvodi[br].naziv=(char*)calloc(strlen(racuni[j].proizvodi[k].naziv)+1,1);
                strcpy(proizvodi[br].naziv,racuni[j].proizvodi[k].naziv);
                proizvodi[br].cijena=racuni[j].proizvodi[k].cijena;
                proizvodi[br].sifra=racuni[j].proizvodi[k].sifra;
                kolicina[br]=racuni[j].kolicina[k];
                br++;
            }
        }
    }
    if(c=='p')
    {
        char pom,naziv[20]= {0};
        double sifra;
        do
        {
            printf("\nPretragu vrsite po : ");
            printf("\n1. Sifri");
            printf("\n2. Nazivu");
            printf("\n Vasa opcija : ");
            fflush(stdin);
            scanf(" %c",&pom);
            if(pom=='1' || pom=='2')
                break;
            else
                printf("\nPogresan unos!\nMolimo unesite opet!\n");
        }
        while(pom!='1' || pom!='2');
        fflush(stdin);
        if(pom=='1')
        {
            int p1=0;
            printf("\nUnesite sifru : ");
            scanf("%lf",&sifra);
            for(i=0; i<br; i++)
                if(sifra==proizvodi[i].sifra)
                {
                    printf("==================================================================\n");
                    printf("RB. NAZIV PROIZVODA              CIJENA     KOLICINA        UKUPNO\n");
                    printf("\n%2d. %-25s %6.2lf %s %11.2lf %9.2lf %3s\n",1,proizvodi[i].naziv,proizvodi[i].cijena*valuta.kurs,valuta.oznaka,kolicina[i],proizvodi[i].cijena*kolicina[i]*valuta.kurs,valuta.oznaka);
                    printf("==================================================================\n");
                    p1++;
                }
            if(p1==0)
                printf("\nNema proizvoda sa trazenom sifrom na stanju !");
        }
        if(pom=='2')
        {
            int p2=0;
            printf("\nUnesite naziv : ");
            scanf("%s",naziv);
            for(i=0; i<br; i++)
                if(strcmp(naziv,proizvodi[i].naziv)==0)
                {
                    printf("==================================================================\n");
                    printf("RB. NAZIV PROIZVODA              CIJENA     KOLICINA        UKUPNO\n");
                    printf("\n%2d. %-25s %6.2lf %s %11.2lf %9.2lf %3s\n",1,proizvodi[i].naziv,proizvodi[i].cijena*valuta.kurs,valuta.oznaka,kolicina[i],proizvodi[i].cijena*kolicina[i]*valuta.kurs,valuta.oznaka);
                    printf("==================================================================\n");
                    p2++;
                }
            if(p2==0)
                printf("\nNema proizvoda sa trazenim nazivom na stanju !");
        }
    }
    else
    {
        printf("PREGLED SVIH PROIZVODA : \n\n");
        printf("==================================================================\n");
        printf("RB. NAZIV PROIZVODA              CIJENA     KOLICINA        UKUPNO\n");
        for(i=0; i<br; i++)
            printf("\n%2d. %-25s %6.2lf %s %11.2lf %9.2lf %3s\n",i+1,proizvodi[i].naziv,proizvodi[i].cijena*valuta.kurs,valuta.oznaka,kolicina[i],proizvodi[i].cijena*kolicina[i]*valuta.kurs,valuta.oznaka);
        printf("==================================================================\n");
    }
    obrisiRacune(racuni,broj_racuna);
    for(i=0;i<br;i++)
        free(proizvodi[i].naziv);
    free(proizvodi);
    free(kolicina);

}
void evidencijaRacuna()
{
    int broj_racuna,j;
    RACUN* racuni=ucitajRacune(&broj_racuna);
    for(j=0; j<broj_racuna; j++)
        pisiRacun(&racuni[j]);
    obrisiRacune(racuni,broj_racuna);
}

void prikazKursneListe()
{
    printf("Izaberite valutu sistema : ");
    printf("\n1. KM");
    printf("\n2. RSD");
    printf("\n3. EU");
    printf("\n4. USD");
    printf("\nVas izbor : ");
    char c;
    fflush(stdin);
    scanf(" %c",&c);
    switch(c)
    {
    case '1':
        valuta.kurs=1;
        strcpy(valuta.oznaka,"KM");
        break;
    case '2':
        valuta.kurs=60.5213;
        strcpy(valuta.oznaka,"RSD");
        break;
    case '3':
        valuta.kurs=0.51129;
        strcpy(valuta.oznaka,"EU");
        break;
    case '4':
        valuta.kurs=0.62725;
        strcpy(valuta.oznaka,"USD");
        break;
    default:
        break;
    }
}

void pregledPodatakaKupca()
{
    char kupac[20]= {0};
    printf("\nUnesite ime kupca : ");
    scanf("%s",kupac);
    int broj_racuna,br=0,i;
    RACUN* racuni=ucitajRacune(&broj_racuna);
    for(i=0; i<broj_racuna; i++)
        if(strcmp(kupac,racuni[i].kupac)==0)
        {
            pisiRacun(&racuni[i]);
            br++;
        }
    if(br==0)
        printf("\nNema racuna sa trazenim kupcem !");
    obrisiRacune(racuni,broj_racuna);
}

void pregledStanjaMjesec()
{
    int i,broj_racuna,mjesec;
    double sum=0;
    RACUN* racuni=ucitajRacune(&broj_racuna);
    printf("\nUnesite redni broj mjeseca : ");
    scanf("%d",&mjesec);
    for(i=0; i<broj_racuna; i++)
        if(racuni[i].datum.mjesec==mjesec)
        {
            sum+=racuni[i].iznos;
        }
    if(sum==0)
        printf("\n Nema racuna sa trazenim mjesecom !");
    else
        printf("Presjek za %d mjesec iznosi : %8.3lf %s (bez PDV-a)",mjesec,sum*valuta.kurs,valuta.oznaka);

    obrisiRacune(racuni,broj_racuna);
}


int brojRadnika()
{
    FILE *fp;
    int br=0,p;
    double plata;
    char ime[20],prezime[20],username[20],pin[5],radno_mjesto;
    if((fp=fopen("RADNICI.txt","r")))
    {
        do
        {
            p=fscanf(fp,"%s %s %lf %s %s %c",ime,prezime,&plata,username,pin,&radno_mjesto);
            if(p==6)
                br++;
        }
        while(p==6);
        fclose(fp);
    }
    return br;
}

void sacuvajNalog(RADNIK *rad)
{
    FILE *dat;
    if((dat = fopen("RADNICI.TXT","a ")))
    {
        fprintf(dat,"%s %s %lf %s %s %c\n",rad->osoba->ime, rad->osoba->prezime, rad->osoba->plata, rad->username, rad->pin, rad->radno_mjesto);
        //printf("Nalog je uspjesno kreiran i sacuvan!\n");
        fclose(dat);
        return;
    }
    else
        printf("Nalog nije uspjesno kreiran i sacuvan, greska prilikom cuvanja naloga u bazi.\n");
}
//FUNKCIJA KOJA ALOCIRA  RADNIKA NA OSNOVU PARAMETARA
RADNIK* kopirajRadnika(char *ime, char *prezime, double plata, char *username, char *pin, char rmjesto)
{
    RADNIK *novi = (RADNIK*)malloc(sizeof(RADNIK));
    novi->osoba = (OSOBA*)malloc(sizeof(OSOBA));
    novi->osoba->ime = (char*)calloc(strlen(ime)+1,sizeof(char));
    novi->osoba->prezime = (char*)calloc(strlen(prezime)+1, sizeof(char));
    novi->username=(char*)calloc(strlen(username)+1, sizeof(char));
    strcpy(novi->osoba->ime,ime);
    strcpy(novi->osoba->prezime,prezime);
    novi->osoba->plata = plata;
    strcpy(novi->username,username);
    novi->radno_mjesto = rmjesto;
    strcpy(novi->pin,pin);
    return novi;

}

//FUNKCIJA KOJA UCITAVA RADNIKE IZ DATOTEKE U DINAMICKI NIZ
RADNIK** ucitajRadnike()
{
    char ime[20],prezime[20],username[20],pin[5],radno_mjesto;
    double plata;
    int provjera,br_radnika;
    FILE *dat;
    br_radnika = brojRadnika();
    RADNIK **radnici = (RADNIK**)malloc((br_radnika) * sizeof(RADNIK*));
    if((dat=fopen("RADNICI.txt","r")))
    {
        int i;
        for( i=0; i<br_radnika; i++)
        {
            provjera=fscanf(dat,"%s %s %lf %s %s %c",ime,prezime,&plata,username,pin,&radno_mjesto);
            if(provjera==6)
                radnici[i] = kopirajRadnika(ime,prezime,plata,username,pin,radno_mjesto);
        }
        fclose(dat);
    }
    return radnici;
}

void pisiRadnike()
{
    RADNIK** r=ucitajRadnike();
    int broj=brojRadnika();
    int i;

    printf("========== =============== =============== ==== ======== ===============\n");
    printf("IME        PREZIME         USERNAME        PIN  PLATA    VRSTA KORISNIKA\n");
    printf("========== =============== =============== ==== ======== ===============\n");
    for(i=0; i<broj; i++)
    {
        printf("%-10s %-15s %-15s %-4s %8.2lf ",r[i]->osoba->ime,r[i]->osoba->prezime,r[i]->username,r[i]->pin,r[i]->osoba->plata);
        if(r[i]->radno_mjesto=='a')
            printf("Administrator\n");
        else
            printf("Analiticar\n");

    }
    printf("======================================================================\n");
}


//FUNKCIJA ZA CUVANJE NALOGA U DATOTECI
void dodajNalog()
{
    RADNIK *novi = kreirajRadnika();
    sacuvajNalog(novi);  //FUNKCIJA KOJA DODAJE RADNIKA U DATOTEKU
    obrisiRadnika(novi);    //FUNKCIJA KOJA DEALOCIRA SVE DIJELOVE RADNIKA
    return;
}

//FUNKCIJA BRISE NALOG IZ FAJLA
void brisiNalog()
{
    int i;
    char username[20];
    printf("Unesite username radnika ciji nalog zelite obrisati:");
    scanf("%s",username);
    RADNIK **radnici = ucitajRadnike();
    int broj = brojRadnika();
    remove("RADNICI.txt");
    for(i=0 ; i<broj ; i++)
    {
        if(strcmp(radnici[i]->username, username))
            sacuvajNalog(radnici[i]);
        obrisiRadnika(radnici[i]);
    }
    free(radnici);
    return ;
}

//FUNKCIJA AZUIRRA ODREDJENI NALOG U FAJLU
void azurirajNalog()
{
    FILE *dat;
    int br_radnika,provjera,i=0,pom1=0;
    char pom[20],ime[20],prezime[20],username[20],pin[5],radno_mjesto;
    double plata;
    printf("Unesite username naloga koji zelite da azurirate!\n");
    scanf("%s",pom);
    br_radnika=brojRadnika();
    RADNIK *radnici[br_radnika];
    if((dat=fopen("RADNICI.txt","r")))
    {
        for(i=0; i<br_radnika; i++)
        {
            provjera=fscanf(dat,"%s %s %lf %s %s %c",ime,prezime,&plata,username,pin,&radno_mjesto);
            if(provjera==6)
                radnici[i] = kopirajRadnika(ime,prezime,plata,username,pin,radno_mjesto);
        }
        fclose(dat);
    }
    for(i=0; i<br_radnika; i++)
    {
        if(strcmp(pom,radnici[i]->username)==0)
        {
            printf("Unesite ime:");
            scanf("%s",ime);
            printf("Unesite prezime:");
            scanf("%s",prezime);
            printf("Unesite platu:");
            scanf("%lf",&plata);
            printf("Unesite username:");
            scanf("%s",username);
            printf("Unesite pin:");
            scanf("%s",pin);
            fflush(stdin);
            printf("Unesite radno mjesto:");
            scanf("%c",&radno_mjesto);
            pom1++;
            obrisiRadnika(radnici[i]);
            radnici[i] = kopirajRadnika(ime,prezime,plata,username,pin,radno_mjesto);
        }
    }
    if(pom1)
    {
        if((dat=fopen("RADNICI.txt","w")))
        {
            for(i=0; i<br_radnika; i++)
            {
                fflush(stdin);
                fprintf(dat,"%s %s %lf %s %s %c\n",radnici[i]->osoba->ime,radnici[i]->osoba->prezime,radnici[i]->osoba->plata,radnici[i]->username,radnici[i]->pin,radnici[i]->radno_mjesto);

            }
            fclose(dat);
        }
        printf("Nalog '%s' uspjesno azuriran!\n",pom);
    }

    else
        printf("Greska pri azuriranju !Nalog '%s' nije azuriran jer ne postoji u bazi podataka!\n",pom);

}//#ByIgorS&RH


void adminMeniGrafika()
{
    printf(" Dobrodosli u administratorski meni\n");
    printf("Molimo unesite broj opcije koju zelite:\n ");
    printf("             MENI:             \n");
    printf("1.Pristup korisnickim nalozima\n");
    printf("2.Pristup evidenciji zaposlenih\n");
    printf("3.Evidencija robe --- RIJETKO PUKNE\n");
    printf("4.Evidencija racuna\n");
    printf("5.Prikaz kursne liste\n");
    printf("6.Pregled podataka o kupcu\n");
    printf("7.Pregled proizvoda --- RIJETKO PUKNE\n");
    printf("8.Mjesecni presjek \n");
    printf("----------------------------------------\n");
    printf("IZLAZ('0')\n");
    printf("\n\nVas izbor :");
}

void radnikMeniGrafika()
{
    printf("Dobrodosli u analiticki meni!\n");
    printf("Molimo vas unesite broj opcije koju zelite: \n");
    printf("         MENI:        \n");
    printf("1.Evidencija robe --- DOLAZI NA SLJEDECEM UPDATE-u\n");
    printf("2.Pregled podataka o kupcu --- DOLAZI NA SLJEDECEM UPDATE-u\n");
    printf("3.Pregled proizvod --- DOLAZI NA SLJEDECEM UPDATE-u\n");
    printf("4.Evidencija racuna\n");
    printf("5.Mjesecni presjek --- DOLAZI NA SLJEDECEM UPDATE-u\n");
    printf("------------------------------------------------\n");
    printf("IZLAZ('0')");
    printf("\n\nVas izbor :");
}

void pristupNalogGrafika() // PRIKA
{
    printf("Molimo vas unesite broj opcije za pristup nalogu:\n");
    printf("      MENI\n");
    printf("1. Dodaj nalog\n");
    printf("2. Azuriraj nalog\n");
    printf("3. Brisi nalog\n");
    printf("------------------------\n");
    printf("IZLAZ('0')\n");
    printf("\n\nVas izbor :");
}


void loadingGrafika()
{
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("                                            [                   ] 0%% ");
    Sleep(500);
    printf("\r                                            [=                  ] 10%% ");
    Sleep(500);
    printf("\r                                            [= =                ] 20%% ");
    Sleep(500);
    printf("\r                                            [= = =              ] 30%% ");
    Sleep(500);
    printf("\r                                            [= = = =            ] 40%% ");
    Sleep(500);
    printf("\r                                            [= = = = =          ] 50%% ");
    Sleep(500);
    printf("\r                                            [= = = = = =        ] 60%% ");
    Sleep(500);
    printf("\r                                            [= = = = = = =      ] 70%% ");
    Sleep(500);
    printf("\r                                            [= = = = = = = =    ] 80%% ");
    Sleep(500);
    printf("\r                                            [= = = = = = = = =  ] 90%% ");
    Sleep(500);
    printf("\r                                            [= = = = = = = = = =] 100%% ");

    system("cls");

    char pom[11]="DOBRODOSLI";
    int i;
    Sleep(1000);

    printf("\n\n\n\n\n\n\n");

    printf("                                          * *    * *   * * *  \n");
    Sleep(350);
    printf("                                         *   *  *   *    *    \n");
    Sleep(350);
    printf("                                         *   *  * * *    *    \n");
    Sleep(350);
    printf("                                          *     *   *    *    \n");
    Sleep(350);
    printf("                                            *   *   *    *    \n");
    Sleep(350);
    printf("                                         *   *                \n");
    Sleep(350);
    printf("                                         *   * ");
    Sleep(350);

    printf("S ");
    Sleep(200);
    printf("0 ");
    Sleep(200);
    printf("F ");
    Sleep(200);
    printf("T ");
    Sleep(200);
    printf("V ");
    Sleep(200);
    printf("E ");
    Sleep(200);
    printf("R  \n");
    Sleep(200);
    printf("                                          * *  ");
    Sleep(350);
    Sleep(1000);
    system("cls");
    printf("\n\n\n\n\n\n\n\n\n\n\n\n                              \t\t");
    for(i=0; i<10; i++)
    {
        printf("%c ",pom[i]);
        Sleep(100);
    }

}

void ispisLogo()
{
    printf("\n\n\n\n\n\n\n\n");
    printf("                                          * *    * *   * * *  \n");
    printf("                                         *   *  *   *    *    \n");
    printf("                                         *   *  * * *    *    \n");
    printf("                                          *     *   *    *    \n");
    printf("                                            *   *   *    *    \n");
    printf("                                         *   *                \n");
    printf("                                         *   * ");
    printf("S ");
    printf("0 ");
    printf("F ");
    printf("T ");
    printf("V ");
    printf("E ");
    printf("R  \n");
    printf("                                          * *  ");
}


void izlazGrafika()
{
    char pom[11]="DOVIDJENJA";
    int i;
    Sleep(500);
    for(i=0;i<3;i++)
    {
        printf("Sistem se gasi");ispisLogo();Sleep(500);system("cls");
        printf("Sistem se gasi .");ispisLogo();Sleep(500);system("cls");
        printf("Sistem se gasi . .");ispisLogo();Sleep(500);system("cls");
        printf("Sistem se gasi . . .");ispisLogo();Sleep(500);system("cls");
    }
    Sleep(200);
    printf("\n\n\n\n\n\n\n\n\n\n\n\n                                         ");
    for(i=0;i<10;i++)
    {
        printf("%c ",pom[i]);
        Sleep(100);
    }
    printf("!");


    //IGAC OVDE UBACI
}
