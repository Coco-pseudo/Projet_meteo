#!/bin/bash

while getopts ":t:p:whmFGSAOQd-:f:" opt

do
    case $opt in
        t) 
        t=1
        i=$OPTARG 
        if [ -z "$i" ]
        then
            echo "Sélectionner un mode de sélection des températures"
        fi 
        case $i in 
            1)  #min/max/moy   
            t1=1 
            ;;
            2) 
            ;;
            3) 
            ;;
            *) 
            exit 1
            ;;  
        esac


        ;; 
        p) echo "Option pression"
        p=1
        j=$OPTARG 
        if [ -z "$j" ]
        then
            echo "Sélectionner un mode de sélection des pressions"
        fi 
        case $j in 
            1) echo "Mode 1"
            ;;
            2) echo "Mode 2"
            ;;
            3) echo "Mode 3"
            ;;
            *) echo "Mode inconnue" 
            exit 1   
        esac

        ;;
        w) echo "Option de vent"
        w=1
        ;;
        h) echo "Option altitude"
        h=1
        ;;
        m) echo "Option humidité"

        ;;
        F) echo "Option localisation 1"

        ;;
        G) echo "Option localisation 2"

        ;;
        S) echo "Option localisation 3"

        ;;
        A) echo "Option localisation 4"

        ;;
        O) echo "Option localisation 5"

        ;;
        Q) echo "Option localisation 6"

        ;;
        d) echo "Option date"

        ;;
        -)
        case ${OPTARG} in
            Tab) echo "Option Tab"
            T=1
            ;;
            abr) echo "Option abr"
            a=1
            ;;
            avl) echo "Option avl"
            A=1
            ;;
            help) echo "Menu help" 
            exit 2
            ;;
            *) echo "$OPTARG: option inconnue"
            exit 1
        esac

        ;;
        f) echo "fichier"

        f=1
        I=$OPTARG
        if  [ ! -f $I ]
        then
            echo "Veuillez présicer un nom de fichier valide"
            exit 1
        fi

        ;;
        help) echo "Option help"

        ;;
        :) echo "L'option $OPTARG nécessite un argument (mode, nom de fichier)"
        exit 1
        ;;
        
        \?) echo "$OPTARG: option inconnue"
        exit 1

        ;;
    esac

done

#verif presence option fichier 
#OK




if [ -z "$f" ]
then
    echo "Sélectionner l'option fichier (obligatoire)"
fi 





#verif presence fichier dans dossier 
#OK

#traiter les options composées de chaines de caractères --> considérer - comme une option et regarder les arguments ensuite via un autre case 
#OK

#verif un seul choix parmis AVL,ABR,tab     --> si pas de choix, AVL par défaut
#ok
if   [ -z "$a" ] && [ -z "$A" ]  && [ -z "$T" ]
then
   echo "Mode de tri par default : AVL"
fi


if [ ! -z "$a" ] && [ ! -z "$A" ]
then
    echo "Un seul mode de tri autorisé"
    exit 2
fi
if [ ! -z "$a" ] && [ ! -z "$T" ]
then
    echo "Un seul mode de tri autorisé"
    exit 2
fi
if [ ! -z "$T" ] && [ ! -z "$A" ]
then
    echo "Un seul mode de tri autorisé"
    exit 2
fi
#verif deux argument pour option date, avec min, max

#verif au moins un parmis t,p,w,h

if   [ -z "$t" ] && [ -z "$p" ]  && [ -z "$w" ] && [ -z "$h" ]
then
   echo "Choisissez au moins une grandeur pour trier les données (température, pression, vent, humidité)"
fi


if [ ! -z  "$t1" ] #cas où on est en temperature mode 1
then
    echo "température mode 1"

fi






exit 0

