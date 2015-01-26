#include "Globals.h"
#include "cGame.h"
#include <iostream>
cGame Game;

using namespace std;
struct A{};

void AppRender() {
	Game.Render();
}
void AppKeyboard(unsigned char key, int x, int y) {
	Game.ReadKeyboard(key, x, y, true);
}
void AppKeyboardUp(unsigned char key, int x, int y) {
	Game.ReadKeyboardUp(key, x, y, false);
}

void AppSpecialKeys(int key, int x, int y) {
	Game.ReadKeyboard(key, x, y, true);
}
void AppSpecialKeysUp(int key, int x, int y) {
	Game.ReadSpecialKeyboard(key, x, y, false);
}
void AppMouse(int button, int state, int x, int y) {
	Game.ReadMouse(button, state, x, y);
}
void AppIdle() {
	if (!Game.Loop()) exit(0);
}
void TimerFunction(int n)
{
	n--;
	std::cout << Game.GetTime() << " \n";

	if (n > 0){
		glutTimerFunc(1000, TimerFunction, n);
		Game.SetTime((float) n);
		
	}
	else{
		//glutTimerFunc(1, cGame::DrawGameOver, n);
		std::cout << "FINAL !!!!! \n";
		
		
	}

}

void LOG(char* s){

	cout << s << typeid(Game).name() << "\n";
	
	 
}

void menuapp(int value)
{
	if (value == 1) glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (value == 2) exit(0);
}
void main(int argc, char** argv)
{
	int res_x, res_y, pos_x, pos_y;

	//GLUT initialization
	glutInit(&argc, argv);
	LOG("GLUT iniciado");

	
	//RGBA with double buffer
	glutInitDisplayMode(GLUT_RGBA | GLUT_ALPHA | GLUT_DOUBLE);

	//Create centered window
	res_x = glutGet(GLUT_SCREEN_WIDTH);
	res_y = glutGet(GLUT_SCREEN_HEIGHT);
	pos_x = (res_x >> 1) - (GAME_WIDTH >> 1);
	pos_y = (res_y >> 1) - (GAME_HEIGHT >> 1);

	glutInitWindowPosition(pos_x, pos_y);
	glutInitWindowSize(GAME_WIDTH, GAME_HEIGHT);
	glutCreateWindow("My GLUT Application!");
	//glutFullScreen();

	glutCreateMenu(menuapp);
	glutAddMenuEntry("Borrar Pantalla", 1);
	glutAddMenuEntry("Salir", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	
	/*glutGameModeString("800x600:32");
	glutEnterGameMode();*/

	//Make the default cursor disappear
	//glutSetCursor(GLUT_CURSOR_NONE);

	//Register callback functions
	glutDisplayFunc(AppRender);
	glutKeyboardFunc(AppKeyboard);
	glutKeyboardUpFunc(AppKeyboardUp);
	glutSpecialFunc(AppSpecialKeys);
	glutSpecialUpFunc(AppSpecialKeysUp);
	glutMouseFunc(AppMouse);
	glutIdleFunc(AppIdle);

	//Game initializations
	Game.Init();
	glutTimerFunc(1000, TimerFunction, 5);
	//Application loop
	glutMainLoop();

	//return 0;
}
