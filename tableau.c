#include "projet.h"

//pour l'instant, on considere que on fait d'abord appel au traitement avl
//pour avoir le nombre de lignes finale
// ou on cree un tableau qui contient des elmts

//tableau de 70 cases: 70 stations en tout


Elmt ** creationTableau(){
    Elmt * Tableau[70];
    return Tableau;
}
int rechercheDichotomique(Elmt * Tableau[70], Elmt * elmt, int * maximum){
    int min = 0;
    int recherchemax = *maximum;
    while(Tableau[(recherchemax+min)/2]->station != elmt->station){
        if(Tableau[(recherchemax+min)/2] == NULL)return ((recherchemax+min)/2);
        if(Tableau[min+1]==Tableau[recherchemax]){
            if (Tableau[min]->station == elmt->station)return min;//seul l'un des deux est utile si il minore ou majore
            if (Tableau[recherchemax]->station == elmt->station)return recherchemax;
            return min;
        }
        if (Tableau[(recherchemax+min)/2]->station < elmt->station){
            min = (recherchemax+min)/2 ;
        }else{
            recherchemax = (recherchemax+min)/2 ;
        }
    }
}
Elmt ** decalageTableau(int debut, Elmt * Tableau[70]){
    Elmt * tmp = Tableau[debut +1];
    Elmt * tmp2 = malloc(sizeof(Elmt));
    Tableau[debut +1]=NULL;
    debut = debut +1;
    while(Tableau[debut]!=NULL || tmp!=NULL){
        Tableau[debut] = tmp2;
        tmp2 = tmp;
        tmp = Tableau[debut + 1];
        debut = debut +1;
    }
    return Tableau;
}
Elmt ** ajoutElmtTableau(Elmt * Tableau [70], Elmt * elmt, int * maximum){
    int i = rechercheDichotomique(Tableau,elmt, maximum);
    if(Tableau[i]->station == elmt->station){
        Tableau[i]->somme = Tableau[i]->somme + elmt->somme;
        Tableau[i]->nbelmt = Tableau[i]->nbelmt + elmt->nbelmt;
        Tableau[i]->min = min(Tableau[i]->min,elmt->min);
        Tableau[i]->max = max(Tableau[i]->max,elmt->max);
    }else{
        Tableau = decalageTableau(i,Tableau)
        *maximum = *maximum + 1;
    }
    return Tableau;
}
Elmt * scanElmt(FILE * fichier);
void parcoursCroissantTableauEcriture(FILE fichier, Elmt * Tableau [70])
    Elmt * scanElmt(FILE fichier)
    traitementTableau(FILE* fichier, Elmt * Tableau ,int mod){
    Elmt * Tableau[70];
    Elmt * test = malloc(sizeof(Elmt));
    int valeur = 0;
    int * maximum = &valeur;
    Tableau[0]=test;
    Elmt * tmp = malloc(sizeof(Elmt));
    while(!feof(fichier)){
        Elmt * tmp = malloc(sizeof(Elmt));
        tmp = scanElmt(fichier, mod);
        Tableau = ajoutElmtTableau(Tableau, tmp, maximum);
    }
    return *Tableau;
}
int main(){
    Elmt * Tableau[70];
    *Tableau = traitementTableau(Tableau);
    return 0;
}
