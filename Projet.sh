#!/bin/bash
L=0
t=0
p=0
w=0
h=0
m=0

FC="projetV2.c"
FH="projetV2.h"
Ftab="tableau.c"

if [  -d Data/ ]
then 
    rm -r Data/ 
fi

#-----------------------------------------------------------------------------------------------------------------
#-----------------Verif tous les fichiers sont présent avant de commencer-----------------------------------------
#-----------------------------------------------------------------------------------------------------------------
#-----------------------------------------------------------------------------------------------------------------

if [ !  -f $FC ] #verif c present
then
    echo "Absence du fichier C ($FC)"
    exit 3
fi

if [ !  -f $Ftab ] #verif c present
then
    echo "Absence du fichier C ($Ftab)"
    exit 3
fi

 

if [ ! -f $FH  ] #verif h present
then
    echo "Absence du fichier .h pour ($FH)"
    exit 3
fi

if [ ! -f help.txt ]
then 
    echo "Absence du fichier  d'aide (help.txt)"
    exit 3
fi

if [ ! -f meteo_filtered_data_v1.csv ]
then 
    echo "Absence du fichier de données de référence (meteo_filtered_data_v1.csv)"
    exit 3
fi

if [ ! -d gnuplot ]
then
    echo "Absence du répertoire contenant les fichier gnu (gnuplot)"
    exit 3
fi

if [ ! -f gnuplot/Barre.gnu ] || [ ! -f gnuplot/Ligne.gnu ] || [ ! -f gnuplot/MultiLigne.gnu ] || [ ! -f gnuplot/CarteInter.gnu ] || [ ! -f gnuplot/vecteur.gnu ]
then 
    echo "Absence d'un(ou plusieurs) fichier(s) gnu (Barre.gnu, Ligne.gnu, MultiLigne.gnu, CarteInter.gnu, vecteur.gnu)"
    exit 3
fi





#-----------------------------------------------------------------------------------------------------------------
#-----------------Traitement Options------------------------------------------------------------------------------
#-----------------------------------------------------------------------------------------------------------------
#-----------------------------------------------------------------------------------------------------------------


while getopts ":t:p:whmFGSAOQd:-:f:" opt

do
    case $opt in
        t) 
        i=$OPTARG 
        case $i in 
            1)  
            if [ $t -ne 0 ]
            then
                echo "Un seul mode de tri par température a la fois est autorisé"
                exit 2
            fi
            t=1     
            ;;
            2)
            echo "Option -$opt$j: prochainement"
            exit 4 
            if [ $t -ne 0 ]
            then
                echo "Un seul mode de tri par température a la fois est autorisé"
                exit 2
            fi
            t=2
            ;;
            3)
            echo "Option -$opt$j: prochainement"
            exit 4
            if [ $t -ne 0 ]
            then
                echo "Un seul mode de tri par température a la fois est autorisé"
                exit 2
            fi 
            t=3
            ;;

            *) echo "Mode inconnu/manquant "
            exit 2
            ;;  
        esac


        ;; 
        p) 
        j=$OPTARG 
        case $j in 
            1)
            if [ $p -ne 0 ]
            then
                echo "Un seul mode de tri par pression a la fois est autorisé"
                exit 2
            fi 
            p=1
            ;;
            2) 
            echo "Option -$opt$j: prochainement"
            exit 4
            if [ $p -ne 0 ]
            then
                echo "Un seul mode de tri par pression a la fois est autorisé"
                exit 2
            fi 
            p=2
            ;;
            3)
            echo "Option -$opt$j: prochainement"
            exit 4
            if [ $p -ne 0 ]
            then
                echo "Un seul mode de tri par pression a la fois est autorisé"
                exit 2
            fi 
            p=3
            ;;
            *) echo "Mode inconnu/manquant" 
            exit 2   
        esac

        ;;
        
        w)
        #echo "Option -$opt: prochainement"
        #exit 4 
        w=1
        ;;
        
        h)
        #echo "Option -$opt: prochainement"
        #exit 4
        h=1
        ;;
        
        m) 
        #echo "Option -$opt: prochainement"
        #exit 4
        m=1
        ;;
        
        F) #echo "Option localisation 1"
        if [ $L -ne 0 ]
        then
            echo "Une seule Option de localisation à la fois est autorisé (parmis -F -G -S -A -O -Q)"
            exit 2
        fi
        L=1
        ;;
        
        G) #echo "Option localisation 2"
        if [ $L -ne 0 ]
        then
            echo "Une seule Option de localisation à la fois est autorisé (parmis -F -G -S -A -O -Q)"
            exit 2
        fi
        L=2

        ;;
        
        S) #echo "Option localisation 3"
        if [ $L -ne 0 ]
        then
            echo "Une seule Option de localisation à la fois est autorisé (parmis -F -G -S -A -O -Q)"
            exit 2
        fi
        L=3
        ;;
        
        A) #echo "Option localisation 4"
        echo "Option -$opt: prochainement"
        exit 4
        if [ $L -ne 0 ]
        then
            echo "Une seule Option de localisation à la fois est autorisé (parmis -F -G -S -A -O -Q)"
            exit 2
        fi        
        L=4
        ;;

        O) #echo "Option localisation 5"
        echo "Option -$opt: prochainement"
        exit 4
        if [ $L -ne 0 ]
        then
            echo "Une seule Option de localisation à la fois est autorisé (parmis -F -G -S -A -O -Q)"
            exit 2
        fi
        L=5
        ;;

        Q) #echo "Option localisation 6"
        echo "Option -$opt: prochainement"
        exit 4
        if [ $L -ne 0 ]
        then
            echo "Une seule Option de localisation à la fois est autorisé (parmis -F -G -S -A -O -Q)"
            exit 2
        fi
        L=6
        ;;
        
        d) 
        echo "Option -$opt: prochainement"
        exit 4
        i=$OPTARG
        echo $i
        #grep -q [2][0][0-2][0-9].[0-1][0-9].[0-3][0-9] - [2][0][0-2][0-9].[0-1][0-9].[0-3][0-9] $i

        ;;
        -)
        case ${OPTARG} in
            tab) #echo "Option Tab"
            #echo "Option -$opt$OPTARG: prochainement"
            #exit 4
            T=3
            ;;
            abr) #echo "Option abr"
            T=2
            ;;
            avl) #echo "Option avl"
            T=1
            ;;
            help)  cat help.txt | less
            exit 0
            ;;
            *) echo "--$OPTARG: option inconnue"
            exit 2
        esac

        ;;
        f) #echo "fichier"

        f=1
        I=$OPTARG
        if  [ ! -f $I ]
        then
            echo "Veuillez présicer un nom de fichier valide"
            exit 2
        fi      

        ;;

        :) echo "L'option -$OPTARG nécessite un argument (mode/nom de fichier)"
        exit 2
        ;;
        
        \?) echo "-$OPTARG : option inconnue"
        exit 2

        ;;
    esac

