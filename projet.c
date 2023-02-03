// station; temperature
// station; tmpmoyenne; tmpmin; tmpmax;
#include "projet.h"

// to do list: creer fonction equilibrage d'avl, finir creation fils, finir creation arbre, finir le projet :)
// verifier si lors de l'equilibre, il faut que avoir acces au parent du noeud pour certaines rotations
// verifier les fonctions de calcul d'équilibre
//commencer a chercher comment extraire les données du fichier pour l'incrémenter et faire le tri
//mettre a jour le projet.h
//continuer fonctions d'equilibrage et faire les fcts de pivot
//finir implementation de touts les modes différents


//fonctions manquantes pour les arbres: suppression d'un arbre

//tout remanier pour avoir un tri par moyenne/ min/ max -> bcp moins d'elements
type absolu (type a){
    return (a>=0 ? a : -a);
}
type max(type a, type b){
    return (a>b ? a : b);
}
type min(type a, type b){
    return (a<b ? a : b);
}
int estVide(pA a){
    if (a == NULL) return 1;
    return 0;
}
int descendance(pA a){
    if (!estVide(a)){
        if(!estVide(a->fg) || !estVide(a->fd))return 1;
    }
    return 0;
}
pA rechercheParentCreation(pA a, long id){ //dans le cas ou un element est egal a celui que l'on cree, on renvoie sa localisation, sinon c le futur parent.
    //printf("%d, %d", &a, id);
    //printf(" %li \n", a->elmt->station);
    if(!estVide(a)){
        if(a->elmt != NULL){ //cas du premier element ajouté a l'arbre (ne devrait pas etre rencontré)
            if(id < a->elmt->station){
            //if(a->elmt->station > id){
                if(!estVide(a->fg)){
                    if(id == a->fg->elmt->station){
                        return a->fg;
                    }else{
                        return rechercheParentCreation(a->fg, id);
                    }
                }else{
                    return a;
                }
            }else{
                if(id > a->elmt->station){
                //if(a->elmt->station < id){
                    if(! estVide(a->fd)){
                        if(id == a->fd->elmt->station){
                            return a->fd;
                        }else{
                            return rechercheParentCreation(a->fd, id);
                        }
                    }else{
                        return a;
                    }
                }else{//a-> elmt->station == id (a est la racine de l'arbre d'origine)
                    return a;
                }
            }
        }
    }
    return a;
}

/*pA rechercheParent(pA a, int id){
    printf("%d, %d", &a, id);
    if(!estVide(a)){
        if(id < a->elmt->station){
            if(!estVide(a->fg)){
                if(id == a->fg->elmt->station){
                    return a;
                }else{
                    return rechercheParent(a->fg, id);
                }
            }else{
                return NULL;
            }
        }else{
            if(id > a->elmt->station){
                if(!estVide(a->fd)){
                    if(id == a->fd->elmt->station){
                        return a;
                    }else{
                        return rechercheParent(a->fd, id);
                    }
                }else{
                    return NULL;
                }
            }else{//a-> elmt == id
                return a;
            }
        }
    }
}*/

//ne sert pas actuellement ...
/*pA creationFils (pA papa, pA enfant, int info){ //info sert a savoir si on le trie est AVL ou ABR
    if(papa->elmt->station < enfant->elmt->station){
        papa->fg = enfant;
        if(info == 1){
            papa ->equilibre = papa->equilibre - 1;
            verifEquilibre(papa);
        }
    }else{
        if(papa->elmt == enfant->elmt)exit(2);
        papa->fd = enfant;
        if(info == 1){
            papa ->equilibre = papa->equilibre + 1;
            verifEquilibre(papa);
        }
    }
}*/

