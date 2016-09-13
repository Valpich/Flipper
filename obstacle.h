#ifndef _X11Fenetre_H_	
#include "X11Fenetre.h"  
#endif
#ifndef _outils_h_	
#include "outils.h"  
#endif
#ifndef _MATH_H_	
#include <math.h>  
#endif
#include <string.h>

typedef struct Rectangle {      //Définition de la structure Rectangle
	double x;		//Position en x du coin supérieur gauche
	double y;		//Position en y du coin supérieur gauche
	int width;		//Longueur du rectangle
	int height;		//Largueur du rectangle
} Rectangle;

typedef struct Bille {	            //Définition de la structure Bille
	Rectangle r;  		    //Rectangle circonscrit à la bille
	double * dimensions; 	    //Dimensions nécessaires pour définir la bille				
	unsigned long couleurint;   //Couleur de l'intérieur de la bille
	unsigned long couleurbord;  //Couleur du bord de la bille
	dXPoint vitesse;            //Vecteur vitesse sur chaque coordonée
	double distance; 	    //Distance entre la bille et le dernier osbtacle touché (debuggage)
} Bille;

typedef struct Obstacle {	    //Définition de la structure Obstacle
	Rectangle r;  		    //Rectangle circonscrit à l'obstacle 
	dXPoint * dpoints; 	    //Coordonnées des dXPoints nécessaires pour définir l'obstacle
	int nbpoints;		    //Le nombre de dXPoints pour définir l'obstacles
	unsigned long couleurint;   //Couleur de l'intérieur de l'obstacle
	unsigned long couleurbord;  //Couleur du bord de l'obstacle
} Obstacle;

void afficherpoly(int k);            	 //Afficher un polygone
void afficherbordpoly(int k);  		 //Afficher le bord d'un polygone
void affichercercle(int k); 	  	 //Afficher un cercle
void afficherrectangle(int k);   	 //Afficher un rectangle
void afficherbille(Bille *b);     	 //Afficher la bille
void afficherflipperdepart(void); 	 //Initiliaser l'affichage du flipper
void afficherclapets(Obstacle *o); 	 //Modification des obstacles à afficher
void afficherflipper(void); 		 //Affichage du flipper
void afficherchoixdebut(void); 		 //Afficher les choix proposés au début
void presentationdujeu(void); 		 //Presenter le jeu de flipper 

Obstacle creerrectangle(Rectangle r,unsigned long couleurint, unsigned long couleurbord); 
//Creer un obstacle rectangle à partir d'un rectangle 
Obstacle creercercle(Rectangle r,unsigned long couleurint, unsigned long couleurbord);    
//Creer un obstacle cercle à partir du rectangle dans lequel il est inscrit
Obstacle creertriangle(dXPoint a,dXPoint b,dXPoint c,unsigned long couleurint, unsigned long couleurbord); 
//Creer un obstacle triangle à partir de 3 dXPoints
Obstacle creerpolygone(dXPoint *tab,int nbpoint,unsigned long couleurint, unsigned long couleurbord); 
//Creer un obstacle polygone à partir d'un tableau de dXPoint

Bille creerbille(Rectangle r,unsigned long couleurint, unsigned long couleurbord); 
//Creer la bille

XPoint *dXPtoXP(dXPoint *tab,int nbpoints); 
//Conversion d'un tableau de dXPoint en un tableau de XPoint

