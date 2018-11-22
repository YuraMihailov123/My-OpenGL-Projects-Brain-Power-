#include <GL/glut.h>
#include <string.h>
#include <iostream>
#include "../SnakeGame/AdditionalFunc.h"
using namespace std;

class Shapes{
public:
        int r=3,c=3;
        int aCount;
        int a[3][3];
        int a1[3][3]={
        {0,1,0},
        {1,1,1},
        {0,0,0}
        };
        int a2[3][3]={
        {2,2,0},
        {2,2,0},
        {0,0,0}
        };
        int a3[3][3]={
        {0,0,3},
        {3,3,3},
        {0,0,0}
        };
        int a4[4][4]={
        {0,0,0,0},
        {4,4,4,4},
        {0,0,0,0},
        {0,0,0,0}
        };
        int length;
        int dir=0;
        int x,y;//x=3;y=19
        void drawShape();
        void Merge();
        void Drop();
        bool Collide();
        void CopyMap();
        void SaveMap();
        void CollideSides();
        void HorFix(int _dir);
        void RandomizeCount();
        void RotateShape();
        void CopyShape();
        void _Merge();
};

Shapes s;
int n=10,m=20;
int map[20][10];
int mapRes[20][10];
int score=0;
char buff[100];
char name[100]="<Tetris> Score: ";
char nameRes[100]="<Tetris> Score: ";
int tempShape[3][3];

/////////////////////////////////////////////////////////////////////
void Shapes::RotateShape(){
        this->CopyShape();
        for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                        this->a[i][j]=tempShape[j][i];
                        cout << this->a[i][j]<<"=";
                }
                cout << endl;
        } 
        cout << endl;
        this->_Merge();       
}

void Shapes::CopyShape(){
        for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                        tempShape[i][j]=this->a[i][j];
                        cout << this->a[i][j]<<"+";
                }
                cout << endl;
        }    
        cout << endl;
}

void Shapes::_Merge(){
        int x1=0,y1=0;
        for(int i=s.y;i<s.y+3;i++){
        
        for(int j=s.x;j<s.x+3;j++){
                //if(i>m-4 && j<3){
                map[i][j]=0;
                map[i][j]=this->a[x1][y1];
                cout << y1<<"-";
                //}
                y1++;
        }
        y1=0;
        cout << endl;
        x1++;
        cout << x1;
        }
        cout << endl;
}
////////////////////////////////////////////////////////////////////////
void Shapes::RandomizeCount(){
        this->aCount = rand() % 3+1;
        switch(this->aCount){
                case 1:
                for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                       a[i][j]=a1[i][j];
                }
                }     
                this->length=3;
                break;
                 case 2:
                for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                       a[i][j]=a2[i][j];
                }
                }     
                this->length=2;
                break;
                 case 3:
                for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                       a[i][j]=a3[i][j];
                }
                }     
                this->length=3;
                break;
                 case 4:
                for(int i=0;i<4;i++){
                for(int j=0;j<4;j++){
                       a[i][j]=a3[i][j];
                }
                }     
                this->length=4;
                break;
        }
}

void RemoveLine(){
      int count=0; 
      int index=0; 
      for(int i=0;i<m;i++){
              
              index=i;
              count=0;
              for(int j=0;j<n;j++){
                        
                        if(map[i][j]!=0){count++;                         
                        }
                        
              }
              
              if(count==n){
                for(int k=index;k<m-1;k++){
                        for(int l=0;l<n;l++){
                                map[k][l]=map[k+1][l];
                        }
                }
                for(int k=m-1;k<=m-1;k++){
                        for(int l=0;l<n;l++){
                                map[k][l]=0;
                        }
                }
                score+=10;
              }
      }        
      
}

void Shapes::SaveMap(){
        for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
        if(map[i][j]==1 || map[i][j]==3|| map[i][j]==2) map[i][j]=9;
        }       
        }
}


