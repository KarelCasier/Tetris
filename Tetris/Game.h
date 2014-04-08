#pragma once

#include <SFML/System/Time.hpp>
#include <SFML/Graphics.hpp>
#include "GameStateManager.h"
#include "MainMenuState.h"
#include <vector>
#include <memory>
#include <cmath>
#include <iostream>
#include <sstream>

class Game
{
public:
	Game();
	void run();

private:
	void processEvents();
	void update(sf::Time dtTime);
	void render();
	void handleUserInput(sf::Keyboard::Key key, bool isPressed);

private:
	//For FPS calculations and consistent movement
	static const sf::Time TimePerFrame;

	sf::RenderWindow mWindow;
};
