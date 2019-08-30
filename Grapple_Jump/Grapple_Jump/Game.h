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
#include <vector>

//minimap starting X -9000
//minimap end X 3700
//minimap starting Y 0
//minimap end Y 5500

class Splash;
class License;
class MainMenu;
class GameOver;
class Loading;
class Player;
class Ground;
class HookPoint;
class MiniMap;
class MusicManager;
class Start;
class Goal;

//Enum class for switching current gamestate
enum class GameState
{
	SPLASH, LICENSE, MAIN, GAME, GAMEOVER, LOADING
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

protected:
	GameState gameState;

private:
	void loadTextures();
	void initialise();

	void processEvents(); //Process all game events
	void processGameEvents(sf::Event&);
	void processInput();
	void update(sf::Time deltaTime); //Update game objects
	void render(); //Draw objects to screen
	//void determineTile(int type, int x, int y);

	sf::RenderWindow m_window; //SFML window for game
	bool is_running;

	sf::Sprite  m_targetSprite;
	sf::Texture m_playerTexture, m_otherTexture, m_groundTexture, m_hookTexture, m_targetTexture, m_miniMapTexture;
	sf::Vector2i m_mousePosition;
	sf::Vector2f m_mouseVector;
	sf::Vector2f m_penetrationVector;

	sf::View m_playerView, m_miniMapView;

	float m_mouseX;
	float m_mouseY;
	
	Splash * m_splashScreen;
	License * m_licenseScreen;
	MainMenu * m_mainMenu;
	GameOver * m_gameOver;
	Loading * m_loading;
	Player * m_player;
	Player * m_miniPlayer;
	HookPoint * m_hookPoint[3];
	MiniMap * m_miniMap;
	MusicManager * m_musicPlayer;
	Start * m_start;
	Goal * m_goal;

	std::vector<Ground *> m_grounds;
};

#include "SplashScreen.h"
#include "LicenseScreen.h"
#include "MainMenu.h"
#include "GameOverScreen.h"
#include "LoadingScreen.h"
#include "Player.h"
#include "Ground.h"
#include "HookPoint.h"
#include "MiniMap.h"
#include "MusicManager.h"
#include "Start.h"
#include "Goal.h"

#endif // !GAME_H