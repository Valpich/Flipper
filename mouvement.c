#include "obstacle.h"
#include "mouvement.h"
#include <time.h>
#define WIDTH 600
#define HEIGHT 600
#define NBDROITES 36
#define NBOBSTACLES 48
#define Haut 1
#define Bas 2
#define Gauche 3
#define DROITE 4
#define Hautgauche 13
#define Hautdroite 14
#define Basgauche 23
#define Basdroite 24
#define diam 2            //Pour obstacles
#define depcolli 0.03     //Déplacement collision
Bille bille[1];
Bille billetampon[2];
Droite droites[NBDROITES];
Obstacle obstacles[NBOBSTACLES];
XEvent event;
int numerocollision=-1;
int numerocollisiondisque=-1;
int score=0;
int u=0;
int v=0;
bool sortie=0;
double tempsdepuisdebut=0;
dXPoint clapets[4]={{4.5*WIDTH/27,14.5*HEIGHT/18.},{4.5*WIDTH/27+80,14.5*HEIGHT/18+47},{13.*WIDTH/27,14.5*HEIGHT/18.},{13.*WIDTH/27-80,14.5*HEIGHT/18+47}};

Droite creerunedroite(dXPoint A,dXPoint B,int type){
	Droite d;
	d.type=type;
	d.a=(B.y-A.y);
	d.b=(A.x-B.x);
	d.c=A.y*(B.x)-A.x*(B.y);
	d.Ad=A;
	d.Bd=B;
	return d;
}

int gameover(float difficultee){
	nettoyer();
	XSelectInput(display,window,ButtonPressMask); 
	XEvent event;
	FILE *fichier=NULL;
	fichier=fopen("highscores.txt","r+");
	if(fichier==NULL){
		fichier=fopen("highscores.txt","w+");
		if(fichier!=NULL){
			printf("Le fichier contenant les scores n'a pas pu être ouvert ou n'existe pas, celui-ci est maintenant cree\n");
			fputs("00 ",fichier);
			fputs("00 ",fichier);
			fputs("00 ",fichier);
			rewind(fichier);
		}
	}
	int scores[3];
	int scorestmp[3];
	static int a=0;
	char ch0bis[100];
	if(a==0){
		fscanf(fichier,"%d %d %d ",scores,scores+1,scores+2);
		rewind(fichier);
		if(scores[0]<score){
			fprintf(fichier,"%d %d %d ",score,scores[0],scores[1]);
		}else{
			if(scores[1]<score){
				fprintf(fichier,"%d %d %d ",scores[0],score,scores[1]);
			}else{
				if(scores[2]<score){
					fprintf(fichier,"%d %d %d ",scores[0],scores[1],score);
				}
			}
		}
		a=1;	
	}
	rewind(fichier);
	fscanf(fichier,"%d %d %d ",scorestmp,scorestmp+1,scorestmp+2);
	sprintf(ch0bis,"Les meilleurs scores sont : 1er->%d 2ieme->%d 3ieme->%d ",scorestmp[0],scorestmp[1],scorestmp[2]);
	fclose(fichier);
	XSetForeground(display,graphicContext,0xFFAA66);
	XFillRectangle(DX11,0,0,WIDTH,HEIGHT);
	XSetForeground(display,graphicContext,0x66AAFF);
	XFillRectangle(DX11,2.*WIDTH/8,HEIGHT/2,WIDTH/8,HEIGHT/8);
	XSetForeground(display,graphicContext,0xAA66FF);
	XFillRectangle(DX11,5.*WIDTH/8,HEIGHT/2,WIDTH/8,HEIGHT/8);
	XSetForeground(display,graphicContext,0x000000);
	char ch0[100];
	sprintf(ch0,"Votre score est de %d !",score);
	XDrawString(DX11,2.35*WIDTH/6,1.5*HEIGHT/6,ch0,strlen(ch0));
	XDrawString(DX11,1.4*WIDTH/6,5.*HEIGHT/6,ch0bis,strlen(ch0bis));
	char ch1[]={"Vous avez laisse tomber la balle, dommage !"};
	XDrawString(DX11,1.7*WIDTH/6,2*HEIGHT/6,ch1,strlen(ch1));
	char ch2[]={"Vous pouvez recommencer ou quitter le jeu !"};
	XDrawString(DX11,1.7*WIDTH/6,2.5*HEIGHT/6,ch2,strlen(ch2));
	char ch3[]={"Recommencer"};
	XDrawString(DX11,1.55*WIDTH/6,3.4*HEIGHT/6,ch3,strlen(ch3));
	char ch4[]={"Abandonner"};
	XDrawString(DX11,3.85*WIDTH/6,3.4*HEIGHT/6,ch4,strlen(ch4));
	char ch5[]={"Flipper en C code par Clarene et Valentin !"};
	XDrawString(DX11,1.7*WIDTH/6,4.5*HEIGHT/6,ch5,strlen(ch5));
	XFlush(display);
	XNextEvent(display,&event);
	XPoint tmp;
	tmp.x=event.xbutton.x;
	tmp.y=event.xbutton.y;
	if(tmp.y>=(HEIGHT/2)&&tmp.y<5*HEIGHT/8){
		if (tmp.x>=(2.*WIDTH/8) && tmp.x<=(3.*WIDTH/8)){
			score=0;
			debogageflipper(difficultee,0);
			a=0;
			u=0;
			v=0;
			numerocollision=-1;
			numerocollisiondisque=-1;
			return 1;
		}
		if (tmp.x>=(5.*WIDTH/8) && tmp.x<=(6.*WIDTH/8)){
			exit(EXIT_SUCCESS);
		}
	}
	return gameover(difficultee);	
}

bool collisiondedeuxcercle(int k){
	double distance = sqrt(pow(((obstacles+k)->r.x+(obstacles+k)->r.width/2)-(bille->r.x+bille->r.width/2),2)+ pow((((obstacles+k)->r.y+(obstacles+k)->r.height/2)-(bille->r.y+bille->r.height/2)),2));
	if (distance > ((obstacles+k)->r.height/2 + bille->r.height/2)){
		bille->distance=2*distance;
		return false;
	}else{
		numerocollisiondisque=k;
		bille->distance=distance;
		return true;
	}
}

