#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>
#include"oceloboard.h"
#include"object.h"
#include"mouse.h"
#include"scenemanager.h"

#define WIDTH 640
#define HEIGHT 640

void Display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);

  DrawAllObject();

  glutSwapBuffers();
}

void Resize(int w, int h) {
  glViewport(0, 0, w, h);
  glLoadIdentity();
  glOrtho(0, WIDTH, HEIGHT, 0, -300.0, 300.0);
}

void Idle() {
  static int timestd = 1000 / 60;
  int timenow;

  timenow = glutGet(GLUT_ELAPSED_TIME);

  if(timenow > timestd) {
    timestd = timenow + (1000 / 60);
    
    ControlGameWithState();
    UpdateAllObject();

    glutPostRedisplay();
  }
}

void init(int argc, char **argv) {
  glClearColor(0, 0.7, 0, 1);
  if(!SetSocket(argv)) exit(1);
}

int main(int argc, char **argv) {
  if(argc < 3) {
    fprintf(stderr, "write host and port\n");
    exit(1);
  }

  glutInit(&argc, argv);
  glutInitWindowSize(WIDTH, HEIGHT);
  glutInitWindowPosition(100, 100);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
  glutCreateWindow(argv[0]);
  glutDisplayFunc(Display);
  glutReshapeFunc(Resize);
  glutMouseFunc(Mouse);
  glutIdleFunc(Idle);
  init(argc, argv);

  glutMainLoop();

  return 0;
}