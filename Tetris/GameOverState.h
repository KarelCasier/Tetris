#pragma once
#include "GameStateManager.h"
#include "MainMenuState.h"

class GameOverState : public GameState
{
public:
	GameOverState();
	virtual void processEvents(sf::Event event);
	virtual void update(sf::Time dtTime);
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

	virtual void onEnter();
	virtual void onExit();

	virtual void resume() {};

	virtual std::string getStateID() const { return mStateID; };

protected:
	static const std::string mStateID;

	sf::RectangleShape menuButton;

	sf::Font font;
	sf::Text menuText;
	sf::Text gameOverText;
};
