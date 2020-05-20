#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
    #include <windows.h>
#endif
#include "debugmalloc.h"
#include "econio.h"
#include "header.h"

void menu_kiir()        /*ASII ART from https://www.asciiart.eu/*/
{

        econio_set_title("Könyvtár");
        printf("\t         ________________________________________________\n");
        printf("\t________|                                               |_______\n");

        printf("\t\\       |     ");
        printf("KÖNYVTÁR ELEKTRONIKUS NYILVÁNTARTÁSA");

        printf("      |      /\n");
        printf("\t \\      ");

        printf("|                                               |");

        printf("     /\n");

        printf("\t /      |_______________________________________________|     \\\n");
        printf("\t/__________)                                        (__________\\\n");


        printf("\n");
        printf("\t\t    __________________   __________________\n");
        printf("\t\t.-/|                  \\ /                  |\\-.\n");
        printf("\t\t||||                 ME|NÜ                 ||||\n");
        printf("\t\t||||                   |                   ||||\n");
        printf("\t\t||||                   |                   ||||\n");
        printf("\t\t||||    "); printf("1. Új"); printf("          |     ");printf("2.Listáz");printf("      ||||\n");
        printf("\t\t||||                   |                   ||||\n");
        printf("\t\t||||    3.Módosítás    |     4.Keresés     ||||\n");
        printf("\t\t||||                   |                   ||||\n");
        printf("\t\t||||    5.Törlés       |     6.Kilépés     ||||\n");
        printf("\t\t||||                   |                   ||||\n");
        printf("\t\t||||                   |                   ||||\n");
        printf("\t\t||||__________________ | __________________||||\n");
        printf("\t\t||/===================\\|/===================\\||\n");
        printf("\t\t`--------------------~___~-------------------''\n");
        printf("\n");
        printf("\t\t    ");

        econio_textbackground(COL_CYAN);
        econio_textcolor(COL_BLACK);
        printf("Kérem válasszon az alábbi felsorolásból!\n\n");
        econio_textcolor(COL_RESET);
        econio_textbackground(COL_RESET);
        printf("\n");
        econio_textcolor(COL_WHITE);


}

void menu_lista(int menu, Konyv *eleje)
{
    switch(menu){
        case 1: eleje = beolvas(eleje); break;
        case 2: kiir(eleje);  lista_hossz(eleje); break;
        case 3: hanyadikat_modosit(eleje); break;
        case 4: keres(eleje); break;
        case 5: hanyadikat_torol(eleje); break;
        case 6: mentes(eleje); felszabadit(eleje); exit(0); break;
        default:econio_textbackground(COL_RED); printf("Érvénytelen számot adott meg!");econio_textbackground(COL_RESET);break;
    }


}

void kiir(Konyv *eleje)
{
    Konyv *h;
    int i = 1;
    for(h = eleje; h!=NULL; h = h->kov)
    {
        printf("\n ");
        econio_textbackground(COL_LIGHTGRAY);
        econio_textcolor(COL_BLACK);
        printf( "%d. Könyv:",i);
        econio_textbackground(COL_RESET);
        econio_textcolor(COL_RESET);
        printf(" \n Cim: %s \n", h->cim);
        printf(" Szerzo: %s \n", h->szerzo);
        printf(" Ev: %s \n", h->ev);
        printf(" Tema: %s \n", h->tema);
        i++;
    }
    printf("\n");
}

void lista_hossz(Konyv *eleje) {
    /* Végigmegyünk a listán és számoljuk az elemeket */
    int hossz = 0;
    Konyv *p = eleje;
    while (p != NULL) {
        hossz++;
        p = p->kov;
    }
    printf("A nyilvántartásban %d darab könyv található!\n", hossz);
}

int hossz(Konyv *eleje) {
    /* Végigmegyünk a listán és számoljuk az elemeket */
    int hossz = 0;
    Konyv *p = eleje;
    while (p != NULL) {
        hossz++;
        p = p->kov;
    }
    return hossz;
}

void felszabadit(Konyv *eleje)
{
    Konyv *p = eleje;
    while (p != NULL)
    {
        free(p->cim);
        free(p->szerzo);
        free(p->ev);
        free(p->tema);
        Konyv *tmp = p->kov;
        free(p);
        p = tmp;
    }
}

void keres_cim(Konyv *eleje)
{
    printf("Cím: ");
    char *beolvas = hosszu_sort_olvas();
    int i = 1;
    int darab = 0;
    Konyv *h;
    for(h = eleje; h!=NULL; h = h->kov)
    {
        if(!(strstr(h->cim, beolvas) == NULL))
        {
             printf( "\n %d. Könyv: ",i);
             printf( "\n Címe: %s", h->cim );
             printf( "\n Szerző: %s", h->szerzo );
             printf( "\n Megjelenési éve: %s", h->ev );
             printf( "\n Témaja: %s\n", h->tema );
             darab++;
        }
        i++;
    }
    if (darab == 0)
        {econio_textbackground(COL_RED); printf("Ilyen könyv nincs az adatbázisban!");econio_textbackground(COL_RESET);}
    free(beolvas);
}

