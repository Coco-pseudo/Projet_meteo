#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef int type;
typedef struct elmt{
    float min;
    float max;
    float somme;
    int nbelmt;
    int station; //peut contenir la date comme chaine de caractere
}Elmt;
typedef struct arbre {
    struct arbre * fd;
    struct arbre * fg;
    Elmt elmt;
    int equilibre;
} Arbre ;
typedef  Arbre* pA;


type absolu (type a);
int max(type a, type b);
int estVide(pA a);
int descendance(pA a);
pA rechercheParentCreation(pA a, type e);
pA rechercheParent(pA a, type e)
pA creationFils (pA papa, pA enfant, int info);
int profondeurDescendance (pA a);
void calculEquilibre (pA a);
int verifEquilibre (pA a);
pA rechercheParentModifEquilibre(pA a, type e);
void creationArbre(pA a, type elmt, int info);