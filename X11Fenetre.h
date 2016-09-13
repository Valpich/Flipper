//
//  X11Fenetre.h
//  Events
//
//  Created by Bureau on 23/04/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

/* 	Compiler  avec la commande
 *	   gcc pgm.c -o pgm -Wall -lX11 
 */



#include <X11/Xlib.h>
#include <X11/Xutil.h> 

#ifndef _STDLIB_H_	
#include <stdlib.h>  
#endif

#ifndef _MATH_H_	
#include <math.h>  
#endif

#ifndef _STDIO_H_	
#include <stdio.h>  
#endif

#ifndef _UNISTD_H_	
#include <unistd.h>  
#endif

Display * display;			// canal de communication avec le serveur X Window
int screen;							// Le numéro de l'écran où s'affiche notre fenêtre
Window window;					// La fenêtre du programme (il peut y en avoir plusieurs)
GC graphicContext;			// Contenu graphique transmis (traits, épaisseur de trait, couleurs, ...)

// macros 
#define DX11 display,window,graphicContext 
#define XSetLineWidth(width)\
XSetLineAttributes(display,graphicContext,width,LineSolid,CapButt,JoinMiter);


void dealloc(void);

void initConnection(void) ;

void initWindow(int width,int height,char name[]);