void keres_szerzo(Konyv *eleje)
{
    printf("Szerző: ");
    char *beolvas = hosszu_sort_olvas();
    int i = 1;
    int darab = 0;
    Konyv *h;
    for(h = eleje; h!=NULL; h = h->kov)
    {
        if(strstr(h->szerzo, beolvas) != NULL)
        {
             printf( "\n %d. Könyv: ",i);
             printf( "\n Címe: %s", h->cim );
             printf( "\n Szerző: %s", h->szerzo );
             printf( "\n Megjelenési éve: %s", h->ev );
             printf( "\n Témaja: %s\n", h->tema );
             darab++;
        }
        i++;
    }
    if (darab == 0)
        {econio_textbackground(COL_RED); printf("Ilyen könyv nincs az adatbázisban!");econio_textbackground(COL_RESET);}
    free(beolvas);
}

void keres_ev(Konyv *eleje)
{
    printf("Év: ");
    char *beolvas = hosszu_sort_olvas();
    int i = 1;
    int darab = 0;
    Konyv *h;
    for(h = eleje; h!=NULL; h = h->kov)
    {
        if(strstr(h->ev, beolvas) != NULL)
        {
             printf( "\n %d. Könyv: ",i);
             printf( "\n Címe: %s", h->cim );
             printf( "\n Szerző: %s", h->szerzo );
             printf( "\n Megjelenési éve: %s", h->ev );
             printf( "\n Témaja: %s\n", h->tema );
             darab++;
        }
        i++;
    }
    if (darab == 0)
        {econio_textbackground(COL_RED); printf("Ilyen könyv nincs az adatbázisban!");econio_textbackground(COL_RESET);}
    free(beolvas);
}

void keres_tema(Konyv *eleje)
{
    printf("Téma: ");
    char *beolvas = hosszu_sort_olvas();
    int i = 1;
    int darab = 0;
    Konyv *h;
    for(h = eleje; h!=NULL; h = h->kov)
    {
        if(strstr(h->tema, beolvas) != NULL)
        {
             printf( "\n %d. Könyv: ",i);
             printf( "\n Címe: %s", h->cim );
             printf( "\n Szerző: %s", h->szerzo );
             printf( "\n Megjelenési éve: %s", h->ev );
             printf( "\n Témaja: %s\n", h->tema );
             darab++;
        }
        i++;
    }
    if (darab == 0)
        {econio_textbackground(COL_RED); printf("Ilyen könyv nincs az adatbázisban!");econio_textbackground(COL_RESET);}
    free(beolvas);
}

void keres(Konyv *eleje)
{
    printf("\n\t\t\t        ");
    econio_textbackground(COL_LIGHTGRAY);
    econio_textcolor(COL_BLACK);
    printf("---Keresés---");
    econio_textbackground(COL_RESET);
    econio_textcolor(COL_RESET);
    printf("\n\n");
    printf("\t1. Cím alapján\n");
    printf("\t2. Szerző alapján\n");
    printf("\t3. Év alapján\n");
    printf("\t4. Téma alapján\n");
    printf("\n\t\t    ");
    econio_textbackground(COL_CYAN);
    econio_textcolor(COL_BLACK);
    printf("Kérem válasszon az alábbi felsorolásból!");
    econio_textbackground(COL_RESET);
    econio_textcolor(COL_RESET);
    printf("\n\n");

    int szam = 0;
    scanf("%d", &szam);
    getchar();

    switch(szam){
        case 1: keres_cim(eleje); break;
        case 2: keres_szerzo(eleje); break;
        case 3: keres_ev(eleje); break;
        case 4: keres_tema(eleje);break;
        default:  econio_textbackground(COL_RED);printf("Érvénytelen számot adott meg!"); econio_textbackground(COL_RESET);break;
    }
}

Konyv *torol(Konyv *eleje, int hanyadik) {
    Konyv *iter, *lemarado;

    iter = eleje;
    lemarado = NULL;
    int i = 1;

    while (iter != NULL) {
        if (i == hanyadik) {
            Konyv *kov = iter->kov;
            if (lemarado    )
                lemarado->kov = kov;
            else
                eleje = kov;

            free(iter);
            iter = kov;
        } else {
            lemarado = iter;
            iter = iter->kov;
        }
        i++;
    }

    return eleje;
}

