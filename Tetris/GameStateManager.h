#pragma once
#include <vector>
#include "GameState.h"

class GameStateManager : public sf::Drawable
{
public:
	static GameStateManager* Instance()
	{
		if (pInstance == nullptr)
		{
			pInstance = new GameStateManager;
			return pInstance;
		}
		return pInstance;
	}

	void processEvents(sf::Event event);
	void update(sf::Time dtTime);
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

	void popGameState();
	void pushGameState(GameState* gameState);
	void changeGameState(GameState* gameState);

	void clean();

private:
	static GameStateManager* pInstance;
	std::vector<GameState*> mGameStates;
};