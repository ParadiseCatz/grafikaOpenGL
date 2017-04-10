//headers
#include</Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.12.sdk/System/Library/Frameworks/OpenGL.framework/Headers/gl.h>
#include</Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.12.sdk/System/Library/Frameworks/GLUT.framework/Headers/glut.h>
#include<stdio.h>
#include <cstdlib>
#include <vector>
//globals
GLuint elephant;
float elephantrot;
char ch='1';
//other functions and main
//wavefront .obj loader code begins

std::vector<GLfloat> vertices;

// This is the identifier for your vertex buffer
GLuint vbo;
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
        glBegin(GL_POINTS);
        while(!(feof(fp)))
        {
            read=fscanf(fp,"%c %f %f %f",&ch,&x,&y,&z);
            if(read==4&&ch=='v')
            {
                glVertex3f(x,y,z);
                vertices.push_back(x);
                vertices.push_back(y);
                vertices.push_back(z);
                vertices.push_back(1.0);
                
            }
        }
        glEnd();
    }

    // This creates our identifier and puts it in vbo
    glGenBuffers(1, &vbo);
    // This binds our vbo
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // This hands the vertices into the vbo and to the rendering pipeline
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
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
    glTranslatef(0,-40.00,-105);
    glColor3f(1.0,0.23,0.27);
    glScalef(10,10,10);
    glRotatef(elephantrot,0,1,0);
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
    // "Enable a port" to the shader pipeline
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // pass information about how vertex array is composed
    glVertexAttribPointer(0, // same as in glEnableVertexAttribArray(0)
                          4, // # of coordinates that build a vertex
                          GL_FLOAT, // data type
                          GL_FALSE, // normalized?
                          0,        // stride
                          (void*)0);// vbo offset
    
    glDrawArrays(GL_LINES, 0, 2);
    glDisableVertexAttribArray(0);
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
