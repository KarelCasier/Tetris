#include "PlayState.h"
#include <iostream>

const std::string PlayState::mStateID = "PLAY";

PlayState::PlayState()
: landed()
{
	font.loadFromFile("assets/MYRIADPRO-BOLD.OTF");

	//Play Area
	playArea.setSize(sf::Vector2f(350, 560));
	playArea.setFillColor(sf::Color(100, 100, 100, 255));
	playArea.setPosition(20, 20);

	//Side Area
	sideArea.setSize(sf::Vector2f(110, 600));
	sideArea.setFillColor(sf::Color(100, 100, 100, 255));
	sideArea.setPosition(390, 0);

	//next Text
	nextText.setFont(font);
	nextText.setCharacterSize(30);
	nextText.setString("NEXT");
	nextText.setOrigin(nextText.getLocalBounds().width / 2, nextText.getLocalBounds().height / 2);
	nextText.setPosition(sideArea.getPosition().x + sideArea.getLocalBounds().width / 2, sideArea.getPosition().y + 5);

	//Menu Button
	menuButton.setSize(sf::Vector2f(100, 50));
	menuButton.setFillColor(DarkGrey);
	menuButton.setOrigin(menuButton.getLocalBounds().width / 2, menuButton.getLocalBounds().height / 2);
	menuButton.setPosition(sideArea.getPosition() + sf::Vector2f(sideArea.getLocalBounds().width / 2, 0) + sf::Vector2f(0, 515));

	//Menu Text
	menuText.setFont(font);
	menuText.setCharacterSize(30);
	menuText.setString("MENU");
	menuText.setOrigin(menuText.getLocalBounds().width / 2, menuText.getLocalBounds().height / 2);
	menuText.setPosition(menuButton.getPosition().x, menuButton.getPosition().y - 10);

	//exit Button
	exitButton.setSize(sf::Vector2f(100, 50));
	exitButton.setFillColor(DarkGrey);
	exitButton.setOrigin(exitButton.getLocalBounds().width / 2, exitButton.getLocalBounds().height / 2);
	exitButton.setPosition(sideArea.getPosition() + sf::Vector2f(sideArea.getLocalBounds().width / 2, 0) + sf::Vector2f(0, 570));

	//exit Text
	exitText.setFont(font);
	exitText.setCharacterSize(30);
	exitText.setString("EXIT");
	exitText.setOrigin(exitText.getLocalBounds().width / 2, exitText.getLocalBounds().height / 2);
	exitText.setPosition(exitButton.getPosition().x, exitButton.getPosition().y - 10);

	int temp[16][10] =
	{
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
	};
	for (int row = 0; row != 16; row++)
	{
		for (int col = 0; col != 10; col++)
		{
			landed[row][col] = temp[row][col];
		}
	}

	srand((unsigned)time(NULL));

	newPiece();
}

void PlayState::processEvents(sf::Event event)
{
	switch (event.type)
	{
	case sf::Event::KeyPressed:
		handlePlayerInput(event.key.code, true);
		break;

	case sf::Event::KeyReleased:
		handlePlayerInput(event.key.code, false);
		break;
	}

	sf::Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);
	if (exitButton.getGlobalBounds().contains((float)mousePos.x, (float)mousePos.y))
	{
		GameStateManager::Instance()->clean();
	}
	else if (menuButton.getGlobalBounds().contains((float)mousePos.x, (float)mousePos.y))
	{
		GameStateManager::Instance()->changeGameState(new MainMenuState);
	}

	/*if ((mousePos.x > menuButton.getPosition().x - menuButton.getLocalBounds().width / 2) &&
		(mousePos.x < menuButton.getPosition().x + menuButton.getLocalBounds().width / 2) &&
		(mousePos.y > menuButton.getPosition().y - menuButton.getLocalBounds().height / 2) &&
		(mousePos.y < menuButton.getPosition().y + menuButton.getLocalBounds().height / 2))
		{
		}*/
}

void PlayState::update(sf::Time dtTime)
{
	if (moveLeft)
	{
		moveLeft = false;
		move(-1, 0);
	}
	if (moveRight)
	{
		moveRight = false;
		move(1, 0);
	}
	if (moveDown)
	{
		moveDown = false;
		move(0, 1);
	}
	if (moveRotate)
	{
		moveRotate = false;
		rotatePiece();
	}
	if (tickCount.getElapsedTime().asSeconds() > dropDelay)
	{
		move(0, 1);
		tickCount.restart();
	}
}

