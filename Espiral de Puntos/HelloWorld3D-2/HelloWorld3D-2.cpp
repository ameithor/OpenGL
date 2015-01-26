// HelloWorld3D.cpp: define el punto de entrada de la aplicación de consola.
//

#include "Globals.h"
#include "cGame.h"

cGame Game;

void AppRender() {
	Game.Render();
}
void AppKeyboard(unsigned char key, int x, int y) {
	Game.ReadKeyboard(key, x, y, true);
}
void AppKeyboardUp(unsigned char key, int x, int y) {
	Game.ReadKeyboard(key, x, y, false);
}

void AppSpecialKeys(int key, int x, int y) {
	Game.ReadKeyboard(key, x, y, true);
}
void AppSpecialKeysUp(int key, int x, int y) {
	Game.ReadKeyboard(key, x, y, false);
}
void AppMouse(int button, int state, int x, int y) {
	Game.ReadMouse(button, state, x, y);
}
void AppIdle() {
	if (!Game.Loop()) exit(0);
}


using namespace std;

void main(int argc, char** argv)
{
	std::cout << "Hello World!" << std::endl;

	GLsizei w = 100;
	GLsizei h = 100;
	GLfloat nRange = 100.0f;

	if (h == 0) h = 1;
	glViewport(0, 0, w, h);

	//GLUT initialization
	glutInit(&argc, argv);


	//RGBA with double buffer
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(GAME_Xo, GAME_Yo);
	glutInitWindowSize(GAME_WIDTH, GAME_HEIGHT);
	glutCreateWindow("My Game");

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w <= h)
		glOrtho(-nRange, nRange, -nRange*h / w, nRange*h / w, -nRange, nRange);
	else
		glOrtho(-nRange*w / h, nRange*w / h, -nRange, nRange, -nRange, nRange);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//Register callback functions
	glutDisplayFunc(AppRender);
	glutKeyboardFunc(AppKeyboard);
	glutKeyboardUpFunc(AppKeyboardUp);
	glutSpecialFunc(AppSpecialKeys);
	glutSpecialUpFunc(AppSpecialKeysUp);
	glutIdleFunc(AppIdle);
	//Game initializations
	Game.Init();
	//Application loop
	glutMainLoop();


}