bool collisiondroitecerclepente(int k){
	double distance = fabs(((droites+k)->a*(bille->r.width/2.+bille->r.x))+((droites+k)->b*(bille->r.height/2.+bille->r.y))+(droites+k)->c)/sqrt(((droites+k)->a)*((droites+k)->a)+((droites+k)->b)*((droites+k)->b));
 	if ((distance <= (bille->r.height/2.))&&((bille->r.width/2.+bille->r.x)>=minimum((droites+k)->Ad.x,(droites+k)->Bd.x))&&((bille->r.width/2.+bille->r.x)<=maximum((droites+k)->Ad.x,(droites+k)->Bd.x))&&((bille->r.height/2.+bille->r.y)>=minimum((droites+k)->Ad.y,(droites+k)->Bd.y))&&((bille->r.height/2.+bille->r.y)<=maximum((droites+k)->Ad.y,(droites+k)->Bd.y))){
		numerocollision=k;
		bille->distance=distance;
		return true;
	}else{
		bille->distance=2*distance;
		return false;
	}
}

bool collisiondroitecerclehori(int k){
	double distance = fabs(((droites+k)->a*(bille->r.width/2.+bille->r.x))+((droites+k)->b*(bille->r.height/2.+bille->r.y))+(droites+k)->c)/sqrt(((droites+k)->a)*((droites+k)->a)+((droites+k)->b)*((droites+k)->b));
	if ((distance <= (bille->r.height/2.)&&((bille->r.width/2.+bille->r.x)>=minimum((droites+k)->Ad.x,(droites+k)->Bd.x))&&((bille->r.width/2.+bille->r.x)<=maximum((droites+k)->Ad.x,(droites+k)->Bd.x)))){
		numerocollision=k;
		bille->distance=distance;
		return true;
	}else{
		bille->distance=2*distance;
		return false;
	}
}


bool collisiondroitecercleverti(int k){
	double distance = fabs(((droites+k)->a*(bille->r.width/2.+bille->r.x))+((droites+k)->b*(bille->r.height/2.+bille->r.y))+(droites+k)->c)/sqrt(((droites+k)->a)*((droites+k)->a)+((droites+k)->b)*((droites+k)->b));
	if ((distance <= (bille->r.height/2.)&&((bille->r.width/2.+bille->r.y)>minimum((droites+k)->Ad.y,(droites+k)->Bd.y))&&((bille->r.width/2.+bille->r.y)<=maximum((droites+k)->Ad.y,(droites+k)->Bd.y)))){
		numerocollision=k;
		bille->distance=distance;
		return true;
	}else{
		bille->distance=2*distance;
		return false;
	}
}

bool mouvementbille(bool succes,int affichage,float difficultee){
	int ralenti=0;	
	char scores[100];
	char tempsdejeu[100];
	int timerminutes=(int)((-tempsdepuisdebut+(double)time(NULL))/60);
	int timersecondes=((int)(-tempsdepuisdebut+(double)time(NULL)))%60;
	if(affichage==0) nettoyer(); 
	if(affichage==0) billetampon[1]=billetampon[0];
	dXPoint clapetgauche[3]={{clapets[0].x,clapets[0].y},{clapets[1].x,clapets[1].y},{5.*WIDTH/27,15*HEIGHT/18.}};
	dXPoint clapetdroite[3]={{clapets[2].x,clapets[2].y},{clapets[3].x,clapets[3].y},{12.5*WIDTH/27,15*HEIGHT/18.}};
	obstacles[15]=creerpolygone(clapetgauche,3,0xFFAA00,0xFFAA00);
	obstacles[16]=creerpolygone(clapetdroite,3,0xFFAA00,0xFFAA00);
	XGrabKeyboard(display,DefaultRootWindow(display),True,GrabModeAsync,GrabModeAsync,CurrentTime);
	if(XCheckMaskEvent(display,KeyPress,&event)||u<60||v<60){
		int kc;
		kc=((XKeyPressedEvent*)&event)->keycode;
		switch(kc){
			case 113:
				mouvementclapetgauche();
				if(u<59){
					u=u+2;
				}
				break;
			case 114:
				mouvementclapetdroite();
				if(v<59){
					v=v+2;
				}
				break;
		}
	}
	if(u==60){
		u=0;
		event.xbutton.button=Button4;
	}
	if(v==60){
		v=0;
		event.xbutton.button=Button4;
	}	
	afficherclapets(obstacles);
	if(affichage==0) afficherflipper();
	if(affichage==0) afficherbille(bille);
	XSetForeground(display,graphicContext,0x000000);
	if(bille->r.y+WIDTH/20<(obstacles+25)->dpoints[0].y) sortie=1;
	sprintf(scores,"Votre score est de %d !",score);
	sprintf(tempsdejeu,"Votre temps de jeu est de %d minutes et %d secondes !",timerminutes,timersecondes);
	if(affichage==0){
		XDrawString(DX11,2.35*WIDTH/6,0.2*HEIGHT/6,scores,strlen(scores));
		XDrawString(DX11,1.5*WIDTH/6,0.4*HEIGHT/6,tempsdejeu,strlen(tempsdejeu));
	}
	creerclapets();
	for(ralenti=0;ralenti<10;ralenti++){
		billetampon[0]=bille[0];
		translationbille();
		collisiondisques();
		if((bille->vitesse.x==billetampon->vitesse.x)&&(bille->vitesse.y==billetampon->vitesse.y)){
			collisionpente(difficultee);
		}
		if((bille->vitesse.x==billetampon->vitesse.x)&&(bille->vitesse.y==billetampon->vitesse.y)){
			collisionsurclapets(difficultee);	
		}
		if((bille->vitesse.x==billetampon->vitesse.x)&&(bille->vitesse.y==billetampon->vitesse.y)){
			collisionhorizontale(difficultee);
		}
		if((bille->vitesse.x==billetampon->vitesse.x)&&(bille->vitesse.y==billetampon->vitesse.y)){
			collisionverticale(difficultee);
		}
		chocreel();
		if(numerocollision!=-1||numerocollisiondisque!=-1) break;
	}
	augmenterscore();
	fermercouloir(affichage);
	animationimpactcercle();
	animationtriangle();
	debogageflipper(difficultee,affichage);
	usleep(1000000/120);
	if(1!=((bille->r.x+WIDTH/36>(obstacles+25)->dpoints[0].x)&&(bille->r.y+WIDTH/36>(obstacles+25)->dpoints[0].y))){
		gererlagravite(difficultee);
	}
	if(numerocollision==26){
		augmenterscore();
		numerocollision=-1;
		numerocollisiondisque=-1;
		succes=0;
		u=0;
		v=0;
		return succes;
	}else{
		affichage++;
		if(affichage==3) affichage=0;
		numerocollision=-1;
		numerocollisiondisque=-1;
		mouvementbille(succes,affichage,difficultee);
	}
	return succes;
}

