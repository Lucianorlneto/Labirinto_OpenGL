#include <iostream>
#include <vector>
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include "png_texture.h"
#include <pthread.h> 
#include <unistd.h>
#include <string.h>

using namespace std;

#define TEXTURA_DO_CHAO "montanhas.png"
#define TEXTURA_DA_PAREDE "parede.png"
#define TEXTURA_DO_CEU "ceu.png"
#define TEXTURA_DO_WIN "Portal.png"

// vector<float> coordenadas;
// vector<vector<float> > paredes;
GLubyte space[] =
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
GLubyte letters[][13] = {
    {0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xc3, 0xc3, 0xc3, 0x66, 0x3c, 0x18},
    {0x00, 0x00, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe},
    {0x00, 0x00, 0x7e, 0xe7, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xe7, 0x7e},
    {0x00, 0x00, 0xfc, 0xce, 0xc7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc7, 0xce, 0xfc},
    {0x00, 0x00, 0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xfc, 0xc0, 0xc0, 0xc0, 0xc0, 0xff},
    {0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xfc, 0xc0, 0xc0, 0xc0, 0xff},
    {0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xcf, 0xc0, 0xc0, 0xc0, 0xc0, 0xe7, 0x7e},
    {0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3},
    {0x00, 0x00, 0x7e, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x7e},
    {0x00, 0x00, 0x7c, 0xee, 0xc6, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06},
    {0x00, 0x00, 0xc3, 0xc6, 0xcc, 0xd8, 0xf0, 0xe0, 0xf0, 0xd8, 0xcc, 0xc6, 0xc3},
    {0x00, 0x00, 0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0},
    {0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xdb, 0xff, 0xff, 0xe7, 0xc3},
    {0x00, 0x00, 0xc7, 0xc7, 0xcf, 0xcf, 0xdf, 0xdb, 0xfb, 0xf3, 0xf3, 0xe3, 0xe3},
    {0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xe7, 0x7e},
    {0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe},
    {0x00, 0x00, 0x3f, 0x6e, 0xdf, 0xdb, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x66, 0x3c},
    {0x00, 0x00, 0xc3, 0xc6, 0xcc, 0xd8, 0xf0, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe},
    {0x00, 0x00, 0x7e, 0xe7, 0x03, 0x03, 0x07, 0x7e, 0xe0, 0xc0, 0xc0, 0xe7, 0x7e},
    {0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xff},
    {0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3},
    {0x00, 0x00, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3},
    {0x00, 0x00, 0xc3, 0xe7, 0xff, 0xff, 0xdb, 0xdb, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3},
    {0x00, 0x00, 0xc3, 0x66, 0x66, 0x3c, 0x3c, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3},
    {0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3},
    {0x00, 0x00, 0xff, 0xc0, 0xc0, 0x60, 0x30, 0x7e, 0x0c, 0x06, 0x03, 0x03, 0xff}
};

GLuint fontOffset;


float ztemp, xtemp;
int flag_parede = 0;
float **paredes;
int parede_count = 0;
float z1_parede, z2_parede, x1_parede, x2_parede;
float ang = 0.0;
float ang2 = 0.0;
float tmp_ang = 0.0;
float z_ = 6.0;
float z_temp = 0.0;
float x_ = -6.0;
float x_temp = 0.0;
float y_ = -0.5;
float y_temp = 0.0;
float zu_ = -2.5;
float zu_temp = 20.0;
float xu_ = 2.5;
float xu_temp = -20.0;
int m = 1;
int posx1_win, posz1_win, posx2_win, posz2_win;

int tamanhox = 10;
int tamanhoy = 10;

int tempo = 0;
int tempo1, tempo2, tempo3;

float dz = 10.0;

int **matriz;

int fase = 1;

GLshort texturas=1;
GLuint  textura_chao;
GLuint  textura_parede;
GLuint  textura_ceu;
GLuint  textura_win;

void *thread_function(void *arg);
char message[] = "";

//Coordenadas para a textura
GLfloat ctp[4][2]={
  {-1.0,-1.0},
  {+1.0,-1.0},
  {+1.0,+1.0},
  {-1.0,+1.0}
};

GLfloat ctp2[4][2]={
  {+1.0,-0.0},
  {+0.0,-0.0},
  {+0.0,+1.0},
  {+1.0,+1.0}
};