/*int verifEquilibre(pA a){ //retourne si |l'equilibre| d'un des noeuds est  >1
    if(!estVide(a)){
        return (verifEquilibre(a->fg)<verifEquilibre(a->fd) ? verifEquilibre(a->fg) : verifEquilibre(a->fd));
    }
}*/
int profondeurDescendance (pA a){
    if(!estVide(a)){
        if(!descendance(a)){
            return max(profondeurDescendance(a->fg)+1,profondeurDescendance(a->fd)+1);
        }
        return 1;
    }return 0;
}
void calculEquilibre (pA a){ //sert a recalculer l'equilibre sans se servir de la valeur precedente
    if(!estVide(a)) a->equilibre = profondeurDescendance(a->fg) - profondeurDescendance(a->fd);
}
Pile * creationPile(pA a){
    Pile * nouveau = malloc(sizeof(Pile));
    nouveau->arbre = a;
    nouveau->modif = 0;
    nouveau -> suivant = NULL;
    return nouveau;
}
pA appelRechercheParentModifEquilibre(pA a, long id){
    Pile * liste = malloc(sizeof(Pile));
    liste = creationPile(a);
    liste = rechercheParentModifEquilibre(id, liste);
    pA b = NULL;
    while(liste !=NULL && b != NULL){
        liste->arbre->equilibre = liste->arbre->equilibre + liste->modif;
        b = verifEquilibre(liste->arbre);
        if(liste->arbre == a && b!= a) return b; //cas ou la racine est modifié
        Pile * tmp = liste;
        if(liste->suivant != NULL){
            liste = liste->suivant;
        }
        free(tmp);
    }
    return a;
}
Pile * rechercheParentModifEquilibre(long id, Pile* pile){ //dans le cas ou un element est egal a celui que l'on cree, on renvoie sa localisation, sinon c le futur parent.
    if(!estVide(pile->arbre)){
        if(id < pile->arbre->elmt->station){
            if(!estVide(pile->arbre->fg)){
                Pile * nouveau = creationPile(pile->arbre->fg);
                nouveau->modif = -1;
                nouveau->suivant = pile;
                return rechercheParentModifEquilibre(id, nouveau);
            }else{
                return pile;
            }
        }else{
            if(id > pile->arbre->elmt->station){
                if(!estVide(pile->arbre->fd)){
                    Pile * nouveau = creationPile(pile->arbre->fd);
                    nouveau->modif = 1;
                    nouveau->suivant = pile;
                    return rechercheParentModifEquilibre(id, nouveau);
                }else{ //on a atteint le nouvel element
                    return pile;
                }
            }
        }
    }
    return pile;
}
pA creationArbre(pA a, Elmt* elm, int info, int mod){ //si la station existe dans l'arbre
    if(mod == 1){
        //printf("%li \n",elm->station);
        //printf("%f \n", elm->somme);
        pA tmp =rechercheParentCreation(a, elm->station);
        //printf("%d ", tmp->elmt->station);
        //printf("%d \n", elm->station);
        //printf("%d \n", &a);
        pA new= malloc(sizeof(Arbre));
        if(tmp->elmt !=NULL){
            if (tmp->elmt->station == elm->station){ //la station est deja presente dans le tableau
                        //printf("test arbre station tmp");
                tmp->elmt->somme = tmp->elmt->somme + elm->somme; //elm->somme est la valeur de la nouvelle donnée (somme de 1 elmt)
                tmp->elmt->nbelmt = tmp->elmt->nbelmt + elm->nbelmt; //elm->nbelmt est 1
                tmp->elmt->min = min(tmp->elmt->min, elm->min);
                tmp->elmt->max = max(tmp->elmt->max, elm->max);
                return a;
            }else{
            if (info == 1){ //info = 1 veut dire qu'on utilise un avl
                a = appelRechercheParentModifEquilibre(a,elm->station); //modifier la fonction pour faire un parcour qui modifie des enfants vers les parents(genre une file)
            }
            if (tmp->elmt->station < elm->station){
                if(tmp->fd != NULL) exit(6); //code erreur a determiner
                tmp->fd = new;
                //printf("fils va a droite\n");
            }else{
                if(tmp->fg != NULL) exit(6); //code erreur a determiner
                tmp->fg = new;
                //printf("fils va a gauche\n");
            }
            new -> elmt = elm;
            new->equilibre = 0;
            new->fg = NULL ;
            new->fd = NULL ;
            return a;
            }
        }
    }
    if(mod == 5){
        pA tmp = rechercheParentCreation(a, elm->station);
        pA new = malloc(sizeof(Arbre));
        if(tmp->elmt->station == elm->station){
            tmp->elmt->max = max(tmp->elmt->max, elm->max);
        }else{
            if (info == 1){ //info = 1 veut dire qu'on utilise un avl
                a = appelRechercheParentModifEquilibre(a,elm->station); //modifier la fonction pour faire un parcour qui modifie des enfants vers les parents(genre une file)
            }
            if (tmp->elmt->station < elm->station){
                if(tmp->fd != NULL) exit(6); //code erreur a determiner
                tmp->fd = new;
                //printf("fils va a droite\n");
            }else{
                if(tmp->fg != NULL) exit(6); //code erreur a determiner
                tmp->fg = new;
                //printf("fils va a gauche\n");
            }
            new->elmt = elm;
            new->equilibre = 0;
            new->fg = NULL ;
            new->fd = NULL ;
        }
        return a;
    }
}

