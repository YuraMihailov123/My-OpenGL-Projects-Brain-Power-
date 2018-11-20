#include <GL/glut.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <iostream>
#include "AdditionalFunc.h"

using namespace std;

int n=20;
float dirX=1,dirY=0;
int num=2;
int w=800,h=800;
char buff[100];
char title[100]="'Snake' Score: ";
char titleRes[100]="'Snake' Score: ";

class Fruit{
public:
        float x,y;
        void Create();
        void DrawFruit();
};

Fruit f;

void Fruit::Create(){
        this->x =rand() % n;
        this->y =rand() % n;        
        
}
void Fruit::DrawFruit(){
        glColor3f(1.0,1.0,0.0);
        glRectf(this->x,this->y,this->x+1,this->y+1);
}

struct Cube{
    float x,y;        
}zm[100];

void MoveBody(){
       
    for(int i=num;i>0;i--){
        zm[i].x = zm[i-1].x;
        zm[i].y = zm[i-1].y;
    }
    zm[0].x +=dirX*1;
    zm[0].y +=dirY*1;
    
    if(zm[0].x==f.x && zm[0].y==f.y){
        
        num++;
        f.Create();      
    }
    
    if(zm[0].x<0)dirX=1;
    if(zm[0].x>n-1)dirX=-1;
    if(zm[0].y<0)dirY=1;
    if(zm[0].y>n-1)dirY=-1;
    
    for(int i=1;i<num;i++){
        if(zm[0].x==zm[i].x && zm[0].y==zm[i].y)
                num =i;
    }
     
}
void displayMe(void)
{
    glPushMatrix();
    glClear(GL_COLOR_BUFFER_BIT);
    f.DrawFruit();
    glColor3f(1.0f,0.0f,0.0f); 
    for(int i=0;i<num;i++){    
        glRectf(zm[i].x,zm[i].y,zm[i].x+1,zm[i].y+1);
    }
       
    glColor3f(0.5f,0.5f,1.0f);  
    glBegin(GL_LINES);
        for(float i=0;i<=w/4;i+=10.0){
               glVertex2f(i/10, 0);
               glVertex2f(i/10, 100);
        }
        for(float i=0;i<=h/4;i+=10.0){
               glVertex2f(0,i/10);
               glVertex2f(100,i/10);
        }
    glEnd();
    glutSetWindowTitle(strcat(title,itoa(num-2,buff,10)));
    glPopMatrix();
    glutSwapBuffers();
}

void SKeyboard(int key, int x,int y)
{
        switch(key){
                case GLUT_KEY_LEFT: dirX=-1;dirY=0;
                        break;
                case GLUT_KEY_RIGHT: dirX=1;dirY=0;
                        break;     
                case GLUT_KEY_UP: dirX=0;dirY=1;
                        break;    
                case GLUT_KEY_DOWN: dirX=0;dirY=-1;
                        break;                           
        }
}

void Timer(int){
        strcpy(title,titleRes);
        MoveBody();
        glutPostRedisplay();
        glutTimerFunc(300,Timer,0);
}
 
int main(int argc, char** argv)
{
    srand(time(0));
    zm[0].x = 0.0;
    zm[0].y = 0.0;
    f.Create();
    //Initialization
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(w, h);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Snake");
    gluOrtho2D(0,20,0,20);
    //Registration
    glutDisplayFunc(displayMe);
    glutTimerFunc(300,Timer,0);
    glutSpecialFunc(SKeyboard);
    glutMainLoop();
    return 0;
}
