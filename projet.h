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
typedef struct pile{
    struct pile * suivant;
    pA arbre;
    int modif;
}Pile;

//fonctions generales
type absolu (type a);
type max(type a, type b);
type min(type a, type b);

//fonctions pour les arbres
int estVide(pA a);
int descendance(pA a);
pA rechercheParentCreation(pA a, int id);
pA rechercheParent(pA a, int id);
pA creationArbre(pA a, Elmt* elm, int info);
//pA creationFils (pA papa, pA enfant, int info);
int profondeurDescendance (pA a);

//fonctions pour les piles
Pile * creationPile(pA a);

//fonctions d'equilibrage des AVL
pA rotationDG(pA arbre);
pA rotationSG(pA arbre);
pA rotationSD(pA arbre);
pA rotationGD(pA arbre);
void calculEquilibre (pA a);
pA verifEquilibre (pA a);
pA appelRechercheParentModifEquilibre(pA a, int id);
Pile * rechercheParentModifEquilibre(int id, Pile* pile);


void traitementArbre(char* nomdufichier, int info);
FILE * ouvertureFichierSortie(char* nomdufichierentree);
void ecriture (FILE * fichier, pA arbre);
void parcoursSufixeEcriture(FILE* fichier, pA arbre);
void parcoursInfixeEcriture(FILE* fichier,pA arbre);