void makeRasterFont(void)
{
   GLuint i, j;
   glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

   fontOffset = glGenLists (128);
   for (i = 0,j = 'A'; i < 26; i++,j++) {
      glNewList(fontOffset + j, GL_COMPILE);
      glBitmap(8, 13, 0.0, 2.0, 10.0, 0.0, letters[i]);
      glEndList();
   }
   glNewList(fontOffset + ' ' , GL_COMPILE);
   glBitmap(8, 13, 0.0, 2.0, 10.0, 0.0, space);
   glEndList();
}

void printString(char *s)
{
   glPushAttrib (GL_LIST_BIT);
   glListBase(fontOffset);
   glCallLists(strlen(s), GL_UNSIGNED_BYTE, (GLubyte *) s);
   glPopAttrib ();
}

//Carregar as texturas pelo png_texture.h
void carregar_texturas(void){
  textura_chao = png_texture_load(TEXTURA_DO_CHAO, NULL, NULL);
  textura_parede = png_texture_load(TEXTURA_DA_PAREDE, NULL, NULL);
  textura_ceu = png_texture_load(TEXTURA_DO_CEU, NULL, NULL);
  textura_win = png_texture_load(TEXTURA_DO_WIN, NULL, NULL);
}

void local(int x1, int x2, int z1, int z2){
	glBegin(GL_QUADS);

	//parede da frente
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(x1, 4.0, z1);
	glVertex3f(x2, 4.0, z1);
	glVertex3f(x2, 4.0, z2);
	glVertex3f(x1, 4.0, z2);

	glEnd();
}

void parede(int x1,int x2,int y1,int y2,int z1,int z2){
	if(m == 1){
		glBindTexture(GL_TEXTURE_2D,textura_parede);
		glBegin(GL_QUADS);

		//parede da frente
		// glColor3f(0.0, 1.0, 0.0);
		glTexCoord2fv(ctp[0]); glVertex3f(x1, y1, z2);
		glTexCoord2fv(ctp[1]); glVertex3f(x2, y1, z2);
		glTexCoord2fv(ctp[2]); glVertex3f(x2, y2, z2);
		glTexCoord2fv(ctp[3]); glVertex3f(x1, y2, z2);
		glEnd();

		glBegin(GL_QUADS);
		//parede da direita
		// glColor3f(1.0, 0.0, 0.0);
		glTexCoord2fv(ctp[1]); glVertex3f(x2, y1, z1);
		glTexCoord2fv(ctp[2]); glVertex3f(x2, y2, z1);
		glTexCoord2fv(ctp[3]); glVertex3f(x2, y2, z2);
		glTexCoord2fv(ctp[0]); glVertex3f(x2, y1, z2);
		glEnd();

		glBegin(GL_QUADS);
		//parede de trás
		// glColor3f(0.0, 0.0, 1.0);
		glTexCoord2fv(ctp[0]); glVertex3f(x1, y1, z1);
		glTexCoord2fv(ctp[1]); glVertex3f(x2, y1, z1);
		glTexCoord2fv(ctp[2]); glVertex3f(x2, y2, z1);
		glTexCoord2fv(ctp[3]); glVertex3f(x1, y2, z1);
		glEnd();

		glBegin(GL_QUADS);
		//parede da esquerda
		// glColor3f(1.0, 1.0, 1.0);
		glTexCoord2fv(ctp[1]); glVertex3f(x1, y1, z1);
		glTexCoord2fv(ctp[2]); glVertex3f(x1, y2, z1);
		glTexCoord2fv(ctp[3]); glVertex3f(x1, y2, z2);
		glTexCoord2fv(ctp[0]); glVertex3f(x1, y1, z2);
		glEnd();


		glBegin(GL_QUADS);
		// // chao
		// // glColor3f(0.5, 0.5, 0.5);
		// // glVertex3f(x1, y1, z1);
		// // glVertex3f(x2, y1, z1);
		// // glVertex3f(x2, y1, z2);
		// // glVertex3f(x1, y1, z2);

		// //teto
		// glColor3f(0.5, 0.5, 0.5);
		glTexCoord2fv(ctp[0]); glVertex3f(x1, y2, z1);
		glTexCoord2fv(ctp[1]); glVertex3f(x2, y2, z1);
		glTexCoord2fv(ctp[2]); glVertex3f(x2, y2, z2);
		glTexCoord2fv(ctp[3]); glVertex3f(x1, y2, z2);

		glEnd();
	}else{
		glBegin(GL_QUADS);

		//parede da frente
		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(x1, y1, z2);
		glVertex3f(x2, y1, z2);
		glVertex3f(x2, y2, z2);
		glVertex3f(x1, y2, z2);

		glEnd();

		glBegin(GL_QUADS);

		//parede da direita
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(x2, y1, z1);
		glVertex3f(x2, y2, z1);
		glVertex3f(x2, y2, z2);
		glVertex3f(x2, y1, z2);

		glEnd();

		glBegin(GL_QUADS);

		//parede de trás
		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(x1, y1, z1);
		glVertex3f(x2, y1, z1);
		glVertex3f(x2, y2, z1);
		glVertex3f(x1, y2, z1);

		glEnd();

		glBegin(GL_QUADS);

		//parede da esquerda
		glColor3f(1.0, 1.0, 1.0);
		glVertex3f(x1, y1, z1);
		glVertex3f(x1, y2, z1);
		glVertex3f(x1, y2, z2);
		glVertex3f(x1, y1, z2);

		glEnd();

		glBegin(GL_QUADS);

		// chao
		// glColor3f(0.5, 0.5, 0.5);
		// glVertex3f(x1, y1, z1);
		// glVertex3f(x2, y1, z1);
		// glVertex3f(x2, y1, z2);
		// glVertex3f(x1, y1, z2);

		//teto
		glColor3f(0.5, 0.5, 0.5);
		glVertex3f(x1, y2, z1);
		glVertex3f(x2, y2, z1);
		glVertex3f(x2, y2, z2);
		glVertex3f(x1, y2, z2);

		glEnd();
	}

}

