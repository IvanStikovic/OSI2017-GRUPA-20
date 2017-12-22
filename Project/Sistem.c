#include "Sistem.h"

void obrisiDatoteku()
{
	FILE *dat;
	if(dat = fopen("RADNICI.TXT","w"))
		fclose(dat);
}

void oslobodi(RADNIK *rad)
{

    free(rad->osoba->ime);
    free(rad->osoba->prezime);
    free(rad->username);
}

int brojRadnika()
{
    FILE *fp;
    int br=0,p;
    double plata;
    char pom[20],ime[20],prezime[20],username[20],pin[5],radno_mjesto;
    if(fp=fopen("RADNICI.txt","r"))
    {
        do
        {
            p=fscanf(fp,"%s %s %lf %s %s %c",ime,prezime,&plata,username,pin,&radno_mjesto);
            if(p==6)
                br++;
        }while(p==6);
        fclose(fp);
    }
    return br;
}

void sacuvajNalog(RADNIK *rad)
{
    FILE *dat;
    if(dat = fopen("RADNICI.TXT","a "))
    {
        fprintf(dat,"%s %s %lf %s %s %c\n",rad->osoba->ime, rad->osoba->prezime, rad->osoba->plata, rad->username, rad->pin, rad->radno_mjesto);
        printf("Nalog je uspjesno kreiran i sacuvan!\n");
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
	if(dat=fopen("RADNICI.txt","r"))
	{
		for(int i=0; i<br_radnika; i++)
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
    for(i=0;i<broj;i++)
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
    oslobodi(novi);    //FUNKCIJA KOJA DEALOCIRA SVE DIJELOVE RADNIKA
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
	obrisiDatoteku();
	for(i=0 ; i<broj ; i++)
		{
			if(strcmp(radnici[i]->username, username))
				sacuvajNalog(radnici[i]);
			oslobodi(radnici[i]);
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
    if(dat=fopen("RADNICI.txt","r"))
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
            	oslobodi(radnici[i]);
            	radnici[i] = kopirajRadnika(ime,prezime,plata,username,pin,radno_mjesto);
        	}
    }
    if(pom1)
    {
        if(dat=fopen("RADNICI.txt","w"))
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


void sistemStart()
{
    char c;
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
    }
    while(c);
    return 0;
}


void pristupNalog()
{
    char c;
    do
    {
        pristupNalogGrafika();
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
    while(c);
}

char provjeriNalog(char* usrnm,char* sfr)
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
            pristupNalog();
            break;
        case '2':
            evidencijaZaposlenih();
            break;
        case '3':
            evidencijaRobe();
            break;
        case '4':
            evidencijaRacuna();
            break;
        case '5':
            prikazKursneListe();
            break;
        case '6':
            pregledPodatakaKupca();
            break;
        case '7':
            pregledProizvod();
            break;
        case '8':
            pregledStanjaMjesec();
            break;
        case '0':
            break;
        }
    }
    while(c);
        izlazGrafika();
}

void radnikMeni() //Dane ZAVRSENO!!! TREBA PREGLEDATI
{
    char c;
    do
    {
        radnikMeniGrafika();
        scanf("%c",&c);
        switch(c)
        {
        case '1':
            evidencijaRobe();
            break;
        case '2':
            pregledPodatakaKupca();
            break;
        case '3':
            pregledProizvod();
            break;
        case '4':
            citanjeRacuna();
            break;
        case '5':
            pregledStanjaMjesec();
            break;
        case '0':
            break;
        }
    }
    while(c);
        izlazGrafika();
}

void adminMeniGrafika()
{
    printf(" Dobrodosli u administratorski meni\n");
    printf("Molimo unesite broj opcije koju zelite:\n ");
    printf("             MENI:             \n")
    printf("1.Pristup korisnickim nalozima\n");
    printf("2.Pristup evidenciji zaposlenih\n");
    printf("3.Evidencija robe\n");
    printf("4.Evidencija racuna\n");
    printf("5.Prikaz kursne liste\n");
    printf("6.Pregled podataka o kupcu\n");
    printf("7.Pregled proizvoda\n");
    printf("8.Mjesecni presjek\n");
    printf("----------------------------------------\n");
    printf("IZLAZ('0')\n");
}

void radnikMeniGrafika()
{
    printf("Dobrodosli u analiticki meni!\n");
    printf("Molimo vas unesite broj opcije koju zelite: \n");
    printf("         MENI:        \n")
    printf("1.Evidencija robe\n");
    printf("2.Pregled podataka o kupcu\n");
    printf("3.Pregled proizvod\n");
    printf("4.Citanje racuna\n");
    printf("5.Mjesecni presjek");
    printf("------------------------------------------------\n");
    printf("IZLAZ('0')");
}

void pristupNalogGrafika() // PRIKA ZAVRSIO - OBAVEZNO PREGLEDATI !
{
    printf("Molimo vas unesite broj opcije za pristup nalogu:\n");
    printf("      MENI\n");
    printf("1. Dodaj nalog\n");
    printf("2. Azuriraj nalog\n");
    printf("3. Brisi nalog\n");
    printf("------------------------\n");
    printf("IZLAZ('0')\n");
}