void PlayState::move(int x, int y)
{
	if (collisionTest(x, y))
	{
		if (y == 1)
		{
			if (sPiece.y < 1)
			{
				GameStateManager::Instance()->changeGameState(new GameOverState());
			}
			else
			{
				//Add piece to landed
				for (int row = 0; row != 4; row++)
				{
					for (int col = 0; col != 4; col++)
					{
						if (sPiece.size[row][col] != TILEBLANK)
						{
							landed[sPiece.y + row][sPiece.x + col] = sPiece.size[row][col];
						}
					}
				}

				//Check filled rows
				for (int row = 0; row != 16; row++)
				{
					bool filled{ true };

					for (int col = 0; col != 10; col++)
					{
						if (landed[row][col] == TILEBLANK)
						{
							filled = false;
						}
					}

					if (filled)
					{
						deleteRow(row);
					}
				}

				dropDelay -= .05;
				newPiece();
			}
		}
	}
	else //No collision, move piece
	{
		sPiece.x += x;
		sPiece.y += y;
	}
}

void PlayState::deleteRow(int r)
{
	for (int row = r; row != 0; row--) //Loop from row to delete to 1 (as we use row - 1)
	{
		//Move row above, down
		for (int col = 0; col != 10; col++)
		{
			landed[row][col] = landed[row - 1][col];
		}

	}
}

void PlayState::rotatePiece()
{
	//Create temporary array to check for collisions
	int temp[4][4];
	for (int row = 0; row != 4; row++)
	{
		for (int col = 0; col != 4; col++)
		{
			temp[3 - row][col] = sPiece.size[col][row]; //Inverse and flip -> rotate
		}
	}

	for (int row = 0; row != 4; row++)
	{
		for (int col = 0; col != 4; col++)
		{
			if (temp[row][col] != TILEBLANK)
			{
				if (sPiece.x + col < 0 || sPiece.x + col > 10 - 1 ||
					sPiece.y + row < 0 || sPiece.y + row > 16 - 1)
				{
					return;
				}
			}
		}
	}

	for (int row = 0; row != 4; row++)
	{
		for (int col = 0; col != 4; col++)
		{
			if (row >= sPiece.y && row < sPiece.y + 4)
			{
				if (col >= sPiece.x && col < sPiece.x + 4)
				{
					if (landed[row][col] != TILEBLANK)
					{
						if (temp[row - sPiece.y][col - sPiece.x] != TILEBLANK)
						{
							return;
						}
					}
				}
			}
		}
	}

	//If no collision, put temp array into sPiece array
	for (int row = 0; row != 4; row++)
	{
		for (int col = 0; col != 4; col++)
		{
			sPiece.size[row][col] = temp[row][col];
		}
	}
}

bool PlayState::collisionTest(int nx, int ny)
{
	int newX = sPiece.x + nx;
	int newY = sPiece.y + ny;

	//Check wall Collisions
	for (int row = 0; row != 4; row++)
	{
		for (int col = 0; col != 4; col++)
		{
			if (sPiece.size[row][col] != TILEBLANK)
			{
				if (newX + col < 0 || newX + col > 10 - 1 ||
					newY + row < 0 || newY + row > 16 - 1)
				{
					return true;
				}
			}
		}
	}
	//Check land collisions
	for (int row = 0; row != 16; row++)
	{
		for (int col = 0; col != 10; col++)
		{
			//Check to make sure it only checks within the 4x4 area
			if (col >= newX && col < newX + 4)
			{
				if (row >= newY && row < newY + 4)
				{
					if (landed[row][col] != TILEBLANK)
					{
						if (sPiece.size[row - newY][col - newX] != TILEBLANK)
						{
							return true;
						}
					}
				}
			}
		}
	}
	return false; //No collision
}

