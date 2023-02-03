#!/bin/bash
FC="projetV2.c"
FH="projetV2.h"
Ftab="tableau.c"



if [  -d Data/ ]
then 
    rm -r Data/ 
fi
mkdir Data/


while getopts ":t:p:whmL:T:f:" opt

do
    case $opt in
        t) 
        i=$OPTARG 
        case $i in 
            1)  
            t=1
            var="températures_en_mode_1_"     
            ;;
            2) 
            t=2
            var="températures_en_mode_2_"
            ;;
            3) 
            t=3
            var="températures_en_mode_3_" 
            ;;

            *) echo "Mode inconnu/manquant "
            exit 2
            ;;  
        esac


        ;; 
        p) 
        p=1
        j=$OPTARG 
        case $j in 
            1) 
            p=1
            var="_pressions_en_mode_1_"
            ;;
            2) 
            p=2
            var="_pressions_en_mode_2_"
            ;;
            3) 
            p=3
            var="_pressions_en_mode_3_"
            ;;
            *) echo "Erreur interne" 
            exit 2   
        esac

        ;;
        
        w) 
        w=1
        var="_vents_"
        ;;
        
        h)
        h=1
        var="_altitudes_"
        ;;
        
        m) 
        m=1
        var="_humidités_"
        ;;
        T)
        j=$OPTARG 
        case $j in 
            1) 
            T=1
            Tri="AVL"
            ;;
            2) 
            T=2
            Tri="ABR"
            ;;
            3) 
            T=3
            Tri="Tableaux"
            ;;
            *) echo "Erreur Interne" 
            exit 2   
        esac        
        ;;
        
        L)
        j=$OPTARG 
        case $j in 
            0) 
            L=0
            Lieu=""
            ;;
            1) 
            L=1
            Lieu="en_France_Métropolitaine_et_en_Corse_"
            ;;
            2) 
            L=2
            Lieu="en_Guyanne_"
            ;;
            3)
            L=3
            Lieu="à_Saint-Pierre_et_Miquelon_"
            ;;
            4)
            L=4
            Lieu="aux_Antilles"
            ;;
            5)
            L=5
            Lieu="dans_l'Océan_Indien"
            ;;
            6)
            L=6
            Lieu="en_Antarctique"
            ;;
            *) echo "Erreur Interne" 
            exit 2   
        esac

        ;;
        
        f)

        f=1
        I=$OPTARG
        #echo "$I"
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
#-----------------Partie épuration du fichier --------------------------------------------------------------------
#-----------------------------------------------------------------------------------------------------------------
#-----------------------------------------------------------------------------------------------------------------

case $t in #conservation des colonnes souhaitée pour temp
    1)cut -d";" -f1,11,10 $I > tmp.csv 
    awk -F";" '$1!="" && $3!="" {print $0}' tmp.csv > Tmp.csv  
    awk -F\; '{print $2";"$1";"$3}' Tmp.csv > tmp.csv
    sed 's/,/;/g' "tmp.csv" >Tmp.csv
    rm tmp.csv
    M=1
    ;;


    2)cut -d";" -f2,11,10 $I > tmp.csv
    awk -F";" '$1!="" && $3!="" {print $0}' tmp.csv > Tmp.csv 
    awk -F\; '{print $2";"$1";"$3}' Tmp.csv > tmp.csv
    sed 's/,/;/g' "tmp.csv" >Tmp.csv
    rm tmp.csv
    M=2
    ;;


    3)cut -d";" -f1,2,11,10 $I > tmp.csv
    awk -F";" '$1!="" && $2!="" && $4!="" {print $0}' tmp.csv > Tmp.csv 
    awk -F\; '{print $3";"$1";"$2";"$4}' Tmp.csv > tmp.csv
    sed 's/,/;/g' "tmp.csv" >Tmp.csv
    rm tmp.csv
    M=3
    ;;


    \?)
    exit 1
esac

case $p in #conservation des colonnes souhaitée pour pression
    1)cut -d";" -f1,7,10 $I > tmp.csv
    awk -F";" '$1!="" && $2!="" {print $0}' tmp.csv > Tmp.csv
    awk -F\; '{print $3";"$1";"$2}' Tmp.csv > tmp.csv 
    sed 's/,/;/g' "tmp.csv" >Tmp.csv
    rm tmp.csv
    M=1
    ;;


    2)cut -d";" -f2,7,10 $I > tmp.csv
    awk -F";" '$1!="" && $2!="" {print $0}' tmp.csv > Tmp.csv
    awk -F\; '{print $3";"$1";"$2"}' Tmp.csv > tmp.csv  
    sed 's/,/;/g' "tmp.csv" >Tmp.csv
    rm tmp.csv
    M=2
    ;;


    3)cut -d";" -f1,2,7,10 $I > tmp.csv
    awk -F";" '$1!="" && $2!="" && $3!="" {print $0}' tmp.csv > Tmp.csv
    awk -F\; '{print $4";"$1";"$2";"$3"}' Tmp.csv > tmp.csv  
    sed 's/,/;/g' "tmp.csv" >Tmp.csv
    rm tmp.csv
    M=3
    ;;



    \?)
    exit 1
