#include "obstacle.h"
#define WIDTH 600
#define HEIGHT 600
#define NBOBSTACLES 31
Obstacle obstaclesaffichage[NBOBSTACLES];
dXPoint clapetsdepart[4]={{4.5*WIDTH/27,14.45*HEIGHT/18.},{4.5*WIDTH/27+80,14.5*HEIGHT/18+47},{13.*WIDTH/27,14.45*HEIGHT/18.},{13.*WIDTH/27-80,14.5*HEIGHT/18+47}};

void afficherpoly(int k){
	XSetForeground(display,graphicContext,(obstaclesaffichage+k)->couleurint);
	XFillPolygon(DX11,dXPtoXP((obstaclesaffichage+k)->dpoints,(obstaclesaffichage+k)->nbpoints),(obstaclesaffichage+k)->nbpoints,Convex,CoordModeOrigin);	
	XSetForeground(display,graphicContext,(obstaclesaffichage+k)->couleurbord);
	XDrawLines(DX11,dXPtoXP((obstaclesaffichage+k)->dpoints,(obstaclesaffichage+k)->nbpoints),(obstaclesaffichage+k)->nbpoints,CoordModeOrigin); 
	XFlush(display);
}

void afficherbordpoly(int k){
	XSetForeground(display,graphicContext,(obstaclesaffichage+k)->couleurbord);
	XSetLineWidth(1);
	XDrawLines(DX11,dXPtoXP((obstaclesaffichage+k)->dpoints,(obstaclesaffichage+k)->nbpoints),(obstaclesaffichage+k)->nbpoints,CoordModeOrigin); 
	XFlush(display);
}

void affichercercle(int k){
	XSetForeground(display,graphicContext,(obstaclesaffichage+k)->couleurint);
	XFillArc(DX11,(obstaclesaffichage+k)->r.x,(obstaclesaffichage+k)->r.y,(obstaclesaffichage+k)->r.width,(obstaclesaffichage+k)->r.height,0,360*64);
	XSetForeground(display,graphicContext,(obstaclesaffichage+k)->couleurbord);
	XFillArc(DX11,(obstaclesaffichage+k)->r.x-1,(obstaclesaffichage+k)->r.y-1,(obstaclesaffichage+k)->r.width,(obstaclesaffichage+k)->r.height,0,360*64);
	XFlush(display);
	}

void afficherrectangle(int k){
	XSetForeground(display,graphicContext,(obstaclesaffichage+k)->couleurint);
	XFillRectangle(DX11,(obstaclesaffichage+k)->r.x,(obstaclesaffichage+k)->r.y,(obstaclesaffichage+k)->r.width,(obstaclesaffichage+k)->r.height);
	XSetForeground(display,graphicContext,(obstaclesaffichage+k)->couleurbord);
	XFillRectangle(DX11,(obstaclesaffichage+k)->r.x+1,(obstaclesaffichage+k)->r.y+1,(obstaclesaffichage+k)->r.width-2,(obstaclesaffichage+k)->r.height-2);
	XFlush(display);
}

void afficherbille(Bille *b){
	XSetForeground(display,graphicContext,b->couleurint);
	XFillArc(DX11,b->r.x,b->r.y,b->r.width,b->r.height,0,360*64);
	XFlush(display);
	XSetForeground(display,graphicContext,b->couleurbord);
	XFillArc(DX11,b->r.x,b->r.y,b->r.width,b->r.height,0,360*64);
	XFlush(display);
}

