#include <GL/glut.h>
#include<string.h>
#include<windows.h>
#include <iostream>
#include <math.h>


#define MAX_PARTICLES 1000
#define WCX		640
#define WCY		480
#define RAIN	0
#define SNOW	1
#define	HAIL	2
#define FP    10
void display();
using namespace std;

int flag=0;
int fp=0;
char *str = "***************************************************";
char *str1 = "MANGALORE INSTITUTE OF TECHNOLOGY & ENGINEERING";
char *str2 = "DEPARTMENT OF COMPUTER SCIENCE AND ENGINEERING";
char *str3 = "COMPUTER GRAPHICS AND VISUALIZATION LABORATORY";
char *str4 = "A MINI PROJECT";
char *str5 = "ON";
char *str6 = "OPENGL FOG SIMULATION";
char *str7 = "Submitted By:";
char *str8 = "RAVI R MOOLYA   - 4MT15CS080";
char *str9 = "PRASHANT SALIAN - 4MT15CS088";
char *str10 = "Submitted to:";
char *str11 = "MR. SUNIL KUMAR S";
char *str12 = "MR. PRASHANTH B.S";
char *str13 = "<--- Press ENTER key to Continue --->";
void *font = GLUT_BITMAP_TIMES_ROMAN_24;

void special(int,int,int);
void Key(unsigned char,int,int);

