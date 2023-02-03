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
    long station; //peut contenir la date comme chaine de caractere
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

//===========================================================================
//projet.c

//fonctions generales
type absolu (type a);
type max(type a, type b);
type min(type a, type b);

//fonctions pour les arbres
int estVide(pA a);
int descendance(pA a);
pA rechercheParentCreation(pA a, long id);
//pA rechercheParent(pA a, long id);
pA creationArbre(pA a, Elmt* elm, int info, int mod);
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
pA appelRechercheParentModifEquilibre(pA a, long id);
Pile * rechercheParentModifEquilibre(long id, Pile* pile);


void traitementArbre(char* nomdufichier, int info, int mod);
FILE * ouvertureFichierSortie(char* nomdufichierentree, int info);
void ecriture (FILE * fichier, Elmt * elmt, int mod, int* num, int file);
void parcoursSufixeEcriture(FILE* fichier, pA arbre, int mod, int * num, int file);
void parcoursInfixeEcriture(FILE* fichier,pA arbre, int mod, int* num, int file);
void parcoursInfixe(pA arbre);

//===========================================================================================
//tableau.c

Elmt ** creationTableau();
int maxint(int a, int b);
int minint(int a, int b);
int rechercheDichotomique(Elmt * Tableau[70], Elmt * elmt, int mod, int * maximum);
Elmt ** decalageTableau(int debut, Elmt * Tableau[70]);
Elmt ** ajoutElmtTableau(Elmt * Tableau [70], Elmt * elmt, int mod, int * maximum);
Elmt * scanElmt(FILE * fichier, int mod);
void parcoursCroissantTableauEcriture(FILE* fichier, Elmt * Tableau [70],int mod, int file);
void parcoursDecroissantTableauEcriture(FILE* fichier, Elmt * Tableau [70],int mod, int file);
Elmt ** traitementTableau(FILE* fichier, Elmt * Tableau[70] ,int mod);
void appelTraitementTableau(char* nomdufichier, int mod);