void chao(int x1, int x2, int y1, int z1, int z2){
	if(m == 1){
		glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);
		glBindTexture(GL_TEXTURE_2D,textura_chao);
		glBegin(GL_QUADS);

		//chao
		glColor3f(0.7, 1.0, 0.2);
		glTexCoord2fv(ctp[0]); glVertex3f(x1, y1, z1);
		glTexCoord2fv(ctp[1]); glVertex3f(x2, y1, z1);
		glTexCoord2fv(ctp[2]); glVertex3f(x2, y1, z2);
		glTexCoord2fv(ctp[3]); glVertex3f(x1, y1, z2);
		glEnd();

		glBindTexture(GL_TEXTURE_2D,textura_ceu);
		glBegin(GL_QUADS);

		//teto
		glColor3f(0.6, 0.7, 0.77);
		glTexCoord2fv(ctp[0]); glVertex3f(x1, y1 + 2.0, z1);
		glTexCoord2fv(ctp[1]); glVertex3f(x2, y1 + 2.0, z1);
		glTexCoord2fv(ctp[2]); glVertex3f(x2, y1 + 2.0, z2);
		glTexCoord2fv(ctp[3]); glVertex3f(x1, y1 + 2.0, z2);

		glEnd();
	}else{
		glBegin(GL_QUADS);

		//chao
		glColor3f(0.7, 1.0, 0.2);
		glVertex3f(x1, y1, z1);
		glVertex3f(x2, y1, z1);
		glVertex3f(x2, y1, z2);
		glVertex3f(x1, y1, z2);

		glEnd();

		glBegin(GL_QUADS);

		//teto
		glColor3f(0.6, 0.7, 0.77);
		glVertex3f(x1, y1 + 2.0, z1);
		glVertex3f(x2, y1 + 2.0, z1);
		glVertex3f(x2, y1 + 2.0, z2);
		glVertex3f(x1, y1 + 2.0, z2);

		glEnd();
	}
}

void win(int x1, int x2, int y1, int z1, int z2){
	if(m == 1){

		glBindTexture(GL_TEXTURE_2D,textura_win);
		glBegin(GL_QUADS);

		//chao
		glColor3f(0.0, 0.0, 0.0);
		glTexCoord2fv(ctp2[0]); glVertex3f(x1, y1, z1);
		glTexCoord2fv(ctp2[1]); glVertex3f(x2, y1, z1);
		glTexCoord2fv(ctp2[2]); glVertex3f(x2, y1, z2);
		glTexCoord2fv(ctp2[3]); glVertex3f(x1, y1, z2);

		glEnd();

		glBindTexture(GL_TEXTURE_2D,textura_ceu);
		glBegin(GL_QUADS);

		//teto
		glColor3f(0.6, 0.7, 0.77);
		glTexCoord2fv(ctp[0]); glVertex3f(x1, y1 + 2.0, z1);
		glTexCoord2fv(ctp[1]); glVertex3f(x2, y1 + 2.0, z1);
		glTexCoord2fv(ctp[2]); glVertex3f(x2, y1 + 2.0, z2);
		glTexCoord2fv(ctp[3]); glVertex3f(x1, y1 + 2.0, z2);

		glEnd();
	}else{
		glBegin(GL_QUADS);

		//chao
		glColor3f(0.1, 0.1, 0.1);
		glVertex3f(x1, y1, z1);
		glVertex3f(x2, y1, z1);
		glVertex3f(x2, y1, z2);
		glVertex3f(x1, y1, z2);

		glEnd();

		glBegin(GL_QUADS);

		//teto
		glColor3f(0.6, 0.7, 0.77);
		glVertex3f(x1, y1 + 2.0, z1);
		glVertex3f(x2, y1 + 2.0, z1);
		glVertex3f(x2, y1 + 2.0, z2);
		glVertex3f(x1, y1 + 2.0, z2);

		glEnd();
	}
}

