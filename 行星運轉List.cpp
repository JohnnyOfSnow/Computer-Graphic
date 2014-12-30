/**************************
 * Includes
 *
 **************************/

#include <windows.h>
#include <GL/glut.h>
#include <gl/gl.h>
#include <math.h>
#define GL_PI 3.14;
#define SUN 1;
#define WATER 2;
#define WATERLINE 3;
#define GOLD 4;
#define GOLDLINE 5;
#define EARTH 6;
#define EARTHLINE 7;
#define MARS 8;
#define MARSLINE 9;
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

/**************************
 * Function Declarations
 *
 **************************/
LRESULT CALLBACK WndProc (HWND hWnd, UINT message,
WPARAM wParam, LPARAM lParam);
void EnableOpenGL (HWND hWnd, HDC *hDC, HGLRC *hRC);
void DisableOpenGL (HWND hWnd, HDC hDC, HGLRC hRC);


/**************************
 * WinMain
 *
 **************************/

int WINAPI WinMain (HINSTANCE hInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpCmdLine,
                    int iCmdShow)
{
    WNDCLASS wc;
    HWND hWnd;
    HDC hDC;
    HGLRC hRC;        
    MSG msg;
    BOOL bQuit = FALSE;
    float theta = 0.0f;

    /* register window class */
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor (NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH) GetStockObject (BLACK_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "GLSample";
    RegisterClass (&wc);

    /* create main window */
    hWnd = CreateWindow (
      "GLSample", "OpenGL Sample", 
      WS_CAPTION | WS_POPUPWINDOW | WS_VISIBLE,
      0, 0, 256, 256,
      NULL, NULL, hInstance, NULL);

    /* enable OpenGL for the window */
    EnableOpenGL (hWnd, &hDC, &hRC);
    
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = t*90.0; //調地球公轉速度 
    const double b = t*45.0; //調金星公轉速度 
    const double c = t*30.0; //調水星公轉速度 
    const double d = t*20.0; //調火星公轉速度 
    glNewList(SUN,GL_COMPILE);  //太陽
      glColor3d(1,0,0);
      glTranslatef(0.0, 0.0, -20.0);
      glRotatef(Sunday, 0.2,3.0, 0.0); //自轉 (速度, 旋轉向量)
      glutWireSphere(3,slices,stacks);
    glEndList();
   
   glNewList(WATER, GL_COMPILE);  //水星 
      glColor3d(0,1,1);
      glTranslatef(0.0, 0.0, -20.0);
      glRotatef(c, 0.0,1.0, 0.0); //公轉 (繞y軸轉)
      glTranslatef(0.0, 0.0, 4.0);  
      glRotatef(WaterPlantday, 0.0, 0.0, 1.0); //自轉 (速度, 旋轉向量)
      glutSolidSphere(0.06,slices,stacks);
    glEndList();
    
    glNewList(WATERLINE, GL_COMPILE);   
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
    glEndList();
    
    glNewList(GOLD, GL_COMPILE);  //金星 
      glColor3d(1,1,0);
      glTranslatef(0.0, 0.0, -20.0);
      glRotatef(b, 0.0,1.0, 0.0); //公轉 (繞y軸轉)
      glTranslatef(0.0, 0.0, 6.0);  
      glRotatef(GoldPlantday, 0.0, 1.0, 1.0); //自轉 (速度, 旋轉向量)
      glutWireSphere(0.86,slices,stacks);
    glEndList();
    
    glNewList(GOLDLINE, GL_COMPILE);   
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
    glEndList();
    
    glNewList(EARTH, GL_COMPILE);  //地球 
      glColor3d(0,0,1);
      glTranslatef(0.0, 0.0, -20.0);
      glRotatef(a, 0.0,1.0, 0.0); //公轉 (繞y軸轉)
      glTranslatef(0.0, 0.0, 7.0);  
      glRotatef(Earthday, 0.0, 0.0, 1.0); //自轉 (速度, 旋轉向量)
      glutSolidSphere(1.0,slices,stacks);
    glEndList();
    
    glNewList(EARTHLINE, GL_COMPILE);   
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
    glEndList();
    
    glNewList(MARS, GL_COMPILE);  //火星 
      glColor3d(1,0,0);
      glTranslatef(0.0, 0.0, -20.0);
      glRotatef(d, 0.0,1.0, 0.0); //公轉 (繞y軸轉)
      glTranslatef(0.0, 0.0, 9.0);  
      glRotatef(FirePlantday, 0.0, 0.0, 1.0); //自轉 (速度, 旋轉向量)
      glutWireSphere(0.15,slices,stacks);
    glEndList();
    
    glNewList(MARSLINE, GL_COMPILE);   
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
    glEndList();
    
    /* program main loop */
    while (!bQuit)
    {
        /* check for messages */
        if (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE))
        {
            /* handle or dispatch messages */
            if (msg.message == WM_QUIT)
            {
                bQuit = TRUE;
            }
            else
            {
                TranslateMessage (&msg);
                DispatchMessage (&msg);
            }
        }
        else
        {
            
            Earthday = (Earthday + 1) % 360; //調地球自轉角度吧?  
            WaterPlantday = (WaterPlantday + 1) % 360; //調水星自轉角度吧?  
            GoldPlantday = (GoldPlantday + 20)% 360; //調金星自轉角度吧? 
            FirePlantday = (FirePlantday + 10)% 360; //調火星自轉角度吧?
            Sunday = (Sunday + 5) % 360;//調太陽自轉角度吧?
    
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glColor3d(1,0,0);
            glEnable(GL_DEPTH_TEST);
            glClearColor (0.0, 0.0, 0.0, 0.0);

            glPushMatrix();
              glCallList(2); 
            glPopMatrix();
            
            glPushMatrix();
              glCallList(4); 
            glPopMatrix();
            
            glPushMatrix();
              glCallList(6); 
            glPopMatrix();
            
            glPushMatrix();
              glCallList(8); 
            glPopMatrix();
            
             glPushMatrix();
              glCallList(1); 
            glPopMatrix();
            
             glPushMatrix();
              glCallList(3); 
            glPopMatrix();
            
             glPushMatrix();
              glCallList(5); 
            glPopMatrix();
            
            glPushMatrix();
              glCallList(7); 
            glPopMatrix();
            
            glPushMatrix();
              glCallList(9); 
            glPopMatrix();
            
            SwapBuffers (hDC);

            
        }
    }

    /* shutdown OpenGL */
    DisableOpenGL (hWnd, hDC, hRC);

    /* destroy the window explicitly */
    DestroyWindow (hWnd);

    return msg.wParam;
}