//fonctions de rotation
pA rotationSG(pA arbre){
    pA pivot = arbre->fd;
    arbre->fd = pivot->fg;
    pivot->fg = arbre;
    arbre->equilibre = arbre->equilibre - max(pivot->equilibre,0) -1;
    pivot->equilibre = min(arbre->equilibre-2, min(arbre->equilibre + arbre->equilibre-2, pivot->equilibre - 1));
    return pivot;
}
pA rotationSD(pA arbre){
    pA pivot = arbre->fg;
    arbre->fg = pivot->fd;
    pivot->fd = arbre;
    arbre->equilibre = arbre->equilibre - max(pivot->equilibre,0) +1;
    pivot->equilibre = max(arbre->equilibre+2, max(arbre->equilibre + arbre->equilibre+2, pivot->equilibre + 1));
    return pivot;
}
pA rotationDG(pA arbre){ //AKA rota double gauche
    arbre->fd=rotationSD(arbre->fd);
    return rotationSG(arbre);
}
pA rotationGD(pA arbre){ //AKA rota double droite
    arbre->fg=rotationSG(arbre->fg);
    return rotationSD(arbre);
}
pA verifEquilibre (pA a){ //renvoie le pivot: si l'arbre envoyé etait la racine, modif de la racine
    if(!estVide(a)){
        if(absolu(a->equilibre)==2){
            if(a->equilibre == 2){ //trop lourd sur la droite -> rotation SG ou DG
                //printf("tout va bien\n");
                if(!estVide(a->fd)){
                    if(a->fd->equilibre == -1) a = rotationDG(a);
                    else a = rotationSG(a);
                }
            }
            else{//trop lourd sur la gauche
                if(!estVide(a->fd)){
                    if(a->fg->equilibre == 1) a = rotationGD(a);
                    else a = rotationSD(a);
                }
            }
        }
    }
    return a;
}

//fonctions de modification de fichier
FILE * ouvertureFichierSortie(char* nomdufichierentree, int info){
    //info correspond a l'appel de la fonction(premier ou deuxieme)
    //verifier la comparaison entre le nom du fichier en entree pour ne pas le supprimer en ouvrant celui en sortie
    //printf("test\n");
    FILE* fichier = NULL;
    char * chaine;
    if (info == 2)chaine = "ValeursRetours.csv";
    if (info == 1)chaine = "ValeursIdReelles.csv";
    if (chaine != nomdufichierentree){
        fichier = fopen ( chaine, "w+");
	    if (fichier == NULL)exit(6); //code erreur a determiner
    }else {
        if (chaine == nomdufichierentree){
            if(info == 2)fichier = fopen ("sortiedufourbe.csv", "w+");
            if(info == 1)fichier = fopen ("sortiedufourbeIDReelles","w+");
        }
        if (fichier == NULL) exit(6); //code erreur a determiner 
    }
    return fichier;
}
void parcoursSufixeEcriture(FILE* fichier, pA arbre, int mod, int * num, int file){ //ecriture de l'arbre dans l'ordre croissant
    if(!estVide(arbre)){
        if(!estVide(arbre->fd)) parcoursSufixeEcriture(fichier,arbre->fd, mod, num, file);
        ecriture(fichier, arbre->elmt, mod, num,file);
        if(!estVide(arbre->fg)) parcoursSufixeEcriture(fichier,arbre->fg, mod, num, file);
    }
}
void parcoursInfixeEcriture(FILE* fichier,pA arbre, int mod, int* num, int file){ //ecriture de l'arbre dans le tri croissant
    if(!estVide(arbre)){
        if(!estVide(arbre->fg)) parcoursInfixeEcriture(fichier,arbre->fg, mod, num, file);
        ecriture(fichier, arbre->elmt, mod,num, file);
        if(!estVide(arbre->fd)) parcoursInfixeEcriture(fichier,arbre->fd, mod, num, file);
    }
}
void ecriture (FILE * fichier, Elmt * elmt, int mod, int * num, int file){// arbre en entrée, ecrit dans le fichier les elements de pa dans l'ordre
    // *num est l'indice factice de la station
    //printf("%li \n", ftell(fichier));
    //mod 5 sortie : longitude; latitude ; humidité
    if (file == 2){ //Valeurretours
        //identique a l'autre fichier pour 5 et 6
        //printf("test\n");
        //printf("%f;%f;%f;\n", elmt->somme, elmt->min, elmt->max);
        
        if (mod == 1)fprintf(fichier, "%li;%f;%f;%f;\n", *num, elmt->somme / elmt->nbelmt, elmt->min, elmt->max);
        if (mod == 2)fprintf(fichier, "%li;%f;\n", *num, elmt->somme / elmt->nbelmt);
        if (mod == 3);
        if (mod == 4);
        if (mod == 5)fprintf(fichier, "%f;%f;%f;\n", elmt->max, elmt->somme, elmt->min);
        if (mod == 6);
        if (mod == 7)fprintf(fichier, "%f;%f;%f;\n", elmt->max, elmt->somme, elmt->min);
        //printf("?\n");
        *num = *num + 1;
    }
    if(file == 1){ //valeuridreelle
        //printf("%f;%f;%f;\n", elmt->somme, elmt->min, elmt->max);
        if (mod == 1)fprintf(fichier, "%li;%f;%f;%f\n", elmt->station, elmt->somme / elmt->nbelmt, elmt->min, elmt->max);
        if (mod == 2)fprintf(fichier, "%li;%f\n", elmt->station, elmt->somme / elmt->nbelmt);
        if (mod == 3);
        if (mod == 4);
        if (mod == 5)fprintf(fichier, "%f;%f;%f\n", elmt->max, elmt->somme, elmt->min);
        if (mod == 6);
        if (mod == 7)fprintf(fichier, "%f;%f;%f;\n", elmt->max, elmt->somme, elmt->min);
    }
}

