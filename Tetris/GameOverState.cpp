#include "GameOverState.h"
#include <iostream>

const std::string GameOverState::mStateID = "GAMEOVER";

GameOverState::GameOverState()
{
	//Menu Button
	menuButton.setSize(sf::Vector2f(100, 50));
	menuButton.setFillColor(sf::Color(100, 100, 100, 255));
	menuButton.setOrigin(menuButton.getLocalBounds().width / 2, menuButton.getLocalBounds().height / 2);
	menuButton.setPosition(sf::Vector2f(250, 400));

	//Menu Text
	font.loadFromFile("assets/MYRIADPRO-BOLD.OTF");
	menuText.setFont(font);
	menuText.setCharacterSize(30);
	menuText.setString("MENU");
	menuText.setOrigin(menuText.getLocalBounds().width / 2, menuText.getLocalBounds().height / 2);
	menuText.setPosition(menuButton.getPosition().x, menuButton.getPosition().y - 10);

	//GameOver Text
	gameOverText.setFont(font);
	gameOverText.setCharacterSize(50);
	gameOverText.setString("GAMEOVER");
	gameOverText.setOrigin(gameOverText.getLocalBounds().width / 2, gameOverText.getLocalBounds().height / 2);
	gameOverText.setPosition(250, 150);
}

void GameOverState::processEvents(sf::Event event)
{
	if (event.type == sf::Event::MouseButtonPressed)
	{
		sf::Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);

		if ((mousePos.x > menuButton.getPosition().x - menuButton.getLocalBounds().width / 2) &&
			(mousePos.x < menuButton.getPosition().x + menuButton.getLocalBounds().width / 2) &&
			(mousePos.y > menuButton.getPosition().y - menuButton.getLocalBounds().height / 2) &&
			(mousePos.y < menuButton.getPosition().y + menuButton.getLocalBounds().height / 2))
		{
			//menuButton Clicked
			GameStateManager::Instance()->changeGameState(new MainMenuState());
		}
	}
}

void GameOverState::update(sf::Time dtTime)
{
}

void GameOverState::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(menuButton, states);
	target.draw(menuText, states);
	target.draw(gameOverText, states);
}

void GameOverState::onEnter()
{
	std::cout << "Entering GameOverState" << std::endl;
}

void GameOverState::onExit()
{
	std::cout << "Exiting GameOverState" << std::endl;
}