void translationbille(void){ 
	bille->r.x=bille->r.x+bille->vitesse.x/10.;	
	bille->r.y=bille->r.y+bille->vitesse.y/10.;
}

void creerobstacles(void){
	dXPoint A={23.*WIDTH/27,1.5*HEIGHT/18};
	dXPoint B={WIDTH,1.5*HEIGHT/18};
	dXPoint C={WIDTH,4.*HEIGHT/18};
	obstacles[0]=creertriangle(A,B,C,0x0DDDFD,0x0DDDFD);
	dXPoint D={4.*WIDTH/27,1.5*HEIGHT/18};
	dXPoint E={0,1.5*HEIGHT/18};
	dXPoint F={0,4.*HEIGHT/18};
	obstacles[1]=creertriangle(D,E,F,0x0DDDFD,0x0DDDFD);
	Rectangle rhaut={0,0,WIDTH,1.5*HEIGHT/18};
	obstacles[2]=creerrectangle(rhaut,0x0DDDFD,0x0DDDFD);
	Rectangle rbasborddroite={21.5*WIDTH/27,16*HEIGHT/18.,5.5*WIDTH/27+1,2.*HEIGHT/18};
	obstacles[3]=creerrectangle(rbasborddroite,0x00AA00,0x00AA00);
	Rectangle rmilieudroite={17.5*WIDTH/27,5*HEIGHT/18.,4.*WIDTH/27,13.*HEIGHT/18};
	obstacles[4]=creerrectangle(rmilieudroite,0xAA0000,0xAA0000);
	Rectangle rmilieugauche={12.5*WIDTH/27,16*HEIGHT/18.,5.*WIDTH/27,2.*HEIGHT/18};
	obstacles[5]=creerrectangle(rmilieugauche,0x222222,0x222222);
	Rectangle rbasbordgauche={0,16*HEIGHT/18.,5.*WIDTH/27,2.*HEIGHT/18};
	obstacles[6]=creerrectangle(rbasbordgauche,0x440044,0x440044);
	dXPoint H={17.5*WIDTH/27,16*HEIGHT/18.};
	dXPoint I={17.5*WIDTH/27,14*HEIGHT/18.};
	obstacles[7]=creertriangle((obstacles+5)->dpoints[0],H,I,0x004444,0x004444);
	dXPoint J={0,16*HEIGHT/18.};
	dXPoint K={5.*WIDTH/27,16*HEIGHT/18.};
	dXPoint L={0,14*HEIGHT/18.};
	obstacles[8]=creertriangle(J,K,L,0x000044,0x000044);
	dXPoint M={2.9*WIDTH/27,10.7*HEIGHT/18.};
	dXPoint N={2.9*WIDTH/27,13.*HEIGHT/18.};
	dXPoint O={5.*WIDTH/27,13.9*HEIGHT/18.};
	obstacles[9]=creertriangle(M,N,O,0x440000,0x440000);
	dXPoint P={12.5*WIDTH/27,13.9*HEIGHT/18.};
	dXPoint Q={14.6*WIDTH/27,13*HEIGHT/18.};
	dXPoint R={14.6*WIDTH/27,10.7*HEIGHT/18.};
	obstacles[10]=creertriangle(P,Q,R,0xAA0AAA,0xAA0AAA);
	Rectangle cerclebasgauche={2.5*WIDTH/27,7.5*HEIGHT/18,1*WIDTH/18,1*HEIGHT/18};
	obstacles[11]=creercercle(cerclebasgauche,0xFD0D7D,0xFD0D7D);
	Rectangle cerclebasdroite={12.5*WIDTH/27,7.5*HEIGHT/18,1*WIDTH/18,1*HEIGHT/18};
	obstacles[12]=creercercle(cerclebasdroite,0xFF6633,0xFF6633);
	Rectangle cerclehautgauche={5.75*WIDTH/27,5.*HEIGHT/18,1*WIDTH/18,1*HEIGHT/18};
	obstacles[13]=creercercle(cerclehautgauche,0xFFFF00,0xFFFF00);
	Rectangle cerclehautdroite={9.75*WIDTH/27,5.*HEIGHT/18,1*WIDTH/18,1*HEIGHT/18};
	obstacles[14]=creercercle(cerclehautdroite,0x33FF66,0x033FF66);
	dXPoint clapetgauche[3]={{clapets[0].x,clapets[0].y},{clapets[1].x,clapets[1].y},{5.*WIDTH/27,15*HEIGHT/18.}};
	obstacles[15]=creerpolygone(clapetgauche,3,0xFFAA00,0xFFAA00);
	dXPoint clapetdroite[3]={{clapets[2].x,clapets[2].y},{clapets[3].x,clapets[3].y},{12.5*WIDTH/27,15*HEIGHT/18.}};
	obstacles[16]=creerpolygone(clapetdroite,3,0xFFAA00,0xFFAA00);
	Rectangle rectvertidroite={15.7*WIDTH/27,10.7*HEIGHT/18.,0.42*WIDTH/27,2.85*HEIGHT/18};
	obstacles[17]=creerrectangle(rectvertidroite,0x0000FF,0x0000FF);
	dXPoint polydroite[4]={{12.5*WIDTH/27,15*HEIGHT/18.},{16.12*WIDTH/27,13.5*HEIGHT/18.},{16.12*WIDTH/27,13.20*HEIGHT/18.},{12.2*WIDTH/27,14.8*HEIGHT/18.}};
	obstacles[18]=creerpolygone(polydroite,4,0xFF0000,0xFF0000);
	Rectangle rectvertigauche={1.5*WIDTH/27,10.7*HEIGHT/18.,0.42*WIDTH/27,2.85*HEIGHT/18};
	obstacles[19]=creerrectangle(rectvertigauche,0x00FF00,0x00FF00);	
	dXPoint polygauche[4]={{5.*WIDTH/27,15*HEIGHT/18.},{1.5*WIDTH/27,13.5*HEIGHT/18.},{1.5*WIDTH/27,13.20*HEIGHT/18.},{5.3*WIDTH/27,14.8*HEIGHT/18.}};
	obstacles[20]=creerpolygone(polygauche,4,0x00FFFF,0x00FFFF);
	Rectangle rectf={(obstacles+1)->dpoints[2].x-diam/2,(obstacles+1)->dpoints[2].y-diam/2,diam,diam};
	obstacles[21]=creercercle(rectf,0x000000,0x000000);
	Rectangle rectd={(obstacles+1)->dpoints[0].x-diam/2,(obstacles+1)->dpoints[0].y-diam/2,diam,diam};
	obstacles[22]=creercercle(rectd,0x000000,0x000000);
	Rectangle recta={(obstacles)->dpoints[0].x-diam/2,(obstacles)->dpoints[0].y-diam/2,diam,diam};
	obstacles[23]=creercercle(recta,0x000000,0x000000);
	Rectangle rectc={(obstacles)->dpoints[2].x-diam/2,(obstacles)->dpoints[2].y-diam/2,diam,diam};
	obstacles[24]=creercercle(rectc,0x000000,0x000000);
	Rectangle rectg={(obstacles+4)->dpoints[0].x-diam/2+(obstacles+4)->r.width,(obstacles+4)->dpoints[0].y-diam/2,diam,diam};
	obstacles[25]=creercercle(rectg,0x000000,0x000000);
	Rectangle rectgbis={(obstacles+4)->dpoints[0].x-diam/2,(obstacles+4)->dpoints[0].y-diam/2,diam,diam};
	obstacles[26]=creercercle(rectgbis,0x000000,0x000000);
	Rectangle recti={(obstacles+7)->dpoints[2].x-diam/2,(obstacles+7)->dpoints[2].y-diam/2,diam,diam};
	obstacles[27]=creercercle(recti,0x000000,0x000000);
	Rectangle recth={(obstacles+5)->dpoints[0].x-diam/2,(obstacles+5)->dpoints[0].y-diam/2,diam,diam};
	obstacles[28]=creerrectangle(recth,0x000000,0x000000);
	Rectangle rectj={(obstacles+6)->dpoints[0].x-diam/2+(obstacles+6)->dpoints[0].x,(obstacles+6)->dpoints[0].y-diam/2,diam,diam};
	obstacles[29]=creercercle(rectj,0x000000,0x000000);
	Rectangle rectl={(obstacles+8)->dpoints[2].x-diam/2,(obstacles+8)->dpoints[2].y-diam/2,diam,diam};
	obstacles[30]=creercercle(rectl,0x000000,0x000000);
	Rectangle rectclapgauche={clapets[1].x-diam/2,clapets[1].y-diam/2,diam,diam};
	obstacles[31]=creercercle(rectclapgauche,0x000000,0x000000);
	Rectangle rectclapdroite={clapets[3].x-diam/2,clapets[3].y-diam/2,diam,diam};
	obstacles[32]=creercercle(rectclapdroite,0x000000,0x000000);
	Rectangle rects={(obstacles+20)->dpoints[0].x-diam/2,(obstacles+20)->dpoints[0].y-diam/2,diam,diam};
	obstacles[33]=creercercle(rects,0x000000,0x000000);
	Rectangle rectt={(obstacles+20)->dpoints[1].x-diam/2,(obstacles+20)->dpoints[1].y-diam/2,diam,diam};
	obstacles[34]=creercercle(rectt,0x000000,0x000000);
	Rectangle rectu={(obstacles+19)->dpoints[0].x-diam/2,(obstacles+19)->dpoints[0].y-diam/2,diam,diam};
	obstacles[35]=creercercle(rectu,0x000000,0x000000);
	Rectangle rectv={(obstacles+19)->dpoints[0].x-diam/2+(obstacles+19)->r.width,(obstacles+19)->dpoints[0].y-diam/2,diam,diam};
	obstacles[36]=creercercle(rectv,0x000000,0x000000);
	Rectangle rectm={(obstacles+9)->dpoints[0].x-diam/2,(obstacles+9)->dpoints[0].y-diam/2,diam,diam};
	obstacles[37]=creercercle(rectm,0x000000,0x000000);
	Rectangle rectn={(obstacles+9)->dpoints[1].x-diam/2,(obstacles+9)->dpoints[1].y-diam/2,diam,diam};
	obstacles[38]=creercercle(rectn,0x000000,0x000000);
	Rectangle recto={(obstacles+9)->dpoints[2].x-diam/2,(obstacles+9)->dpoints[2].y-diam/2,diam,diam};	
	obstacles[39]=creercercle(recto,0x000000,0x000000);
	Rectangle rectp={(obstacles+10)->dpoints[0].x-diam/2,(obstacles+10)->dpoints[0].y-diam/2,diam,diam};	
	obstacles[40]=creercercle(rectp,0x000000,0x000000);
	Rectangle rectq={(obstacles+10)->dpoints[1].x-diam/2,(obstacles+10)->dpoints[1].y-diam/2,diam,diam};
	obstacles[41]=creercercle(rectq,0x000000,0x000000);
	Rectangle rectr={(obstacles+10)->dpoints[2].x-diam/2,(obstacles+10)->dpoints[2].y-diam/2,diam,diam};
	obstacles[42]=creercercle(rectr,0x000000,0x000000);
	Rectangle rectw={(obstacles+17)->dpoints[0].x-diam/2,(obstacles+17)->dpoints[0].y-diam/2,diam,diam};
	obstacles[43]=creercercle(rectw,0x000000,0x000000);
	Rectangle rectx={(obstacles+17)->dpoints[0].x-diam/2+(obstacles+17)->r.width,(obstacles+17)->dpoints[0].y-diam/2,diam,diam};
	obstacles[44]=creercercle(rectx,0x000000,0x000000);
	Rectangle recty={(obstacles+18)->dpoints[1].x-diam/2,(obstacles+18)->dpoints[1].y-diam/2,diam,diam};
	obstacles[45]=creercercle(recty,0x000000,0x000000);
	Rectangle rectz={(obstacles+18)->dpoints[0].x-diam/2,(obstacles+18)->dpoints[0].y-diam/2,diam,diam};
	obstacles[46]=creercercle(rectz,0x000000,0x000000);
	Rectangle fermeture={(obstacles+4)->dpoints[0].x+(obstacles+4)->r.width,(obstacles+4)->dpoints[0].y,5.5*WIDTH/27,HEIGHT/18.};
	obstacles[47]=creerrectangle(fermeture,0x000000,0x000000);
}