//se renseigner sur feof
void traitementArbre(char *  nomdufichier, int info, int mod){
    FILE* fichierEntree = fopen(nomdufichier, "r");
    FILE* fichierSortie1 = ouvertureFichierSortie(nomdufichier,1);
    FILE* fichierSortie2 = fichierSortie2 = ouvertureFichierSortie(nomdufichier,2);
    printf("ok pour l'ouverture des fichiers \n");
    //info sera 1 pour tout
    int tmp2;
    pA arbre = malloc(sizeof(Arbre));
    Elmt * elmt1 = malloc(sizeof(Elmt));
    if(elmt1 == NULL) exit(6); //code a definir
    //else printf("ok pointeur\n");
    int a;
    Elmt * tmp = malloc(sizeof(Elmt));
    //initialisation
    if(mod == 1){ //boucle pour le tri 1
        //format: entree puis sortie
        // station;variable\n
        //station;moyenne;min;max\n
        if(! feof(fichierEntree)){
            fscanf(fichierEntree, "%d", &elmt1->station);
            //printf("%d \n", elmt1->station);
            //printf("%c \n", elmt1->station);
            a = fgetc(fichierEntree);//passe le separateur
            if(a != '\n' && a != EOF && a != ' '){ 
                if(! feof(fichierEntree)){
                    a = fgetc(fichierEntree); 
                    if (a != '\n' && a != ' '){
                        fseek(fichierEntree,SEEK_CUR,-1);
                        fscanf(fichierEntree, "%f", &elmt1->somme);
                        //printf("%d, %f \n", tmp->station, tmp->somme);
                        elmt1->nbelmt = 1;
                        elmt1->min = elmt1->somme;
                        elmt1->max = elmt1->somme;
                        arbre->elmt = elmt1;
                    }
                }
            }
        }
          //boucle generale
        while (! feof(fichierEntree)){ //boucle de creation de l'arbre
            tmp = malloc(sizeof(Elmt));
            //printf("boucle\n");
            fscanf(fichierEntree, "%d", &tmp->station);
            if(! feof(fichierEntree)){
                a = fgetc(fichierEntree);//passe le separateur
                if(a != '\n' && a != ' '){ 
                    if(! feof(fichierEntree)){
                        a = fgetc(fichierEntree); 
                        if (a != '\n' && a != ' '){
                            fseek(fichierEntree,SEEK_CUR,-1);
                            fscanf(fichierEntree, "%f", &tmp->somme);
                            //printf("%d, %f \n", tmp->station, tmp->somme);
                            tmp->nbelmt = 1;
                            tmp->min = tmp->somme;
                            tmp->max = tmp->somme;
                            //printf("avant creation arbre \n");
                            arbre = creationArbre(arbre, tmp, info, mod);
                              //printf("ok jusqu'ici \n");
                        }
                    }
                }
            }
        }
    }
    if(mod == 2){ //boucle pour le tri 2
        //format: entree puis sortie
        // date/heure;variable\n
        //date/heure;moyenne\n
        //partie du principe que on peut comparer les dates comme si ils etaient des entiers en ascii, a verifier
        int i = 0;
        int nvldate;
        long date = 0;
        int utc = 0;
        char signe = 1; //prend 1 pour + et -1 pour -
        int n = 0;
        if(! feof(fichierEntree)){
            //modifs a mettre ici pour convertir la date en entier
            for(i=0; i<19; i++){
                a = fgetc(fichierEntree);
                nvldate= a;
                //printf("nvldate = %d \n", nvldate);
                if (!(nvldate < '0'|| nvldate > '9')){
                    date = date * 10 + nvldate - 48;
                    //printf("%d \n", nvldate - 48);
                    //printf("%li \n", date);
                    n++;
                    //printf("iteration %d \n", n);
                }
            }
            a = fgetc(fichierEntree);
            if(a == '+')signe = 1;
            if(a == '-')signe == -1;
            for(i=0; i<5; i++){
                nvldate = fgetc(fichierEntree);
                if (!(nvldate < '0'&& nvldate > '9')){
                    utc = utc * 10 + nvldate - 48;
                    printf("utc : %i \n");
                }
            }
            //voir atoi
            //printf("utc = %d \n", utc);
            //printf ("signe = %d \n", signe);
            //printf("%d\n", date);
            date = date + (signe * utc);
            printf("%li \n", date);
            
            elmt1->station = date;
            //a = fgetc(fichierEntree);//passe le separateur
                //if (a != '\n' &&a != EOF && a!= ' '){
                    fscanf(fichierEntree, "%f", &elmt1->somme);
                    printf("%f \n", elmt1->somme);
                    //printf("%d, %f \n", tmp->station, tmp->somme);
                    elmt1->nbelmt = 1;
                    arbre->elmt = elmt1;
                //}
        }
          //boucle generale
        /*while*/ if (! feof(fichierEntree)){ //boucle de creation de l'arbre
            tmp = malloc(sizeof(Elmt));
            printf("entree dans ma boucle\n");
            //modifs a mettre ici pour convertir la date en entier
            date = 0;
            utc = 0;
            for(i=0; i<19; i++){
                a = fgetc(fichierEntree);
                nvldate= a;
                if (!(nvldate < '0'|| nvldate > '9')){
                    date = date * 10 + nvldate -48;
                    n++;
                    printf("%li \n",date);
                    //printf("iteration %d \n", n);
                }
            }
            a = fgetc(fichierEntree);
            if(a == '+')signe = 1;
            if(a == '-')signe == -1;
            printf("%d signe\n");
            for(i=0; i<5; i++){
                nvldate = fgetc(fichierEntree);
                printf("nvldate : %d\n");
                if (!(nvldate < '0'&& nvldate > '9')){
                    utc = utc * 10 + nvldate -48;
                    printf("utc = %i\n");
                }
            }
            printf("utc : %d\n ",utc);
            date = date + signe * utc;
            printf("date : %li \n", date);
            tmp->station = date;
            //a = fgetc(fichierEntree);
            //if(a != '\n' && a != EOF && a != ' '){
                //if (a != '\n' && a != EOF && a != ' '){
                  //fseek(fichierEntree,SEEK_CUR,-1);
                  fscanf(fichierEntree, "%f", &tmp->somme);

                    printf("elmt : %f \n", tmp->somme);
                  //printf("%li, %f \n", tmp->station, tmp->somme);
                  tmp->nbelmt = 1;
                  //printf("avant creation arbre \n");
                  arbre = creationArbre(arbre, tmp, info, mod);
                    //printf("ok jusqu'ici \n");
                //}
            //}
        }
    }
    if(mod == 3){ //boucle pour le tri 3
        //format: entree puis sortie
        // date/heure;variable\n
        // date/heure;station;valeur\n
        // ou station;date/heure;valeur

    }
    if(mod == 4){ //boucle pour le tri 4
        
    }
    if(mod == 5){ //boucle pour le tri 5
        //tri selon station, humidité, longitude et lattitude
        //printf("debut du mod5\n");
        if(! feof(fichierEntree)){
            rewind(fichierEntree);
            fscanf(fichierEntree, "%d", &elmt1->station);
            //printf("%d \n", elmt1->station);
            //printf("%c \n", elmt1->station);
            if(! feof(fichierEntree)){
                a = fgetc(fichierEntree); 
                if (a != '\n' && a != ' '){
                    fseek(fichierEntree,SEEK_CUR,-1);
                    fscanf(fichierEntree, "%f", &elmt1->max); //prend l'humidite
                    a = fgetc(fichierEntree);
                    if(a != '\n' && a != EOF && a != ' '){
                        fseek(fichierEntree,SEEK_CUR,-1);
                        fscanf(fichierEntree, "%f", &elmt1->somme);//prend la longitude
                        a = fgetc(fichierEntree);
                        if(a != '\n' && a != EOF && a != ' '){
                            //printf("c\n", a);
                            fseek(fichierEntree,SEEK_CUR,-1);
                            fscanf(fichierEntree, "%f", &elmt1->min);//prend la lattitude
                            //printf("%d, %f \n", tmp->station, tmp->somme);
                            elmt1->nbelmt = 1;
                            arbre->elmt = elmt1;
                        }
                    }
                }
            }
        }
        //boucle generale
        while (! feof(fichierEntree)){ //boucle de creation de l'arbre
            
            tmp = malloc(sizeof(Elmt));
            //printf("boucle\n");
            fscanf(fichierEntree, "%d", &tmp->station);
            //printf("%d\n", tmp->station);
            if(! feof(fichierEntree)){
                a = fgetc(fichierEntree); 
                if (a != '\n' && a != ' '){
                    fseek(fichierEntree,SEEK_CUR,-1);
                    fscanf(fichierEntree, "%f", &tmp->max);
                    a = fgetc(fichierEntree);
                    if(a != '\n' && a != EOF && a != ' '){
                        fseek(fichierEntree,SEEK_CUR,-1);
                        fscanf(fichierEntree, "%f", &tmp->somme);
                        //printf("%f \n", tmp->somme);
                        a = fgetc(fichierEntree);
                        if(a != '\n' && a != EOF && a != ' '){
                            fseek(fichierEntree,SEEK_CUR,-1);
                            //printf("%c\n", a);
                            fscanf(fichierEntree, "%f", &tmp->min);
                            //printf("%f \n", tmp->min);
                            //printf("%d, %f \n", tmp->station, tmp->somme);
                            tmp->nbelmt = 1;
                            arbre = creationArbre(arbre, tmp, info, mod);
                        }
                    }
                }
            }
        }
    }
    if(mod == 6){ //boucle pour le tri 6
        //tri selon station, altitude, longitude et lattitude
        if(! feof(fichierEntree)){
            fscanf(fichierEntree, "%d", &elmt1->station);
            //printf("%d \n", elmt1->station);
            //printf("%c \n", elmt1->station);
            if(! feof(fichierEntree)){
                a = fgetc(fichierEntree); 
                if (a != '\n' && a != ' '){
                    fseek(fichierEntree,SEEK_CUR,-1);
                    fscanf(fichierEntree, "%f", &elmt1->max); //prend l'altitude
                    a = fgetc(fichierEntree);
                    if(a != '\n' && a != EOF && a != ' '){
                        fseek(fichierEntree,SEEK_CUR,-1);
                        fscanf(fichierEntree, "%f", &elmt1->somme);//prend la longitude
                        a = fgetc(fichierEntree);
                        if(a != '\n' && a != EOF && a != ' '){
                            //printf("c\n", a);
                            fseek(fichierEntree,SEEK_CUR,-1);
                            fscanf(fichierEntree, "%f", &elmt1->min);//prend la lattitude
                            //printf("%d, %f \n", tmp->station, tmp->somme);
                            elmt1->nbelmt = 1;
                            arbre->elmt = elmt1;
                        }
                    }
                }
            }
        }
          //boucle generale
        while (! feof(fichierEntree)){ //boucle de creation de l'arbre
            tmp = malloc(sizeof(Elmt));
            //printf("boucle\n");
            fscanf(fichierEntree, "%d", &tmp->station);
            if(! feof(fichierEntree)){
                a = fgetc(fichierEntree); 
                if (a != '\n' && a != ' '){
                    fseek(fichierEntree,SEEK_CUR,-1);
                    fscanf(fichierEntree, "%f", &tmp->max);
                    a = fgetc(fichierEntree);
                    if(a != '\n' && a != EOF && a != ' '){
                        fseek(fichierEntree,SEEK_CUR,-1);
                        fscanf(fichierEntree, "%f", &tmp->somme);
                        //printf("%f \n", tmp->somme);
                        a = fgetc(fichierEntree);
                        if(a != '\n' && a != EOF && a != ' '){
                            fseek(fichierEntree,SEEK_CUR,-1);
                            //printf("%c\n", a);
                            fscanf(fichierEntree, "%f", &tmp->min);
                            //printf("%f \n", tmp->min);
                            //printf("%d, %f \n", tmp->station, tmp->somme);
                            tmp->nbelmt = 1;
                            arbre = creationArbre(arbre, tmp, info, mod);
                        }
                    }
                }
            }
            
        }
    }
    //printf("ok pour la creation de l'arbre \n");
    fclose(fichierEntree);
    printf("arbre ok\n");
    //printf("%d est la racine de l'arbre \n" , arbre->elmt->station);
    //parcoursInfixe(arbre);
    int* num = NULL;
    int valeur = 0;
    num = &valeur;
    //printf("%d\n", *num);
    //printf("%d\n", num);
    parcoursInfixeEcriture(fichierSortie1, arbre, mod,num, 1);
    if(mod == 5 || mod == 6){
        fseek(fichierSortie1,SEEK_SET,0);
        Elmt ** Tableau = creationTableau();
        Tableau = traitementTableau(fichierSortie1, Tableau, 7);
        fclose(fichierSortie1);
        FILE * fichierSortie3 = ouvertureFichierSortie(nomdufichier,1);
        for(int i=0; i< 70; i++){
            if(Tableau[i]!=NULL){
                printf("%f, %f, %f\n", Tableau[i]->min, Tableau[i]->somme , Tableau[i]->max);
            }
        }
        parcoursDecroissantTableauEcriture(fichierSortie3,Tableau,7,1);
        parcoursDecroissantTableauEcriture(fichierSortie2,Tableau,7,2);
    }else{
        parcoursInfixeEcriture(fichierSortie2, arbre, mod, num, 2);
        //printf("ok pour l'ecriture \n");
    }
    if (mod != 5 && mod !=6)fclose(fichierSortie1);
    fclose(fichierSortie2);
}
/*probleme a corriger: seule la derniere ligne du fichier est affiche dans le fichier de sortie.
Cause possible: defaults dans la creation/gestion de l'arbre
pas ecriture (testé)*/


