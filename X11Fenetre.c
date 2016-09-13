/*****************************************************
 *  Outils pour initialisation d'une fenêtre dans X11
 *    variables globales
 *    macros utiles
 *    fonctions simplifiées
 *
 *	version 2013.11.14 
 */

#include <X11/Xlib.h>
#include <X11/Xutil.h> 
#ifndef _STDLIB_H_	
	#include <stdlib.h>  
#endif

#ifndef _STDIO_H_	
#include <stdio.h>  
#endif

#ifndef _UNISTD_H_	
	#include <unistd.h>  
#endif

Display * display;			// canal de communication avec le serveur X Window
int screen;					// Le numéro de l'écran où s'affiche notre fenêtre
Window window;				// La fenêtre du programme (il peut y en avoir plusieurs)
GC graphicContext;			// Contenu graphique transmis (traits, épaisseur de trait, couleurs, ...)

// macros 
#define DX11 display,window,graphicContext 
#define SetLineWidth(width) 	XSetLineAttributes(display,graphicContext,width,LineSolid,CapButt,JoinMiter);

void dealloc(void){
	if(display) XCloseDisplay(display);
}

void initConnection(void) {
	// Appeler la fonction dealloc() avant de quitter l'application
	atexit(dealloc);
	// Ouvre la connexion au serveur XWindow
	if(!(display=XOpenDisplay(""))) {
		perror("");
	}
	// choix de l'écran parmi ceux gérés par le serveur
	screen=DefaultScreen(display);
}

void initWindow(int width,int height,char name[]){
	if(!display) {
		return;
	}
	// Création de la fenêtre 
	window=XCreateSimpleWindow(display,
	                           RootWindow(display,screen),
	                           0,0,                        // position
	                           width,height,               // dimensions
	                           2,                          // largeur du bord
	                           BlackPixel(display,screen), // couleur du bord
	                           WhitePixel(display,screen)  // couleur de fond
	                          );
	if(!window) {
		exit(-1);
	}
	XStoreName(display,window,name);	
	if(!(graphicContext=XCreateGC(display,window,0,0))) {
		exit(-1);
	}	
  
	XMapWindow(display,window);                    // la rendre visible
	XSetWindowAttributes xsetwinAtt;
	xsetwinAtt.bit_gravity=NorthWestGravity;       // comportement lors d'un rédimensionnement 
	XChangeWindowAttributes(display,window,CWBitGravity,&xsetwinAtt);
	XFlush(display);
	usleep(10000);
}