void creerclapets(void){	
	dXPoint clapetgauche[3]={{(obstacles+15)->dpoints[0].x,(obstacles+15)->dpoints[0].y},{(obstacles+15)->dpoints[1].x,(obstacles+15)->dpoints[1].y},{(obstacles+15)->dpoints[2].x,(obstacles+15)->dpoints[2].y}};
	obstacles[15]=creerpolygone(clapetgauche,3,0xFFAA00,0xFFAA00);
	dXPoint clapetdroite[3]={{(obstacles+16)->dpoints[0].x,(obstacles+16)->dpoints[0].y},{(obstacles+16)->dpoints[1].x,(obstacles+16)->dpoints[1].y},{(obstacles+16)->dpoints[2].x,(obstacles+16)->dpoints[2].y}};
	obstacles[16]=creerpolygone(clapetdroite,3,0xFFAA00,0xFFAA00);
	Rectangle rectclapgauche={(obstacles+15)->dpoints[1].x-diam/2,(obstacles+15)->dpoints[1].y-diam/2,diam,diam};
	obstacles[31]=creercercle(rectclapgauche,0x000000,0x000000);
	Rectangle rectclapdroite={(obstacles+16)->dpoints[1].x-diam/2,(obstacles+16)->dpoints[1].y-diam/2,diam,diam};
	obstacles[32]=creercercle(rectclapdroite,0x000000,0x000000);
	droites[6]=creerunedroite((obstacles+20)->dpoints[0],(obstacles+15)->dpoints[1],Basgauche);
	droites[7]=creerunedroite((obstacles+15)->dpoints[0],(obstacles+15)->dpoints[1],Hautdroite);
	droites[8]=creerunedroite((obstacles+16)->dpoints[1],(obstacles+16)->dpoints[0],Hautdroite);
	droites[9]=creerunedroite((obstacles+16)->dpoints[1],(obstacles+18)->dpoints[0],Basdroite);
}

