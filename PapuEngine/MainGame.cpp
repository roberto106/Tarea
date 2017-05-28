#include "MainGame.h"
#include "Sprite.h"
#include "ImageLoader.h"
#include <iostream>
#include <time.h>
using namespace std;
int a=50;
int x,y;
int c = 0;

void MainGame::run() {
	init();
	srand(time(NULL));

	_sprites.push_back(new Sprite());
	_sprites.back()->init(-1, -1, 1, 1, "Textures/mario.png");

	_sprites.push_back(new Sprite());
	_sprites.back()->init(0, -1, 1, 1, "Textures/mario2.png");

	_sprites.push_back(new Sprite());
	_sprites.back()->init(0, 0, 1, 1, "Textures/mario3.png");
	
	_sprites.push_back(new Sprite());
	_sprites.back()->init(-1, 0, 1, 1, "Textures/mario4.png");

	for (int i = 0; i < 15; i++)
	{
		x = -1 + rand() % 2;
		y = -1 + rand() % 2;
		_sprites.push_back(new Sprite());
		_sprites.back()->init(x, y, 1, 1, "Textures/mario.png");

	
		x = -1 + rand() % 2;
		y = -1 + rand() % 2;
		_sprites.push_back(new Sprite());
		_sprites.back()->init(x, y, 1, 1, "Textures/mario2.png");

		x = -1 + rand() % 2;
		y = -1 + rand() % 2;
		_sprites.push_back(new Sprite());
		_sprites.back()->init(x, y, 1, 1, "Textures/mario3.png");

		x = -1 + rand() % 2;
		y = -1 + rand() % 2;
		_sprites.push_back(new Sprite());
		_sprites.back()->init(x, y, 1, 1, "Textures/mario4.png");

	}
		

		

	
	



	//_texture = ImageLoader::loadPNG("Textures/mario.png");
	update();
}
void MainGame::init() {

	SDL_Init(SDL_INIT_EVERYTHING);
	_window = SDL_CreateWindow("Papu engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _witdh, _height, SDL_WINDOW_OPENGL);
	if (_window == nullptr) {
	}

	SDL_GLContext glContext = SDL_GL_CreateContext(_window);
	
	GLenum error = glewInit();
	if (error != GLEW_OK) {

	}
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	initShaders();
}

void MainGame::initShaders() {
	_program.compileShaders("Shaders/colorShaderVert.txt",
		"Shaders/colorShaderFrag.txt");
	_program.addAtribute("vertexPosition");
	_program.addAtribute("vertexColor");
	_program.addAtribute("vertexUV");

	_program.linkShader();
}


void MainGame::draw() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_program.use();
	//que texturas se activan
	glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, _texture.id);
	
	GLuint imageLocation = _program.getUniformLocation("myImage");
	glUniform1i(imageLocation, 0);
	
	GLuint timeLocation = 
		_program.getUniformLocation("time");
		
	glUniform1f(timeLocation,_time);
	
	_time+=0.5;
	
	
	
	if (c > _sprites.size()-1)
		c = 4;
	if (_time>a)
	{
		a = a + 100;
		c++;
	}
	for (int i = 0; i < c; i++)
	{
		_sprites[i]->draw();

	}
	_program.unuse();
	SDL_GL_SwapWindow(_window);
}

void MainGame::procesInput() {
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				_gameState = GameState::EXIT;
				break;
			case SDL_MOUSEMOTION:
			break;
		}
	}

}

void MainGame::update() {

	while (_gameState != GameState::EXIT) {
		procesInput();
		draw();
		
	}
}


MainGame::MainGame(): _window(nullptr), 
					  _witdh(800),
					  _height(600),
					  _gameState(GameState::PLAY),
					  _time(0)
{

}


MainGame::~MainGame()
{
}
