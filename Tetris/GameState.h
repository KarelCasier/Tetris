#pragma once
#include <SFML/Graphics.hpp>
#include <string>
class GameState : public sf::Drawable
{
public:
	virtual void processEvents(sf::Event event) = 0;
	virtual void update(sf::Time dtTime) = 0;
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const = 0;

	virtual void onEnter() = 0;
	virtual void onExit() = 0;

	virtual void resume() {};

	virtual std::string getStateID() const = 0;

protected:

	bool mLoadingComplete{ false };
	bool mExiting{ false };
};
