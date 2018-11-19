#include <GL/glut.h>
#include <string.h>

class Circle{
public:
        float x,y,r,alpha;
        Circle(float _x=0,float _y=0,float _r=10):x(_x),y(_y),r(_r) ,alpha(1.0)       
};

void displayMe(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();
}

void Timer(int){
        
        glutPostRedisplay();
        glutTimerFunc(50,Timer,0);
}

void Timer2(int){
        
        glutPostRedisplay();
        glutTimerFunc(1000,Timer2,0);
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
    glutTimerFunc(50,Timer,0);
    glutTimerFunc(1000,Timer2,0);
    glutKeyboardFunc(Keyboard);
    glutSpecialFunc(SKeyboard);
    glutMainLoop();
    return 0;
}
