#ifndef _X11Fenetre_H_	
#include "X11Fenetre.h"  
#endif
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

typedef struct Droite {   //Définition de la structure droite d'équation ax+by+c=0
	int type;
	double a;
	double b;
	double c;
	dXPoint Ad;
	dXPoint Bd;
}Droite;

Droite creerunedroite(dXPoint A,dXPoint B,int type); //Fonction qui renvoie une droite à partir de deux dXPoints

int gameover(float difficultee);		 //Fonction de gestion de la fin de la partie

bool collisiondedeuxcercle(int k); 	//Fonction qui retourne true si deux cercles sont en collision
bool collisiondroitecerclepente(int k); //Fonction qui retourne true si une droite avec une pente et un cercle sont en collision
bool collisiondroitecerclehori(int k);  //Fonction qui retourne true si une droite horizontale et un cercle sont en collision 
bool collisiondroitecercleverti(int k); //Fonction qui retourne true si une droite verticale et un cercle sont en collision
bool mouvementbille(bool succes,int affichage,float difficultee); //Fonction récursive de gestion du déplacement de la bille dans le flipper

void translationbille(void); 		 //Mouvement de la bille dans le repère (x,y)
void creerobstacles(void); 		 //Procédure de création des obstacles
void creerclapets(void); 		 //Procédure de creation des clapets
void vecteurvitessesortant(int k,float difficultee); //Procédure de calcul du vecteur vitesse après impact sur une droite
void vecteurvitessesortantdisque(int k); //Procédure de calcul du vecteur vitesse après impact sur un disque
void collisionpente(float difficultee);  //Procédure de detection de collision sur les droites ayant une pente
void creerlesdroites(void);		 //Procédure d'initiliasitation de toutes les droites
void collisionsurclapets(float difficultee); //Procédure de gestion de la collision de la bille avec les clapets
void collisionhorizontale(float difficultee);//Procédure de la gestion de la collision de la bille avec une droite horizontale
void collisionverticale(float difficultee); //Procédure de gestion de la collision de la bille avec une droite verticale
void collisiondisques(void); 		 //Procédure de gestion de la collision de la bille avec un cercle
void gererlagravite(float difficultee);  //Procédure de gestion de la gravité en supposant une inclinaison sur y
void jouerauflipper(float difficultee,dXPoint vecteur); //Procédure permettant de jouer au flipper
void animationboule(int k); 		 //Procédure créant une animation lors d'un impact sur un des disques
void animationimpactcercle(void); 	 //Procédure qui s'occupe de gérer l'ensemble animations sur des disques
void animationtriangle(void); 		 //Procédure qui s'occupe de créer une animation sur les triangles si impact sur les cotés
void mouvementclapetgauche(void); 	 //Procédure de gestion du mouvement du clapet de gauche
void mouvementclapetdroite(void); 	 //Procédure de gestion du mouvement du clapet de droite
void mouvementbilleclapetgauche(void);	 //Procédure de gestion du mouvement de la bille avec le clapet de gauche
void mouvementbilleclapetdroite(void); 	 //Procédure de gestion du mouvement de la bille avec le clapet de droite
void fermercouloir(int affichage); 	 //Procédure de fermeture du couloir de départ de la bille
void debogageflipper(float difficultee, int affichage); //Procédure de correction d'éventuelles erreurs
void chocreel(void);			 //Procédure de gestion des chocs réels
void vitessealeatoire(float difficultee);//Procédure de création d'une vitesse aleatoire pour la bille
void augmenterscore(void); 		 //Procédure de gestion du score
