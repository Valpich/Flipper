#include "obstacle.h"
#include <stdlib.h>
#include <stdio.h>
#include "X11Fenetre.c"
#include "mouvement.h"
#define WIDTH 600
#define HEIGHT 600

int main(void){
	int a=1;
	char choix1[]={"En attente du choix du premier point"};
	char choix2[]={"En attente du choix du second point"};
	char choisi[]={"Votre vecteur est correctement saisi"};
	char jouer[]={"    Pour jouer"};
	char jouerbis[]={"   cliquez ici !"};
	initConnection(); 
	initWindow(WIDTH,HEIGHT,"Flipper");
	XSelectInput(display,window,ButtonPressMask|KeyPress);
	XPoint clic={0,0};
	XEvent event;
	nettoyer();
	usleep(10000);
	presentationdujeu();
	creerobstacles();
	afficherflipperdepart();
	afficherflipper();
	XDrawString(DX11,22.*WIDTH/27,17.*HEIGHT/18,jouer,strlen(jouer));
	XDrawString(DX11,22.*WIDTH/27,17.5*HEIGHT/18,jouerbis,strlen(jouerbis));
	afficherchoixdebut();
	XFlush(display);
	XNextEvent(display,&event);
	clic.x=event.xbutton.x;
	clic.y=event.xbutton.y;
	int attentechoix=1;
	float difficultee=0;
	dXPoint vecteur={0,0};
	while(attentechoix){
		if(clic.y>=(16.*HEIGHT/18)&&clic.y<HEIGHT){
			if (clic.x>=(21.5*WIDTH/27)&&clic.x<=(WIDTH)&&(difficultee==1||difficultee==1.5||difficultee==2)){
				attentechoix=0;
			}else{
				XCheckWindowEvent(display,window,ButtonPressMask,&event);
				clic.x=event.xbutton.x;
				clic.y=event.xbutton.y;
			}
		}
		if(clic.x>=(18.5*WIDTH/27)&&clic.x<=(20.5*WIDTH/27)){
			if(clic.y>=(8*HEIGHT/18.)&&clic.y<=(9*HEIGHT/18.)){
				difficultee=1;
			}
			if(clic.y>=(10*HEIGHT/18.)&&clic.y<=(11*HEIGHT/18.)){
				difficultee=1.5;
			}
			if(clic.y>=(12*HEIGHT/18.)&&clic.y<=(13*HEIGHT/18.)){
				difficultee=2;
			}
			if(clic.y>=(14*HEIGHT/18.)&&clic.y<=(15*HEIGHT/18.)){
				nettoyer();				
				creerobstacles();
				afficherflipperdepart();
				afficherflipper();
				afficherchoixdebut();
				XDrawString(DX11,22.*WIDTH/27,17.*HEIGHT/18,jouer,strlen(jouer));
				XDrawString(DX11,22.*WIDTH/27,17.5*HEIGHT/18,jouerbis,strlen(jouerbis));
				XDrawString(DX11,4.*WIDTH/27,10.*HEIGHT/18.,choix1,strlen(choix1));
				XNextEvent(display,&event);
				vecteur.x=event.xbutton.x;
				vecteur.y=event.xbutton.y;
				nettoyer();				
				creerobstacles();
				afficherflipperdepart();
				afficherflipper();
				afficherchoixdebut();
				XDrawString(DX11,22.*WIDTH/27,17.*HEIGHT/18,jouer,strlen(jouer));
				XDrawString(DX11,22.*WIDTH/27,17.5*HEIGHT/18,jouerbis,strlen(jouerbis));
				XDrawString(DX11,4.*WIDTH/27,10.*HEIGHT/18.,choix2,strlen(choix2));
				XNextEvent(display,&event);
				vecteur.x=event.xbutton.x-vecteur.x;
				vecteur.y=-event.xbutton.y+vecteur.y;
				nettoyer();				
				creerobstacles();
				afficherflipperdepart();
				afficherflipper();
				afficherchoixdebut();
				XDrawString(DX11,22.*WIDTH/27,17.*HEIGHT/18,jouer,strlen(jouer));
				XDrawString(DX11,22.*WIDTH/27,17.5*HEIGHT/18,jouerbis,strlen(jouerbis));
				XDrawString(DX11,4.*WIDTH/27,10.*HEIGHT/18.,choisi,strlen(choisi));
			}
			XCheckWindowEvent(display,window,ButtonPressMask,&event);
			clic.x=event.xbutton.x;
			clic.y=event.xbutton.y;
		}else{
			XCheckWindowEvent(display,window,ButtonPressMask,&event);
			clic.x=event.xbutton.x;
			clic.y=event.xbutton.y;
		}
	}
	while(a){
		int attentechoix=1;
		jouerauflipper(difficultee/2.,vecteur);
		a=gameover(difficultee);
		nettoyer();
		XPoint clic={0,0};
		XEvent event;
		usleep(10000);
		creerobstacles();
		afficherflipperdepart();
		afficherflipper();
		char jouer[]={"    Pour jouer"};
		char jouerbis[]={"   cliquez ici !"};
		XDrawString(DX11,22.*WIDTH/27,17.*HEIGHT/18,jouer,strlen(jouer));
		XDrawString(DX11,22.*WIDTH/27,17.5*HEIGHT/18,jouerbis,strlen(jouerbis));
		afficherchoixdebut();
		XFlush(display);
		XNextEvent(display,&event);
		clic.x=event.xbutton.x;
		clic.y=event.xbutton.y;
		float difficultee=0;
		dXPoint vecteur={0,0};
		while(attentechoix){
			if(clic.y>=(16.*HEIGHT/18)&&clic.y<HEIGHT){
				if (clic.x>=(21.5*WIDTH/27)&&clic.x<=(WIDTH)&&(difficultee==1||difficultee==1.5||difficultee==2)){
					attentechoix=0;
				}else{
					XCheckWindowEvent(display,window,ButtonPressMask,&event);
					clic.x=event.xbutton.x;
					clic.y=event.xbutton.y;
				}
			}
			if(clic.x>=(18.5*WIDTH/27)&&clic.x<=(20.5*WIDTH/27)){
				if(clic.y>=(8*HEIGHT/18.)&&clic.y<=(9*HEIGHT/18.)){
					difficultee=1;
				}
				if(clic.y>=(10*HEIGHT/18.)&&clic.y<=(11*HEIGHT/18.)){
					difficultee=1.5;
				}
				if(clic.y>=(12*HEIGHT/18.)&&clic.y<=(13*HEIGHT/18.)){
					difficultee=2;
				}
				if(clic.y>=(14*HEIGHT/18.)&&clic.y<=(15*HEIGHT/18.)){
					nettoyer();				
					creerobstacles();
					afficherflipperdepart();
					afficherflipper();
					afficherchoixdebut();
					XDrawString(DX11,22.*WIDTH/27,17.*HEIGHT/18,jouer,strlen(jouer));
					XDrawString(DX11,22.*WIDTH/27,17.5*HEIGHT/18,jouerbis,strlen(jouerbis));
					XDrawString(DX11,4.*WIDTH/27,10.*HEIGHT/18.,choix1,strlen(choix1));
					XNextEvent(display,&event);
					vecteur.x=event.xbutton.x;
					vecteur.y=event.xbutton.y;
					nettoyer();				
					creerobstacles();
					afficherflipperdepart();
					afficherflipper();
					afficherchoixdebut();
					XDrawString(DX11,22.*WIDTH/27,17.*HEIGHT/18,jouer,strlen(jouer));
					XDrawString(DX11,22.*WIDTH/27,17.5*HEIGHT/18,jouerbis,strlen(jouerbis));
					XDrawString(DX11,4.*WIDTH/27,10.*HEIGHT/18.,choix2,strlen(choix2));
					XNextEvent(display,&event);
					vecteur.x=event.xbutton.x-vecteur.x;
					vecteur.y=-event.xbutton.y+vecteur.y;
					nettoyer();				
					creerobstacles();
					afficherflipperdepart();
					afficherflipper();
					afficherchoixdebut();
					XDrawString(DX11,22.*WIDTH/27,17.*HEIGHT/18,jouer,strlen(jouer));
					XDrawString(DX11,22.*WIDTH/27,17.5*HEIGHT/18,jouerbis,strlen(jouerbis));
					XDrawString(DX11,4.*WIDTH/27,10.*HEIGHT/18.,choisi,strlen(choisi));
				}	
				XCheckWindowEvent(display,window,ButtonPressMask,&event);
				clic.x=event.xbutton.x;
				clic.y=event.xbutton.y;
			}else{
				XCheckWindowEvent(display,window,ButtonPressMask,&event);
				clic.x=event.xbutton.x;
				clic.y=event.xbutton.y;
			}
		}
	}	
	return 0;
}