void afficherflipperdepart(void){
	dXPoint A={23.*WIDTH/27,1.5*HEIGHT/18};
	dXPoint B={WIDTH,1.5*HEIGHT/18};
	dXPoint C={WIDTH,4.*HEIGHT/18};
	obstaclesaffichage[0]=creertriangle(A,B,C,0x0DDDFD,0x0DDDFD);
	dXPoint D={4.*WIDTH/27,1.5*HEIGHT/18};
	dXPoint E={0,1.5*HEIGHT/18};
	dXPoint F={0,4.*HEIGHT/18};
	obstaclesaffichage[1]=creertriangle(D,E,F,0x0DDDFD,0x0DDDFD);
	Rectangle rhaut={0,0,WIDTH,1.5*HEIGHT/18};
	obstaclesaffichage[2]=creerrectangle(rhaut,0x0DDDFD,0x0DDDFD);
	dXPoint polyduhaut[7]={{0,0},{WIDTH-1,0},{WIDTH-1,4*HEIGHT/18.},{23*WIDTH/27,1.5*HEIGHT/18},{4.*WIDTH/27,1.5*HEIGHT/18},{0,4.*HEIGHT/18},{0,0}};
	obstaclesaffichage[3]=creerpolygone(polyduhaut,7,0xFFFFFF,0x00AA00);
	Rectangle rbasborddroite={21.5*WIDTH/27,16*HEIGHT/18.,5.5*WIDTH/27+1,2.*HEIGHT/18};
	obstaclesaffichage[4]=creerrectangle(rbasborddroite,0x00AA00,0x00AA00);
	Rectangle rmilieudroite={17.5*WIDTH/27,5*HEIGHT/18.,4.*WIDTH/27+1,13.*HEIGHT/18};
	obstaclesaffichage[5]=creerrectangle(rmilieudroite,0xAA0000,0xAA0000);
	Rectangle rmilieugauche={12.5*WIDTH/27,16*HEIGHT/18.,5.*WIDTH/27,2.*HEIGHT/18};
	obstaclesaffichage[6]=creerrectangle(rmilieugauche,0x222222,0x222222);
	Rectangle rbasbordgauche={0,16*HEIGHT/18.,5.*WIDTH/27,2.*HEIGHT/18};
	obstaclesaffichage[7]=creerrectangle(rbasbordgauche,0x440044,0x440044);
	dXPoint G={12.5*WIDTH/27,16*HEIGHT/18.-1};
	dXPoint H={17.5*WIDTH/27-2,16*HEIGHT/18.-1};
	dXPoint I={17.5*WIDTH/27-2,14*HEIGHT/18.};
	obstaclesaffichage[8]=creertriangle(G,H,I,0x004444,0x004444);
	dXPoint J={0,16*HEIGHT/18.};
	dXPoint K={5.*WIDTH/27-1,16*HEIGHT/18.};
	dXPoint L={0,14*HEIGHT/18.};
	obstaclesaffichage[9]=creertriangle(J,K,L,0x000044,0x000044);
	dXPoint M={2.9*WIDTH/27,10.7*HEIGHT/18.};
	dXPoint N={2.9*WIDTH/27,13.*HEIGHT/18.};
	dXPoint O={5.*WIDTH/27,13.9*HEIGHT/18.};
	obstaclesaffichage[10]=creertriangle(M,N,O,0x44AAF0,0x000000);
	dXPoint P={12.5*WIDTH/27,13.9*HEIGHT/18.};
	dXPoint Q={14.6*WIDTH/27,13*HEIGHT/18.};
	dXPoint R={14.6*WIDTH/27,10.7*HEIGHT/18.};
	obstaclesaffichage[11]=creertriangle(P,Q,R,0xAA0AAA,0x000000);
	Rectangle cerclebasgauche={2.5*WIDTH/27,7.5*HEIGHT/18,1*WIDTH/18,1*HEIGHT/18};
	obstaclesaffichage[12]=creercercle(cerclebasgauche,0x000000,0xFD0D7D);
	Rectangle cerclebasdroite={12.5*WIDTH/27,7.5*HEIGHT/18,1*WIDTH/18,1*HEIGHT/18};
	obstaclesaffichage[13]=creercercle(cerclebasdroite,0x000000,0xFF6633);
	Rectangle cerclehautgauche={5.75*WIDTH/27,5.*HEIGHT/18,1*WIDTH/18,1*HEIGHT/18};
	obstaclesaffichage[14]=creercercle(cerclehautgauche,0x000000,0xFFFF00);
	Rectangle cerclehautdroite={9.75*WIDTH/27,5.*HEIGHT/18,1*WIDTH/18,1*HEIGHT/18};
	obstaclesaffichage[15]=creercercle(cerclehautdroite,0x000000,0x033FF66);
	Rectangle rbordgauche={0,4*HEIGHT/18.,2,10.*HEIGHT/18};
	obstaclesaffichage[16]=creerrectangle(rbordgauche,0x222222,0x222222);
	Rectangle rbordroit={WIDTH-2,4*HEIGHT/18.,2,12.*HEIGHT/18};
	obstaclesaffichage[17]=creerrectangle(rbordroit,0x440044,0x440044);
	dXPoint clapetgauche[3]={{clapetsdepart[0].x,clapetsdepart[0].y},{clapetsdepart[1].x,clapetsdepart[1].y},{5.*WIDTH/27,15*HEIGHT/18.}};
	obstaclesaffichage[18]=creerpolygone(clapetgauche,3,0xFFAA00,0xFFAA00);
	dXPoint clapetdroite[3]={{clapetsdepart[2].x,clapetsdepart[2].y},{clapetsdepart[3].x,clapetsdepart[3].y},{12.5*WIDTH/27,15*HEIGHT/18.}};
	obstaclesaffichage[19]=creerpolygone(clapetdroite,3,0xFFAA00,0xFFAA00);
	dXPoint anticlapetgauche[4]={{3,14*HEIGHT/18.},{1.5*WIDTH/27,13.5*HEIGHT/18.},{5.*WIDTH/27,15*HEIGHT/18.},{5.*WIDTH/27,16*HEIGHT/18.}};
	obstaclesaffichage[20]=creerpolygone(anticlapetgauche,4,0xFFFFFF,0xFFFFFF);
	dXPoint anticlapetdroite[4]={{12.5*WIDTH/27,15*HEIGHT/18.},{16.*WIDTH/27,13.5*HEIGHT/18.},{17.4*WIDTH/27,13.9*HEIGHT/18.},{12.5*WIDTH/27-4,16*HEIGHT/18.-4}};
	obstaclesaffichage[21]=creerpolygone(anticlapetdroite,4,0xFFFFFF,0xFFFFFF);
	Rectangle rectvertidroite={15.7*WIDTH/27,10.7*HEIGHT/18.,0.42*WIDTH/27,2.85*HEIGHT/18};
	obstaclesaffichage[22]=creerrectangle(rectvertidroite,0x0000FF,0x0000FF);
	dXPoint polydroite[4]={{12.5*WIDTH/27,15*HEIGHT/18.},{16.*WIDTH/27,13.5*HEIGHT/18.},{16.*WIDTH/27,13.20*HEIGHT/18.},{12.2*WIDTH/27,14.8*HEIGHT/18.}};
	obstaclesaffichage[23]=creerpolygone(polydroite,4,0xFF0000,0xFF0000);
	Rectangle rectvertigauche={1.5*WIDTH/27,10.7*HEIGHT/18.,0.42*WIDTH/27,2.85*HEIGHT/18};
	obstaclesaffichage[24]=creerrectangle(rectvertigauche,0x00FF00,0x00FF00);	
	dXPoint polygauche[4]={{5.*WIDTH/27,15*HEIGHT/18.},{1.5*WIDTH/27,13.5*HEIGHT/18.},{1.5*WIDTH/27,13.20*HEIGHT/18.},{5.3*WIDTH/27,14.8*HEIGHT/18.}};
	obstaclesaffichage[25]=creerpolygone(polygauche,4,0x00FFFF,0x00FFFF);
}

