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
    if(mod!=7){
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
      }else{
        while(Tableau[(recherchemax+min)/2]->min != elmt->min){
            if(Tableau[(recherchemax+min)/2] == NULL)return ((recherchemax+min)/2);
            if(Tableau[min+1]==Tableau[recherchemax]){
                if (Tableau[min]->min == elmt->min)return min;//seul l'un des deux est utile si il minore ou majore
                if (Tableau[recherchemax]->min == elmt->min)return recherchemax;
                return min;
            }
            if (Tableau[(recherchemax+min)/2]->min < elmt->min){
              min = (recherchemax+min)/2 ;
            }else{
              recherchemax = (recherchemax+min)/2 ;
            }
        }
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
    int i = rechercheDichotomique(Tableau,elmt, maximum, mod);
    if(mod !=7){
      if(Tableau[i]->station == elmt->station){
        if (mod == 1){
          Tableau[i]->somme = Tableau[i]->somme + elmt->somme;
          Tableau[i]->nbelmt = Tableau[i]->nbelmt + elmt->nbelmt;
          Tableau[i]->min = min(Tableau[i]->min,elmt->min);
          Tableau[i]->max = max(Tableau[i]->max,elmt->max);
        }
      }else{
        Tableau = decalageTableau(i,Tableau)
        *maximum = *maximum + 1;
      }
    }else{
      if(Tableau[i]->min == elmt->min){

      }
    }
    return Tableau;
}
Elmt * scanElmt(FILE * fichier);
Elmt * elmt = malloc(sizeof(Elmt));
switch (mod){
  case (1) :
  if(! feof(fichierEntree)){
      fscanf(fichierEntree, "%d", &elmt->station);
      //printf("%d \n", elmt1->station);
      //printf("%c \n", elmt1->station);
      a = fgetc(fichierEntree);//passe le separateur
      if(a != '\n' && a != EOF && a != ' '){
          if(! feof(fichierEntree)){
              a = fgetc(fichierEntree);
              if (a != '\n' && a != ' '){
                  fseek(fichierEntree,SEEK_CUR,-1);
                  fscanf(fichierEntree, "%f", &elmt->somme);
                  //printf("%d, %f \n", tmp->station, tmp->somme);
                  elmt->nbelmt = 1;
                  elmt->min = elmt1->somme;
                  elmt->max = elmt1->somme;
                  return elmt;
              }
          }
      }
  }
  break;
  case (2) :
  break;
  case (3) :
  break;
  case (4) :
  break;
  case (5) :
  break;
  case (6) :
  break;
  case(7) : //cas du deuxieme tri avec
  if(! feof(fichier)){
      fscanf(fichier, "%f", &elmt->max);// prend la longitude
      //printf("%d \n", elmt1->station);
      //printf("%c \n", elmt1->station);
      if(! feof(fichier)){
          a = fgetc(fichier);
          if (a != '\n' && a != ' '){
              fseek(fichier,SEEK_CUR,-1);
              fscanf(fichier, "%f", &elmt->somme); //prend la lattitude
              a = fgetc(fichier);
              if(a != '\n' && a != EOF && a != ' '){
                  fseek(fichierSortie1,SEEK_CUR,-1);
                  fscanf(fichierSortie1, "%f", &elmt->min);//prend l'humidite
                  return elmt1;
              }
          }
      }

  }
  break;
  return NULL;
}
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
