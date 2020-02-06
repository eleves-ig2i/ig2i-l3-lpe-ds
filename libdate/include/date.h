#ifndef date_h
#define date_h

#include <time.h>
#include <stdio.h>

typedef enum{dimanche,lundi,mardi,mercredi,jeudi,vendredi,samedi}T_Jour;
typedef struct{
    T_Jour day;
    int jour;
    int mois;
    int annee;
}T_Date;


/***********************************************************************************************/
/*Nom de la fonction : datescanf
/*Description : saisie d'une date
/*Retourne : rien
/*Effets de bord : saisie au clavier
/*Paramètres en entrée : rien
/*Paramètres en sortie : la date saisie
/***********************************************************************************************/
void datescanf(T_Date *, char*);

/***********************************************************************************************/
/*Nom de la fonction : datecpy
/*Description : copie la deuxième date dans la première
/*Retourne : rien
/*Effets de bord : rien
/*Paramètres en entrée : dateun et datedeux
/*Paramètres en sortie : rien
/***********************************************************************************************/
void datecpy(T_Date *,T_Date );

/***********************************************************************************************/
/*Nom de la fonction : dbsxtile
/*Description : retourne 1 si l'année de la date est bissextile, 0 sinon.
/*Retourne : 1 ou 0
/*Effets de bord : aucun
/*Paramètres en entrée : la date
/*Paramètres en sortie : 1 ou 0
/***********************************************************************************************/
int dbsxtile(T_Date );

/***********************************************************************************************/
/*Nom de la fonction : dsame
/*Description : retourne 1 si les deux dates proposées sont identiques, 0 sinon.
/*Retourne : 1 ou 0
/*Effets de bord : aucun
/*Paramètres en entrée : les deux dates
/*Paramètres en sortie : 1 ou 0
/***********************************************************************************************/
int dsame(T_Date ,T_Date );


/***********************************************************************************************/
/*Nom de la fonction : ddate
/*Description : retourne 1 si la date proposée est cohérente, 0 sinon.
/*Retourne : 1 ou 0
/*Effets de bord : aucun
/*Paramètres en entrée : la date (today)
/*Paramètres en sortie : 1 ou 0
/***********************************************************************************************/
int ddate(T_Date );


/***********************************************************************************************/
/*Nom de la fonction : ddaymonth
/*Description : retourne le nombre de jours dans un mois
/*Retourne : cf au dessus
/*Effets de bord : aucun
/*Paramètres en entrée : la date (jour)
/*Paramètres en sortie : le nombre de jours.
/***********************************************************************************************/
int ddaymonth(T_Date );


/***********************************************************************************************/
/*Nom de la fonction : dateprintf
/*Description : affiche la date entrée en paramètres d'entrée
/*Retourne : rien
/*Effets de bord : affichage
/*Paramètres en entrée : la date
/*Paramètres en sortie : rien
/***********************************************************************************************/
void dateprintf(T_Date , char*);

/**********************************************************************************************/
/*Nom de la fonction : drecent
/*Description : retourne 1 ou 2 en fonction des deux proposées ou 0 si les deux sont identiques
/*Retourne : cf au dessus
/*Effets de bord : aucun 
/*Paramètres en entrée : la date 1 et la date2
/*Paramètres en sortie : la plus grande date
/***********************************************************************************************/
int drecent(T_Date ,T_Date );

/**********************************************************************************************/
/*Nom de la fonction : drecentbis
/*Description : retourne 1 ou 2 en fonction des deux proposées ou 0 si les deux sont identiques
/*  		Les deux années doivent être identiques.
/*Retourne : cf au dessus
/*Effets de bord : aucun 
/*Paramètres en entrée : la date 1 et la date2
/*Paramètres en sortie : la plus grande date
/***********************************************************************************************/
int drecentbis(T_Date ,T_Date );
/**********************************************************************************************/
/*Nom de la fonction : dtomorrow
/*Description : retourne la date qui correspond au lendemain de la date en entrée
/*Retourne : cf au dessus
/*Effets de bord : aucun 
/*Paramètres en entrée : la date (today) 
/*Paramètres en sortie : le lendemain
/***********************************************************************************************/
T_Date dtomorrow(T_Date );


