#include "outils.h"
#define WIDTH 600
#define HEIGHT 600

int minimum(int a, int b){
	if (a<=b)return a;
	return b;
}

int maximum(int a,int b){
	if(a>=b) return a;
	return b;
}

int xmini(dXPoint *tab,int nbpoint){ 
	int k;
	int u=tab[0].x;
	for (k=0;k<nbpoint;k++){
	u=minimum(u,tab[k].x);}
	return u;
}

int ymini(dXPoint *tab,int nbpoint){ 
	int k;
	int v=tab[0].y;
	for (k=0;k<nbpoint;k++){
	v=minimum(v,tab[k].y);}
	return v;
}

double radian(double z){ 
	double z1;
	z1=(z*3.14159)/(180);
	return z1;
}

double distance(dXPoint a,dXPoint b){  
	double k=sqrt(pow((b.x-a.x),2)+pow((b.y-a.y),2));
	return k;
}

dXPoint rotationp(dXPoint A, dXPoint B, double z){
	dXPoint M;
	M.x= (A.x-B.x)*cos(z)-(A.y-B.y)*sin(z)+B.x;
	M.y= (A.x-B.x)*sin(z)+(A.y-B.y)*cos(z)+B.y;	
	return M;
}

void nettoyer(void){ 
	XClearArea(display,window,0,0,WIDTH,HEIGHT,0);
	XFlush(display);
}

