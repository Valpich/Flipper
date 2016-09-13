#ifndef _X11Fenetre_H_	
#include "X11Fenetre.h"  
#endif 

typedef struct dXPoint {   		//Définition de la structure Rectangle
	double x;			//Position en x du coin supérieur gauche
	double y;			//Position en y du coin supérieur gauche
} dXPoint;

int minimum(int a, int b); 		//Valeur minimale pour deux nombres
int maximum(int a,int b); 		//Valeur maximale pour deux nombres
int xmini(dXPoint *tab,int nbpoint);    //Position minimale en x pour un tableau de dXPoint
int ymini(dXPoint *tab,int nbpoint);    //Position minimale en y pour un tableau de dXPoint

double radian(double z); 		//Convertir les angles de degrés en radians
double distance(dXPoint a,dXPoint b);   //Distance entre deux dXPoint

dXPoint rotationp(dXPoint A, dXPoint B, double z); 
//Rotation d'un dXPoint par rapport à un autre d'un angle z en radian

void nettoyer(void); 			//Nettoyage complet de la fenetre 

