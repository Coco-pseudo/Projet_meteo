#include "projet.h"

//pour l'instant, on considere que on fait d'abord appel au traitement avl
//pour avoir le nombre de lignes finale
// ou on cree un tableau qui contient des elmts

//tableau de 70 cases: 70 stations en tout


Elmt ** creationTableau(){
    Elmt ** Tableau = malloc(sizeof(Elmt)*70);
    for(int i=0; i<70; i++){
        Tableau[i] = malloc(sizeof(Elmt));
    }
    return Tableau;
}
int maxint(int a, int b){
    return (a > b?  a : b);
}
int minint(int a, int b){
    return (a < b?  a : b);
}
int rechercheDichotomique(Elmt * Tableau[70], Elmt * elmt, int mod, int * maximum){
    int minimum = 0;
    int recherchemax = *maximum;
    //printf("recherche : %d\n",recherchemax);
    //printf("recherche : %d, %d\n",recherchemax, *maximum);
    //printf("milieu depart : %d\n", (recherchemax + minimum)/2);
    //printf("elmt->station = %d\n",elmt->station);
    if(mod!=7){
        //verif extremums
        if (Tableau[minimum]->station > elmt->station)return minimum;
        if (Tableau[recherchemax]->station < elmt->station)return recherchemax;
        //boucle generale
        while((Tableau[((recherchemax + minimum)/2) ]->station!=elmt->station) && recherchemax != minimum && recherchemax != minimum +1){
            //printf("milieu actuel : %d\n", (recherchemax + minimum)/2);
            if (Tableau[minimum]->station > elmt->station)return minimum;
            if(Tableau[recherchemax]->station < elmt->station)return recherchemax;
            if(Tableau[((recherchemax + minimum)/2)]->station > elmt->station){
                recherchemax = ((recherchemax+minimum)/2);
            }if(Tableau[((recherchemax + minimum)/2)]->station < elmt->station){
                minimum = ((recherchemax+minimum)/2);
            }
        }//Tableau[((recherchemax + minimum)/2)]->station==elmt->station ou minimum = max de recherche
        if (Tableau[((recherchemax + minimum)/2)]->station==elmt->station){
            if(mod == 1){
                return (recherchemax + minimum)/2;
                //Tableau[((recherchemax + minimum)/2)]->somme = Tableau[((recherchemax + minimum)/2)]->somme + elmt->somme;
                //Tableau[((recherchemax + minimum)/2)]->nbelmt = Tableau[((recherchemax + minimum)/2)]->nbelmt + elmt->nbelmt;
                //Tableau[((recherchemax + minimum)/2)]->max = maxint(Tableau[((recherchemax + minimum)/2)]->max , elmt->max);
                //Tableau[((recherchemax + minimum)/2)]->min = minint(Tableau[((recherchemax + minimum)/2)]->min , elmt->min);
            }
        }else{
            return minimum;
        }
    }else{
        //verif extremums
        if (Tableau[minimum]->min > elmt->min)return minimum;
        if (Tableau[recherchemax]->min < elmt->min)return recherchemax;
        //boucle generale
        while((Tableau[minimum]->min != elmt->min) && Tableau[minimum]->min<elmt->min){
            minimum = minimum +1;
        }//Tableau[((recherchemax + minimum)/2)]->min==elmt->min ou minimum = max de recherche
        
        return minimum;
    }
    /*printf("debut recherche dichotomique , %d, %d\n", mod,elmt->station);
    int min = 0;
    int recherchemax = *maximum;
    if(mod!=7){
        while(Tableau[(recherchemax+min)/2]!=NULL){
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
        return ((recherchemax+min)/2);
    }else{
        while(Tableau[(recherchemax+min)/2]!=NULL){
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
        return((recherchemax+min)/2);
    }*/
}
Elmt ** decalageTableau(int debut, Elmt * Tableau[70]){
    //printf("debut decalage\n");
    Elmt * tmp = malloc(sizeof(Elmt));
    tmp = Tableau[debut];
    Tableau[debut]=NULL;
    Elmt * tmp2 = malloc(sizeof(Elmt));
    debut = debut +1;
    while(Tableau[debut]!=NULL || tmp!=NULL){
        tmp2 = Tableau[debut];
        Tableau[debut] = tmp;
        tmp = tmp2;
        debut = debut +1;
    }
    return Tableau;
}
Elmt ** ajoutElmtTableau(Elmt * Tableau [70], Elmt * elmt, int mod, int * maximum){
    //printf("debut ajout elmt\n");
    //printf("max actuel :%d\n", *maximum);
    int i = rechercheDichotomique(Tableau,elmt, mod, maximum);
    //printf("fin recherche\n");
    //printf("max actuel :%d\n", *maximum);
    //printf("%d \n", i);
    if(mod !=7){
        if(Tableau[i]==NULL){
            Tableau[i]=elmt;exit(1);
            return Tableau;
        }
        if(Tableau[i]->station == elmt->station){
            if (mod == 1){
                //printf("%d test\n", Tableau[i]->station);
                //printf("%d, %d, %d \n",Tableau[i]->station,Tableau[i]->somme,Tableau[i]->nbelmt);
                Tableau[i]->somme = Tableau[i]->somme + elmt->somme;
                Tableau[i]->nbelmt = Tableau[i]->nbelmt + elmt->nbelmt;
                Tableau[i]->min = min(Tableau[i]->min,elmt->min);
                Tableau[i]->max = max(Tableau[i]->max,elmt->max);
                //printf("%d, %d, %d \n",Tableau[i]->station,Tableau[i]->somme,Tableau[i]->nbelmt);
            }
        }else{
            if(Tableau[i]->station < elmt->station)i = i + 1;
            Tableau = decalageTableau(i,Tableau);
            Tableau[i] = elmt;
            *maximum = *maximum + 1;
        }
    }else{
        if(Tableau[i] == NULL){
            Tableau[i] = elmt;exit(1);
            return Tableau;
        }else{
            if(Tableau[i]->min > elmt->min){
                Tableau = decalageTableau(i, Tableau);
                Tableau[i] = elmt;
                *maximum = *maximum + 1;
            }else{
                i = i+1;
                Tableau = decalageTableau(i,Tableau);
                Tableau[i] = elmt;
                *maximum = *maximum + 1;
                
            }
        }
    }
    /*printf("\n \n \n ");
    for(int i=0; i< 70; i++){
        if(Tableau[i]!=NULL){
            printf("%d, %f\n", Tableau[i]->station, Tableau[i]->somme / Tableau[i]->nbelmt);
        }
    }*/

    //printf("fin ajout elmt\n");
    return Tableau;
}
Elmt * scanElmt(FILE * fichier, int mod){
    //printf("debut scanElmt\n");
    Elmt * elmt = malloc(sizeof(Elmt));
    int a = 0;
    switch (mod){
        case (1) :
        if(! feof(fichier)){
            fscanf(fichier, "%d", &elmt->station);
            //printf("%d \n", elmt->station);
            a = fgetc(fichier);//passe le separateur
            if(a != '\n' && a != EOF && a != ' '){
                if(! feof(fichier)){
                    a = fgetc(fichier);
                    if (a != '\n' && a != ' '){
                        fseek(fichier,SEEK_CUR,-1);
                        fscanf(fichier, "%f", &elmt->somme);
                        //printf("%d, %f \n", elmt->station, elmt->somme);
                        elmt->nbelmt = 1;
                        elmt->min = elmt->somme;
                        elmt->max = elmt->somme;
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
        case (6) ://ne servira a rien
        break;
        case(7) : //cas du deuxieme tri avec
        if(! feof(fichier)){
            fscanf(fichier, "%f", &elmt->min);// prend la l'humidite
            //printf("%d \n", elmt->station);
            //printf("%c \n", elmt->station);
            if(! feof(fichier)){
                a = fgetc(fichier);
                if (a != '\n' && a != ' '){
                    fseek(fichier,SEEK_CUR,-1);
                    fscanf(fichier, "%f", &elmt->max); //prend la longitude
                    a = fgetc(fichier);
                    if(a != '\n' && a != EOF && a != ' '){
                        fseek(fichier,SEEK_CUR,-1);
                        fscanf(fichier, "%f", &elmt->somme);//prend lattitude
                        //printf("humidite : %f \n", elmt->min);
                        //printf("%f,%f\n",elmt->max, elmt->somme);
                        if(elmt->min != 0)return elmt;
                    }
                }
            }
        }
        break;
        default : //erreur, ne fait rien 
        break;
    }
    return NULL;
}
void parcoursCroissantTableauEcriture(FILE* fichier, Elmt * Tableau [70],int mod, int file){
    int * num = NULL;
    int valeur =0;
    num = &valeur;
    for(int i=0; i<=69; i++){
        if(Tableau[i]!=NULL){
            if(Tableau[i]->station !=0)ecriture(fichier, Tableau[i],mod,num,file);
        }
    }
}
void parcoursDecroissantTableauEcriture(FILE* fichier, Elmt * Tableau [70],int mod, int file){
    int * num = NULL;
    int valeur =0;
    num = &valeur;
    for(int i=69; i>=0; i--){
        if(Tableau[i]!=NULL){
            if(Tableau[i]->min !=0)ecriture(fichier, Tableau[i],mod,num,file);
        }
    }
}
Elmt ** traitementTableau(FILE* fichier, Elmt * Tableau[70] ,int mod){
    //Elmt * Tableau[70];
    //printf("debutTraitementTableau\n");
    int valeur = 0;
    int * maximum = &valeur;
    Elmt * elmt1 = malloc(sizeof(Elmt)); 
    Elmt * tmp = malloc(sizeof(Elmt));
    elmt1 = scanElmt(fichier, mod);
    Tableau[0] = elmt1;
    //printf("%d\n \n",Tableau[0]->station);
    while(!feof(fichier)){
        Elmt * tmp = malloc(sizeof(Elmt));
        tmp = scanElmt(fichier, mod);
        if(tmp!=NULL)Tableau = ajoutElmtTableau(Tableau, tmp, mod, maximum);
    }
    return Tableau;
}
void appelTraitementTableau(char* nomdufichier, int mod){
    //printf("traitement\n");
    FILE * fichierEntree = fopen(nomdufichier, "r");
    FILE* fichierSortie1 = ouvertureFichierSortie(nomdufichier,1);
    FILE* fichierSortie2 = fichierSortie2 = ouvertureFichierSortie(nomdufichier,2);
    //printf("ok pour l'ouverture des fichiers \n");
    Elmt ** Tableau = creationTableau();
    Tableau = traitementTableau(fichierEntree, Tableau, mod);
    //printf("tableau complet\n");
    if(mod<5){
        parcoursCroissantTableauEcriture(fichierSortie1, Tableau, mod, 1);
        parcoursCroissantTableauEcriture(fichierSortie2, Tableau, mod, 2);
        fclose(fichierSortie1);
        fclose(fichierSortie2);
    }else{
        //parcoursDecroissantTableauEcriture(fichierSortie1, Tableau, mod, 1);
        //parcoursDecroissantTableauEcriture(fichierSortie2, Tableau, mod, 2);
    }
}
/*int main(){
    Elmt * Tableau[70];
    //Tableau = traitementTableau(Tableau);
    return 0;
}*/