void ReadMaze(){

	if(fase == 1){
		matriz = (int**)malloc(sizeof(int*) * tamanhoy);

		for (int i = 0; i < tamanhoy; ++i)
		{
			matriz[i] = (int*)malloc(sizeof(int) * tamanhox);
		}

		char c;
		FILE *file;
		file = fopen("labirinto.txt", "r");
		if(file == NULL) return;

		int i = 0;
		int j = 0;

		while((c = fgetc(file)) != EOF){
			if(c == '\n'){
				i++;
				j = 0;	
			}else{
				if(c == '0'){
					matriz[i][j] = 0;
				}else if( c == '1'){
					matriz[i][j] = 1;
					parede_count++;
					
				}else{
					matriz[i][j] = 2;
					posz1_win = 4*j;
					posx1_win = 4*i;
					posz2_win = 4*(j + 1);
					posx2_win = 4*(i + 1);

					}
				j++;
			} 
		}

		fclose(file);
	} else if(fase == 2){
		matriz = (int**)malloc(sizeof(int*) * tamanhoy);

		for (int i = 0; i < tamanhoy; ++i)
		{
			matriz[i] = (int*)malloc(sizeof(int) * tamanhox);
		}

		char c;
		FILE *file;
		file = fopen("labirinto2.txt", "r");
		if(file == NULL) return;

		int i = 0;
		int j = 0;

		while((c = fgetc(file)) != EOF){
			if(c == '\n'){
				i++;
				j = 0;	
			}else{
				if(c == '0'){
					matriz[i][j] = 0;
				}else if( c == '1'){
					matriz[i][j] = 1;
				}else{
					matriz[i][j] = 2;
					posz1_win = 4*j;
					posx1_win = 4*i;
					posz2_win = 4*(j + 1);
					posx2_win = 4*(i + 1);
				}
				j++;
			} 
		}

		fclose(file);
	
	} else if(fase == 3){
		matriz = (int**)malloc(sizeof(int*) * tamanhoy);

		for (int i = 0; i < tamanhoy; ++i)
		{
			matriz[i] = (int*)malloc(sizeof(int) * tamanhox);
		}

		char c;
		FILE *file;
		file = fopen("labirinto3.txt", "r");
		if(file == NULL) return;

		int i = 0;
		int j = 0;

		while((c = fgetc(file)) != EOF){
			if(c == '\n'){
				i++;
				j = 0;	
			}else{
				if(c == '0'){
					matriz[i][j] = 0;
				}else if( c == '1'){
					matriz[i][j] = 1;
				}else{
					matriz[i][j] = 2;
					posz1_win = 4*j;
					posx1_win = 4*i;
					posz2_win = 4*(j + 1);
					posx2_win = 4*(i + 1);
				}
				j++;
			} 
		}

		fclose(file);
	}else{
		
	}



}

void detect_parede(){
	paredes = (float**)malloc(sizeof(float*)*parede_count);
	for (int i = 0; i < parede_count; ++i)
		{
			paredes[i] = (float*)malloc(sizeof(float) * 4);
		}
	parede_count = 0;
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			if(matriz[i][j] == 1){
				z1_parede = 4*j;
				x1_parede = 4*i;
				z2_parede = 4*(j + 1);
				x2_parede = 4*(i + 1);
				paredes[parede_count][0] = z1_parede;
				paredes[parede_count][1] = x1_parede;
				paredes[parede_count][2] = z2_parede;
				paredes[parede_count][3] = x2_parede;
				parede_count++;
			}
		}
	}
}