void vecteurvitessesortant(int k,float difficultee){
	dXPoint Aincident={billetampon->r.x,billetampon->r.y};
	dXPoint Bincident={bille->r.x,bille->r.y};
	Droite incidente=creerunedroite(Aincident,Bincident,0);
	double alpha=3.14159-2*atan((((droites+k)->a)*(incidente.b)-(incidente.a)*((droites+k)->b))/((((droites+k)->a)*(incidente.a))+(((droites+k)->b)*(incidente.b))));
	dXPoint Creflechi=rotationp(Aincident,Bincident,alpha);
	switch((droites+numerocollision)->type){
		case Hautgauche:
			bille[0]=billetampon[0];
			bille->vitesse.x=10*(Creflechi.x-Bincident.x)-depcolli*difficultee;
			bille->vitesse.y=10*(Creflechi.y-Bincident.y)-2*depcolli*difficultee;
			break;
		case Hautdroite:
			bille[0]=billetampon[0];
			bille->vitesse.x=10*(Creflechi.x-Bincident.x)+depcolli*difficultee;
			bille->vitesse.y=10*(Creflechi.y-Bincident.y)-2*depcolli*difficultee;
			break;
		case Basgauche:
			bille[0]=billetampon[0];
			bille->vitesse.x=10*(Creflechi.x-Bincident.x)-depcolli*difficultee;
			bille->vitesse.y=10*(Creflechi.y-Bincident.y)+2*depcolli*difficultee;
			break;
		case Basdroite:
			bille[0]=billetampon[0];
			bille->vitesse.x=10*(Creflechi.x-Bincident.x)+depcolli*difficultee;
			bille->vitesse.y=10*(Creflechi.y-Bincident.y)+2*depcolli*difficultee;
			break;
	}
}

void vecteurvitessesortantdisque(int k){
	dXPoint Aincident={billetampon->r.x,billetampon->r.y};
	dXPoint Bincident={bille->r.x,bille->r.y};
	Droite incidente=creerunedroite(Aincident,Bincident,0);
	double alpha=3.14159-2*atan((((droites+k)->a)*(incidente.b)-(incidente.a)*((droites+k)->b))/((((droites+k)->a)*(incidente.a))+(((droites+k)->b)*(incidente.b))));
	dXPoint Creflechi=rotationp(Aincident,Bincident,alpha);;
	bille[0]=billetampon[0];
	bille->vitesse.x=10*(Creflechi.x-Bincident.x);
	bille->vitesse.y=10*(Creflechi.y-Bincident.y);
}

void collisionpente(float difficultee){
	if (collisiondroitecerclepente(0)||collisiondroitecerclepente(2)||collisiondroitecerclepente(5)||collisiondroitecerclepente(10)||collisiondroitecerclepente(14)||collisiondroitecerclepente(15)||collisiondroitecerclepente(16)||collisiondroitecerclepente(17)||collisiondroitecerclepente(19)||collisiondroitecerclepente(23)||collisiondroitecerclepente(24)||collisiondroitecerclepente(28)){ 
		vecteurvitessesortant(numerocollision,difficultee);   
	}
}

