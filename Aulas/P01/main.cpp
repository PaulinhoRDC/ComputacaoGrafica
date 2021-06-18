#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION    // foi necess�rio para "tirar" os warnings no mac
#include <GLUT/glut.h>
#else
#include <OpenGL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>


void changeSize(int w, int h)
{
    // Prevent a divide by zero, when window is too short
    // (you can't make a window with zero width).
    if (h == 0)
        h = 1;
    // compute window's aspect ratio
    float ratio = w * 1.0f / h;
    // Set the projection matrix as current
    glMatrixMode(GL_PROJECTION);
    // Load the identity matrix
    glLoadIdentity();
    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);
    // Set the perspective
    gluPerspective(45.0f, ratio, 1.0f, 1000.0f);
    // return to the model view matrix mode
    glMatrixMode(GL_MODELVIEW);
}

float size;

void renderScene(void)
{
    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set camera
    glLoadIdentity();
    gluLookAt(0.0f, 0.0f, 5.0f,
              0.0f, 0.0f, -1.0f,
              0.0f, 1.0f, 0.0f);

    // put drawing instructions here
    glutWireTeapot(size);

    // End of frame
    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y){
    switch(key){
        case 27:
            exit(0);
            break;
        case '+':
            size += 0.1f;
            break;
        case '-':
            size -= 0.1f;
            break;
        case 'a':
            size -= 0.1f;
            break;
        case 's':
            size -= 1;
            break;
        case 'd':
            size += 0.1f;
            break;
        case 'w':
            size += 1;
            break;
    }
}
void printInfo() {

    printf("Vendor: %s\n", glGetString(GL_VENDOR));
    printf("Renderer: %s\n", glGetString(GL_RENDERER));
    printf("Version: %s\n", glGetString(GL_VERSION));
}


int main(int argc, char** argv)
{
    // put GLUT�s init here
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 800);
    glutCreateWindow("CG@DI");

    // put callback registry here
    glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene);
    glutDisplayFunc(renderScene);

    // some OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glutKeyboardFunc(keyboard);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);


    // enter GLUT�s main cycle
    glutMainLoop();

    return 1;
}


