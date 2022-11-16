/*
 * File: SierpinskiTriangle.cpp
 * ----------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter code for the Sierpinski Triangle problem
 * fron Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "graphics.h"
using namespace std;


void drawTriangle(double x ,double y , double r );
void sierpinskiTriangle(double x , double y , double edge, int order);


int main() {
   initGraphics();
   int edge=300;
   int order=3;
   
	sierpinskiTriangle(getWindowWidth()/2-edge/2 ,getWindowHeight()/2+((edge*1.732050807568877)/4) , edge , order);


   return 0;
}

/*
 * Function: sierpinskiTriangle
 * Usage: sierpinskiTriangle(x,y,edge,order);
 * ----------------------
 * draws a sierpinskiTriangle of edge length edge, at x,y point ad its lower left corner of oerder oeder. 
 */
void sierpinskiTriangle(double x , double y , double edge, int order){
	if(order==-1)
		return;
	
	drawTriangle(x,y,edge);

	sierpinskiTriangle(x,y,edge/2,order-1);
	sierpinskiTriangle(x+edge/2,y,edge/2,order-1);
	sierpinskiTriangle(x+edge/4,y-((edge*1.732050807568877)/4),edge/2,order-1);
}


/*
 * Function: drawTriangle
 * Usage: drawTriangle(x,y,edge);
 * ----------------------
 * draws a tringle of edge length edge, at x,y point ad its lower left corner. 
 */
void drawTriangle(double x ,double y , double r ){
	
	drawPolarLine(x , y , r ,  60);
	drawPolarLine(x ,y , r ,  0);
	drawPolarLine(x+r , y , r ,  120);
	
}