void creerlesdroites(void){
	dXPoint A={(obstacles+4)->dpoints[0].x+(obstacles+4)->r.width,(obstacles+4)->dpoints[0].y};
	dXPoint B={(obstacles+19)->dpoints[0].x+(obstacles+19)->r.width,(obstacles+19)->dpoints[0].y+(obstacles+20)->r.height};
	dXPoint C={(obstacles+19)->dpoints[0].x+(obstacles+19)->r.width,(obstacles+19)->dpoints[0].y};
	dXPoint D={(obstacles+17)->dpoints[0].x,(obstacles+17)->dpoints[0].y+(obstacles+17)->r.height};
	dXPoint E={(obstacles+17)->dpoints[0].x+(obstacles+17)->r.width,(obstacles+17)->dpoints[0].y};
	dXPoint F={(obstacles+6)->dpoints[0].x+(obstacles+6)->r.width,(obstacles+6)->dpoints[0].y+(obstacles+6)->r.height};
	dXPoint G={(obstacles+5)->dpoints[0].x,(obstacles+5)->dpoints[0].y+(obstacles+5)->r.height};
	dXPoint H={(obstacles+3)->dpoints[0].x+(obstacles+3)->r.width,(obstacles+3)->dpoints[0].y};
	dXPoint I={WIDTH,(obstacles+4)->dpoints[0].y};
	droites[0]=creerunedroite((obstacles)->dpoints[0],(obstacles)->dpoints[2],Basgauche);
	droites[1]=creerunedroite((obstacles+1)->dpoints[1],(obstacles)->dpoints[1],Bas);
	droites[2]=creerunedroite((obstacles+1)->dpoints[2],(obstacles+1)->dpoints[0],Basdroite);
	droites[3]=creerunedroite((obstacles+4)->dpoints[0],A,Haut);
	droites[4]=creerunedroite((obstacles+19)->dpoints[0],(obstacles+20)->dpoints[1],Gauche);
	droites[5]=creerunedroite((obstacles+20)->dpoints[1],(obstacles+20)->dpoints[0],Basgauche);
	droites[6]=creerunedroite((obstacles+20)->dpoints[0],(obstacles+15)->dpoints[1],Basgauche);
	droites[7]=creerunedroite((obstacles+20)->dpoints[3],(obstacles+15)->dpoints[1],Hautdroite);
	droites[8]=creerunedroite((obstacles+16)->dpoints[1],(obstacles+16)->dpoints[0],Hautgauche);
	droites[9]=creerunedroite((obstacles+16)->dpoints[1],(obstacles+18)->dpoints[0],Basdroite);
	droites[10]=creerunedroite((obstacles+20)->dpoints[2],(obstacles+20)->dpoints[3],Hautdroite);
	droites[11]=creerunedroite(C,B,DROITE);
	droites[12]=creerunedroite((obstacles+19)->dpoints[0],C,Haut);
	droites[13]=creerunedroite((obstacles+9)->dpoints[0],(obstacles+9)->dpoints[1],Gauche);
	droites[14]=creerunedroite((obstacles+9)->dpoints[0],(obstacles+9)->dpoints[2],Hautdroite);
	droites[15]=creerunedroite((obstacles+9)->dpoints[1],(obstacles+9)->dpoints[2],Basgauche);
	droites[16]=creerunedroite((obstacles+10)->dpoints[0],(obstacles+10)->dpoints[2],Hautgauche);
	droites[17]=creerunedroite((obstacles+10)->dpoints[0],(obstacles+10)->dpoints[1],Basdroite);
	droites[18]=creerunedroite((obstacles+10)->dpoints[2],(obstacles+10)->dpoints[1],DROITE);
	droites[19]=creerunedroite((obstacles+18)->dpoints[3],(obstacles+18)->dpoints[2],Hautgauche);
	droites[20]=creerunedroite((obstacles+17)->dpoints[0],D,Gauche);
	droites[21]=creerunedroite((obstacles+17)->dpoints[0],E,Haut);
	droites[22]=creerunedroite(E,(obstacles+18)->dpoints[1],DROITE);
	droites[23]=creerunedroite((obstacles+18)->dpoints[0],(obstacles+18)->dpoints[1],Basdroite);
	droites[24]=creerunedroite((obstacles+8)->dpoints[2],(obstacles+8)->dpoints[1],Hautdroite);
	droites[25]=creerunedroite((obstacles+8)->dpoints[1],F,DROITE);
	droites[26]=creerunedroite(F,G,Haut);
	droites[27]=creerunedroite((obstacles+5)->dpoints[0],G,Gauche);
	droites[28]=creerunedroite((obstacles+5)->dpoints[0],(obstacles+7)->dpoints[2],Hautgauche);
	droites[29]=creerunedroite((obstacles+4)->dpoints[0],(obstacles+7)->dpoints[1],Gauche);
	droites[30]=creerunedroite(A,(obstacles+3)->dpoints[0],DROITE);
	droites[31]=creerunedroite((obstacles+3)->dpoints[0],H,Haut);
	droites[32]=creerunedroite(H,(obstacles)->dpoints[2],Gauche);
	droites[33]=creerunedroite((obstacles+1)->dpoints[2],(obstacles+8)->dpoints[2],DROITE);
	droites[34]=creerunedroite(A,I,Haut);
}

void collisionsurclapets(float difficultee){
	int k=6;
	double r1=sqrt(pow((bille->r.x+WIDTH/72)-(obstacles+15)->dpoints[2].x,2)+pow((bille->r.y+WIDTH/72)-(obstacles+15)->dpoints[2].y,2));
	double r2=sqrt(pow((bille->r.x+WIDTH/72)-(obstacles+16)->dpoints[2].x,2)+pow((bille->r.y+WIDTH/72)-(obstacles+16)->dpoints[2].y,2));
	double rmax=sqrt(pow((obstacles+15)->dpoints[1].x-(obstacles+15)->dpoints[2].x,2)+pow((obstacles+15)->dpoints[1].y-(obstacles+15)->dpoints[2].y,2))+WIDTH/72;
	for(;k<10;k++){
		if((bille->vitesse.x==billetampon->vitesse.x)&&(bille->vitesse.y==billetampon->vitesse.y)){
			if(collisiondroitecerclepente(k)){
				if(signbit(droites[k].a*droites[k].b)){
					droites[6].type=Basgauche;
					droites[7].type=Hautdroite;
					droites[8].type=Hautgauche;
					droites[9].type=Basdroite;
					if(numerocollision==6&&u!=0) numerocollision=7;
					vecteurvitessesortant(k,difficultee);
					if(numerocollision==7&&u!=0){
						bille->vitesse.x+=(r1/rmax)*bille->vitesse.x;
						bille->vitesse.y+=(r1/rmax)*bille->vitesse.y;
						mouvementbilleclapetgauche();
					} 
				}else{
					droites[6].type=Basdroite;
					droites[7].type=Hautgauche;
					droites[8].type=Hautdroite;
					droites[9].type=Basgauche;
					if(numerocollision==9&&v!=0) numerocollision=8;
					vecteurvitessesortant(k,difficultee);
					if(numerocollision==8&&v!=0){
						bille->vitesse.x+=(r2/rmax)*bille->vitesse.x;
						bille->vitesse.y+=(r2/rmax)*bille->vitesse.y;
						mouvementbilleclapetdroite();
					}
				}					
			}
		}
	}
}