void afficherclapets(Obstacle *o){	
	dXPoint clapetgauche[3]={{round((o+15)->dpoints[0].x),round((o+15)->dpoints[0].y)},{round((o+15)->dpoints[1].x),round((o+15)->dpoints[1].y)},{round((o+15)->dpoints[2].x),round((o+15)->dpoints[2].y)}};
	obstaclesaffichage[18]=creerpolygone(clapetgauche,3,0xFFAA00,0xFFAA00);
	dXPoint clapetdroite[3]={{round((o+16)->dpoints[0].x),round((o+16)->dpoints[0].y)},{round((o+16)->dpoints[1].x),round((o+16)->dpoints[1].y)},{round((o+16)->dpoints[2].x),round((o+16)->dpoints[2].y)}};
	obstaclesaffichage[19]=creerpolygone(clapetdroite,3,0xFFAA00,0xFFAA00);
	XFlush(display);
}

void afficherflipper(void){
	afficherpoly(18);
	afficherpoly(19);
	afficherpoly(20);
	afficherpoly(21);
	afficherpoly(0);
	afficherpoly(1);
	afficherrectangle(2);
	afficherbordpoly(3);
	afficherrectangle(4);
	afficherrectangle(5);	
	afficherrectangle(6);
	afficherrectangle(7);
	afficherpoly(8);
	afficherpoly(9);
	afficherpoly(10);
	afficherpoly(11);
	affichercercle(12);
	affichercercle(13);
	affichercercle(14);	
	affichercercle(15);
	afficherrectangle(16);
	afficherrectangle(17);
	afficherrectangle(22);
	afficherpoly(23);	
	afficherrectangle(24);	
	afficherpoly(25);
	XSetForeground(display,graphicContext,0x000000);	
	XFlush(display);
}