done

#-----------------------------------------------------------------------------------------------------------------
#-----------------Verif options sont présent et correct avant de commencer----------------------------------------
#-----------------------------------------------------------------------------------------------------------------
#-----------------------------------------------------------------------------------------------------------------


 


if [ -z "$f" ]
then
    echo "Sélectionner l'option fichier -f (obligatoire)"
    exit 2
fi

if [ $I = "meteo_filtered_data_v1.csv" ]
then
    echo "fichier original"
else

    echo "Il ne s'agit pas du bon fichier ($I atttendu:meteo_filtered_data_v1.csv)" 
fi

if [ ! -s $I ]
then 
    echo "Le fichier $I vide" 
    exit 1
fi



if   [ -z "$a" ] && [ -z "$A" ]  && [ -z "$T" ]
then
    #tri par defaut : AVL
    T=1
fi


if [ ! -z "$a" ] && [ ! -z "$A" ]
then
    echo "Un seul mode de tri autorisé (parmis AVL,ABR,Tab)"
    exit 2
fi
if [ ! -z "$a" ] && [ ! -z "$T" ]
then
    echo "Un seul mode de tri autorisé (parmis AVL,ABR,Tab)"
    exit 2
fi
if [ ! -z "$T" ] && [ ! -z "$A" ]
then
    echo "Un seul mode de tri autorisé (parmis AVL,ABR,Tab)"
    exit 2
fi


 
if   [ -z "$t" ] && [ -z "$p" ]  && [ -z "$w" ] && [ -z "$m" ] && [ -z "$h" ]
then
   echo "Choisissez au moins une grandeur pour trier les données ( parmis température, pression, vent, humidité, altitude)"
   exit 2
fi

if [ ! -x Traitement.sh ] #donner permission d'executer si pas déjà
    then
    chmod +x Traitement.sh
    fi

if [ $t -ne 0 ]
then
    ./Traitement.sh -f$I -t$t -T$T -L$L
fi

if [ $p -ne 0 ]
then
    ./Traitement.sh -f$I -p$p -T$T -L$L
fi

if [ $w -ne 0 ]
then
    ./Traitement.sh -f$I -w -T$T -L$L
fi

if [ $h -ne 0 ]
then
    ./Traitement.sh -f$I -h -T$T -L$L
fi

if [ $m -ne 0 ]
then
    ./Traitement.sh -f$I -m -T$T -L$L
fi



#echo "Fin normale"
exit 0