void collisionhorizontale(float difficultee){
	if(collisiondroitecerclehori(1)||collisiondroitecerclehori(3)||collisiondroitecerclehori(12)||collisiondroitecerclehori(21)||collisiondroitecerclehori(26)||collisiondroitecerclehori(31)){
		switch((droites+numerocollision)->type){
			case Haut:
				bille[0]=billetampon[0];
				bille->vitesse.y=-(bille->vitesse.y)-2*depcolli*difficultee;
				break;
			case Bas:
				bille[0]=billetampon[0];
				bille->vitesse.y=-(bille->vitesse.y)+2*depcolli*difficultee;
				break;
		}
	}	
}

void collisionverticale(float difficultee){
	if(collisiondroitecercleverti(4)||collisiondroitecercleverti(11)||collisiondroitecercleverti(13)||collisiondroitecercleverti(18)||collisiondroitecercleverti(20)||collisiondroitecercleverti(22)||collisiondroitecercleverti(25)||collisiondroitecercleverti(27)||collisiondroitecercleverti(29)||collisiondroitecercleverti(30)||collisiondroitecercleverti(32)||collisiondroitecercleverti(33)){
		switch((droites+numerocollision)->type){
			case Gauche:
				bille[0]=billetampon[0];
				bille->vitesse.x=-(bille->vitesse.x)-2*depcolli*difficultee;
				break;
			case DROITE:
				bille[0]=billetampon[0];
				bille->vitesse.x=-(bille->vitesse.x)+2*depcolli*difficultee;
				break;
		}	
	}
}

void collisiondisques(void){
	int k;
	dXPoint tmpA;
	int tmpon;
	for(k=11;k<47;k++){
		if(k==15)k+=6;
		if(k==31)k+=2;
		if (collisiondedeuxcercle(k)){
			tmpA.x=bille->r.x+bille->dimensions[0];
			tmpA.y=bille->r.y+bille->dimensions[0];
			droites[35]=creerunedroite((obstacles+k)->dpoints[0],tmpA,0);
			tmpon=(droites+35)->a;
			(droites+35)->a=-(droites+35)->b;
			(droites+35)->b=tmpon;
			vecteurvitessesortantdisque(35);
		}
	}    
}

void gererlagravite(float difficultee){
	if(fabs((bille->vitesse.y))<=0.01){
		bille->vitesse.y=-(billetampon->vitesse.y);
		bille->vitesse.y+=0.02*difficultee;
	}	
	if((bille->r.y)<(billetampon->r.y)||(bille->r.y)>(billetampon->r.y)){
		bille->vitesse.y+=0.02*difficultee;
	}
}

void jouerauflipper(float difficultee,dXPoint vecteur){
	nettoyer();
	sortie=0;
	creerobstacles();
	creerlesdroites();
	afficherclapets(obstacles);
	afficherflipper();
	XFlush(display);
	dXPoint p={24.25*WIDTH/27,14.*HEIGHT/16};
	bool succes=1;
	if(succes==1){
		Rectangle rbille={p.x-WIDTH/72,p.y-WIDTH/72,WIDTH/36,HEIGHT/36};
		bille[0]=creerbille(rbille,0xAABBCC,0xAABBCC);
		int m;
		for(m=0;m<4*HEIGHT/16.;m=m+4){
			nettoyer();
			Rectangle rdepart={23.85*WIDTH/27,14.*HEIGHT/16-m,WIDTH/36,HEIGHT/16+m};
			XSetForeground(display,graphicContext,0x000000);
			XFillRectangle(DX11,rdepart.x,rdepart.y,rdepart.width,rdepart.height);
			afficherclapets(obstacles);
			afficherflipper();
			afficherbille(bille);
			usleep(10000);	
			translationbille();
		}
		vitessealeatoire(difficultee);
		if(vecteur.x!=0||vecteur.y!=0){
			double normevitesse=sqrt(pow(vecteur.x,2)+pow(vecteur.y,2));
			bille->vitesse.x=bille->vitesse.x*vecteur.x/normevitesse*difficultee;
			bille->vitesse.y=bille->vitesse.y*vecteur.y/normevitesse*difficultee;
		}else{
			bille->vitesse.x=bille->vitesse.x*difficultee;
			bille->vitesse.y=bille->vitesse.y*difficultee;
		}
		billetampon[0]=bille[0];
		bille->distance=-1;
		tempsdepuisdebut=(double)time(NULL);
		event.xbutton.button=0;
		succes=mouvementbille(succes,0,difficultee);
	}
}

void animationboule(int k){
	XSetForeground(display,graphicContext,0x000000);
	XFillArc(DX11,(obstacles+k)->r.x,(obstacles+k)->r.y,(obstacles+k)->r.width,(obstacles+k)->r.height,0,360*64);
	XFlush(display);
	printf("\a");		
	usleep(10000);
}

void animationimpactcercle(void){
	if(numerocollisiondisque==11){
		animationboule(11);
	}
	if(numerocollisiondisque==12){
		animationboule(12);
	}
	if(numerocollisiondisque==13){
		animationboule(13);
	}
	if(numerocollisiondisque==14){
		animationboule(14);
	}
}