void PlayState::newPiece()
{
	//Pieces
	///////////////////////////////////////       /////////////////////////////
	//  0   1     2     3    4    5  6   //       // (0,0) (0,1) (0,2) (0,3) //
	///////////////////////////////////////       // (1,0) (1,1) (1,2) (1,3) //
	//  X              X     X           //       // (2,0) (2,1) (2,2) (2,3) //
	//  X  X X    X    XX   XX  XX  XX   //       // (3,0) (3,1) (3,2) (3,3) //
	//  X  X X  X X X   X   X    X  X    //       /////////////////////////////
	//  X                        X  X    //
	///////////////////////////////////////

	for (int row = 0; row != 4; row++)
	{
		for (int col = 0; col != 4; col++)
		{
			sPiece.size[row][col] = TILEBLANK; //Set all sPiece to zero
		}
	}

	sPiece.x = 3; //since array is 4x4, and board is 16x10. This centers the array inside the board
	sPiece.y = 0;

	if (firstPiece) //If new game, generate a piece rather then using sPrePiece
	{
		firstPiece = false;

		int newblock = rand() % 7;

		switch (newblock)
		{
		case 0: //Tower
			sPiece.size[1][0] = TILERED;
			sPiece.size[1][1] = TILERED;
			sPiece.size[1][2] = TILERED;
			sPiece.size[1][3] = TILERED;
			break;
		case 1: //Box
			sPiece.size[1][1] = TILEBLUE;
			sPiece.size[1][2] = TILEBLUE;
			sPiece.size[2][1] = TILEBLUE;
			sPiece.size[2][2] = TILEBLUE;
			break;
		case 2: //Pyramid
			sPiece.size[1][1] = TILETEAL;
			sPiece.size[0][2] = TILETEAL;
			sPiece.size[1][2] = TILETEAL;
			sPiece.size[2][2] = TILETEAL;
			break;
		case 3: //Left Leaner
			sPiece.size[0][1] = TILEYELLOW;
			sPiece.size[1][1] = TILEYELLOW;
			sPiece.size[1][2] = TILEYELLOW;
			sPiece.size[2][2] = TILEYELLOW;
			break;
		case 4: //Right Leaner
			sPiece.size[0][2] = TILEGREEN;
			sPiece.size[1][2] = TILEGREEN;
			sPiece.size[1][1] = TILEGREEN;
			sPiece.size[2][1] = TILEGREEN;
			break;
		case 5: //Left Knight
			sPiece.size[0][1] = TILEORANGE;
			sPiece.size[0][2] = TILEORANGE;
			sPiece.size[1][2] = TILEORANGE;
			sPiece.size[2][2] = TILEORANGE;
			break;
		case 6: //Right Knight
			sPiece.size[0][2] = TILEPURPLE;
			sPiece.size[0][1] = TILEPURPLE;
			sPiece.size[1][1] = TILEPURPLE;
			sPiece.size[2][1] = TILEPURPLE;
			break;
		}
	}
	else //If not first piece (not a new game) use the preview piece to generate the piece
	{
		for (int row = 0; row != 4; row++)
		{
			for (int col = 0; col != 4; col++)
			{
				sPiece.size[row][col] = sPrePiece.size[row][col];
			}
		}
	}

	//Generate sPrePiece
	//////////////////////////////////////////////////////////////////////////
	for (int row = 0; row != 4; row++)
	{
		for (int col = 0; col != 4; col++)
		{
			sPrePiece.size[row][col] = TILEBLANK; //Set all sPrePiece to zero
		}
	}

	sPrePiece.x = 0;
	sPrePiece.y = 0;

	int newblock = rand() % 7;

	switch (newblock)
	{
	case 0: //Tower
		sPrePiece.size[1][0] = TILERED;
		sPrePiece.size[1][1] = TILERED;
		sPrePiece.size[1][2] = TILERED;
		sPrePiece.size[1][3] = TILERED;
		break;
	case 1: //Box
		sPrePiece.size[1][1] = TILEBLUE;
		sPrePiece.size[1][2] = TILEBLUE;
		sPrePiece.size[2][1] = TILEBLUE;
		sPrePiece.size[2][2] = TILEBLUE;
		break;
	case 2: //Pyramid
		sPrePiece.size[1][1] = TILETEAL;
		sPrePiece.size[0][2] = TILETEAL;
		sPrePiece.size[1][2] = TILETEAL;
		sPrePiece.size[2][2] = TILETEAL;
		break;
	case 3: //Left Leaner
		sPrePiece.size[0][1] = TILEYELLOW;
		sPrePiece.size[1][1] = TILEYELLOW;
		sPrePiece.size[1][2] = TILEYELLOW;
		sPrePiece.size[2][2] = TILEYELLOW;
		break;
	case 4: //Right Leaner
		sPrePiece.size[0][2] = TILEGREEN;
		sPrePiece.size[1][2] = TILEGREEN;
		sPrePiece.size[1][1] = TILEGREEN;
		sPrePiece.size[2][1] = TILEGREEN;
		break;
	case 5: //Left Knight
		sPrePiece.size[0][1] = TILEORANGE;
		sPrePiece.size[0][2] = TILEORANGE;
		sPrePiece.size[1][2] = TILEORANGE;
		sPrePiece.size[2][2] = TILEORANGE;
		break;
	case 6: //Right Knight
		sPrePiece.size[0][2] = TILEPURPLE;
		sPrePiece.size[0][1] = TILEPURPLE;
		sPrePiece.size[1][1] = TILEPURPLE;
		sPrePiece.size[2][1] = TILEPURPLE;
		break;
	}
	//////////////////////////////////////////////////////////////////////////
}

