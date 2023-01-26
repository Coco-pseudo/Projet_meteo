#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

typedef float type;
typedef struct element{
    float min;
    float max;
    float somme;
    int nbelmt;
    int station; //peut contenir la date comme chaine de caractere
}Elmt;
typedef struct arbre {
    struct arbre * fd;
    struct arbre * fg;
    struct element * elmt;
    int equilibre;
} Arbre ;
typedef  Arbre* pA;


type absolu (type a);
type max(type a, type b);
int estVide(pA a);
int descendance(pA a);
pA rechercheParentCreation(pA a, int id);
pA rechercheParent(pA a, int id);
//pA creationFils (pA papa, pA enfant, int info);
int profondeurDescendance (pA a);
void calculEquilibre (pA a);
int verifEquilibre (pA a);
pA rechercheParentModifEquilibre(pA a, int id);
void creationArbre(pA a, Elmt* elm, int info);
void traitementAVL(char nomdufichier);