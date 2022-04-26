#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include<stdbool.h> 
#include <math.h>
#include <GL/gl.h>
#include "GL/glut.h"
#include "matrizes.h"

#define PHI 3.141572
#define MAXVERTEXS 30

struct polygon
{
	float v[3];
} pvertex[MAXVERTEXS];



GLenum doubleBuffer;


int tipo_operacao = 0;      // tipo de operacao: O: gera poligono; 1: transalacao; 2:...
int largura_janela, altura_janela;
int tipoPoligono;  // poligo por vertices ou por arestas
int numero_vertices = 0; //mudar
int gIndVert = -1;
bool MOUSE_SELECIONADO = false;
float angulo_rotacao =0.0f;    // angulo para rotacao
float gCen[3];       // centroido do poligono
float gAng =0.0f;    // angulo para rotacao 


static void Reshape(int width, int height)
{
    largura_janela = width / 2;
    altura_janela = height / 2;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-largura_janela, largura_janela, -altura_janela, altura_janela);

    glMatrixMode(GL_MODELVIEW);
}


int clipVertex(int x, int y)
{
	int i;
	float d;
	gIndVert=-1;
	for (i=0; i<numero_vertices; i++) {
		d = sqrt(pow((pvertex[i].v[0]-x), 2.0) + pow((pvertex[i].v[1]-y), 2.0));
		if(d < 3.0){
			gIndVert = i;
			break;
		}
	}
	return gIndVert;
}

void coord_line(void)
{
    glLineWidth(1);

    glColor3f(1.0, 0.0, 0.0);

    // vertical line

    glBegin(GL_LINE_STRIP);
    glVertex2f(-largura_janela, 0);
    glVertex2f(largura_janela, 0);
    glEnd();

    glColor3f(0.0, 1.0, 0.0);

    // horizontal line

    glBegin(GL_LINE_STRIP);
    glVertex2f(0, -altura_janela);
    glVertex2f(0, altura_janela);
    glEnd();
}

//Independente
void PolygonDraw(void)
{
    int i;

    glColor3f(0.0, 0.0, 0.0);

    glPolygonMode(GL_FRONT_AND_BACK, tipoPoligono);

    glBegin(tipoPoligono);
    for (i = 0; i < numero_vertices; i++)
    {
        glVertex2fv(pvertex[i].v);
    }
    glEnd();
}


static void Draw(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    coord_line();
    

    PolygonDraw();

	if(gIndVert>-1) {
		glColor3f(1.0, 0.0, 0.0);
		glPointSize(3);
		glBegin(GL_POINTS); 
			glVertex2fv(pvertex[gIndVert].v);
		glEnd();
	}
    if (doubleBuffer)
    {
        glutSwapBuffers();
    }
    else
    {
        glFlush();
    }
}

void procegVertMenuEvents(int option) 
{
	switch (option) 
	{
		case 1 : 
			if (tipoPoligono == GL_LINE)
				tipoPoligono = GL_FILL;
			else 
				tipoPoligono = GL_LINE;
			break;
	}
	glutPostRedisplay();
}

void circulo(float r, float ang, float pp[3])
{
    pp[0] = (float)(r * cos(ang));
    pp[1] = (float)(r * sin(ang));
    pp[2] = (float)0.0;
}


void translate(float dx, float dy)
{
	int i;
	
    matrizIdentidade();	
    gMatriz[0][2] = dx;
    gMatriz[1][2] = dy;
    
    
    	// opera transformação de cada vetor vértice
	for (i=0; i<numero_vertices; i++) 
		operaTransforma(pvertex[i].v);
}

void calCentro(float vetAUX[])
{
     int i;
    // computando o centroide
     vetAUX[0] = vetAUX[1] = 0.0f;    
     for (i=0; i<numero_vertices; i++) {
		vetAUX[0] += pvertex[i].v[0];
		vetAUX[1] += pvertex[i].v[1];
		vetAUX[2] += pvertex[i].v[2];		
	 }
     vetAUX[0] /= numero_vertices;     
     vetAUX[1] /= numero_vertices; 
     vetAUX[2] /= numero_vertices; 
	     
}

void scale(float dx, float dy)
{
	
     int i;
     float sx, sy, xy[3]; 
     
	calCentro(xy);    
	translate(-1*xy[0], -1*xy[1]);
          
     sx = sy = 1.0f;
     if(fabs(pvertex[gIndVert].v[0]) > 0.01f)
        sx = 1.0f + dx / pvertex[gIndVert].v[0];
     if(fabs(pvertex[gIndVert].v[1]) > 0.01f)
        sy = 1.0f + dy / pvertex[gIndVert].v[1];     
     for (i=0; i<numero_vertices; i++) {
		    pvertex[i].v[0] *= sx;		
		    pvertex[i].v[1] *= sy;
	 }
    matrizIdentidade(); 
	gMatriz[0][0] = sx; 
 	gMatriz[1][1] = sy;
 	 	 
     translate(xy[0],xy[1]);              
}

