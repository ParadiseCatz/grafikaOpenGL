//headers
#include</Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.12.sdk/System/Library/Frameworks/OpenGL.framework/Headers/gl.h>
#include</Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.12.sdk/System/Library/Frameworks/GLUT.framework/Headers/glut.h>
#include<stdio.h>
#include <cstdlib>
//globals
GLuint elephant;
float elephantrot;
char ch='1';
//other functions and main
//wavefront .obj loader code begins


void loadObj(char *fname)
{
    FILE *fp;
    int read;
    GLfloat x, y, z;
    char ch;
    elephant=glGenLists(1);
    fp=fopen(fname,"r");
    if (!fp)
    {
        printf("can't open file %s\n", fname);
        exit(1);
    }
    glPointSize(2.0);
    glNewList(elephant, GL_COMPILE);
    {
        glPushMatrix();
        glBegin(GL_POLYGON);
        glVertex3f(315.2,548.3, -5.0f);
        glVertex3f(392,545.9, -5.0f);
        glVertex3f(394.6,603.2, -5.0f);
//        glVertex3f(409.9,551.2, -5.0f);
        glVertex3f(393.9,545.2, -5.0f);
        glVertex3f(427.7,542.7, -5.0f);
        glVertex3f(543.4,522.1, -5.0f);
        glVertex3f(579.8,482.1, -5.0f);
        glVertex3f(508.5,505.8, -5.0f);
        glVertex3f(529.6,516.1, -5.0f);
        glVertex3f(430.4,499.2, -5.0f);
        glVertex3f(430.6,480.3, -5.0f);
        glVertex3f(457.4,401.7, -5.0f);
        glVertex3f(520,342.8, -5.0f);
        glVertex3f(373.8,338.4, -5.0f);
        glVertex3f(347.3,437.7, -5.0f);
        glVertex3f(296.4,349.9, -5.0f);
        glVertex3f(274.9,361.2, -5.0f);
        glVertex3f(262.3,437.4, -5.0f);
//        glVertex3f(279.8,462.5, -5.0f);
        glVertex3f(329.5,500.7, -5.0f);
        glVertex3f(185.4,500.2, -5.0f);
        glVertex3f(188.4,471.9, -5.0f);
        glVertex3f(171.2,503.7, -5.0f);
        glVertex3f(152.2,481.7, -5.0f);
        glVertex3f(156.1,509.7, -5.0f);
        glVertex3f(139.4,525.3, -5.0f);
        glVertex3f(163,531.6, -5.0f);
        glVertex3f(151.5,549, -5.0f);
        glVertex3f(189.6,537, -5.0f);
        glVertex3f(303.1,548.5, -5.0f);
        glVertex3f(312.7,587.3, -5.0f);
        glVertex3f(325.9,553.3, -5.0f);
        glEnd();
    }
    glPopMatrix();
    glEndList();
    fclose(fp);
}
//wavefront .obj loader code ends here
void reshape(int w,int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective (60, (GLfloat)w / (GLfloat)h, 0.1, 1000.0);
    //glOrtho(-25,25,-2,2,0.1,100);
    glMatrixMode(GL_MODELVIEW);
}
void drawElephant()
{
    glPushMatrix();
    glTranslatef(-60,80.00,-105);
    glColor3f(1.0,0.23,0.27);
    glScalef(0.2,0.2,0.2);
//    glRotatef(elephantrot,0,1,0);
    glRotatef(180,1,0,0);
    glCallList(elephant);
    glPopMatrix();
    elephantrot=elephantrot+0.6;
    if(elephantrot>360)elephantrot=elephantrot-360;
}
void display(void)
{
    glClearColor (0.0,0.0,0.0,1.0);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    drawElephant();
    glutSwapBuffers(); //swap the buffers
}
int main(int argc,char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(800,600);
    glutInitWindowPosition(20,20);
    glutCreateWindow("ObjLoader");
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    loadObj("/Users/anthony/Swift/TEST/Grafika/Grafika/dragon.obj");//replace elepham.obj withp orsche.obj or radar.obj or any other .obj to display it
    glutMainLoop();
    return 0;
}
