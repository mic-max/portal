#include "Game.h"
#include "Map.h"

#include "ECS/Components.h"

#include <iostream> // for testing

SDL_Renderer* Game::_renderer = nullptr;
SDL_Event Game::event;

Map* map;
Manager manager;

Game::Game() {
	_running = false;
	_count = 0;
}

Game::~Game() {
}

void Game::init(const char* title, int width, int height, bool fullscreen ) {
	int flags = 0;

	if (fullscreen)
		flags = SDL_WINDOW_FULLSCREEN;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		_running = false;
		return;
	}

	std::cout << "Subsystems Initialized" << std::endl;

	_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
	if (_window) {
		std::cout << "Window Created" << std::endl;
	}

	_renderer = SDL_CreateRenderer(_window, -1, 0);
	if (_renderer) {
		SDL_SetRenderDrawColor(_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		std::cout << "Renderer Created" << std::endl;
	}

	_running = true;
	auto& player(manager.addEntity()); // (2, 6) 0 angle, 0 sector
	map = new Map(&player);
}

void Game::handleEvents() {
	SDL_PollEvent(&event);

	switch (event.type) {
		case SDL_KEYDOWN:
		case SDL_KEYUP:
			switch (event.key.keysym.sym) {
				case 'w':
					std::cout << "KEY PRESS: W" << std::endl;
					break;
				case 's':
					std::cout << "KEY PRESS: S" << std::endl;
					break;
				case 'a':
					std::cout << "KEY PRESS: A" << std::endl;
					break;
				case 'd':
					std::cout << "KEY PRESS: D" << std::endl;
					break;
				case ' ':
					std::cout << "KEY PRESS: SPACE" << std::endl;
					break;
			}
			break;
		case SDL_QUIT:
			_running = false;
			break;
		default:
			break;
	}
}

void Game::update() {
	//std::cout << _count++ << std::endl;
	map->update();
	manager.update();
}

void Game::render() {
	SDL_RenderClear(_renderer);
	/* START OF RENDER */
	map->drawMap(800, 640);

	/* END OF RENDER */
	SDL_RenderPresent(_renderer);
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
}

void Game::clean() {
	SDL_DestroyWindow(_window);
	SDL_DestroyRenderer(_renderer);
	SDL_Quit();

	std::cout << "Game Cleaned" << std::endl;
}

bool Game::running() {
	return _running;
}