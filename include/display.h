#ifndef __DISPLAY_H
#define __DISPLAY_H

#include <GL/glut.h>
#include <math.h>

enum MODE{KMEANS,HIERARCHY,DBSCAN,DEFAULT};
extern int mode;

void InitGL();
void InitMenu();
void DisplayFunc();

void KeyboardFunc(unsigned char ch, int x, int y);
void MouseFunc(int button, int state, int x, int y);
void MotionFunc(int x, int y);
void MenuCallback(int value);
void ReshapeFunc(int width, int height);
void MotionFunc(int x, int y);
void SetBoundaryBox(float a[3],float b[3]);

void DrawKmeans();
void DrawHierarchy();
void DrawDbscan();


#endif
