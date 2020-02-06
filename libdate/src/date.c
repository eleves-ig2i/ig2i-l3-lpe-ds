#include "date.h"


/***********************************************************************************************/
/*Nom de la fonction : datescanf
/*Description : saisie d'une date
/*Retourne : rien
/*Effets de bord : saisie au clavier
/*Paramètres en entrée : la date
/*Paramètres en sortie : rien
/***********************************************************************************************/
void datescanf(T_Date *date, char *affichage) {
printf(" %s :\n ",affichage);
scanf("%02d",&date->jour);
scanf("%02d",&date->mois);
scanf("%04d",&date->annee);
date->day=dwhichday(*date);
}


/***********************************************************************************************/
/*Nom de la fonction : datecpy
/*Description : copie la deuxième date dans la première
/*Retourne : rien
/*Effets de bord : rien
/*Paramètres en entrée : dateun et datedeux
/*Paramètres en sortie : rien
/***********************************************************************************************/
void datecpy(T_Date *dateun,T_Date datedeux) {
dateun->annee=datedeux.annee;
dateun->mois=datedeux.mois;
dateun->jour=datedeux.jour;
dateun->day=datedeux.day;
}

/***********************************************************************************************/
/*Nom de la fonction : dbsxtile
/*Description : retourne 1 si l'année de la date est bissextile, 0 sinon.
/*Retourne : 1 ou 0
/*Effets de bord : aucun
/*Paramètres en entrée : la date
/*Paramètres en sortie : 1 ou 0
/***********************************************************************************************/
int dbsxtile(T_Date today) {
if( (today.annee%4==0 && today.annee%100!=0) || (today.annee%400==0) ) return 1;
else return 0;
}

/***********************************************************************************************/
/*Nom de la fonction : dsame
/*Description : retourne 1 si les deux dates proposées sont identiques, 0 sinon.
/*Retourne : 1 ou 0
/*Effets de bord : aucun
/*Paramètres en entrée : les deux dates
/*Paramètres en sortie : 1 ou 0
/***********************************************************************************************/
int dsame(T_Date dateun, T_Date datedeux) {
if(dateun.jour==datedeux.jour && dateun.mois==datedeux.mois && dateun.annee==datedeux.annee) return 1;
else return 0;
}

/***********************************************************************************************/
/*Nom de la fonction : ddate
/*Description : retourne 1 si la date proposée est cohérente, 0 sinon.
/*Retourne : 1 ou 0
/*Effets de bord : aucun
/*Paramètres en entrée : la date (today)
/*Paramètres en sortie : 1 ou 0
/***********************************************************************************************/
int ddate(T_Date today){

if(today.annee>0 && today.jour>0) {
	switch(today.mois) {
		// Mois de 31 jours
		case 1 :
		case 3 :
		case 5 :
		case 7 :
		case 8 :
		case 10 :
		case 11 :
		case 12 : if(today.jour<=31) return 1;
			  break;
		// Mois de 30 jours
		case 4 :
		case 6 :
		case 9 : if(today.jour<=30) return 1;
			 break;
		// Mois de Fevrier
		case 2 : if( (today.annee%4==0 && today.annee%100!=0) || (today.annee%400==0) ) {
				if(today.jour<=29) return 1;
				}
			  else{ if(today.jour<=28) return 1;
			 	 }
		default : return 0;
		}
	}
else{ return 0;}
}


/***********************************************************************************************/
/*Nom de la fonction : ddaymonth
/*Description : retourne le nombre de jours dans un mois
/*Retourne : cf au dessus
/*Effets de bord : aucun
/*Paramètres en entrée : la date (jour)
/*Paramètres en sortie : le nombre de jours.
/***********************************************************************************************/
int ddaymonth(T_Date date) {
switch(date.mois) {
		// Mois de 31 jours
		case 1 :
		case 3 :
		case 5 :
		case 7 :
		case 8 :
		case 10 :
		case 12 : return 31;
			  break;
		// Mois de 30 jours
		case 4 :
		case 6 :
		case 9 : 
		case 11 : return 30;
			 break;
		// Mois de Fevrier
		case 2 : if( (date.annee%4==0 && date.annee%100!=0) || (date.annee%400==0) ) {
				return 29;
				}
			  else{ return 28;
			 	 }
		default : return 0;
		}
}
		
