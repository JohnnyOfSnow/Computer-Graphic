/*
 * FreeGLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone 
 * and torus shapes in FreeGLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */

#include <GL/glut.h>

#include <stdlib.h>
#include <math.h>
#define GL_PI = 3.14;
static int slices = 16;
static int stacks = 16;
static int Earthday = 1;
static int WaterPlantday = 20;
static int GoldPlantday = 3;
static int FirePlantday = 5;
static int Sunday = 11;
const int n = 1000;
const GLfloat R = 0.5f;
const GLfloat Pi = 3.1415926536f;
float radius = 5.0f;     //radious??半?
float step = 0.1f;
float x;
float y;
float angle;
/* GLUT callback Handlers */

static void 
resize(int width, int height)
{
    const float ar = (float) width / (float) height;
    
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

static void 
display(void)
{
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = t*90.0; //調地球公轉速度 
    const double b = t*45.0; //調金星公轉速度 
    const double c = t*30.0; //調水星公轉速度 
    const double d = t*20.0; //調火星公轉速度 
    Earthday = (Earthday + 1) % 360; //調地球自轉角度吧?  
    WaterPlantday = (WaterPlantday + 1) % 360; //調水星自轉角度吧?  
    GoldPlantday = (GoldPlantday + 20)% 360; //調金星自轉角度吧? 
    FirePlantday = (FirePlantday + 10)% 360; //調火星自轉角度吧?
    Sunday = (Sunday + 5) % 360;//調太陽自轉角度吧?
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1,0,0);
    glEnable(GL_DEPTH_TEST);
    glClearColor (0.0, 0.0, 0.0, 0.0);

  

     glPushMatrix();                            //太陽
        glColor3d(1,0,0);
            glTranslatef(0.0, 0.0, -20.0);
            glRotatef(Sunday, 0.2,3.0, 0.0); //自轉 (速度, 旋轉向量)
            glutWireSphere(3,slices,stacks);
    glPopMatrix();
    
    glPushMatrix();                            //水星 
        glColor3d(0,1,1);
            glTranslatef(0.0, 0.0, -20.0);
            glRotatef(c, 0.0,1.0, 0.0); //公轉 (繞y軸轉)
           glTranslatef(0.0, 0.0, 4.0);  
           glRotatef(WaterPlantday, 0.0, 0.0, 1.0); //自轉 (速度, 旋轉向量)
           glutSolidSphere(0.06,slices,stacks);
    glPopMatrix();
    
    glBegin(GL_LINE_STRIP);   //水星 的軌道 
    glColor3d(0,0,1);
      radius = 4.0f;     //radious
      step = 0.1f;        //step
      for(angle = 0.0f; angle <= (2.0f*3.14159f); angle += step){
        x = radius *sin(angle);
        y = radius *cos(angle);

       // Specify the point and move the Z value up a little	
       glVertex3f(x , 0, -20.0f + y);
    }
    glEnd();
   
    glPushMatrix();                            //金星 
        glColor3d(1,1,0);
            glTranslatef(0.0, 0.0, -20.0);
            glRotatef(b, 0.0,1.0, 0.0); //公轉 (繞y軸轉)
           glTranslatef(0.0, 0.0, 6.0);  
           glRotatef(GoldPlantday, 0.0, 1.0, 1.0); //自轉 (速度, 旋轉向量)
           glutWireSphere(0.86,slices,stacks);
    glPopMatrix();
    
    glBegin(GL_LINE_STRIP);   //金星 的軌道 
      glColor3d(0,1,1);
      x = 0.0f;
      y = 0.0f;
    
      radius = 6.0f;     //radius
      step = 0.1f;        //step
      for(angle = 0.0f; angle <= (2.0f*3.14159f); angle += step){
        x = radius *sin(angle);
        y = radius *cos(angle);

       // Specify the point and move the Z value up a little	
       glVertex3f(x , 0, -20.0f + y);
    } 
    glEnd();
    
    
     glPushMatrix();                            //地球
        glColor3d(0,0,1);
            glTranslatef(0.0, 0.0, -20.0);
            glRotatef(a, 0.0,1.0, 0.0); //公轉 (繞y軸轉)
           glTranslatef(0.0, 0.0, 7.0);  
           glRotatef(Earthday, 0.0, 0.0, 1.0); //自轉 (速度, 旋轉向量)
           glutSolidSphere(1.0,slices,stacks);
    glPopMatrix();
    
    glBegin(GL_LINE_STRIP);   //地球 的軌道 
      glColor3d(1,0,0);
      x = 0.0f;
      y = 0.0f;
    
      radius = 7.0f;     //radius
      step = 0.1f;        //step
      for(angle = 0.0f; angle <= (2.0f*3.14159f); angle += step){
        x = radius *sin(angle);
        y = radius *cos(angle);

       // Specify the point and move the Z value up a little	
       glVertex3f(x , 0, -20.0f + y); // x-z軸圓 
    }
    glEnd();
    
    glBegin(GL_LINE_STRIP);   //火星 的軌道 
    glColor3d(0,1,0);
    x = 0.0f;
    y = 0.0f;
    
      radius = 9.0f;     //radius
      step = 0.1f;        //step?
      for(angle = 0.0f; angle <= (2.0f*3.14159f); angle += step){
        x = radius *sin(angle);
        y = radius *cos(angle);

       // Specify the point and move the Z value up a little	
       glVertex3f(x , 0, -20.0f + y);  // x-z軸圓 
    }
    glEnd();
    
    glPushMatrix();                            //火星 
        glColor3d(1,0,0);
            glTranslatef(0.0, 0.0, -20.0);
            glRotatef(d, 0.0,1.0, 0.0); //公轉 (繞y軸轉)
           glTranslatef(0.0, 0.0, 9.0);  
           glRotatef(FirePlantday, 0.0, 0.0, 1.0); //自轉 (速度, 旋轉向量)
           glutWireSphere(0.15,slices,stacks);
    glPopMatrix();
    glutSwapBuffers();
    
}


static void 
key(unsigned char key, int x, int y)
{
    switch (key) 
    {
        case 27 : 
        case 'q':
            exit(0);
            break;

        case '+':
            slices++;
            stacks++;
            break;

        case '-':
            if (slices>3 && stacks>3)
            {
                slices--;
                stacks--;
            }
            break;
    }

    glutPostRedisplay();
}

static void 
idle(void)
{
    glutPostRedisplay();
}

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

/* Program entry point */

int 
main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("FreeGLUT Shapes");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);

    glClearColor(1,1,1,1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

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

    glutMainLoop();

    return EXIT_SUCCESS;
}