//info = 1 veut dire qu'on utilise un avl
int main (int argc, char *argv[]) {// a indique le mode souhaité entre AVL, ABR et tableau
    //printf("debut programme\n");
    char a = argv[1][0];
    char test = argv [1][1];
    if (test != '\0') exit (6); //code erreur a determiner
    test = argv[3][1];
    if (test != '\0') exit (6); //code erreur a determiner
    //printf("%d\n", argv[3][0]);
    test = argv[3][0];
    if(test<'0' || test>'6') exit(6); //code a determiner
    //printf("a=%c\n",a);
    //if (argv[2]==NULL) exit(6);//code a determiner
    int i= strlen(argv[2]);
    if (i == 0) exit(6); //code a determiner
    switch (a){
        case ('1') ://printf("1\n") ; //traitement en AVL
        //printf("%s \n",argv[2]);
        //printf("ok jusqu'a la fin des tests des variables \n");
        traitementArbre(argv[2],1,argv[3][0]-48);
        break;
        case ('2') ://printf("2\n") ; //traitement en ABR
        traitementArbre(argv[2],0,argv[3][0]-48); //-48 pour repasser a la valeur numerique (pas ascii)
        break;
        case ('3') ://printf("3\n")  ;//traitement en tableau
        appelTraitementTableau(argv[2],argv[3][0]-48);
        break;
        default :
            printf("erreur dans l'option\n"); //ne devrait pas arriver car testé dans le script
            exit(1);
            break;
    }
    printf("done c \n");
    return 0;

}//*/


