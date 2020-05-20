#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
    #include <windows.h>
#endif
#include "debugmalloc.h"
#include "econio.h"
#include "header.h"

int main()
{
#ifdef _WIN32
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
#endif

    Konyv *eleje = NULL;
    menu_kiir();
    int menu = 0;
    eleje = fajlbol_olvas(eleje);
    scanf("%d", &menu);
    getchar();
    menu_lista(menu, eleje);
    while (menu != 6)
        {
            menu=0;

            printf("\n\t\t    ");
            econio_textbackground(COL_CYAN);
            econio_textcolor(COL_BLACK);
            printf("Válasszon ismént az alábbi menüpontokból!");
            econio_textbackground(COL_RESET);
            econio_textcolor(COL_RESET);

            printf("\n\t   ");
            econio_textbackground(COL_BROWN);
            econio_textcolor(COL_BLACK);
            printf("1.Új, 2.Listáz, 3.Módosítás, 4.Keresés, 5.Törlés, 6. Kilépés");
            econio_textbackground(COL_RESET);
            econio_textcolor(COL_RESET);
            printf(" \n\n");

            scanf("%d", &menu);
            getchar();
            menu_lista(menu, eleje);
        }

    return 0;
}
