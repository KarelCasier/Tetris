#pragma once
//#include "GameState.h"
#include "GameStateManager.h"
#include "MainMenuState.h"
#include "GameOverState.h"
#include <ctime>
#include <cstdlib>

class PlayState : public GameState
{
public:
	enum TileColour { TILEBLANK, TILERED, TILEBLUE, TILETEAL, TILEYELLOW, TILEGREEN, TILEORANGE, TILEPURPLE };
public:
	PlayState();
	virtual void processEvents(sf::Event event);
	virtual void update(sf::Time dtTime);
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

	virtual void onEnter();
	virtual void onExit();

	virtual void resume() {};

	virtual std::string getStateID() const { return mStateID; };

private:
	void move(int x, int y);
	void newPiece();
	bool collisionTest(int nx, int ny);
	void rotatePiece();
	void deleteRow(int r);

	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

private:
	static const std::string mStateID;

	sf::Font font;
	sf::RectangleShape playArea;
	sf::RectangleShape sideArea;

	struct Piece
	{
		int size[4][4];
		int x;
		int y;
	};

	Piece sPrePiece;
	Piece sPiece;
	bool firstPiece{ true };

	//Buttons
	sf::RectangleShape menuButton;
	sf::Text menuText;

	sf::RectangleShape exitButton;
	sf::Text exitText;

	sf::Text nextText;

	int landed[16][10];// = { { 0 } };

	sf::Clock tickCount;
	double dropDelay{ 1 };

	bool moveLeft{ false };
	bool moveRight{ false };
	bool moveDown{ false };
	bool skipTime{ false };
	bool moveRotate{ false };

	//COLOURS:

	sf::Color Purple = sf::Color(147, 59, 207, 255);
	sf::Color Red = sf::Color(241, 95, 116, 255);
	sf::Color Orange = sf::Color(247, 109, 60, 255);
	sf::Color Yellow = sf::Color(247, 216, 66, 255);
	sf::Color Teal = sf::Color(44, 168, 194, 255);
	sf::Color Green = sf::Color(152, 203, 74, 255);
	sf::Color Grey = sf::Color(131, 144, 152, 255);
	sf::Color DarkGrey = sf::Color(101, 114, 122, 255);
	sf::Color Blue = sf::Color(84, 129, 232, 255);
	sf::Color Black = sf::Color::Black;
};
