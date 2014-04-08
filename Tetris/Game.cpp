#include "Game.h"

const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f); // = 0.6 seconds per frame, therefore 60fps

Game::Game() : mWindow(sf::VideoMode(500, 600), "Tetris")
{
	GameStateManager::Instance()->changeGameState(new MainMenuState);
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen())
	{
		sf::Time elapsedTime = clock.restart(); //Note restart returns the time on the clock then restarts the clock
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > TimePerFrame) //Ensures that the logic is caught up before rendering again
		{
			timeSinceLastUpdate -= TimePerFrame;

			processEvents();
			update(TimePerFrame);
		}
		render();
	}
	mWindow.close();
}

void Game::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			GameStateManager::Instance()->clean();
			mWindow.close();
			break;
		case sf::Event::KeyPressed:
			handleUserInput(event.key.code, true);
			break;
		case sf::Event::KeyReleased:
			handleUserInput(event.key.code, false);
			break;
		}
		GameStateManager::Instance()->processEvents(event);
	}
}

void Game::update(sf::Time dtTime)
{
	GameStateManager::Instance()->update(dtTime);
}

void Game::render()
{
	mWindow.clear(sf::Color(150, 150, 150, 255));
	mWindow.draw(*GameStateManager::Instance());
	mWindow.display();
}

void Game::handleUserInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::Escape)
	{
		GameStateManager::Instance()->clean();
		mWindow.close();
	}
}