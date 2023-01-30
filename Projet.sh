#!/bin/bash

while getopts ":t:p:whmFGSAOQd:-:f:" opt

do
    case $opt in
        t) 
        i=$OPTARG 
        case $i in 
            1)  #min/max/moy   #il faut garder les colonnes 1 et 11 (num balise + temp)
            t=1     
            ;;
            2) 
            t=2
            ;;
            3) 
            t=3
            ;;
            12) echo "coucou"
            ;;
            *) echo "Mode inconnu/manquant "
            exit 1
            ;;  
        esac


        ;; 
        p) 
        p=1
        j=$OPTARG 
        case $j in 
            1) 
            p=1
            ;;
            2) 
            p=2
            ;;
            3) 
            p=3
            ;;
            *) echo "Mode inconnu/manquant" 
            exit 1   
        esac

        ;;
        w) 
        w=1
        ;;
        h)
        h=1
        ;;
        m) 
        m=1
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
        d) 
        i=$OPTARG
        echo $i
        #grep -q [2][0][0-2][0-9].[0-1][0-9].[0-3][0-9] - [2][0][0-2][0-9].[0-1][0-9].[0-3][0-9] $i

        ;;
        -)
        case ${OPTARG} in
            tab) echo "Option Tab"
            T=1
            ;;
            abr) echo "Option abr"
            T=2
            ;;
            avl) echo "Option avl"
            T=1
            ;;
            help)  cat help.txt | more
            exit 0
            ;;
            *) echo "--$OPTARG: option inconnue"
            exit 1
        esac

        ;;
        f) #echo "fichier"

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
        :) echo "L'option -$OPTARG nécessite un argument (mode/nom de fichier)"
        exit 1
        ;;
        
        \?) echo "-$OPTARG : option inconnue"
        exit 1

        ;;
    esac

done

#verif presence option fichier 
#OK

#verif date si mode 2/3

 


if [ -z "$f" ]
then
    echo "Sélectionner l'option fichier -f (obligatoire)"
    exit 2
fi






#verif presence fichier dans dossier 
#OK

#traiter les options composées de chaines de caractères --> considérer "-" comme une option et regarder les arguments ensuite via un autre case{...}
#OK

#verif un seul choix parmis AVL,ABR,tab     --> si pas de choix, AVL par défaut
#ok
if   [ -z "$a" ] && [ -z "$A" ]  && [ -z "$T" ]
then
    #tri par defaut : AVL
    T=3
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
#verif deux argument pour option date, avec min, max

#verif au moins un parmis t,p,w,h ==> ok

if   [ -z "$t" ] && [ -z "$p" ]  && [ -z "$w" ] && [ -z "$m" ] && [ -z "$h" ]
then
   echo "Choisissez au moins une grandeur pour trier les données ( parmis température, pression, vent, humidité, altitude)"
   exit 2
fi


if [ ! -z  "$t1" ] #cas où on est en temperature mode 1
then
    echo "température mode 1 "

fi

#tri du doc (garder que infos utiles) in progress
#option date/localisation
#executer programme c
#affichage gnuplot
#commande HELP


#-------------partie "epuration" du fichier--------------
case $t in 
    1)cut -d";" -f1,11 $I > Tmp.csv
    M=1
    ;;
    2)cut -d";" -f2,11 $I > Tmp.csv
    M=2
    ;;
    3)cut -d";" -f1,2,11 $I > Tmp.csv
    M=3
    ;;
    \?)
    exit 1
esac

case $p in 
    1)cut -d";" -f1,7 $I > Tmp.csv
    M=1
    ;;
    2)cut -d";" -f2,7 $I > Tmp.csv
    M=2
    ;;
    3)cut -d";" -f1,2,7 $I > Tmp.csv
    M=3
    ;;
    \?)
    exit 1
esac


if [ ! -z "$w" ] 
then
    if [ $w -eq 1 ] 
    then
        M=4
        cut -d";" -f1,4,5  $I > Tmp.csv
    fi
fi

if [ ! -z "$m" ] # mettre longitude, lattitude et pas Id station
then
    if [ $m -eq 1 ] 
    then
        cut -d";" -f10,6  $I > Tmp2.csv
        sed 's/,/;/g' "Tmp2.csv" >Tmp.csv
        rm Tmp2.csv 
        M=5
    fi
fi

if [ ! -z "$h" ] # mettre longitude, lattitude et pas Id station
then
    if [ $h -eq 1 ] 
    then
        cut -d";" -f14,10 $I > Tmp2.csv
        sed 's/,/;/g' "Tmp2.csv" >Tmp3.csv
        awk -F\; '{print $3";"$1";"$2}' Tmp3.csv >Tmp.csv
        rm Tmp2.csv
        rm Tmp3.csv
    fi
fi
 


#retirer la premiere ligne (avec les chaines de caractères)
sed '1d' Tmp.csv > tmp.csv
rm Tmp.csv




#-------------------utilisation du c-----------------
gcc Projet.c -o Exec 
./Exec 1 tmp.csv

sed 's/\./,/g' "ValeursRetours.csv" > ValeursRetours2.csv
rm ValeursRetours.csv
mv ValeursRetours2.csv ValeursRetours.csv







#------------------partie affichage gnuplot-----------------------



case $M in 

    1)
    cp ValeursRetours.csv testgnuplot/
    cd testgnuplot
    gnuplot Barre.gnu --persist
    cd ..
    ;;


    2)
    cd testgnuplot
    gnuplot Ligne.gnu --persist
    cd ..

    ;;




    3)
    cd testgnuplot
    gnuplot MultiLigne.gnu --persist
    cd ..
    ;;




    4)
    cd testgnuplot 
    gnuplot vecteur.gnu --persist
    cd ..
    ;;



    5)cd testgnuplot 
    gnuplot CarteInter.gnu --persist
    cd ..
    ;;



    \?)
    exit 1


esac


echo "done"
exit 0