void display(void)
{
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity ();
	glFrustum (-1.5, 1.5, -0.5, 0.5, 1.0, dz);
	if(fase < 4){
		glRotatef(ang,0.0,1.0,0.0);
		glRotatef(ang2,1.0,0.0,0.0);
	}
	
	if(m == 1){
		if(fase < 4){
			glTranslatef(x_,y_, z_);
		}
	}else{
		glTranslatef(xu_,y_, zu_);
	}

	if(texturas){
	    glEnable(GL_TEXTURE_2D);
	}
	else{
	    glDisable(GL_TEXTURE_2D);
	}

	if(fase < 4){
		for (int i = 0; i < tamanhoy; i++)
		{
			for (int j = 0; j < tamanhox; j++)
			{
				if(matriz[i][j] == 1){
					parede(4*i, 4*(i + 1), 0.0, 2, -4*j, -4*(j + 1));
				}else if(matriz[i][j] == 0){
					chao(4*i, 4*(i + 1), 0.0, -4*j, -4*(j + 1));
				}else{
					win(4*i, 4*(i + 1), 0.0, -4*j, -4*(j + 1));
				}
			}
		}
	}else{
		glDisable(GL_DEPTH_TEST);
		printf("tempo 1 = %u, tempo 2 = %u, tempo 3 = %u\n", tempo1, tempo2, tempo3);
		GLfloat white[3] = { 1.0, 1.0, 1.0 };

	   glClear(GL_COLOR_BUFFER_BIT);
	   glColor3fv(white);

	   glRasterPos2i(-4, -2.5);
	   printString("THE QUICK BROWN FOX JUMPS");
	   glRasterPos2i(-4, -2.5);
	   printString("OVER A LAZY DOG");
	   //printf("x = %f, y = %f, z = %f\n", x_, y_, z_);
	   glFlush ();
	}

	if(m == 0){

		local(-x_temp+0.5, -x_temp-0.5, -z_temp+0.5, -z_temp-0.5);
	}

	if(z_ <= posz2_win && z_ >= posz1_win && x_ <= -posx1_win && x_ >= -posx2_win){
		//printf("posz1_win = %u, posz2_win = %u, posx1_win = %u, posx2_win = %u\n", posz1_win, posz2_win, posx1_win, posx2_win);
		//printf("ganhou, mizeravi\n");
		fase++;
		ang = 0.0;
		ang2 = 0.0;
		tmp_ang = 0.0;
		z_ = 6.0;
		z_temp = 0.0;
		x_ = -6.0;
		x_temp = 0.0;
		y_ = -0.5;
		y_temp = 0.0;
		zu_ = -2.5;
		zu_temp = 20.0;
		xu_ = 2.5;
		xu_temp = -20.0;
		int m = 1;
		if(fase == 2){
			tempo1 = tempo;
		}else if(fase == 3){
			tempo2 = tempo;
		}else{
			tempo3 = tempo;
		}
		tempo = 0;
		ReadMaze();
		detect_parede();
		//glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	glutSwapBuffers();
}

void init()
{
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	carregar_texturas();
  	glEnable(GL_TEXTURE_2D);
  	makeRasterFont();
}

void Reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
		case 'a':
			if( m == 1){
			ang -= 15.0;
			if(ang > 360.0) ang -= 360.0;
			if(ang < 0) ang += 360.0;
			//printf("ang = %f, ang2 = %f\n", ang, ang2);
			}
			else{
				// xu_ += 1.0;
				//printf("x_ = %f, f3 = %f, f = %f\n", x_, y_, z_);
			}
			glutPostRedisplay();
			break;
		case 'd':
			if(m == 1){
			ang += 15.0;
			if(ang < 0.0) ang += 360.0;
			if(ang > 360.0) ang -= 360.0;
			//printf("ang = %f, ang2 = %f\n", ang, ang2);
			}
			else{
				// xu_ -= 1.0;
				//printf("x_ = %f, y_ = %f, z_ = %f\n", x_, y_, z_);
			}
			glutPostRedisplay();
			break;
		case 's':
			if(m == 1){
				xtemp = x_ + 2.0*sin(ang*(3.14/180));	
				ztemp = z_ - 2.0*cos(ang*(3.14/180));
				//printf("ztemp = %f, xtemp = %f\n", ztemp, xtemp);
				//printf("flag_parede = %u\n", flag_parede);
				for (int i = 0; i < parede_count; ++i)
				{
					//printf("z1 = %f, x1 = %f, z2 = %f, x2 = %f\n", paredes[i][0]+1.5,-paredes[i][1]-1.5,paredes[i][2]+1.5,-paredes[i][3]-1.5);
					if(ztemp <= paredes[i][2]+1.5 && ztemp >= paredes[i][0]-1.5 && xtemp <= -paredes[i][1]+1.5 && xtemp >= -paredes[i][3]-1.5){
						flag_parede = 1;
						//printf("flag_parede = %u\n", flag_parede);
					}
				}
				if(flag_parede == 1){

				}else{
					x_ = xtemp;	
					z_ = ztemp;
				}
				flag_parede = 0;
			//z_ -= 1.0;
				// x_ += 2.0*sin(ang*(3.14/180));	
				// z_ -= 2.0*cos(ang*(3.14/180));
			}else{
				// xu_ += 2.0*sin(ang*(3.14/180));	
				// zu_ -= 2.0*cos(ang*(3.14/180));
			}
			//printf("x_ = %f, y_ = %f, z_ = %f\n", x_, y_, z_);
			//glTranslatef(x_,y_, z_);	
			glutPostRedisplay();
			break;
		case 'w':
			if(m == 1 ){
				xtemp = x_- 2.0*sin(ang*(3.14/180));	
				ztemp = z_ + 2.0*cos(ang*(3.14/180));
				//printf("ztemp = %f, xtemp = %f\n", ztemp, xtemp);
				//printf("flag_parede = %u\n", flag_parede);
				for (int i = 0; i < parede_count; ++i)
				{
					//printf("z1 = %f, x1 = %f, z2 = %f, x2 = %f\n", paredes[i][0]+1.5,-paredes[i][1]-1.5,paredes[i][2]+1.5,-paredes[i][3]-1.5);
					if(ztemp <= paredes[i][2]+1.5 && ztemp >= paredes[i][0]-1.5 && xtemp <= -paredes[i][1]+1.5 && xtemp >= -paredes[i][3]-1.5){
						flag_parede = 1;
						//printf("flag_parede = %u\n", flag_parede);
					}
				}
				if(flag_parede == 1){

				}else{
					x_ = xtemp;	
					z_ = ztemp;
				}
				flag_parede = 0;
			//z_ += 1.0;
				// x_ -= 2.0*sin(ang*(3.14/180));	
				// z_ += 2.0*cos(ang*(3.14/180));
			} else{
				// xu_ -= 2.0*sin(ang*(3.14/180));	
				// zu_ += 2.0*cos(ang*(3.14/180));
			}
			//printf("x_ = %f, y_ = %f, z_ = %f\n", x_, y_, z_);	
			glutPostRedisplay();
			break;
		case 'm':
			if(m == 1){
				texturas = !texturas;
				tmp_ang = ang;
				z_temp = z_;
				x_temp = x_;
				zu_ = zu_temp;
				xu_ = xu_temp;
				ang = 0.0; 
				m = 0;
				y_ = -40.0;
				ang2 = 90.0;
				dz = 70.0;
				glutPostRedisplay();
				}
			else{
				if(m == 0){
				texturas = !texturas;
				ang = tmp_ang;
				z_ = z_temp;
				x_ = x_temp;
				zu_temp = zu_;
				xu_temp = xu_;
				m = 1;
				y_ = -0.5;
				ang2 = 0.0;
				dz = 10.0;
				//printf("dz = %f\n", dz);
				glutPostRedisplay();
				}
			}
			break;
		case 27:
			exit(0);
			break;
	}
}

int main(int argc, char** argv)
{
	int res;
    pthread_t a_thread;
    void *thread_result;
    res = pthread_create(&a_thread, NULL, thread_function, (void*)message);
    if (res != 0) {
        perror("A Craição da Thread falhou");
        exit(EXIT_FAILURE);
    }
	ReadMaze();
	detect_parede();
	//PlaySound("mb_new.wav", NULL, SND_ASYNC);
	glutInit(&argc,argv);
	glutInitDisplayMode ( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	//glutInitWindowSize (1280, 720); 
   glutInitWindowPosition (0, 0);
   glutCreateWindow (argv[0]);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc( keyboard );
	glutDisplayFunc(display);
	glutFullScreen();
	
	init();
	glutMainLoop();
}

void *thread_function(void *arg) {
	while(fase < 4){
		//printf("tempo = %u\n", tempo);
		sleep(1);
		tempo++;
	}
    pthread_exit((void *) "Jogo encerrado.");
}