void animationtriangle(void){
	if(numerocollision==14||numerocollisiondisque==37||numerocollisiondisque==39){
		XSetForeground(display,graphicContext,0x000000);
		XFillPolygon(DX11,dXPtoXP((obstacles+9)->dpoints,(obstacles+9)->nbpoints),(obstacles+9)->nbpoints,Convex,CoordModeOrigin);
		XFlush(display);
		printf("\a"); 
		usleep(10000);
	}
        if(numerocollision==16||numerocollisiondisque==40||numerocollisiondisque==42){
        	XSetForeground(display,graphicContext,0x000000);
        	XFillPolygon(DX11,dXPtoXP((obstacles+10)->dpoints,(obstacles+10)->nbpoints),(obstacles+10)->nbpoints,Convex,CoordModeOrigin);		
		XFlush(display);
		printf("\a");
		usleep(10000);
	}
}
 
void mouvementclapetgauche(void){
	dXPoint gauche={5.*WIDTH/27,15*HEIGHT/18.};
	(obstacles+15)->dpoints[0]=rotationp((obstacles+15)->dpoints[0],gauche,-radian(u));
	(obstacles+15)->dpoints[1]=rotationp((obstacles+15)->dpoints[1],gauche,-radian(u));
}

void mouvementclapetdroite(void){
	dXPoint droite={12.5*WIDTH/27,15*HEIGHT/18.};
	(obstacles+16)->dpoints[0]=rotationp((obstacles+16)->dpoints[0],droite,radian(v));
	(obstacles+16)->dpoints[1]=rotationp((obstacles+16)->dpoints[1],droite,radian(v));
}
void mouvementbilleclapetgauche(void){
	dXPoint gauche={5.*WIDTH/27,15*HEIGHT/18.};
	dXPoint dxpbille={bille->r.x,bille->r.y};
	dxpbille=rotationp(dxpbille,gauche,-radian(5));
	bille->r.x=dxpbille.x;
	bille->r.y=dxpbille.y;
}

void mouvementbilleclapetdroite(void){
	dXPoint droite={12.5*WIDTH/27,15*HEIGHT/18.};
	dXPoint dxpbille={bille->r.x,bille->r.y};
	dxpbille=rotationp(dxpbille,droite,radian(5));
	bille->r.x=dxpbille.x;
	bille->r.y=dxpbille.y;
}

void fermercouloir(int affichage){
	if(affichage==0){
		if(1!=((bille->r.x+WIDTH/36>=(obstacles+47)->r.x)&&(bille->r.y+WIDTH/36>=(obstacles+47)->r.y))){
			XSetForeground(display,graphicContext,(obstacles+47)->couleurint);
			XFillRectangle(DX11,(obstacles+47)->r.x,(obstacles+47)->r.y,(obstacles+47)->r.width,(obstacles+47)->r.height);
			XFlush(display);
		}
	}
	if(sortie&&collisiondroitecerclehori(34)){
		bille->vitesse.y=-bille->vitesse.y;
	}
}

void debogageflipper(float difficultee, int affichage){
	if(sqrt(pow(bille->vitesse.x,2)+pow(bille->vitesse.y,2))-sqrt(pow(billetampon->vitesse.x,2)+pow(billetampon->vitesse.y,2))>5){
		double debug=sqrt(pow(billetampon->vitesse.x,2)+pow(billetampon->vitesse.y,2))/sqrt(pow(bille->vitesse.x,2)+pow(bille->vitesse.y,2));
		bille->vitesse.x=(bille->vitesse.x)*debug;
		bille->vitesse.y=(bille->vitesse.y)*debug;
	}
	if(isnan(sqrt(pow(bille->vitesse.x,2)+pow(bille->vitesse.y,2)))){
		bille[0]=billetampon[0];
	}
	if(affichage==2&&(bille->r.x==(billetampon+1)->r.x)&&((billetampon+1)->r.y==billetampon->r.y)&&(numerocollision==10||numerocollision==19)){
		bille->r.y-=WIDTH/72;
	}
	if(numerocollisiondisque==28) bille->r.x-=WIDTH/36;
	if(numerocollisiondisque==29) bille->r.x+=WIDTH/36;
	if(bille->r.x>WIDTH||bille->r.y>HEIGHT||bille->r.x<0||bille->r.y<0){
		dXPoint p={24.25*WIDTH/27,4.*HEIGHT/16};
		Rectangle rbille={p.x-WIDTH/72,p.y-WIDTH/72,WIDTH/36,HEIGHT/36};
		bille[0]=creerbille(rbille,0xAABBCC,0xAABBCC);
		vitessealeatoire(difficultee);
	}
}

void chocreel(void){
	if(numerocollision==0||numerocollision==3||numerocollision==30||numerocollision==31||numerocollision==32||numerocollision==34||(numerocollision==-1&&numerocollisiondisque==-1)){
	}else{
		if(numerocollision==14||numerocollision==16||numerocollisiondisque==11||numerocollisiondisque==12||numerocollisiondisque==13||numerocollisiondisque==14){
			bille->vitesse.x*=12./10;
			bille->vitesse.y*=12./10;
		}else{
			if(((numerocollision==7)&&u==0)||((numerocollision==8)&&v==0)){
				bille->vitesse.x*=6./10;
				bille->vitesse.y*=6./10;
			}
			if(numerocollision!=7&&numerocollision!=8){
				bille->vitesse.x*=8./10;
				bille->vitesse.y*=8./10;
			}
		}
	}		
}

void vitessealeatoire(float difficultee){
	while(bille->vitesse.x>=4||bille->vitesse.y>=4||bille->vitesse.x<=-4||bille->vitesse.y<=-4){
		srand(time(NULL));
		int x=(rand()%(801))-400;
		while(x>400){
			x=(rand()%(801))-400;
		}
		bille->vitesse.x=x/100.;
		bille->vitesse.y=-sqrt(16-pow(bille->vitesse.x,2));
	}
	bille->vitesse.x*=difficultee;
	bille->vitesse.y*=difficultee;
}

void augmenterscore(void){
	if(numerocollision==14||numerocollision==16||numerocollisiondisque==37||numerocollisiondisque==39||numerocollisiondisque==40||numerocollisiondisque==42){
		score=score+1;
	}
	if(numerocollisiondisque==11||numerocollisiondisque==12){
		score=score+2;
	}
	if(numerocollisiondisque==13||numerocollisiondisque==14){
		score=score+3;
	}
	if(numerocollision==26){
		score=score+10;
	}
}
