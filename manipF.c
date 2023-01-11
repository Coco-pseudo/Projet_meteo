#include <stdio.h>
#include <stdlib.h>
#include <string.h> //pour strerror
#include <errno.h>//pour errno
//#include "manipF.c"


void ouvertureFichier(){
    FILE* fichier = fopen ( "tmp.txt", "r");
}

void rechercheDonne (FILE* fichier /*probablement d'autres elements*/){
    int a =0;
    while (a!=';'&& a!= EOF){
        a=fgetc(fichier) ;
    }
}

 //fprintf

//partie de test des fcts
int main(int argc, char *argv[])
{
    int errno;
    FILE* fichier = NULL;

    fichier = fopen("test.txt", "r+");

    if (fichier != NULL)
    {
        // On peut lire et écrire dans le fichier
        int car = 0;
        car = fgetc(fichier);
        while (car != EOF){
            //if (car != '\n'){
                
                printf("%c", car);
                car = fgetc(fichier);
            /*}else{

                printf ("\n");
                car = fgetc(fichier);
            }*/
        }
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
