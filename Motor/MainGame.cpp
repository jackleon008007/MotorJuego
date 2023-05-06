#include "MainGame.h"
#include "Error.h"
#include "Sprite.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;






MainGame::MainGame() {
	window = nullptr;
	width = 1000;
	height = 800;
	gameState = GameState::PLAY;
	time = 0;
}

MainGame::~MainGame() {

}

void MainGame::initShaders() {
	program.compileShaders("Shaders/colorShaderVert.txt", "Shaders/colorShaderFrag.txt");
	program.addAtribute("vertexPosition");
	program.addAtribute("vertexColor");
	program.linkShader();


}

void MainGame::init() {
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("HOLA", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);

	if (window == nullptr) {
		fatalError("SDL not initialized");
	}
	SDL_GLContext glContext = SDL_GL_CreateContext(window);
	GLenum error = glewInit();
	if (error != GLEW_OK) {
		fatalError("Glew not initialized");
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	//para dar color la pantalla
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	initShaders();

}

void MainGame::draw() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	program.use();
	GLuint timeLocation = program.getUniformLocation("time");
	glUniform1f(timeLocation, time);
	time += 0.0002;
	//sprite.draw();
	for (int i = 0; i < listSprite.size(); ++i) {
		listSprite[i].draw();
	
	}
	//sprite2.draw();
	program.unuse();
	// SI TENGO ELEMENTOS ACTUALIZO
	SDL_GL_SwapWindow(window);


}

void MainGame::processInput() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type)
		{
		case SDL_QUIT:
			gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			cout << event.motion.x << " , " << event.motion.y << endl;
			break;

		}
	}
}

void MainGame::run() {
	init();

	//sprite.init(0.2, 0.2, 1, 1);
	//sprite2.init(1, 1, -1, -1);

	update();

}


void MainGame::addRandomSprite() {
	float randomPosx = rand() % 100;
	randomPosx = randomPosx / 100;

	float randomPosy = rand() % 100;
	randomPosy = randomPosy / 100;


	listSprite.push_back(Sprite());
	listSprite[listSprite.size() - 1].init(randomPosx, randomPosy, -1, -1);
}
void MainGame::update() {
	int timer = 0;

	while (gameState != GameState::EXIT) {
		draw();
		processInput();
		timer++;
		if (timer>500) {
			addRandomSprite();
			timer = 0;
		}
		
	}
}