void PlayState::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(playArea, states);

	//Draw landed array
	for (int row = 0; row != 16; row++)
	{
		for (int col = 0; col != 10; col++)
		{
			sf::RectangleShape *rect = new sf::RectangleShape();
			rect->setSize(sf::Vector2f(34, 34));
			rect->setOrigin(rect->getLocalBounds().width / 2, rect->getLocalBounds().height / 2);
			rect->setPosition(playArea.getPosition().x + col * 35 + rect->getLocalBounds().width / 2, playArea.getPosition().y + row * 35 + rect->getLocalBounds().height / 2);

			switch (landed[row][col])
			{
			case TILEBLANK:
				rect->setFillColor(DarkGrey);
				rect->setSize(sf::Vector2f(17, 17));
				rect->setOrigin(rect->getLocalBounds().width / 2, rect->getLocalBounds().height / 2);
				break;
			case TILERED:
				rect->setFillColor(Red);
				break;
			case TILEBLUE:
				rect->setFillColor(Blue);
				break;
			case TILETEAL:
				rect->setFillColor(Teal);
				break;
			case TILEYELLOW:
				rect->setFillColor(Yellow);
				break;
			case TILEGREEN:
				rect->setFillColor(Green);
				break;
			case TILEORANGE:
				rect->setFillColor(Orange);
				break;
			case TILEPURPLE:
				rect->setFillColor(Purple);
				break;
			}

			target.draw(*rect, states);
			delete rect;
		}
	}

	//Draw sPiece
	for (int row = 0; row != 4; row++)
	{
		for (int col = 0; col != 4; col++)
		{
			sf::RectangleShape *rect = new sf::RectangleShape();
			rect->setSize(sf::Vector2f(34, 34));
			rect->setOrigin(rect->getLocalBounds().width / 2, rect->getLocalBounds().height / 2);
			rect->setPosition(playArea.getPosition().x + (col + sPiece.x) * 35 + rect->getLocalBounds().width / 2, playArea.getPosition().y + (row + sPiece.y) * 35 + rect->getLocalBounds().height / 2);

			switch (sPiece.size[row][col])
			{
			case TILEBLANK:
				rect->setFillColor(sf::Color(0, 0, 0, 0));
				rect->setSize(sf::Vector2f(17, 17));
				rect->setOrigin(rect->getLocalBounds().width / 2, rect->getLocalBounds().height / 2);
				break;
			case TILERED:
				rect->setFillColor(Red);
				break;
			case TILEBLUE:
				rect->setFillColor(Blue);
				break;
			case TILETEAL:
				rect->setFillColor(Teal);
				break;
			case TILEYELLOW:
				rect->setFillColor(Yellow);
				break;
			case TILEGREEN:
				rect->setFillColor(Green);
				break;
			case TILEORANGE:
				rect->setFillColor(Orange);
				break;
			case TILEPURPLE:
				rect->setFillColor(Purple);
				break;
			}

			target.draw(*rect, states);
			delete rect;
		}
	}

	//////////////////////////////////////////////////////////////////////////
	//Side Area
	target.draw(sideArea, states);

	target.draw(nextText, states);

	//Draw sPrePiece
	for (int row = 0; row != 4; row++)
	{
		for (int col = 0; col != 4; col++)
		{
			sf::RectangleShape *rect = new sf::RectangleShape();
			rect->setSize(sf::Vector2f(27.5, 27.5));
			rect->setOrigin(rect->getLocalBounds().width / 2, rect->getLocalBounds().height / 2);
			rect->setPosition(sideArea.getPosition().x + col * 27.5 + rect->getLocalBounds().width / 2, sideArea.getPosition().y + row * 27.5 + rect->getLocalBounds().height / 2 + 30);

			switch (sPrePiece.size[row][col])
			{
			case TILEBLANK:
				rect->setFillColor(DarkGrey);
				rect->setSize(sf::Vector2f(13.75, 13.75));
				rect->setOrigin(rect->getLocalBounds().width / 2, rect->getLocalBounds().height / 2);
				break;
			case TILERED:
				rect->setFillColor(Red);
				break;
			case TILEBLUE:
				rect->setFillColor(Blue);
				break;
			case TILETEAL:
				rect->setFillColor(Teal);
				break;
			case TILEYELLOW:
				rect->setFillColor(Yellow);
				break;
			case TILEGREEN:
				rect->setFillColor(Green);
				break;
			case TILEORANGE:
				rect->setFillColor(Orange);
				break;
			case TILEPURPLE:
				rect->setFillColor(Purple);
				break;
			}

			target.draw(*rect, states);
			delete rect;
		}
	}

	target.draw(menuButton, states);
	target.draw(menuText, states);

	target.draw(exitButton, states);
	target.draw(exitText, states);
}

void PlayState::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::W)
		moveRotate = isPressed;
	else if (key == sf::Keyboard::A)
		moveLeft = isPressed;
	else if (key == sf::Keyboard::D)
		moveRight = isPressed;
	else if (key == sf::Keyboard::S)
		moveDown = isPressed;
	else if (key == sf::Keyboard::Space)
		skipTime = isPressed;
}

void PlayState::onEnter()
{
	std::cout << "Entering PlayState" << std::endl;
}

void PlayState::onExit()
{
	std::cout << "Exiting PlayState" << std::endl;
}