void afficherchoixdebut(void){
	Rectangle rniveau1={18.5*WIDTH/27,8*HEIGHT/18.,2.*WIDTH/27,1.*HEIGHT/18};
	Rectangle rniveau2={18.5*WIDTH/27,10*HEIGHT/18.,2.*WIDTH/27,1.*HEIGHT/18};
	Rectangle rniveau3={18.5*WIDTH/27,12*HEIGHT/18.,2.*WIDTH/27,1.*HEIGHT/18};
	Rectangle rvecteur={18.5*WIDTH/27,14*HEIGHT/18.,2.*WIDTH/27,1.*HEIGHT/18};
	obstaclesaffichage[26]=creerrectangle(rniveau1,0x14A93D,0x54F98D);
	obstaclesaffichage[27]=creerrectangle(rniveau2,0xAE6317,0xFEA347);
	obstaclesaffichage[28]=creerrectangle(rniveau3,0x760800,0xC60800);
	obstaclesaffichage[29]=creerrectangle(rvecteur,0x803A8F,0xAE0CA7);
	afficherrectangle(26);
	afficherrectangle(27);
	afficherrectangle(28);
	afficherrectangle(29);
	char difficultee[]={"Modes de jeu"};
	char facile[]={"Lent"};
	char normal[]={"Normal"};
	char difficile[]={"Rapide"};
	char vecteur[]={"Vecteur"};
	XSetForeground(display,graphicContext,0x000000);
	XDrawString(DX11,17.95*WIDTH/27,7.55*HEIGHT/18.,difficultee,strlen(difficultee));	
	XDrawString(DX11,18.95*WIDTH/27,8.55*HEIGHT/18.,facile,strlen(facile));
	XDrawString(DX11,18.75*WIDTH/27,10.55*HEIGHT/18.,normal,strlen(normal));	
	XDrawString(DX11,18.75*WIDTH/27,12.5*HEIGHT/18.,difficile,strlen(difficile));	
	XDrawString(DX11,18.65*WIDTH/27,14.5*HEIGHT/18.,vecteur,strlen(vecteur));
	XFlush(display);
}