static float fog_color[] = {0.8, 0.8, 0.8, 1.0};
float lx=-800.0f,ly=1400.0f,lz=500.0f;
float fogDensity = 0.0002;
GLfloat ar=1.0f,ag=1.0f,ab=0.0f;
 GLfloat light_ambient[]  = { ar, ag, ab, 0.5f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = {lx,ly,lz,0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };


GLfloat d=10;

GLfloat X=0;
GLfloat Y=0;
GLfloat Z=-800;

GLfloat A=0;
GLfloat B=0;

GLfloat p=0;
GLfloat q=0;
//GLfloat r=1;

GLfloat dw=0.5;

GLfloat R=100;

GLfloat X2=0;
GLfloat Y2=0;
GLfloat Z2=1000;

GLfloat FXmin;
GLfloat FXmax;
GLfloat FYmin;
GLfloat FYmax;

GLfloat angle=0;

GLfloat angley=0;

GLfloat C1[3];
GLfloat C2[3];

GLfloat WC[3];

GLfloat W;
GLfloat dW;


int M=-1;
int ax=-1;
int N=-1;



float slowdown = 2.0;
float velocity = 0.0;
float zoom = -40.0;
float pan = 0.0;
float tilt = 0.0;
float hailsize = 0.1;

int loop;
int fall;

//floor colors
float r = 0.0;
float g = 1.0;
float b = 0.0;
float ground_points[21][21][3];
float ground_colors[21][21][4];
float accum = -10.0;

typedef struct {
	// Life
	bool alive;	// is the particle alive?
	float life;	// particle lifespan
	float fade; // decay
	// color
	float red;
	float green;
	float blue;
	// Position/direction
	float xpos;
	float ypos;
	float zpos;
	// Velocity/Direction, only goes down in y dir
	float vel;
	// Gravity
	float gravity;
}particles;



void SetC1(float x,float y,float z)
{
   C1[0]=x;
   C1[1]=y;
   C1[2]=z;
}

void SetC2(float x,float y,float z)
{
   C2[0]=x;
   C2[1]=y;
   C2[2]=z;
}

void SetWin(float x,float y,float z,float p,float q)
{
   WC[0]=x;
   WC[1]=y;
   WC[2]=z;

   W=p;  dW=q;
}







void Building(float l,float b,float h)
{

   glColor3f(1,0,0);
   glBegin(GL_POLYGON);
   glVertex3f(l/2,0,b/2);
   glVertex3f(l/2,0,-b/2);
   glVertex3f(-l/2,0,-b/2);
   glVertex3f(-l/2,0,+b/2);
   glEnd();


   glColor3fv(C1);
   glBegin(GL_POLYGON);
   glVertex3f(l/2,h,-b/2);
   glVertex3f(l/2,0,-b/2);
   glVertex3f(-l/2,0,-b/2);
   glVertex3f(-l/2,h,-b/2);
   glEnd();


   glColor3fv(C2);
   glBegin(GL_POLYGON);
  glVertex3f(-l/2,h,-b/2);
   glVertex3f(-l/2,h,b/2);
   glVertex3f(-l/2,0,b/2);
   glVertex3f(-l/2,0,-b/2);
   glEnd();



   glColor3fv(C1);
   glBegin(GL_POLYGON);
   glVertex3f(-l/2,h,b/2);
   glVertex3f(l/2,h,b/2);
   glVertex3f(l/2,0,b/2);
   glVertex3f(-l/2,0,b/2);
   glEnd();



   glColor3fv(C2);
   glBegin(GL_POLYGON);
   glVertex3f(l/2,h,b/2);
   glVertex3f(l/2,0,b/2);
   glVertex3f(l/2,0,-b/2);
   glVertex3f(l/2,h,-b/2);
   glEnd();



   glColor3f(0,0,1);
   glBegin(GL_POLYGON);
   glVertex3f(l/2,h,b/2);
   glVertex3f(l/2,h,-b/2);
   glVertex3f(-l/2,h,-b/2);
   glVertex3f(-l/2,h,b/2);
   glEnd();



}




void twistsearsTower(float l,float b,int blocks,float h,float d,float dangle)
{

  int i=1;


  float th;

  th=0;  float ax=0;

  for(i=0;i<blocks;i++)
  {
    glPushMatrix();
    glTranslatef(0,th,0);
    glRotatef(ax,0,1,0);
      Building(l,b,h);
      //cout<<l<<" "<<b<<" "<<BH[i]<<endl;
      glPopMatrix();
      th=th+h;
      l=l-d;  b=b-d;

      ax=ax+dangle;
  }
}

void searsTower(float l,float b,int blocks,float BH[20],float d)
{

  int i=1;


  float th;

  th=0;
  for(i=0;i<blocks;i++)
  {
    glPushMatrix();
    glTranslatef(0,th,0);
    //glRotatef(ax,0,1,0);
      Building(l,b,BH[i]);
     // cout<<l<<" "<<b<<" "<<BH[i]<<endl;
      glPopMatrix();
      th=th+BH[i];
      l=l-d;  b=b-d;

  }
}

void myinit()
{
    glClearColor(0.0,0.0,0.0,1.0);
    glMatrixMode(GL_PROJECTION);
    glOrtho(-10.0,10.0,-10.0,10.0,-10,0);
    //glMatrixMode(GL_MODELVIEW);
    //glEnable(GL_DEPTH_TEST);
}

 void draw_front_page()
{
    myinit();
    int i=0;
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);

	glColor3f(0.9, 0.9, 0.9); // foreground color
	glRasterPos2f(-5,10);
	for (i = 0;i < strlen(str);i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]); //****
	/*glRasterPos2f(-5,9);
	for (i = 0;i < strlen(str);i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);*/

	glRasterPos2f(-4.5,-10);
	for (i = 0;i < strlen(str);i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]); //****
	glRasterPos2f(-4.5,-9);
	for (i = 0;i < strlen(str);i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);

	glRasterPos2f(-5,8);
	for (i = 0;i < strlen(str1);i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str1[i]); //MITE
	glRasterPos2f(-4.9, 7);
	for (i = 0;i<strlen(str2);i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str2[i]); //DEPARTMENT OF COMPUTER SCIENCE AND ENGINEERING
	glRasterPos2f(-4.9, 5);
	for (i = 0;i<strlen(str3);i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str3[i]); //COMPUTER GRAPHICS AND VISUALIZATION LABORATORY
	glRasterPos2f(-1.5, 3);
	for (i = 0;i<strlen(str4);i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str4[i]); //A MINI PROJECT
	glRasterPos2f(-0.4,2.1);
	for (i = 0;i<strlen(str5);i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str5[i]); //ON
	glRasterPos2f(-2.3, 1.2);
	for (i = 0;i<strlen(str6);i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str6[i]); //SIMULATION OF GEARBOX
	glRasterPos2f(-6.5, -4);
	for (i = 0;i<strlen(str7);i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str7[i]); //DESIGNED BY:
	glRasterPos2f(-6.5, -5);
	for (i = 0;i<strlen(str8);i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str8[i]);
	glRasterPos2f(-6.5, -6);
	for (i = 0;i<strlen(str9);i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str9[i]);
	glRasterPos2f(3, -4);
	for (i = 0;i<strlen(str10);i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str10[i]);
	glRasterPos2f(3, -5);
	for (i = 0;i<strlen(str11);i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str11[i]);
	glRasterPos2f(3, -6);
	for (i = 0;i<strlen(str12);i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str12[i]);

		//glTranslated(-1,0,0);
    glRasterPos2f(-3,-8);
	for (i = 0;i<strlen(str13);i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str13[i]);


    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnd();
    //glFlush();

}


