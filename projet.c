// station; temperature
// station; tmpmoyenne; tmpmin; tmpmax;
#include "projet.h"

// to do list: creer fonction equilibrage d'avl, finir creation fils, finir creation arbre, finir le projet :)
// verifier si lors de l'equilibre, il faut que avoir acces au parent du noeud pour certaines rotations
// verifier les fonctions de calcul d'équilibre
//commencer a chercher comment extraire les données du fichier pour l'incrémenter et faire le tri
//mettre a jour le projet.h
//continuer fonctions d'equilibrage et faire les fcts de pivot
//finir traitement avl
//finir la correction de compilation

//fonctions manquantes pour les arbres: suppression d'un arbre

//tout remanier pour avoir un tri par moyenne/ min/ max -> bcp moins d'elements
type absolu (type a){
    return (a>=0 ? a : -a);
}
type max(type a, type b){
    return (a<b ? a : b);
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
pA rechercheParentCreation(pA a, int id){ //dans le cas ou un element est egal a celui que l'on cree, on renvoie sa localisation, sinon c le futur parent.
    if(!estVide(a)){
        if(a->elmt != NULL){ //cas du premier element ajouté a l'arbre
            if(id < a->elmt->station){
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
                    if(!estVide(a->fd)){
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

pA rechercheParent(pA a, int id){
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
}

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
pA appelRechercheParentModifEquilibre(pA a, int id){
    Pile * liste;
    liste->arbre = a;
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
Pile * rechercheParentModifEquilibre(int id, Pile* pile){ //dans le cas ou un element est egal a celui que l'on cree, on renvoie sa localisation, sinon c le futur parent.
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
pA creationArbre(pA a, Elmt* elm, int info){ //si la station existe dans l'arbre
    pA tmp =rechercheParentCreation(a, elm->station);
    pA new= malloc(sizeof(Arbre));
    if(tmp->elmt !=NULL){
        if (tmp->elmt->station == elm->station || tmp->fg->elmt->station == elm->station || tmp->fd->elmt->station == elm->station){ //la station est deja presente dans le tableau
            if (tmp->elmt->station == elm->station){
                tmp->elmt->somme = tmp->elmt->somme + elm->somme; //elm->somme est la valeur de la nouvelle donnée (somme de 1 elmt)
                tmp->elmt->nbelmt = tmp->elmt->nbelmt + elm->nbelmt; //elm->nbelmt est 1
                tmp->elmt->min = min(tmp->elmt->min, elm->min);
                tmp->elmt->max = max(tmp->elmt->max, elm->max);
            }else{
                if (tmp->fg->elmt->station == elm->station){
                    tmp->fg->elmt->somme = tmp->fg->elmt->somme + elm->somme;
                    tmp->fg->elmt->nbelmt = tmp->fg->elmt->nbelmt + elm->nbelmt;
                    tmp->fg->elmt->min = min(tmp->fg->elmt->min, elm->min);
                    tmp->fg->elmt->max = max(tmp->fg->elmt->max, elm->max);
                }else{
                    tmp->fd->elmt->somme = tmp->fd->elmt->somme + elm->somme;
                    tmp->fd->elmt->nbelmt = tmp->fd->elmt->nbelmt + elm->nbelmt;
                    tmp->fd->elmt->min = min(tmp->fd->elmt->min, elm->min);
                    tmp->fd->elmt->max = max(tmp->fd->elmt->max, elm->max);
                }
            }
            return a;
        }
        if (info == 1){ //info = 1 veut dire qu'on utilise un avl
            a = appelRechercheParentModifEquilibre(a,elm->station); //modifier la fonction pour faire un parcour qui modifie des enfants vers les parents(genre une file)
        }
        if (tmp->elmt->station < new->elmt->station){
            if(tmp->fg != NULL) exit(6); //code erreur a determiner
            tmp->fg = new;
        }else{
            if(tmp->fd != NULL) exit(6); //code erreur a determiner
            tmp->fd = new;
        }
    }else new = a;
    new -> elmt = elm;
    new->equilibre = 0;
    new->fg = NULL ;
    new->fd = NULL ;
    return a;
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
                if(a->fd->equilibre == -1) a = rotationDG(a);
                else a = rotationSG(a);
            }
            else{//trop lourd sur la gauche
                if(a->fg->equilibre == 1) a = rotationGD(a);
                else a = rotationSD(a);
            }
            return a;
        }
    }
    return a;
}

//fonctions de modification de fichier
FILE * ouvertureFichierSortie(char* nomdufichierentree){
    //verifier la comparaison entre le nom du fichier en entree pour ne pas le supprimer en ouvrant celui en sortie
    FILE* fichier = NULL;
    char * chaine = "sortietest.csv";
    if (chaine != nomdufichierentree){
        fichier = fopen ( chaine, "w+");
	    if (fichier == NULL)exit(6); //code erreur a determiner
    }else {
        fichier = fopen ("sortiedufourbe.csv", "w+");
        if (fichier == NULL) exit(6);
    }
    return fichier;
}
void parcoursSufixeEcriture(FILE* fichier, pA arbre){ //ecriture de l'arbre dans l'ordre croissant
    if(!estVide(arbre)){
        if(!estVide(arbre->fd)) parcoursSufixeEcriture(fichier,arbre->fd);
        ecriture(fichier, arbre);
        if(!estVide(arbre->fg)) parcoursSufixeEcriture(fichier,arbre->fg);
    }
}
void parcoursInfixeEcriture(FILE* fichier,pA arbre){ //ecriture de l'arbre dans le tri croissant
    if(!estVide(arbre)){
        if(!estVide(arbre->fg)) parcoursInfixeEcriture(fichier,arbre->fg);
        ecriture(fichier, arbre);
        if(!estVide(arbre->fd)) parcoursInfixeEcriture(fichier,arbre->fd);
    }
}
void ecriture (FILE * fichier, pA arbre){// arbre en entrée, ecrit dans le fichier les elements de pa dans l'ordre
    fprintf(fichier, "%d;%f;%f;%f;\n", arbre->elmt->station, arbre->elmt->somme / arbre->elmt->nbelmt, arbre->elmt->min, arbre->elmt->max);
}

//se renseigner sur feof
void traitementArbre(char *  nomdufichier, int info){
    FILE* fichierEntree = fopen(nomdufichier, "r");
    FILE* fichierSortie = ouvertureFichierSortie(nomdufichier);
    printf("ok pour l'ouverture des fichiers");
    //info sera 1 pour tout
    int tmp2;
    pA arbre = malloc(sizeof(Arbre));
    int a;
    Elmt * tmp = malloc(sizeof(Elmt));
    //initialisation
    if(! feof(fichierEntree)){
      fscanf(fichierEntree, "%d", &tmp->station);
      a = fgetc(fichierEntree);
      if (a!='\n'&&a!='EOF'){
        fseek(fichierEntree,SEEK_CUR,-1);
        fscanf(fichierEntree, "%f", &tmp->somme);
        tmp->nbelmt = 1;
        tmp->min = tmp->somme;
        tmp->max = tmp->somme;
        arbre = creationArbre(arbre, tmp, info);
      }
      //boucle generale
    while (! feof(fichierEntree)){ //boucle de creation de l'arbre
        fscanf(fichierEntree, "%d", &tmp->station);
        a = fgetc(fichierEntree);
        if (a!='\n'&&a!='EOF'){
          fseek(fichierEntree,SEEK_CUR,-1);
          fscanf(fichierEntree, "%f", &tmp->somme);
          tmp->nbelmt = 1;
          tmp->min = tmp->somme;
          tmp->max = tmp->somme;
          arbre = creationArbre(arbre, tmp, info);
        }
    }
    printf("ok pour la creation de l'arbre");
    fclose(fichierEntree);
    parcoursInfixeEcriture(fichierSortie, arbre);
    printf("ok pour l'ecriture");
}


//info = 1 veut dire qu'on utilise un avl
int main (int argc, char *argv[]) {// a indique le mode souhaité entre AVL, ABR et tableau
    char a = argv[1][0];
    char test = argv [1][1];
    if (test != '\0') exit (6); //code erreur a determiner
    printf("a=%c\n",a);
    int i= strlen(argv[2]);
    if (i == 0) exit(6); //code a determiner
    switch (a){
        case ('1') :printf("1\n") ; //traitement en AVL
        printf("%s",argv[2]);
        printf("ok jusqu'a la fin des tests des variables");
        if (argv[2]==NULL) exit(6);//code a determiner
        traitementArbre(argv[2],1);
        break;
        case ('2') :printf("2\n") ; //traitement en ABR
        break;
        case ('3') :printf("3\n")  ;//traitement en tableau
        break;
        default :
            printf("erreur dans l'option\n"); //ne devrait pas arriver car testé dans le script
            exit(1);
            break;
    }
    return 0;

}
