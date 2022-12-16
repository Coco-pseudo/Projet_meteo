#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <projet.h>

// to do list: fonction absolu, finir creation fils, finir creation arbre, finir le projet :)
typedef int type;
typedef struct arbre {
    struct arbre * fd;
    struct arbre * fg;
    type elmt;
    int equilibre;
} Arbre ;
typedef Arbre * pA;

int max(int a, int b){
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
        enfant->fg = papa->fg; //cas où pour une raison qlq papa a un fg
        papa->fg = enfant;
        if(info == 1){
            papa ->equilibre = papa->equilibre - 1;
            equilibrage(papa);
            if(!estVide(enfant->fg))enfant->equilibre = -absolu(enfant->equi)
        }
    }else
    if(papa->elmt == enfant->elmt)exit(2); //données egales, avoir si on doit exit ou creer un branchement dans l'arbre pour tous ses enfants dont l'element est egal au sien
        enfant->fd = papa->fd;
        papa->fd = enfant;
        papa ->equilibre = papa->equilibre + 1;
}

int verifEquilibre(pA a){ //retourne si |l'equilibre| d'un des noeuds est  >1
    if(!estVide(a)){
        return (verifEquilibre(a->fg)<verifEquilibre(a->fd) ? verifEquilibre(a->fg) : verifEquilibre(a->fd));
    }
}
void creationArbre(type elmt){
    pA new= malloc(sizeof(Arbre));
    pA tmp =rechercheParent(elmt);
    new -> elmt = elmt;
    new->equilibre = 0;
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