particles par_sys[MAX_PARTICLES];


void initParticles(int i) {
		par_sys[i].alive = true;
		par_sys[i].life = 1.0;
		par_sys[i].fade = float(rand()%100)/1000.0f+0.003f;

		par_sys[i].xpos = (float) (rand() % 21) - 10;
		par_sys[i].ypos = 10.0;
		par_sys[i].zpos = (float) (rand() % 21) - 10;

		par_sys[i].red = 0.5;
		par_sys[i].green = 0.5;
		par_sys[i].blue = 1.0;

		par_sys[i].vel = velocity;
		par_sys[i].gravity = -0.8;//-0.8;

}


void drawRain() {
	float x, y, z;
	for (loop = 0; loop < MAX_PARTICLES; loop=loop+2) {
		if (par_sys[loop].alive == true) {
			x = par_sys[loop].xpos;
			y = par_sys[loop].ypos;
			z = par_sys[loop].zpos + zoom;


			glColor3f(0.5, 0.5, 1.0);
			glBegin(GL_LINES);
				glVertex3f(x, y, z);
				glVertex3f(x, y+0.5, z);
			glEnd();


			par_sys[loop].ypos += par_sys[loop].vel / (slowdown*1000);
			par_sys[loop].vel += par_sys[loop].gravity;

			par_sys[loop].life -= par_sys[loop].fade;

			if (par_sys[loop].ypos <= -10) {
				par_sys[loop].life = -1.0;
			}

			if (par_sys[loop].life < 0.0) {
				initParticles(loop);
			}
		}
	}
	//glutSwapBuffers();
}



 void Key(unsigned char key, int x, int y)
{
  switch (key) {
  case 'd':
    fogDensity *= 1.10;
    glFogf(GL_FOG_DENSITY, fogDensity);
    glutPostRedisplay();
    break;
  case 'D':
    fogDensity /= 1.10;
    glFogf(GL_FOG_DENSITY, fogDensity);
    glutPostRedisplay();
    break;
  case 'R':
        fall = RAIN;
		glutPostRedisplay();
		break;


  case 'q':
    exit(0);
  }
  if( key == (char)13)
  {
      if(flag == 0)
        flag = 1;
  }
  glutPostRedisplay();
}





void special(int key,int x,int y)
{


   switch(key)
   {
      case GLUT_KEY_LEFT:  ;  { X=X-20; } break;


      case GLUT_KEY_RIGHT:  { X=X+20; };   break;

      case  GLUT_KEY_DOWN:  { Z=Z-20; }  break;

      case GLUT_KEY_UP:  { Z=Z+20; }   break;

      case GLUT_KEY_F1: {Y=Y+20; } break;

      case GLUT_KEY_F2: {Y= Y-20; } break;


   }

    //cout<<X<<" "<<Y<<" "<<Z<<endl;

   //updateView();
   glutPostRedisplay();
}


void Axes()
{
    glLineWidth(10);

    glColor3f(1,0,0);

    glBegin(GL_LINES);
    glVertex3f(0,1,5000);
    glVertex3f(0,1,-5000);
    glEnd();



     glColor3f(1,0,1);

    glBegin(GL_LINES);
    glVertex3f(0,5000,0);
    glVertex3f(0,-5000,0);
    glEnd();

     glColor3f(0,0,1);

    glBegin(GL_LINES);
    glVertex3f(5000,1,0);
    glVertex3f(-5000,1,0);
    glEnd();

    glLineWidth(2.5);


    for(int i=-5000;i<=5000;i+=100)
    {
       glColor3f(1,0,0);
     glBegin(GL_LINES);
    glVertex3f(i,1,5000);
    glVertex3f(i,1,-5000);
    glEnd();

    }

    for(int i=-5000;i<=5000;i+=100)
    {
      glColor3f(0,0,1);
     glBegin(GL_LINES);
    glVertex3f(5000,1,i);
    glVertex3f(-5000,1,i);
    glEnd();

    }


}