/***********************************************************************************************/
/*Nom de la fonction : dateprintf
/*Description : affiche la date entrée en paramètres d'entrée
/*Retourne : rien
/*Effets de bord : affichage
/*Paramètres en entrée : la date
/*Paramètres en sortie : rien
/***********************************************************************************************/
void dateprintf(T_Date now,char *affichage) {
printf("%s : ",affichage);
    // Jour
    switch(now.day) {
        case dimanche : printf("Dimanche");break;
        case lundi : printf("Lundi");break;
        case mardi : printf("Mardi");break;
        case mercredi : printf("Mercredi");break;
        case jeudi : printf("Jeudi");break;
        case vendredi : printf("Vendredi");break;
        case samedi : printf("Samedi");break;
        default : printf("JOUR INCONNU");
    }
    //Numéro de jour
    printf(" %02d ",now.jour);
    //Mois
    switch(now.mois) {
        case 1 : printf("Janvier"); break;
        case 2 : printf("Fevrier"); break;
        case 3 : printf("Mars"); break;
        case 4 : printf("Avril"); break;
        case 5 : printf("Mai"); break;
        case 6 : printf("Juin"); break;
        case 7 : printf("Juillet"); break;
        case 8 : printf("Aout"); break;
        case 9 : printf("Septembre"); break;
        case 10 : printf("Octobre"); break;
        case 11 : printf("Novembre"); break;
        case 12 : printf("Decembre"); break;
        default : printf("MOIS INCONNU");
    }
    printf(" %04d\n",now.annee);
}


/**********************************************************************************************/
/*Nom de la fonction : drecent
/*Description : retourne 1 ou 2 en fonction des deux proposées ou 0 si les deux sont identiques
/*Retourne : cf au dessus
/*Effets de bord : aucun 
/*Paramètres en entrée : la date 1 et la date2
/*Paramètres en sortie : la plus grande date
/***********************************************************************************************/
int drecent(T_Date dateun,T_Date datedeux) {

if(dsame(dateun,datedeux)==1) return 0;
else{
	if(dateun.annee-datedeux.annee>0) return 1;
	else {
		if(dateun.annee-datedeux.annee<0) return 2;
		else{		// dateun.annee==datedeux.anneee
			if(dateun.mois-datedeux.mois>0) return 1;
			else {
				if(dateun.mois-datedeux.mois<0) return 2;
				else {		//dateun.mois==datedeux.mois
					if(dateun.jour-datedeux.jour>0) return 1;
					else return 2;
					}
				}
			}
		}
	}
}


/**********************************************************************************************/
/*Nom de la fonction : drecentbis
/*Description : retourne 1 ou 2 en fonction des deux proposées ou 0 si les deux sont identiques
/*  		Les deux années doivent être identiques.
/*Retourne : cf au dessus
/*Effets de bord : aucun 
/*Paramètres en entrée : la date 1 et la date2
/*Paramètres en sortie : la plus grande date
/***********************************************************************************************/
int drecentbis(T_Date dateun,T_Date datedeux) {

dateun.annee=datedeux.annee;
if(dsame(dateun,datedeux)==1) return 0;
else{
	if(dateun.mois-datedeux.mois>0) return 1;
		else {
			if(dateun.mois-datedeux.mois<0) return 2;
			else {		//dateun.mois==datedeux.mois
				if(dateun.jour-datedeux.jour>0) return 1;
				else return 2;
				}
		     }
    }
}

/**********************************************************************************************/
/*Nom de la fonction : dtomorrow
/*Description : retourne la date qui correspond au lendemain de la date en entrée
/*Retourne : cf au dessus
/*Effets de bord : aucun 
/*Paramètres en entrée : la date (today) 
/*Paramètres en sortie : le lendemain
/***********************************************************************************************/
T_Date dtomorrow(T_Date today) {

if(today.jour!=ddaymonth(today)) today.jour++;		// On est pas à la fin du mois
else{   today.jour=1;
	if(today.mois!=12) today.mois++;		// On est pas à la fin de l'année
      	else { today.mois=1;
      	       today.annee++;
      	       }
      	}
return today;
}
      		

