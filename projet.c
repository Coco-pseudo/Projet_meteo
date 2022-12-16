#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <projet.h>

// to do list: creer fonction equilibrage d'avl, finir creation fils, finir creation arbre, finir le projet :)
// verifier si lors de l'equilibre, il faut que avoir acces au parent du noeud pour certaines rotations
// verifier les fonctions de calcul d'équilibre
typedef int type;
typedef struct arbre {
    struct arbre * fd;
    struct arbre * fg;
    type elmt;
    int equilibre;
    int doublon;
} Arbre ;
typedef Arbre * pA;



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
                        return rechercheParent(a->fd, e);
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
            return max(profondeurDescendance(fg)+1, max(profondeurDescendance(fd)+1));
        }
        return 1;
    }return 0;
}
void calculEquilibre (pA a){
    if(!estVide(a)) a->equilibre = profondeurDescendance(fg) - profondeurDescendance(fd);
}
int verifEquilibre (pA a){ //si |equilibre de l'arbre >= 2, modifie 
    if(!estVide(a)){
        if(absolu(a->equilibre >=2)){
            //faire appel aux fonctions d'equilibrage

        }
    }else return 1;
}
void creationArbre(pA arbre, type elmt){
    pA tmp =rechercheParentCreation(a,elmt);
    if (tmp->elmt = elmt){
        tmp->doublon = tmp->doublon + 1
        return;
    }
    pA new= malloc(sizeof(Arbre));
    new -> elmt = elmt;
    new->equilibre = 0;
    new->doublon = 0;
    new = creationFils(tmp,new);
}




int main (int a) {// a indique le mode souhaité entre AVL, ABR et tableau
    printf("a=%d\n",a);
    switch (a){
        case (1) :printf("1\n") ; //traitement en AVL
        break;
        case 2 :printf("2\n") ; //traitement en ABR 
        break;
        case 3 :printf("3\n")  ;//traitement en tableau
        break;
        default : 
            printf("erreur dans l'option\n"); //ne devrait pas arriver car testé dans le script
            exit(1);
            break;
    }
    return 0;
    
}
