#include <GL/glut.h>
#include <string.h>

int _angle=0;
float y1=0.0,y2=0.5,y3=0.0,y4=-0.5; 
char _buff[5];
char _title[12]="Angle: ";
char _titleRes[12]="Angle: ";

char* itoa(int value, char* result, int base) {
		// check that the base if valid
		if (base < 2 || base > 36) { *result = '\0'; return result; }

		char* ptr = result, *ptr1 = result, tmp_char;
		int tmp_value;

		do {
			tmp_value = value;
			value /= base;
			*ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
		} while ( value );

		// Apply negative sign
		if (tmp_value < 0) *ptr++ = '-';
		*ptr-- = '\0';
		while(ptr1 < ptr) {
			tmp_char = *ptr;
			*ptr--= *ptr1;
			*ptr1++ = tmp_char;
		}
		return result;
	}

void displayMe(void)
{
    glPushMatrix();
    _angle%=360;
    glClear(GL_COLOR_BUFFER_BIT);
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
        //glVertex2f(0.5, y3);
        //glVertex2f(0.0, y4);
        //glVertex2f(1.5, 0.0);
        //glVertex2f(0.0,1.0);
    glEnd();
    strcpy(_title,_titleRes);
    glutSetWindowTitle(strcat(_title,itoa(_angle,_buff,10)));
    glPopMatrix();
    glutSwapBuffers();
}

void Keyboard(unsigned char key, int x,int y)
{
        switch(key){
                case 'a': _angle++;
                        break;
                case 'd': _angle--;
                        break;        
        }
}

void SKeyboard(int key, int x,int y)
{
        switch(key){
                case GLUT_KEY_LEFT: _angle++;
                        break;
                case GLUT_KEY_RIGHT: _angle--;
                        break;     
                case GLUT_KEY_UP: y1=y1+0.1; y2=y2+0.1; y3=y3+0.1; y4=y4+0.1;
                        break;    
                case GLUT_KEY_DOWN: y1=y1-0.1; y2=y2-0.1; y3=y3-0.1; y4=y4-0.1;
                        break;                           
        }
}

void Timer(int){
        
        glutPostRedisplay();
        glutTimerFunc(50,Timer,0);
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
    glutKeyboardFunc(Keyboard);
    glutSpecialFunc(SKeyboard);
    glutMainLoop();
    return 0;
}
