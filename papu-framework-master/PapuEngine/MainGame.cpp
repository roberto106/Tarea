#include "MainGame.h"
#include "ImageLoader.h"
#include <iostream>
#include "ResourceManager.h"
#include "PapuEngine.h"


using namespace std;
int bala = 0;
void MainGame::run() {
	init();
	update();
}

void MainGame::init() {
	Papu::init();
	_window.create("Engine", _witdh, _height, 0);
	glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
	initLevel();
	initShaders();

}

void MainGame::initLevel() {
	_levels.push_back(new Level("Levels/level1.txt"));
	_player = new Player();
	_currenLevel = 0;
	_player->init(1.0f, _levels[_currenLevel]->getPlayerPosition(), &_inputManager);
	_humans.push_back(_player);
	_spriteBacth.init();
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

	glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, _texture.id);

	/*GLuint timeLocation = 
		_program.getUniformLocation("time");

	glUniform1f(timeLocation,_time);*/

	GLuint pLocation =
		_program.getUniformLocation("P");

	glm::mat4 cameraMatrix = _camera.getCameraMatrix();
	glUniformMatrix4fv(pLocation, 1,GL_FALSE, &(cameraMatrix[0][0]));

	GLuint imageLocation = _program.getUniformLocation("myImage");
	glUniform1i(imageLocation, 0);

	_spriteBacth.begin();
	_levels[_currenLevel]->draw();

	for (int i = 0; i < _humans.size(); i++)
	{
		_humans[i]->draw(_spriteBacth);
	}
	if (bala == 0)
	for (int i = 0; i < _bullets.size(); i++)
	{
		_bullets[i].draw(_spriteBacth);
	}
	if (bala == 1)
		for (int i = 0; i < _bullets1.size(); i++)
		{
			_bullets1[i].draw1(_spriteBacth);
		}
	else if (bala == 2)
		for (int i = 0; i < _bullets2.size(); i++)
		{
			_bullets2[i].draw2(_spriteBacth);
		}
	else if (bala == 3)
		for (int i = 0; i < _bullets3.size(); i++)
		{
			_bullets3[i].draw3(_spriteBacth);
		}
	_spriteBacth.end();
	_spriteBacth.renderBatch();

	glBindTexture(GL_TEXTURE_2D, 0);

	_program.unuse();
	_window.swapBuffer();
}

void MainGame::procesInput() {
	SDL_Event event;
	const float CAMERA_SPEED = 1.0f;
	const float SCALE_SPEED = 0.1f;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				_gameState = GameState::EXIT;
				break;
			case SDL_MOUSEMOTION:
				_inputManager.setMouseCoords(event.motion.x,event.motion.y);
			break;
			case  SDL_KEYUP:
				_inputManager.releaseKey(event.key.keysym.sym);
				break;
			case  SDL_KEYDOWN:
				_inputManager.pressKey(event.key.keysym.sym);
				break;
			case SDL_MOUSEBUTTONDOWN:
				_inputManager.pressKey(event.button.button);
				break;
			case SDL_MOUSEBUTTONUP:
				_inputManager.releaseKey(event.button.button);
				break;
		}

		/*if (_inputManager.isKeyPressed(SDLK_w)) {
			_camera.setPosition(_camera.getPosition() + glm::vec2(0.0, CAMERA_SPEED));
		}
		if (_inputManager.isKeyPressed(SDLK_s)) {
			_camera.setPosition(_camera.getPosition() + glm::vec2(0.0, -CAMERA_SPEED));
		}
		if (_inputManager.isKeyPressed(SDLK_a)) {
			_camera.setPosition(_camera.getPosition() + glm::vec2(-CAMERA_SPEED, 0.0));
		}
		if (_inputManager.isKeyPressed(SDLK_d)) {
			_camera.setPosition(_camera.getPosition() + glm::vec2(CAMERA_SPEED, 0.0));
		}*/
		if (_inputManager.isKeyPressed(SDLK_q)) {
			_camera.setScale(_camera.getScale() + SCALE_SPEED);
		}
		if (_inputManager.isKeyPressed(SDLK_e)) {
			_camera.setScale(_camera.getScale() - SCALE_SPEED);
		}
		if (_inputManager.isKeyPressed(SDL_BUTTON_LEFT)) {
			bala = 0;
			glm::vec2 mouseCoords =  _camera.convertScreenToWorl(_inputManager.getMouseCoords());

			glm::vec2 playerPosition(_player->getPosition());

			glm::vec2 direction = mouseCoords - playerPosition;
			direction = glm::normalize(direction);
			_bullets.emplace_back(playerPosition, direction, 0.5f,1000);
		}
		if (_inputManager.isKeyPressed(SDLK_u)) {
			bala = 1;
			glm::vec2 mouseCoords = _camera.convertScreenToWorl(_inputManager.getMouseCoords());

			glm::vec2 playerPosition(_player->getPosition());

			glm::vec2 direction = mouseCoords - playerPosition;
			direction = glm::normalize(direction);
			_bullets1.emplace_back(playerPosition, direction, 0.5f, 1000);
		}
		if (_inputManager.isKeyPressed(SDLK_i)) {
			bala = 2;
			glm::vec2 mouseCoords = _camera.convertScreenToWorl(_inputManager.getMouseCoords());

			glm::vec2 playerPosition(_player->getPosition());

			glm::vec2 direction = mouseCoords - playerPosition;
			direction = glm::normalize(direction);
			_bullets2.emplace_back(playerPosition, direction, 0.5f, 1000);
		}
		if (_inputManager.isKeyPressed(SDLK_o)) {
			bala = 3;
			glm::vec2 mouseCoords = _camera.convertScreenToWorl(_inputManager.getMouseCoords());

			glm::vec2 playerPosition(_player->getPosition());

			glm::vec2 direction = mouseCoords - playerPosition;
			direction = glm::normalize(direction);
			_bullets3.emplace_back(playerPosition, direction, 0.5f, 1000);
		}
	}
}

void MainGame::update() {

	while (_gameState != GameState::EXIT) {
		procesInput();
		draw();
		_camera.update();
		_time += 0.002f;
		for (int i = 0; i < _bullets.size();)
		{
			if(_bullets[i].update()){
				_bullets[i] = _bullets.back();
				_bullets.pop_back();
			}
			
			else {
				i++;
			}
		}
		for (int i = 0; i < _bullets1.size();)
		{
			if (_bullets1[i].update()) {
				_bullets1[i] = _bullets1.back();
				_bullets1.pop_back();
			}

			else {
				i++;
			}
		}
		for (int i = 0; i < _bullets2.size();)
		{
			if (_bullets2[i].update()) {
				_bullets2[i] = _bullets2.back();
				_bullets2.pop_back();
			}

			else {
				i++;
			}
		}
		for (int i = 0; i < _bullets3.size();)
		{
			if (_bullets3[i].update()) {
				_bullets3[i] = _bullets3.back();
				_bullets3.pop_back();
			}

			else {
				i++;
			}
		}
		updateAgents();
		_camera.setPosition(_player->getPosition());
	}
}

void MainGame::updateAgents() {
	for (int i = 0; i < _humans.size(); i++)
	{
		_humans[i]->update();
	}
}

MainGame::MainGame(): 
					  _witdh(800),
					  _height(600),
					  _gameState(GameState::PLAY),
					  _time(0),
					  _player(nullptr)
{
	_camera.init(_witdh, _height);
}


MainGame::~MainGame()
{
}
