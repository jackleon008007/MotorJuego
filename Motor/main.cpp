#include <SDL/SDL.h>
#include "MainGame.h"
#include <time.h>

int main(int argc, char** argv) {
	srand(time(NULL));
	MainGame mainGame;
	mainGame.run();
	system("PAUSE");


	return 0;
}