void hanyadikat_torol(Konyv *eleje)
{
    printf("\n\t\t\t        ");
    econio_textbackground(COL_LIGHTGRAY);
    econio_textcolor(COL_BLACK);
    printf("---Törlés---");
    econio_textbackground(COL_RESET);
    econio_textcolor(COL_RESET);
    printf("\n\n");
    int szam = 1;
    int i = 1;
    printf("Hányadikat szeretné törölni?  ");
    scanf("%d", &szam);
    getchar();

    if (szam <= hossz(eleje))
    {
        Konyv *h;

        for(h = eleje; h!=NULL; h = h->kov)
        {
            if(i==szam)
            {
                 printf( "\n %d. Könyv: ",i);
                 printf( "\n Címe: %s", h->cim );
                 printf( "\n Szerző: %s", h->szerzo );
                 printf( "\n Megjelenési éve: %s", h->ev );
                 printf( "\n Témaja: %s\n", h->tema );
            }
            i++;
        }
        printf("\n");
        econio_textbackground(COL_RED);
        printf("Biztosan ezt szeretné törölni? (igen/nem)");
        econio_textbackground(COL_RESET);
        char c[10] = "";
        scanf("%s", c);
        getchar();

        if (strstr(c, "igen")!= NULL)
            {
                eleje = torol(eleje, szam);
                printf("\nSikeres törlés!\n");
            }
        else{return;}
    }
    else{
        printf("\n");
        econio_textbackground(COL_RED);
        printf("%d. könyv nem létezik, összesen csak %d darab könyv van az adatbázisban!", szam, hossz(eleje));
        econio_textbackground(COL_RESET);
        printf("\n");
        hanyadikat_torol(eleje);
    }
}

void hanyadikat_modosit(Konyv *eleje)
{
    printf("\n\t\t\t        ");
    econio_textbackground(COL_LIGHTGRAY);
    econio_textcolor(COL_BLACK);
    printf("---Módosítás---");
    econio_textbackground(COL_RESET);
    econio_textcolor(COL_RESET);
    printf("\n\n");
    int szam = 1;
    printf("Hányadikat szeretné módosítani? ");
    scanf("%d", &szam);
    getchar();
    int i = 1;
    if (szam <= hossz(eleje))
    {

        Konyv *h;

        for(h = eleje; h!=NULL; h = h->kov)
        {
            if(i==szam)
            {
                 printf( "\n %d. Könyv: ",i);
                 printf( "\n Címe: %s", h->cim );
                 printf( "\n Szerző: %s", h->szerzo );
                 printf( "\n Megjelenési éve: %s", h->ev );
                 printf( "\n Témaja: %s\n", h->tema );
            }
            i++;
        }
        printf("\n");
        econio_textbackground(COL_RED);
        printf("Biztosan ezt szeretné módosítani? (igen/nem)");
        econio_textbackground(COL_RESET);
        char c[10] = "";
        scanf("%s", c);
        getchar();

        printf("\n");
        if (strstr(c, "igen")!= NULL)
           {
                eleje = modosit(eleje, szam);
                eleje = torol(eleje, szam+1);
                printf("\nSikeres módosítás!\n");
           }
        else{return;}
    }
     else{
        printf("\n");
        econio_textbackground(COL_RED);
        printf("%d. könyv nem létezik, összesen csak %d darab könyv van az adatbázisban!", szam, hossz(eleje));
        econio_textbackground(COL_RESET);
        printf("\n");
        hanyadikat_modosit(eleje);
    }
}

Konyv *modosit(Konyv *eleje, int hanyadik) {
    Konyv *iter, *lemarado;
    Konyv *uj = NULL;

    char *becim;
    char *beszerzo;
    char *beev;
    char *betema;
    int i  =1;
    for (iter = eleje, lemarado = NULL;
         iter != NULL;
         lemarado = iter, iter = iter->kov)
    {
        if (i == hanyadik) {

            uj = (Konyv*)malloc(sizeof(Konyv));
            econio_textcolor(COL_YELLOW);

            printf("Cim: ");
            econio_textcolor(COL_RESET);
            becim = hosszu_sort_olvas();
            uj->cim = (char *)malloc((strlen(becim)+1)*sizeof(char));
            strcpy(uj->cim, becim);
            free(becim);
            econio_textcolor(COL_YELLOW);

            printf("Szerzo: ");
            econio_textcolor(COL_RESET);
            beszerzo = hosszu_sort_olvas();
            uj->szerzo = (char *)malloc((strlen(beszerzo)+1)*sizeof(char));
            strcpy(uj->szerzo, beszerzo);
            free(beszerzo);
            econio_textcolor(COL_YELLOW);

            printf("Ev: ");
            econio_textcolor(COL_RESET);
            beev = hosszu_sort_olvas();
            uj->ev = (char *)malloc((strlen(beev)+1)*sizeof(char));
            strcpy(uj->ev, beev);
            free(beev);
            econio_textcolor(COL_YELLOW);

            printf("Tema: ");
            econio_textcolor(COL_RESET);
            betema = hosszu_sort_olvas();
            uj->tema = (char *)malloc((strlen(betema)+1)*sizeof(char));
            strcpy(uj->tema, betema);
            free(betema);

            uj->kov = iter;
            if (lemarado!=NULL)
                lemarado->kov = uj;
            else
                eleje = uj;
        }
        i++;
    }
    return eleje;
}

void mentes(Konyv *eleje)
{
    FILE *file;
    file = fopen("adatok.txt", "wt");
    Konyv *h;
    int i = 1;
    for(h = eleje; h!=NULL; h = h->kov)
    {
        fprintf(file, "%s;", h->cim);
        fprintf(file, "%s;", h->szerzo);
        fprintf(file, "%s;", h->ev);
        fprintf(file, "%s;", h->tema);
        fprintf(file, "\n");
        i++;
    }
    fclose(file);
}