esac


if [ ! -z "$w" ] #conservation des colonnes souhaitée pour vent
then
    if [ $w -eq 1 ] 
    then
        cut -d";" -f1,4,5,10  $I > tmp.csv
        awk -F";" '$1!="" && $2!="" && $3!="" {print $0}' tmp.csv > Tmp.csv
        awk -F\; '{print $4";"$1";"$2";"$3}' Tmp.csv > tmp.csv 
        sed 's/,/;/g' "tmp.csv" > Tmp.csv 
        rm tmp.csv
        M=4

    fi
fi

if [ ! -z "$m" ] #humidité
then
    if [ $m -eq 1 ] 
    then
        cut -d";" -f1,10,6  $I > Tmp2.csv
        sed 's/,/;/g' "Tmp2.csv" >tmp.csv  #remplacer les , par des ; pour séparer les coordonnées en X et Y
        rm Tmp2.csv 
        awk -F";" '$1!="" && $2!="" && $3!="" {print $0}' tmp.csv > Tmp.csv
        awk -F\; '{print $3";"$4";"$1";"$2}' Tmp.csv > tmp.csv  
        mv tmp.csv Tmp.csv
        M=5
    fi
fi

if [ ! -z "$h" ] #altitude
then
    if [ $h -eq 1 ] 
    then
        cut -d";" -f1,14,10 $I > Tmp2.csv
        sed 's/,/;/g' "Tmp2.csv" >Tmp3.csv  #remplacer les , par des ; pour séparer les coordonnées en X et Y
        awk -F\; '{print $3";"$4";"$1";"$2}' Tmp3.csv >tmp.csv #inverser les colonnes pour simplifier le traitement
        awk -F";" '$1!="" && $2!="" && $3!="" {print $0}' tmp.csv > Tmp.csv 
        rm tmp.csv
        rm Tmp2.csv
        rm Tmp3.csv
        M=5

    fi
fi





#retirer la premiere ligne (avec les chaines de caractères)
sed '1d' Tmp.csv > tmp.csv










#-----------------------------------------------------------------------------------------------------------------
#-----------------Verif Localisation -----------------------------------------------------------------------------
#-----------------------------------------------------------------------------------------------------------------
#-----------------------------------------------------------------------------------------------------------------




#depuis  tmp.csv vers Tmp.csv vers tmp.csv
case $L in 
    0)
    #echo " Aucune restriction geographique"
    ;;



    1)
    echo "FranceMetro"
    cp tmp.csv TEST.csv
    m1="50.0"
    m2="38.0"
    m3="10.0"
    m4="-6.0"

    awk -F";" -v n4="$m4" ' $1<50 && $1>38 && $2<10 && $2>m4 {print $0 } ' tmp.csv > Tmp.csv
    #awk -F";" -v n1="$m1" -v n2="$m2" -v n3="$m3" -v n4="$m4" ' $1<=n1 && $1>=n2 && $2<=n3 && $2>=n4 {print $0} '  tmp.csv > Tmp.csv  

    cp Tmp.csv TEST.csv
    mv Tmp.csv tmp.csv
    ;;



    2)
    echo "GuyanneFra"
    cp tmp.csv Test.csv
    m1="6.0"
    m2="1.0"
    n3="-50.0"
    n4="-55.0"


    awk -F";" -v n3="$n3" -v n4="$n4" ' $1=6 && $1>1 && $2<n3 && $2>n4 {print $0} ' tmp.csv > Tmp.csv  
    mv Tmp.csv tmp.csv
    ;;



    3)
    echo "Saint-Pierre et Miquelon"
    cp tmp.csv Test.csv
    m1="48.0"
    m2="46.0"
    m3="-54.0"
    m4="-58.0"

    awk -F";" -v n3="$n3" -v n4="$n4" ' $1<48 && $1>=46  && $2 <=m3 && $2>=m4 {print $0} ' tmp.csv > Tmp.csv  # 
    mv Tmp.csv tmp.csv
    ;;



    4)
    ;;



    5)
    ;;



    6)
    ;;



    \?)
        exit 1

