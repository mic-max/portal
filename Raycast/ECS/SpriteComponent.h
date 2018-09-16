#pragma once

#include "Components.h"
#include "SDL.h"

class SpriteComponent : public Component {
private:
	PositionComponent* _position;
	SDL_Texture* _texture;
	SDL_Rect _srcRect, _destRect;

public:
	SpriteComponent() = default;
	SpriteComponent(const char* path) {
		//_texture = TextureManager::LoadTexture(path);
	}

	void init() override {
		_position = &entity->getComponent<PositionComponent>();

		_srcRect.x = _srcRect.y = 0;
		_srcRect.w = _srcRect.h = 32;
		_destRect.w = _destRect.h = 64;
	}

	void update() override {
		_destRect.x = (int) _position->getX();
		_destRect.y = (int) _position->getY();
	}

	void draw() override {
		//TextureManager::Draw(_texture, _srcRect, _destRect);
	}
};