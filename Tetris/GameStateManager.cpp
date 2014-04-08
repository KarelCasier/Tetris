#include "GameStateManager.h"

GameStateManager* GameStateManager::pInstance = nullptr;

void GameStateManager::update(sf::Time dtTime)
{
	if (!mGameStates.empty())
	{
		mGameStates.back()->update(dtTime);
	}
}

void GameStateManager::processEvents(sf::Event event)
{
	if (!mGameStates.empty())
	{
		mGameStates.back()->processEvents(event);
	}
}

void GameStateManager::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (!mGameStates.empty())
	{
		mGameStates.back()->draw(target, states);
	}
}

void GameStateManager::popGameState()
{
	if (!mGameStates.empty())
	{
		mGameStates.back()->onExit();
		mGameStates.pop_back();
	}
	mGameStates.back()->resume();
}

void GameStateManager::pushGameState(GameState* gameState)
{
	mGameStates.push_back(gameState);
	mGameStates.back()->onEnter();
}

void GameStateManager::changeGameState(GameState* gameState)
{
	if (!mGameStates.empty())
	{
		if (mGameStates.back()->getStateID() != gameState->getStateID())
		{
			mGameStates.back()->onExit();
			mGameStates.pop_back();
		}
	}

	gameState->onEnter();
	mGameStates.push_back(gameState);
}

void GameStateManager::clean()
{
	if (!mGameStates.empty())
	{
		mGameStates.back()->onExit();

		delete mGameStates.back();

		mGameStates.clear();
	}
}