void sun(){
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1,1,0);
    glPushMatrix();
        glTranslatef(lx,ly,lz);
        glutSolidSphere(100,300,300);
    glPopMatrix();

}



void display(void)
{

  glClearColor(0.8,0.8,0.8,1);
  if(flag == 0){
      draw_front_page();
  }
  else{


   glClearDepth(1);
   glClear(GL_COLOR_BUFFER_BIT);
   glClear(GL_DEPTH_BUFFER_BIT);

   glEnable(GL_DEPTH_TEST);
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();

  gluPerspective(45,16/9,1,10000);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

/*      for (loop = 0; loop < MAX_PARTICLES; loop++)
        {
        initParticles(loop);
        }*/
//prashanthsagar@mite.ac.in
glFlush();

gluLookAt(X,Y,Z,X2,Y2,Z2,0,1,0);


glColor3f(1.0,1.0,1.0);

  glRotatef(angle,0,1,0);
  glRotatef(angley,1,0,0);


     if(ax==1)
     Axes();
    sun();


   glColor3f(0,1,0);
   glBegin(GL_POLYGON);
   glVertex3f(-1000,0,-1000);
   glVertex3f(-1000,0,1000);
   glVertex3f(1000,0,1000);
   glVertex3f(1000,0,-1000);
   glEnd();


   glBegin(GL_POLYGON);
   glVertex3f(1000,0,1000);
   glVertex3f(1000,0,-1000);
   glVertex3f(1300,-25,-1300);
   glVertex3f(1300,-25,1300);
   glEnd();


  glBegin(GL_POLYGON);
   glVertex3f(-1000,0,1000);
   glVertex3f(1000,0,1000);
   glVertex3f(1300,-25,1300);
   glVertex3f(-1300,-25,1300);
   glEnd();


   glBegin(GL_POLYGON);
   glVertex3f(-1000,0,1000);
   glVertex3f(-1000,0,-1000);
   glVertex3f(-1300,-25,-1300);
   glVertex3f(-1300,-25,1300);
   glEnd();


 glPushMatrix();
 glScalef(1,2,1);

   glPushMatrix();
   glScalef(0.5,0.5,0.5);

   glPopMatrix();

SetC1(0.69,0.769,0.871);
  SetC2(0.373,0.620,0.627);
  SetWin(0,0,1,0.8,4);
   glPushMatrix();
  glTranslatef(-300,0,-300);
  // petronas();
   glPopMatrix();


    SetC1(0.69,0.769,0.871);
  SetC2(0.373,0.620,0.627);
  SetWin(0.529,0.808,0.922,3,9);
   glPushMatrix();
  glTranslatef(900,0,-200);
  glRotatef(90,0,1,0);
   Building(300,100,100);
   glPopMatrix();


    SetC1(0.741,0.718,0.420);
  SetC2(0.502,0.502,0.000);
  SetWin(0.373,0.620,0.627,4,12);
   glPushMatrix();
  glTranslatef(900,0,200);
  glRotatef(90,0,1,0);
   Building(300,100,200);
   glPopMatrix();





     SetC1(0.275,0.510,0.706);
  SetC2(0.373,0.620,0.627);
    SetWin(0,0,1,0.8,4);
   glPushMatrix();
   glTranslatef(-470,0,-525);
  //glRotatef(90,0,1,0);
   Building(50,50,250);
   glPopMatrix();




    SetC1(0.275,0.510,0.706);
  SetC2(0.373,0.620,0.627);
  SetWin(0,0,1,0.8,4);
   glPushMatrix();
  glTranslatef(-540,0,-500);
  glRotatef(90,0,1,0);
   Building(50,50,250);
   glPopMatrix();

/*
   //road
       SetC1(0,0,0);
  SetC2(1,1,1);
  SetWin(0,0,1,0.8,4);
   glPushMatrix();
  glTranslatef(100,0,-700);
  glRotatef(90,0,1,0);
   Building(150,2300,2);
   glPopMatrix();

*/


    SetC1(0.741,0.718,0.420);
  SetC2(0.502,0.502,0.000);
  SetWin(0.373,0.620,0.627,1.5,5);
   glPushMatrix();
  glTranslatef(550,0,-150);
  //glRotatef(90,0,1,0);
   Building(100,50,100);
   glPopMatrix();




        SetC1(0.850,0.510,0.20);
  SetC2(1.00,0.620,0.15);
  SetWin(0.0,0.808,0.820,3,8);
   glPushMatrix();
  glTranslatef(730,0,500);
  glRotatef(45,0,1,0);
   Building(50,50,250);
   glPopMatrix();



      SetC1(0.850,0.510,0.20);
  SetC2(1.00,0.620,0.15);
  SetWin(0.0,0.808,0.820,3,8);
   glPushMatrix();
  glTranslatef(750,0,500);
  glRotatef(45,0,1,0);
   Building(30,30,300);
   Building(20,20,500);
   glPopMatrix();

   //new
    SetC1(0.275,1.00,0.706);
  SetC2(.373,0.620,0.627);
  SetWin(0.0,0.808,0.820,3,8);
   glPushMatrix();
  glTranslatef(492,0,500);
  glRotatef(45,0,1,0);
   Building(35,35,200);
    glRotatef(45,0,1,0);
   Building(30,30,300);
  glRotatef(45,0,1,0);
   Building(25,25,400);
   glRotatef(45,0,1,0);
   Building(20,20,500);
   glPopMatrix();





   SetC1(0.275,0.510,0.706);
  SetC2(0.373,0.620,0.627);
  SetWin(0.0,0.808,0.820,3,8);

  float arr4[10]={80,60,40,20,10};

   glPushMatrix();
  glTranslatef(710,0,-150);
  glRotatef(90,0,1,0);
   searsTower(100,100,5,arr4,5);
   glPopMatrix();

    SetC1(0.275,0.510,0.706);
  SetC2(0.373,0.620,0.627);
  SetWin(0.0,0.808,0.820,3,8);
   glPushMatrix();
  glTranslatef(710,0,-150);
  glRotatef(90,0,1,0);
   Building(100,50,250);
   glPopMatrix();




   SetC1(0.275,0.510,0.706);
  SetC2(0.373,0.620,0.627);
  SetWin(0.0,0.808,0.820,3,8);
   glPushMatrix();
  glTranslatef(150,0,500);
  glRotatef(45,0,1,0);
   Building(50,50,250);
   glPopMatrix();


  SetC1(0.741,0.718,0.420);
  SetC2(0.502,0.502,0.000);
  SetWin(0.373,0.620,0.627,4,12);
   glPushMatrix();
  glTranslatef(-450,0,500);
  //glRotatef(90,0,1,0);
   Building(200,100,200);
   glPopMatrix();


glPopMatrix();
  }
  glutSwapBuffers();
  glFlush();

}









int f=1;
void FUN()
{ if(flag==0)
{
;
}
else{
    if(M==1)
      angle=angle+1;
     lx+=0.10;
     if(lx>800){
            if(f==1){
       ar=1.0;ag=1.0;ab=1.0;
       f=0;}
       else{
         ar=1.0;ag=1.0;ab=0.0;
       }
        lx=-800;
      glutPostRedisplay();
     }

    glutPostRedisplay();
}
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowPosition(0,0);
  glutCreateWindow("Test");
  glutFullScreen();
  glEnable(GL_FOG);
  glFogi(GL_FOG_MODE, GL_EXP2);
  glFogf(GL_FOG_DENSITY, fogDensity);
  glFogfv(GL_FOG_COLOR, fog_color);
  glClearColor(0.8, 0.8, 0.8, 1.0);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

      glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
     glutSpecialFunc(special);
    glutKeyboardFunc(Key);
  glutDisplayFunc(display);
  glutIdleFunc(FUN);
  glutMainLoop();

  return 0;
}

