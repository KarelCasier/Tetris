#pragma once
//#include "GameState.h"
#include "GameStateManager.h"
#include "PlayState.h"
class MainMenuState : public GameState
{
public:
	MainMenuState();
	virtual void processEvents(sf::Event event);
	virtual void update(sf::Time dtTime);
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

	virtual void onEnter();
	virtual void onExit();

	virtual void resume() {};

	virtual std::string getStateID() const { return mStateID; };

protected:
	static const std::string mStateID;

	sf::RectangleShape playButton;

	sf::Font font;
	sf::Text playText;
	sf::Text Title;
	sf::Text footer;
};
