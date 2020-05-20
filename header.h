/**
 *
 * @author Zsolt Drahos
 * @date 2019.11.29
 *
 */

typedef struct Konyv{
    char *cim;
    char *szerzo;
    char *ev;
    char *tema;
    struct Konyv *kov;
}Konyv;

void kiir(Konyv *eleje);
void lista_hossz(Konyv *eleje);
char *hosszu_sort_olvas();
Konyv *beolvas(Konyv *eleje);
Konyv *fajlbol_olvas(Konyv *eleje);
void felszabadit(Konyv *eleje);
void keres_cim(Konyv *eleje);
void keres_szerzo(Konyv *eleje);
void keres_ev(Konyv *eleje);
void keres_tema(Konyv *eleje);
void keres(Konyv *eleje);
void menu_lista(int menu, Konyv *eleje);
Konyv *torol(Konyv *eleje, int hanyadik);
void hanyadikat_torol(Konyv *eleje);
Konyv *modosit(Konyv *eleje, int hanyadik);
void hanyadikat_modosit(Konyv *eleje);
void mentes(Konyv *eleje);
void menu_kiir();
int hossz(Konyv *eleje);