/**********************************************************************************************/
/*Nom de la fonction : dage
/*Description : Détermine l'âge d'une personne né pendant le jour correspondant à la date
/*Retourne : l'age
/*Effets de bord : aucun 
/*Paramètres en entrée : date
/*Paramètres en sortie : l'age
/***********************************************************************************************/
int dage(T_Date , T_Date);

/**********************************************************************************************/
/*Nom de la fonction : dcompareone
/*Description : Détermine le nombre de jours entre 1/1 et la dateun
/*Retourne : le nombre de jours
/*Effets de bord : aucun 
/*Paramètres en entrée : date
/*Paramètres en sortie : le nombre de jours
/***********************************************************************************************/
int dcompareone(T_Date );

/**********************************************************************************************/
/*Nom de la fonction : dcomparetwo
/*Description : Détermine le nombre de jours une date et le 31/12
/*Retourne : le nombre de jours
/*Effets de bord : aucun 
/*Paramètres en entrée : date et le nombre de jours
/*Paramètres en sortie : le nombre de jours
/***********************************************************************************************/
int dcomparetwo(T_Date ,int *);

/**********************************************************************************************/
/*Nom de la fonction : dcomparethree
/*Description : Détermine le nombre de jours deux dates de la même année (dateun + récent que datedeux)
/*Retourne : le nombre de jours
/*Effets de bord : aucun 
/*Paramètres en entrée : dateun, datedeux
/*Paramètres en sortie : le nombre de jours
/***********************************************************************************************/
int dcomparethree(T_Date ,T_Date );

/**********************************************************************************************/
/*Nom de la fonction : dcompare
/*Description : retourne le nombre de jours d'écart entre 2 dates (la plus récente est à gauche)
/*Retourne : cf au dessus
/*Effets de bord : aucun 
/*Paramètres en entrée : la date 1 et la date2
/*Paramètres en sortie : le nombre de jours
/***********************************************************************************************/
int dcompare(T_Date ,T_Date );

/**********************************************************************************************/
/*Nom de la fonction : dcomparebis
/*Description : retourne le nombre de jours d'écart entre (mois+jour) de deux dates
/*Retourne : cf au dessus
/*Effets de bord : aucun 
/*Paramètres en entrée : la date 1 et la date2
/*Paramètres en sortie : le nombre de jours
/***********************************************************************************************/
int dcomparebis(T_Date ,T_Date );

/**********************************************************************************************/
/*Nom de la fonction : dwhichday
/*Description : retourne le jour, correspondant à la date.
/*Retourne : cf au dessus
/*Effets de bord : aucun 
/*Paramètres en entrée : la date (date) 
/*Paramètres en sortie : le jour
/***********************************************************************************************/
T_Jour dwhichday(T_Date );


/**********************************************************************************************/
/*Nom de la fonction : dfutur
/*Description : retourne la date qui correspond à today+nbjour
/*Retourne : cf au dessus
/*Effets de bord : aucun 
/*Paramètres en entrée : la date (today) et le nombre de jours (nbjour)
/*Paramètres en sortie : la date correspond au nombre de jours
/***********************************************************************************************/
T_Date dfutur(T_Date , int );

/**********************************************************************************************/
/*Nom de la fonction : dpast
/*Description : retourne la date qui correspond à today-nbjour
/*Retourne : cf au dessus
/*Effets de bord : aucun 
/*Paramètres en entrée : la date (today) et le nombre de jours (nbjour)
/*Paramètres en sortie : la date correspond au nombre de jours
/***********************************************************************************************/
T_Date dpast(T_Date , int );

/**********************************************************************************************/
/*Nom de la fonction : dtoday
/*Description : Permet d'obtenir la date d'aujourd'hui, sur un système Linux.
/*Retourne : rien
/*Effets de bord : aucun 
/*Paramètres en entrée : Pointeur sur une date.
/*Paramètres en sortie : aucun.
/***********************************************************************************************/
void dtoday(T_Date *);


#endif



