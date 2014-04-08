#include "MainMenuState.h"
#include <iostream>

const std::string MainMenuState::mStateID = "MAINMENU";

MainMenuState::MainMenuState()
{
	//Play Button
	playButton.setSize(sf::Vector2f(100, 50));
	playButton.setFillColor(sf::Color(100, 100, 100, 255));
	playButton.setOrigin(playButton.getLocalBounds().width / 2, playButton.getLocalBounds().height / 2);
	playButton.setPosition(sf::Vector2f(250, 400));

	//Play Text
	font.loadFromFile("assets/MYRIADPRO-BOLD.OTF");
	playText.setFont(font);
	playText.setCharacterSize(30);
	playText.setString("PLAY");
	playText.setOrigin(playText.getLocalBounds().width / 2, playText.getLocalBounds().height / 2);
	playText.setPosition(playButton.getPosition().x, playButton.getPosition().y - 10);

	//Title
	Title.setFont(font);
	Title.setCharacterSize(50);
	Title.setString("TETRIS");
	Title.setOrigin(Title.getLocalBounds().width / 2, Title.getLocalBounds().height / 2);
	Title.setPosition(250, 150);

	footer.setFont(font);
	footer.setCharacterSize(10);
	footer.setString("Karel Casier");
	footer.setOrigin(footer.getLocalBounds().width / 2, footer.getLocalBounds().height / 2);
	footer.setPosition(250, 585);
}

void MainMenuState::processEvents(sf::Event event)
{
	if (event.type == sf::Event::MouseButtonPressed)
	{
		sf::Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);

		if ((mousePos.x > playButton.getPosition().x - playButton.getLocalBounds().width / 2) &&
			(mousePos.x < playButton.getPosition().x + playButton.getLocalBounds().width / 2) &&
			(mousePos.y > playButton.getPosition().y - playButton.getLocalBounds().height / 2) &&
			(mousePos.y < playButton.getPosition().y + playButton.getLocalBounds().height / 2))
		{
			//playButton Clicked
			GameStateManager::Instance()->changeGameState(new PlayState());
		}
	}
}

void MainMenuState::update(sf::Time dtTime)
{
}

void MainMenuState::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(playButton, states);
	target.draw(playText, states);
	target.draw(Title, states);
	target.draw(footer, states);
}

void MainMenuState::onEnter()
{
	std::cout << "Entering MainMenuState" << std::endl;
}

void MainMenuState::onExit()
{
	std::cout << "Exiting MainMenuState" << std::endl;
}