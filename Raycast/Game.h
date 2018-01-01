#pragma once

#include "SDL.h"

class Game {
public:
	Game();
	~Game();

	void init(const char * title, int width, int height, bool fullscreen = false);

	void handleEvents();
	void update();
	void render();
	void clean();

	bool running();

	static SDL_Renderer* _renderer; // underscore this?
	static SDL_Event event;
private:
	bool _running;
	int _count;

	SDL_Window* _window;
};