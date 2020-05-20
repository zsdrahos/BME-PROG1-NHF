#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
    #include <windows.h>
#endif
#include "debugmalloc.h"
#include "econio.h"
#include "header.h"


char *hosszu_sort_olvas() {
    int db = 0;
    char *sor = (char*) malloc(sizeof(char) * 1); /*új karakter tömb*/
    sor[0] = '\0'; /*0. elemének a lezáró nullát adjuk*/
    char ujkar;
    while (scanf("%c", &ujkar) == 1 && ujkar != '\n')  /*beolvasok \n végjelig*/
    {
        char *ujtomb = (char*) malloc(sizeof(char) * (db+1+1));  /* itt a tömb nyújtása */
        for (int i = 0; i < db; ++i)    /*átmásolom a karaktereket*/
            ujtomb[i] = sor[i];
        free(sor);  /*felszabadítom a sor-t*/
        sor = ujtomb;
        ujtomb[db] = ujkar;
        ujtomb[db+1] = '\0';
        ++db;
    }
    return sor;
}

Konyv *beolvas(Konyv *eleje)
{
    FILE *file;
    file = fopen("adatok.txt", "at");
    char *becim;
    char *beszerzo;
    char *beev;
    char *betema;
    Konyv *uj = NULL;
    uj = (Konyv*)malloc(sizeof(Konyv));
    econio_textcolor(COL_YELLOW);

    printf("Cim: ");
    econio_textcolor(COL_RESET);
    becim = hosszu_sort_olvas();
    uj->cim = (char *)malloc((strlen(becim)+1)*sizeof(char));
    strcpy(uj->cim,  becim);
    free(becim);
    fprintf(file, "%s;", uj->cim);
    econio_textcolor(COL_YELLOW);

    printf("Szerző: ");
    econio_textcolor(COL_RESET);
    beszerzo = hosszu_sort_olvas();
    uj->szerzo = (char *)malloc((strlen(beszerzo)+1)*sizeof(char));
    strcpy(uj->szerzo,  beszerzo);
    free(beszerzo);
    fprintf(file, "%s;", uj->szerzo);
    econio_textcolor(COL_YELLOW);

    printf("Év: ");
    econio_textcolor(COL_RESET);
    beev = hosszu_sort_olvas();
    uj->ev = (char *)malloc((strlen(beev)+1)*sizeof(char));
    strcpy(uj->ev,  beev);
    free(beev);
    fprintf(file, "%s;", uj->ev);
    econio_textcolor(COL_YELLOW);

    printf("Téma: ");
    econio_textcolor(COL_RESET);
    betema = hosszu_sort_olvas();
    uj->tema = (char *)malloc((strlen(betema)+1)*sizeof(char));
    strcpy(uj->tema,  betema);
    free(betema);
    fprintf(file, "%s;", uj->tema);

    fprintf(file, "\n");
    fclose(file);

    uj->kov = NULL;
    printf("Hozzáadva!\n");
    if (eleje == NULL)
        return uj;
    else{
        Konyv *mozgo = eleje;
        while (mozgo->kov !=NULL)
            mozgo = mozgo->kov;
        mozgo->kov = uj;
        return eleje;
    }
}

Konyv *fajlbol_olvas(Konyv *eleje) {
    FILE *fp;
    Konyv* utolso = NULL;
    fp = fopen("adatok.txt", "rt");
    if (fp == NULL) {
        perror("Nem sikerult megnyitni a fajlt");
        return NULL;
    }
    char c;
    int sor = 0;
    while((c = fgetc(fp)) != EOF)   /*elmegyünk a fájl végéig*/
        {
            if(c == '\n')       /* megszámolom a sorokat*/
                sor++;
        }
    rewind(fp); /*fájl elejére ugrik*/

    while (sor != 0) /*minden egyes beolvasáskor csökkentem a sor-t */
    {
        char *becim = (char *)malloc(100*sizeof(char));
        char *beszerzo= (char *)malloc(100*sizeof(char));
        char *beev= (char *)malloc(5*sizeof(char));
        char *betema= (char *)malloc(100*sizeof(char));

        fscanf(fp, "%[^;];%[^;];%[^;];%[^;];\n", becim, beszerzo, beev, betema);

        Konyv *uj = (Konyv *) malloc(sizeof(Konyv));
        uj->cim = (char *)malloc((strlen(becim)+1)*(sizeof(char)));
        strcpy(uj->cim, becim);
        free(becim);

        uj->szerzo = (char *)malloc((strlen(beszerzo)+1)*(sizeof(char)));
        strcpy(uj->szerzo, beszerzo);
        free(beszerzo);

        uj->ev = (char *)malloc((strlen(beev)+1)*(sizeof(char)));
        strcpy(uj->ev, beev);
        free(beev);

        uj->tema = (char *)malloc((strlen(betema)+1)*(sizeof(char)));
        strcpy(uj->tema, betema);
        free(betema);

        uj->kov = NULL;
        if (utolso == NULL)
            eleje = uj;
        else
            utolso->kov = uj;
        utolso = uj;
        sor--;
    }
    fclose(fp);

    return eleje;
}
