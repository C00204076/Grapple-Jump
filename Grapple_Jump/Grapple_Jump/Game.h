// Game header file used for methods and functions related to Game
// C00204076
// Brandon Seah-Dempsey
// Started at 9:42 31 October 2018
// Finished at 15:07 11 April 2019
// Time Taken: 4 hours 39 minutes
// Known Bugs: None

#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>

class Player;
class Ground;
class HookPoint;
class TileMap;
class MiniMap;

//Enum class for switching current gamestate
enum class GameState
{
	SPLASH, LICENSE, MAIN, GAME
};

// Game class
class Game
{
public:
	Game();
	~Game();
	void setGameState(GameState gameMode);
	GameState getGameState();
	void run();

	void loadTextures();
	void initialise();

protected:
	GameState gameState;

private:
	void processEvents(); //Process all game events
	void processGameEvents(sf::Event&);
	void processInput();
	void update(sf::Time deltaTime); //Update game objects
	void render(); //Draw objects to screen

	sf::RenderWindow m_window; //SFML window for game
	bool is_running;

	sf::Sprite  m_targetSprite;
	sf::Texture m_playerTexture, m_otherTexture, m_groundTexture, m_hookTexture, m_targetTexture;
	sf::Vector2i m_mousePosition;
	sf::Vector2f m_mouseVector;
	sf::Vector2f m_penetrationVector;

	sf::View m_playerView, m_miniMapView;

	float m_mouseX;
	float m_mouseY;
	

	Player * m_player;
	Ground * m_ground[4];
	HookPoint * m_hookPoint[7];
	TileMap * m_tileMap;
	MiniMap * m_miniMap;
};

#include "Player.h"
#include "Ground.h"
#include "HookPoint.h"
#include "TileMap.h"
#include "MiniMap.h"

#endif // !GAME_H