void rotate(float dx, float dy)
{
     int i; 
     float oo, angulo_teta, xy[3]; 
     
     calCentro(xy);                    // calculo vetor vc ao centro geométric do polígono
     translate(-1*xy[0], -1*xy[1]);    // translada o polígo ao origem em -vc
     
     // determinando o angulo: 
     
	    // produto vetorial --> (v[0], v[1]) x (dx, dy)  
     oo = pvertex[gIndVert].v[1] * dx - pvertex[gIndVert].v[0] * dy;
     
     	// oo é esacalar positivo (horaria) ou negativo (anti-horaria)

     angulo_teta = gAng;                // angulo constante definido no init
     if(oo>0.0f)
        angulo_teta = -1.0f * gAng; 		 
		
		// Define a matriz de Rotacao	 
 	 
 	 matrizIdentidade();  
 	 gMatriz[0][0] = cos(angulo_teta);    gMatriz[0][1] = -sin(angulo_teta);
 	 gMatriz[1][0] = sin(angulo_teta);    gMatriz[1][1] = cos(angulo_teta);
 	 
    	// opera transformação Rotacao de cada vetor vértice
	 for (i=0; i<numero_vertices; i++) {
	 	 operaTransforma(pvertex[i].v);
	 }
	
 	 
     translate(xy[0], xy[1]);     // o poligo é tranladado para sua posicao original
}

void shear(float dx, float dy)
{
     int i;
     float sx, sy, xy[3];
      
	
	 sx = 0.00001 * dx;
	 sy = 0.00001 * dy;
	 calCentro(xy);
	 translate(-1*xy[0], -1*xy[1]); 
     //sy = 0.001f*dy;
     if(dx>dy)
     {
         if(fabs(pvertex[gIndVert].v[0])>0.1f)
            sx =  dx / pvertex[gIndVert].v[1];
     }
     else
     {
         if(fabs(pvertex[gIndVert].v[1])>0.1f)
            sy =  dy / pvertex[gIndVert].v[0]; 
     }
     matrizIdentidade(); 
     //sx = 0.001f*dx;
     gMatriz[0][1] = sx;
     gMatriz[1][0] = sy;	
       

      // rota em teta para lado oo         
     for (i=0; i<numero_vertices; i++) {
		operaTransforma(pvertex[i].v);
			
	 } 
	 
	 translate(xy[0], xy[1]);   
}

void reflect(float dx, float dy){
      int i;
	  float oo, teta, vc[3]; 

     calCentro(vc);                    // calculo vetor vc ao centro geométric do polígono
     translate(-1*vc[0], -1*vc[1]);    // translada o polígo ao origem em -vc

     oo = pvertex[gIndVert].v[1] * dx - pvertex[gIndVert].v[0] * dy;
	

     teta = gAng;                // angulo constante definido no init
     if(oo>0.0f)
        teta = -1.0f * gAng; 		 


	 if(dx>0 && dy>0){
	 	printf("1\n");
	 	matrizIdentidade();  
 	 			gMatriz[0][0] = 1;    gMatriz[0][1] = 0;
 	 			gMatriz[1][0] = 0;    gMatriz[1][1] = -1;
     			
	 }
	 if(dx<0 && dy>0){
	 	printf("2\n");
	 	matrizIdentidade();  
 	 			gMatriz[0][0] = -1;    gMatriz[0][1] = 0;
 	 			gMatriz[1][0] = 0;    gMatriz[1][1] = 1;

	 }
	 if(dx>0 && dy<0){
	 	printf("3");
	 	matrizIdentidade();  
 	 			gMatriz[0][0] = 0;    gMatriz[0][1] = 1;
 	 			gMatriz[1][0] = 1;    gMatriz[1][1] = 0;
 	
	}
	
	 if(dx<0 && dy<0){
	 	printf("4");
	 	matrizIdentidade();  
 	 			gMatriz[0][0] = -1;    gMatriz[0][1] = 0;
 	 			gMatriz[1][0] = 0;    gMatriz[1][1] = -1;
	}
 	 
	 for (i=0; i<numero_vertices; i++){
	 		operaTransforma (pvertex[i].v);
	 }
	 	translate(vc[0], vc[1]); 
	 }
	


void motion(int x, int y)
{
	float dx, dy;
	if(gIndVert>-1) {	
		x=x-largura_janela; y=altura_janela-y;
		dx = x - pvertex[gIndVert].v[0];
		dy = y - pvertex[gIndVert].v[1];
	    switch (tipo_operacao)
	    {
               case 1:	
			   translate(dx, dy);
			   break;     
               
			   case 2: 
			   rotate(dx, dy); 
			   break;   
               
			   case 3: 
			   scale(dx, dy); 
			   break;   
               
			   case 4: 
			   shear(dx, dy); 
			   break; 
			   case 5: 
			   reflect(dx, dy); 
			   break;    
        }
		Draw();
	}
}


