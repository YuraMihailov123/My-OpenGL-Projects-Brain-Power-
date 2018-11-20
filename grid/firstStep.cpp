#include <GL/glut.h>
#include <string.h>

int _angle=0;
float y1=0.0,y2=0.1,y3=0.1,y4=0.0; 
float x1=-0.1,x2=-0.1,x3=0.0,x4=0.0; 
char _buff[5];
char _title[12]="Angle: ";
char _titleRes[12]="Angle: ";
int dirX=1,dirY=0;


void displayMe(void)
{
    glPushMatrix();
    _angle%=360;
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f,0.0f,0.0f); 
    
    glBegin(GL_POLYGON);
    for(int i=0;i<4;i++){    
    glVertex2f(x1-0.1*i, y1);
    glVertex2f(x2-0.1*i, y2);
    glVertex2f(x3-0.1*i,y3);  
    glVertex2f(x4-0.1*i,y4);
    }
       
    glEnd();
    
    glColor3f(0.5f,0.5f,1.0f);  
    glRotatef(_angle,0.0,0.0,2.0);
    glBegin(GL_LINES);
        for(float i=-200.0;i<=200.0;i+=20.0){
               glVertex2f(i/200, -1);
               glVertex2f(i/200, 1);
        }
        for(float i=-200.0;i<=200.0;i+=20.0){
               glVertex2f(-1,i/200);
               glVertex2f(1,i/200);
        }
    glEnd();
    glPopMatrix();
    glutSwapBuffers();
}

void Keyboard(unsigned char key, int x,int y)
{
        /*switch(key){
                case 'a': _angle++;
                        break;
                case 'd': _angle--;
                        break;        
        }*/
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

void Move(int dirX,int dirY){
        x1=x1+dirX*0.1; x2=x2+dirX*0.1; x3=x3+dirX*0.1; x4=x4+dirX*0.1;
        y1=y1+dirY*0.1; y2=y2+dirY*0.1; y3=y3+dirY*0.1; y4=y4+dirY*0.1;
}

void Timer(int){
        Move(dirX,dirY);
        glutPostRedisplay();
        glutTimerFunc(500,Timer,0);
}
 
int main(int argc, char** argv)
{
    //Initialization
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("First Step");
    //Registration
    glutDisplayFunc(displayMe);
    glutTimerFunc(500,Timer,0);
    glutKeyboardFunc(Keyboard);
    glutSpecialFunc(SKeyboard);
    glutMainLoop();
    return 0;
}