esac






#-----------------------------------------------------------------------------------------------------------------
#---------------------------------reareanger si option humid/altitude---------------------------------------------
#-------------------------------supprimer colonnes position si pas besoin-----------------------------------------
#-----------------------------------------------------------------------------------------------------------------

                        # tmp.csv vers Tmps.csv vers tmp.csv

case $M in 
    1)
    cut -d";" -f3,4 tmp.csv > Tmp.csv
    mv Tmp.csv tmp.csv
    ;;


    2)
    cut -d";" -f3,4 tmp.csv > Tmp.csv
    mv Tmp.csv tmp.csv
    ;;


    3)
    cut -d";" -f3,4,5 tmp.csv > Tmp.csv
    mv Tmp.csv tmp.csv
    ;;


    4)
    awk -F";" '{print $3";"$1";"$2";"$4";"$5}' tmp.csv > Tmp.csv
    mv Tmp.csv tmp.csv
    ;;


    5)
    awk -F\; '{print $3";"$4";"$1";"$2}' tmp.csv > Tmp.csv
    mv Tmp.csv tmp.csv
    ;;



    \?)
    exit 1

esac


cp tmp.csv ValeursEntrées.csv



#-----------------------------------------------------------------------------------------------------------------
#---------------------------------Utilisation du C----------------------------------------------------------------
#-----------------------------------------------------------------------------------------------------------------
#-----------------------------------------------------------------------------------------------------------------


if [ ! -s ValeursEntrées.csv ]
then
    echo "Le fichier a envoyer est Vide"
    exit 1
fi


gcc $FC $Ftab -o Exec 

if [ -f Exec ] 
then 
    if [ ! -x Exec ] #donner permission d'executer si pas déjà
    then
    chmod +x Exec
    fi
    if [ $M -eq 1 ] || [ $M -eq 2 ] || [ $M -eq 3 ] || [ $M -eq 4 ] || [ $M -eq 5 ]
    then
        #echo "Valeurs dans tmp.csv"
        ./Exec $T ValeursEntrées.csv $M 
    fi
fi

#remplacer les . par des , pour traiter les température decimales (1.000 = 1000 != 1,0)
sed 's/\./,/g' "ValeursRetours.csv" > ValeursRetours2.csv
rm ValeursRetours.csv
mv ValeursRetours2.csv ValeursRetours.csv



if [ ! -s ValeursRetours.csv ]
then
    echo "Le fichier de retour Vide"
    exit 1
fi




#-----------------------------------------------------------------------------------------------------------------
#---------------------------------Affichage Gnuplot --------------------------------------------------------------
#-----------------------------------------------------------------------------------------------------------------
#-----------------------------------------------------------------------------------------------------------------

case $M in 

    1)
    cp ValeursRetours.csv gnuplot/
    cd gnuplot
    gnuplot Barre.gnu --persist --slow
    mv Barre.png ../Data/Graphique$var$Lieu.png 
    cd ..
    
    
    ;;
#--persist permet d'ouvir une fenetre supplémentaire avec le graphique( par defaut il apparait puis disparait quasi instantanement)
#--slow permet a gnuplot d'attendre si l'acquisition des données est trop longues


    2)
    cp ValeursRetours.csv gnuplot/
    cd gnuplot
    gnuplot Ligne.gnu --persist --slow
    cd ..

    ;;




    3)
    cp ValeursRetours.csv gnuplot/
    cd gnuplot
    gnuplot MultiLigne.gnu --persist --slow
    cd ..
    ;;




    4)
    cp ValeursRetours.csv gnuplot/
    cd gnuplot 
    #echo "mode vents"
	gnuplot vecteur.gnu --persist --slow
    mv Vecteur.png ../Data/Graphique$var$Lieu.png
    cd ..
    ;;



    5)

    cp ValeursRetours.csv gnuplot/
    cd gnuplot 
    gnuplot CarteInter.gnu --persist --slow 
    mv CarteInter.png ../Data/Graphique$var$Lieu.png
    cd ..
    ;;



    \?)
    exit 1


esac

cp $I Data/ValeursInit
cp Id.csv Data/Id.csv
mv ValeursEntrées.csv Data/ValeursEntrées.csv
mv ValeursRetours.csv Data/ValeursRetours.csv
mv ValeursIdReelles.csv Data/ValeursIdReelles.csv

echo ""
echo ""
echo "Fin de traitement des $var en utilisant les $Tri $Lieu" 
echo ""
echo "Graphique enregistré sous le nom:  Graphique$var$Lieu.png dans le répertoire Data/"
echo ""
echo ""
exit 0















