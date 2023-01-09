#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <projet.h>

// to do list: creer fonction equilibrage d'avl, finir creation fils, finir creation arbre, finir le projet :)
// verifier si lors de l'equilibre, il faut que avoir acces au parent du noeud pour certaines rotations
// verifier les fonctions de calcul d'équilibre
//commencer a chercher comment extraire les données du fichier pour l'incrémenter et faire le tri
//chercher comment creer un fichier de sorti
//mettre a jour le projet.h
//continuer fonctions d'equilibrage et faire les fcts de pivot
//rajouter la partie recherche des elements dans le fichier en parametre et creer un fichier qui contiendras les donnees tries
typedef int type;
typedef struct arbre {
    struct arbre * fd;
    struct arbre * fg;
    type elmt;
    int equilibre;
    int doublon;
} Arbre ;
typedef Arbre * pA;
//a supprimer la liste suivante de prototypes
int verifEquilibre (pA);

type absolu (type a){
    return (a>=0 ? a : -a);
}
int max(type a, type b){
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
pA rechercheParentCreation(pA a, type e){ //dans le cas ou un element est egal a celui que l'on cree, on renvoie sa localisation, sinon c le futur parent.
    if(!estVide(a)){
        if(e< a->elmt){
            if(!estVide(a->fg)){
                if(e == a->fg->elmt){
                    return a->fg;
                }else{
                    return rechercheParentCreation(a->fg, e);
                }
            }else{
                return a;
            }
        }else{
            if(e> a->elmt){
                if(!estVide(a->fd)){
                    if(e == a->fd->elmt){
                        return a->fd;
                    }else{
                        return rechercheParentCreation(a->fd, e);
                    }
                }else{
                    return a;
                }
            }else{//a-> elmt == e (a est la racine de l'arbre d'origine)
                return a;
            }
        }
    }
}

pA rechercheParent(pA a, type e){
    if(!estVide(a)){
        if(e< a->elmt){
            if(!estVide(a->fg)){
                if(e == a->fg->elmt){
                    return a;
                }else{
                    return rechercheParent(a->fg, e);
                }
            }else{
                return NULL;
            }
        }else{
            if(e> a->elmt){
                if(!estVide(a->fd)){
                    if(e == a->fd->elmt){
                        return a;
                    }else{
                        return rechercheParent(a->fd, e);
                    }
                }else{
                    return NULL;
                }
            }else{//a-> elmt == e
                return a;
            }
        }
    }
}

pA creationFils (pA papa, pA enfant, int info){ //info sert a savoir si on le trie est AVL ou ABR
    if(papa->elmt < enfant->elmt){
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
}

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
            //faire appel aux fonctions d'equilibrage

        }
    }else return 1;
}
pA rechercheParentModifEquilibre(pA a, type e){ //dans le cas ou un element est egal a celui que l'on cree, on renvoie sa localisation, sinon c le futur parent.
    if(!estVide(a)){
        if(e< a->elmt){
            if(!estVide(a->fg)){
                //modifier l'equilibre
                a->equilibre = a->equilibre -1;
                verifEquilibre(a);
                return rechercheParentModifEquilibre;
            }else{
                return a;
            }
        }else{
            if(e> a->elmt){
                if(!estVide(a->fd)){
                //modifier l'equilibre
                a->equilibre = a->equilibre +1;
                verifEquilibre(a);
                    return rechercheParentModifEquilibre(a->fd, e);
                }else{
                    return a;
                }
            }
        }
    }
}
void creationArbre(pA a, type elmt, int info){
    pA tmp =rechercheParentCreation(a,elmt);
    if (tmp->elmt = elmt){
        tmp->doublon = tmp->doublon + 1;
        return;
    }
    if (info == 1){ //info = 1 veut dire qu'on utilise un avl
        rechercheParentModifEquilibre(a,elmt);
    }
    pA new= malloc(sizeof(Arbre));
    new -> elmt = elmt;
    new->equilibre = 0;
    new->doublon = 0;
    new = creationFils(tmp,new,info);
}



//info = 1 veut dire qu'on utilise un avl
int main (int argc, char *argv[]) {// a indique le mode souhaité entre AVL, ABR et tableau
    char a = argv[1][0];
    char test = argv [1][1];
    if (test != '\0') exit (6); //code erreur a determiner
    printf("a=%c\n",a);
    switch (a){
        case ('1') :printf("1\n") ; //traitement en AVL
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
