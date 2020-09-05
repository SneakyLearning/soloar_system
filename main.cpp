#include <GL/glut.h>
#include "solor_system.h"

#define WINDOW_X_POS 50
#define WINDOW_Y_POS 50
#define WIDTH 700
#define HEIGHT 700

SolorSystem solorsystem;

void onDisplay(void) {
    solorsystem.onDisplay();
}
void onUpdate(void) {
    solorsystem.onUpdate();
}
void onKeyboard(unsigned char key, int x, int y) {
    solorsystem.onKeyboard(key, x, y);
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowPosition(WINDOW_X_POS, WINDOW_Y_POS);
    glutCreateWindow("SolarSystem at Shiyanlou");
    
	glutDisplayFunc(onDisplay);
    glutIdleFunc(onUpdate);
    glutKeyboardFunc(onKeyboard);
    //三个重要的回调函数

	glutMainLoop();
    return 0;
}