/********************
 * Window Procedure
 *
 ********************/

LRESULT CALLBACK WndProc (HWND hWnd, UINT message,
                          WPARAM wParam, LPARAM lParam)
{

    switch (message)
    {
    case WM_CREATE:
        return 0;
    case WM_CLOSE:
        PostQuitMessage (0);
        return 0;

    case WM_DESTROY:
        return 0;

    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_ESCAPE:
            PostQuitMessage(0);
            return 0;
        }
        return 0;

    default:
        return DefWindowProc (hWnd, message, wParam, lParam);
    }
}


/*******************
 * Enable OpenGL
 *
 *******************/

void EnableOpenGL (HWND hWnd, HDC *hDC, HGLRC *hRC)
{
    PIXELFORMATDESCRIPTOR pfd;
    int iFormat;

    /* get the device context (DC) */
    *hDC = GetDC (hWnd);

    /* set the pixel format for the DC */
    ZeroMemory (&pfd, sizeof (pfd));
    pfd.nSize = sizeof (pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | 
      PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;
    iFormat = ChoosePixelFormat (*hDC, &pfd);
    SetPixelFormat (*hDC, iFormat, &pfd);

    /* create and enable the render context (RC) */
    *hRC = wglCreateContext( *hDC );
    wglMakeCurrent( *hDC, *hRC );

}


/******************
 * Disable OpenGL
 *
 ******************/

void DisableOpenGL (HWND hWnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent (NULL, NULL);
    wglDeleteContext (hRC);
    ReleaseDC (hWnd, hDC);
}
