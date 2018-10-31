//
// C00204076
// Brandon Seah-Dempsey
// Started at 9:42 31 October 2017
// Finished at
// Time Taken:
// Known Bugs:

#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>

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
	void update(sf::Time t_deltaTime); //Update game objects
	void render(); //Draw objects to screen

	sf::RenderWindow m_window; //SFML window for game
	bool is_running;

	

};

#endif // !GAME_H