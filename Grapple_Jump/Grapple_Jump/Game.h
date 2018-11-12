//
// C00204076
// Brandon Seah-Dempsey
// Started at 9:42 31 October 2018
// Finished at
// Time Taken:
// Known Bugs:

#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>

class Player;
class Ground;

//Enum class for switching current gamestate
enum class GameState
{
	SPLASH, LICENSE, MAIN, GAME
};

//
class Game
{
public:
	Game();
	~Game();
	void setGameState(GameState gameMode);
	GameState getGameState();
	void run();

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

	sf::Texture m_playerTexture, m_otherTexture, m_groundTexture;

	Player * m_player;
	Ground * m_ground;
};

#include "Player.h"
#include "Ground.h"

#endif // !GAME_H