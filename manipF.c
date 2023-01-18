#include <stdio.h>
#include <stdlib.h>
#include <string.h> //pour strerror
#include <errno.h>//pour errno
//#include "manipF.c"

/*to do list :
finir d'adapter le 'test' pour ajouter les donnes au c*/

int ecriture (FILE* fichier, pA arbre);
void ouvertureFichier(){
    FILE* fichier = fopen ( "tmp.txt", "r");
}

int rechercheDonne (FILE* fichier /*probablement d'autres elements*/){ 
    int a =0;
    int chaine;
    //on change pour fscanf, separateur devient espace
    if (fgetc(fichier)!=EOF){
        fseek(fichier, -1, SEEK_CUR);
        chaine = fscanf(fichier);
    }else{
        exit(6)//code erreur a determiner
        //le test est deja fait avant l'appel -> gros pb on arrete totu
    }
    return chaine;
}
void passerCase(FILE* fichier){
    while (int a!=';'&& a!= EOF && a!='\n'){
        a= fgetc(fichier)
    }
}


 //fprintf

//partie de test des fcts
int test(/*variables a voir*/) //objectif: a chaque fois que j'y fais appel, je prend pour le tableau toutes les infos de l'elmt suivant
{
    int errno;
    FILE* fichier = NULL;

    fichier = fopen("test.txt", "r+");
    int car = 0;

    if (fichier != NULL)
    // On peut lire et écrire dans le fichier
    {
        car = fgetc(fichier);
        if (car == EOF){
            return 0;
        }
        fseek(fichier,-1,SEEK_CUR);
        car = rechercheDonne(fichier);
        return car;
/*        
        car = fgetc(fichier);
        while (car != EOF){
            //if (car != '\n'){
                
                printf("%c", car);
                car = fgetc(fichier);
            /*}else{

                printf ("\n");
                car = fgetc(fichier);
            }

*/
    }
    else
    {
        // On affiche un message d'erreur si on veut
        printf("Impossible d'ouvrir le fichier test.txt");
        printf("message d'erreur: %d\n",strerror(errno));
        printf("code d'erreur: %d\n", &errno);
    }

    return 0;
}

int ecriture (FILE* fichier, pA arbre)
{
    //parcours infixe par rapport au id de station 
    if (!estVide(arbre->fg)){
        ecriture(fichier,arbre->fg);
    }
    tmp = arbre->elmt->somme / arbre->elmt->nbelmt;
    fprintf("%d;%f;%f;%f\n", arbre->elmt->station, tmp,arbre->elmt->max,arbre->elmt->min);
    if (!estVide(arbre->fd)){
        ecriture(fichier, arbre->fd);
    }
}