void presentationdujeu(void){
	nettoyer();
	static XEvent event;
	char presentation0[]={"Bonjour et bienvenue dans ce jeu de Flipper en 2D"};
	char presentation1[]={"Nous allons vous proposer un choix parmis trois niveaux de difficultee"};
	char presentation2[]={"En augmentant la difficultee de jeu, la vitesse initiale sera augmentee"};
	char presentation3[]={"Vous aurez egalement une gravite plus importante, attention a vous !"};
	char presentation4[]={"Apres, vous pourez soit lancer le jeu avec une vitesse aleatoire en cliquant sur depart"};
	char presentation5[]={"Soit choisir la direction du vecteur vitesse au depart a l'aide de la case vecteur"};
	char presentation6[]={"Attention, la difficultee choisie n'influent pas sur les points gagnes"};
	char presentation7[]={"Pour utiliser les clapets,veuillez utiliser les touches <- et ->  du clavier"};
	char presentation8[]={"Pour continuer, cliquez n'importe ou ! Nous vous souhaitons bonne chance !"};
	XSetForeground(display,graphicContext,0xFFAA66);
	XFillRectangle(DX11,0,0,WIDTH,HEIGHT);
	XSetForeground(display,graphicContext,0x000000);
	XPoint clic={0,0};
	while(clic.x==0&&clic.y==0){
		XDrawString(DX11,6*WIDTH/27,1*HEIGHT/18.,presentation0,strlen(presentation0));	
		XDrawString(DX11,3.65*WIDTH/27,3*HEIGHT/18.,presentation1,strlen(presentation1));	
		XDrawString(DX11,3.5*WIDTH/27,5*HEIGHT/18.,presentation2,strlen(presentation2));	
		XDrawString(DX11,3.75*WIDTH/27,7*HEIGHT/18.,presentation3,strlen(presentation3));	
		XDrawString(DX11,1.25*WIDTH/27,9*HEIGHT/18.,presentation4,strlen(presentation4));	
		XDrawString(DX11,2.2*WIDTH/27,11*HEIGHT/18.,presentation5,strlen(presentation5));	
		XDrawString(DX11,3.65*WIDTH/27,13*HEIGHT/18.,presentation6,strlen(presentation6));	
		XDrawString(DX11,3*WIDTH/27,15*HEIGHT/18.,presentation7,strlen(presentation7));	
		XDrawString(DX11,3.75*WIDTH/27,17*HEIGHT/18.,presentation8,strlen(presentation8));	
		XFlush(display);
		XCheckWindowEvent(display,window,ButtonPressMask,&event);
		clic.x=event.xbutton.x;
		clic.y=event.xbutton.y;
		usleep(100000);
	}
	nettoyer();
}

Obstacle creerrectangle(Rectangle r,unsigned long couleurint, unsigned long couleurbord){
	Obstacle o;
	o.r=r; 
	o.dpoints=calloc(1,sizeof(dXPoint));
	o.dpoints[0]=(dXPoint){r.x,r.y};
	o.nbpoints=1;
	o.couleurbord=couleurbord;
	o.couleurint=couleurint;
	return o;
}

Obstacle creercercle(Rectangle r,unsigned long couleurint, unsigned long couleurbord){
	Obstacle o;
	o.r=r; 
	o.dpoints=calloc(1,sizeof(dXPoint));
	o.dpoints[0]=(dXPoint){r.x+r.width/2.,r.y+r.height/2.};
	o.nbpoints=1;
	o.couleurbord=couleurbord;
	o.couleurint=couleurint;
	return o;
}

Obstacle creertriangle(dXPoint a,dXPoint b,dXPoint c,unsigned long couleurint, unsigned long couleurbord){
	Obstacle o;
	o.dpoints=calloc(3,sizeof(dXPoint));
	o.dpoints[0]=a;
	o.dpoints[1]=b;
	o.dpoints[2]=c;
	o.nbpoints=3;
	o.couleurbord=couleurbord;
	o.couleurint=couleurint;
	return o;
}

Obstacle creerpolygone(dXPoint *tab,int nbpoint,unsigned long couleurint, unsigned long couleurbord){
	Obstacle o;
	o.dpoints=calloc(nbpoint,sizeof(dXPoint));
	int k=0;
	for(;k<nbpoint;k++){
		o.dpoints[k]=tab[k];
	}
	o.nbpoints=nbpoint;
	o.couleurbord=couleurbord;
	o.couleurint=couleurint;
	return o;
}

Bille creerbille(Rectangle r,unsigned long couleurint, unsigned long couleurbord){
	Bille b;
	b.r=r;
	b.dimensions=calloc(2,sizeof(double));
	b.dimensions[0]=r.width/2.;
	b.dimensions[1]=r.height/2.;  
	b.vitesse.x=0;
	b.vitesse.y=-40;
	b.couleurbord=couleurbord;
	b.couleurint=couleurint;
	b.distance=0;
	return b;
}

XPoint *dXPtoXP(dXPoint *tab,int nbpoints){
	XPoint *tableauconverti=calloc(nbpoints,sizeof(XPoint));
	int i=0;
	for(;i<nbpoints;i++){
		tableauconverti[i].x=round(tab[i].x);
		tableauconverti[i].y=round(tab[i].y);
	}
	return tableauconverti;
}