void parcoursInfixe(pA arbre){
    if(!estVide(arbre)){
        if(!estVide(arbre->fg)){
            parcoursInfixe(arbre->fg);
        }
        printf("%d, %f, %f, %f \n",   arbre->elmt->station, arbre->elmt->somme / arbre->elmt->nbelmt, arbre->elmt->min, arbre->elmt->max);
        if(!estVide(arbre->fd)) {
            parcoursInfixe(arbre->fd);
        }
    }
}

/*
int main (){
    pA arbre = malloc(sizeof(Arbre));
    Elmt * element1 = malloc (sizeof(Elmt));
    Elmt * element2 = malloc (sizeof(Elmt));
    Elmt * element3 = malloc (sizeof(Elmt));
    Elmt * element4 = malloc (sizeof(Elmt));
    Elmt * element5 = malloc (sizeof(Elmt));
    Elmt * element6 = malloc (sizeof(Elmt));
    Elmt * element7 = malloc (sizeof(Elmt));
    Elmt * element8 = malloc (sizeof(Elmt));
    Elmt * element9 = malloc (sizeof(Elmt));
    Elmt * element10 = malloc (sizeof(Elmt));
    Elmt * element11 = malloc (sizeof(Elmt));
    Elmt * element12 = malloc (sizeof(Elmt));
    Elmt * element13 = malloc (sizeof(Elmt));
    Elmt * elemenraitementTableau
7558 
� 
t14 = malloc (sizeof(Elmt));
    Elmt * element15 = malloc (sizeof(Elmt));
    Elmt * element16 = malloc (sizeof(Elmt));
    Elmt * element17 = malloc (sizeof(Elmt));
    Elmt * element18 = malloc (sizeof(Elmt));
    Elmt * element19 = malloc (sizeof(Elmt));
    Elmt * element20 = malloc (sizeof(Elmt));
    Elmt * element21 = malloc (sizeof(Elmt));


    element1->station = 15;
    element2->station = 15;
    element3->station = 10;
    element4->station = 16;
    element5->station = 9;
    element6->station = 11;
    element7 -> station = 7;
    element8 -> station = 8; 
    element9 -> station = 9; 
    element10->station = 22;
    element11->station = 25;
    element12->station = 27;
    element13->station = 23;
    element14->station = 25;
    element15->station = 24;
    element16->station = 26;
    element17->station = 28;
    element18->station = 27;
    element19->station = 25;
    element20->station = 13;
    element21->station = 20;

    element1->somme = 30;
    element1->min = 30;
    element1->max = 30;
    element1->nbelmt = 1;

    element2->somme = 10;
    element2->min = 10;
    element2->max = 10;
    element2->nbelmt = 1;

    element3->somme = 30;
    element3->min = 30;
    element3->max = 30;
    element3->nbelmt = 1;

    element4->somme = 30;
    element4->min = 30;
    element4->max = 30;
    element4->nbelmt = 1;

    element5->somme = 30;
    element5->min = 30;
    element5->max = 30;
    element5->nbelmt = 1;

    element6->somme = 30;
    element6->min = 30;
    element6->max = 30;
    element6->nbelmt = 1;

    element7->somme =25;
    element7->min = 25;
    element7->max = 25;
    element7->nbelmt = 1;

    element8->somme =25;
    element8->min = 25;
    element8->max = 25;
    element8->nbelmt = 1;

    element9->somme =25;
    element9->min = 25;
    element9->max = 25;
    element9->nbelmt = 1;

    element10->somme =25;
    element10->min = 25;
    element10->max = 25;
    element10->nbelmt = 1;

    element11->somme =25;
    element11->min = 25;
    element11->max = 25;
    element11->nbelmt = 1;

    element12->somme =25;
    element12->min = 25;
    element12->max = 25;
    element12->nbelmt = 1;
    
    element13->somme =25;
    element13->min = 25;
    element13->max = 25;
    element13->nbelmt = 1;
    
    element14->somme =25;
    element14->min = 25;
    element14->max = 25;
    element14->nbelmt = 1;

    element15->somme = 25;
    element15->min = 25;
    element15->max = 25;
    element15->nbelmt = 1;

    element16->somme = 25;
    element16->min = 25;
    element16->max = 25;
    element16->nbelmt = 1;

    element17->somme = 25;
    element17->min = 25;
    element17->max = 25;
    element17->nbelmt = 1;

    element18->somme = 25;
    element18->min = 25;
    element18->max = 25;
    element18->nbelmt = 1;

    element19->somme = 25;
    element19->min = 25;
    element19->max = 25;
    element19->nbelmt = 1;

    element20->somme = 25;
    element20->min = 25;
    element20->max = 25;
    element20->nbelmt = 1;

    element21->somme = 25;
    element21->min = 25;
    element21->max = 25;
    element21->nbelmt = 1;


    arbre->elmt = element1;
    arbre = creationArbre(arbre, element2, 1, mod);
    arbre = creationArbre(arbre, element3, 1, mod);
    arbre = creationArbre(arbre, element4, 1, mod);
    arbre = creationArbre(arbre, element5, 1, mod);
    arbre = creationArbre(arbre, element6, 1, mod);
    arbre = creationArbre(arbre, element7, 1, mod);
    arbre = creationArbre(arbre, element8, 1, mod);
    arbre = creationArbre(arbre, element9, 1, mod);
    arbre = creationArbre(arbre, element10, 1, mod);
    arbre = creationArbre(arbre, element11, 1, mod);
    arbre = creationArbre(arbre, element12, 1, mod);
    arbre = creationArbre(arbre, element13, 1, mod);
    arbre = creationArbre(arbre, element14, 1, mod);
    arbre = creationArbre(arbre, element15, 1, mod);
    arbre = creationArbre(arbre, element16, 1, mod);
    arbre = creationArbre(arbre, element17, 1, mod);
    arbre = creationArbre(arbre, element18, 1, mod);
    arbre = creationArbre(arbre, element19, 1, mod);
    arbre = creationArbre(arbre, element20, 1, mod);
    arbre = creationArbre(arbre, element21, 1, mod);
    parcoursInfixe(arbre);
    return 0 ;
}

*/
// test du scanf

