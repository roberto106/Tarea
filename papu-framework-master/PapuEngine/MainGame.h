#pragma once
#include <SDL\SDL.h>
#include <GL\glew.h>
#include "GLS_Program.h"
#include "Window.h"
#include "Camera2D.h"
#include <vector>
#include "SpriteBacth.h"
#include "InputManager.h"
#include "Bullet.h"
#include "Level.h"
#include "Player.h"
#include "Human.h"

enum class GameState
{
	PLAY, EXIT
};


class MainGame
{
private:
	int _witdh;
	int _height;
	float _time;
	Window _window;
	void init();
	void procesInput();
	GLS_Program _program;
	Camera2D _camera;
	SpriteBacth _spriteBacth;
	InputManager _inputManager;
	vector<Bullet> _bullets;
	vector<Bullet> _bullets1;
	vector<Bullet> _bullets2;
	vector<Bullet> _bullets3;
	vector<Level*> _levels;
	vector<Human*>  _humans;
	Player* _player;
	int _currenLevel;
	void initLevel();
	void updateAgents();
	
public:
	MainGame();
	~MainGame();
	GameState _gameState;
	void initShaders();
	void run();
	void draw();
	void update();
};