/**********************************************************************************************/
/*Nom de la fonction : dage
/*Description : Détermine l'âge d'une personne né pendant le jour correspondant à la date
/*Retourne : l'age
/*Effets de bord : aucun 
/*Paramètres en entrée : date
/*Paramètres en sortie : l'age
/***********************************************************************************************/
int dage(T_Date birthday, T_Date today){
int save;

if(drecent(birthday,today)==2) {
	save=today.annee;
	today.annee=birthday.annee;	//Pour effectuer la comparaison entre mois et jour des deux dates.
	if(drecent(birthday,today)==1) return save-birthday.annee-1;
	else return save-birthday.annee;
	}
else {return 0;}
}

/**********************************************************************************************/
/*Nom de la fonction : dcompareone
/*Description : Détermine le nombre de jours entre 1/1 et la date
/*Retourne : le nombre de jours
/*Effets de bord : aucun 
/*Paramètres en entrée : date
/*Paramètres en sortie : le nombre de jours
/***********************************************************************************************/
int dcompareone(T_Date date) {
int nbjours;


nbjours=date.jour-1;
date.jour=1;

while(date.mois!=1) {
	(date.mois)--;
	nbjours=nbjours+ddaymonth(date);
	//printf("\n nbjours = %d jours \n",nbjours);
	}
return nbjours;
}	
	
/**********************************************************************************************/
/*Nom de la fonction : dcomparetwo
/*Description : Détermine le nombre de jours une date et le 31/12
/*Retourne : le nombre de jours
/*Effets de bord : aucun 
/*Paramètres en entrée : date et le nombre de jours
/*Paramètres en sortie : le nombre de jours
/***********************************************************************************************/
int dcomparetwo(T_Date date,int *nbjours) {
T_Date annexe={0,date.jour,12,date.annee};

*nbjours=*nbjours+31-date.jour;		//nbjours n'est pas nul !
while(annexe.mois!=date.mois) {
	(annexe.mois)--;
	*nbjours=*nbjours+ddaymonth(annexe);
	//printf("\n nbjours = %d jours \n",*nbjours);
	}
return *nbjours;
}

/**********************************************************************************************/
/*Nom de la fonction : dcomparethree
/*Description : Détermine le nombre de jours deux dates de la même année (dateun + récent que datedeux)
/*Retourne : le nombre de jours
/*Effets de bord : aucun 
/*Paramètres en entrée : dateun, datedeux
/*Paramètres en sortie : le nombre de jours
/***********************************************************************************************/
int dcomparethree(T_Date dateun, T_Date datedeux) {
int nbjours=0;

if(drecent(dateun,datedeux)==1 || drecent(dateun,datedeux)==0) {
	while(dateun.mois>datedeux.mois) {
		nbjours=nbjours+dateun.jour;
		(dateun.mois)--;
		dateun.jour=ddaymonth(dateun);
		}
	nbjours=nbjours+(dateun.jour-datedeux.jour);
	return nbjours;
	}
else {return 0;}
}
	


/**********************************************************************************************/
/*Nom de la fonction : dcompare
/*Description : retourne le nombre de jours d'écart entre 2 dates (la plus récente est à gauche)
/*Retourne : cf au dessus
/*Effets de bord : aucun 
/*Paramètres en entrée : la date 1 et la date2
/*Paramètres en sortie : le nombre de jours
/***********************************************************************************************/
int dcompare(T_Date dateun,T_Date datedeux){
int nbjours=0;

if(drecent(dateun,datedeux)==1 || drecent(dateun,datedeux)==0) {
	if(dateun.annee!=datedeux.annee) {
		//Phase 1 : xx/xx/xxxx - 1/1/xxxx
		while(dateun.annee>datedeux.annee) {
			nbjours=nbjours+dcompareone(dateun)+1;
			//printf("\n nbjours = %d \n",nbjours);
			(dateun.annee)--;
			dateun.jour=31;
			dateun.mois=12;
			//printf("Date : ");dateprintf(dateun);
			}
		//Phase 2 : 31/12/xxxx - datedeux
		dcomparetwo(datedeux,&nbjours);
		//printf("\n nbjours = %d \n",nbjours);
		//printf("Date : ");dateprintf(dateun);
		}
	else{nbjours=dcomparethree(dateun,datedeux);}
	}
return nbjours;
}