/*int main(int argc, char *argv[]){
    /*FILE * fichierEntree = fopen(argv[1],"r");
    FILE * fichierSortie = ouvertureFichierSortie(argv[1], 1);
    int a =0;
    fscanf(fichierEntree, "%d", &a);
    fprintf(fichierSortie, "%d",a);
    a = fgetc(fichierEntree);
    fprintf(fichierSortie, "%d",a);
    //test tableau
    Elmt ** Tableau=creationTableau();
    int n = -1;
    printf("debut\n");
    for(int i=0; i<8;i++){
        printf("i = %d\n", i);
        Tableau[i]->station = i;
        Tableau[i]->somme = i;
        Tableau[i]->nbelmt = 1;
        printf("%d, %f, %d \n",Tableau[i]->station,Tableau[i]->somme,Tableau[i]->nbelmt);
        n++;
    }
    printf("test\n");
    int valeur = n;
    int * max = &valeur;
    printf("%d, %d\n", *max, valeur);
    Elmt * testdecalage = malloc(sizeof(Elmt));
    if(Tableau[valeur]== NULL)printf("pb\n");
    Elmt * elm = malloc(sizeof(Elmt));
    elm->station = 3;
    elm->somme = 1;
    elm->nbelmt = 1;
    Tableau = ajoutElmtTableau(Tableau,elm,1,max);
    for(int i=0; i< 70; i++){
        if(Tableau[i]!=NULL){
            printf("%d, %f\n", Tableau[i]->station, Tableau[i]->somme / Tableau[i]->nbelmt);
        }
    }
    return 0;
}*/
