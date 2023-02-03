# Projet_meteo


Projet d'Informatique 3 : CyMeteo 
	par Guedes Corentin et Gagneux Quentin





Le contenu est le suivant : 

	-Deux executable shell : Projet.sh et Traitement.sh
	
	-Les fichier c : projet.c et tableau.c
	
	-Un fichier h : projet.h
	
	-Un dossier "gnuplot" contenant les fichiers gnu : Barre.gnu, Ligne.gnu, MultiLigne.gnu, CarteInter.gnu, vecteur.gnu
	
	-Le fichier txt : help.txt
	
	-Le fichier csv : meteo_filtered_data_v1.csv (NON PRESENT DANS LE GITHUB)
	
	-Ce fichier : README.txt
	
	-Le Fichier csv : Id.csv
	


Les noms de ces fichiers devront être respéctés au caractère près afin de faire fonctionner correctement le script.

Le Projet produira au final un répertoire "Data/" contenant les données initiales(ValeursInit.csv), les données avant le traitement par le C (ValeursEntrées.csv), les données traitées par le C avec le numéro de la station(ValeursIdReelles.csv), les données traitées par le C mais avec un equivalent au numéro de station, afin de faciliter l'affichage avec gnuplot (ValeursRetours.csv), un fichier contenant la correspondance entre chaque numéro(1 à 61) et son numéro de station (Id.csv)


Appel du shell depuis un terminal:
	-se placer dans le repertoire contenant l'intégralité des fichiers requis
	-saisir :  "./Projet.sh " suivi des options.


		-f NOM avec NOM le fichier .csv à trier (ATTENTION cette option est obligatoire, le scipt ne pourra fonctionner sans)

 		
Au moins une des options suivante devra absolument être précisé afin de faire fonctionner correctement le script.
Ces options ne pourront pas être saisis simultanément 

		-t M avec M le mode* 

		
		-p M avec M le mode*

			(*) Les modes disponibles :
				
				-1 : température(ou pression) moyenne, minimal et maximal par station

				-2 : température(ou pression) moyenne par date/heure (NON-DISPONIBLE POUR LE MOMENT)

				-3 : température(ou pression) par date/heure et par station (NON-DISPONIBLE POUR LE MOMENT)
				
				Il n'est pas possible de choisir plusieurs mode en même temps(./Projet.sh -f doc.csv -t1 -t2 ne seras pas accepté)
				
	
	
		-w : L'orientation et la vitesse des vents par station (NON-DISPONIBLE POUR LE MOMENT)

		
		-h : L'altitude de chaque station (NON DISPONIBLE)


		-m : Lhumidité maximale pour chaque station (NON DISPONIBLE)

				Il est possible de choisir plusieurs mode s'ils ne concerne pas la même données (température, pression, vent, altitude, humidité)
				
					Seront acceptés, des commmandes du type ./Projet.sh -f doc.csv -t1 -p3 -w -h 







Les options suivantes ne sont pas obligatoires mais pourront permettre de restreindre le traitement des données à une zone géographique précise.
Si aucune n'est précisé, le script traitera l'ensemble des données. Attention il n'est pas possible de choisir plusieurs options parmis les suivantes.
	

		-F : Restreindre le traitement aux stations situées en France métropolitaine et en Corse


		-G : Restreindre le traitement aux stations situées en Guyanne Française (NON-DISPONIBLE POUR LE MOMENT)


		-S : Restreindre le traitement aux stations situées à Saint-Pierre et Miquelon (NON-DISPONIBLE POUR LE MOMENT)


		-A : Restreindre le traitement aux stations situées aux Antilles (NON-DISPONIBLE POUR LE MOMENT)


		-O : Restreindre le traitement aux stations situées dans l'Océan Indien (NON-DISPONIBLE POUR LE MOMENT)


		-Q : Restreindre le traitement aux stations situées en Antarctique (NON-DISPONIBLE POUR LE MOMENT)





Les options 3 suivantes ne sont pas obligatoire mais pourront permettre de choisir la méthode de tri à utiliser dans le programme C. Si aucune n'est précisé 
le tri utilisera les AVL( Arbres binaires de recherche equilibrés qui se trouve être la meilleure d'un point de vue complexité temporelle). Attention il n'est 
pas possible de choisir plusieurs options parmis les suivantes:

		--avl : utilisation des AVL (Arbres binaires de recherche equilibrés) (NON DISPONIBLE)


		--abr : utilisation des AVL (Arbres binaires de recherche non-equilibrés)


		--tab : utilisation d'un tableau (NON-DISPONIBLE POUR LE MOMENT)



Le menu d'aide

		

		--help : Affichera le menu d'aide recapitulant l'ensemble de ces informations

		
		
		
Le script pourra retourner un code erreur en fonction de la situation:

		
		
		0 : Aucun problème le script s'est exécuté jusqu'à la fin sans erreur 
		
		
		1 : Erreur liée à un fichier vide (Entrée ou Sortie)		
		
		
		2 : Erreur liée a un problème d'option (option/argument inconnu, insufisant ou trop d'option/ d'arguments)
		
		
		3 : Erreur liée aux fichiers present dans le répertoire(Absent, mal nommé)
		
		
		4 : L'option n'est pas encore disponible
		
		
		




















		