bool Shapes::Collide(){
     //
     

     for(int i=s.y-1;i<=s.y-1;i++){
        for(int j=s.x;j<s.x+s.length;j++){
                
                if(map[i][j]==9){
                        s.RandomizeCount();
                        s.SaveMap();
                        RemoveLine();
                        s.Merge();
                        return false;
                }
        }
       
      }
                
     if(s.y<=1 ){
     s.RandomizeCount();
     s.SaveMap();
     RemoveLine();
     s.Merge();
     return false;                                   
     }
     
     
     return true;
}

void Shapes::Merge(){
     
     for(int i=m-1;i>0;i--){
        for(int j=0;j<n;j++){
                if(i>m-4 && j<3){
                map[i][j]=s.a[m-1-i][j];
                //cout << s.a[m-i][j]<<"";
                }
        }
        //
     } 
     s.y = 18;
     s.x=0;
    
}

void Shapes::Drop(){
     for(int i=0;i<m;i++){
       for(int j=0;j<n;j++){              
                if(map[i][j]!=0 && map[i][j]!=9 && s.y>1 && s.Collide()){
                        int temp= map[i][j];
                        map[i][j]=0;
                        map[i-1][j+dir*1]=temp;    
                                          
                }              
       }       
     }  
     if(s.Collide())
     s.y--;
     s.x+=dir*1; 
     s.dir=0;    
}



void Shapes::drawShape(){
     
     
     for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
                if(map[i][j]==1){
                        glColor3f(1.0f,0.0f,0.0f); 
                        glRectf(j,i,j+1,i-1);    
                        }       
                if(map[i][j]==2 ){
                        glColor3f(0.0f,1.0f,0.0f); 
                        glRectf(j,i,j+1,i-1);    
                        }  
                if(map[i][j]==3){
                        glColor3f(0.0f,0.0f,1.0f); 
                        glRectf(j,i,j+1,i-1);    
                        }      
                 if( map[i][j]==9){
                        glColor3f(0.1f,0.5f,0.5f); 
                        glRectf(j,i,j+1,i-1);    
                        }                                                  
        }        
     }
}

void displayMe(void)
{
    glPushMatrix();
 
    glClear(GL_COLOR_BUFFER_BIT);
    s.drawShape(); 
    
    
    
    glColor3f(0.5f,0.5f,1.0f);  
    glBegin(GL_LINES);
        for(float i=0;i<=100.0;i+=10.0){
               glVertex2f(i/10, 0);
               glVertex2f(i/10, 20);
        }
        for(float i=0;i<=200.0;i+=10.0){
               glVertex2f(0,i/10);
               glVertex2f(20,i/10);
        }
    glEnd();
    glutSetWindowTitle(strcat(name,itoa(score,buff,10)));
    glPopMatrix();
    glutSwapBuffers();
}

void SKeyboard(int key, int x,int y)
{
        switch(key){
                case GLUT_KEY_LEFT: if(s.x>0 /* check for collide with other shapes*/)s.dir=-1;
                        break;
                case GLUT_KEY_RIGHT:if(s.x+s.length<n /*checkforcollidewithshapes*/)s.dir=1;
                        break;     
                case GLUT_KEY_UP: s.RotateShape();
                        break;    
                case GLUT_KEY_DOWN: //dirX=0;dirY=-1;
                        break;                           
        }
}


void Timer(int){
        s.Drop();
        strcpy(name,nameRes);
        glutPostRedisplay();
        glutTimerFunc(1000,Timer,0);
}
 
int main(int argc, char** argv)
{
    srand(time(0));
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
               map[i][j]=0;
               mapRes[i][j]=0;
        }
     }
     
     cout << endl;
     s.RandomizeCount();
     s.y=20;
     s.x=4;
     s.Merge();
    //Initialization
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(200, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("First Step");
    //Registration
    glutDisplayFunc(displayMe);
    glutTimerFunc(1000,Timer,0);
    gluOrtho2D(0,10,0,20);
    glutSpecialFunc(SKeyboard);
    glutMainLoop();
    return 0;
}
