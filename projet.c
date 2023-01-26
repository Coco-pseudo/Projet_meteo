// station; temperature
// station; tmpmoyenne; tmpmax; tmpmin;
#include "projet.h"

// to do list: creer fonction equilibrage d'avl, finir creation fils, finir creation arbre, finir le projet :)
// verifier si lors de l'equilibre, il faut que avoir acces au parent du noeud pour certaines rotations
// verifier les fonctions de calcul d'équilibre
//commencer a chercher comment extraire les données du fichier pour l'incrémenter et faire le tri
//mettre a jour le projet.h
//continuer fonctions d'equilibrage et faire les fcts de pivot
//finir traitement avl
//finir la correction de compilation

//a supprimer la liste suivante de prototypes
int verifEquilibre (pA);

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
void calculEquilibre (pA a){
    if(!estVide(a)) a->equilibre = profondeurDescendance(a->fg) - profondeurDescendance(a->fd);
}
int verifEquilibre (pA a){ //si |equilibre de l'arbre >= 2, modifie 
    if(!estVide(a)){
        if(absolu(a->equilibre >=2)){
            //faire appel aux fonctions d'equilibrage, (surtouten fonctions des enfants)

        }
    }else return 1;
}
pA rechercheParentModifEquilibre(pA a, int id){ //dans le cas ou un element est egal a celui que l'on cree, on renvoie sa localisation, sinon c le futur parent.
    if(!estVide(a)){
        if(id < a->elmt->station){
            if(!estVide(a->fg)){
                //modifier l'equilibre
                a->equilibre = a->equilibre -1;
                verifEquilibre(a);
                return rechercheParentModifEquilibre(a->fg, id);
            }else{
                return a;
            }
        }else{
            if(id > a->elmt->station){
                if(!estVide(a->fd)){
                //modifier l'equilibre
                a->equilibre = a->equilibre +1;
                verifEquilibre(a);
                    return rechercheParentModifEquilibre(a->fd, id);
                }else{
                    return a;
                }
            }
        }
    }
}
void creationArbre(pA a, Elmt* elm, int info){
    pA tmp =rechercheParentCreation(a, elm->station);
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
        return;
    }
    if (info == 1){ //info = 1 veut dire qu'on utilise un avl
        rechercheParentModifEquilibre(a,elm->station); 
    }
    pA new= malloc(sizeof(Arbre));
    new -> elmt = elm;
    new->equilibre = 0;
    new->fg = NULL ;
    new->fd = NULL ;
    if (tmp->elmt->station < new->elmt->station){
        if(tmp->fg != NULL) exit(6); //code erreur a determiner
        tmp->fg = new;
    }else{
        if(tmp->fd != NULL) exit(6); //code erreur a determiner
        tmp->fd = new;
    }
}

//ajouter securite: tester si le nom du fichier en entrée est celui que le c crée, si oui créer un fichier avec un autre nom par default
void traitementAVL(char nomdufichier){
    //transformer char nomdufichier en const char * restrict
    FILE* fichier = fopen(nomdufichier, "r");
    //info sera 1 pour tout
    int a=0;
    int tmp2;
    pA arbre = malloc(sizeof(Arbre));
    Elmt * tmp = malloc(sizeof(Elmt));
    while (tmp!=0){
//        tmp = test();
        creationArbre(arbre, tmp, 1);
    }
}


//info = 1 veut dire qu'on utilise un avl
int main (int argc, char *argv[]) {// a indique le mode souhaité entre AVL, ABR et tableau
    char a = argv[1][0];
    char test = argv [1][1];
    if (test != '\0') exit (6); //code erreur a determiner
    printf("a=%c\n",a);
    switch (a){
        case ('1') :printf("1\n") ; //traitement en AVL
        printf("%c",argv[2]);
        if (argv[2]==NULL) exit(6);//code a determiner
        traitementAVL(*argv[2]);
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