/**********************************************************************************************/
/*Nom de la fonction : dcomparebis
/*Description : retourne le nombre de jours d'écart entre (mois+jour) de deux dates
/*Retourne : cf au dessus
/*Effets de bord : aucun 
/*Paramètres en entrée : la date 1 et la date2
/*Paramètres en sortie : le nombre de jours
/***********************************************************************************************/
int dcomparebis(T_Date dateun,T_Date datedeux) {

if(drecent(dateun,datedeux)==1) 	//dateun est plus récente
	return dcomparethree(dateun,datedeux);
else if(drecent(dateun,datedeux)==2) return dcomparethree(datedeux,dateun);
     else return 0;
}



/**********************************************************************************************/
/*Nom de la fonction : dwhichday
/*Description : retourne le jour, correspondant à la date.
/*Retourne : cf au dessus
/*Effets de bord : aucun 
/*Paramètres en entrée : la date (date) 
/*Paramètres en sortie : le jour
/***********************************************************************************************/
T_Jour dwhichday(T_Date date){
T_Jour jour;
T_Date base = {dimanche,31,12,2017};		// 31 Decembre 2017 = dimanche

if(drecent(date,base)) {	//Si date=base alors on aura toujours lundi.
	if(drecent(date,base)==1) jour=(dcompare(date,base))%7;		//date est plus récente que base
	else if(drecent(date,base)==2) jour=(7-((dcompare(base,date))%7))%7;	// 1 doit devenir 6
	}
return jour;
}



/***********************************************************************************************/
/*Nom de la fonction : dfutur
/*Description : retourne la date qui correspond à today+nbjour
/*Retourne : cf au dessus
/*Effets de bord : aucun 
/*Paramètres en entrée : la date (today) et le nombre de jours (nbjours)
/*Paramètres en sortie : la date correspond au nombre de jours
/***********************************************************************************************/
T_Date dfutur(T_Date today, int nbjours) {
T_Date futur;

datecpy(&futur,today);

//On avance mois par mois
while(nbjours >= ddaymonth(futur)+1-futur.jour) {	
	nbjours=nbjours-(ddaymonth(futur)+1-futur.jour);
	futur.jour=1;
	if(futur.mois==12) { 
		futur.mois=1;
		(futur.annee)++;
		}
	else { 
		(futur.mois)++;
		}
	/*printf("\n Date futur = ");		// Pour comprendre cette partie : faire appliquer ces 3 lignes de code
	dateprintf(futur);
	printf("\n Nombre de jours restant = %d \n",nbjours);*/
	}

futur.jour=futur.jour+nbjours;
return futur;
}


/**********************************************************************************************/
/*Nom de la fonction : dpast
/*Description : retourne la date qui correspond à today-nbjour
/*Retourne : cf au dessus
/*Effets de bord : aucun 
/*Paramètres en entrée : la date (today) et le nombre de jours (nbjour)
/*Paramètres en sortie : la date correspond au nombre de jours
/***********************************************************************************************/
T_Date dpast(T_Date today, int nbjours){

//On recule mois par mois
while(nbjours >= today.jour) {	
	nbjours=nbjours-today.jour;
	if(today.mois==1) { 
		today.mois=12;
		(today.annee)--;
		}
	else { 
		(today.mois)--;
		}
	today.jour=ddaymonth(today);
	/*printf("\n Date futur = ");		// Pour comprendre cette partie : faire appliquer ces 3 lignes de code
	dateprintf(today);
	printf("\n Nombre de jours restant = %d \n",nbjours);*/
	}
today.jour=today.jour-nbjours;
return today;
}


/**********************************************************************************************/
/*Nom de la fonction : dtoday
/*Description : Permet d'obtenir la date d'aujourd'hui, sur un système Linux.
/*Retourne : rien
/*Effets de bord : aucun 
/*Paramètres en entrée : Pointeur sur une date.
/*Paramètres en sortie : aucun.
/***********************************************************************************************/
void dtoday(T_Date *date) {
    time_t now = time(NULL);
    struct tm tm_now = *localtime(&now);
    date->day = tm_now.tm_wday;
    date->jour = tm_now.tm_mday;
    date->mois = tm_now.tm_mon + 1;
    date->annee = 1900 + tm_now.tm_year;
}


